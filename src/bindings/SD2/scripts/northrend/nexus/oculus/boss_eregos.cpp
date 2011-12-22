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
SDName: oculus
SD%Complete: %
SDComment:
SDCategory: Ley-Guardian Eregos
EndScriptData */

#include "precompiled.h"
#include "oculus.h"


/*###
#Ley-Guardian Eregos
####*/

enum
{
    SAY_AGGRO            = -1578030,
    SAY_KILL_1           = -1578031,
    SAY_KILL_2           = -1578032,
    SAY_KILL_3           = -1578033,
    SAY_DEATH            = -1578034,
    SAY_ARCANE_SHIELD    = -1578035,
    SAY_FIRE_SHIELD      = -1578036,
    SAY_NATURE_SHIELD    = -1578037,
    SAY_FRENZY           = -1578038,
    SAY_SPAWN            = -1578039,
};

struct MANGOS_DLL_DECL boss_eregosAI: public ScriptedAI
{
	boss_eregosAI(Creature* pCreature) : ScriptedAI(pCreature)
	{
		m_pInstance = (instance_oculus*)m_creature->GetInstanceData();
		m_bIsRegularMode = m_creature->GetMap()->IsRegularDifficulty();
		m_creature->addUnitState(UNIT_STAT_IGNORE_PATHFINDING);
		Reset();
	}

    instance_oculus* m_pInstance;
    bool m_bIsRegularMode;

    void Reset()
    {

        if (m_pInstance)
        {
           m_pInstance->SetData(TYPE_EREGOS, NOT_STARTED);
           if(m_pInstance->GetData(TYPE_UROM) == DONE)
           {
              m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
           }
           else
           {
              m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
           }
        }

///-> Flying stuff
        m_creature->SetLevitate(true);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_EREGOS, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EREGOS, FAIL);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(1,3))
        {
            case 1: DoScriptText(SAY_KILL_1,m_creature); break;
            case 2: DoScriptText(SAY_KILL_2,m_creature); break;
            case 3: DoScriptText(SAY_KILL_3,m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_EREGOS, DONE);
    }

///-> might not need
    /*void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (m_creature->HasAura(SPELL_PLANAR_SHIFT))
            damage = 0;
    }*/

    void MoveInLineOfSight(Unit* pWho)
    {
        if(pWho->GetTypeId() == TYPEID_PLAYER
           && m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE)
           && !((Player*)pWho)->isGameMaster()
           && m_creature->IsWithinDistInMap(pWho, 50.0f)
           && pWho->GetVehicle()
           && m_pInstance->GetData(TYPE_UROM) == DONE)
        {
              m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_boss_eregos(Creature* pCreature)
{
	return new boss_eregosAI(pCreature);
}

void AddSC_boss_eregos()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_eregos";
    pNewScript->GetAI = &GetAI_boss_eregos;
    pNewScript->RegisterSelf();
}

