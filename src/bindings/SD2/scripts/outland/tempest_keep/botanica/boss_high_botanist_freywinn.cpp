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
SDName: Boss_High_Botanist_Freywinn
SD%Complete: 90
SDComment: some strange visual related to tree form(if aura lost before normal duration end). possible make summon&transform -process smoother(transform after delay)
SDCategory: Tempest Keep, The Botanica
EndScriptData */

#include "precompiled.h"

enum
{
    SAY_AGGRO                  = -1553000,
    SAY_KILL_1                 = -1553001,
    SAY_KILL_2                 = -1553002,
    SAY_TREE_1                 = -1553003,
    SAY_TREE_2                 = -1553004,
    SAY_DEATH                  = -1553005,

    SPELL_TRANQUILITY          = 34550,
    SPELL_TREE_FORM            = 34551,

    SPELL_SUMMON_FRAYER        = 34557,
    ENTRY_FRAYER               = 19953,

    SPELL_PLANT_WHITE          = 34759,
    SPELL_PLANT_GREEN          = 34761,
    SPELL_PLANT_BLUE           = 34762,
    SPELL_PLANT_RED            = 34763,
};

struct MANGOS_DLL_DECL boss_high_botanist_freywinnAI : public ScriptedAI
{
    boss_high_botanist_freywinnAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    GUIDList Adds_List;

    uint32 m_uiSummonSeedling_Timer;
    uint32 m_uiTreeForm_Timer;
    uint32 m_uiMoveCheck_Timer;
    uint32 m_uiDeadAddsCount;
    bool m_bMoveFree;

    void Reset()
    {
        Adds_List.clear();

        m_uiSummonSeedling_Timer = 6000;
        m_uiTreeForm_Timer = 30000;
        m_uiMoveCheck_Timer = 1000;
        m_uiDeadAddsCount = 0;
        m_bMoveFree = true;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustSummoned(Creature *summoned)
    {
        if (summoned->GetEntry() == ENTRY_FRAYER)
            Adds_List.push_back(summoned->GetObjectGuid());
    }

    void DoSummonSeedling()
    {
        switch(urand(0, 3))
        {
            case 0: DoCastSpellIfCan(m_creature,SPELL_PLANT_WHITE); break;
            case 1: DoCastSpellIfCan(m_creature,SPELL_PLANT_GREEN); break;
            case 2: DoCastSpellIfCan(m_creature,SPELL_PLANT_BLUE); break;
            case 3: DoCastSpellIfCan(m_creature,SPELL_PLANT_RED); break;
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_KILL_1 : SAY_KILL_2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiTreeForm_Timer < uiDiff)
        {
            DoScriptText(urand(0, 1) ? SAY_TREE_1 : SAY_TREE_2, m_creature);

            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(true);

            m_creature->RemoveAllAuras();

            DoCastSpellIfCan(m_creature, SPELL_SUMMON_FRAYER, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_TRANQUILITY,   CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_TREE_FORM,     CAST_TRIGGERED);

            m_creature->GetMotionMaster()->MoveIdle();
            m_bMoveFree = false;

            m_uiTreeForm_Timer = 75000;
        }else m_uiTreeForm_Timer -= uiDiff;

        if (!m_bMoveFree)
        {
            if (m_uiMoveCheck_Timer < uiDiff)
            {
                for(GUIDList::iterator itr = Adds_List.begin(); itr != Adds_List.end(); ++itr)
                {
                    if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
                    {
                        if (!pTemp->isAlive())
                        {
                            Adds_List.erase(itr);
                            ++m_uiDeadAddsCount;
                            break;
                        }
                    }
                }

                if (m_uiDeadAddsCount < 3 && m_uiTreeForm_Timer-30000 < uiDiff)
                    m_uiDeadAddsCount = 3;

                if (m_uiDeadAddsCount >= 3)
                {
                    Adds_List.clear();
                    m_uiDeadAddsCount = 0;

                    m_creature->InterruptNonMeleeSpells(true);
                    m_creature->RemoveAllAuras();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_bMoveFree = true;
                }
                m_uiMoveCheck_Timer = 500;
            }
            else m_uiMoveCheck_Timer -= uiDiff;

            return;
        }

        /*if (m_creature->HasAura(SPELL_TREE_FORM, EFFECT_INDEX_0) || m_creature->HasAura(SPELL_TRANQUILITY, EFFECT_INDEX_0))
            return;*/

        //one random seedling every 5 secs, but not in tree form
        if (m_uiSummonSeedling_Timer < uiDiff)
        {
            DoSummonSeedling();
            m_uiSummonSeedling_Timer = 6000;
        }else m_uiSummonSeedling_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_high_botanist_freywinn(Creature* pCreature)
{
    return new boss_high_botanist_freywinnAI(pCreature);
}

void AddSC_boss_high_botanist_freywinn()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_high_botanist_freywinn";
    pNewScript->GetAI = &GetAI_boss_high_botanist_freywinn;
    pNewScript->RegisterSelf();
}
