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
SDName: instance_oculus
SD%Complete: %
SDComment:
SDCategory: The Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

instance_oculus::instance_oculus(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_oculus::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_oculus::OnPlayerEnter(Player *pPlayer)
{
    // show world state if players reenter oculus for any reason (e.i. = gated , died ,raid wipe, ect ect )
    if (GetData(TYPE_DRAKOS) == DONE && GetData(TYPE_VAROS) != DONE)
    {
        DoUpdateWorldState(WORLD_STATE_CON, 1);
        DoUpdateWorldState(WORLD_STATE_CON_COUNT, m_sConstructsGUIDs.size());
    }
}

void instance_oculus::DoOpenAllCages()
{
    // open all doors
    for(GUIDList::const_iterator itr = m_lCageDoorGUIDs.begin(); itr != m_lCageDoorGUIDs.end(); ++itr)
        DoUseDoorOrButton(*itr);

    // get the prisoners out
    if(Creature* pEternos = GetSingleCreatureFromStorage(NPC_ETERNOS))
        pEternos->GetMotionMaster()->MovePoint(0, m_sPrisonersMoveLocs[0].m_fX, m_sPrisonersMoveLocs[0].m_fY, m_sPrisonersMoveLocs[0].m_fZ);

    if(Creature* pVerdisa = GetSingleCreatureFromStorage(NPC_VERDISA))
        pVerdisa->GetMotionMaster()->MovePoint(0, m_sPrisonersMoveLocs[1].m_fX, m_sPrisonersMoveLocs[1].m_fY, m_sPrisonersMoveLocs[1].m_fZ);

    if(Creature* pBelgaristrasz = GetSingleCreatureFromStorage(NPC_BELGARISTRASZ))
        pBelgaristrasz->GetMotionMaster()->MovePoint(0, m_sPrisonersMoveLocs[2].m_fX, m_sPrisonersMoveLocs[2].m_fY, m_sPrisonersMoveLocs[2].m_fZ);
}

void instance_oculus::OnCreatureDeath(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_CONSTRUCT:
            if (m_sConstructsGUIDs.find(pCreature->GetObjectGuid()) != m_sConstructsGUIDs.end())
            {
                m_sConstructsGUIDs.erase(pCreature->GetObjectGuid());

                // update world state
                DoUpdateWorldState(WORLD_STATE_CON_COUNT, m_sConstructsGUIDs.size());

                // check if event complete
                if (m_sConstructsGUIDs.empty())
                    SetData(TYPE_CONSTRUCTS, DONE);
            }
            break;
    }
}

void instance_oculus::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_EREGOS_CACHE:
        case GO_EREGOS_CACHE_H:
        case GO_SPOTLIGHT:
            m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
            break;
        case GO_DRAGON_CAGE_DOOR:
            m_lCageDoorGUIDs.push_back(pGo->GetObjectGuid());
            if (m_auiEncounter[TYPE_DRAKOS] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        default:
            return;
    }
}

void instance_oculus::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_BELGAR_IMAGE:
        case NPC_VERDISA:
        case NPC_BELGARISTRASZ:
        case NPC_ETERNOS:
        case NPC_DRAKOS:
        case NPC_UROM:
        case NPC_EREGOS:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case NPC_VAROS:
            if (GetData(TYPE_CONSTRUCTS) != DONE)
            {
                pCreature->CastSpell(pCreature, SPELL_CENTRIFUGE_SHIELD, false);
                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case NPC_CONSTRUCT:
            m_sConstructsGUIDs.insert(pCreature->GetObjectGuid());
            break;
    }
}

uint32 instance_oculus::GetData(uint32 uiType)
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

void instance_oculus::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_DRAKOS:
            m_auiEncounter[TYPE_DRAKOS] = uiData;
            if (uiData == DONE)
            {
                // open cages
                DoOpenAllCages();

                // varos intro
                if (Creature* pVaros = GetSingleCreatureFromStorage(NPC_VAROS))
                    DoScriptText(SAY_VAROS_INTRO, pVaros);

                // update world state
                DoUpdateWorldState(WORLD_STATE_CON, 1);
                DoUpdateWorldState(WORLD_STATE_CON_COUNT, m_sConstructsGUIDs.size());
            }
            break;
        case TYPE_VAROS:
            m_auiEncounter[TYPE_VAROS] = uiData;
            if (uiData == DONE)
            {
                // update world state
                DoUpdateWorldState(WORLD_STATE_CON, 0);
            }
            break;
        case TYPE_CONSTRUCTS:
            m_auiEncounter[TYPE_CONSTRUCTS] = uiData;
            if (uiData == DONE)
            {
                if (Creature* pVaros = GetSingleCreatureFromStorage(NPC_VAROS))
                {
                    pVaros->InterruptNonMeleeSpells(false);
                    pVaros->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }
            break;
        default:
            error_log("SD2: Instance OCULUS: ERROR SetData = %u for type %u does not exist/not implemented.", uiType, uiData);
            return;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[TYPE_DRAKOS] << " " << m_auiEncounter[TYPE_VAROS] << " " << m_auiEncounter[TYPE_CONSTRUCTS];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_oculus::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[TYPE_DRAKOS] >> m_auiEncounter[TYPE_VAROS] >> m_auiEncounter[TYPE_CONSTRUCTS];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_oculus(Map* pMap)
{
    return new instance_oculus(pMap);
}

void AddSC_instance_oculus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_oculus";
    pNewScript->GetInstanceData = &GetInstanceData_instance_oculus;
    pNewScript->RegisterSelf();
}
