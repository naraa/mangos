using System;

namespace EventAI
{
    public enum HasOrNot
    {
        Has = 0,
        Not = 1,
    };

    public enum PlayerLevel
    {
        equel   = 0,
        Higher  = 1,
        Lower   = 2,
    };

    public enum SubArea
    {
        In      = 0,
        Not_In  = 1,
    };

    public enum OptionIcon
    {
        Chat            = 0,
        Vendor          = 1,
        Taxi            = 2,
        Trainer         = 3,
        Interact_1      = 4,
        Interact_2      = 5,
        Money_Bag       = 6,
        Talk            = 7,
        Tabard          = 8,
        Battle          = 9,
        Dot             = 10,
    };

    public enum OptionID
    {
        NONE                = 0,
        GOSSIP              = 1,
        QUESTGIVER          = 2,
        VENDOR              = 3,
        TAXIVENDOR          = 4,
        TRAINER             = 5,
        SPIRITHEALER        = 6,
        SPIRITGUID          = 7,
        INNKEPPER           = 8,
        BANKER              = 9,
        PETITONER           = 10,
        TABARDDESIGNER      = 11,
        BATTLEFILED         = 12,
        AUCTIONEER          = 13,
        STABLEPET           = 14,
        ARMORER             = 15,
        UNLEARNTALENTS      = 16,
        UNLEARNPETTALENTS   = 17,
        LEARNDUALSPEC       = 18,
        PLAYER_BOT          = 99,
    };

    public enum Option_NPC_Flag
    {
        NONE                = 0,
        GOSSIP              = 1,
        QUESTGIVER          = 2,
        VENDOR              = 128,
        TAXIVENDOR          = 8192,
        TRAINER             = 16,
        UNLEARNTALENTS      = 16,
        UNLEARNPETTALENTS   = 16,
        LEARNDUALSPEC       = 16,
        SPIRITHEALER        = 16384,
        SPIRITGUID          = 32768,
        INNKEPPER           = 65536,
        BANKER              = 131072,
        PETITONER           = 262144,
        TABARDDESIGNER      = 524288,
        BATTLEFILED         = 1048576,
        AUCTIONEER          = 2097152,
        STABLEPET           = 4194304,
        ARMORER             = 4096,
    };

    public enum Gossip_Conditions
    {
        NONE                    = 0,
        AURA                    = 1,
        ITEM                    = 2,
        ITEM_EQUIPPED           = 3,
        AREAID                  = 4,
        REPUTATION_RANK         = 5,
        TEAM                    = 6,
        SKILL                   = 7,
        QUEST_REWARDED          = 8,
        QUEST_TAKEN             = 9,
        AD_COMMISION_AURA       = 10,
        NO_AURA                 = 11,
        ACTIVE_EVENT            = 12,
        AREA_FLAG               = 13,
        RACE_CLASS              = 14,
        LEVEL                   = 15,
        NO_ITEM                 = 16,
        SPELL                   = 17,
        INSTANCE_SCRIPT         = 18,
        QUEST_AVAILBLE          = 19,
        ACHIEVEMENT             = 20,
        ACHIEVEMENTREALM        = 21,
        QUEST_NONE              = 22,
        ITEM_WITH_BANK          = 23,
        NOITEM_WITH_BANK        = 24,
        NOT_ACTIVE_GAME_EVENT   = 25,
        ACTIVE_HOLIDAY          = 26,
        NOT_ACTIVE_HOLIDAY      = 27
    };
}