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
SDName: Boss_General_Angerforge
SD%Complete: 100
SDComment:
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_MIGHTYBLOW           = 14099,
    SPELL_HAMSTRING            = 9080,
    SPELL_CLEAVE               = 20691,

    NPC_RESERVIST              = 8901,
    NPC_RAGE_MEDIC             = 8894,
};

struct MANGOS_DLL_DECL boss_general_angerforgeAI : public ScriptedAI
{
    boss_general_angerforgeAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiMightyBlow_Timer;
    uint32 m_uiHamString_Timer;
    uint32 m_uiCleave_Timer;
    uint32 m_uiAdds_Timer;
    bool m_bMedics;
    int Rand1;
    int Rand1X;
    int Rand1Y;
    int Rand2;
    int Rand2X;
    int Rand2Y;
    Creature* pSummonedAdds;
    Creature* pSummonedMedics;

    void Reset()
    {
        m_uiMightyBlow_Timer = 8000;
        m_uiHamString_Timer = 12000;
        m_uiCleave_Timer = 16000;
        m_uiAdds_Timer = 0;
        m_bMedics = false;
    }

    void SummonAdds(Unit* pVictim)
    {
        Rand1 = rand()%15;
        switch(urand(0, 1))
        {
            case 0: Rand1X = 0 - Rand1; break;
            case 1: Rand1X = 0 + Rand1; break;
        }
        Rand1 = 0;
        Rand1 = rand()%15;
        switch(urand(0, 1))
        {
            case 0: Rand1Y = 0 - Rand1; break;
            case 1: Rand1Y = 0 + Rand1; break;
        }
        Rand1 = 0;
        pSummonedAdds = DoSpawnCreature(NPC_RESERVIST, Rand1X, Rand1Y, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120000);
        if (pSummonedAdds)
            pSummonedAdds->AI()->AttackStart(pVictim);
    }

    void SummonMedics(Unit* pVictim)
    {
        Rand2 = rand()%10;
        switch(urand(0, 1))
        {
            case 0: Rand2X = 0 - Rand2; break;
            case 1: Rand2X = 0 + Rand2; break;
        }
        Rand2 = 0;
        Rand2 = rand()%10;
        switch(urand(0, 1))
        {
            case 0: Rand2Y = 0 - Rand2; break;
            case 1: Rand2Y = 0 + Rand2; break;
        }
        Rand2 = 0;
        pSummonedMedics = DoSpawnCreature(NPC_RAGE_MEDIC, Rand2X, Rand2Y, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 120000);
        if (pSummonedMedics)
            pSummonedMedics->AI()->AttackStart(pVictim);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiMightyBlow_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_MIGHTYBLOW);
            m_uiMightyBlow_Timer = 18000;
        }else m_uiMightyBlow_Timer -= uiDiff;

        if (m_uiHamString_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_HAMSTRING);
            m_uiHamString_Timer = 15000;
        }else m_uiHamString_Timer -= uiDiff;

        if (m_uiCleave_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE);
            m_uiCleave_Timer = 9000;
        }else m_uiCleave_Timer -= uiDiff;

        //Adds_Timer
        if (m_creature->GetHealthPercent() < 21.0f)
        {
            if (m_uiAdds_Timer < uiDiff)
            {
                // summon 3 Adds every 25s
                SummonAdds(m_creature->getVictim());
                SummonAdds(m_creature->getVictim());
                SummonAdds(m_creature->getVictim());

                m_uiAdds_Timer = 25000;
            } else m_uiAdds_Timer -= uiDiff;
        }

        //Summon Medics
        if (!m_bMedics && m_creature->GetHealthPercent() < 21.0f)
        {
            SummonMedics(m_creature->getVictim());
            SummonMedics(m_creature->getVictim());
            m_bMedics = true;
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_general_angerforge(Creature* pCreature)
{
    return new boss_general_angerforgeAI(pCreature);
}

void AddSC_boss_general_angerforge()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_general_angerforge";
    pNewScript->GetAI = &GetAI_boss_general_angerforge;
    pNewScript->RegisterSelf();
}
