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
SDName: Boss_Hungarfen
SD%Complete: 95
SDComment: Need confirmation if spell data are same in both modes. Summons should have faster rate in heroic
SDCategory: Coilfang Resevoir, Underbog
EndScriptData */

#include "precompiled.h"

/*****
* boss_hungarfen
*****/

enum
{
    SPELL_FOUL_SPORES  = 31673,
    SPELL_ACID_GEYSER  = 38739,
};

struct MANGOS_DLL_DECL boss_hungarfenAI : public ScriptedAI
{
    boss_hungarfenAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    bool m_bIsRegularMode;
    bool Root;
    uint32 m_uiMushroom_Timer;
    uint32 m_uiAcidGeyser_Timer;

    void Reset()
    {
        Root = false;
        m_uiMushroom_Timer = 5000;                              // 1 mushroom after 5s, then one per 10s. This should be different in heroic mode
        m_uiAcidGeyser_Timer = 10000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->GetHealthPercent() <= 20.0f)
        {
            if (!Root)
            {
                DoCastSpellIfCan(m_creature,SPELL_FOUL_SPORES);
                Root = true;
            }
        }

        if (m_uiMushroom_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                m_creature->SummonCreature(17990, pTarget->GetPositionX()+(rand()%8), pTarget->GetPositionY()+(rand()%8), pTarget->GetPositionZ(), (rand()%5), TEMPSUMMON_TIMED_DESPAWN, 22000);
            else
                m_creature->SummonCreature(17990, m_creature->GetPositionX()+(rand()%8), m_creature->GetPositionY()+(rand()%8), m_creature->GetPositionZ(), (rand()%5), TEMPSUMMON_TIMED_DESPAWN, 22000);

            m_uiMushroom_Timer = 10000;
        }else m_uiMushroom_Timer -= uiDiff;

        if (m_uiAcidGeyser_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                DoCastSpellIfCan(pTarget,SPELL_ACID_GEYSER);
            m_uiAcidGeyser_Timer = urand(10000, 17500);
        }else m_uiAcidGeyser_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_hungarfen(Creature* pCreature)
{
    return new boss_hungarfenAI(pCreature);
}

/*****
* mob_underbog_mushroom
*****/

enum
{
    SPELL_SPORE_CLOUD      = 34168,
    SPELL_PUTRID_MUSHROOM  = 31690,
    SPELL_GROW             = 31698,
};

struct MANGOS_DLL_DECL mob_underbog_mushroomAI : public ScriptedAI
{
    mob_underbog_mushroomAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool m_bStop;
    uint32 m_uiGrow_Timer;
    uint32 m_uiShrink_Timer;

    void Reset()
    {
        m_bStop = false;
        m_uiGrow_Timer = 0;
        m_uiShrink_Timer = 20000;

        DoCastSpellIfCan(m_creature, SPELL_PUTRID_MUSHROOM, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_SPORE_CLOUD, CAST_TRIGGERED);
    }

    void MoveInLineOfSight(Unit *pWho) { return; }

    void AttackStart(Unit* pWho) { return; }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bStop)
            return;

        if (m_uiGrow_Timer <= uiDiff)
        {
            DoCastSpellIfCan(m_creature,SPELL_GROW);
            m_uiGrow_Timer = 3000;
        }else m_uiGrow_Timer -= uiDiff;

        if (m_uiShrink_Timer <= uiDiff)
        {
            m_creature->RemoveAurasDueToSpell(SPELL_GROW);
            m_bStop = true;
        }else m_uiShrink_Timer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_underbog_mushroom(Creature* pCreature)
{
    return new mob_underbog_mushroomAI(pCreature);
}

void AddSC_boss_hungarfen()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_hungarfen";
    pNewScript->GetAI = &GetAI_boss_hungarfen;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_underbog_mushroom";
    pNewScript->GetAI = &GetAI_mob_underbog_mushroom;
    pNewScript->RegisterSelf();
}
