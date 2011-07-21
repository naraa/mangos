/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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
SD%Complete: 95%
SDComment:
SDCategory: The Nexus, The Nexus
EndScriptData */

#include "precompiled.h"
#include "nexus.h"

bool DeadChaoticRift; // needed for achievement: Chaos Theory(2037)

enum eEnums
{
    // Spells
    SPELL_SPARK_N                       = 47751,
    SPELL_SPARK_H                       = 57062,
    SPELL_RIFT_SHIELD                   = 47748,
    SPELL_CHARGE_RIFT                   = 47747, // Works wrong (affect players, not rifts)
    SPELL_CREATE_RIFT                   = 47743, // Don't work, using WA
    SPELL_ARCANE_ATTRACTION             = 57063, // not used
    SPELL_CHAOTIC_ENERGY_BURST          = 47688,
    SPELL_CHARGED_CHAOTIC_ENERGY_BURST  = 47737,
    SPELL_ARCANEFORM                    = 48019, // Chaotic Rift visual

    // NPC's
    NPC_CRAZED_MANA_WRAITH              = 26746,
    NPC_CHAOTIC_RIFT                    = 26918,

    // Texts
    SAY_AGGRO                           = -1576010,
    SAY_DEATH                           = -1576011,
    SAY_RIFT                            = -1576012,
    SAY_SHIELD                          = -1576013,

    // Achievements
    ACHIEVEMENT_CHAOS_THEORY            = 2037,
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

struct MANGOS_DLL_DECL boss_anomalusAI : public ScriptedAI
{
    boss_anomalusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiPhase;
    uint32 m_uiSparkTimer;
    ObjectGuid m_ChaoticRiftGuid;

    void Reset()
    {
        m_uiPhase = 0;
        m_uiSparkTimer = 5*IN_MILLISECONDS;
        m_ChaoticRiftGuid.Clear();

        DeadChaoticRift = false;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, NOT_STARTED);
    }

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (!m_bIsRegularMode && !DeadChaoticRift)
        {
            AchievementEntry const *AchievChaosTheory = GetAchievementStore()->LookupEntry(ACHIEVEMENT_CHAOS_THEORY);
            if (AchievChaosTheory)
            {
                Map* pMap = m_creature->GetMap();
                if (pMap && pMap->IsDungeon())
                {
                    Map::PlayerList const &players = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        itr->getSource()->CompletedAchievement(AchievChaosTheory);
                }
            }
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANOMALUS, DONE);
    }

    void SummonRifts()
    {
        DoScriptText(SAY_SHIELD, m_creature);
        DoCast(m_creature, SPELL_RIFT_SHIELD);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        uint8 tmp = urand(0,5);
        Creature* pRift = m_creature->SummonCreature(NPC_CHAOTIC_RIFT, RiftLocation[tmp][0], RiftLocation[tmp][1], RiftLocation[tmp][2], 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
        if (pRift)
        {
            //DoCast(Rift, SPELL_CHARGE_RIFT);
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pRift->AI()->AttackStart(pTarget);

            m_ChaoticRiftGuid = pRift->GetObjectGuid();
            DoScriptText(SAY_RIFT , m_creature);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

       if (m_creature->HasAura(SPELL_RIFT_SHIELD))
       {
            if (!m_ChaoticRiftGuid.IsEmpty())
            {
                Unit* Rift = m_creature->GetMap()->GetUnit(m_ChaoticRiftGuid);
                if (Rift && Rift->isDead())
                {
                    m_creature->RemoveAurasDueToSpell(SPELL_RIFT_SHIELD);
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    m_ChaoticRiftGuid.Clear();
                }
                return;
            }
        }
        else
        {
            m_ChaoticRiftGuid.Clear();
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        if ((m_uiPhase == 0) && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.75))
        {
            m_uiPhase = 1;
            SummonRifts();
        }

        if ((m_uiPhase == 1) && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.50))
        {
            m_uiPhase = 2;
            SummonRifts();
        }

        if ((m_uiPhase == 2) && (m_creature->GetHealth() < m_creature->GetMaxHealth() * 0.25))
        {
            m_uiPhase = 3;
            SummonRifts();
        }

        if (m_uiSparkTimer < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
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

struct MANGOS_DLL_DECL npc_chaotic_riftAI : public Scripted_NoMovementAI
{
    npc_chaotic_riftAI(Creature *pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiChaoticEnergyBurstTimer;
    uint32 m_uiCrazedManaWraithTimer;

    void Reset()
    {
        m_uiChaoticEnergyBurstTimer = 1*IN_MILLISECONDS;
        m_uiCrazedManaWraithTimer = 5*IN_MILLISECONDS;
        m_creature->SetDisplayId(25206); //For some reason in DB models for ally and horde are different.
                                         //Model for ally (1126) does not show auras. Horde model works perfect.
                                         //Set model to horde number
        DoCast(m_creature, SPELL_ARCANEFORM, false);
    }

    void JustDied(Unit *pKiller)
    {
        DeadChaoticRift = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiChaoticEnergyBurstTimer < uiDiff)
        {
            Unit* Anomalus = m_creature->GetMap()->GetUnit(ObjectGuid(m_pInstance ? m_pInstance->GetData64(TYPE_ANOMALUS) : 0));
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (Anomalus && Anomalus->HasAura(SPELL_RIFT_SHIELD))
                    DoCast(pTarget, SPELL_CHARGED_CHAOTIC_ENERGY_BURST);
                else
                    DoCast(pTarget, SPELL_CHAOTIC_ENERGY_BURST);

            m_uiChaoticEnergyBurstTimer = 1*IN_MILLISECONDS;
        }
        else
            m_uiChaoticEnergyBurstTimer -= uiDiff;

        if (m_uiCrazedManaWraithTimer < uiDiff)
        {
            Creature* Wraith = m_creature->SummonCreature(NPC_CRAZED_MANA_WRAITH, m_creature->GetPositionX()+1, m_creature->GetPositionY()+1, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
            if (Wraith)
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    Wraith->AI()->AttackStart(pTarget);

            Unit* Anomalus = m_creature->GetMap()->GetUnit(ObjectGuid(m_pInstance ? m_pInstance->GetData64(TYPE_ANOMALUS) : 0));
            if (Anomalus && Anomalus->HasAura(SPELL_RIFT_SHIELD))
                m_uiCrazedManaWraithTimer = 5*IN_MILLISECONDS;
            else
                m_uiCrazedManaWraithTimer = 10*IN_MILLISECONDS;
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
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_anomalus";
    pNewScript->GetAI = &GetAI_boss_anomalus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_chaotic_rift";
    pNewScript->GetAI = &GetAI_npc_chaotic_rift;
    pNewScript->RegisterSelf();
}
