/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 MangosR2_ScriptDev2
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
SDName: boss_muru
SD%Complete: 25
SDComment:
SDCategory: Sunwell Plateau
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

enum spells // Boss spells
{
    SPELL_OPEN_PORTAL_VISUAL    = 45977,
    SPELL_ENRAGE                = 26662,
    SPELL_NEGATIVE              = 46285, //negative energy -> deals damage
    SPELL_NEGATIVEENERGY        = 46008, //negative energy -> black beams
    SPELL_NEGATIVE_ENERGY       = 46009, //(this trigger 46008)
    SPELL_NEGATIVEENERGY_CHAIN  = 46289, //negative energy ->

    AURA_SINGULARITY            = 46228, //black hole passive  visual effect

    //DARKNESS                  = 45996, // darkness
    SPELL_DARKNESS              = 45999,
    SPELL_ENTROPIUS_SUMMON      = 46217,
    ENTROPIUS_EFFECT            = 46223, // entropius cosmetic spawn

    SUMMON_VOID_SENTINEL        = 45988, // visual effect & summon void sentinel
    SUMMON_VOID_SENTINEL_IMAGE  = 45989, // summon void sentine - summoning visual effect
    SUMMON_VOID_SENTINEL_SUMMON = 45978, //
    SUMMON_VOID_SENTINEL_PORTAL = 45977, // portal visual effect

    SPELL_SUMMON_BERSERKER      = 46037,
    SPELL_SUMMON_FURY_MAGE      = 46038,

// entropius spells
    SPELL_NEGATIVE_ENERGY_ENT   = 46284,
    SPELL_NEGATIVE_ENERGY_DMG   = 46285,
    SPELL_SINGULARITY           = 46282,
    //SPELL_BLACKHOLE           = 46282,
    SPELL_SUMMON_DARKNESS		= 46269,

//Portals
    SPELL_OPEN_ALL_PORTALS      = 46177,
    SPELL_OPEN_PORTAL           = 45977,
    SPELL_OPEN_PORTAL_2         = 45976,

// black hole
    SPELL_BLACK_HOLE_PASSIVE    = 46228,  //grow
    SPELL_BLACKHOLE_SPAWN       = 46242,
    SPELL_VOID_ZONE_PERIODIC    = 46262,
    SPELL_VOID_ZONE_PREEFFECT   = 46265,

//NPC list
    CREATURE_PORTAL_TARGET      = 25770,
    CREATURE_ENTROPIUS          = 25840,
    NPC_VOID_SENTINEL           = 25772,
    NPC_VOID_SPAWN              = 25824,
    NPC_DARK_FIEND              = 25744,
    NPC_SINGULARITY             = 25855,
    NPC_DARKNESS                = 25879,

//Dark Fiend
    DARK_FIEND_AURA             = 45934, // summon dark fiend
    SPELL_DARKFIEND_VISUAL      = 45936,
    DARK_FIEND_DEBUFF           = 45944, // dark fiend debuff AOE
    SPELL_DISPELL               = 32375, // mass dispell
    SPELL_PURGE                 = 8012,  // purge (reinigung)

    SPELL_ARCANEFORM            = 48019, // arcaneform   -- Chaotic Rift visual
// void sentinel
    SPELL_SHADOW_PULSE          = 46086,
    VOID_AURA                   = 46087, // shadow pulse
    VOID_BLAST                  = 46161, // void blast
// Shadowsword Berserker's spells
    SPELL_FLURRY                = 46160,
    SPELL_DUAL_WIELD            = 29651,
// Shadowsword Fury Mage's spells
    SPELL_FEL_FIREBALL          = 46101,
    SPELL_SPELL_FURY            = 46102,

};

enum summons
{
    ID_SWFuryMage	            = 25799, // shadowsword fury mage
    ID_SWBerserker              = 25798, // shadowsword berserker
};

//Boss sounds
#define SOUND_CHANGE_PHASE 12560

// Sumoned trash coordinates
float Trash[6][2] =
{
        {1853.300f,588.653f},
        {1781.502f,659.254f},
        {1853.300f,588.653f},
        {1853.300f,588.653f},
        {1781.502f,659.254f},
        {1781.502f,659.254f},
};

// Dark Fiend spawn coordinates
float DarkFiendSpawn[8][2] =
{
	{1825.39f,620.36f},
	{1827.11f,628.24f},
	{1821.82f,636.50f},
	{1812.42f,637.12f},
	{1805.03f,632.02f},
	{1804.04f,623.09f},
	{1809.85f,615.46f},
	{1818.69f,614.17f},
};
float DarkFiendSpawnZ = 69.7f;

/*######
## Mu'ru
######*/

struct MANGOS_DLL_DECL boss_muruAI : public ScriptedAI
{
    boss_muruAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;

// Timers/\Bools/\ Ect \\

    uint32 m_uiNegativeEnergyTimer;
    uint32 m_uiSummonTrashTimer;
    uint32 m_uiSummonVoidTimer;
    ObjectGuid m_uiPortalGUID;
    uint32 m_uiPortalDelayTimer;
    uint32 m_uiDarknessTimer;
    uint32 m_uiDarkFiendTimer;

    void Reset()
    {
        m_uiNegativeEnergyTimer  = 2000;
        m_uiSummonTrashTimer     = 10000;
        m_uiDarknessTimer        = 45000;
        m_uiDarkFiendTimer		 = 50000;
        m_uiSummonVoidTimer      = 30000;
        m_uiPortalGUID.Clear();
        m_uiPortalDelayTimer     = 60000;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_MURU,NOT_STARTED);

        if (!m_creature->HasAura(SPELL_SUNWELL_RADIANCE_AURA))
            DoCast(m_creature, SPELL_SUNWELL_RADIANCE_AURA);
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MURU,IN_PROGRESS);
    }

    void OpenAllPortals()
    {
        std::list<Creature*> lPortals;
        GetCreatureListWithEntryInGrid(lPortals, m_creature, NPC_PORTAL_TARGET, 40.0f);
        if (!lPortals.empty())
        {
            for(std::list<Creature*>::iterator iter = lPortals.begin(); iter != lPortals.end(); ++iter)
            {
                if ((*iter) && (*iter)->isAlive())
                    (*iter)->CastSpell((*iter), SPELL_OPEN_PORTAL_VISUAL, false);
            }
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoCast(m_creature, SPELL_OPEN_ALL_PORTALS);
        OpenAllPortals();
        DoCast(m_creature, ENTROPIUS_EFFECT);
        m_creature->CastSpell(m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),SPELL_ENTROPIUS_SUMMON, true);
        DoPlaySoundToSet(m_creature, SOUND_CHANGE_PHASE); // only temp til i feel like writing  down what he says 8)
    }

    Creature* SelectRandomPortal()
    {
        std::list<Creature* > lPortalList;
        GetCreatureListWithEntryInGrid(lPortalList, m_creature, NPC_PORTAL_TARGET, 40.0f);

        if (lPortalList.empty()){
            m_uiSummonVoidTimer = 30000;
            return NULL;
        }

        std::list<Creature* >::iterator iter = lPortalList.begin();
        advance(iter, urand(0, lPortalList.size()-1));

        return *iter;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiDarknessTimer < uiDiff)
        {
            DoCast(m_creature, SPELL_DARKNESS);
            m_uiDarkFiendTimer = 5000;
            m_uiDarknessTimer = 45000;
        }
        else m_uiDarknessTimer -= uiDiff;

        if (m_uiDarkFiendTimer < uiDiff)
        {
            for (int i = 0; i < 8; i++)
            {
                 float angle = (float) rand()*360/RAND_MAX + 1;
                 float homeX = m_creature->GetPositionX() + 10*cos(angle*(M_PI/180));
                 float homeY = m_creature->GetPositionY() + 10*sin(angle*(M_PI/180));
                 if (Creature* pTemp = m_creature->SummonCreature(NPC_DARK_FIEND, homeX, homeY, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 11000))
                     pTemp->SetGuidValue(UNIT_FIELD_TARGET, m_creature->GetObjectGuid());
             }
             m_uiDarkFiendTimer = 60000;
        }
        else m_uiDarkFiendTimer -= uiDiff;

        if (m_uiSummonVoidTimer < uiDiff)
        {
            if (Creature* pPortal = SelectRandomPortal())
            {
                 m_uiPortalGUID = pPortal->GetObjectGuid();
                 pPortal->CastSpell(pPortal, SPELL_OPEN_PORTAL_VISUAL, false);
             }
             m_uiPortalDelayTimer = 5000;
             m_uiSummonVoidTimer = 30000;
        }
        else m_uiSummonVoidTimer -= uiDiff;

        if (m_uiPortalDelayTimer < uiDiff)
        {
            if (Creature* pPortal = m_creature->GetMap()->GetCreature(m_uiPortalGUID))
                m_creature->SummonCreature(NPC_VOID_SENTINEL, pPortal->GetPositionX(), pPortal->GetPositionY(), m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);
                m_uiPortalDelayTimer = 60000;
        }
        else m_uiPortalDelayTimer -= uiDiff;

        //Summon 6 humanoids every 1min (1 mage & 2 berserkers)
        if (m_uiSummonTrashTimer < uiDiff)
        {
            for (uint8 i = 0; i < 6; i++)
            {
                 uint32 ID;

                 if ((i == 1) | (i == 2))
                     ID = ID_SWFuryMage;
                 else
                     ID = ID_SWBerserker;

                 Creature* sTrash = m_creature->SummonCreature(ID, Trash[i][0], Trash[i][1], m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 15000);

                 if (Unit* sTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                     if (sTrash)
                         sTrash->AI()->AttackStart(sTarget);
            }
            m_uiSummonTrashTimer = 60000;
        }else m_uiSummonTrashTimer -= uiDiff;

        //negative energy on 4-5 targets
        if (m_uiNegativeEnergyTimer < uiDiff)
        {   //choose 4-5 targets
            for(uint8 i=rand()%2; i<5; ++i)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    m_creature->CastSpell(pTarget, SPELL_NEGATIVE, false);
            }
            m_uiNegativeEnergyTimer = 2000;
        }else m_uiNegativeEnergyTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_muru(Creature *_Creature)
{
    return new boss_muruAI(_Creature);
}

/*######
## Entropius
######*/

struct MANGOS_DLL_DECL boss_entropiusAI : public ScriptedAI
{
    boss_entropiusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiTargetsCount;
    uint32 m_uiTargetsCountTimer;
    uint32 m_uiNegativeEnergyTimer;
    uint32 m_uiBerserkTimer;

    void Reset()
    {
        m_uiNegativeEnergyTimer = 1000;
        m_uiBerserkTimer        = 300000;
        m_uiTargetsCount        = 0;
        m_uiTargetsCountTimer   = 1500;

        if (!m_creature->HasAura(SPELL_SUNWELL_RADIANCE_AURA, EFFECT_INDEX_0))
            m_creature->CastSpell(m_creature, SPELL_SUNWELL_RADIANCE_AURA, true);
	}

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MURU, NOT_STARTED);

        if (Creature* pMuru = m_pInstance->GetSingleCreatureFromStorage(NPC_MURU))
            pMuru->Respawn();

        m_creature->ForcedDespawn();
    }

    void JustDied(Unit* pKiller)
    {
         if (m_pInstance)
             m_pInstance->SetData(TYPE_MURU, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
         if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

         if (m_uiBerserkTimer < uiDiff)
         {
             DoCast(m_creature, SPELL_ENRAGE);
             m_uiBerserkTimer = 60000;
         }
         else m_uiBerserkTimer -= uiDiff;

         // add a target every other cast
         if (m_uiTargetsCountTimer < uiDiff)
         {
             ++m_uiTargetsCount;
             m_uiTargetsCountTimer = 1500;  //  1 sec cast  1.5 secs means would have added a second target by second cast
         }else m_uiTargetsCountTimer -= uiDiff;

         if (m_uiNegativeEnergyTimer < uiDiff)
         {
             for(uint8 i=0; i<m_uiTargetsCount; ++i)
             {
                 if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                     m_creature->CastSpell(pTarget, SPELL_NEGATIVE, false);
             }

             m_uiNegativeEnergyTimer = 1000;
         }else m_uiNegativeEnergyTimer -= uiDiff;

         DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_boss_entropius(Creature *pCreature)
{
    return new boss_entropiusAI(pCreature);
}

void AddSC_boss_muru()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name="boss_muru";
    pNewScript->GetAI = &GetAI_boss_muru;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="boss_entropius";
    pNewScript->GetAI = &GetAI_boss_entropius;
    pNewScript->RegisterSelf();
}
