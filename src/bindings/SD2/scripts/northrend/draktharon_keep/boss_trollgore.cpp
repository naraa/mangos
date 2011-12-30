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
SDName: Boss_Trollgore
SD%Complete: 80%
SDComment:
SDCategory: Drak'Tharon Keep
ToDo: fix corpse expl. && fix addeds (corpse && way of summon)  // more work is needed
EndScriptData */

#include "precompiled.h"
#include "draktharon_keep.h"

enum
{
    SAY_AGGRO                       = -1600000,
    SAY_CONSUME                     = -1600001,
    SAY_DEATH                       = -1600002,
    SAY_EXPLODE                     = -1600003,
    SAY_KILL                        = -1600004,

    SPELL_CRUSH                     = 49639, // Crushes your target, inflicting 150% melee damage.
    SPELL_INFECTED_WOUND            = 49637, // Increases the Physical damage taken by an enemy by 15% for 10 sec.
    SPELL_CORPSE_EXPLODE            = 49555, // (aura#226)
    SPELL_CORPSE_EXPLODE_H          = 59807, // (aura#226)
    SPELL_CONSUME                   = 49380, // Deals 1885 to 2115 Shadow damage to enemies within 50 yards (50 yrds around target hit). For every enemy damaged in this way, the caster gains a 2% damage increase.
    SPELL_CONSUME_H                 = 59803, // Deals 4713 to 5287 Shadow damage to enemies within 50 yards (50 yrds around target hit). For every enemy damaged in this way, the caster gains a 5% damage increase.

    SPELL_CORPSE_EXPLODE_PROC       = 49618, // Infests a nearby Drakkari Invader corpse, causing it to explode after a few seconds dealing 3770 to 4230 Nature damage to enemies within 5 yards.
    H_SPELL_CORPSE_EXPLODE_PROC     = 59809, // Infests a nearby Drakkari Invader corpse, causing it to explode after a few seconds dealing 9425 to 10575 Nature damage to enemies within 5 yards.

///-> used for Achiev
    SPELL_CONSUME_BUFF_H            = 59805,

    SPELL_INVADER_TAUNT             = 49405, // cast 49406

    SPELL_INVADER_A                 = 49456, 
    SPELL_INVADER_B                 = 49457,
    SPELL_INVADER_C                 = 49458,

};

///-> Temp achi Hack
#define ACHIEVEMENT			2151

const float PosSummon1[3] = {-259.59f, -652.49f, 26.52f};
const float PosSummon2[3] = {-261.60f, -658.71f, 26.51f};
const float PosSummon3[3] = {-262.05f, -665.71f, 26.49f};

/*######
## boss_trollgore
######*/

struct MANGOS_DLL_DECL boss_trollgoreAI : public ScriptedAI
{
    boss_trollgoreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_draktharon_keep*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_draktharon_keep* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiCrush_Timer;
    uint32 m_uiInfectedWound_Timer;
    uint32 m_uiConsumeTimer;
    uint32 m_uiCorpseExplode_Timer;

    uint32 m_uiWave_Timer;

///-> Achiev
    bool m_bAchievFailed;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_uiCrush_Timer          = 10000;
        m_uiInfectedWound_Timer  = 20000;
        m_uiConsumeTimer         = 15000;
        m_uiWave_Timer           = 2000;

        m_uiCorpseExplode_Timer = 10000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, NOT_STARTED);

        if (!m_bIsRegularMode)
            m_pInstance->SetSpecialAchievementCriteria(TYPE_CONSUME_JUNCTION, true);

        m_uiCheckTimer = 1000;
        m_bAchievFailed = false;
    }

    void SummonWaves()
    {
        if (Creature* pInvader1 = m_creature->SummonCreature(NPC_DRAKKARI_INVADER,PosSummon1[0],PosSummon1[1],PosSummon1[2],0, TEMPSUMMON_TIMED_DESPAWN, 150000))
            pInvader1->AI()->AttackStart(m_creature);
        if (Creature* pInvader2 = m_creature->SummonCreature(NPC_DRAKKARI_INVADER,PosSummon2[0],PosSummon2[1],PosSummon2[2],0, TEMPSUMMON_TIMED_DESPAWN, 150000))
            pInvader2->AI()->AttackStart(m_creature);
        if (Creature* pInvader3 = m_creature->SummonCreature(NPC_DRAKKARI_INVADER,PosSummon3[0],PosSummon3[1],PosSummon3[2],0, TEMPSUMMON_TIMED_DESPAWN, 150000))
            pInvader3->AI()->AttackStart(m_creature);
    }

    void JustSummoned(Creature* pSummoned)
    {
        Creature* pTarget = m_pInstance->GetSingleCreatureFromStorage(NPC_TROLLGORE);
        if (Creature* pSummoned = m_pInstance->GetSingleCreatureFromStorage(NPC_DRAKKARI_INVADER))
        {
            pSummoned->AddThreat(pTarget,1000.0f);
            pTarget->AddThreat(pSummoned);
            pSummoned->CastSpell(pSummoned,SPELL_INVADER_TAUNT,true);
        }
    }

    void CheckAchievement()
    {
        if (!m_pInstance)
            return;

        Creature* pTarget = m_pInstance->GetSingleCreatureFromStorage(NPC_TROLLGORE);
        if (pTarget)
        {
            SpellAuraHolderPtr holder = pTarget->GetSpellAuraHolder(SPELL_CONSUME_BUFF_H);
            if (holder)
            {
                if (holder->GetStackAmount() > 10)
                {
                    //m_pInstance->SetSpecialAchievementCriteria(TYPE_CONSUME_JUNCTION, false);
                    m_bAchievFailed = true;
                }
            }
         }
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, DONE);

        if (!m_bIsRegularMode && !m_bAchievFailed)
        {
            if (m_pInstance)
                m_pInstance->DoCompleteAchievement(ACHIEVEMENT);
        }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        Creature* pInvader = m_pInstance->GetSingleCreatureFromStorage(NPC_DRAKKARI_INVADER);
        //m_uiInvaderGuid = pInvader->GetObjectGuid();

        if (!m_bAchievFailed)
        {
            if (m_uiCheckTimer < uiDiff)
            {
                CheckAchievement();
                m_uiCheckTimer = 1000;
            }
            else m_uiCheckTimer -= uiDiff;
        }

        // Summon npcs
        if (m_uiWave_Timer < uiDiff)
        {
            SummonWaves();
            m_uiWave_Timer = 15000;
        }else m_uiWave_Timer -= uiDiff;

        // Crush
        if (m_uiCrush_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CRUSH) == CAST_OK)
                m_uiCrush_Timer = 10000;
        }else m_uiCrush_Timer -= uiDiff;

        // Infected Wound
        if (m_uiInfectedWound_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_INFECTED_WOUND) == CAST_OK)
                m_uiInfectedWound_Timer = 20000;
        }else m_uiInfectedWound_Timer -= uiDiff;

        if (m_uiConsumeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature,  m_bIsRegularMode ? SPELL_CONSUME : SPELL_CONSUME_H) == CAST_OK)
                m_uiConsumeTimer = 15000;
        }else m_uiConsumeTimer -= uiDiff;

        //Corpse Explosion
        if (m_uiCorpseExplode_Timer < uiDiff)
        {
            if (Creature* pCorpse = GetClosestCreatureWithEntry(m_creature, NPC_DRAKKARI_INVADER, 85.0f))
            {
                if (pCorpse->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                {                    
                    DoCast(pCorpse,m_bIsRegularMode ? SPELL_CORPSE_EXPLODE : SPELL_CORPSE_EXPLODE_H,true); 
                    DoScriptText(SAY_EXPLODE, m_creature);
                }
            }
            m_uiCorpseExplode_Timer = 15000;
        }else m_uiCorpseExplode_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_trollgore(Creature* pCreature)
{
    return new boss_trollgoreAI(pCreature);
}

/*######
## Drakkari Invader
######

struct MANGOS_DLL_DECL npc_drakkari_invaderAI : public ScriptedAI
{
    npc_drakkari_invaderAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_draktharon_keep*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_draktharon_keep* m_pInstance;
    bool m_bIsRegularMode;

    void Reset()
    {
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (m_creature->GetHealth() < uiDamage)
        {
            uiDamage = 0;
            if (!m_creature->HasFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE))
            {
                m_creature->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
                m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
                m_creature->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                m_creature->RemoveAllAuras();
                m_creature->InterruptNonMeleeSpells(false);
                m_creature->SetHealth(1);
                m_creature->GetMotionMaster()->Clear(false);
                m_creature->GetMotionMaster()->MoveIdle();
                m_creature->AttackStop();
                m_creature->StopMoving();
                m_creature->getHostileRefManager().clearReferences();
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_TROLLGORE) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
           return;

        if (!m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_drakkari_invader(Creature* pCreature)
{
    return new npc_drakkari_invaderAI(pCreature);
}*/


void AddSC_boss_trollgore()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_trollgore";
    pNewScript->GetAI = &GetAI_boss_trollgore;
    pNewScript->RegisterSelf();

    /*pNewScript = new Script;
    pNewScript->Name = "npc_drakkari_invader";
    pNewScript->GetAI = &GetAI_npc_drakkari_invader;
    pNewScript->RegisterSelf();*/
}
