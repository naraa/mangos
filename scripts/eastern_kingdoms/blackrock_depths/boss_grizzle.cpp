/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 MangosR2
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
SDName: Boss_Grizzle
SD%Complete: 100
SDComment:
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"

enum
{
    EMOTE_GENERIC_FRENZY_KILL  = -1000001,

    SPELL_GROUNDTREMOR         = 6524,
    SPELL_FRENZY               = 28371,
};

struct MANGOS_DLL_DECL boss_grizzleAI : public ScriptedAI
{
    boss_grizzleAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiGroundTremor_Timer;
    uint32 m_uiFrenzy_Timer;

    void Reset()
    {
        m_uiGroundTremor_Timer = 12000;
        m_uiFrenzy_Timer =0;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiGroundTremor_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_GROUNDTREMOR);
            m_uiGroundTremor_Timer = 8000;
        }else m_uiGroundTremor_Timer -= uiDiff;

        if (m_creature->GetHealthPercent() < 51.0f)
        {
            if (m_uiFrenzy_Timer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_FRENZY) == CAST_OK)
                {
                    DoScriptText(EMOTE_GENERIC_FRENZY_KILL, m_creature);
                    m_uiFrenzy_Timer = 15000;
                }
            }else m_uiFrenzy_Timer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_grizzle(Creature* pCreature)
{
    return new boss_grizzleAI(pCreature);
}

void AddSC_boss_grizzle()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_grizzle";
    pNewScript->GetAI = &GetAI_boss_grizzle;
    pNewScript->RegisterSelf();
}
