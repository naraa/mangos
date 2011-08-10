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
SDName: boss_felmyst
SD%Complete:
SDComment: END_OUTRO not made. Script for Outro Madrigosa to be added here and the transform
SDCategory: Sunwell Plateau
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

enum Texts
{
    YELL_REBIRTH        = -1580036,
    YELL_SLAY1          = -1580037,
    YELL_SLAY2          = -1580038,
    YELL_DEATH          = -1580042,
    YELL_TAKEOFF        = -1580040,
    YELL_BREATH         = -1580039,
    YELL_BERSERK        = -1580041,
    YELL_KALECGOS       = -1580043,
};

enum NpcsUsed
{
    //NPC_KALECGOS          = 25319,  //summon after fight

    NPC_UNYELDING_DEAD    = 25268,

    NPC_FELMYST_VISUAL    = 25041,
    NPC_FLIGHT_LEFT       = 25357,
    NPC_FLIGHT_RIGHT      = 25358,

    NPC_VAPOR             = 25265,
    NPC_VAPOR_TRAIL       = 25267,
    NPC_DEATH_CLOUD       = 25703,
};

enum Phasezs
{
    PHASE_IDLE       = 0,
    PHASE_GROUND     = 1,
    PHASE_AIR        = 2,
};

enum SpellsUsed
{
    //Mics
    SPELL_NOXIOUSFUMES			= 47002,
	SPELL_ENRAGE                = 26662,

    //Land Phase
    SPELL_CLEAVE                = 19983,
    SPELL_CORROSION             = 45866,
    SPELL_GASNOVA               = 45855,
    SPELL_ENCAPSULATE           = 45665,
    SPELL_ENCAPSULATE_CHANNEL   = 45661,

    //Flight Phase
    SPELL_DEMONIC_VAPOR_TRIGG   = 45399,
    SPELL_FOG_OF_CORRUPTION     = 45582,  // Visual Effect
    SPELL_FOG_CHARM             = 45717,  // Damage, Speed Increased
    SPELL_SOUL_SEVER            = 45917,
    SPELL_SUMMON_VAPOR          = 45391,  // demonic vapor start spell
    SPELL_SUMMON_VAPOR_TRIAL    = 45410,
    SPELL_SUMMON_DEATH          = 45400, // demonic vapor, unyielding death summon
    SPELL_VAPOR_BEAM            = 45389,
    SPELL_FELMYST_FORCE_BEAM    = 45388, // demonic vapor, force beam cast spell

    // fog
    SPELL_DEATH_COULD_VISUAL    = 45212,
    SPELL_SUMMON_DEATH_CLOUD    = 45884,
};

enum TransformFelmystOutro
{
    SPELL_TRANSFORM_TRIGGER        = 44885,   // madrigosa to self, trigger 46350
    SPELL_TRANSFORM_VISUAL         = 46350,   // 46411stun?
    SPELL_TRANSFORM_FELMYST        = 45068,   // become fel
    SPELL_FELMYST_SUMMON           = 45069,
};

//Positional defines
struct LocationsXY
{
    float x, y, z;
    uint32 id;
};

// Movement coordinates
static LocationsXY MoveLoc[]=
{
	{1489.307f, 701.451f, 40.5f},	// right - 0
	{1447.672f, 649.917f, 40.5f},
	{1430.092f, 604.318f, 40.5f},	// center - 2
	{1462.899f, 536.334f, 40.5f},
	{1537.197f, 522.199f, 40.5f},	// left - 4
};

void AddSC_boss_felmyst()
{
}
