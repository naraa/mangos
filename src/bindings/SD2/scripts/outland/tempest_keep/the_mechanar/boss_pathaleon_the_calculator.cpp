/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 - 2012 Infinity_scriptdev2
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
SDName: Boss Pathaleon the Calculator
SD%Complete: 50
SDComment: Event missing. Script for himself 99% blizzlike.
SDCategory: Tempest Keep, The Mechanar
EndScriptData */

#include "precompiled.h"
#include "mechanar.h"

enum
{
    SAY_AGGRO                      = -1554020,
    SAY_DOMINATION_1               = -1554021,
    SAY_DOMINATION_2               = -1554022,
    SAY_SUMMON                     = -1554023,
    SAY_ENRAGE                     = -1554024,
    SAY_SLAY_1                     = -1554025,
    SAY_SLAY_2                     = -1554026,
    SAY_DEATH                      = -1554027,

// Spells to be casted
    SPELL_MANA_TAP                 = 36021,
    SPELL_ARCANE_TORRENT           = 36022,
    SPELL_DOMINATION               = 35280,
    SPELL_ARCANE_EXPLOSION_H       = 15453,
    SPELL_FRENZY                   = 36992,

    SPELL_SUMMON_NETHER_WRAITH_1   = 35285,              //Spells work, but not implemented
    SPELL_SUMMON_NETHER_WRAITH_2   = 35286,
    SPELL_SUMMON_NETHER_WRAITH_3   = 35287,
    SPELL_SUMMON_NETHER_WRAITH_4   = 35288,

// Add Spells
    SPELL_DETONATION               = 35058,
    SPELL_ARCANE_MISSILES          = 35034,
};

/****
* boss_pathaleon_the_calculator
****/

struct MANGOS_DLL_DECL boss_pathaleon_the_calculatorAI : public ScriptedAI
{
    boss_pathaleon_the_calculatorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    bool m_bIsRegularMode;

    uint32 m_uiSummon_Timer;
    uint32 m_uiManaTap_Timer;
    uint32 m_uiArcaneTorrent_Timer;
    uint32 m_uiDomination_Timer;
    uint32 m_uiArcaneExplosion_Timer;
    bool m_bEnraged;

    void Reset()
    {
        m_uiSummon_Timer = 30000;
        m_uiManaTap_Timer = urand(12000, 20000);
        m_uiArcaneTorrent_Timer = urand(16000, 25000);
        m_uiDomination_Timer = urand(25000, 40000);
        m_uiArcaneExplosion_Timer = urand(8000, 13000);

        m_bEnraged = false;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiSummon_Timer < uiDiff)
        {
            for(int i = 0; i < 3; ++i)
            {
                Unit* pTarget = NULL;
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
                Creature* pWraith = m_creature->SummonCreature(21062,m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(),0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                if (pTarget && pWraith)
                    pWraith->AI()->AttackStart(pTarget);
            }

            DoScriptText(SAY_SUMMON, m_creature);

            m_uiSummon_Timer = urand(30000, 45000);
        }else m_uiSummon_Timer -= uiDiff;

        if (m_uiManaTap_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_MANA_TAP);
            m_uiManaTap_Timer = urand(14000, 22000);
        }else m_uiManaTap_Timer -= uiDiff;

        if (m_uiArcaneTorrent_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_ARCANE_TORRENT);
            m_uiArcaneTorrent_Timer = urand(12000, 18000);
        }else m_uiArcaneTorrent_Timer -= uiDiff;

        if (m_uiDomination_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
            {
                DoScriptText(urand(0, 1) ? SAY_DOMINATION_1 : SAY_DOMINATION_2, m_creature);
                DoCastSpellIfCan(pTarget,SPELL_DOMINATION);
            }

            m_uiDomination_Timer = urand(25000, 30000);
        }else m_uiDomination_Timer -= uiDiff;

        //Only casting if Heroic Mode is used
        if (!m_bIsRegularMode)
        {
            if (m_uiArcaneExplosion_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_ARCANE_EXPLOSION_H);
                m_uiArcaneExplosion_Timer = urand(10000, 14000);
            }else m_uiArcaneExplosion_Timer -= uiDiff;
        }

        if (!m_bEnraged && m_creature->GetHealthPercent() < 21.0f)
        {
            DoCastSpellIfCan(m_creature, SPELL_FRENZY);
            DoScriptText(SAY_ENRAGE, m_creature);
            m_bEnraged = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_pathaleon_the_calculator(Creature* pCreature)
{
    return new boss_pathaleon_the_calculatorAI(pCreature);
}

/****
* mob_nether_wraith
****/

struct MANGOS_DLL_DECL mob_nether_wraithAI : public ScriptedAI
{
    mob_nether_wraithAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    ScriptedInstance* m_pInstance;

    uint32 m_uiArcaneMissiles_Timer;
    uint32 m_uiDetonation_Timer;
    uint32 m_uiDie_Timer;
    bool m_bDetonation;

    void Reset()
    {
        m_uiArcaneMissiles_Timer = urand(1000, 4000);
        m_uiDetonation_Timer = 20000;
        m_uiDie_Timer = 2200;
        m_bDetonation = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiArcaneMissiles_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
                DoCastSpellIfCan(pTarget,SPELL_ARCANE_MISSILES);
            else
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_ARCANE_MISSILES);

            m_uiArcaneMissiles_Timer = urand(5000, 10000);
        }else m_uiArcaneMissiles_Timer -=uiDiff;

        if (!m_bDetonation)
        {
            if (m_uiDetonation_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature,SPELL_DETONATION);
                m_bDetonation = true;
            }else m_uiDetonation_Timer -= uiDiff;
        }

        if (m_bDetonation)
        {
            if (m_uiDie_Timer < uiDiff)
            {
                m_creature->SetDeathState(JUST_DIED);
                m_creature->RemoveCorpse();
            }else m_uiDie_Timer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_mob_nether_wraith(Creature* pCreature)
{
    return new mob_nether_wraithAI(pCreature);
}

void AddSC_boss_pathaleon_the_calculator()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_pathaleon_the_calculator";
    pNewScript->GetAI = &GetAI_boss_pathaleon_the_calculator;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_nether_wraith";
    pNewScript->GetAI = &GetAI_mob_nether_wraith;
    pNewScript->RegisterSelf();
}
