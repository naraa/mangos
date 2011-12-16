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

#ifndef DEF_OCULUS_H
#define DEF_OCULUS_H

enum
{
    MAX_ENCOUNTER                  = 1,

    TYPE_DRAKOS                    = 0,

    NPC_BALGAR_IMAGE       = 28012,
    NPC_VERDISA            = 27657,
    NPC_BELGARISTRASZ      = 27658,
    NPC_ETERNOS            = 27659,
    NPC_DRAKOS             = 27654,
    NPC_VAROS              = 27447,
    NPC_UROM               = 27655,
    NPC_EREGOS             = 27656,

    GO_DRAGON_CAGE_DOOR    = 193995,
    GO_EREGOS_CACHE        = 191349,
    GO_EREGOS_CACHE_H      = 193603,
    GO_SPOTLIGHT           = 191351,
    GO_ORB_OF_NEXUS        = 188715,
};

class MANGOS_DLL_DECL instance_oculus : public ScriptedInstance
{
    public:
        instance_oculus(Map* pMap);

        void Initialize();

        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);

        uint32 GetData(uint32 uiType);
        void SetData(uint32 uiType, uint32 uiData);

        const char* Save() { return m_strInstData.c_str(); }

        void Load(const char* chrIn);

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;
};

#endif
