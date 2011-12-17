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
SD%Complete: ?%
SDComment: by /dev/rsa && FallenangelX
SDCategory: Oculus - Dragons_Vehicles
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

enum Spells
{
    SPELL_GREEN_SEAT                        = 49346,
    SPELL_YELLOW_SEAT                       = 49460,
    SPELL_RED_SEAT                          = 49464,
    SPELL_DRAKE_FLAG_VISUAL                 = 53797,
};

enum NPC
{
    NPC_GREEN_DRAGON                        = 27692,
    NPC_YELLOW_DRAGON                       = 27755,
    NPC_RED_DRAGON                          = 27756,
};

struct MANGOS_DLL_DECL mob_oculus_dragonAI : public ScriptedAI
{
    mob_oculus_dragonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool m_bActive;
    ObjectGuid ownerGUID;
    uint32 m_uiSeatSpell;
    uint32 m_uiStartTimer;

    void Reset()
    {
        m_bActive = false;
        ownerGUID = ObjectGuid();
        m_uiStartTimer = 2000;
        switch (m_creature->GetEntry())
        {
            case NPC_GREEN_DRAGON:
                m_uiSeatSpell = SPELL_GREEN_SEAT;
                break;
            case NPC_RED_DRAGON:
                m_uiSeatSpell = SPELL_RED_SEAT;
                break;
            case NPC_YELLOW_DRAGON:
                m_uiSeatSpell = SPELL_YELLOW_SEAT;
                break;
            default:
                m_uiSeatSpell = 0;
                break;
        }
        ownerGUID = m_creature->GetCreatorGuid();

        if (Unit* owner = m_creature->GetMap()->GetUnit(ownerGUID))
            owner->RemoveAurasDueToSpell(SPELL_DRAKE_FLAG_VISUAL);
    }

    void AttackStart(Unit *) {}
    void MoveInLineOfSight(Unit*) {}

    void JustSummoned(){}

    void JustDied(Unit* killer)
    {
        if (!m_creature || m_creature->GetTypeId() != TYPEID_UNIT)
            return;

        if (ownerGUID.IsEmpty())
            ownerGUID = m_creature->GetCreatorGuid();

        Unit* owner = m_creature->GetMap()->GetUnit(ownerGUID);

        if (!owner || owner->GetTypeId() != TYPEID_PLAYER)
            return;

        owner->RemoveAurasDueToSpell(m_uiSeatSpell);
        owner->RemoveAurasDueToSpell(SPELL_DRAKE_FLAG_VISUAL);
        m_creature->SetCreatorGuid(ObjectGuid());
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE && uiPointId == 0)
            return;

        if (Unit* owner = m_creature->GetMap()->GetUnit(ownerGUID))
        {
             m_creature->setFaction(owner->getFaction());
             owner->CastSpell(m_creature, m_uiSeatSpell, true);
             owner->CastSpell(owner, SPELL_DRAKE_FLAG_VISUAL, true);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {

        if (ownerGUID.IsEmpty())
            ownerGUID = m_creature->GetCreatorGuid();

        if (!ownerGUID.IsEmpty())
        {
            if (m_uiStartTimer < uiDiff && !m_bActive)
            {
               if (Unit* owner = m_creature->GetMap()->GetUnit(ownerGUID))
               {
                   float x, y, z;
                   owner->GetClosePoint(x, y, z, owner->GetObjectBoundingRadius(), 1.0f, owner->GetAngle(m_creature));
                   m_creature->GetMotionMaster()->MovePoint(0, x, y, z);
                   m_bActive = true;
               }
            }
            else
                m_uiStartTimer -= uiDiff;
        }
        else
            if (m_uiStartTimer < uiDiff)
                m_creature->ForcedDespawn();
    }
};

CreatureAI* GetAI_mob_oculus_dragon(Creature* pCreature)
{
    return new mob_oculus_dragonAI(pCreature);
}

void AddSC_oculus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "mob_oculus_dragon";
    pNewScript->GetAI = &GetAI_mob_oculus_dragon;
    pNewScript->RegisterSelf();
}