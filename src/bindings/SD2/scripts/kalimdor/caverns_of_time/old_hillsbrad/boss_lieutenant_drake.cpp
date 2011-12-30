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
SDName: Boss_Lieutenant_Drake
SD%Complete: 70
SDComment: Missing proper code for patrolling area after being spawned. Script for GO (barrels) quest 10283
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

#include "precompiled.h"
#include "old_hillsbrad.h"
#include "escort_ai.h"

/*######
## go_barrel_old_hillsbrad
######*/

bool GOUse_go_barrel_old_hillsbrad(Player* pPlayer, GameObject* pGo)
{
    if (ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData())
    {
        if (pInstance->GetData(TYPE_BARREL_DIVERSION) == DONE)
            return false;

        pInstance->SetData(TYPE_BARREL_DIVERSION, IN_PROGRESS);
    }
    return false;
}

/*######
## boss_lieutenant_drake
######*/

enum
{
    SAY_ENTER              = -1560006,
    SAY_AGGRO              = -1560007,
    SAY_SLAY1              = -1560008,
    SAY_SLAY2              = -1560009,
    SAY_MORTAL             = -1560010,
    SAY_SHOUT              = -1560011,
    SAY_DEATH              = -1560012,

    SPELL_WHIRLWIND         = 31909,
    SPELL_HAMSTRING         = 9080,
    SPELL_MORTAL_STRIKE     = 31911,
    SPELL_FRIGHTENING_SHOUT = 33789,
};

struct Location
{
    uint32 wpId;
    float x;
    float y;
    float z;
};

static Location DrakeWP[]=
{
    {0, 2125.84f, 88.2535f, 54.8830f},
    {1, 2111.01f, 93.8022f, 52.6356f},
    {2, 2106.70f, 114.753f, 53.1965f},
    {3, 2107.76f, 138.746f, 52.5109f},
    {4, 2114.83f, 160.142f, 52.4738f},
    {5, 2125.24f, 178.909f, 52.7283f},
    {6, 2151.02f, 208.901f, 53.1551f},
    {7, 2177.00f, 233.069f, 52.4409f},
    {8, 2190.71f, 227.831f, 53.2742f},
    {9, 2178.14f, 214.219f, 53.0779f},
    {10, 2154.99f, 202.795f, 52.6446f},
    {11, 2132.00f, 191.834f, 52.5709f},
    {12, 2117.59f, 166.708f, 52.7686f},
    {13, 2093.61f, 139.441f, 52.7616f},
    {14, 2086.29f, 104.950f, 52.9246f},
    {15, 2094.23f, 81.2788f, 52.6946f},
    {16, 2108.70f, 85.3075f, 53.3294f},
    {17, 2125.50f, 88.9481f, 54.7953f},
    {18, 2128.20f, 70.9763f, 64.4221f}
};

struct MANGOS_DLL_DECL boss_lieutenant_drakeAI : public ScriptedAI
{
    boss_lieutenant_drakeAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    bool m_bCanPatrol;
    uint32 wpId;

    uint32 m_uiWhirlwind_Timer;
    uint32 m_uiFear_Timer;
    uint32 m_uiMortalStrike_Timer;
    uint32 m_uiExplodingShout_Timer;

    void Reset()
    {
        m_bCanPatrol = true;
        wpId = 0;

        m_uiWhirlwind_Timer = 20000;
        m_uiFear_Timer = 30000;
        m_uiMortalStrike_Timer = 45000;
        m_uiExplodingShout_Timer = 25000;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //TODO: make this work
        if (m_bCanPatrol && wpId == 0)
        {
            m_creature->GetMotionMaster()->MovePoint(DrakeWP[0].wpId, DrakeWP[0].x, DrakeWP[0].y, DrakeWP[0].z);
            ++wpId;
        }

        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Whirlwind
        if (m_uiWhirlwind_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_WHIRLWIND);
            m_uiWhirlwind_Timer = urand(20000, 25000);
        }else m_uiWhirlwind_Timer -= uiDiff;

        //Fear
        if (m_uiFear_Timer < uiDiff)
        {
            DoScriptText(SAY_SHOUT, m_creature);
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FRIGHTENING_SHOUT);
            m_uiFear_Timer = urand(25000, 35000);
        }else m_uiFear_Timer -= uiDiff;

        //Mortal Strike
        if (m_uiMortalStrike_Timer < uiDiff)
        {
            DoScriptText(SAY_MORTAL, m_creature);
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_STRIKE);
            m_uiMortalStrike_Timer = urand(20000, 30000);
        }else m_uiMortalStrike_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_lieutenant_drake(Creature* pCreature)
{
    return new boss_lieutenant_drakeAI(pCreature);
}

void AddSC_boss_lieutenant_drake()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "go_barrel_old_hillsbrad";
    pNewScript->pGOUse = &GOUse_go_barrel_old_hillsbrad;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_lieutenant_drake";
    pNewScript->GetAI = &GetAI_boss_lieutenant_drake;
    pNewScript->RegisterSelf();
}
