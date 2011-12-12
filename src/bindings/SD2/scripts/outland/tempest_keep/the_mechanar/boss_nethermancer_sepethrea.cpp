/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 - 2012 Infinity_Scriptdev2
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
SDName: Boss_Nethermancer_Sepethrea
SD%Complete: 90
SDComment: Need adjustments to initial summons
SDCategory: Tempest Keep, The Mechanar
EndScriptData */

#include "precompiled.h"
#include "mechanar.h"

enum
{
    SAY_AGGRO                      = -1554013,
    SAY_SUMMON                     = -1554014,
    SAY_DRAGONS_BREATH_1           = -1554015,
    SAY_DRAGONS_BREATH_2           = -1554016,
    SAY_SLAY1                      = -1554017,
    SAY_SLAY2                      = -1554018,
    SAY_DEATH                      = -1554019,

    SPELL_SUMMON_RAGIN_FLAMES      = 35275,
    SPELL_FROST_ATTACK             = 35263,
    SPELL_ARCANE_BLAST             = 35314,
    SPELL_DRAGONS_BREATH           = 35250,
    SPELL_KNOCKBACK                = 37317,
    SPELL_SOLARBURN                = 35267,
};

/****
* boss_nethermancer_sepethrea
****/

struct MANGOS_DLL_DECL boss_nethermancer_sepethreaAI : public ScriptedAI
{
    boss_nethermancer_sepethreaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularuiDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiFrost_attack_Timer;
    uint32 m_uiArcane_blast_Timer;
    uint32 m_uiDragons_breath_Timer;
    uint32 m_uiKnockback_Timer;
    uint32 m_uiSolarburn_Timer;

    void Reset()
    {
        m_uiFrost_attack_Timer = urand(7000, 10000);
        m_uiArcane_blast_Timer = urand(12000, 18000);
        m_uiDragons_breath_Timer = urand(18000, 22000);
        m_uiKnockback_Timer = urand(22000, 28000);
        m_uiSolarburn_Timer = 30000;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        //Summon two guards, three in heroic
        uint8 am = (m_bIsRegularMode ? 2 : 1);
        for (int i = 0; i < am; ++i)
        {
            DoCastSpellIfCan(who,SPELL_SUMMON_RAGIN_FLAMES);
        }

        DoScriptText(SAY_SUMMON, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_SEPETHREA, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Frost Attack
        if (m_uiFrost_attack_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_FROST_ATTACK);
            m_uiFrost_attack_Timer = urand(7000, 10000);
        }else m_uiFrost_attack_Timer -= uiDiff;

        //Arcane Blast
        if (m_uiArcane_blast_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_ARCANE_BLAST);
            m_uiArcane_blast_Timer = 15000;
        }else m_uiArcane_blast_Timer -= uiDiff;

        //Dragons Breath
        if (m_uiDragons_breath_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_DRAGONS_BREATH);

            if (urand(0, 1))
                DoScriptText(urand(0, 1) ? SAY_DRAGONS_BREATH_1 : SAY_DRAGONS_BREATH_2, m_creature);

            m_uiDragons_breath_Timer = urand(12000, 22000);
        }else m_uiDragons_breath_Timer -= uiDiff;

        //Check for Knockback
        if (m_uiKnockback_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_KNOCKBACK);
            m_uiKnockback_Timer = urand(15000, 25000);
        }else m_uiKnockback_Timer -= uiDiff;

        //Check for Solarburn
        if (m_uiSolarburn_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_SOLARBURN);
            m_uiSolarburn_Timer = 30000;
        }else m_uiSolarburn_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_nethermancer_sepethrea(Creature* pCreature)
{
    return new boss_nethermancer_sepethreaAI(pCreature);
}

/****
* mob_ragin_flames
****/

enum
{
    SPELL_INFERNO                  = 35268,
    SPELL_INFERNO_H                = 39346,
    SPELL_FIRE_TAIL                = 35278,
};

struct MANGOS_DLL_DECL mob_ragin_flamesAI : public ScriptedAI
{
    mob_ragin_flamesAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularuiDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiInferno_Timer;
    uint32 m_uiFlame_Timer;
    uint32 m_uiCheck_Timer;

    bool onlyonce;

    void Reset()
    {
        m_uiInferno_Timer = 10000;
        m_uiFlame_Timer = 500;
        m_uiCheck_Timer = 2000;
        onlyonce = false;
        m_creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
        m_creature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, true);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!onlyonce)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
                m_creature->GetMotionMaster()->MoveChase(pTarget);
            onlyonce = true;
        }

        if (m_uiInferno_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_INFERNO : SPELL_INFERNO_H);

            m_creature->TauntApply(m_creature->getVictim());

            m_uiInferno_Timer = 10000;
        }else m_uiInferno_Timer -= uiDiff;

        if (m_uiFlame_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature,SPELL_FIRE_TAIL);
            m_uiFlame_Timer = 500;
        }else m_uiFlame_Timer -=uiDiff;

        //m_uiCheck_Timer
        if (m_uiCheck_Timer < uiDiff)
        {
            if (m_pInstance)
            {
                if (m_pInstance->GetData(TYPE_SEPETHREA) == DONE)
                {
                    //remove
                    m_creature->SetDeathState(JUST_DIED);
                    m_creature->RemoveCorpse();
                    return;
                }
            }

            m_uiCheck_Timer = 1000;
        }else m_uiCheck_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};
CreatureAI* GetAI_mob_ragin_flames(Creature* pCreature)
{
    return new mob_ragin_flamesAI(pCreature);
}
void AddSC_boss_nethermancer_sepethrea()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_nethermancer_sepethrea";
    pNewScript->GetAI = &GetAI_boss_nethermancer_sepethrea;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_ragin_flames";
    pNewScript->GetAI = &GetAI_mob_ragin_flames;
    pNewScript->RegisterSelf();
}
