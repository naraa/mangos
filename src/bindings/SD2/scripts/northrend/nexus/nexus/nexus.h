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

#ifndef DEF_NEXUS_H
#define DEF_NEXUS_H

enum
{
    MAX_ENCOUNTER                  = 4,
    MAX_SPECIAL_ACHIEV_CRITS       = 3,

    TYPE_TELESTRA                  = 0,
    TYPE_ANOMALUS                  = 1,
    TYPE_ORMOROK                   = 2,
    TYPE_KERISTRASZA               = 3,

    TYPE_CHAOS_THEORY              = 0,
    TYPE_DOUBLE_PERSONALITY        = 1,
    TYPE_INTENSE_COLD              = 2,

    NPC_TELESTRA                   = 26731,
    NPC_FIRE_MAGUS                 = 26928,
    NPC_FROST_MAGUS                = 26930,
    NPC_ARCANE_MAGUS               = 26929,

    NPC_ANOMALUS                   = 26763,
    NPC_CRAZED_MANA_WRAITH         = 26746,
    NPC_CHAOTIC_RIFT               = 26918,

    NPC_ORMOROK                    = 26794,
    NPC_CRYSTAL_SPIKE              = 27099,
    NPC_CRYSTALLINE_TANGLER        = 32665,

    NPC_KERISTRASZA                = 26723,
    NPC_BREATH_CASTER              = 27048,

///-> NEED RESPAWN IN BETTER FORMATION ON NPC IN GAME ( COME ONE ALL HEALERS AT ONE END OF TUNNEL )
///->ALIANCE COMMANDER STUFF
    NPC_COMM_STOUTBEARD            = 26796,
    NPC_ALLIANCE_COMMANDER         = 27949,
    NPC_ALLIANCE_BERSERKER         = 26800,
    NPC_ALLIANCE_BERSERKER_H       = 30496,
    NPC_ALLIANCE_CLERIC            = 26805,
    NPC_ALLIANCE_CLERIC_H          = 30498, 
    NPC_ALLIANCE_RANGER            = 26802,
    NPC_ALLIANCE_RANGER_H          = 30509,
///-> HORDE COMMANDER STUFF
    NPC_COMM_KOLURG                = 26798,
    NPC_HORDE_COMMANDER            = 27947,
    NPC_HORDE_RANGER               = 26801,
    NPC_HORDE_RANGER_H             = 30508,
    NPC_HORDE_CLERIC               = 26803,
    NPC_HORDE_CLERIC_H             = 30497,
    NPC_HORDE_BERSERKER            = 26799,
    NPC_HORDE_BERSERKER_H          = 30495,

    GO_CONTAINMENT_SPHERE_TELESTRA = 188526,
    GO_CONTAINMENT_SPHERE_ANOMALUS = 188527,
    GO_CONTAINMENT_SPHERE_ORMOROK  = 188528,

    SPELL_FROZEN_PRISON             = 47854,

    // Achievements
    ACHIEV_CHAOS_THEORY            = 7316,
    ACHIEV_DOUBLE_PERSONALITY      = 7577,
    ACHIEV_INTENSE_COLD            = 7315,
};

class MANGOS_DLL_DECL instance_nexus : public ScriptedInstance
{
    public:
        instance_nexus(Map* pMap);

        void Initialize();

        void OnPlayerEnter(Player* pPlayer);
        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);
        void OnCreatureDeath(Creature* pCreature);

        uint32 GetData(uint32 uiType);
        void SetData(uint32 uiType, uint32 uiData);

        bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/);
        void SetSpecialAchievementCriteria(uint32 uiType, bool bIsMet);

        const char* Save() { return m_strInstData.c_str(); }

        void Load(const char* chrIn);

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        bool m_abAchievCriteria[MAX_SPECIAL_ACHIEV_CRITS];
};

#endif
