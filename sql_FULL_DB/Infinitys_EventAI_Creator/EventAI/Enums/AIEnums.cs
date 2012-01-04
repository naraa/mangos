using System;

namespace EventAI
{
    [Flags]
    public enum Phase
    {
        PHASE_1,
        PHASE_2,
        PHASE_3,
        PHASE_4,
        PHASE_5,
        PHASE_6,
        PHASE_7,
        PHASE_8,
        PHASE_9,
        PHASE_10,
        PHASE_11,
        PHASE_12,
        PHASE_13,
        PHASE_14,
        PHASE_15,
        PHASE_16,
        PHASE_17,
        PHASE_18,
        PHASE_19,
        PHASE_20,
        PHASE_21,
        PHASE_22,
        PHASE_23,
        PHASE_24,
        PHASE_25,
        PHASE_26,
        PHASE_27,
        PHASE_28,
        PHASE_29,
        PHASE_30,
        PHASE_31,
    };

    public enum EventType
    {
        TIMER                   = 0,
        TIMER_OOC               = 1,
        HP                      = 2,
        MANA                    = 3,
        AGGRO                   = 4,
        KILL                    = 5,
        DEATH                   = 6,
        EVADE                   = 7,
        SPELLHIT                = 8,
        RANGE                   = 9,
        OOC_LOS                 = 10,
        SPAWNED                 = 11,
        TARGET_HP               = 12,
        TARGET_CASTING          = 13,
        FRIENDLY_HP             = 14,
        FRIENDLY_IS_CC          = 15,
        FRIENDLY_MISSING_BUFF   = 16,
        SUMMONED_UNIT           = 17,
        TARGET_MANA             = 18,
        REACHED_HOME            = 21,
        RECEIVE_EMOTE           = 22,
        AURA                    = 23,
        TARGET_AURA             = 24,
        SUMMONED_JUST_DIED      = 25,
        SUMMONED_JUST_DESPAWN   = 26,
        MISSING_AURA            = 27,
        TARGET_MISSING_AURA     = 28,
    };

    public enum ActionType
    {
        NONE                       = 0,
        TEXT                       = 1,
        SET_FACTION                = 2,
        MORPH_TO_ENTRY_OR_MODEL    = 3,
        SOUND                      = 4,
        EMOTE                      = 5,
        RANDOM_SAY                 = 6,
        RANDOM_YELL                = 7,
        RANDOM_TEXTEMOTE           = 8,
        RANDOM_SOUND               = 9,
        RANDOM_EMOTE               = 10,
        CAST                       = 11,
        TEMP_SUMMON                = 12,
        THREAT_SINGLE_PCT          = 13,
        THREAT_ALL_PCT             = 14,
        QUEST_EVENT                = 15,
        CASTCREATUREGO             = 16,
        SET_UNIT_FIELD             = 17,
        SET_UNIT_FLAG              = 18,
        REMOVE_UNIT_FLAG           = 19,
        AUTO_ATTACK                = 20,
        COMBAT_MOVEMENT            = 21,
        SET_PHASE                  = 22,
        INC_PHASE                  = 23,
        EVADE                      = 24,
        FLEE_FOR_ASSIST            = 25,
        QUEST_EVENT_ALL            = 26,
        CASTCREATUREGO_ALL         = 27,
        REMOVEAURASFROMSPELL       = 28,
        RANGED_MOVEMENT            = 29,
        RANDOM_PHASE               = 30,
        RANDOM_PHASE_RANGE         = 31,
        SUMMON                     = 32,
        KILLED_MONSTER             = 33,
        SET_INST_DATA              = 34,
        SET_INST_DATA64            = 35,
        UPDATE_TEMPLATE            = 36,
        DIE                        = 37,
        ZONE_COMBAT_PULSE          = 38,
        CALL_FOR_HELP              = 39,
        SET_SHEATH                 = 40,
        FORCE_DESPAWN              = 41,
        SET_INVINCIBILITY_HP_LEVEL = 42,
        MOUNT_TO_ENTRY_OR_MODEL    = 43,
    };

    public enum ConditionType
    {
        NONE              = 0,
        AURA              = 1,
        ITEM              = 2,
        ITEM_EQUIPPED     = 3,
        ZONEID            = 4,
        REPUTATION_RANK   = 5,
        TEAM              = 6,
        SKILL             = 7,
        QUESTREWARDED     = 8,
        QUESTTAKEN        = 9,
        ACTIVE_EVENT      = 12,
    };

    public enum ConditionTeam
    {
        Alliance = 469,
        Horde = 67,
    };

    public enum Team
    {
        Alliance = 0,
        Horde = 1,
    };

    public enum ValueType
    {
        VALUE = 0,
        RATE = 1,
    };

    public enum YesNO
    {
        NO = 0,
        YES  = 1,
    };

    public enum TargetFrends
    {
        Hostile = 0,
        Friendly = 1,
    }

    public enum SheathState
    {
        STATE_UNARMED    = 0,
        STATE_MELEE      = 1,
        STATE_RANGED     = 2,
    };

    public enum instanceData
    {
        NOT_STARTED = 0,
        IN_PROGRESS = 1,
        FAIL        = 2,
        DONE        = 3,
        SPECIAL     = 4,
    };

    public enum CastFlags
    { 
        INTURRUPT_PREVIOUS         = 1,
        TRIGGERED                  = 2,
        FORCE_CAST                  = 4,
        NO_MELEE_IF_OOM            = 8,
        FORCE_TARGET_SELF          = 16,
        AURA_NOT_PRESENT           = 32,
    };

    public enum School
    { 
        NORMAL      = 0,
        HOLY        = 1,
        FIRE        = 2,
        NATURE      = 3,
        FROST       = 4,
        SHADOW      = 5,
        ARCANE      = 6,
    };

    public enum CastTarget
    {
        SELF                   = 0,
        HOSTILE                = 1,
        HOSTILE_SECOND_AGGRO   = 2,
        HOSTILE_LAST_AGGRO     = 3,
        HOSTILE_RANDOM         = 4,
        HOSTILE_RANDOM_NOT_TOP = 5,
        ACTION_INVOKER         = 6,
    };

    public enum MessageType
    { 
        SAY             = 0,
        YELL            = 1,
        TEXT_EMOTE      = 2,
        BOSS_EMOTE      = 3,
        WHISPER         = 4,
        BOSS_WHISPER    = 5,
        ZONE_YELL       = 6,
    };

    public enum Lenguage   // language
    { 
        UNIVERSAL               = 0,
        ORCISH                  = 1,
        DARNASSIAN              = 2,
        TAURAHE                 = 3,
        DWARVISH                = 6,
        COMMON                  = 7,
        DEMONIC                 = 8,
        TITAN                   = 9,
        THALASSIAN              = 10,
        DRACONIC                = 11,
        KALIMAG                 = 12,
        GNOMISH                 = 13,
        TROLL                   = 14,
        GUTTERSPEAK             = 33,
        DRAENEI                 = 35,
        ZOMBIE                  = 36,
        GNOMISH_BINARY          = 37,
        GOBLIN_BINARY           = 38,
    };

    public enum Locales
    {
        enUS = 0,
        koKR = 1,
        frFR = 2,
        deDE = 3,
        zhCN = 4,
        zhTW = 5,
        esES = 6,
        esMX = 7,
        ruRU = 8,
    };

    public enum Race
    {
        Human       = 1,
        Orc         = 2,
        Dwarf       = 3,
        Night_Elf   = 4,
        Undead      = 5,
        Tauren      = 6,
        Gnome       = 7,
        Troll       = 8,
        Bloodelf    = 9,
        Draenei     = 11
    }

    public enum Class
    {
        Warrior         = 1,
        Paladin         = 2,
        Hunter          = 3,
        Rogue           = 4,
        Priest          = 5,
        Death_Knight    = 6,
        Shaman          = 7,
        Mage            = 8,
        Warlock         = 9,
        Druid           = 11
    }
}
