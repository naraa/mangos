/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 - 2012 Infinity_scriptdev2
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
SDName: Boss_Gatewatcher_Ironhand
SD%Complete: 75
SDComment:
SDCategory: Tempest Keep, The Mechanar
EndScriptData */

#include "precompiled.h"

enum
{
    SAY_AGGRO_1                    = -1554006,
    SAY_HAMMER_1                   = -1554007,
    SAY_HAMMER_2                   = -1554008,
    SAY_SLAY_1                     = -1554009,
    SAY_SLAY_2                     = -1554010,
    SAY_DEATH_1                    = -1554011,
    EMOTE_HAMMER                   = -1554012,

    SPELL_SHADOW_POWER             = 35322,
    SPELL_SHADOW_POWER_H           = 39193,
    SPELL_HAMMER_PUNCH             = 35326,
    SPELL_JACKHAMMER               = 35327,
    SPELL_JACKHAMMER_H             = 39194,
    SPELL_STREAM_OF_MACHINE_FLUID  = 35311,
};

struct MANGOS_DLL_DECL boss_gatewatcher_iron_handAI : public ScriptedAI
{
    boss_gatewatcher_iron_handAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiShadow_Power_Timer;
    uint32 m_uiJackhammer_Timer;
    uint32 m_uiStream_of_Machine_Fluid_Timer;

    void Reset()
    {
        m_uiShadow_Power_Timer = 25000;
        m_uiJackhammer_Timer = 45000;
        m_uiStream_of_Machine_Fluid_Timer = 55000;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO_1, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (urand(0, 1))
            return;

        DoScriptText(urand(0, 1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void JustDied(Unit* PKiller)
    {
        DoScriptText(SAY_DEATH_1, m_creature);

        if (!m_pInstance)
            return;

        //TODO: Add door check/open code
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Shadow Power
        if (m_uiShadow_Power_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SHADOW_POWER : SPELL_SHADOW_POWER_H);
            m_uiShadow_Power_Timer = urand(20000, 28000);
        }else m_uiShadow_Power_Timer -= uiDiff;

        //Jack Hammer
        if (m_uiJackhammer_Timer < uiDiff)
        {
            //TODO: expect cast this about 5 times in a row (?), announce it by emote only once
            DoScriptText(EMOTE_HAMMER, m_creature);
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_JACKHAMMER : SPELL_JACKHAMMER_H);

            //chance to yell, but not same time as emote (after spell in fact casted)
            if (urand(0, 4))
                DoScriptText(urand(0, 1) ? SAY_HAMMER_1 : SAY_HAMMER_2, m_creature);

            m_uiJackhammer_Timer = 30000;
        }else m_uiJackhammer_Timer -= uiDiff;

        //Stream of Machine Fluid
        if (m_uiStream_of_Machine_Fluid_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_STREAM_OF_MACHINE_FLUID);
            m_uiStream_of_Machine_Fluid_Timer = urand(35000, 50000);
        }else m_uiStream_of_Machine_Fluid_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_gatewatcher_iron_hand(Creature* pCreature)
{
    return new boss_gatewatcher_iron_handAI(pCreature);
}

void AddSC_boss_gatewatcher_iron_hand()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_gatewatcher_iron_hand";
    pNewScript->GetAI = &GetAI_boss_gatewatcher_iron_hand;
    pNewScript->RegisterSelf();
}
