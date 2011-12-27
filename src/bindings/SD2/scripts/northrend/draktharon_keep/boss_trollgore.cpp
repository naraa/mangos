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
SD%Complete: %
SDComment:
SDCategory: Drak'Tharon Keep
ToDo: fix corpse expl, other minor things and achievement
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

    SPELL_CRUSH                     = 49639, // Crushes your target, inflicting 150% melee damage.
    SPELL_INFECTED_WOUND            = 49637, // Increases the Physical damage taken by an enemy by 15% for 10 sec.
    SPELL_CORPSE_EXPLODE            = 49555, // (aura#226)
    H_SPELL_CORPSE_EXPLODE          = 59807, // (aura#226)
    SPELL_CONSUME                   = 49380, // Deals 1885 to 2115 Shadow damage to enemies within 50 yards (50 yrds around target hit). For every enemy damaged in this way, the caster gains a 2% damage increase.
    H_SPELL_CONSUME                 = 59803, // Deals 4713 to 5287 Shadow damage to enemies within 50 yards (50 yrds around target hit). For every enemy damaged in this way, the caster gains a 5% damage increase.

    SPELL_CORPSE_EXPLODE_PROC       = 49618, // Infests a nearby Drakkari Invader corpse, causing it to explode after a few seconds dealing 3770 to 4230 Nature damage to enemies within 5 yards.
    H_SPELL_CORPSE_EXPLODE_PROC     = 59809, // Infests a nearby Drakkari Invader corpse, causing it to explode after a few seconds dealing 9425 to 10575 Nature damage to enemies within 5 yards.
};

const float PosSummon1[3] = {-259.59f, -652.49f, 26.52f};
const float PosSummon2[3] = {-261.60f, -658.71f, 26.51f};
const float PosSummon3[3] = {-262.05f, -665.71f, 26.49f};

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

    uint32 m_uiCrush_Timer;
    uint32 m_uiInfectedWound_Timer;

    void Reset()
    {
        m_uiCrush_Timer = 10000;
        m_uiInfectedWound_Timer = 20000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TROLLGORE, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
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

        // Crush
        if (m_uiCrush_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CRUSH) == CAST_OK)
                m_uiCrush_Timer = 10000;
        }else m_uiCrush_Timer -= uiDiff;

        // Infected Wound
        if (m_uiInfectedWound_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_INFECTED_WOUND) == CAST_OK)
                m_uiInfectedWound_Timer = 20000;
        }else m_uiInfectedWound_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_trollgore(Creature* pCreature)
{
    return new boss_trollgoreAI(pCreature);
}

/*######
## Drakkari Invader
######

struct MANGOS_DLL_DECL npc_invaderAI : public ScriptedAI
{
};

CreatureAI* GetAI_npc_invader(Creature* pCreature)
{
    return new npc_invaderAI(pCreature);
}
*/

void AddSC_boss_trollgore()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_trollgore";
    pNewScript->GetAI = &GetAI_boss_trollgore;
    pNewScript->RegisterSelf();
}
