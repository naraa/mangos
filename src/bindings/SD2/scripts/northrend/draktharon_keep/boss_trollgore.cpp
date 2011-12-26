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
SDName: Boss_Trollgore
SD%Complete: 20%
SDComment:
SDCategory: Drak'Tharon Keep
EndScriptData */

#include "precompiled.h"
#include "draktharon_keep.h"

enum
{
    SAY_AGGRO                       = -1600000,
    SAY_CONSUME                     = -1600001,
    SAY_DEATH                       = -1600002,
    SAY_EXPLODE                     = -1600003,
    SAY_KILL                        = -1600004,

    SPELL_CRUSH                     = 49639,
    SPELL_INFECTED_WOUND            = 49367,
    SPELL_CORPSE_EXPLODE            = 49555,
    H_SPELL_CORPSE_EXPLODE          = 59087,
    SPELL_CONSUME                   = 49380,
    H_SPELL_CONSUME                 = 59803,
    SPELL_CONSUME_BUFF              = 49381,
    H_SPELL_CONSUME_BUFF            = 59805,

    SPELL_CORPSE_EXPLODE_PROC       = 49618,
    H_SPELL_CORPSE_EXPLODE_PROC     = 59809,
};

/*######
## boss_trollgore
######*/

struct MANGOS_DLL_DECL boss_trollgoreAI : public ScriptedAI
{
    boss_trollgoreAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_draktharon_keep*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_draktharon_keep* m_pInstance;
    bool m_bIsRegularMode;

    void Reset()
    {
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim->GetCharmerOrOwnerPlayerOrPlayerItself())
            DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_trollgore(Creature* pCreature)
{
    return new boss_trollgoreAI(pCreature);
}

void AddSC_boss_trollgore()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_trollgore";
    pNewScript->GetAI = &GetAI_boss_trollgore;
    pNewScript->RegisterSelf();
}
