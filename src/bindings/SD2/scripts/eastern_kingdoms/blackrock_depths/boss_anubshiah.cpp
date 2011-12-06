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
SDName: Boss_Anubshiah
SD%Complete: 100
SDComment:
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_SHADOWBOLT           = 17228,
    SPELL_CURSEOFTONGUES       = 15470,
    SPELL_CURSEOFWEAKNESS      = 17227,
    SPELL_DEMONARMOR           = 11735,
    SPELL_ENVELOPINGWEB        = 15471,
};

struct MANGOS_DLL_DECL boss_anubshiahAI : public ScriptedAI
{
    boss_anubshiahAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiShadowBolt_Timer;
    uint32 m_uiCurseOfTongues_Timer;
    uint32 m_uiCurseOfWeakness_Timer;
    uint32 m_uiDemonArmor_Timer;
    uint32 m_uiEnvelopingWeb_Timer;

    void Reset()
    {
        m_uiShadowBolt_Timer = 7000;
        m_uiCurseOfTongues_Timer = 24000;
        m_uiCurseOfWeakness_Timer = 12000;
        m_uiDemonArmor_Timer = 3000;
        m_uiEnvelopingWeb_Timer = 16000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiShadowBolt_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_SHADOWBOLT);
            m_uiShadowBolt_Timer = 7000;
        }else m_uiShadowBolt_Timer -= uiDiff;

        if (m_uiCurseOfTongues_Timer < uiDiff)
        {
            Unit* pTarget = NULL;
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
            if (pTarget) DoCastSpellIfCan(pTarget,SPELL_CURSEOFTONGUES);
            m_uiCurseOfTongues_Timer = 18000;
        }else m_uiCurseOfTongues_Timer -= uiDiff;

        if (m_uiCurseOfWeakness_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CURSEOFWEAKNESS);
            m_uiCurseOfWeakness_Timer = 45000;
        }else m_uiCurseOfWeakness_Timer -= uiDiff;

        if (m_uiDemonArmor_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature,SPELL_DEMONARMOR);
            m_uiDemonArmor_Timer = 300000;
        }else m_uiDemonArmor_Timer -= uiDiff;

        if (m_uiEnvelopingWeb_Timer < uiDiff)
        {
            Unit* pTarget = NULL;
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
            if (pTarget) DoCastSpellIfCan(pTarget,SPELL_ENVELOPINGWEB);
            m_uiEnvelopingWeb_Timer = 12000;
        }else m_uiEnvelopingWeb_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_anubshiah(Creature* pCreature)
{
    return new boss_anubshiahAI(pCreature);
}

void AddSC_boss_anubshiah()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_anubshiah";
    pNewScript->GetAI = &GetAI_boss_anubshiah;
    pNewScript->RegisterSelf();
}
