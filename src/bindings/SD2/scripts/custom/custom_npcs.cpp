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
SDName: all of our custom npcs
SD%Complete: 100
SDComment: The collection of Infinity cutom npcs
EndScriptData */

/*npc_content
custom_npc_buffmaster
custom_npc_guildmaster
custom_npc_news
custom_npc_professionmaster
custom_npc_renamecharacter
custom_npc_resetinstance
custom_npc_resetlevel
custom_npc_spellmaster
custom_npc_teleportmaster
custom_npc_titlemaster
custom_npc_tokenvendor
custom_script_training_dummy
*/

#include "precompiled.h"
#include "../../../../shared/Config/Config.h"
#include "../../config.h"
#include "Database/DatabaseEnv.h"
extern DatabaseMysql SD2Database;
extern DatabaseType CharacterDatabase;
extern Config SD2Config;

#define MSG_COMBAT	"You Are In Combat."

int DEBUG_TELE = 0; //Set to 1 to see debugger messages in error logs

//buff master
bool GossipHello_custom_npc_buffmaster(Player* pPlayer, Creature* pCreature)
{
    Config SD2Config;
	if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
		error_log("SD2: Unable to open configuration file");

	bool SmallBuffsEnabled = SD2Config.GetBoolDefault("BuffsMaster.SmallBuffsEnabled", true);
	bool GreatBuffsEnabled = SD2Config.GetBoolDefault("BuffsMaster.GreatBuffsEnabled", true);
	bool GameMasterBuffsEnabled = SD2Config.GetBoolDefault("BuffsMaster.GameMasterBuffsEnabled", true);
	bool PlayerToolsEnabled = SD2Config.GetBoolDefault("BuffsMaster.PlayerToolsEnabled", true);
	bool GoldSpellEnabled = SD2Config.GetBoolDefault("BuffsMaster.GoldSpellEnabled", false);

    if (pPlayer->GetTeam() == ALLIANCE)
	{
	    if(SmallBuffsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buffs ->"              , GOSSIP_SENDER_MAIN, 1000);
	    if(GreatBuffsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buffs ->"              , GOSSIP_SENDER_MAIN, 2000);
	    if(GameMasterBuffsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buffs ->"                 , GOSSIP_SENDER_MAIN, 3000);
        if(PlayerToolsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
	}
	else
	{
	    if(SmallBuffsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buffs ->"              , GOSSIP_SENDER_MAIN, 1000);
	    if(GreatBuffsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buffs ->"              , GOSSIP_SENDER_MAIN, 2000);
	    if(GameMasterBuffsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buffs ->"                 , GOSSIP_SENDER_MAIN, 3000);
        if(PlayerToolsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
	}
    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
    return true;
}

void SendDefaultMenu_custom_npc_buffmaster(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

    //Combat Check
    if (pPlayer->isInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
        return;
    }

    Config SD2Config;
	if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
		error_log("SD2: Unable to open configuration file");

    //Money Check
    if (pPlayer->GetMoney() < (SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)))
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterWhisper("You don't have enough money.", pPlayer, false);
        return;
    }

	bool SmallBuffsEnabled = SD2Config.GetBoolDefault("BuffsMaster.SmallBuffsEnabled", true);
	bool GreatBuffsEnabled = SD2Config.GetBoolDefault("BuffsMaster.GreatBuffsEnabled", true);
	bool GameMasterBuffsEnabled = SD2Config.GetBoolDefault("BuffsMaster.GameMasterBuffsEnabled", true);
	bool PlayerToolsEnabled = SD2Config.GetBoolDefault("BuffsMaster.PlayerToolsEnabled", true);
	bool GoldSpellEnabled = SD2Config.GetBoolDefault("BuffsMaster.GoldSpellEnabled", false);

    switch(uiAction)
    {
        case 1000:
        {
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Mark of the Wild"                , GOSSIP_SENDER_MAIN, 1001);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Amplify Magic"                   , GOSSIP_SENDER_MAIN, 1010);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Arcane Intellect"                , GOSSIP_SENDER_MAIN, 1015);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Dalaran Intellect"               , GOSSIP_SENDER_MAIN, 1020);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Dampen Magic"                    , GOSSIP_SENDER_MAIN, 1025);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Blessing of Kings"               , GOSSIP_SENDER_MAIN, 1030);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Blessing of Might"               , GOSSIP_SENDER_MAIN, 1035);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Blessing of Wisdom"              , GOSSIP_SENDER_MAIN, 1040);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Divine Spirit"                   , GOSSIP_SENDER_MAIN, 1045);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Power Word: Fortitude"           , GOSSIP_SENDER_MAIN, 1050);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Shadow Protection"               , GOSSIP_SENDER_MAIN, 1055);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
                break;
        }
        case 2000:
        {
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Gift of the Wild"                , GOSSIP_SENDER_MAIN, 2001);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Arcane Brilliance"               , GOSSIP_SENDER_MAIN, 2005);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Dalaran Brilliance"              , GOSSIP_SENDER_MAIN, 2010);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Kings"       , GOSSIP_SENDER_MAIN, 2015);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Might"       , GOSSIP_SENDER_MAIN, 2020);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Sanctuary"   , GOSSIP_SENDER_MAIN, 2025);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Greater Blessing of Wisdom"      , GOSSIP_SENDER_MAIN, 2030);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Prayer of Fortitude"             , GOSSIP_SENDER_MAIN, 2035);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Prayer of Shadow Protection"     , GOSSIP_SENDER_MAIN, 2040);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Prayer of Spirit"                , GOSSIP_SENDER_MAIN, 2045);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
                break;
        }
        case 3000:
        {
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Agamaggan's Agility"             , GOSSIP_SENDER_MAIN, 3001);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Agamaggan's Strength"            , GOSSIP_SENDER_MAIN, 3005);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Armor Magic"                     , GOSSIP_SENDER_MAIN, 3010);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Armor Penetration"               , GOSSIP_SENDER_MAIN, 3015);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Increased Stamina"               , GOSSIP_SENDER_MAIN, 3020);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Razorhide"                       , GOSSIP_SENDER_MAIN, 3025);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Rising Spirit"                   , GOSSIP_SENDER_MAIN, 3030);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Spirit of the Wind"              , GOSSIP_SENDER_MAIN, 3035);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Buff me Wisdom of Agamaggan"             , GOSSIP_SENDER_MAIN, 3040);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
                break;
        }
        case 4000:
        {
                if(GoldSpellEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Give me Gold"                            , GOSSIP_SENDER_MAIN, 4001);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Give me Soul Shards"                     , GOSSIP_SENDER_MAIN, 4005);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Heal me Please"                          , GOSSIP_SENDER_MAIN, 4010);
                pPlayer->ADD_GOSSIP_ITEM( 5, "Heal me and party members Please"        , GOSSIP_SENDER_MAIN, 4015);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"                            , GOSSIP_SENDER_MAIN, 5005);

                pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
                break;
        }
        case 5005:
        {
            if (pPlayer->GetTeam() == ALLIANCE)
            {
                if(SmallBuffsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buffs ->"              , GOSSIP_SENDER_MAIN, 1000);
                if(GreatBuffsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buffs ->"              , GOSSIP_SENDER_MAIN, 2000);
                if(GameMasterBuffsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buffs ->"                 , GOSSIP_SENDER_MAIN, 3000);
                if(PlayerToolsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
            }
            else
            {
                if(SmallBuffsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "Small Buffs ->"              , GOSSIP_SENDER_MAIN, 1000);
                if(GreatBuffsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "Great Buffs ->"              , GOSSIP_SENDER_MAIN, 2000);
                if(GameMasterBuffsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "GM Buffs ->"                 , GOSSIP_SENDER_MAIN, 3000);
                if(PlayerToolsEnabled)
                    pPlayer->ADD_GOSSIP_ITEM( 7, "Player Tools ->"            , GOSSIP_SENDER_MAIN, 4000);
            }
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            break;
        }
        case 1001: // Buff me Mark of the Wild
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48469,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1010: // Buff me Amplify Magic
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,43017,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1015: // Buff me Arcane Intellect
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,42995,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1020: // Buff me Dalaran Intellect
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,61024,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1025: // Buff me Dampen Magic
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,43015,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1030: // Buff me Blessing of Kings
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,20217,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1035: // Buff me Blessing of Might
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48932,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1040: // Buff me Blessing of Wisdom
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48936,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1045: // Buff me Divine Spirit
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48073,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1050: // Buff me Power Word: Fortitude
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48161,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 1055: // Buff me Shadow Protection
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48169,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        //////////////////////////////////////////////////Great Buff///////////////////////////////////////////////////////////////

        case 2001: // Buff me Gift of the Wild
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,48470,true);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2005: // Buff me Arcane Brilliance
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,43002,true);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2010: // Buff me Dalaran Brilliance
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,61316,true);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2015: // Buff me Greater Blessing of Kings
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,25898,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2020: // Buff me Greater Blessing of Might
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48934,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2025: // Buff me Greater Blessing of Sanctuary
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,25899,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2030: // Buff me Greater Blessing of Wisdom
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,48938,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2035: // Buff me Prayer of Fortitude
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,48162,true);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2040: // Buff me Prayer of Shadow Protection
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,48170,true);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 2045: // Buff me Prayer of Spirit
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,48074,true);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        //////////////////////////////////////////////////GM Buff///////////////////////////////////////////////////////////////

        case 3001: // Buff me Agamaggan's Agility
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,17013,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3005: // Buff me Agamaggan's Strength
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,16612,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3010: // Buff me Armor Magic
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,58453,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3015: // Buff me Armor Penetration
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,34106,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3020: // Buff me Increased Stamina
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,25661,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3025: // Buff me Razorhide
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,16610,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3030: // Buff me Rising Spirit
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,10767,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3035: // Buff me Spirit of the Wind
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,16618,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 3040: // Buff me Wisdom of Agamaggan
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,7764,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        //////////////////////////////////////////////////Player Tools///////////////////////////////////////////////////////////////

        case 4001://Give me Gold
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,46642,false); // 5000 gold
            break;
        }
        case 4005://Give me Soul Shards
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,24827,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 4010: // Heal me please
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer,38588,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 4015: // Heal me and party members Please
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,53251,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 4020: // Conjure Refreshment
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,42956,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        case 4025: // Conjure Mana Gem
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->CastSpell(pPlayer,42985,false);
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("BuffsMaster.BuffCost",0)));
            break;
        }
        pPlayer->CLOSE_GOSSIP_MENU();
    }
}

bool GossipSelect_custom_npc_buffmaster(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	// Main menu
	if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_buffmaster(pPlayer, pCreature, uiAction);

    return true;
}

//guild master
#define MSG_GOSSIP_TELE          "Teleport to Guild Hall."
#define MSG_GOSSIP_BUY           "Buy Guild Hall (10000 Gold)."
#define MSG_GOSSIP_SELL          "Sell Guild Hall (5000 Gold)."
#define MSG_GOSSIP_NEXTPAGE      "Next -->"
#define MSG_INCOMBAT             "Your in combat!"
#define MSG_NOGUILDHOUSE         "Your Guild doesn't have a Guild Hall."
#define MSG_NOFREEGH             "Sorry, but all Guild Halls are taken."
#define MSG_ALREADYHAVEGH        "Sorry, but you already have a Guild Hall."
#define MSG_NOTENOUGHMONEY       "Sorry, but you dont have enough gold."
#define MSG_GHOCCUPIED           "Sorry, but this Guild Hall is already taken."
#define MSG_CONGRATULATIONS      "You have been teleported to your Guild Hall."
#define MSG_SOLD                 "You have sold your Guild Hall, here is your gold."
#define MSG_NOTINGUILD           "You dont have a guild! Join or create new one."
#define MSG_HASGUILDHOUSE        "Your guild already has a Guild Hall, get lost n00b!"

#define OFFSET_GH_ID_TO_ACTION   1500
#define OFFSET_SHOWBUY_FROM      10000

#define ACTION_TELE              1001
#define ACTION_SHOW_BUYLIST      1002
#define ACTION_SELL_GUILDHOUSE   1003

#define ICON_GOSSIP_BALOON       0
#define ICON_GOSSIP_WING         2
#define ICON_GOSSIP_BOOK         3
#define ICON_GOSSIP_WHEEL1       4
#define ICON_GOSSIP_WHEEL2       5
#define ICON_GOSSIP_GOLD         6
#define ICON_GOSSIP_BALOONDOTS   7
#define ICON_GOSSIP_TABARD       8
#define ICON_GOSSIP_XSWORDS      9

#define COST_GH_BUY              100000000  //10000 G.
#define COST_GH_SELL             50000000   //5000 G.

#define GOSSIP_COUNT_MAX         10

bool isPlayerGuildLeader(Player *player)
{
    return (player->GetRank() == 0) && (player->GetGuildId() != 0);
}

bool getGuildHouseCoords(uint32 guildId, float &x, float &y, float &z, uint32 &map)
{
    if (guildId == 0)
    {
        //if player has no guild
        return false;
    }

    QueryResult *result;
    result = SD2Database.PQuery("SELECT `x`, `y`, `z`, `map` FROM `guildhalls` WHERE `guildId` = %u", guildId);
    if(result)
    {
        Field *fields = result->Fetch();
        x = fields[0].GetFloat();
        y = fields[1].GetFloat();
        z = fields[2].GetFloat();
        map = fields[3].GetUInt32();
        delete result;
        return true;
    }
    return false;
}

void teleportPlayerToGuildHouse(Player *player, Creature *_creature)
{
    if (player->GetGuildId() == 0)
    {
        //if player has no guild
        _creature->MonsterWhisper(MSG_NOTINGUILD, player, false);
        return;
    }

    if (player->IsInCombat())
    {
        //if player in combat
        _creature->MonsterSay(MSG_INCOMBAT, LANG_UNIVERSAL, player);
        return;
    }

    float x, y, z;
    uint32 map;

    if (getGuildHouseCoords(player->GetGuildId(), x, y, z, map))
    {
        //teleport player to the specified location
        player->TeleportTo(map, x, y, z, 0.0f);
    }
    else
        _creature->MonsterWhisper(MSG_NOGUILDHOUSE, player, false);

}

bool showBuyList(Player *player, Creature *_creature, uint32 showFromId = 0)
{
    //show not occupied guildhalls

    QueryResult *result;
    result = SD2Database.PQuery("SELECT `id`, `comment` FROM `guildhalls` WHERE `guildId` = 0 AND `id` > %u ORDER BY `id` ASC LIMIT %u", showFromId, GOSSIP_COUNT_MAX);

    if (result)
    {
        uint32 guildhouseId = 0;
        std::string comment = "";
        do {

            Field *fields = result->Fetch();

            guildhouseId = fields[0].GetInt32();
            comment = fields[1].GetString();

            //send comment as a gossip item
            //transmit guildhouseId in Action variable
            player->ADD_GOSSIP_ITEM(ICON_GOSSIP_TABARD, comment, GOSSIP_SENDER_MAIN,
                guildhouseId + OFFSET_GH_ID_TO_ACTION);

        } while (result->NextRow());

        if (result->GetRowCount() == GOSSIP_COUNT_MAX)
        {
            //assume that we have additional page
            //add link to next GOSSIP_COUNT_MAX items
            player->ADD_GOSSIP_ITEM(ICON_GOSSIP_BALOONDOTS, MSG_GOSSIP_NEXTPAGE, GOSSIP_SENDER_MAIN,
                guildhouseId + OFFSET_SHOWBUY_FROM);
        }

        delete result;

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetObjectGuid());

        return true;
    }
    else
    {
        if (showFromId = 0)
        {
            //all guildhalls are occupied
            _creature->MonsterWhisper(MSG_NOFREEGH, player, false);
            player->CLOSE_GOSSIP_MENU();
        }
        else
        {
            //this condition occurs when COUNT(guildhalls) % GOSSIP_COUNT_MAX == 0
            //just show GHs from beginning
            showBuyList(player, _creature, 0);
        }
    }
    return false;
}

bool isPlayerHasGuildhouse(Player *player, Creature *_creature, bool whisper = false)
{

    QueryResult *result;

    result = SD2Database.PQuery("SELECT `comment` FROM `guildhalls` WHERE `guildId` = %u", player->GetGuildId());

    if (result)
    {
        if (whisper)
        {
            //whisper to player "already have etc..."
            Field *fields = result->Fetch();
            char msg[100];
            sprintf(msg, MSG_ALREADYHAVEGH, fields[0].GetString());
            _creature->MonsterWhisper(msg, player, false);
        }
        delete result;
        return true;
    }
    return false;
}

void buyGuildhouse(Player *player, Creature *_creature, uint32 guildhouseId)
{
    if (player->GetMoney() < COST_GH_BUY)
    {
        //show how much money player need to buy GH (in gold)
        char msg[100];
        sprintf(msg, MSG_NOTENOUGHMONEY, COST_GH_BUY / 10000);
        _creature->MonsterWhisper(msg, player, false);
        return;
    }

    if (isPlayerHasGuildhouse(player, _creature, true))
    {
        //show how much money player need to buy GH (in gold)
        char msg[100];
        sprintf(msg, MSG_HASGUILDHOUSE);
        _creature->MonsterWhisper(msg, player, false);
        return;
    }

    QueryResult *result;

    //check if somebody already occupied this GH
    result = SD2Database.PQuery("SELECT `id` FROM `guildhalls` WHERE `id` = %u AND `guildId` <> 0", guildhouseId);

    if (result)
    {
        delete result;
        _creature->MonsterWhisper(MSG_GHOCCUPIED, player, false);
        return;
    }

    //update DB
    result = SD2Database.PQuery("UPDATE `guildhalls` SET `guildId` = %u WHERE `id` = %u", player->GetGuildId(), guildhouseId);

    if (result)
        delete result;

    player->ModifyMoney(-COST_GH_BUY);
    _creature->MonsterSay(MSG_CONGRATULATIONS, LANG_UNIVERSAL, player);

}

void sellGuildhouse(Player *player, Creature *_creature)
{
    if (isPlayerHasGuildhouse(player, _creature))
    {
        QueryResult *result;

        result = SD2Database.PQuery("UPDATE `guildhalls` SET `guildId` = 0 WHERE `guildId` = %u", player->GetGuildId());

        if (result)
            delete result;

        player->ModifyMoney(COST_GH_SELL);

        //display message e.g. "here your money etc."
        char msg[100];
        sprintf(msg, MSG_SOLD, COST_GH_SELL / 10000);
        _creature->MonsterWhisper(msg, player, false);
    }
}

bool GossipHello_custom_npc_guildmaster(Player *player, Creature *_creature)
{
    player->ADD_GOSSIP_ITEM(ICON_GOSSIP_BALOON, MSG_GOSSIP_TELE, GOSSIP_SENDER_MAIN, ACTION_TELE);

    if (isPlayerGuildLeader(player))
    {
        //show additional menu for guild leader
        player->ADD_GOSSIP_ITEM(ICON_GOSSIP_GOLD, MSG_GOSSIP_BUY, GOSSIP_SENDER_MAIN, ACTION_SHOW_BUYLIST);
        if (isPlayerHasGuildhouse(player, _creature))
        {
            //and additional for guildhouse owner
            player->PlayerTalkClass->GetGossipMenu().AddMenuItem(ICON_GOSSIP_GOLD, MSG_GOSSIP_SELL, GOSSIP_SENDER_MAIN, ACTION_SELL_GUILDHOUSE, 0, true);
        }
    }
    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, _creature->GetObjectGuid());
    return true;
}

bool GossipSelect_custom_npc_guildmaster(Player *player, Creature *_creature, uint32 sender, uint32 action )
{
    if (sender != GOSSIP_SENDER_MAIN)
        return false;

    switch (action)
    {
        case ACTION_TELE:
        {
            //teleport player to GH
            player->CLOSE_GOSSIP_MENU();
            teleportPlayerToGuildHouse(player, _creature);
            break;
        }
        case ACTION_SHOW_BUYLIST:
        {
            //show list of GHs which currently not occupied
            showBuyList(player, _creature);
            break;
        }
        case ACTION_SELL_GUILDHOUSE:
        {
            sellGuildhouse(player, _creature);
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        default:
        {
            if (action > OFFSET_SHOWBUY_FROM)
            {
                showBuyList(player, _creature, action - OFFSET_SHOWBUY_FROM);
            }
            else if (action > OFFSET_GH_ID_TO_ACTION)
            {
                //player clicked on buy list
                player->CLOSE_GOSSIP_MENU();
                //get guildhouseId from action
                //guildhouseId = action - OFFSET_GH_ID_TO_ACTION
                buyGuildhouse(player, _creature, action - OFFSET_GH_ID_TO_ACTION);
            }
            break;
        }
    }
    return true;
}

//custom news

#define MSG_N1		"Welcome to World of WarCraft 3.3.5!"

bool GossipHello_custom_npc_news(Player* pPlayer, Creature* pCreature)
{

    // Top Menu News & Updates
    pPlayer->ADD_GOSSIP_ITEM( 3, "Realm News & Updates"     , GOSSIP_SENDER_MAIN, 1000);
    // Close Menu
    pPlayer->ADD_GOSSIP_ITEM( 0, "No Thanks"                , GOSSIP_SENDER_MAIN, 10000);

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());

    return true;
}

void SendDefaultMenu_custom_npc_news(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (pPlayer->isInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay(MSG_COMBAT, LANG_UNIVERSAL, NULL);
        return;
    }

    switch(uiAction)
    {
        case 1000: // News & Updates submenu
            pPlayer->ADD_GOSSIP_ITEM( 3, "20th July 2010"   , GOSSIP_SENDER_MAIN, 1001);
            pPlayer->ADD_GOSSIP_ITEM( 3, "No Thanks"        , GOSSIP_SENDER_MAIN, 10000);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 1001: // Actual News
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay(MSG_N1, LANG_UNIVERSAL, NULL);
        break;

        case 10000: //Close Menu
            pPlayer->CLOSE_GOSSIP_MENU();
        break;


    }
}

bool GossipSelect_custom_npc_news(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_news(pPlayer, pCreature, uiAction);

    return true;
}

// profession master
bool GossipHello_custom_npc_professionmaster(Player* pPlayer, Creature* pCreature)
{
    Config SD2Config;
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file");

    bool ProfessionsEnabled = SD2Config.GetBoolDefault("ProfessionMaster.ProfessionsEnabled", true);
    bool SecondarySkillsEnabled = SD2Config.GetBoolDefault("ProfessionMaster.SecondarySkillsEnabled", true);

    if (pPlayer->GetTeam() == ALLIANCE)
    {
        if(ProfessionsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Professions ->"        , GOSSIP_SENDER_MAIN, 1000);
        if(SecondarySkillsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Secondary Skills ->"   , GOSSIP_SENDER_MAIN, 2000);
    }
    else
    {
        if(ProfessionsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Professions ->"        , GOSSIP_SENDER_MAIN, 1000);
        if(SecondarySkillsEnabled)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Secondary Skills ->"   , GOSSIP_SENDER_MAIN, 2000);
    }

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());

    return true;
}

void SendDefaultMenu_custom_npc_professionmaster(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

    //Combat Check
    if (pPlayer->isInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("You are in combat!", LANG_UNIVERSAL, NULL);
        return;
    }

    Config SD2Config;
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file");

    //Money Check
    if (pPlayer->GetMoney() < (SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)))
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterWhisper("You don't have enough money.", pPlayer, false);
        return;
    }

    bool ProfessionsEnabled = SD2Config.GetBoolDefault("ProfessionMaster.ProfessionsEnabled", true);
    bool SecondarySkillsEnabled = SD2Config.GetBoolDefault("ProfessionMaster.SecondarySkillsEnabled", true);

    switch(uiAction)
    {
        case 1000: //Profession
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Alchemy."              , GOSSIP_SENDER_MAIN, 1001);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Blacksmithing."        , GOSSIP_SENDER_MAIN, 1002);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Enchanting."           , GOSSIP_SENDER_MAIN, 1003);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Engineering."          , GOSSIP_SENDER_MAIN, 1004);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Herbalism."            , GOSSIP_SENDER_MAIN, 1005);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Inscription."          , GOSSIP_SENDER_MAIN, 1006);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Jewelcrafting."        , GOSSIP_SENDER_MAIN, 1007);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Leatherworking."       , GOSSIP_SENDER_MAIN, 1008);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Mining."               , GOSSIP_SENDER_MAIN, 1009);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Skinning."             , GOSSIP_SENDER_MAIN, 1010);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Tailoring."            , GOSSIP_SENDER_MAIN, 1011);
                    pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"          , GOSSIP_SENDER_MAIN, 3000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 2000: //Secondary Skills
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Cooking."              , GOSSIP_SENDER_MAIN, 2001);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "First Aid."            , GOSSIP_SENDER_MAIN, 2002);
                    pPlayer->ADD_GOSSIP_ITEM( 5, "Fishing."              , GOSSIP_SENDER_MAIN, 2003);
                  //pPlayer->ADD_GOSSIP_ITEM( 5, "Riding."               , GOSSIP_SENDER_MAIN, 2004);
                  //pPlayer->ADD_GOSSIP_ITEM( 5, "Archaeology."          , GOSSIP_SENDER_MAIN, 2005);
                    pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"          , GOSSIP_SENDER_MAIN, 3000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3000:

            if (pPlayer->GetTeam() == ALLIANCE)
            {
                if(ProfessionsEnabled)
                pPlayer->ADD_GOSSIP_ITEM( 7, "Professions ->"        , GOSSIP_SENDER_MAIN, 1000);
                if(SecondarySkillsEnabled)
                pPlayer->ADD_GOSSIP_ITEM( 7, "Secondary Skills ->"   , GOSSIP_SENDER_MAIN, 2000);
            }
            else
            {
                if(ProfessionsEnabled)
                pPlayer->ADD_GOSSIP_ITEM( 7, "Professions ->"        , GOSSIP_SENDER_MAIN, 1000);
                if(SecondarySkillsEnabled)
                pPlayer->ADD_GOSSIP_ITEM( 7, "Secondary Skills ->"   , GOSSIP_SENDER_MAIN, 2000);
            }

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;


        case 1001: // Alchemy
            if(!pPlayer->UpdateSkill(171,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(171,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1002: // Blacksmithing
            if(!pPlayer->UpdateSkill(164,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(164,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1003: // Enchanting
            if(!pPlayer->UpdateSkill(333,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(333,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1004: // Engineering
            if(!pPlayer->UpdateSkill(202,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(202,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1005: // Herbalism
            if(!pPlayer->UpdateSkill(182,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(182,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1006: // Inscription
            if(!pPlayer->UpdateSkill(773,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(773,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1007: // Jewelcrafting
            if(!pPlayer->UpdateSkill(755,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(755,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1008: // Leatherworking
            if(!pPlayer->UpdateSkill(165,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(165,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1009: // Mining
            if(!pPlayer->UpdateSkill(186,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(186,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1010: // Skinning
            if(!pPlayer->UpdateSkill(393,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(393,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 1011: // Tailoring
            if(!pPlayer->UpdateSkill(197,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(197,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        //////////////////////////////////////////////////Secondary Skills///////////////////////////////////////////////////////////////

        case 2001: // Cooking
            if(!pPlayer->UpdateSkill(185,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(185,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 2002: // First Aid
            if(!pPlayer->UpdateSkill(129,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(129,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 2003: // Fishing
            if(!pPlayer->UpdateSkill(356,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(356,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        case 2005: // Archaeology
            if(!pPlayer->UpdateSkill(794,0))
            {
                pCreature->MonsterWhisper("You don't have this skill or you allready have the maximum skill value $C.", pPlayer, false);
                GossipHello_custom_npc_professionmaster(pPlayer, pCreature);
                return;
            }
            else
            {
            pPlayer->UpdateSkill(794,(SD2Config.GetFloatDefault("ProfessionMaster.AddSkillPoints",0)));
            pPlayer->ModifyMoney(-(SD2Config.GetFloatDefault("ProfessionMaster.SkillPointCost",0)));
            pPlayer->CLOSE_GOSSIP_MENU();
            }
        break;

        pPlayer->CLOSE_GOSSIP_MENU();
    }
}

bool GossipSelect_custom_npc_professionmaster(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Main menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_professionmaster(pPlayer, pCreature, uiAction);

    return true;
}

//rename npc
bool GossipHello_custom_npc_renamecharacter(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(0, "Do you want to rename your character ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(0, "You're not interested.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->SEND_GOSSIP_MENU(907,pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_custom_npc_renamecharacter(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pCreature->MonsterWhisper("You will be allowed to change your name at next relogin.", pPlayer, false);
        pPlayer->SetAtLoginFlag(AT_LOGIN_RENAME);
        SD2Database.PExecute("UPDATE characters.characters SET at_login = at_login | '1' WHERE guid = '%u'", pPlayer->GetGUIDLow());
        pPlayer->CLOSE_GOSSIP_MENU();
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pCreature->MonsterWhisper("Mh ok. See you around!", pPlayer, false);
        pPlayer->CLOSE_GOSSIP_MENU();
    }

    return true;
}

//reset instance npc
bool GossipHello_custom_npc_resetinstance(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(0, "Do you want to reset all instances ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(0, "You're not interested.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->PlayerTalkClass->SendGossipMenu(907,pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_custom_npc_resetinstance(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    /*if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        QueryResult *result = CharacterDatabase.Query("SELECT map FROM character_instance;");
		QueryResult *raw_count = CharacterDatabase.Query("SELECT count(map) FROM character_instance;");
		uint8 count = (*raw_count)[0].GetUInt8();
        for(int i = 0; i <= count; ++i)
        {
            uint32 mapid = (*result)[i].GetUInt8();
			MapEntry const *mapEntry = sMapStore.LookupEntry(mapid);
            if (!mapEntry->Instanceable())
                return false;

            for(InstanceSaveHashMap::iterator itr = m_instanceSaveById.begin(); itr != m_instanceSaveById.end();)
            {
                if (itr->second->GetMapId() == mapid)
                    _ResetSave(itr);
                else
                    ++itr;
            }
            CharacterDatabase.BeginTransaction();
            CharacterDatabase.PExecute("DELETE FROM character_instance USING character_instance LEFT JOIN instance ON character_instance.instance = id WHERE map = '%u'", mapid);
            CharacterDatabase.PExecute("DELETE FROM group_instance USING group_instance LEFT JOIN instance ON group_instance.instance = id WHERE map = '%u'", mapid);
            CharacterDatabase.PExecute("DELETE FROM instance WHERE map = '%u'", mapid);
            CharacterDatabase.CommitTransaction();

            Map const *map = sMapMgr.FindMap(mapid);
            MapInstanced::InstancedMaps &instMaps = ((MapInstanced*)map)->GetInstancedMaps();
            MapInstanced::InstancedMaps::iterator mitr;
            for(mitr = instMaps.begin(); mitr != instMaps.end(); ++mitr)
            {
                Map *map2 = mitr->second;
                if (!map2->IsDungeon())
                    continue;

               ((InstanceMap*)map2)->Reset(INSTANCE_RESET_GLOBAL);
            }
        }
        return false;
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pCreature->MonsterWhisper("Ok, cya!", pPlayer, false);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    */
    return true;
}

// reset level
bool GossipHello_custom_npc_resetlevel(Player* pPlayer, Creature* pCreature)
{
    Config SD2Config;
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file");

    pPlayer->ADD_GOSSIP_ITEM(0, "Do you want to reset your character ?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(0, "You're not interested.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->PlayerTalkClass->SendGossipMenu(907,pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_custom_npc_resetlevel(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    Config SD2Config;
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file");

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        if (pPlayer->getLevel() == (SD2Config.GetFloatDefault("ResetMaster.ResetMinimumLevel",0)))
        {
            Config SD2Config;
            if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
                error_log("SD2: Unable to open configuration file");

            pCreature->MonsterWhisper("You have been reset!", pPlayer, false);
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->ModifyMoney(+(SD2Config.GetFloatDefault("ResetMaster.ResetAddMoney",0)));
            pPlayer->SetLevel((SD2Config.GetFloatDefault("ResetMaster.LevelAfterReset",0)));
        }
        else
        {
            pCreature->MonsterWhisper("Your level is too low or too high to reset!", pPlayer, false);
            pPlayer->CLOSE_GOSSIP_MENU();
        }
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pCreature->MonsterWhisper("Mh ok. See you around!", pPlayer, false);
        pPlayer->CLOSE_GOSSIP_MENU();
    }

    return true;
}

//spell master
#define MSG_LEARNED_SPELL           "Congratulations, you've learned all of your class spells!"
#define MSG_LEARNED_WEAPON          "Congratulations, you've learned all your class weapon skills!"
#define MSG_LEARNED_LANGUAGES       "Congratulations, you've learned all languages!"
#define MSG_MAXED_WEAPON            "Congratulations, you've maxed out your weapon skills!"
#define MSG_MAXED_LANGUAGES         "Congratulations, you've maxed out all languages!"
#define MSG_MAXED_RIDING            "Congratulations, you've maxed out your riding skills!"
#define CLASS_WARRIOR               1
#define CLASS_PALADIN               2
#define CLASS_HUNTER                3
#define CLASS_ROGUE                 4
#define CLASS_PRIEST                5
#define CLASS_DEATHKNIGHT           6
#define CLASS_SHAMAN                7
#define CLASS_MAGE                  8
#define CLASS_WARLOCK               9
#define CLASS_DRUID                 11


bool GossipHello_custom_npc_spellmaster(Player* pPlayer, Creature* pCreature)
{
    Config SD2Config;
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file");

    bool LearnAllWeapons            = SD2Config.GetBoolDefault("Spellmaster.LearnAllWeapons", true);
    bool LearnAllLanguages          = SD2Config.GetBoolDefault("Spellmaster.LearnAllLanguages", true);
    bool MaxOutWeaponSkills         = SD2Config.GetBoolDefault("Spellmaster.MaxOutWeaponSkills", true);
    bool MaxOutRidingSkills         = SD2Config.GetBoolDefault("Spellmaster.MaxOutRidingSkills", true);
    bool MaxOutLanguageSkills       = SD2Config.GetBoolDefault("Spellmaster.MaxOutAllLanguageSkills", true);

    if(pPlayer->getLevel() > (SD2Config.GetFloatDefault("SpellMaster.MinimumLevel",0)))
    {
        // Warrior Spells
        if(pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Warrior spells"            , GOSSIP_SENDER_MAIN, 1000);
        // Paladin Spells
        if(pPlayer->getClass() == CLASS_PALADIN)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Paladin spells"            , GOSSIP_SENDER_MAIN, 2000);
        // Hunter Spells
        if(pPlayer->getClass() == CLASS_HUNTER)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Hunter spells"            , GOSSIP_SENDER_MAIN, 3000);
        // Rogue Spells
        if(pPlayer->getClass() == CLASS_ROGUE)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Rogue spells"            , GOSSIP_SENDER_MAIN, 4000);
        // Priest Spells
        if(pPlayer->getClass() == CLASS_PRIEST)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Priest spells"            , GOSSIP_SENDER_MAIN, 5000);
        // Death Knight Spells
        if(pPlayer->getClass() == CLASS_DEATHKNIGHT)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Death Knight spells"    , GOSSIP_SENDER_MAIN, 6000);
        // Shaman Spells
        if(pPlayer->getClass() == CLASS_SHAMAN)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Shaman spells"            , GOSSIP_SENDER_MAIN, 7000);
        // Mage Spells
        if(pPlayer->getClass() == CLASS_MAGE)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Mage spells"            , GOSSIP_SENDER_MAIN, 8000);
        // Warlock Spells
        if(pPlayer->getClass() == CLASS_WARLOCK)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Warlock spells"            , GOSSIP_SENDER_MAIN, 9000);
        // Druid Spells
        if(pPlayer->getClass() == CLASS_DRUID)
            pPlayer->ADD_GOSSIP_ITEM( 3, "Learn all Druid spells"            , GOSSIP_SENDER_MAIN, 10000);
        // Weapon Skills
        if(LearnAllWeapons)
            pPlayer->ADD_GOSSIP_ITEM( 9, "Learn my class weapon skills"        , GOSSIP_SENDER_MAIN, 11000);
        // Max out all weapon skills
        if(MaxOutWeaponSkills)
            pPlayer->ADD_GOSSIP_ITEM( 9, "Max out weapon skills"            , GOSSIP_SENDER_MAIN, 12000);
        // Max out all riding skills
        if(MaxOutRidingSkills)
            pPlayer->ADD_GOSSIP_ITEM( 2, "Max out riding skills"            , GOSSIP_SENDER_MAIN, 13000);
        // Learn all languages
        if(LearnAllLanguages)
            pPlayer->ADD_GOSSIP_ITEM( 0, "Learn all languages"                , GOSSIP_SENDER_MAIN, 14000);
        // Max out all languages
        if(MaxOutLanguageSkills)
            pPlayer->ADD_GOSSIP_ITEM( 7, "Max out language skills"            , GOSSIP_SENDER_MAIN, 15000);

        pPlayer->ADD_GOSSIP_ITEM( 0, "Not Interested"                    , GOSSIP_SENDER_MAIN, 99000);
    }
    else
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterWhisper("You need more levels to learn the spells!", pPlayer, false);
    }

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
    return true;
}

void SendDefaultMenu_custom_npc_spellmaster(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

    // Not allow in combat
    if (pPlayer->isInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay(MSG_COMBAT, LANG_UNIVERSAL, NULL);
        return;
    }

    switch(uiAction)
    {
        case 1000: //Warrior Spells
            pPlayer->learnSpell(47436, false);      // Battle Shout  [Rank 9]
            pPlayer->learnSpell(18499, false);      // Beserker Rage
            pPlayer->learnSpell(2458, false);       // Beserker Stance
            pPlayer->learnSpell(2687, false);       // Bloodrage
            pPlayer->learnSpell(1161, false);       // Challenging Shout
            pPlayer->learnSpell(11578, false);      // Charge [Rank 3]
            pPlayer->learnSpell(47520, false);      // Cleave [Rank 8]
            pPlayer->learnSpell(469, false);        // Commanding Shout [Rank 1]
            pPlayer->learnSpell(47439, false);      // Commanding Shout [Rank 2]
            pPlayer->learnSpell(47440, false);      // Commanding Shout [Rank 3]
            pPlayer->learnSpell(71, false);         // Defensive Stance
            pPlayer->learnSpell(47437, false);      // Demoralizing Shout [Rank 8]
            pPlayer->learnSpell(676, false);        // Disarm
            pPlayer->learnSpell(55694, false);      // Enraged Regeneration
            pPlayer->learnSpell(47471, false);      // Execute [Rank 9]
            pPlayer->learnSpell(1715, false);       // Hamstring
            pPlayer->learnSpell(47450, false);      // Heroic Strike [Rank 13]
            pPlayer->learnSpell(57755, false);      // Heroic Throw
            pPlayer->learnSpell(20252, false);      // Intercept
            pPlayer->learnSpell(3411, false);       // Intervene
            pPlayer->learnSpell(5246, false);       // Intimidating Shout
            pPlayer->learnSpell(694, false);        // Mocking Blow
            pPlayer->learnSpell(7384, false);       // Overpower
            pPlayer->learnSpell(6552, false);       // Pummel
            pPlayer->learnSpell(1719, false);       // Recklessness
            pPlayer->learnSpell(47471, false);      // Rend [Rank 10]
            pPlayer->learnSpell(20230, false);      // Retaliation
            pPlayer->learnSpell(57823, false);      // Revenge  [Rank 9]
            pPlayer->learnSpell(64382, false);      // Shattering Throw
            pPlayer->learnSpell(72, false);         // Shield Bash
            pPlayer->learnSpell(2565, false);       // Shield Block
            pPlayer->learnSpell(47488, false);      // Shield Slam [Rank 8]
            pPlayer->learnSpell(871, false);        // Shield Wall
            pPlayer->learnSpell(47475, false);      // Slam [Rank 8]
            pPlayer->learnSpell(23920, false);      // Spell Reflection
            pPlayer->learnSpell(12678, false);      // Stance Mastery
            pPlayer->learnSpell(7386, false);       // Sunder Armor
            pPlayer->learnSpell(355, false);        // Taunt
            pPlayer->learnSpell(47502, false);      // Thunder Clap [Rank 9]
            pPlayer->learnSpell(34428, false);      // Victory Rush
            pPlayer->learnSpell(1680, false);       // Whirlwind
            pPlayer->learnSpell(750, false);        // Plate Mail

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 2000: //Paladin Spells
            pPlayer->learnSpell(31884, false);      // Avenging Wrath
            pPlayer->learnSpell(20217, false);      // Blessing of Kings
            pPlayer->learnSpell(48932, false);      // Blessing of Might [Rank 10]
            pPlayer->learnSpell(48936, false);      // Blessing of Wisdom [Rank 9]
            pPlayer->learnSpell(4987, false);       // Cleanse
            pPlayer->learnSpell(19746, false);      // Concentration Aura
            pPlayer->learnSpell(48810, false);      // Consecration [Rank 8]
            pPlayer->learnSpell(32223, false);      // Crusader Aura
            pPlayer->learnSpell(48942, false);      // Devotion Aura [Rank 10]
            pPlayer->learnSpell(19752, false);      // Divine Intervention
            pPlayer->learnSpell(54428, false);      // Divine Plea
            pPlayer->learnSpell(498, false);        // Divine Protection
            pPlayer->learnSpell(642, false);        // Divine Shield
            pPlayer->learnSpell(48801, false);      // Exorcism [Rank 9]
            pPlayer->learnSpell(48947, false);      // Fire Resistance Aura [Rank 5]
            pPlayer->learnSpell(48785, false);      // Flash of Light [Rank 9]
            pPlayer->learnSpell(48945, false);      // Frost Resistance Aura [Rank 5]
            pPlayer->learnSpell(25898, false);      // Greater Blessing of Kings
            pPlayer->learnSpell(48934, false);      // Greater Blessing of Might [Rank 5]
            pPlayer->learnSpell(25899, false);      // Greater Blessing of Sanctuary
            pPlayer->learnSpell(48938, false);      // Greater Blessing of Wisdom [Rank 5]
            pPlayer->learnSpell(48806, false);      // Hammer of Wrath [Rank 6]
            pPlayer->learnSpell(1044, false);       // Hand of Freedom
            pPlayer->learnSpell(10278, false);      // Hand of Protection [Rank 3]
            pPlayer->learnSpell(62124, false);      // Hand of Reckoning
            pPlayer->learnSpell(6940, false);       // Hand of Sacrifice
            pPlayer->learnSpell(1038, false);       // Hand of Salvation
            pPlayer->learnSpell(48782, false);      // Holy Light [Rank 13]
            pPlayer->learnSpell(48817, false);      // Holy Wrath [Rank 5]
            pPlayer->learnSpell(53407, false);      // Judgement of Justice
            pPlayer->learnSpell(20271, false);      // Judgement of Light
            pPlayer->learnSpell(53408, false);      // Judgement of Wisdom
            pPlayer->learnSpell(48788, false);      // Lay on Hands [Rank 5]
            pPlayer->learnSpell(48950, false);      // Redemption [Rank 7]
            pPlayer->learnSpell(54043, false);      // Retribution Aura [Rank 7]
            pPlayer->learnSpell(31789, false);      // Righteous Defense
            pPlayer->learnSpell(25780, false);      // Righteous Fury
            pPlayer->learnSpell(53601, false);      // Sacred Shield [Rank 1]
            pPlayer->learnSpell(20164, false);      // Seal of Justice
            pPlayer->learnSpell(20165, false);      // Seal of Light
            pPlayer->learnSpell(21084, false);      // Seal of Righteousness
            pPlayer->learnSpell(20166, false);      // Seal of Wisdom
            pPlayer->learnSpell(48943, false);      // Shadow Resistance Aura [Rank 5]
            pPlayer->learnSpell(5502, false);       // Sense Undead
            pPlayer->learnSpell(10326, false);      // Turn Evil
            if(pPlayer->getRace() == 10)
            pPlayer->learnSpell(34769, false);      // Summon Warhorse Horde
            else if(pPlayer->getRace() == 1 || 3 || 11)
            pPlayer->learnSpell(13819, false);      // Summon Warhorse Alliance
            if(pPlayer->getRace() == 10)
            pPlayer->learnSpell(2825, false);       // Seal of Corruption
            else if(pPlayer->getRace() == 1 || 3 || 11)
            pPlayer->learnSpell(32182, false);      // Seal of Vengeance
            if(pPlayer->getRace() == 10)
            pPlayer->learnSpell(34767, false);      // Summon Charger Horde
            else if(pPlayer->getRace() == 1 || 3 || 11)
            pPlayer->learnSpell(23214, false);      // Summon Charger Alliance
            pPlayer->learnSpell(750, false);        // Plate Mail

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 3000: //Hunter Spells
            pPlayer->learnSpell(49045, false);      // Arcane Shot [Rank 11]
            pPlayer->learnSpell(13161, false);      // Aspect of the Beast
            pPlayer->learnSpell(5118, false);       // Aspect of the Cheetah
            pPlayer->learnSpell(61847, false);      // Aspect of the Dragonhawk [Rank 2]
            pPlayer->learnSpell(27044, false);      // Aspect of the Hawk [Rank 8]
            pPlayer->learnSpell(13163, false);      // Aspect of the Monkey
            pPlayer->learnSpell(13159, false);      // Aspect of the Pack
            pPlayer->learnSpell(34074, false);      // Aspect of the Viper
            pPlayer->learnSpell(49071, false);      // Aspect of the Wild [Rank 4]
            pPlayer->learnSpell(1462, false);       // Beast Lore
            pPlayer->learnSpell(883, false);        // Call Pet
            pPlayer->learnSpell(62757, false);      // Call Stabled Pet
            pPlayer->learnSpell(5116, false);       // Concussive Shot
            pPlayer->learnSpell(19263, false);      // Deterrence
            pPlayer->learnSpell(781, false);        // Disengage
            pPlayer->learnSpell(2641, false);       // Dismiss Pet
            pPlayer->learnSpell(20736, false);      // Distracting Shot [Rank 1]
            pPlayer->learnSpell(6197, false);       // Eagle Eye
            pPlayer->learnSpell(49067, false);      // Explosive Trap [Rank 6]
            pPlayer->learnSpell(1002, false);       // Eyes of the Beast
            pPlayer->learnSpell(6991, false);       // Feed Pet
            pPlayer->learnSpell(5384, false);       // Feign Death
            pPlayer->learnSpell(1543, false);       // Flare
            pPlayer->learnSpell(14311, false);      // Freezing Trap [Rank 3]
            pPlayer->learnSpell(13809, false);      // Frost Trap
            pPlayer->learnSpell(53338, false);      // Hunter's Mark [Rank 5]
            pPlayer->learnSpell(49056, false);      // Immolation Trap [Rank 8]
            pPlayer->learnSpell(34026, false);      // Kill Command
            pPlayer->learnSpell(61006, false);      // Kill Shot [Rank 3]
            pPlayer->learnSpell(53271, false);      // Master's Call
            pPlayer->learnSpell(48990, false);      // Mend Pet [Rank 10]
            pPlayer->learnSpell(34477, false);      // Misdirection
            pPlayer->learnSpell(53339, false);      // Mongoose Bite [Rank 6]
            pPlayer->learnSpell(49048, false);      // Multi-Shot [Rank 8]
            pPlayer->learnSpell(3045, false);       // Rapid Fire
            pPlayer->learnSpell(48996, false);      // Raptor Strike [Rank 11]
            pPlayer->learnSpell(982, false);        // Revive Pet
            pPlayer->learnSpell(14327, false);      // Scare Beast [Rank 3]
            pPlayer->learnSpell(3043, false);       // Scorpid Sting
            pPlayer->learnSpell(49001, false);      // Serpent Sting [Rank 12]
            pPlayer->learnSpell(34600, false);      // Snake Trap
            pPlayer->learnSpell(49052, false);      // Steady Shot [Rank 4]
            pPlayer->learnSpell(1515, false);       // Tame Beast
            pPlayer->learnSpell(19801, false);      // Tranquilizing Shot
            pPlayer->learnSpell(3034, false);       // Viper Sting
            pPlayer->learnSpell(58434, false);      // Volley [Rank 6]
            pPlayer->learnSpell(2974, false);       // Wing Clip
            pPlayer->learnSpell(1494, false);       // Track Beasts
            pPlayer->learnSpell(19878, false);      // Track Demons
            pPlayer->learnSpell(19879, false);      // Track Dragonkin
            pPlayer->learnSpell(19880, false);      // Track Elementals
            pPlayer->learnSpell(19882, false);      // Track Giants
            pPlayer->learnSpell(19885, false);      // Track Hidden
            pPlayer->learnSpell(19883, false);      // Track Humanoids
            pPlayer->learnSpell(19884, false);      // Track Undead
            pPlayer->learnSpell(8737, false);       // Mail

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 4000: // Rogue Spells
            pPlayer->learnSpell(48691, false);      // Ambush [Rank 10]
            pPlayer->learnSpell(48657, false);      // Backstab [Rank 12]
            pPlayer->learnSpell(2094, false);       // Blind
            pPlayer->learnSpell(1833, false);       // Cheap Shot
            pPlayer->learnSpell(31224, false);      // Cloak of Shadows
            pPlayer->learnSpell(48674, false);      // Deadly Throw [Rank 3]
            pPlayer->learnSpell(2836, false);       // Detect Traps
            pPlayer->learnSpell(1842, false);       // Disarm Trap
            pPlayer->learnSpell(51722, false);      // Dismantle
            pPlayer->learnSpell(1725, false);       // Distract
            pPlayer->learnSpell(57993, false);      // Envenom [Rank 4]
            pPlayer->learnSpell(26669, false);      // Evasion [Rank 2]
            pPlayer->learnSpell(48668, false);      // Eviscerate [Rank 12]
            pPlayer->learnSpell(8647, false);       // Expose Armor
            pPlayer->learnSpell(51723, false);      // Fan of Knives
            pPlayer->learnSpell(48659, false);      // Feint [Rank 8]
            pPlayer->learnSpell(48676, false);      // Garrote [Rank 10]
            pPlayer->learnSpell(1776, false);       // Gouge
            pPlayer->learnSpell(1766, false);       // Kick
            pPlayer->learnSpell(8643, false);       // Kidney Shot [Rank 2]
            pPlayer->learnSpell(1804, false);       // Pick Lock
            pPlayer->learnSpell(921, false);        // Pick Pocket
            pPlayer->learnSpell(48672, false);      // Rupture [Rank 9]
            pPlayer->learnSpell(1860, false);       // Safe Fall
            pPlayer->learnSpell(51724, false);      // Sap [Rank 4]
            pPlayer->learnSpell(5938, false);       // Shiv
            pPlayer->learnSpell(48638, false);      // Sinister Strike [Rank 12]
            pPlayer->learnSpell(6774, false);       // Slice and Dice [Rank 2]
            pPlayer->learnSpell(11305, false);      // Sprint [Rank 3]
            pPlayer->learnSpell(1787, false);       // Stealth [Rank 4]
            pPlayer->learnSpell(57934, false);      // Tricks of the Trade
            pPlayer->learnSpell(26889, false);      // Vanish [Rank 3]

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 5000: // Priest Spells
            pPlayer->learnSpell(552, false);        // Abolish Disease
            pPlayer->learnSpell(48120, false);      // Binding Heal [Rank 3]
            pPlayer->learnSpell(528, false);        // Cure Disease
            pPlayer->learnSpell(48300, false);      // Devouring Plague [Rank 9]
            pPlayer->learnSpell(988, false);        // Dispel Magic [Rank 2]
            pPlayer->learnSpell(64843, false);      // Divine Hymn
            pPlayer->learnSpell(48073, false);      // Divine Spirit [Rank 6]
            pPlayer->learnSpell(586, false);        // Fade
            pPlayer->learnSpell(6346, false);       // Fear Ward
            pPlayer->learnSpell(48071, false);      // Flash Heal [Rank 11]
            pPlayer->learnSpell(48063, false);      // Greater Heal [Rank 9]
            pPlayer->learnSpell(6064, false);       // Heal [Rank 4]
            pPlayer->learnSpell(48135, false);      // Holy Fire [Rank 11]
            pPlayer->learnSpell(48078, false);      // Holy Nova [Rank 9]
            pPlayer->learnSpell(64901, false);      // Hymn of Hope
            pPlayer->learnSpell(48168, false);      // Inner Fire [Rank 9]
            pPlayer->learnSpell(2053, false);       // Lesser Heal [Rank 3]
            pPlayer->learnSpell(1706, false);       // Levitate
            pPlayer->learnSpell(8129, false);       // Mana Burn
            pPlayer->learnSpell(32375, false);      // Mass Dispel
            pPlayer->learnSpell(48127, false);      // Mind Blast [Rank 13]
            pPlayer->learnSpell(605, false);        // Mind Control
            pPlayer->learnSpell(53023, false);      // Mind Sear [Rank 2]
            pPlayer->learnSpell(453, false);        // Mind Soothe
            pPlayer->learnSpell(10909, false);      // Mind Vision [Rank 2]
            pPlayer->learnSpell(48161, false);      // Power Word: Fortitude [Rank 8]
            pPlayer->learnSpell(48066, false);      // Power Word: Shield [Rank 14]
            pPlayer->learnSpell(48162, false);      // Prayer of Fortitude [Rank 4]
            pPlayer->learnSpell(48072, false);      // Prayer of Healing [Rank 7]
            pPlayer->learnSpell(48113, false);      // Prayer of Mending [Rank 3]
            pPlayer->learnSpell(48170, false);      // Prayer of Shadow Protection [Rank 3]
            pPlayer->learnSpell(48074, false);      // Prayer of Spirit [Rank 3]
            pPlayer->learnSpell(10890, false);      // Psychic Scream [Rank 4]
            pPlayer->learnSpell(48068, false);      // Renew [Rank 14]
            pPlayer->learnSpell(48171, false);      // Resurrection [Rank 7]
            pPlayer->learnSpell(10955, false);      // Shackle Undead [Rank 3]
            pPlayer->learnSpell(48169, false);      // Shadow Protection [Rank 5]
            pPlayer->learnSpell(48158, false);      // Shadow Word: Death [Rank 4]
            pPlayer->learnSpell(48125, false);      // Shadow Word: Pain [Rank 12]
            pPlayer->learnSpell(34433, false);      // Shadowfiend
            pPlayer->learnSpell(48123, false);      // Smite [Rank 12]

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 6000: // Death Knight Spells
            pPlayer->learnSpell(48778, false);      // Acherus Deathcharger
            pPlayer->learnSpell(48707, false);      // Anti-Magic Shell
            pPlayer->learnSpell(42650, false);      // Army of the Dead
            pPlayer->learnSpell(49941, false);      // Blood Boil [Rank 4]
            pPlayer->learnSpell(49930, false);      // Blood Strike [Rank 6]
            pPlayer->learnSpell(45529, false);      // Blood Tap
            pPlayer->learnSpell(45524, false);      // Chains of Ice
            pPlayer->learnSpell(56222, false);      // Dark Command
            pPlayer->learnSpell(49938, false);      // Death and Decay [Rank 4]
            pPlayer->learnSpell(62904, false);      // Death Coil [Rank 5]
            pPlayer->learnSpell(50977, false);      // Death Gate
            pPlayer->learnSpell(48743, false);      // Death Pact
            pPlayer->learnSpell(49924, false);      // Death Strike [Rank 5]
            pPlayer->learnSpell(47568, false);      // Empower Rune Weapon
            pPlayer->learnSpell(48263, false);      // Frost Presence
            pPlayer->learnSpell(57623, false);      // Horn of Winter [Rank 2]
            pPlayer->learnSpell(48792, false);      // Icebound Fortitude
            pPlayer->learnSpell(49909, false);      // Icy Touch [Rank 5]
            pPlayer->learnSpell(47528, false);      // Mind Freeze
            pPlayer->learnSpell(51425, false);      // Obliterate [Rank 4]
            pPlayer->learnSpell(3714, false);       // Path of Frost
            pPlayer->learnSpell(50842, false);      // Pestilence
            pPlayer->learnSpell(49221, false);      // Plague Strike [Rank 6]
            pPlayer->learnSpell(61999, false);      // Raise Ally
            pPlayer->learnSpell(46584, false);      // Raise Dead
            pPlayer->learnSpell(56815, false);      // Rune Strike
            pPlayer->learnSpell(53428, false);      // Runeforging
            pPlayer->learnSpell(53341, false);      // Rune of Cinderglacier
            pPlayer->learnSpell(53331, false);      // Rune of Lichbane
            pPlayer->learnSpell(53343, false);      // Rune of Razorice
            pPlayer->learnSpell(54447, false);      // Rune of Spellbreaking
            pPlayer->learnSpell(53342, false);      // Rune of Spellshattering
            pPlayer->learnSpell(54446, false);      // Rune of Swordbreaking
            pPlayer->learnSpell(53323, false);      // Rune of Swordshattering
            pPlayer->learnSpell(53344, false);      // Rune of the Fallen Crusader
            pPlayer->learnSpell(62158, false);      // Rune of the Stoneskin Gargoyle
            pPlayer->learnSpell(47476, false);      // Strangulate
            pPlayer->learnSpell(48265, false);      // Unholy Presence

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 7000: // Shaman Spells
            pPlayer->learnSpell(49277, false);      // Ancestral Spirit [Rank 7]
            pPlayer->learnSpell(556, false);        // Astral Recall
            pPlayer->learnSpell(66843, false);      // Call of the Ancestors
            pPlayer->learnSpell(66842, false);      // Call of the Elements
            pPlayer->learnSpell(66844, false);      // Call of the Spirits
            pPlayer->learnSpell(55459, false);      // Chain Heal [Rank 7]
            pPlayer->learnSpell(49271, false);      // Chain Lightning [Rank 8]
            pPlayer->learnSpell(8170, false);       // Cleansing Totem
            pPlayer->learnSpell(526, false);        // Cure Toxins
            pPlayer->learnSpell(2062, false);       // Earth Elemental Totem
            pPlayer->learnSpell(49231, false);      // Earth Shock [Rank 10]
            pPlayer->learnSpell(2484, false);       // Earthbind Totem
            pPlayer->learnSpell(51994, false);      // Earthliving Weapon [Rank 6]
            pPlayer->learnSpell(6196, false);       // Far Sight
            pPlayer->learnSpell(2894, false);       // Fire Elemental Totem
            pPlayer->learnSpell(61657, false);      // Fire Nova Totem [Rank 9]
            pPlayer->learnSpell(58739, false);      // Fire Resistance Totem [Rank 6]
            pPlayer->learnSpell(49233, false);      // Flame Shock [Rank 9]
            pPlayer->learnSpell(58656, false);      // Flametongue Totem [Rank 8]
            pPlayer->learnSpell(58790, false);      // Flametongue Weapon [Rank 10]
            pPlayer->learnSpell(58745, false);      // Frost Resistance Totem [Rank 6]
            pPlayer->learnSpell(49236, false);      // Frost Shock [Rank 7]
            pPlayer->learnSpell(58796, false);      // Frostbrand Weapon [Rank 9]
            pPlayer->learnSpell(2645, false);       // Ghost Wolf
            pPlayer->learnSpell(8177, false);       // Grounding Totem
            pPlayer->learnSpell(58757, false);      // Healing Stream Totem [Rank 9]
            pPlayer->learnSpell(49273, false);      // Healing Wave [Rank 14]
            pPlayer->learnSpell(51514, false);      // Hex
            pPlayer->learnSpell(60043, false);      // Lava Burst [Rank 2]
            pPlayer->learnSpell(49276, false);      // Lesser Healing Wave [Rank 9]
            pPlayer->learnSpell(49238, false);      // Lightning Bolt [Rank 14]
            pPlayer->learnSpell(49281, false);      // Lightning Shield [Rank 11]
            pPlayer->learnSpell(58734, false);      // Magma Totem [Rank 7]
            pPlayer->learnSpell(58774, false);      // Mana Spring Totem [Rank 8]
            pPlayer->learnSpell(58749, false);      // Nature Resistance Totem [Rank 6]
            pPlayer->learnSpell(8012, false);       // Purge [Rank 2]
            pPlayer->learnSpell(20608, false);      // Reincarnation
            pPlayer->learnSpell(10399, false);      // Rockbiter Weapon [Rank 4]
            pPlayer->learnSpell(58704, false);      // Searing Totem [Rank 10]
            pPlayer->learnSpell(6495, false);       // Sentry Totem
            pPlayer->learnSpell(58582, false);      // Stoneclaw Totem [Rank 10]
            pPlayer->learnSpell(58753, false);      // Stoneskin Totem [Rank 10]
            pPlayer->learnSpell(58643, false);      // Strength of Earth Totem [Rank 8]
            pPlayer->learnSpell(36936, false);      // Totemic Recall
            pPlayer->learnSpell(8143, false);       // Tremor Totem
            pPlayer->learnSpell(131, false);        // Water Breathing
            pPlayer->learnSpell(57960, false);      // Water Shield [Rank 9]
            pPlayer->learnSpell(546, false);        // Water Walking
            pPlayer->learnSpell(57994, false);      // Wind Shear
            pPlayer->learnSpell(8512, false);       // Windfury Totem
            pPlayer->learnSpell(58804, false);      // Windfury Weapon [Rank 8]
            if(pPlayer->getRace() == 2 || 6 || 8)
            pPlayer->learnSpell(2825, false);       // Bloodlust
            else if(pPlayer->getRace() == 11)
            pPlayer->learnSpell(32182, false);      // Heroism
            pPlayer->learnSpell(8737, false);       // Mail

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 8000: // Mage Spells
            pPlayer->learnSpell(43017, false);      // Amplify Magic [Rank 7]
            pPlayer->learnSpell(42897, false);      // Arcane Blast [Rank 4]
            pPlayer->learnSpell(43002, false);      // Arcane Brilliance [Rank 3]
            pPlayer->learnSpell(42921, false);      // Arcane Explosion [Rank 10]
            pPlayer->learnSpell(42995, false);      // Arcane Intellect [Rank 7]
            pPlayer->learnSpell(42846, false);      // Arcane Missles [Rank 13]
            pPlayer->learnSpell(1953, false);       // Blink
            pPlayer->learnSpell(42940, false);      // Blizzard [Rank 9]
            pPlayer->learnSpell(42931, false);      // Cone of Cold [Rank 8]
            pPlayer->learnSpell(33717, false);      // Conjure Food [Rank 8]
            pPlayer->learnSpell(42985, false);      // Conjure Mana Gem [Rank 6]
            pPlayer->learnSpell(42956, false);      // Conjure Refreshment [Rank 2]
            pPlayer->learnSpell(27090, false);      // Conjure Water [Rank 9]
            pPlayer->learnSpell(2139, false);       // Counterspell
            pPlayer->learnSpell(61316, false);      // Dalaran Brilliance [Rank 3]
            pPlayer->learnSpell(61024, false);      // Dalaran Intellect [Rank 7]
            pPlayer->learnSpell(43015, false);      // Dampen Magic [Rank 7]
            pPlayer->learnSpell(12051, false);      // Evocation
            pPlayer->learnSpell(42873, false);      // Fire Blast [Rank 11]
            pPlayer->learnSpell(43010, false);      // Fire Ward [Rank 7]
            pPlayer->learnSpell(42833, false);      // Fireball [Rank 16]
            pPlayer->learnSpell(42926, false);      // Flamestrike [Rank 9]
            pPlayer->learnSpell(7301, false);       // Frost Armor [Rank 3]
            pPlayer->learnSpell(42917, false);      // Frost Nova [Rank 6]
            pPlayer->learnSpell(43012, false);      // Frost Ward [Rank 7]
            pPlayer->learnSpell(42842, false);      // Frostbolt [Rank 16]
            pPlayer->learnSpell(47610, false);      // Frostfire Bolt [Rank 2]
            pPlayer->learnSpell(43008, false);      // Ice Armor [Rank 6]
            pPlayer->learnSpell(45438, false);      // Ice Block
            pPlayer->learnSpell(42914, false);      // Ice Lance [Rank 3]
            pPlayer->learnSpell(66, false);         // Invisibility
            pPlayer->learnSpell(43024, false);      // Mage Armor [Rank 6]
            pPlayer->learnSpell(43020, false);      // Mana Shield [Rank 9]
            pPlayer->learnSpell(55342, false);      // Mirror Image
            pPlayer->learnSpell(43046, false);      // Molten Armor [Rank 3]
            pPlayer->learnSpell(12826, false);      // Polymorph [Rank 4]
            pPlayer->learnSpell(61305, false);      // Polymorph: Black Cat
            pPlayer->learnSpell(28272, false);      // Polymorph: Pig
            pPlayer->learnSpell(61721, false);      // Polymorph: Rabbit
            pPlayer->learnSpell(61780, false);      // Polymorph: Turkey
            pPlayer->learnSpell(28271, false);      // Polymorph: Turtle
            pPlayer->learnSpell(53142, false);      // Portal: Dalaran
            if(pPlayer->getRace() == 1 || 3 || 4 || 7 || 11)
                pPlayer->learnSpell(11419, false),  // Portal: Darnassus
                pPlayer->learnSpell(32266, false),  // Portal: Exodar
                pPlayer->learnSpell(11416, false),  // Portal: Ironforge
                pPlayer->learnSpell(33691, false),  // Portal: Shattrath
                pPlayer->learnSpell(11059, false),  // Portal: Stormwind
                pPlayer->learnSpell(49360, false);  // Portal: Theramore
            else if(pPlayer->getRace() == 2 || 5 || 6 || 8 || 10)
                pPlayer->learnSpell(11417, false),  // Portal: Orgrimmar
                pPlayer->learnSpell(35717, false),  // Portal: Shattrath
                pPlayer->learnSpell(32267, false),  // Portal: Silvermoon
                pPlayer->learnSpell(49361, false),  // Portal: Stonard
                pPlayer->learnSpell(11420, false),  // Portal: Thunder Bluff
                pPlayer->learnSpell(11418, false);  // Portal: Undercity
            if(pPlayer->getRace() == 1 || 3 || 4 || 7 || 11)
                pPlayer->learnSpell(3565, false),   // Teleport: Darnassus
                pPlayer->learnSpell(32271, false),  // Teleport: Exodar
                pPlayer->learnSpell(3562, false),   // Teleport: Ironforge
                pPlayer->learnSpell(33690, false),  // Teleport: Shattrath
                pPlayer->learnSpell(3561, false),   // Teleport: Stormwind
                pPlayer->learnSpell(49359, false);  // Teleport: Theramore
            else if(pPlayer->getRace() == 2 || 5 || 6 || 8 || 10)
                pPlayer->learnSpell(3567, false),   // Teleport: Orgrimmar
                pPlayer->learnSpell(35715, false),  // Teleport: Shattrath
                pPlayer->learnSpell(32272, false),  // Teleport: Silvermoon
                pPlayer->learnSpell(49358, false),  // Teleport: Stonard
                pPlayer->learnSpell(3566, false),   // Teleport: Thunder Bluff
                pPlayer->learnSpell(3563, false);   // Teleport: Undercity
            pPlayer->learnSpell(475, false);        // Remove Curse
            pPlayer->learnSpell(58659, false);      // Ritual of Refreshment [Rank 2]
            pPlayer->learnSpell(42859, false);      // Scorch [Rank 11]
            pPlayer->learnSpell(130, false);        // Slow Fall
            pPlayer->learnSpell(30449, false);      // Spellsteal
            pPlayer->learnSpell(53140, false);      // Teleport: Dalaran

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 9000: // Warlock Spells
            pPlayer->learnSpell(60220, false);      // Create Firestone [Rank 7]
            pPlayer->learnSpell(47884, false);      // Create Soulstone [Rank 7]
            pPlayer->learnSpell(47888, false);      // Create Spellstone [Rank 6]
            pPlayer->learnSpell(18647, false);      // Banish [Rank 2]
            pPlayer->learnSpell(47813, false);      // Corruption [Rank 10]
            pPlayer->learnSpell(47878, false);      // Create Healthstone [Rank 8]
            pPlayer->learnSpell(47864, false);      // Curse of Agony [Rank 9]
            pPlayer->learnSpell(11719, false);      // Curse of Tongues [Rank 2]
            pPlayer->learnSpell(47867, false);      // Curse of Doom [Rank 3]
            pPlayer->learnSpell(50511, false);      // Curse of Weakness [Rank 9]
            pPlayer->learnSpell(47865, false);      // Curse of the Elements [Rank 5]
            pPlayer->learnSpell(47860, false);      // Death Coil [Rank 6]
            pPlayer->learnSpell(47889, false);      // Demon Armor [Rank 8]
            pPlayer->learnSpell(696, false);        // Demon Skin [Rank 2]
            pPlayer->learnSpell(48018, false);      // Demonic Circle: Summon
            pPlayer->learnSpell(48020, false);      // Demonic Circle: Teleport
            pPlayer->learnSpell(132, false);        // Detect Invisibility
            pPlayer->learnSpell(47857, false);      // Drain Life [Rank 9]
            pPlayer->learnSpell(5138, false);       // Drain Mana
            pPlayer->learnSpell(47855, false);      // Drain Soul [Rank 6]
            pPlayer->learnSpell(23161, false);      // Dreadsteed
            pPlayer->learnSpell(61191, false);      // Enslave Demon [Rank 4]
            pPlayer->learnSpell(126, false);        // Eye of Kilrogg
            pPlayer->learnSpell(6215, false);       // Fear [Rank 3]
            pPlayer->learnSpell(47893, false);      // Fel Armor [Rank 4]
            pPlayer->learnSpell(5784, false);       // Felsteed
            pPlayer->learnSpell(47856, false);      // Health Funnel [Rank 9]
            pPlayer->learnSpell(47823, false);      // Hellfire [Rank 5]
            pPlayer->learnSpell(17928, false);      // Howl of Terror [Rank 2]
            pPlayer->learnSpell(47811, false);      // Immolate [Rank 11]
            pPlayer->learnSpell(47838, false);      // Incinerate [Rank 4]
            pPlayer->learnSpell(57946, false);      // Life Tap [Rank 8]
            pPlayer->learnSpell(47820, false);      // Rain of Fire [Rank 7]
            pPlayer->learnSpell(18540, false);      // Ritual of Doom
            pPlayer->learnSpell(58887, false);      // Ritual of Souls [Rank 2]
            pPlayer->learnSpell(698, false);        // Ritual of Summoning
            pPlayer->learnSpell(47815, false);      // Searing Pain [Rank 10]
            pPlayer->learnSpell(47836, false);      // Seed of Corruption [Rank 3]
            pPlayer->learnSpell(5500, false);       // Sense Demons
            pPlayer->learnSpell(47809, false);      // Shadow Bolt [Rank 13]
            pPlayer->learnSpell(47891, false);      // Shadow Ward [Rank 6]
            pPlayer->learnSpell(61290, false);      // Shadowflame [Rank 2]
            pPlayer->learnSpell(47825, false);      // Soul Fire [Rank 6]
            pPlayer->learnSpell(29858, false);      // Soulshatter
            pPlayer->learnSpell(691, false);        // Summon Felhunter
            pPlayer->learnSpell(688, false);        // Summon Imp
            pPlayer->learnSpell(712, false);        // Summon Succubus
            pPlayer->learnSpell(697, false);        // Summon Voidwalker
            pPlayer->learnSpell(5697, false);       // Unending Breath

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 10000: // Druid Spells
            pPlayer->learnSpell(2893, false);       // Abolish Poison
            pPlayer->learnSpell(1066, false);       // Aquatic Form
            pPlayer->learnSpell(22812, false);      // Barkskin
            pPlayer->learnSpell(8983, false);       // Bash [Rank 3]
            pPlayer->learnSpell(768, false);        // Cat Form
            pPlayer->learnSpell(5209, false);       // Challenging Roar
            pPlayer->learnSpell(48570, false);      // Claw [Rank 8]
            pPlayer->learnSpell(48575, false);      // Cower [Rank 6]
            pPlayer->learnSpell(8946, false);       // Cure Poison
            pPlayer->learnSpell(33786, false);      // Cyclone
            pPlayer->learnSpell(33357, false);      // Dash [Rank 3]
            pPlayer->learnSpell(48560, false);      // Demoralizing Roar [Rank 8]
            pPlayer->learnSpell(9634, false);       // Dire Bear Form
            pPlayer->learnSpell(5229, false);       // Enrage
            pPlayer->learnSpell(53308, false);      // Entangling Roots [Rank 8]
            pPlayer->learnSpell(770, false);        // Faerie Fire
            pPlayer->learnSpell(16857, false);      // Faerie Fire (Feral)
            pPlayer->learnSpell(20719, false);      // Feline Grace
            pPlayer->learnSpell(16979, false);      // Feral Charge - Bear
            pPlayer->learnSpell(49376, false);      // Feral Charge - Cat
            pPlayer->learnSpell(48577, false);      // Ferocious Bite [Rank 8]
            pPlayer->learnSpell(33943, false);      // Flight Form
            pPlayer->learnSpell(48470, false);      // Gift of the Wild [Rank 4]
            pPlayer->learnSpell(6795, false);       // Growl
            pPlayer->learnSpell(22842, false);      // Frenzied Regeneration [Rank 1]
            pPlayer->learnSpell(48378, false);      // Healing Touch [Rank 15]
            pPlayer->learnSpell(48467, false);      // Hurricane [Rank 5]
            pPlayer->learnSpell(29166, false);      // Innervate
            pPlayer->learnSpell(48451, false);      // Lifebloom [Rank 3]
            pPlayer->learnSpell(48568, false);      // Lacerate [Rank 3]
            pPlayer->learnSpell(49802, false);      // Maim [Rank 2]
            pPlayer->learnSpell(48564, false);      // Mangle (Bear, false); [Rank 5]
            pPlayer->learnSpell(48566, false);      // Mangle (Cat, false); [Rank 5]
            pPlayer->learnSpell(48469, false);      // Mark of the Wild [Rank 9]
            pPlayer->learnSpell(48480, false);      // Maul [Rank 10]
            pPlayer->learnSpell(48463, false);      // Moonfire [Rank 14]
            pPlayer->learnSpell(53312, false);      // Nature's Grasp [Rank 8]
            pPlayer->learnSpell(50464, false);      // Nourish [Rank 1]
            pPlayer->learnSpell(49803, false);      // Pounce [Rank 5]
            pPlayer->learnSpell(9913, false);       // Prowl [Rank 3]
            pPlayer->learnSpell(48574, false);      // Rake [Rank 7]
            pPlayer->learnSpell(48579, false);      // Ravage [Rank 7]
            pPlayer->learnSpell(48477, false);      // Rebirth [Rank 7]
            pPlayer->learnSpell(48443, false);      // Regrowth [Rank 12]
            pPlayer->learnSpell(48441, false);      // Rejuvenation [Rank 15]
            pPlayer->learnSpell(2782, false);       // Remove Curse
            pPlayer->learnSpell(50763, false);      // Revive [Rank 7]
            pPlayer->learnSpell(49800, false);      // Rip [Rank 9]
            pPlayer->learnSpell(62600, false);      // Savage Defense
            pPlayer->learnSpell(48572, false);      // Shred [Rank 9]
            pPlayer->learnSpell(26995, false);      // Soothe Animal [Rank 4]
            pPlayer->learnSpell(48465, false);      // Starfire [Rank 10]
            pPlayer->learnSpell(40120, false);      // Swift Flight Form
            pPlayer->learnSpell(62078, false);      // Swipe (Cat) [Rank 1]
            pPlayer->learnSpell(48562, false);      // Swipe (Bear) [Rank 8]
            pPlayer->learnSpell(18960, false);      // Teleport: Moonglade
            pPlayer->learnSpell(53307, false);      // Thorns [Rank 8]
            pPlayer->learnSpell(50213, false);      // Tiger's Fury [Rank 6]
            pPlayer->learnSpell(5225, false);       // Track Humanoids
            pPlayer->learnSpell(48447, false);      // Tranquility [Rank 7]
            pPlayer->learnSpell(783, false);        // Travel Form
            pPlayer->learnSpell(48461, false);      // Wrath [Rank 12]

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_SPELL, pPlayer, false);

        break;

        case 11000: // Weapon Skills
            if(pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(264, false),        // Bows
            pPlayer->learnSpell(5011, false),       // Crossbows
            pPlayer->learnSpell(266, false),        // Guns
            pPlayer->learnSpell(3018, false),       // Shoot (Ranged)
            pPlayer->learnSpell(2764, false),       // Throw
            pPlayer->learnSpell(2567, false);       // Thrown

            if(pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(1180, false),       // Daggers
            pPlayer->learnSpell(227, false);        // Staves

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(674, false);        // Dual Wield

            if(pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(15590, false);      // Fist Weapons

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(196, false),        // One-Handed Axes
            pPlayer->learnSpell(3127, false);       // Parry

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(198, false);        // One-Handed Maces

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(201, false);        // One-Handed Swords

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(200, false);        // Polearms

            if(pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_WARLOCK)
            pPlayer->learnSpell(5009, false),       // Wands
            pPlayer->learnSpell(5019, false);       // Shoot (Wand)

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(197, false);        // Two-Handed Axes

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(199, false);        // Two-Handed Maces

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->learnSpell(202, false);        // Two-Handed Swords

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_WEAPON, pPlayer, false);

        break;

        case 12000: // Max out all weapon skills

            if(pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_BOWS, 450, 450),            // Max Out Bows
            pPlayer->SetSkill(SKILL_CROSSBOWS, 450, 450),       // Max Out Crossbows
            pPlayer->SetSkill(SKILL_GUNS, 450, 450),            // Max Out Guns
            pPlayer->SetSkill(SKILL_THROWN, 450, 450);          // Max Out Thrown

            if(pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_DAGGERS, 450, 450),         // Max Out Daggers
            pPlayer->SetSkill(SKILL_STAVES, 450, 450);          // Max Out Staves

            if(pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_FIST_WEAPONS, 450, 450);    // Max Out Fist Weapons

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_AXES, 450, 450);            // Max Out Axes

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_MACES, 450, 450);           // Max Out Maces

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_ROGUE || pPlayer->getClass() == CLASS_WARLOCK || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_SWORDS, 450, 450);          // Max Out Swords

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_POLEARMS, 450, 450);        // Max Out Polearms

            if(pPlayer->getClass() == CLASS_MAGE || pPlayer->getClass() == CLASS_PRIEST || pPlayer->getClass() == CLASS_WARLOCK)
            pPlayer->SetSkill(SKILL_WANDS, 450, 450);           // Max Out Wands

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_2H_AXES, 450, 450);         // Max Out Two-Handed Axes

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_DRUID || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_SHAMAN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_2H_MACES, 450, 450);        // Max Out Two-Handed Maces

            if(pPlayer->getClass() == CLASS_DEATHKNIGHT || pPlayer->getClass() == CLASS_HUNTER || pPlayer->getClass() == CLASS_PALADIN || pPlayer->getClass() == CLASS_WARRIOR)
            pPlayer->SetSkill(SKILL_2H_SWORDS, 450, 450);       // Max Out Two-Handed Swords

            pPlayer->SetSkill(SKILL_UNARMED, 450, 450);         // Max Out Unarmed

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_MAXED_WEAPON, pPlayer, false);

        break;

        case 13000: // Max out all riding skills

            pPlayer->learnSpell(34091, false);          // Artisan Riding
            pPlayer->learnSpell(54197, false);          // Cold Weather Flying

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_MAXED_RIDING, pPlayer, false);

        break;

        case 14000: // Learn all languages

            pPlayer->learnSpell(668, false);            // Language Common
            pPlayer->learnSpell(671, false);            // Language Darnassian
            pPlayer->learnSpell(29932, false);          // Language Draenei
            pPlayer->learnSpell(672, false);            // Language Dwarven
            pPlayer->learnSpell(7340, false);           // Language Gnomish
            pPlayer->learnSpell(17737, false);          // Language Gutterspeak
            pPlayer->learnSpell(669, false);            // Language Orcish
            pPlayer->learnSpell(670, false);            // Language Taurahe
            pPlayer->learnSpell(813, false);            // Language Thalassian
            pPlayer->learnSpell(7341, false);           // Language Troll

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_LEARNED_LANGUAGES, pPlayer, false);

        break;

        case 15000: // Max out all languages

            pPlayer->UpdateSkill(98,300);               // Max Out Language Common
            pPlayer->UpdateSkill(113,300);              // Max Out Language Darnassian
            pPlayer->UpdateSkill(759,300);              // Max Out Language Draenei
            pPlayer->UpdateSkill(111,300);              // Max Out Language Dwarven
            pPlayer->UpdateSkill(313,300);              // Max Out Language Gnomish
            pPlayer->UpdateSkill(673,300);              // Max Out Language Gutterspeak
            pPlayer->UpdateSkill(109,300);              // Max Out Language Orcish
            pPlayer->UpdateSkill(115,300);              // Max Out Language Taurahe
            pPlayer->UpdateSkill(137,300);              // Max Out Language Thalassian
            pPlayer->UpdateSkill(315,300);              // Max Out Language Troll

            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterWhisper(MSG_MAXED_LANGUAGES, pPlayer, false);

        break;

        // Close gossip menu
        case 99000:
            pPlayer->CLOSE_GOSSIP_MENU();
        break;
    }
}

bool GossipSelect_custom_npc_spellmaster(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_spellmaster(pPlayer, pCreature, uiAction);

    return true;
}

//npc teleportmaster
std::string CopperToGold(uint32 copper)
{
    // Convert copper to gold/silver/copper
    int32 gold = 0;
    int32 silver = 0;
    if(copper>9999)
    {
        gold = floor(copper/10000.0);
        copper -= gold*10000;
    }
    if(copper>99)
    {
        silver = floor(copper/100.0);
        copper -= silver*100;
    }
    std::stringstream ss;
    ss<< gold << "g " << silver << "s " << copper << "c";
    return ss.str();
}

void ProcessTeleport_custom_npc_teleportmaster(Player *player, Creature *Creature, uint32 action)
{
    QueryResult* pResult = SD2Database.PQuery("SELECT ID,Cost,MapID,Xpos,Ypos,Zpos,Rpos,Name FROM teleportmaster_locations ORDER BY id");
    if(pResult)
    {
        do
        {
            Field* pFields = pResult->Fetch();
            // Make sure this row is the teleport location we want
            if(pFields[0].GetInt32() == action)
            {
                if(player->GetMoney() < pFields[1].GetUInt32())
                {
                        std::stringstream ss;
                        ss << "You do not have enough money to teleport here.  You need " << CopperToGold(pFields[1].GetUInt32()) <<".";
                        Creature->MonsterWhisper(ss.str().c_str(), player, false);
                }
                else
                {
                    // Player has enough money! Do the teleport!
                    std::stringstream ss;
                    ss << "You spent " << CopperToGold(pFields[1].GetUInt32()) <<" on your teleport to " << pFields[7].GetCppString() << ".";
                    Creature->MonsterWhisper(ss.str().c_str(), player, false);
                    player->ModifyMoney(-pFields[1].GetInt32());
                    player->CLOSE_GOSSIP_MENU();
                    player->TeleportTo(pFields[2].GetInt32(),pFields[3].GetFloat(),pFields[4].GetFloat(),pFields[5].GetFloat(),pFields[6].GetFloat());
                }
            }
        } while(pResult->NextRow());
        return;
    }
}

void ProcessMenu_custom_npc_teleportmaster(Player *player, Creature *Creature, uint32 action, uint32 MoreLess, uint32 GroupID)
{
    if(DEBUG_TELE)
        error_log("TeleportMaster: Running ProcessMenu - Action: \"%i\" MoreLess: \"%i\" GroupID: \"%i\"",action,MoreLess,GroupID);

    //Initialize
    int32 ItemCount = 0;
    int32 locations = 0;
    int32 throttle  = 0;
    QueryResult* pResult;
    if(action==100000) action=0;
    if(action<=1000) throttle = 1000;
    if(action<=100)  throttle = 100;
    if(GroupID>0)    throttle = 1000;

    // Query the DB
    if( action<=1000 )
    {
        pResult = SD2Database.PQuery("SELECT CategoryID,CategoryName,SubCatGroupID,SubCatName FROM teleportmaster_categories WHERE CategoryID >= \"%i\" AND CategoryID <= \"%i\" ORDER BY CategoryID", action, throttle);
        //Not a SubCat, list out locations
        if( pResult->Fetch()[2].GetInt32()==0 && (action>100 || (action<=100 && action>0 && MoreLess==0)) )
        {
            pResult = SD2Database.PQuery("SELECT ID,CategoryID,Name,faction,ReqLevel,GuildID,Cost FROM teleportmaster_locations WHERE CategoryID = \"%i\" ORDER BY ID", action);
            locations = 1;
        }
        else if(action<=1000 && action>1)
        {
            if(MoreLess>0 || action<=100)
            {
                if(action<=100)
                    pResult = SD2Database.PQuery("SELECT CategoryID,CategoryName,SubCatGroupID,SubCatName FROM teleportmaster_categories WHERE CategoryID >= \"%i\" AND CategoryID <= \"%i\" ORDER BY CategoryID", action, throttle);
                else
                {
                    QueryResult* pResultGroup = SD2Database.PQuery("SELECT CategoryID,CategoryName,SubCatGroupID,SubCatName FROM teleportmaster_categories WHERE CategoryID = \"%i\"", action);
                    if(pResultGroup)
                    {
                        GroupID = pResultGroup->Fetch()[2].GetInt32();
                        pResult = SD2Database.PQuery("SELECT CategoryID,CategoryName,SubCatGroupID,SubCatName FROM teleportmaster_categories WHERE CategoryID >= \"%i\" AND SubCatGroupID = \"%i\" ORDER BY CategoryID", action, GroupID);
                    }
                }
            }
            else
            {
                //List what is INSIDE this sub-group
                pResult = SD2Database.PQuery("SELECT ID,CategoryID,Name,faction,ReqLevel,GuildID,Cost FROM teleportmaster_locations WHERE CategoryID = \"%i\" ORDER BY ID", action);
                locations = 1;
            }
        }
    }
    if(action>1000)
    {
        if(MoreLess>0)
        {
            QueryResult* pResultGroup = SD2Database.PQuery("SELECT ID,CategoryID FROM teleportmaster_locations WHERE ID = \"%i\"", action);
            if(pResultGroup)
            {
                GroupID = pResultGroup->Fetch()[1].GetInt32();
                pResult = SD2Database.PQuery("SELECT ID,CategoryID,Name,faction,ReqLevel,GuildID,Cost FROM teleportmaster_locations WHERE CategoryID = \"%i\" AND ID>= \"%i\" ORDER BY ID", GroupID, action);
                locations = 1;
            }
        }
        else
        {
            ProcessTeleport_custom_npc_teleportmaster( player, Creature, action);
            return;
        }
    }

    // Make sure the result is valid, add menu items
    if(pResult)
    {
        if(DEBUG_TELE)
            error_log("TeleportMaster: ProcessMenu queried the DB and got results, processing results...");
        do
        {
            Field* pFields = pResult->Fetch();
            if(ItemCount==10)
            {
                //Count is 10! We need a 'more' button!
                if(DEBUG_TELE)
                    error_log("TeleportMaster: 10 Items on menu, adding 'more' button: \"%i\"", pFields[0].GetInt32() + 200000);
                player->ADD_GOSSIP_ITEM( 4, "More ->", GOSSIP_SENDER_MAIN,  pFields[0].GetInt32() + 200000);
                ItemCount++;
            }
            else
            {
                std::stringstream CatName;
                //MainCat Items
                if(action<101 && !locations && GroupID==0)
                {
                        CatName<<pFields[1].GetCppString()<<" ->";
                        player->ADD_GOSSIP_ITEM( 5, CatName.str().c_str(), GOSSIP_SENDER_MAIN, pFields[0].GetInt32());
                        ItemCount++;
                }
                //SubCat Items
                if(action<1001 && GroupID>0 && pFields[0].GetInt32()>100 && pFields[2].GetInt32()==GroupID && !locations)
                {
                        CatName<<pFields[3].GetCppString()<<" ->";
                        player->ADD_GOSSIP_ITEM( 5, CatName.str().c_str(), GOSSIP_SENDER_MAIN, pFields[0].GetInt32());
                        ItemCount++;
                }
                //Locations or Root SubCats
                if(locations)
                {
                    if(GroupID==0 || action>1000 || (action<=1000 && MoreLess==0) )
                    {
                        if( (pFields[3].GetInt32()==2 && player->GetTeam()==ALLIANCE) || (pFields[3].GetInt32()==1 && player->GetTeam()==HORDE) || (player->getLevel()<pFields[4].GetUInt32()) || (pFields[5].GetInt32()>0 && player->GetGuildId() != pFields[5].GetInt32()) )
                        {
                                //FAIL!!  Do nothing...
                        }
                        else
                        {
                            std::stringstream menuItem;
                            menuItem << pFields[2].GetCppString() << " - " << CopperToGold(pFields[6].GetInt32());
                            player->ADD_GOSSIP_ITEM( 2, menuItem.str().c_str(), GOSSIP_SENDER_MAIN, pFields[0].GetInt32());
                            ItemCount++;
                        }
                    }
                    else
                    {
                        CatName<<pFields[1].GetCppString()<<" ->";
                        player->ADD_GOSSIP_ITEM( 5, CatName.str().c_str(), GOSSIP_SENDER_MAIN, pFields[0].GetInt32());
                        ItemCount++;
                    }
                }
            }
        } while(pResult->NextRow() && ItemCount<11);
    }

    //scan teleportmaster_locations for locations matching this groupID and add them if ItemCount<10
    if( GroupID>0 && !locations && ItemCount<10 )
    {
        pResult = SD2Database.PQuery("SELECT ID,CategoryID,faction,ReqLevel,GuildID,Name,cost FROM teleportmaster_locations WHERE CategoryID = \"%i\" ORDER BY ID",action);
        if(pResult)
        {
            if(DEBUG_TELE)
                error_log("TeleportMaster: Adding additional locations to a SubCat");
            do
            {
                Field* pFields = pResult->Fetch();
                if(ItemCount==10)
                {
                    //Count is 10! We need a 'more' button!
                    if(DEBUG_TELE) error_log("TeleportMaster: 10 Items on menu, adding 'more' button: \"%i\"", pFields[0].GetInt32() + 200000);
                    player->ADD_GOSSIP_ITEM( 4, "More ->", GOSSIP_SENDER_MAIN,  pFields[0].GetInt32() + 200000);
                    ItemCount++;
                }
                if( (pFields[2].GetInt32()==2 && player->GetTeam()==ALLIANCE) || (pFields[2].GetInt32()==1 && player->GetTeam()==HORDE) || (player->getLevel()<pFields[3].GetUInt32()) || (pFields[4].GetInt32()>0 && player->GetGuildId() != pFields[4].GetInt32()) )
                {
                    //FAIL!!  Do nothing...
                }
                else
                {
                    std::stringstream menuItem;
                    menuItem << pFields[5].GetCppString() << " - " << CopperToGold(pFields[6].GetInt32());
                    player->ADD_GOSSIP_ITEM( 2, menuItem.str().c_str(), GOSSIP_SENDER_MAIN, pFields[0].GetInt32());
                    ItemCount++;
                }
            } while(pResult->NextRow() && ItemCount<11);
        }
    }

    //Add 'Prev' and 'Main Menu' buttons as needed
    if(DEBUG_TELE)
        error_log("TeleportMaster: Adding 'Prev' and 'Main Menu' buttons for action: \"%i\" GroupId:\"%i\"",action,GroupID);
    if(MoreLess>0 || locations)
    {
        if(action<2)
        {
            if(MoreLess==0)
                player->ADD_GOSSIP_ITEM( 4, "<- Main Menu", GOSSIP_SENDER_MAIN,  100000 );
        }
        else
        {
            int32 prevAction=0;
            QueryResult* pResultPrev;
            if(action>=1000)
                pResultPrev = SD2Database.PQuery("SELECT ID,CategoryID,faction,ReqLevel,GuildID FROM teleportmaster_locations WHERE CategoryID = \"%i\" AND ID <= \"%i\" ORDER BY ID DESC",GroupID,action);
            if(action>=100 && action<1000)
                pResultPrev = SD2Database.PQuery("SELECT CategoryID,SubCatGroupID FROM teleportmaster_categories WHERE SubCatGroupID = \"%i\" AND CategoryID <= \"%i\" ORDER BY CategoryID DESC",GroupID,action);
            if(action>1 && action<100)
                pResultPrev = SD2Database.PQuery("SELECT CategoryID,SubCatGroupID FROM teleportmaster_categories WHERE CategoryID <= \"%i\" ORDER BY CategoryID DESC",action);

            // Make sure the result is valid
            if(pResultPrev)
            {
                int32 count=0;
                //Count backwards starting at our last item and only count valid locations
                do
                {
                    Field* pFields = pResultPrev->Fetch();
                    if(action>1000)
                    {
                        if( (pFields[2].GetInt32()==2 && player->GetTeam()==ALLIANCE) || (pFields[2].GetInt32()==1 && player->GetTeam()==HORDE) || (player->getLevel()<pFields[3].GetUInt32()) || (pFields[4].GetInt32()>0 && player->GetGuildId() != pFields[4].GetInt32()) )
                        {
                            //FAIL!!  Do nothing...
                        }
                        else
                            count++;
                    }
                    else
                        count++;
                    if(count==11)
                        prevAction = pFields[0].GetInt32();
                } while(pResultPrev->NextRow());

            }
            if(prevAction>0)
            {
                player->ADD_GOSSIP_ITEM( 4, "<- Prev", GOSSIP_SENDER_MAIN, prevAction + 400000 );
                if(DEBUG_TELE)
                    error_log("TeleportMaster: Prev1: \"%i\"", prevAction + 400000);
            }
            player->ADD_GOSSIP_ITEM( 4, "<- Main Menu", GOSSIP_SENDER_MAIN,  100000 );
        }
    }
    else if(action<=1000 && action>0 && MoreLess==0)
    {
        if( GroupID==0 || (action<100 && GroupID>0) )
            player->ADD_GOSSIP_ITEM( 4, "<- Main Menu", GOSSIP_SENDER_MAIN,  100000 );
    }
    player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,Creature->GetObjectGuid());
    return;
}

bool GossipHello_custom_npc_teleportmaster(Player *player, Creature *Creature)
{
    // Make sure we can access the Config file
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
    {
        player->CLOSE_GOSSIP_MENU();
        error_log("TeleportMaster: Unable to open configuration file");
        Creature->MonsterWhisper("I'm sorry, we are having technical difficulties.  Please check back later.", player, false);
        return false;
    }
    // Make sure player is not in combat
    if (player->IsInCombat()){
        player->CLOSE_GOSSIP_MENU();
        Creature->MonsterWhisper("You are in combat!", player, false);
        return false;
    }

    ProcessMenu_custom_npc_teleportmaster(player, Creature,0,0,0);
    return true;
}

void SendDefaultMenu_custom_npc_teleportmaster(Player *player, Creature *Creature, uint32 action)
{
    int32 ItemCount = 0;			//Track how many items we have on the menu so far
    int32 MoreLess = 0;				//Track if we possibly just clicked a 'more' or 'prev' button
    int32 actionID = action;		//Track our initial action code when we got here

    if(action>400000)
        action-=100000;
    if(action>300000)
    {
        action-=300000;
        MoreLess = 2;	//This was a 'prev' button click
    }
    if(action>200000)
        action-=100000;
    if(action>100000)
    {
        action-=100000;
        MoreLess = 1;   //This was a 'more' button click
    }
    if(DEBUG_TELE)
        error_log("TeleportMaster: Processing Default Menu using 'action': \"%i\"  ActionID: \"%i\" MoreLess: \"%i\" ",action,actionID,MoreLess);

    // Main Menu Return
    if(action==100000)
    {
        ProcessMenu_custom_npc_teleportmaster(player,Creature,action,0,0);
        return;
    }//End Main Menu Return

    if(MoreLess>0)
    {
        ProcessMenu_custom_npc_teleportmaster(player,Creature,action,MoreLess,0);
        return;
    }
    //Sub-Groups
    //Check for Group ID Number if we find a match, we have a sub-group
    int32 Group = 0;
    QueryResult* pResult = SD2Database.PQuery("SELECT CategoryID,SubCatGroupID FROM teleportmaster_categories ORDER BY CategoryID");
    // Make sure the result is valid
    if(pResult)
    {
        do
        {
            Field* pFields = pResult->Fetch();
            if(pFields[0].GetInt32()==action)
            {  //Magic check
                Group = pFields[1].GetInt32();
            }
        } while(pResult->NextRow());
    }
    if(Group>0)
        ProcessMenu_custom_npc_teleportmaster(player,Creature,action,MoreLess,Group);
    else
        ProcessMenu_custom_npc_teleportmaster(player,Creature,action,MoreLess,0);
}//End SendDefaultMenu_TeleportMaster

bool GossipSelect_custom_npc_teleportmaster(Player *player, Creature *Creature, uint32 sender, uint32 action)
{
    // Main menu
    if (sender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_teleportmaster( player, Creature, action);

    return true;
}

// title master
#define GOSSIP_BUY_ALLIANCE_TITLES		"Buy |cffff0000Alliance|r Titles"
#define GOSSIP_BUY_HORDE_TITLES			"Buy |cffff0000Horde|r Titles"
#define GOSSIP_BUY_OTHER_TITLES			"Buy |cFF959697Other|r Titles"
#define MSG_SHORT_ON_GOLD_OR_HONOR		"You dont have enough money or Honor Points!"
#define SD2_ERROR_LOG					"SD2: Unable to open configuration file!"

bool GossipHello_custom_npc_titlemaster(Player* pPlayer, Creature* pCreature)
{

    // Alliance Titles
    if (pPlayer->GetTeam() == ALLIANCE)
    {
        pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_ALLIANCE_TITLES, GOSSIP_SENDER_MAIN, 1000);
        // Other Tiles
        pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_OTHER_TITLES, GOSSIP_SENDER_MAIN, 3000);
    }
    else // Horde Titles
    {
        pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_HORDE_TITLES, GOSSIP_SENDER_MAIN, 2000);
        // Other Titles
        pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_OTHER_TITLES, GOSSIP_SENDER_MAIN, 3000);
    }

    pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());

    return true;
}

void SendDefaultMenu_custom_npc_titlemaster(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{

    // Not allow in combat
    if (pPlayer->isInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay(MSG_COMBAT, LANG_UNIVERSAL, NULL);
        return;
    }

    switch(uiAction)
    {
        case 1000: //Alliance Titles
                pPlayer->ADD_GOSSIP_ITEM( 9, "Private. |cffff0000Costs:|r 100HP-200Gold"				, GOSSIP_SENDER_MAIN, 1001);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Corporal. |cffff0000Costs:|r 150HP-300Gold"				, GOSSIP_SENDER_MAIN, 1002);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Sergeant. |cffff0000Costs:|r 200HP-400Gold"				, GOSSIP_SENDER_MAIN, 1003);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Master Sergeant. |cffff0000Costs:|r 250HP-500Gold"		, GOSSIP_SENDER_MAIN, 1004);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Sergeant Major. |cffff0000Costs:|r 300HP-600Gold"			, GOSSIP_SENDER_MAIN, 1005);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Knight. |cffff0000Costs:|r 400HP-800Gold"					, GOSSIP_SENDER_MAIN, 1006);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Knight-Lieutenant. |cffff0000Costs:|r 500HP-1000Gold"		, GOSSIP_SENDER_MAIN, 1007);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Knight-Captain. |cffff0000Costs:|r 650HP-1300Gold"		, GOSSIP_SENDER_MAIN, 1008);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Knight-Champion. |cffff0000Costs:|r 800HP-1600Gold"		, GOSSIP_SENDER_MAIN, 1009);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Lieutenant Commander. |cffff0000Costs:|r 1000HP-2000Gold"	, GOSSIP_SENDER_MAIN, 1010);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Commander. |cffff0000Costs:|r 1200HP-2400Gold"			, GOSSIP_SENDER_MAIN, 1011);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Marshal. |cffff0000Costs:|r 1500HP-3000Gold"				, GOSSIP_SENDER_MAIN, 1012);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Field Marshal. |cffff0000Costs:|r 1800HP-3600Gold"		, GOSSIP_SENDER_MAIN, 1013);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"													, GOSSIP_SENDER_MAIN, 1500);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 1500: //Alliance Titles 2
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Marshal. |cffff0000Costs:|r 3600HP-7200Gold"		, GOSSIP_SENDER_MAIN, 1014);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of The Alliance. |cffff0000Costs:|r 5000HP-10000Gold"		, GOSSIP_SENDER_MAIN, 1015);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Justicar. |cffff0000Costs:|r 2000Gold"					, GOSSIP_SENDER_MAIN, 1016);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Flame Warden. |cffff0000Costs:|r 2000Gold"				, GOSSIP_SENDER_MAIN, 1017);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Exodar. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 1018);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Darnassus. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 1019);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Ironforge. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 1020);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Stormwind. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 1021);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Gnomeregan. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 1022);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"													, GOSSIP_SENDER_MAIN, 1000);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 2000: //Horde Titles
                pPlayer->ADD_GOSSIP_ITEM( 9, "Scout. |cffff0000Costs:|r 100HP-200Gold"					, GOSSIP_SENDER_MAIN, 2001);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grunt. |cffff0000Costs:|r 150HP-300Gold"					, GOSSIP_SENDER_MAIN, 2002);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Sergeant. |cffff0000Costs:|r 200HP-400Gold"				, GOSSIP_SENDER_MAIN, 2003);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Senior Sergeant. |cffff0000Costs:|r 250HP-500Gold"		, GOSSIP_SENDER_MAIN, 2004);
                pPlayer->ADD_GOSSIP_ITEM( 9, "First Sergeant. |cffff0000Costs:|r 300HP-600Gold"			, GOSSIP_SENDER_MAIN, 2005);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Stone Guard. |cffff0000Costs:|r 400HP-800Gold"			, GOSSIP_SENDER_MAIN, 2006);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Blood Guard. |cffff0000Costs:|r 500HP-1000Gold"			, GOSSIP_SENDER_MAIN, 2007);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Legionnaire. |cffff0000Costs:|r 650HP-1300Gold"			, GOSSIP_SENDER_MAIN, 2008);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Centurion. |cffff0000Costs:|r 800HP-1600Gold"				, GOSSIP_SENDER_MAIN, 2009);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Champion. |cffff0000Costs:|r 1000HP-2000Gold"				, GOSSIP_SENDER_MAIN, 2010);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Lieutenant General. |cffff0000Costs:|r 1200HP-2400Gold"	, GOSSIP_SENDER_MAIN, 2011);
                pPlayer->ADD_GOSSIP_ITEM( 9, "General. |cffff0000Costs:|r 1500HP-3000Gold"				, GOSSIP_SENDER_MAIN, 2012);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Warlord. |cffff0000Costs:|r 1800HP-3600Gold"				, GOSSIP_SENDER_MAIN, 2013);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"													, GOSSIP_SENDER_MAIN, 2500);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 2500: //Horde Titles 2
                pPlayer->ADD_GOSSIP_ITEM( 9, "High Warlord. |cffff0000Costs:|r 3600HP-7200Gold"		, GOSSIP_SENDER_MAIN, 2014);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Horde. |cffff0000Costs:|r 5000HP-10000Gold"	, GOSSIP_SENDER_MAIN, 2015);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Conqueror. |cffff0000Costs:|r 2000Gold"				, GOSSIP_SENDER_MAIN, 2016);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Flame Keeper. |cffff0000Costs:|r 2000Gold"			, GOSSIP_SENDER_MAIN, 2017);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Orgrimmar. |cffff0000Costs:|r 4000Gold"			, GOSSIP_SENDER_MAIN, 2018);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Sen'jin. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 2019);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Silvermoon. |cffff0000Costs:|r 4000Gold"			, GOSSIP_SENDER_MAIN, 2020);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Thunder Bluff. |cffff0000Costs:|r 4000Gold"		, GOSSIP_SENDER_MAIN, 2021);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Undercity. |cffff0000Costs:|r 4000Gold"		, GOSSIP_SENDER_MAIN, 2022);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"												, GOSSIP_SENDER_MAIN, 2000);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"											, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3000: //Other Titles
                pPlayer->ADD_GOSSIP_ITEM( 9, "Gladiator. |cffff0000Costs:|r 100HP-200Gold"				, GOSSIP_SENDER_MAIN, 3001);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Duelist. |cffff0000Costs:|r 200HP-400Gold"				, GOSSIP_SENDER_MAIN, 3002);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Rival. |cffff0000Costs:|r 300HP-600Gold"					, GOSSIP_SENDER_MAIN, 3003);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Challenger. |cffff0000Costs:|r 250HP-500Gold"				, GOSSIP_SENDER_MAIN, 3004);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Scarab Lord. |cffff0000Costs:|r 4000Gold"					, GOSSIP_SENDER_MAIN, 3005);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Champion of the Naaru. |cffff0000Costs:|r 4000Gold"		, GOSSIP_SENDER_MAIN, 3006);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Merciless Gladiator. |cffff0000Costs:|r 500HP-1000Gold"	, GOSSIP_SENDER_MAIN, 3007);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Shattered Sun. |cffff0000Costs:|r 4000Gold"		, GOSSIP_SENDER_MAIN, 3008);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Hand of A'dal. |cffff0000Costs:|r 4000Gold"				, GOSSIP_SENDER_MAIN, 3009);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Vengeful Gladiator. |cffff0000Costs:|r 600HP-1200Gold"	, GOSSIP_SENDER_MAIN, 3010);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Battlemaster. |cffff0000Costs:|r 15000Gold"				, GOSSIP_SENDER_MAIN, 3011);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Elder. |cffff0000Costs:|r 6000Gold"						, GOSSIP_SENDER_MAIN, 3012);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Exalted. |cffff0000Costs:|r 10000Gold"				, GOSSIP_SENDER_MAIN, 3013);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"													, GOSSIP_SENDER_MAIN, 3500);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3500: //Other Titles 2
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Explorer. |cffff0000Costs:|r 10000Gold"				, GOSSIP_SENDER_MAIN, 3014);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Diplomat. |cffff0000Costs:|r 8000Gold"				, GOSSIP_SENDER_MAIN, 3015);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Brutal Gladiator. |cffff0000Costs:|r 700HP-1400Gold"		, GOSSIP_SENDER_MAIN, 3016);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Seeker. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3017);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Arena Master. |cffff0000Costs:|r 15000Gold"				, GOSSIP_SENDER_MAIN, 3018);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Salty. |cffff0000Costs:|r 4000Gold"						, GOSSIP_SENDER_MAIN, 3019);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Chef. |cffff0000Costs:|r 4000Gold"						, GOSSIP_SENDER_MAIN, 3020);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Supreme. |cffff0000Costs:|r 10000Gold"				, GOSSIP_SENDER_MAIN, 3021);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Ten Storms. |cffff0000Costs:|r 8000Gold"			, GOSSIP_SENDER_MAIN, 3022);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Emerald Dream. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3023);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Prophet. |cffff0000Costs:|r 8000Gold"						, GOSSIP_SENDER_MAIN, 3024);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Malefic. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3025);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"													, GOSSIP_SENDER_MAIN, 3501);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"													, GOSSIP_SENDER_MAIN, 3000);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3501: //Other Titles 3
                pPlayer->ADD_GOSSIP_ITEM( 9, "Stalker. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3026);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Ebon Blade. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3027);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Archmage. |cffff0000Costs:|r 8000Gold"				, GOSSIP_SENDER_MAIN, 3028);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Warbringer. |cffff0000Costs:|r  8000Gold"				, GOSSIP_SENDER_MAIN, 3029);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Assassin. |cffff0000Costs:|r 8000Gold"				, GOSSIP_SENDER_MAIN, 3030);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Alchemist. |cffff0000Costs:|r 2000Gold"	, GOSSIP_SENDER_MAIN, 3031);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Blacksmith. |cffff0000Costs:|r 2000Gold"	, GOSSIP_SENDER_MAIN, 3032);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Iron Chef. |cffff0000Costs:|r 2000Gold"				, GOSSIP_SENDER_MAIN, 3033);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Enchanter. |cffff0000Costs:|r 2000Gold"	, GOSSIP_SENDER_MAIN, 3034);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Engineer. |cffff0000Costs:|r 2000Gold"	, GOSSIP_SENDER_MAIN, 3035);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Doctor. |cffff0000Costs:|r 2000Gold"					, GOSSIP_SENDER_MAIN, 3036);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Angler. |cffff0000Costs:|r 2000Gold"		, GOSSIP_SENDER_MAIN, 3037);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"												, GOSSIP_SENDER_MAIN, 3502);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"												, GOSSIP_SENDER_MAIN, 3500);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"											, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3502: //Other Titles 4
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Herbalist. |cffff0000Costs:|r 2000Gold"			, GOSSIP_SENDER_MAIN, 3038);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Scribe. |cffff0000Costs:|r 2000Gold"				, GOSSIP_SENDER_MAIN, 3039);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Jewelcrafter. |cffff0000Costs:|r 2000Gold"		, GOSSIP_SENDER_MAIN, 3040);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Leatherworker. |cffff0000Costs:|r 2000Gold"		, GOSSIP_SENDER_MAIN, 3041);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Miner. |cffff0000Costs:|r 2000Gold"				, GOSSIP_SENDER_MAIN, 3042);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Skinner. |cffff0000Costs:|r 2000Gold"			, GOSSIP_SENDER_MAIN, 3043);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Master Tailor. |cffff0000Costs:|r 2000Gold"				, GOSSIP_SENDER_MAIN, 3044);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Quel'Thalas. |cffff0000Costs:|r 4000Gold"					, GOSSIP_SENDER_MAIN, 3045);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Argus. |cffff0000Costs:|r 4000Gold"						, GOSSIP_SENDER_MAIN, 3046);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of Khaz Modan. |cffff0000Costs:|r 4000Gold"					, GOSSIP_SENDER_MAIN, 3047);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Lion Hearted. |cffff0000Costs:|r 6000Gold"				, GOSSIP_SENDER_MAIN, 3048);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Champion of Elune. |cffff0000Costs:|r 6000Gold"				, GOSSIP_SENDER_MAIN, 3049);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"														, GOSSIP_SENDER_MAIN, 3503);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"														, GOSSIP_SENDER_MAIN, 3501);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"													, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3503: //Other Titles 5
                pPlayer->ADD_GOSSIP_ITEM( 9, "Hero of Orgrimmar. |cffff0000Costs:|r 6000Gold"						, GOSSIP_SENDER_MAIN, 3050);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Plainsrunner. |cffff0000Costs:|r 6000Gold"							, GOSSIP_SENDER_MAIN, 3051);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Darkspear. |cffff0000Costs:|r 6000Gold"						, GOSSIP_SENDER_MAIN, 3052);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Forsaken. |cffff0000Costs:|r 6000Gold"							, GOSSIP_SENDER_MAIN, 3053);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Magic Seeker. |cffff0000Costs:|r 6000Gold"						, GOSSIP_SENDER_MAIN, 3054);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Twilight Vanquisher. |cffff0000Costs:|r 8000Gold"						, GOSSIP_SENDER_MAIN, 3055);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Conqueror of Naxxramas. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3056);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Hero of Northrend. |cffff0000Costs:|r 8000Gold"						, GOSSIP_SENDER_MAIN, 3057);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Hallowed. |cffff0000Costs:|r 6000Gold"							, GOSSIP_SENDER_MAIN, 3058);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Loremaster. |cffff0000Costs:|r 10000Gold"								, GOSSIP_SENDER_MAIN, 3059);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Flawless Victor. |cffff0000Costs:|r 100000Gold"					, GOSSIP_SENDER_MAIN, 3060);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Champion of the Frozen Wastes. |cffff0000Costs:|r 6000Gold"			, GOSSIP_SENDER_MAIN, 3061);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"																, GOSSIP_SENDER_MAIN, 3504);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"																, GOSSIP_SENDER_MAIN, 3503);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"															, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3504: //Other Titles 6
                pPlayer->ADD_GOSSIP_ITEM( 9, "Ambassador. |cffff0000Costs:|r 10000Gold"				, GOSSIP_SENDER_MAIN, 3062);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Argent Champion. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3063);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Guardian of Cenarius. |cffff0000Costs:|r 6000Gold"	, GOSSIP_SENDER_MAIN, 3064);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Brewmaster. |cffff0000Costs:|r 6000Gold"				, GOSSIP_SENDER_MAIN, 3065);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Merrymaker. |cffff0000Costs:|r 6000Gold"				, GOSSIP_SENDER_MAIN, 3066);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Love Fool. |cffff0000Costs:|r 6000Gold"			, GOSSIP_SENDER_MAIN, 3067);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Matron. |cffff0000Costs:|r 6000Gold"					, GOSSIP_SENDER_MAIN, 3068);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Patron. |cffff0000Costs:|r 6000Gold"					, GOSSIP_SENDER_MAIN, 3069);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Obsidian Slayer. |cffff0000Costs:|r 6000Gold"			, GOSSIP_SENDER_MAIN, 3070);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Nightfall. |cffff0000Costs:|r 6000Gold"		, GOSSIP_SENDER_MAIN, 3071);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Immortal. |cffff0000Costs:|r 20000Gold"			, GOSSIP_SENDER_MAIN, 3072);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Undying. |cffff0000Costs:|r 10000Gold"			, GOSSIP_SENDER_MAIN, 3073);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"												, GOSSIP_SENDER_MAIN, 3503);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"												, GOSSIP_SENDER_MAIN, 3505);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"											, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3505: //Other Titles 7
                pPlayer->ADD_GOSSIP_ITEM( 9, "Jenkins. |cffff0000Costs:|r 6000Gold"						, GOSSIP_SENDER_MAIN, 3074);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Bloodsail Admiral. |cffff0000Costs:|r 4000Gold"			, GOSSIP_SENDER_MAIN, 3075);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Insane. |cffff0000Costs:|r 10000Gold"					, GOSSIP_SENDER_MAIN, 3076);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Noble. |cffff0000Costs:|r 10000Gold"					, GOSSIP_SENDER_MAIN, 3077);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Crusader. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3078);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Deadly Gladiator. |cffff0000Costs:|r 800HP-1600Gold"		, GOSSIP_SENDER_MAIN, 3079);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Death's Demise. |cffff0000Costs:|r 8000Gold"				, GOSSIP_SENDER_MAIN, 3080);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Celestial Defender. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3081);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Conqueror of Ulduar. |cffff0000Costs:|r 8000Gold"			, GOSSIP_SENDER_MAIN, 3082);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Champion of Ulduar. |cffff0000Costs:|r 10000Gold"			, GOSSIP_SENDER_MAIN, 3083);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Vanquisher. |cffff0000Costs:|r 10000Gold"					, GOSSIP_SENDER_MAIN, 3084);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Starcaller. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3085);
                pPlayer->ADD_GOSSIP_ITEM( 7, "Next ->"													, GOSSIP_SENDER_MAIN, 3506);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"													, GOSSIP_SENDER_MAIN, 3504);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 3506: //Other Titles 8
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Astral Walker. |cffff0000Costs:|r 8000Gold"			, GOSSIP_SENDER_MAIN, 3086);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Herald of the Titans. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3087);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Furious Gladiator. |cffff0000Costs:|r 100HP-200Gold"		, GOSSIP_SENDER_MAIN, 3088);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Pilgrim. |cffff0000Costs:|r 900HP-1800Gold"			, GOSSIP_SENDER_MAIN, 3089);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Relentless Gladiator. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3090);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Grand Crusader. |cffff0000Costs:|r 100000Gold"			, GOSSIP_SENDER_MAIN, 3091);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Argent Defender. |cffff0000Costs:|r 8000Gold"			, GOSSIP_SENDER_MAIN, 3092);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Patient. |cffff0000Costs:|r 8000Gold"					, GOSSIP_SENDER_MAIN, 3093);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Light of Dawn. |cffff0000Costs:|r 10000Gold"			, GOSSIP_SENDER_MAIN, 3094);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Bane of the Fallen King. |cffff0000Costs:|r 800Gold"		, GOSSIP_SENDER_MAIN, 3095);
                pPlayer->ADD_GOSSIP_ITEM( 9, "the Kingslayer. |cffff0000Costs:|r 10000Gold"				, GOSSIP_SENDER_MAIN, 3096);
                pPlayer->ADD_GOSSIP_ITEM( 9, "of the Ashen Verdict. |cffff0000Costs:|r 8000Gold"		, GOSSIP_SENDER_MAIN, 3097);
                pPlayer->ADD_GOSSIP_ITEM( 9, "Wrathful Gladiator. |cffff0000Costs:|r 1200HP-2400Gold"	, GOSSIP_SENDER_MAIN, 3098);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Back"													, GOSSIP_SENDER_MAIN, 3505);
                pPlayer->ADD_GOSSIP_ITEM( 7, "<- Main Menu"												, GOSSIP_SENDER_MAIN, 8000);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        //Back To Main Menu
        case 8000:
            // Alliance Titles
            if (pPlayer->GetTeam() == ALLIANCE)
            {
                pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_ALLIANCE_TITLES, GOSSIP_SENDER_MAIN, 1000);
                // Other Tiles
                pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_OTHER_TITLES, GOSSIP_SENDER_MAIN, 3000);
            }
            else // Horde Titles
            {
                pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_HORDE_TITLES, GOSSIP_SENDER_MAIN, 2000);
                // Other Titles
                pPlayer->ADD_GOSSIP_ITEM( 9, GOSSIP_BUY_OTHER_TITLES, GOSSIP_SENDER_MAIN, 3000);
            }

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());

        break;

        //////////////////////////////////////////////////Alliance Titles///////////////////////////////////////////////////////////////

        case 1001: // Private Title
                if ((pPlayer->GetHonorPoints() >= 100) && (pPlayer->GetMoney() >=2000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(1))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Private' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-2000000);
                        pPlayer->ModifyHonorPoints(-100);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Private' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1002: // Corporal Title
                if ((pPlayer->GetHonorPoints() >= 150) && (pPlayer->GetMoney() >=3000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(2))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Corporal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-3000000);
                        pPlayer->ModifyHonorPoints(-150);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Corporal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1003: // Sergeant Title
                if ((pPlayer->GetHonorPoints() >= 200) && (pPlayer->GetMoney() >=4000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(3))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-4000000);
                        pPlayer->ModifyHonorPoints(-200);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1004: // Master Sergeant Title
                if ((pPlayer->GetHonorPoints() >= 250) && (pPlayer->GetMoney() >=5000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(4))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Master Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-5000000);
                        pPlayer->ModifyHonorPoints(-250);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Master Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1005: // Sergeant Major Title
                if ((pPlayer->GetHonorPoints() >= 300) && (pPlayer->GetMoney() >=6000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(5))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Sergeant Major' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-6000000);
                        pPlayer->ModifyHonorPoints(-300);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Sergeant Major' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1006: // Knight Title
                if ((pPlayer->GetHonorPoints() >= 400) && (pPlayer->GetMoney() >=8000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(6))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Knight' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-8000000);
                        pPlayer->ModifyHonorPoints(-400);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Knight' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1007: // Knight-Lieutenant Title
                if ((pPlayer->GetHonorPoints() >= 500) && (pPlayer->GetMoney() >=10000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(7))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Knight-Lieutenant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-10000000);
                        pPlayer->ModifyHonorPoints(-500);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Knight-Lieutenant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1008: // Knight-Captain Title
                if ((pPlayer->GetHonorPoints() >= 650) && (pPlayer->GetMoney() >=13000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(8))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Knight-Captain' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-13000000);
                        pPlayer->ModifyHonorPoints(-650);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Knight-Captain' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1009: // Knight-Champion Title
                if ((pPlayer->GetHonorPoints() >= 800) && (pPlayer->GetMoney() >=16000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(9))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Knight-Champion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-16000000);
                        pPlayer->ModifyHonorPoints(-800);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Knight-Champion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1010: // Lieutenant Commander Title
                if ((pPlayer->GetHonorPoints() >= 1000) && (pPlayer->GetMoney() >=20000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(10))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Lieutenant Commander' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pPlayer->ModifyHonorPoints(-1000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Lieutenant Commander' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1011: // Commander Title
                if ((pPlayer->GetHonorPoints() >= 1200) && (pPlayer->GetMoney() >=24000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(11))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Commander' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-24000000);
                        pPlayer->ModifyHonorPoints(-1200);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Commander' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1012: // Marshal Title
                if ((pPlayer->GetHonorPoints() >= 1500) && (pPlayer->GetMoney() >=30000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(12))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Marshal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-30000000);
                        pPlayer->ModifyHonorPoints(-1500);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Marshal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1013: // Field Marshal Title
                if ((pPlayer->GetHonorPoints() >= 1800) && (pPlayer->GetMoney() >=36000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(13))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Field Marshal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-36000000);
                        pPlayer->ModifyHonorPoints(-1800);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Field Marshal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1014: // Knight-Lieutenant Title
                if ((pPlayer->GetHonorPoints() >= 3600) && (pPlayer->GetMoney() >=72000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(14))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Marshal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-72000000);
                        pPlayer->ModifyHonorPoints(-3600);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Marshal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1015: // of the Alliance Title
                if ((pPlayer->GetHonorPoints() >= 5000) && (pPlayer->GetMoney() >=100000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(126))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Alliance' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pPlayer->ModifyHonorPoints(-5000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Alliance' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1016: // Justicar Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(48))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Justicar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Justicar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1017: // Flame Warden Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(75))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Flame Warden' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Flame Warden' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1018: // of the Exodar Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(146))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Exodar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Exodar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1019: // of Darnassus Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(147))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Darnassus' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Darnassus' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1020: // of the Ironforge Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(148))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Ironforge' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Ironforge' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1021: // of Stormwind Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(149))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Stormwind' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Stormwind' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 1022: // of Gnomeregan Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(113))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Gnomeregan' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Gnomeregan' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

         pPlayer->CLOSE_GOSSIP_MENU();

        //////////////////////////////////////////////////Horde Titles//////////////////////////////////////////////////////////////////

        case 2001: // Scout Title
                if ((pPlayer->GetHonorPoints() >= 100) && (pPlayer->GetMoney() >=2000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(15))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Scout' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-2000000);
                        pPlayer->ModifyHonorPoints(-100);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Scout' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2002: // Grunt Title
                if ((pPlayer->GetHonorPoints() >= 150) && (pPlayer->GetMoney() >=3000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(16))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grunt' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-3000000);
                        pPlayer->ModifyHonorPoints(-150);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grunt' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2003: // Sergeant Title
                if ((pPlayer->GetHonorPoints() >= 200) && (pPlayer->GetMoney() >=4000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(17))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-4000000);
                        pPlayer->ModifyHonorPoints(-200);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2004: // Senior Sergeant Title
                if ((pPlayer->GetHonorPoints() >= 250) && (pPlayer->GetMoney() >=5000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(18))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Senior Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-5000000);
                        pPlayer->ModifyHonorPoints(-250);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Senior Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2005: // First Sergeant Title
                if ((pPlayer->GetHonorPoints() >= 300) && (pPlayer->GetMoney() >=6000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(19))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'First Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-6000000);
                        pPlayer->ModifyHonorPoints(-300);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'First Sergeant' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2006: // Stone Guard Title
                if ((pPlayer->GetHonorPoints() >= 400) && (pPlayer->GetMoney() >=8000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(20))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Stone Guard' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-8000000);
                        pPlayer->ModifyHonorPoints(-400);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Stone Guard' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2007: // Blood Guard Title
                if ((pPlayer->GetHonorPoints() >= 500) && (pPlayer->GetMoney() >=10000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(21))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Blood Guard' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-10000000);
                        pPlayer->ModifyHonorPoints(-500);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Blood Guard' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2008: // Legionnaire Title
                if ((pPlayer->GetHonorPoints() >= 650) && (pPlayer->GetMoney() >=13000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(22))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Legionnaire' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-13000000);
                        pPlayer->ModifyHonorPoints(-650);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Legionnaire' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2009: // Centurion Title
                if ((pPlayer->GetHonorPoints() >= 800) && (pPlayer->GetMoney() >=16000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(23))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Centurion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-16000000);
                        pPlayer->ModifyHonorPoints(-800);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Centurion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2010: // Champion Title
                if ((pPlayer->GetHonorPoints() >= 1000) && (pPlayer->GetMoney() >=20000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(24))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Champion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pPlayer->ModifyHonorPoints(-1000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Champion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2011: // Lieutenant General Title
                if ((pPlayer->GetHonorPoints() >= 1200) && (pPlayer->GetMoney() >=24000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(25))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Lieutenant General' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-24000000);
                        pPlayer->ModifyHonorPoints(-1200);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Lieutenant General' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2012: // General Title
                if ((pPlayer->GetHonorPoints() >= 1500) && (pPlayer->GetMoney() >=30000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(26))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'General' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-30000000);
                        pPlayer->ModifyHonorPoints(-1500);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'General' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2013: // Warlord Title
                if ((pPlayer->GetHonorPoints() >= 1800) && (pPlayer->GetMoney() >=36000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(27))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Warlord' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-36000000);
                        pPlayer->ModifyHonorPoints(-1800);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Warlord' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2014: // High Warlord Title
                if ((pPlayer->GetHonorPoints() >= 3600) && (pPlayer->GetMoney() >=72000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(28))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'High Warlord' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-72000000);
                        pPlayer->ModifyHonorPoints(-3600);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'High Warlord' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2015: // of the Horde Title
                if ((pPlayer->GetHonorPoints() >= 5000) && (pPlayer->GetMoney() >=100000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(127))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Horde' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pPlayer->ModifyHonorPoints(-5000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Horde' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2016: // Conqueror Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(47))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Conqueror' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Conqueror' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2017: // Flame Keeper Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(76))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Flame Keeper' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Flame Keeper' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2018: // of Orgrimmar Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(150))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Orgrimmar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Orgrimmar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2019: // of Sen'jin Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(151))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Sen'jin' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Sen'jin' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2020: // of Silvermoon Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(152))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Silvermoon' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Silvermoon' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2021: // of Thunder Bluff Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(153))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Thunder Bluff' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Thunder Bluff' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 2022: // of the Undercity Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(154))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Undercity' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Undercity' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        //////////////////////////////////////////////////Neutral Titles///////////////////////////////////////////////////////////////

        case 3001: // Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 100) && (pPlayer->GetMoney() >=2000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(42))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-2000000);
                        pPlayer->ModifyHonorPoints(-100);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3002: // Duelist Title
                if ((pPlayer->GetHonorPoints() >= 200) && (pPlayer->GetMoney() >=4000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(43))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Duelist' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-4000000);
                        pPlayer->ModifyHonorPoints(-200);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Duelist' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3003: // Rival Title
                if ((pPlayer->GetHonorPoints() >= 300) && (pPlayer->GetMoney() >=6000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(44))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Rival' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-6000000);
                        pPlayer->ModifyHonorPoints(-300);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Rival' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3004: // Challenger Title
                if ((pPlayer->GetHonorPoints() >= 400) && (pPlayer->GetMoney() >=8000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(45))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Challenger' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-8000000);
                        pPlayer->ModifyHonorPoints(-400);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Challenger' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3007: // Merciless Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 500) && (pPlayer->GetMoney() >=10000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(62))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Merciless Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-10000000);
                        pPlayer->ModifyHonorPoints(-500);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Merciless Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3010: // Vengeful Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 600) && (pPlayer->GetMoney() >=12000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(71))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Vengeful Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-12000000);
                        pPlayer->ModifyHonorPoints(-600);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Vengeful Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3016: // Brutal Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 700) && (pPlayer->GetMoney() >=14000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(80))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Brutal Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-14000000);
                        pPlayer->ModifyHonorPoints(-700);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Brutal Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3079: // Deadly Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 800) && (pPlayer->GetMoney() >=16000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(157))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Deadly Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-16000000);
                        pPlayer->ModifyHonorPoints(-800);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Deadly Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3088: // Furious Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 900) && (pPlayer->GetMoney() >=18000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(167))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Furious Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-18000000);
                        pPlayer->ModifyHonorPoints(-900);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Furious Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3090: // Relentless Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 1000) && (pPlayer->GetMoney() >=20000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(169))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Relentless Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pPlayer->ModifyHonorPoints(-1000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Relentless Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3098: // Wrathful Gladiator Title
                if ((pPlayer->GetHonorPoints() >= 1200) && (pPlayer->GetMoney() >=24000000))
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(177))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Wrathful Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-24000000);
                        pPlayer->ModifyHonorPoints(-1200);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Wrathful Gladiator' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper(MSG_SHORT_ON_GOLD_OR_HONOR, pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3005: // Scarab Lord Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(46))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Scarab Lord' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Scarab Lord' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3006: // Champion of the Naaru Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(53))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Champion of the Naaru' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Champion of the Naaru' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3008: // of the Shattered Sun Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(63))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Shattered Sun' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Shattered Sun' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3009: // Hand of A'dal Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(64))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Hand of A'dal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Hand of A'dal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3011: // Battlemaster Title
                if (pPlayer->GetMoney() >=150000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(72))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Battlemaster' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-150000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Battlemaster' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3012: // Elder Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(74))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Elder' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Elder' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3013: // the Exalted Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(77))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Exalted' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Exalted' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3014: // the Explorer Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(78))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Explorer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Explorer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3015: // the Diplomat Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(79))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Diplomat' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Diplomat' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3017: // the Seeker Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(81))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Seeker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Seeker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3018: // Arena Master Title
                if (pPlayer->GetMoney() >=150000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(82))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Arena Master' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-150000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Arena Master' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3019: // Salty Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(83))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Salty' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Salty' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3020: // Chef Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(84))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Chef' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Chef' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3021: // the Supreme Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(85))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Supreme' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Supreme' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3022: // of the Ten Storms Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(86))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Ten Storms' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Ten Storms' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3023: // of the Emerald Dream Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(87))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Emerald Dream' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Emerald Dream' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3024: // Prophet Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(89))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Prophet' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Prophet' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3025: // the Malefic Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(90))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Malefic' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Malefic' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3026: // Stalker Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(91))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Stalker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Stalker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3027: // of the Ebon Blade Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(92))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Ebon Blade' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Ebon Blade' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3028: // Archmage Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(93))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Archmage' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Archmage' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3029: // Warbringer Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(94))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Warbringer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Warbringer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3030: // Assassin Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(95))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Assassin' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Assassin' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3031: // Grand Master Alchemist Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(96))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Alchemist' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Alchemist' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3032: // Grand Master Blacksmith Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(97))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Blacksmith' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Blacksmith' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3033: // Iron Chef Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(98))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Iron Chef' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Iron Chef' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3034: // Grand Master Enchanter Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(99))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Enchanter' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Enchanter' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3035: // Grand Master Engineer Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(100))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Engineer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Engineer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3036: // Doctor Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(101))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Doctor' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Doctor' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3037: // Grand Master Angler Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(102))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Angler' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Angler' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3038: // Grand Master Herbalist Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(103))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Herbalist' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Herbalist' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3039: // Grand Master Scribe Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(104))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Scribe' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Scribe' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3040: // Grand Master Jewelcrafter Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(105))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Jewelcrafter' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Jewelcrafter' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3041: // Grand Master Leatherworker Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(106))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Leatherworker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Leatherworker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3042: // Grand Master Miner Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(107))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Miner' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Miner' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3043: // Grand Master Skinner Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(108))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Skinner' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Skinner' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3044: // Grand Master Tailor Title
                if (pPlayer->GetMoney() >=20000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(109))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Master Tailor' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-20000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Master Tailor' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3045: // of Quel'Thalas Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(110))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Quel'Thalas' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Quel'Thalas' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3046: // of Argus Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(111))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Argus' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Argus' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3047: // of Khaz Modan Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(112))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of Khaz Modan' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of Khaz Modan' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3048: // the Lion Hearted Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(114))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Lion Hearted' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Lion Hearted' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3049: // Champion of Elune Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(115))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Champion of Elune' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Champion of Elune' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3050: // Hero of Orgrimmar Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(116))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Hero of Orgrimmar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Hero of Orgrimmar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3051: // Plainsrunner Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(117))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Plainsrunner' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Plainsrunner' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3052: // of the Darkspear Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(118))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Darkspear' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Darkspear' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3053: // the Forsaken Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(119))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Forsaken' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Forsaken' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3054: // the Magic Seeker Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(120))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Magic Seeker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Magic Seeker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3055: // Twilight Vanquisher Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(121))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Twilight Vanquisher' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Twilight Vanquisher' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3056: // Conqueror of Naxxramas Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(122))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Conqueror of Naxxramas' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Conqueror of Naxxramas' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3057: // Hero of Northrend Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(123))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Hero of Northrend' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Hero of Northrend' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3058: // the Hallowed Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(124))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Hallowed' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Hallowed' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3059: // Loremaster Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(125))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Loremaster' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Loremaster' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3060: // the Flawless Victor Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(128))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Flawless Victor' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Flawless Victor' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3061: // the Flawless Victor Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(129))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Champion of the Frozen Wastes' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Champion of the Frozen Wastes' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3062: // Ambassador Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(130))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Ambassador' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Ambassador' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3063: // the Argent Champion Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(131))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Argent Champion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Argent Champion' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3064: // Guardian of Cenarius Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(132))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Guardian of Cenarius' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Guardian of Cenarius' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3065: // Brewmaster Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(133))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Brewmaster' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Brewmaster' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3066: // Merrymaker Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(134))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Merrymaker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Merrymaker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3067: // the Love Fool Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(135))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Love Fool' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Love Fool' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3068: // Matron Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(137))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Matron' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Matron' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3069: // Patron Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(138))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Patron' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Patron' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3070: // Obsidian Slayer Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(139))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Obsidian Slayer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Obsidian Slayer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3071: // of the Nightfall Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(140))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Nightfall' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Nightfall' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3072: // the Immortal Title
                if (pPlayer->GetMoney() >=200000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(141))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Immortal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-200000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Immortal' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3073: // the Undying Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(142))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Undying' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Undying' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3074: // Jenkins Title
                if (pPlayer->GetMoney() >=60000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(143))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Jenkins' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-60000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Jenkins' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3075: // Bloodsail Admiral Title
                if (pPlayer->GetMoney() >=40000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(144))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Bloodsail Admiral' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-40000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Bloodsail Admiral' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3076: // the Insane Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(145))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Insane' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Insane' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3077: // the Noble Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(155))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Noble' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Noble' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3078: // Crusader Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(156))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Crusader' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Crusader' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3080: // Death's Demise Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(158))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Death's Demise' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Death's Demise' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3081: // the Celestial Defender Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(159))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Celestial Defender' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Celestial Defender' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3082: // Conqueror of Ulduar Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(160))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Conqueror of Ulduar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Conqueror of Ulduar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3083: // Champion of Ulduar Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(161))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Champion of Ulduar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Champion of Ulduar' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3084: // Vanquisher Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(163))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Vanquisher' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Vanquisher' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3085: // Starcaller Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(164))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Starcaller' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Starcaller' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3086: // the Astral Walker Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(165))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Astral Walker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Astral Walker' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3087: // Herald of the Titans Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(166))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Herald of the Titans' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Herald of the Titans' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3089: // the Pilgrim Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(168))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Pilgrim' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Pilgrim' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3091: // Grand Crusader Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(170))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Grand Crusader' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Grand Crusader' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3092: // the Argent Defender Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(171))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Argent Defender' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Argent Defender' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3093: // the Patient Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(172))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Patient' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Patient' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3094: // the Light of Dawn Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(173))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Light of Dawn' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Light of Dawn' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3095: // Bane of the Fallen King Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(174))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'Bane of the Fallen King' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'Bane of the Fallen King' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3096: // the Kingslayer Title
                if (pPlayer->GetMoney() >=100000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(175))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'the Kingslayer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-100000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'the Kingslayer' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        case 3097: // of the Ashen Verdict Title
                if (pPlayer->GetMoney() >=80000000)
                {
                    if(CharTitlesEntry const* titleEntry = GetCharTitlesStore() -> LookupEntry(176))
                    if (pPlayer->HasTitle(titleEntry))
                    {
                        pCreature->MonsterWhisper("You already have the 'of the Ashen Verdict' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                    else
                    {
                        pPlayer->SetTitle(titleEntry);
                        pPlayer->ModifyMoney(-80000000);
                        pCreature->MonsterWhisper("Congratulations! You've just gained 'of the Ashen Verdict' Title!", pPlayer, false);
                        pPlayer->CLOSE_GOSSIP_MENU();
                    }
                }
                else
                {
                    pCreature->MonsterWhisper("Not enough Gold!", pPlayer, false);
                    pPlayer->CLOSE_GOSSIP_MENU();
                }
        break;

        pPlayer->CLOSE_GOSSIP_MENU();

    }
}

bool GossipSelect_custom_npc_titlemaster(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Main menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_titlemaster(pPlayer, pCreature, uiAction);

    return true;
}

// tokenvendor
bool GossipHello_custom_npc_tokenvendor(Player* pPlayer, Creature* pCreature)
{
    Config SD2Config;
    if(!SD2Config.SetSource(_SCRIPTDEV2_CONFIG))
        error_log("SD2: Unable to open configuration file");

    pPlayer->ADD_GOSSIP_ITEM( 5, "Exchange 25 BOJ to 10 Gold" , GOSSIP_SENDER_MAIN, 2000);
    if(pPlayer->getLevel() < (SD2Config.GetFloatDefault("TokenVendor.MaxLevel",0)))
        pPlayer->ADD_GOSSIP_ITEM( 5, "40 BOJ Exchange 1 Level" , GOSSIP_SENDER_MAIN, 3000);
    pPlayer->ADD_GOSSIP_ITEM( 5, "20 BOJ Exchange 36 Slot Bag" , GOSSIP_SENDER_MAIN, 4000);
    pPlayer->ADD_GOSSIP_ITEM(5,"5 BOJ Exchange 1 Buff Spell" ,GOSSIP_SENDER_MAIN,5000);
    pPlayer->ADD_GOSSIP_ITEM(5,"10 BOJ Exchange 1 Item Summon Trainer" ,GOSSIP_SENDER_MAIN,6000);
    pPlayer->ADD_GOSSIP_ITEM(5,"10 BOJ Exchange 1 Item Summon Professional" ,GOSSIP_SENDER_MAIN,7000);
    pPlayer->ADD_GOSSIP_ITEM(5,"10 BOJ Exchange 1 Item Summon Tele NPC" ,GOSSIP_SENDER_MAIN,8000);

    pPlayer->SEND_GOSSIP_MENU(3961,pCreature->GetObjectGuid());
    return true;
}

void SendDefaultMenu_custom_npc_tokenvendor(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    uint32 itemBoj = 29434; // Badge of Justice
    uint32 itemId2 = 23162; // 36 bag slot, I suppose ? (Darkiss)
    uint32 noSpaceForCount = 0;
    int32 count = 0;
    int32 count2 = 1;

    Item* item = NULL;

    ItemPosCountVec dest;
    ItemPosCountVec dest2;
    uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemBoj, 0);
    uint8 msg2 = pPlayer->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest2, 23162, 1);

    // Not allowed to use in combat
    if (pPlayer->isInCombat())
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pCreature->MonsterSay("You are in combat", LANG_UNIVERSAL, NULL);
        return;
    }

    switch(uiAction)
    {
        case 2000:
            if(pPlayer->HasItemCount(itemBoj, 25 , true))
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->DestroyItemCount(itemBoj, 25, true);
                pPlayer->ModifyMoney(+100000);
                pCreature->MonsterWhisper("You have just exchanged 25 BOJ to 10 Gold!", pPlayer, false);
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You don't have enough tokens!", LANG_UNIVERSAL, NULL);
            }
        break;

        case 3000:
            if(pPlayer->HasItemCount(itemBoj, 40, true))
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->DestroyItemCount(itemBoj, 40, true);
                pPlayer->GiveLevel(pPlayer->getLevel() + 1);
                pCreature->MonsterWhisper("You have just exchanged 40 BOJ for one level!", pPlayer, false);
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You don't have enough tokens!", LANG_UNIVERSAL, NULL);
            }
        break;

        case 4000:
            if(pPlayer->HasItemCount(itemBoj, 20, true))
            {
            if( msg != EQUIP_ERR_OK )
                count2 -= noSpaceForCount;

            if( count2 == 0 || dest.empty())
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("Error: Item count set to 0. Please inform a GM about this error.", pPlayer, false);
            }

            item = pPlayer->StoreNewItem( dest2, itemId2, true, Item::GenerateItemRandomPropertyId(itemId2));

            if(count2 > 0 && item)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->SendNewItem(item,count2,false,true);
                pPlayer->DestroyItemCount(itemBoj, 20, true);
            }

            if(noSpaceForCount > 0)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterWhisper("You don't have enough free inventory slots", pPlayer, false);
            }
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5000:
            pPlayer->ADD_GOSSIP_ITEM(5,"Arcane Brilliance",GOSSIP_SENDER_MAIN,5001);
            pPlayer->ADD_GOSSIP_ITEM(5,"Greater Blessing of Kings",GOSSIP_SENDER_MAIN,5002);
            pPlayer->ADD_GOSSIP_ITEM(5,"Gift of the Wild",GOSSIP_SENDER_MAIN,5003);
            pPlayer->ADD_GOSSIP_ITEM(5,"Dalaran Brilliance",GOSSIP_SENDER_MAIN,5004);
            pPlayer->ADD_GOSSIP_ITEM(5,"Greater Blessing of Might",GOSSIP_SENDER_MAIN,5005);
            pPlayer->ADD_GOSSIP_ITEM(5,"Greater Blessing of Sanctuary",GOSSIP_SENDER_MAIN,5006);
            pPlayer->ADD_GOSSIP_ITEM(5,"Greater Blessing of Wisdom",GOSSIP_SENDER_MAIN,5007);
            pPlayer->ADD_GOSSIP_ITEM(5,"Prayer of Fortitude",GOSSIP_SENDER_MAIN,5008);
            pPlayer->ADD_GOSSIP_ITEM(5,"Prayer of Shadow Protection",GOSSIP_SENDER_MAIN,5009);
            pPlayer->ADD_GOSSIP_ITEM(5,"Prayer of Spirit",GOSSIP_SENDER_MAIN,5010);

            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
        break;

        case 5001:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pPlayer->CastSpell(pPlayer,43002,true);
            pPlayer->DestroyItemCount(itemBoj, 5, true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5002:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pCreature->CastSpell(pPlayer,25898,false);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5003:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pPlayer->CastSpell(pPlayer,48470,true);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5004:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pPlayer->CastSpell(pPlayer,61316,true);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5005:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pCreature->CastSpell(pPlayer,48934,false);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5006:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pCreature->CastSpell(pPlayer,25899,false);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5007:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pCreature->CastSpell(pPlayer,48938,false);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5008:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pPlayer->CastSpell(pPlayer,48162,true);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5009:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pPlayer->CastSpell(pPlayer,48170,true);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 5010:
            if(pPlayer->HasItemCount(itemBoj,5,true))
            {
            pPlayer->ADD_GOSSIP_ITEM(5,"<--Back",GOSSIP_SENDER_MAIN,5000);
            pPlayer->CastSpell(pPlayer,48074,true);
            pPlayer->DestroyItemCount(itemBoj,5,true);
            pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
            }
            else
            {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 6000:
            if(pPlayer->HasItemCount(itemBoj, 10, true))
            {
                if( msg != EQUIP_ERR_OK )
                    count2 -= noSpaceForCount;

                if( count2 == 0 || dest.empty())
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("Error: Item count set to 0. Please inform a GM about this error.", pPlayer, false);
                }

                item = pPlayer->StoreNewItem( dest2, 90010, true, Item::GenerateItemRandomPropertyId(90010));

                if(count2 > 0 && item)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->SendNewItem(item,count2,false,true);
                    pPlayer->DestroyItemCount(itemBoj, 10, true);
                }

                if(noSpaceForCount > 0)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("You don't have enough free inventory slots", pPlayer, false);
                }
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 7000:
            if(pPlayer->HasItemCount(itemBoj, 10, true))
            {
                if( msg != EQUIP_ERR_OK )
                    count2 -= noSpaceForCount;

                if( count2 == 0 || dest.empty())
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("Error: Item count set to 0. Please inform a GM about this error.", pPlayer, false);
                }

                item = pPlayer->StoreNewItem( dest2, 90005, true, Item::GenerateItemRandomPropertyId(90005));

                if(count2 > 0 && item)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->SendNewItem(item,count2,false,true);
                    pPlayer->DestroyItemCount(itemBoj, 10, true);
                }

                if(noSpaceForCount > 0)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("You don't have enough free inventory slots", pPlayer, false);
                }
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;

        case 8000:
            if(pPlayer->HasItemCount(itemBoj, 10, true))
            {
                if( msg != EQUIP_ERR_OK )
                    count2 -= noSpaceForCount;

                if( count2 == 0 || dest.empty())
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("Error: Item count set to 0. Please inform a GM about this error.", pPlayer, false);
                }

                item = pPlayer->StoreNewItem( dest2, 8, true, Item::GenerateItemRandomPropertyId(8));

                if(count2 > 0 && item)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pPlayer->SendNewItem(item,count2,false,true);
                    pPlayer->DestroyItemCount(itemBoj, 10, true);
                }

                if(noSpaceForCount > 0)
                {
                    pPlayer->CLOSE_GOSSIP_MENU();
                    pCreature->MonsterWhisper("You don't have enough free inventory slots", pPlayer, false);
                }
            }
            else
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                pCreature->MonsterSay("You don't have enough tokens", LANG_UNIVERSAL, NULL);
            }
        break;
    }
}

bool GossipSelect_custom_npc_tokenvendor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    // Main menu
    if (uiSender == GOSSIP_SENDER_MAIN)
        SendDefaultMenu_custom_npc_tokenvendor(pPlayer, pCreature, uiAction);

    return true;
}

//custom training dumby
#define OUT_OF_COMBAT_TIME 5000

struct MANGOS_DLL_DECL custom_script_training_dummyAI : public Scripted_NoMovementAI
{
    uint32 combat_timer;

    custom_script_training_dummyAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
        combat_timer = 0;
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        combat_timer = 0;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        m_creature->ModifyHealth(m_creature->GetMaxHealth());

        combat_timer += diff;
        if (combat_timer > OUT_OF_COMBAT_TIME)
            EnterEvadeMode();
    }
};

CreatureAI* GetAI_custom_script_training_dummy(Creature* pCreature)
{
    return new custom_script_training_dummyAI(pCreature);
}

void AddSC_custom_npcs()
{
    Script *newscript;

    newscript                   = new Script;
    newscript->Name             = "custom_npc_buffmaster";
    newscript->pGossipHello     = &GossipHello_custom_npc_buffmaster;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_buffmaster;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_guildmaster";
    newscript->pGossipHello     = &GossipHello_custom_npc_guildmaster;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_guildmaster;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_news";
    newscript->pGossipHello     = &GossipHello_custom_npc_news;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_news;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_professionmaster";
    newscript->pGossipHello     = &GossipHello_custom_npc_professionmaster;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_professionmaster;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_renamecharacter";
    newscript->pGossipHello     = &GossipHello_custom_npc_renamecharacter;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_renamecharacter;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_resetinstance";
    newscript->pGossipHello     = &GossipHello_custom_npc_resetinstance;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_resetinstance;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_resetlevel";
    newscript->pGossipHello     = &GossipHello_custom_npc_resetlevel;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_resetlevel;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_spellmaster";
    newscript->pGossipHello     = &GossipHello_custom_npc_spellmaster;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_spellmaster;
    newscript->RegisterSelf(false);

    newscript                  = new Script;
    newscript->Name            = "custom_npc_teleportmaster";
    newscript->pGossipHello    = &GossipHello_custom_npc_teleportmaster;
    newscript->pGossipSelect   = &GossipSelect_custom_npc_teleportmaster;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_titlemaster";
    newscript->pGossipHello     = &GossipHello_custom_npc_titlemaster;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_titlemaster;
    newscript->RegisterSelf(false);

    newscript                   = new Script;
    newscript->Name             = "custom_npc_tokenvendor";
    newscript->pGossipHello     = &GossipHello_custom_npc_tokenvendor;
    newscript->pGossipSelect    = &GossipSelect_custom_npc_tokenvendor;
    newscript->RegisterSelf(false);

    newscript = new Script;
    newscript->Name = "custom_script_training_dummy";
    newscript->GetAI = &GetAI_custom_script_training_dummy;
    newscript->RegisterSelf(false);
}