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
SDName: Boss_Grandmaster_Vorpil
SD%Complete: 75
SDComment: Despawn all summoned on death not implemented. Void Traveler effects not implemented.
SDCategory: Auchindoun, Shadow Labyrinth
EndScriptData */

#include "precompiled.h"
#include "shadow_labyrinth.h"

enum
{
    SAY_INTRO                      = -1555028,
    SAY_AGGRO1                     = -1555029,
    SAY_AGGRO2                     = -1555030,
    SAY_AGGRO3                     = -1555031,
    SAY_HELP                       = -1555032,
    SAY_SLAY1                      = -1555033,
    SAY_SLAY2                      = -1555034,
    SAY_DEATH                      = -1555035,

    SPELL_DRAW_SHADOWS             = 33563,
    SPELL_VOID_PORTAL_A            = 33566,              //spell only summon one unit, but we use it for the visual effect and summon the 4 other portals manual way(only one spell exist)
    SPELL_VOID_PORTAL_VISUAL       = 33569,
    SPELL_SHADOW_BOLT_VOLLEY       = 32963,
    SPELL_SUMMON_VOIDWALKER_A      = 33582,
    SPELL_SUMMON_VOIDWALKER_B      = 33583,
    SPELL_SUMMON_VOIDWALKER_C      = 33584,
    SPELL_SUMMON_VOIDWALKER_D      = 33585,
    SPELL_SUMMON_VOIDWALKER_E      = 33586,
    SPELL_RAIN_OF_FIRE             = 33617,
    SPELL_RAIN_OF_FIRE_H           = 39363,
    SPELL_BANISH_H                 = 38791,

    ENTRY_VOID_PORTAL              = 19224,
    ENTRY_VOID_TRAVELER            = 19226,
};

#define LOCX                            -253.06f
#define LOCY                            -264.02f
#define LOCZ                            17.08f

struct MANGOS_DLL_DECL boss_grandmaster_vorpilAI : public ScriptedAI
{
    boss_grandmaster_vorpilAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_bIntro = false;
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiShadowBoltVolley_Timer;
    uint32 m_uiDrawShadows_Timer;
    uint32 m_uiTeleport_Timer;
    uint32 m_uiVoidTraveler_Timer;
    uint32 m_uiBanish_Timer;
    bool m_bIntro;
    bool m_bTeleport;

    void Reset()
    {
        m_uiShadowBoltVolley_Timer = urand(7000, 14000);
        m_uiDrawShadows_Timer = 40000;
        m_uiTeleport_Timer = 1000;
        m_uiVoidTraveler_Timer = 20000;
        m_uiBanish_Timer = 25000;
        m_bTeleport = false;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VORPIL, NOT_STARTED);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        //not sure about right radius
        if (!m_bIntro && m_creature->IsWithinDistInMap(pWho, 50))
        {
            DoScriptText(SAY_INTRO, m_creature);
            m_bIntro = true;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void Aggro(Unit* pWho)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
            case 2: DoScriptText(SAY_AGGRO3, m_creature); break;
        }

        DoCastSpellIfCan(m_creature, SPELL_VOID_PORTAL_A,true);
        m_creature->SummonCreature(ENTRY_VOID_PORTAL, -262.40f, -229.57f, 17.08f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN,0);
        m_creature->SummonCreature(ENTRY_VOID_PORTAL, -260.35f, -297.56f, 17.08f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN,0);
        m_creature->SummonCreature(ENTRY_VOID_PORTAL, -292.05f, -270.37f, 12.68f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN,0);
        m_creature->SummonCreature(ENTRY_VOID_PORTAL, -301.64f, -255.97f, 12.68f, 0.0f, TEMPSUMMON_CORPSE_DESPAWN,0);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VORPIL, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == ENTRY_VOID_TRAVELER)
            pSummoned->GetMotionMaster()->MoveFollow(m_creature, 1.0f, 0.0f);

        if (pSummoned->GetEntry() == ENTRY_VOID_PORTAL)
            pSummoned->CastSpell(pSummoned,SPELL_VOID_PORTAL_VISUAL,true);
    }

    void JustDied(Unit* pVictim)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VORPIL, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bTeleport)
        {
            if (m_uiTeleport_Timer <= uiDiff)
            {
                m_creature->NearTeleportTo(LOCX, LOCY, LOCZ, 0.0f);

                float ranX = LOCX;
                float ranY = LOCY;
                float ranZ = LOCZ;

                std::vector<ObjectGuid> vGuids;
                m_creature->FillGuidsListFromThreatList(vGuids);
                for (std::vector<ObjectGuid>::const_iterator itr = vGuids.begin();itr != vGuids.end(); ++itr)
                {
                    Unit* pTarget = m_creature->GetMap()->GetUnit(*itr);

                    if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        pTarget->GetRandomPoint(LOCX,LOCY,LOCZ,3.0f,ranX,ranY,ranZ);
                        DoTeleportPlayer(pTarget,ranX,ranY,ranZ,m_creature->GetAngle(m_creature->GetPositionX(),m_creature->GetPositionY()));
                    }
                }
                m_bTeleport = false;

                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_RAIN_OF_FIRE : SPELL_RAIN_OF_FIRE_H);

                m_uiTeleport_Timer = 1000;
            }else m_uiTeleport_Timer -= uiDiff;
        }

        if (m_uiShadowBoltVolley_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOW_BOLT_VOLLEY);
            m_uiShadowBoltVolley_Timer = urand(15000, 30000);
        }else m_uiShadowBoltVolley_Timer -= uiDiff;

        if (m_uiDrawShadows_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature,SPELL_DRAW_SHADOWS);
            m_uiDrawShadows_Timer = 30000;
            m_bTeleport = true;
        }else m_uiDrawShadows_Timer -= uiDiff;

        if (m_uiVoidTraveler_Timer < uiDiff)
        {
            DoScriptText(SAY_HELP, m_creature);

            switch(urand(0, 4))
            {
                case 0: DoCastSpellIfCan(m_creature, SPELL_SUMMON_VOIDWALKER_A, CAST_TRIGGERED); break;
                case 1: DoCastSpellIfCan(m_creature, SPELL_SUMMON_VOIDWALKER_B, CAST_TRIGGERED); break;
                case 2: DoCastSpellIfCan(m_creature, SPELL_SUMMON_VOIDWALKER_C, CAST_TRIGGERED); break;
                case 3: DoCastSpellIfCan(m_creature, SPELL_SUMMON_VOIDWALKER_D, CAST_TRIGGERED); break;
                case 4: DoCastSpellIfCan(m_creature, SPELL_SUMMON_VOIDWALKER_E, CAST_TRIGGERED); break;
            }
            //faster rate when below (X) health?
            m_uiVoidTraveler_Timer = 35000;
        }else m_uiVoidTraveler_Timer -= uiDiff;

        if (!m_bIsRegularMode)
        {
            if (m_uiBanish_Timer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                    DoCastSpellIfCan(pTarget,SPELL_BANISH_H);
                m_uiBanish_Timer = 35000;
            }else m_uiBanish_Timer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_grandmaster_vorpil(Creature* pCreature)
{
    return new boss_grandmaster_vorpilAI(pCreature);
}

void AddSC_boss_grandmaster_vorpil()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_grandmaster_vorpil";
    pNewScript->GetAI = &GetAI_boss_grandmaster_vorpil;
    pNewScript->RegisterSelf();
}
