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
SD%Complete:
SDComment:
SDCategory: Sunwell Plateau
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

enum spells // Boss spells
{
    ENRAGE                      = 26662,
    SPELL_NEGATIVE              = 46285, //negative energy -> deals damage
    SPELL_NEGATIVEENERGY        = 46008, //negative energy -> black beams
    SPELL_NEGATIVE_ENERGY       = 46009, //(this trigger 46008)
    SPELL_NEGATIVEENERGY_CHAIN  = 46289, //negative energy ->

    AURA_SINGULARITY            = 46228, //black hole passive  visual effect
    AURA_SUNWELL_RADIANCE       = 45769,

    DARKNESS                    = 45996, // darkness
    //SPELL_DARKNESS              = 45999,
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

/* NPC list refenece
	NPC_PORTAL_TARGET           = 25770,

    NPC_ENTROPIUS               = 25840,
    NPC_SHADOW_FURY_MAGE        = 25799,
    NPC_SHADOW_BERSERKER        = 25798,
    NPC_VOID_SENTINEL           = 25772,
    NPC_VOID_SPAWN              = 25824,
    NPC_DARK_FIEND              = 25744,
    NPC_SINGULARITY             = 25855,
    NPC_DARKNESS                = 25879,
*/

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
    ID_DARK_FIEND               = 25744, // dark fiend
    ID_VOID_SENTINEL            = 25772, // void sentinel
    ID_SINGULARITY              = 25855, // visual effect
    ID_SPAWN                    = 25824, // void spawn
};

//Boss sounds
#define SOUND_CHANGE_PHASE 12560
//#define SAY_ENTROPIUS_SUMMON	??????

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

/*  -- might use these locs
float DarkFiends[8][4] =
{
    {1819.9f,    609.80f,    69.74f,    1.94f},
    {1829.39f,   617.89f,    69.73f,    2.61f},
    {1801.98f,   633.62f,    69.74f,    5.71f},
    {1830.88f,   629.99f,    69.73f,    3.52f},
    {1800.38f,   621.41f,    69.74f,    0.22f},
    {1808.3f ,   612.45f,    69.73f,    1.02f},
    {1823.9f ,   639.69f,    69.74f,    4.12f},
    {1811.85f,   640.46f,    69.73f,    4.97f}
};

float Humanoides[6][5] =
{
    {CREATURE_FURY_MAGE, 1780.16f,    666.83f,    71.19f,    5.21f},
    {CREATURE_FURY_MAGE, 1847.93f,    600.30f,    71.30f,    2.57f},
    {CREATURE_BERSERKER, 1779.97f,    660.64f,    71.19f,    5.28f},
    {CREATURE_BERSERKER, 1786.2f ,    661.01f,    71.19f,    4.51f},
    {CREATURE_BERSERKER, 1845.17f,    602.63f,    71.28f,    2.43f},
    {CREATURE_BERSERKER, 1842.91f,    599.93f,    71.23f,    2.44f}
};
*/

void AddSC_boss_muru()
{
}
