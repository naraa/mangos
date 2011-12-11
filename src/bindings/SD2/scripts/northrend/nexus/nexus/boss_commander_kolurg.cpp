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
SDName: Boss Commander Stoutbeard
SD%Complete: 0
SDComment:
SDCategory: Nexus
EndScriptData */

#include "precompiled.h"
#include "nexus.h"

enum
{
    SAY_AGGRO                                          = -1576024,   // need correct text
    SAY_KILL                                           = -1576025,   // need correct text
    SAY_DEATH                                          = -1576026,   // need correct text

    SPELL_BATTLE_SHOUT                                 = 31403,  // Increases the melee attack power of nearby friendly targets for 2 min.
    SPELL_CHARGE                                       = 60067,  // Charges an enemy, inflicting normal damage plus 75 and stuns the opponent for 2 sec.
    SPELL_FRIGHTENING_SHOUT                            = 19134,  // Shouts at nearby enemies causing them to flee in fear for 6 sec
    SPELL_WHIRLWIND_1                                  = 38618,  // triggers spell 38619 Attacks nearby enemies in a whirlwind of steel that lasts until cancelled. and inflicts double damage
    SPELL_WHIRLWIND_2                                  = 38619   // Attacks nearby enemies in a whirlwind of steel that inflicts 200% of weapon damage.
};

/*####
# boss_commander_kolurg
####*/

struct MANGOS_DLL_DECL boss_commander_kolurgAI : public ScriptedAI // triggers spell 38619 Attacks nearby enemies in a whirlwind of steel that lasts until cancelled. and inflicts double damage
{
    boss_commander_kolurgAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
	bool m_bIsRegularMode;

    uint32 SPELL_BATTLE_SHOUT_Timer;
    uint32 SPELL_CHARGE_Timer;
    uint32 SPELL_FRIGHTENING_SHOUT_Timer;
    uint32 SPELL_WHIRLWIND_1_Timer;
    uint32 SPELL_WHIRLWIND_2_Timer;

    void Reset()
    {
        SPELL_BATTLE_SHOUT_Timer = 3000;   // needs adjusting
        SPELL_CHARGE_Timer = 2000;        // needs adjusting
        SPELL_FRIGHTENING_SHOUT_Timer = 2000;  // needs adjusting
        SPELL_WHIRLWIND_1_Timer = 0;   // THIS IS NOT RIGHT JUST A PLACEHOLDER FOR NOW
        SPELL_WHIRLWIND_2_Timer = 2000;   // needs adjusting


        if (m_pInstance)
            m_pInstance->SetData(TYPE_COMMANDER, NOT_STARTED);
    }

    void EnterCombat(Unit* pWho)
    {
        //DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COMMANDER, IN_PROGRESS);
    }

    //void AttackStart(Unit* pWho) {}

    //void MoveInLineOfSight(Unit* pWho) {}

    void KilledUnit(Unit* pVictim)
    {
        //DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        //DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COMMANDER, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (SPELL_BATTLE_SHOUT_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BATTLE_SHOUT);
            SPELL_BATTLE_SHOUT_Timer = 3000 + rand()%5000;
        }else SPELL_BATTLE_SHOUT_Timer -= uiDiff;

        if (SPELL_CHARGE_Timer < uiDiff)  // this spell needs to be a distance check on victims in distance not a timer on victim
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CHARGE);
            SPELL_CHARGE_Timer = 2000 + rand()%5000;
        }else SPELL_CHARGE_Timer -= uiDiff;

        if (SPELL_FRIGHTENING_SHOUT_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FRIGHTENING_SHOUT);
            SPELL_FRIGHTENING_SHOUT_Timer = 2000 + rand()%5000;
        }else SPELL_FRIGHTENING_SHOUT_Timer -= uiDiff;

        if (SPELL_WHIRLWIND_2_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_WHIRLWIND_2);
            SPELL_WHIRLWIND_2_Timer = 2000 + rand()%5000;
        }else SPELL_WHIRLWIND_2_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_commander_kolurg(Creature* pCreature)
{
    return new boss_commander_kolurgAI (pCreature);
}

void AddSC_boss_commander_kolurg()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_commander_kolurg";
    pNewScript->GetAI = &GetAI_boss_commander_kolurg;
    pNewScript->RegisterSelf();
}
