/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SHATTERED_H
#define DEF_SHATTERED_H

enum
{
    MAX_ENCOUNTER               = 3,

    TYPE_NETHEKURSE             = 0,
    TYPE_OMROGG                 = 1,
    TYPE_BLADEFIST              = 2,                        // TODO Currently unhandled

    NPC_NETHEKURSE              = 16807,
    NPC_DRISELLA                = 17294,
    NPC_RANDY_WHIZZLESPROCKET   = 17288,
    NPC_SCOUT_ORGARR            = 17297,
    NPC_KORAG_PROUDMANE         = 17295,
    NPC_CAPTAINBONESHATTER      = 17296,
    NPC_PRIVATE_JACINT          = 17292,
    NPC_RIFLEMAN_BROWNBEARD     = 17289,
    NPC_CAPTAIN_ALINA           = 17290,

    GO_NETHEKURSE_DOOR          = 182540,
    GO_NETHERKURSE_ENTER_DOOR   = 182539,                   // TODO Currently unhandled
};

class MANGOS_DLL_DECL instance_shattered_halls : public ScriptedInstance
{
    public:
        instance_shattered_halls(Map* pMap);

        void Initialize();

        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;
};

#endif
