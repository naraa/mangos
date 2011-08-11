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
SDName: Instance_Shattered_Halls
SD%Complete: 50
SDComment: currently missing info about door. instance not complete
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

#include "precompiled.h"
#include "shattered_halls.h"

instance_shattered_halls::instance_shattered_halls(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_shattered_halls::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_shattered_halls::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_NETHEKURSE_DOOR:
            if (m_auiEncounter[TYPE_NETHEKURSE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_NETHERKURSE_ENTER_DOOR:
            if (m_auiEncounter[TYPE_NETHEKURSE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        default:
            return;
    }

    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_shattered_halls::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_NETHEKURSE:
        case NPC_DRISELLA:
        case NPC_RANDY_WHIZZLESPROCKET:
        case NPC_SCOUT_ORGARR:
        case NPC_KORAG_PROUDMANE:
        case NPC_CAPTAINBONESHATTER:
        case NPC_PRIVATE_JACINT:
        case NPC_RIFLEMAN_BROWNBEARD:
        case NPC_CAPTAIN_ALINA:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
    }
}

void instance_shattered_halls::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_NETHEKURSE:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(GO_NETHEKURSE_DOOR);
            break;
        case TYPE_OMROGG:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_BLADEFIST:
            m_auiEncounter[uiType] = uiData;
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2];
        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_shattered_halls::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_shattered_halls::GetData(uint32 uiType)
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

InstanceData* GetInstanceData_instance_shattered_halls(Map* pMap)
{
    return new instance_shattered_halls(pMap);
}

enum
{
    QUEST_IMPRISONED_IN_THE_CITADEL_A   = 9524,
    QUEST_IMPRISONED_IN_THE_CITADEL_H   = 9525,

    AREATRIGGER_ENTER_1                 = 4183,
    AREATRIGGER_ENTER_2                 = 4182,
    AREATRIGGER_AFTER_NETHEKURSE        = 4524,

    SPELL_KARGATHS_EXECUTIONER_1        = 39288, //55min
    SPELL_KARGATHS_EXECUTIONER_2        = 39289, //10min
    SPELL_KARGATHS_EXECUTIONER_3        = 39290, //15min
};

bool AreaTrigger_at_shattered_halls(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (instance_shattered_halls* pInstance = (instance_shattered_halls*)pPlayer->GetInstanceData())
    {
        if (!pInstance->instance->IsRegularDifficulty())
        {
            if (pPlayer->isGameMaster() || pPlayer->isDead())
                return false;

            if (pInstance->GetData(TYPE_NETHEKURSE) == DONE)
            {
                if (pPlayer->GetQuestStatus(QUEST_IMPRISONED_IN_THE_CITADEL_A) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_IMPRISONED_IN_THE_CITADEL_H) == QUEST_STATUS_INCOMPLETE)
                {
                    if (pAt->id == AREATRIGGER_AFTER_NETHEKURSE)
                    {
                        if (!pPlayer->HasAura(SPELL_KARGATHS_EXECUTIONER_1) || !pPlayer->HasAura(SPELL_KARGATHS_EXECUTIONER_2) || !pPlayer->HasAura(SPELL_KARGATHS_EXECUTIONER_3))
                        {
                            pPlayer->CastSpell(pPlayer, SPELL_KARGATHS_EXECUTIONER_1, true);
                            if (pInstance->GetSingleCreatureFromStorage(NPC_SCOUT_ORGARR) || pInstance->GetSingleCreatureFromStorage(NPC_KORAG_PROUDMANE)  || pInstance->GetSingleCreatureFromStorage(NPC_CAPTAINBONESHATTER) || pInstance->GetSingleCreatureFromStorage(NPC_PRIVATE_JACINT) || pInstance->GetSingleCreatureFromStorage(NPC_RIFLEMAN_BROWNBEARD) || pInstance->GetSingleCreatureFromStorage(NPC_CAPTAIN_ALINA))
                                return false;

                            if (pPlayer->GetTeam() == HORDE)
                            {
                                pPlayer->SummonCreature(NPC_SCOUT_ORGARR, 151.040f, -91.558f, 1.936f, 1.559f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                                pPlayer->SummonCreature(NPC_KORAG_PROUDMANE, 150.669f, -77.015f, 1.933f, 4.705f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                                pPlayer->SummonCreature(NPC_CAPTAINBONESHATTER, 138.241f, -84.198f, 1.907f, 0.055f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                            }
                            if (pPlayer->GetTeam() == ALLIANCE)
                            {
                                pPlayer->SummonCreature(NPC_PRIVATE_JACINT, 151.040f, -91.558f, 1.936f, 1.559f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                                pPlayer->SummonCreature(NPC_RIFLEMAN_BROWNBEARD, 150.669f, -77.015f, 1.933f, 4.705f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                                pPlayer->SummonCreature(NPC_CAPTAIN_ALINA, 138.241f, -84.198f, 1.907f, 0.055f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                            }
                            return false;
                        }
                    }
                }
            }

            if (pAt->id == AREATRIGGER_ENTER_1 || AREATRIGGER_ENTER_2)
            {
                if (pInstance->GetSingleCreatureFromStorage(NPC_DRISELLA) || pInstance->GetSingleCreatureFromStorage(NPC_RANDY_WHIZZLESPROCKET))
                    return false;

                if (pPlayer->GetTeam() == HORDE)
                {
                    pPlayer->SummonCreature(NPC_DRISELLA, 119.609f, 256.127f, -45.254f, 5.133f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                }
                if (pPlayer->GetTeam() == ALLIANCE)
                {
                    pPlayer->SummonCreature(NPC_RANDY_WHIZZLESPROCKET, 131.106f, 254.520f, -45.236f, 3.951f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 24*HOUR*IN_MILLISECONDS);
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
};

void AddSC_instance_shattered_halls()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_shattered_halls";
    pNewScript->GetInstanceData = &GetInstanceData_instance_shattered_halls;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_shattered_halls";
    pNewScript->pAreaTrigger = &AreaTrigger_at_shattered_halls;
    pNewScript->RegisterSelf();
}
