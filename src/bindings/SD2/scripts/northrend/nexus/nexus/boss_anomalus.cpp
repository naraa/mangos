/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 - 2012 Infinity_sd2
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Anomalus
SD%Complete: 90%
SDComment:
TODO:::: Charge rift half implented now ( need anomluas to cast spell at rifts
-- side note while anom is in shield state rift is getting charge bonus effects

SDCategory: The Nexus, The Nexus
EndScriptData */

#include "precompiled.h"
#include "nexus.h"

enum
{
    // Spells
    SPELL_SPARK_N                      = 47751,
    SPELL_SPARK_H                      = 57062,
    SPELL_RIFT_SHIELD                  = 47748,

    // Chaotic Rift Stuff
    SPELL_CHAOTIC_RIFT_VISUAL          = 47686, /// Suppose to be the visual spells
    SPELL_CHARGE_RIFT                  = 47747, /// Works wrong (affect players, not rifts) ---- UNTESTED:X0
    SPELL_CREATE_RIFT                  = 47743, /// Don't work, using WA   --- UNTESTED:X0

    SPELL_RIFT_AURA                    = 47687,  /// 47688 && 47686 spells combined apply aura triggers
    SPELL_CHARGED_RIFT_AURA            = 47733,  /// 47737 && 47686 spells combined apply aura triggers

    SPELL_RIFT_SUMMON_AURA             = 47732,  /// aura to trigger summons wraiths  15 secs
    SPELL_CHARGED_RIFT_SUMMON_AURA     = 47742,  /// aura to trigger summons wraiths  6 secs

    SPELL_CHAOTIC_ENERGY_BURST         = 47688,  /// Unleashes a burst of chaotic energy at an enemy, dealing 244 to 406 Arcane damage and then jumping to additional nearby enemies.  Each jump reduces the damage by 50%.  Affects 3 total targets.
    SPELL_CHARGED_CHAOTIC_ENERGY_BURST = 47737,  /// Unleashes a burst of chaotic energy at an enemy, dealing 357 to 593 Arcane damage and then jumping to additional nearby enemies.  Each jump reduces the damage by 50%.  Affects 3 total targets.

    SPELL_ARCANE_ATTRACTION             = 57063,  /// Increases Arcane damage taken by 2000 for 10 sec.  -- 50 yards

    // Texts
    SAY_AGGRO                           = -1576006,
    SAY_DEATH                           = -1576010,
    SAY_RIFT                            = -1576007,
    SAY_SHIELD                          = -1576008,
    SAY_KILL                            = -1576009,

    EMOTE_OPEN_RIFT                     = -1576021,
    EMOTE_SHIELD                        = -1576022,
};

float RiftLocation[6][3]=
{
    {652.64f, -273.70f, -8.75f},
    {634.45f, -265.94f, -8.44f},
    {620.73f, -281.17f, -9.02f},
    {626.10f, -304.67f, -9.44f},
    {639.87f, -314.11f, -9.49f},
    {651.72f, -297.44f, -9.37f}
};

uint32 m_uiHowManyRifts;

/*####
# boss_anomalus
####*/

struct MANGOS_DLL_DECL boss_anomalusAI : public ScriptedAI
{
    boss_anomalusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_nexus*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_nexus* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiPhase;
    uint32 m_uiSparkTimer;
    uint32 m_uiCreateRiftTimer;
    ObjectGuid m_ChaoticRiftGuid;

    void Reset()
    {
        m_uiPhase = 0;
        m_uiSparkTimer = 5*IN_MILLISECONDS;
        m_ChaoticRiftGuid.Clear();
        m_uiCreateRiftTimer = 25000;

        m_uiHowManyRifts = 0;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ANOMALUS, IN_PROGRESS);

            if (!m_bIsRegularMode)
                m_pInstance->SetSpecialAchievementCriteria(TYPE_CHAOS_THEORY, true);
        }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ANOMALUS, FAIL);
            m_uiHowManyRifts = 0;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, DONE);
    }

    void SummonRifts()
    {
        DoScriptText(EMOTE_OPEN_RIFT, m_creature);

        uint8 tmp = urand(0,5);
        m_creature->SummonCreature(NPC_CHAOTIC_RIFT, RiftLocation[tmp][0], RiftLocation[tmp][1], RiftLocation[tmp][2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
        ++m_uiHowManyRifts;
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_CHAOTIC_RIFT)
        {
            m_ChaoticRiftGuid = pSummoned->GetObjectGuid();

            DoScriptText(SAY_RIFT, m_creature);

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void SummonedCreatureDespawn(Creature* pSummoned)
    {
        --m_uiHowManyRifts;

        if (pSummoned->GetObjectGuid() == m_ChaoticRiftGuid)
        {
            m_ChaoticRiftGuid.Clear();
        }
    }

///-> future function for future rewrite
/*  void ChargeTheRifts()
    {
        DoScriptText(SAY_SHIELD, m_creature);
        DoScriptText(EMOTE_SHIELD, m_creature);
        DoCast(m_creature, SPELL_RIFT_SHIELD);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }
*/

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!m_creature->HasAura(SPELL_RIFT_SHIELD))
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if (m_uiHowManyRifts == 0)
        {
            if (m_creature->HasAura(SPELL_RIFT_SHIELD))
            {
                m_creature->RemoveAurasDueToSpell(SPELL_RIFT_SHIELD);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
        }

        if ((m_uiPhase == 0) && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.75))
        {
            m_uiPhase = 1;
            SummonRifts();
///-> CHARGED STUFF WOULD GO HERE
            DoScriptText(SAY_SHIELD, m_creature);
            DoScriptText(EMOTE_SHIELD, m_creature);
            DoCast(m_creature, SPELL_RIFT_SHIELD);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        if ((m_uiPhase == 1) && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.50))
        {
            m_uiPhase = 2;
            SummonRifts();
///-> CHARGED STUFF WOULD GO HERE
            DoScriptText(SAY_SHIELD, m_creature);
            DoScriptText(EMOTE_SHIELD, m_creature);
            DoCast(m_creature, SPELL_RIFT_SHIELD);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        if ((m_uiPhase == 2) && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.25))
        {
            m_uiPhase = 3;
            SummonRifts();
///-> CHARGED STUFF WOULD GO HERE
            DoScriptText(SAY_SHIELD, m_creature);
            DoScriptText(EMOTE_SHIELD, m_creature);
            DoCast(m_creature, SPELL_RIFT_SHIELD);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        if (m_uiCreateRiftTimer < uiDiff)
        {
            SummonRifts();
            m_uiCreateRiftTimer = 25000;
        }
        else
            m_uiCreateRiftTimer -= uiDiff;

        if (m_uiSparkTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, m_bIsRegularMode ? SPELL_SPARK_N : SPELL_SPARK_H);
            m_uiSparkTimer = 5*IN_MILLISECONDS;
        }
        else
            m_uiSparkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_anomalus(Creature* pCreature)
{
    return new boss_anomalusAI (pCreature);
}

/*####
# npc_chaotic_rift
####*/

struct MANGOS_DLL_DECL npc_chaotic_riftAI : public Scripted_NoMovementAI
{
    npc_chaotic_riftAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (instance_nexus*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_nexus* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiCrazedManaWraithTimer;

    void Reset()
    {
///-> visual && Normal chaotic light attack combined in aura according to DBC values from spell  -- non_charged
        if (!m_creature->HasAura(SPELL_RIFT_AURA))
            DoCast(m_creature,SPELL_RIFT_AURA,true);
///-> aura summons wraiths according to DBC values from spell -- non_charged
        //if (!m_creature->HasAura(SPELL_RIFT_SUMMON_AURA))
          //  DoCast(m_creature,SPELL_RIFT_SUMMON_AURA,true);

        m_uiCrazedManaWraithTimer = 6*IN_MILLISECONDS;
    }

    void JustDied(Unit* pKiller)
    {
        --m_uiHowManyRifts;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (Unit* pAnomalus = m_pInstance->GetSingleCreatureFromStorage(NPC_ANOMALUS))
         {
             if (pAnomalus && pAnomalus->HasAura(SPELL_RIFT_SHIELD))
             {
///->   -- CHARGED
                 if (m_creature->HasAura(SPELL_RIFT_AURA))
                     DoCast(m_creature,SPELL_CHARGED_RIFT_AURA,true);
             }
             else
             {
///-> -- NoN_charged
                 if (!m_creature->HasAura(SPELL_RIFT_AURA))
                     DoCast(m_creature,SPELL_RIFT_AURA,true);
             }
         }
///-> walk around for charged wraith summon  unable to make wraith attack by summon by aura trigger
        if (m_uiCrazedManaWraithTimer < uiDiff)
        {
            Creature* pWraith = m_creature->SummonCreature(NPC_CRAZED_MANA_WRAITH, m_creature->GetPositionX()+1, m_creature->GetPositionY()+1, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
            if (pWraith)
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    pWraith->AI()->AttackStart(pTarget);

            Unit* pAnomalus = m_pInstance->GetSingleCreatureFromStorage(NPC_ANOMALUS);
            if (pAnomalus && pAnomalus->HasAura(SPELL_RIFT_SHIELD))
                m_uiCrazedManaWraithTimer = 6*IN_MILLISECONDS;
            else
                m_uiCrazedManaWraithTimer = 15*IN_MILLISECONDS;
        }
        else
            m_uiCrazedManaWraithTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_chaotic_rift(Creature* pCreature)
{
    return new npc_chaotic_riftAI (pCreature);
}

void AddSC_boss_anomalus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_anomalus";
    pNewScript->GetAI = &GetAI_boss_anomalus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_chaotic_rift";
    pNewScript->GetAI = &GetAI_npc_chaotic_rift;
    pNewScript->RegisterSelf();
}
