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
SDName: Boss_Noxxion
SD%Complete: 100
SDComment:
SDCategory: Maraudon
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_TOXICVOLLEY          = 21687,
    SPELL_UPPERCUT             = 22916,
};

struct MANGOS_DLL_DECL boss_noxxionAI : public ScriptedAI
{
    boss_noxxionAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiToxicVolley_Timer;
    uint32 m_uiUppercut_Timer;
    uint32 m_uiAdds_Timer;
    uint32 m_uiInvisible_Timer;
    bool m_bInvisible;
    int Rand;
    int RandX;
    int RandY;
    Creature* pSummoned;

    void Reset()
    {
        m_uiToxicVolley_Timer = 7000;
        m_uiUppercut_Timer = 16000;
        m_uiAdds_Timer = 19000;
        m_uiInvisible_Timer = 15000;                            //Too much too low?
        m_bInvisible = false;
    }

    void SummonAdds(Unit* pVictim)
    {
        Rand = rand()%8;
        switch(urand(0, 1))
        {
            case 0: RandX = 0 - Rand; break;
            case 1: RandX = 0 + Rand; break;
        }
        Rand = 0;
        Rand = rand()%8;
        switch(urand(0, 1))
        {
            case 0: RandY = 0 - Rand; break;
            case 1: RandY = 0 + Rand; break;
        }
        Rand = 0;
        pSummoned = DoSpawnCreature(13456, RandX, RandY, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 90000);
        if (pSummoned)
            pSummoned->AI()->AttackStart(pVictim);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bInvisible && m_uiInvisible_Timer < uiDiff)
        {
            //Become visible again
            m_creature->setFaction(14);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            //Noxxion model
            m_creature->SetDisplayId(11172);
            m_bInvisible = false;
            //m_creature->m_canMove = true;
        } else if (m_bInvisible)
        {
            m_uiInvisible_Timer -= uiDiff;
            //Do nothing while invisible
            return;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiToxicVolley_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_TOXICVOLLEY);
            m_uiToxicVolley_Timer = 9000;
        }else m_uiToxicVolley_Timer -= uiDiff;

        if (m_uiUppercut_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_UPPERCUT);
            m_uiUppercut_Timer = 12000;
        }else m_uiUppercut_Timer -= uiDiff;

        if (!m_bInvisible && m_uiAdds_Timer < uiDiff)
        {
            //Inturrupt any spell casting
            //m_creature->m_canMove = true;
            m_creature->InterruptNonMeleeSpells(false);
            m_creature->setFaction(35);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            // Invisible Model
            m_creature->SetDisplayId(11686);
            SummonAdds(m_creature->getVictim());
            SummonAdds(m_creature->getVictim());
            SummonAdds(m_creature->getVictim());
            SummonAdds(m_creature->getVictim());
            SummonAdds(m_creature->getVictim());
            m_bInvisible = true;
            m_uiInvisible_Timer = 15000;

            m_uiAdds_Timer = 40000;
        }else m_uiAdds_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_noxxion(Creature* pCreature)
{
    return new boss_noxxionAI(pCreature);
}

void AddSC_boss_noxxion()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_noxxion";
    pNewScript->GetAI = &GetAI_boss_noxxion;
    pNewScript->RegisterSelf();
}
