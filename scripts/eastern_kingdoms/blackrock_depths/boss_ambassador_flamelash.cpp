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
SDName: Boss_Ambassador_Flamelash
SD%Complete: 100
SDComment:
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_FIREBLAST           = 15573,
    NPC_BURNING_SPIRIT        = 9178,
};

struct MANGOS_DLL_DECL boss_ambassador_flamelashAI : public ScriptedAI
{
    boss_ambassador_flamelashAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiFireBlast_Timer;
    uint32 m_uiSpirit_Timer;
    int Rand;
    int RandX;
    int RandY;
    Creature* pSummoned;

    void Reset()
    {
        m_uiFireBlast_Timer = 2000;
        m_uiSpirit_Timer = 24000;
    }

    void SummonSpirits(Unit* pVictim)
    {
        Rand = rand()%10;
        switch(urand(0, 1))
        {
            case 0: RandX -= Rand; break;
            case 1: RandX += Rand; break;
        }
        Rand = 0;
        Rand = rand()%10;
        switch(urand(0, 1))
        {
            case 0: RandY -= Rand; break;
            case 1: RandY += Rand; break;
        }
        pSummoned = DoSpawnCreature(NPC_BURNING_SPIRIT, RandX, RandY, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000);
        if (pSummoned)
            pSummoned->AI()->AttackStart(pVictim);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFireBlast_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_FIREBLAST);
            m_uiFireBlast_Timer = 7000;
        }else m_uiFireBlast_Timer -= uiDiff;

        if (m_uiSpirit_Timer < uiDiff)
        {
            SummonSpirits(m_creature->getVictim());
            SummonSpirits(m_creature->getVictim());
            SummonSpirits(m_creature->getVictim());
            SummonSpirits(m_creature->getVictim());

            m_uiSpirit_Timer = 30000;
        }else m_uiSpirit_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_ambassador_flamelash(Creature* pCreature)
{
    return new boss_ambassador_flamelashAI(pCreature);
}

void AddSC_boss_ambassador_flamelash()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_ambassador_flamelash";
    pNewScript->GetAI = &GetAI_boss_ambassador_flamelash;
    pNewScript->RegisterSelf();
}
