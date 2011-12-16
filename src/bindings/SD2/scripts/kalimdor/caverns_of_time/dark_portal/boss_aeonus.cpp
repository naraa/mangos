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
SDName: Boss_Aeonus
SD%Complete: 80
SDComment: Some spells not implemented
SDCategory: Caverns of Time, The Dark Portal
EndScriptData */

#include "precompiled.h"
#include "dark_portal.h"

enum
{
    SAY_ENTER               = -1269012,
    SAY_AGGRO               = -1269013,
    SAY_BANISH              = -1269014,
    SAY_SLAY1               = -1269015,
    SAY_SLAY2               = -1269016,
    SAY_DEATH               = -1269017,
    EMOTE_GENERIC_FRENZY    = -1000002,

    SPELL_CLEAVE            = 40504,
    SPELL_TIME_STOP         = 31422,
    SPELL_ENRAGE            = 37605,
    SPELL_SAND_BREATH       = 31473,
    SPELL_SAND_BREATH_H     = 39049,
};

struct MANGOS_DLL_DECL boss_aeonusAI : public ScriptedAI
{
    boss_aeonusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiSandBreath_Timer;
    uint32 m_uiTimeStop_Timer;
    uint32 m_uiFrenzy_Timer;

    void Reset()
    {
        m_uiSandBreath_Timer = urand(15000, 30000);
        m_uiTimeStop_Timer = urand(10000, 15000);
        m_uiFrenzy_Timer = urand(30000, 45000);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        //Despawn Time Keeper
        if (who->GetTypeId() == TYPEID_UNIT && pWho->GetEntry() == NPC_TIME_KEEPER)
        {
            if (m_creature->IsWithinDistInMap(pWho,20.0f))
            {
                DoScriptText(SAY_BANISH, m_creature);
                m_creature->DealDamage(pWho, pWho->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
        }

        ScriptedAI::MoveInLineOfSight(who);
    }

    void JustDied(Unit* pVictim)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_RIFT,DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Sand Breath
        if (m_uiSandBreath_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_SAND_BREATH : SPELL_SAND_BREATH_H);
            m_uiSandBreath_Timer = urand(15000, 25000);
        }else m_uiSandBreath_Timer -= uiDiff;

        //Time Stop
        if (m_uiTimeStop_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_TIME_STOP);
            m_uiTimeStop_Timer = urand(20000, 35000);
        }else m_uiTimeStop_Timer -= uiDiff;

        //Frenzy
        if (m_uiFrenzy_Timer < uiDiff)
        {
            DoScriptText(EMOTE_GENERIC_FRENZY, m_creature);
            DoCastSpellIfCan(m_creature, SPELL_ENRAGE);
            m_uiFrenzy_Timer = urand(20000, 35000);
        }else m_uiFrenzy_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_aeonus(Creature* pCreature)
{
    return new boss_aeonusAI(pCreature);
}

void AddSC_boss_aeonus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_aeonus";
    pNewScript->GetAI = &GetAI_boss_aeonus;
    pNewScript->RegisterSelf();
}
