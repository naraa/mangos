/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: instance_halls_of_reflection
SD%Complete: 70%
SDComment:
SDErrors:
SDCategory: instance script
SDAuthor: /dev/rsa, modified by MaxXx2021 aka Mioka
EndScriptData */

#include "precompiled.h"
#include "halls_of_reflection.h"
#include "World.h"

struct MANGOS_DLL_DECL instance_halls_of_reflection : public BSWScriptedInstance
{
    instance_halls_of_reflection(Map* pMap) : BSWScriptedInstance(pMap) 
    {
        Difficulty = pMap->GetDifficulty();
        Initialize();
    }

    uint32 m_auiEncounter[MAX_ENCOUNTERS+1];
    std::string strSaveData;

    uint8 Difficulty;
    uint8 m_uiSummons;
    uint8 m_waveCount;

    uint32 m_auiLeader;

    ObjectGuid m_uiFalricGUID;
    ObjectGuid m_uiMarwynGUID;
    ObjectGuid m_uiLichKingGUID;
    ObjectGuid m_uiLiderGUID;
    ObjectGuid m_uiUtherGUID;

    ObjectGuid m_uiQuelDelarGUID;

    ObjectGuid m_uiMainGateGUID;
    ObjectGuid m_uiExitGateGUID;
    ObjectGuid m_uiDoor2GUID;
    ObjectGuid m_uiDoor3GUID;

    ObjectGuid m_uiFrostGeneralGUID;
    ObjectGuid m_uiCaptainsChestHordeGUID;
    ObjectGuid m_uiCaptainsChestAllianceGUID;
    ObjectGuid m_uiFrostmourneGUID;
    ObjectGuid m_uiFrostmourneAltarGUID;
    ObjectGuid m_uiPortalGUID;
    ObjectGuid m_uiIceWallGUID;
    ObjectGuid m_uiCaveGUID;

    void Initialize()
    {
        for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            m_auiEncounter[i] = NOT_STARTED;
        m_waveCount = 0;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case NPC_FALRIC:
                   m_uiFalricGUID = pCreature->GetObjectGuid();
                   break;
            case NPC_MARWYN:
                   m_uiMarwynGUID = pCreature->GetObjectGuid();
                   break;
            case BOSS_LICH_KING:
                   m_uiLichKingGUID = pCreature->GetObjectGuid();
                   break;
            case NPC_FROST_GENERAL:
                   m_uiFrostGeneralGUID = pCreature->GetObjectGuid();
                   break;
            case NPC_QUEL_DELAR:
                   m_uiQuelDelarGUID = pCreature->GetObjectGuid();
                   break;
            case NPC_UTHER:
                   m_uiUtherGUID = pCreature->GetObjectGuid();
                   break;
        }
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case  GO_IMPENETRABLE_DOOR: m_uiMainGateGUID = pGo->GetObjectGuid();
                                        if (GetData(TYPE_MARWYN) == DONE)
                                            DoOpenDoor(m_uiMainGateGUID);
                                        break;
            case  GO_FROSTMOURNE:       m_uiFrostmourneGUID = pGo->GetObjectGuid(); break;
            case  GO_ICECROWN_DOOR:     m_uiExitGateGUID = pGo->GetObjectGuid(); break;
            case  GO_ICECROWN_DOOR_2:   m_uiDoor2GUID = pGo->GetObjectGuid();
                                        if (GetData(TYPE_FROST_GENERAL) == DONE)
                                            DoOpenDoor(m_uiDoor2GUID);
                                        break;
            case  GO_ICECROWN_DOOR_3:   m_uiDoor3GUID = pGo->GetObjectGuid(); break;
            case  GO_PORTAL:            m_uiPortalGUID = pGo->GetObjectGuid(); break;
            case  GO_CAPTAIN_CHEST_1:
                                  if (Difficulty == RAID_DIFFICULTY_10MAN_NORMAL)
                                  m_uiCaptainsChestHordeGUID = pGo->GetObjectGuid(); 
                                  break;
            case  GO_CAPTAIN_CHEST_3:
                                  if (Difficulty == RAID_DIFFICULTY_25MAN_NORMAL)
                                  m_uiCaptainsChestHordeGUID = pGo->GetObjectGuid(); 
                                  break;
            case  GO_CAPTAIN_CHEST_2:
                                  if (Difficulty == RAID_DIFFICULTY_10MAN_NORMAL)
                                  m_uiCaptainsChestAllianceGUID = pGo->GetObjectGuid(); 
                                  break;
            case  GO_CAPTAIN_CHEST_4:
                                  if (Difficulty == RAID_DIFFICULTY_25MAN_NORMAL)
                                  m_uiCaptainsChestAllianceGUID = pGo->GetObjectGuid(); 
                                  break;

            case  GO_ICE_WALL:    m_uiIceWallGUID  = pGo->GetObjectGuid();
                                  pGo->SetPhaseMask(65535, true);
                                  break;
            case  GO_CAVE:        m_uiCaveGUID     = pGo->GetObjectGuid(); 
                                  DoOpenDoor(m_uiCaveGUID);
                                  break;
        }
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_PHASE:                m_auiEncounter[uiType] = uiData; break;
            case TYPE_EVENT:                m_auiEncounter[uiType] = uiData;
                                            uiData = NOT_STARTED;
                break;
            case TYPE_FALRIC:               m_auiEncounter[uiType] = uiData;
                                            if (uiData == SPECIAL)
                                                DoCloseDoor(m_uiExitGateGUID);
                                            else if (uiData == FAIL)
                                                DoOpenDoor(m_uiExitGateGUID);
                break;
            case TYPE_MARWYN:               m_auiEncounter[uiType] = uiData;
                                            if (uiData == SPECIAL)
                                                DoCloseDoor(m_uiExitGateGUID);
                                            else if (uiData == FAIL)
                                                DoOpenDoor(m_uiExitGateGUID);
                                            else if (uiData == DONE)
                                            {
                                               DoOpenDoor(m_uiMainGateGUID);
                                               DoOpenDoor(m_uiExitGateGUID);
                                            }
                break;
            case TYPE_FROST_GENERAL:        m_auiEncounter[uiType] = uiData; 
                                            if(uiData == DONE)
                                               DoOpenDoor(m_uiDoor2GUID);
                break;
            case TYPE_LICH_KING:            m_auiEncounter[uiType] = uiData;
                                            if(uiData == IN_PROGRESS)
                                               DoOpenDoor(m_uiDoor3GUID);
                                            if(uiData == DONE)
                                            {
                                                if (GameObject* pChest = instance->GetGameObject(m_uiCaptainsChestAllianceGUID))
                                                    if (pChest && !pChest->isSpawned() && GetData(DATA_ESCAPE_LIDER) == NPC_JAINA_OUTRO)
                                                    {
                                                        pChest->SetRespawnTime(DAY);
                                                    }
                                                if (GameObject* pChest = instance->GetGameObject(m_uiCaptainsChestHordeGUID))
                                                    if (pChest && !pChest->isSpawned() && GetData(DATA_ESCAPE_LIDER) == NPC_SYLVANA_OUTRO)
                                                    {
                                                        pChest->SetRespawnTime(DAY);
                                                    };
                                                if (GameObject* pPortal = instance->GetGameObject(m_uiPortalGUID))
                                                    if (pPortal && !pPortal->isSpawned()) 
                                                    {
                                                        pPortal->SetRespawnTime(DAY);
                                                    };
                                            }
                break;
            case TYPE_HALLS:                m_auiEncounter[uiType] = uiData; break;
            case DATA_SUMMONS:              if (uiData == 3) m_uiSummons = 0;
                                            else if (uiData == 1) ++m_uiSummons;
                                            else if (uiData == 0) --m_uiSummons;
                                            uiData = NOT_STARTED;
                break;
            case DATA_ESCAPE_LIDER:         m_auiLeader = uiData;
                                            uiData = NOT_STARTED;
            case DATA_WAVE_COUNT:           m_waveCount = uiData;
                                            uiData = NOT_STARTED;
                                            if (m_waveCount > 0 && m_waveCount < 10)
                                            {
                                                DoUpdateWorldState(WORLD_STATE_HOR, 1);
                                                DoUpdateWorldState(WORLD_STATE_HOR_WAVE_COUNT, m_waveCount-1);
                                            }
                                            else
                                                DoUpdateWorldState(WORLD_STATE_HOR, 0);
                break;
            default:
                break;
        }

        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;

            for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                saveStream << m_auiEncounter[i] << " ";

            strSaveData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    const char* Save()
    {
        return strSaveData.c_str();
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_PHASE:                return m_auiEncounter[uiType];
            case TYPE_EVENT:                return m_auiEncounter[uiType];
            case TYPE_FALRIC:               return m_auiEncounter[uiType];
            case TYPE_MARWYN:               return m_auiEncounter[uiType];
            case TYPE_LICH_KING:            return m_auiEncounter[uiType];
            case TYPE_FROST_GENERAL:        return m_auiEncounter[uiType];
            case TYPE_HALLS:                return m_auiEncounter[uiType];
            case DATA_SUMMONS:              return m_uiSummons;
            case DATA_ESCAPE_LIDER:         return m_auiLeader;
            default:                        return 0;
        }
        return 0;
    }

    void SetData64(uint32 uiData, uint64 uiGuid)
    {
        switch(uiData)
        {
            case DATA_ESCAPE_LIDER:
                   m_uiLiderGUID = uiGuid;
                   break;
        }
    }

    uint64 GetData64(uint32 uiData)
    {
        switch(uiData)
        {
            case GO_IMPENETRABLE_DOOR: return m_uiMainGateGUID.GetRawValue();
            case GO_FROSTMOURNE:       return m_uiFrostmourneGUID.GetRawValue();
            case NPC_FALRIC:           return m_uiFalricGUID.GetRawValue();
            case NPC_MARWYN:           return m_uiMarwynGUID.GetRawValue();
            case NPC_UTHER:            return m_uiUtherGUID.GetRawValue();
            case BOSS_LICH_KING:       return m_uiLichKingGUID.GetRawValue();
            case DATA_ESCAPE_LIDER:    return m_uiLiderGUID.GetRawValue();
            case NPC_FROST_GENERAL:    return m_uiFrostGeneralGUID.GetRawValue();
            case NPC_QUEL_DELAR:       return m_uiQuelDelarGUID.GetRawValue();
            case GO_ICECROWN_DOOR:     return m_uiExitGateGUID.GetRawValue();
            case GO_ICECROWN_DOOR_2:   return m_uiDoor2GUID.GetRawValue();
            case GO_ICECROWN_DOOR_3:   return m_uiDoor3GUID.GetRawValue();
            case GO_ICE_WALL:          return m_uiIceWallGUID.GetRawValue();
            case GO_CAVE:              return m_uiCaveGUID.GetRawValue();
        }
        return 0;
    }

    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(chrIn);

        std::istringstream loadStream(chrIn);

        for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
        {
            loadStream >> m_auiEncounter[i];

            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }

        OUT_LOAD_INST_DATA_COMPLETE;
    }

};

InstanceData* GetInstanceData_instance_halls_of_reflection(Map* pMap)
{
    return new instance_halls_of_reflection(pMap);
}

void AddSC_instance_halls_of_reflection()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_halls_of_reflection";
    newscript->GetInstanceData = &GetInstanceData_instance_halls_of_reflection;
    newscript->RegisterSelf();
}
