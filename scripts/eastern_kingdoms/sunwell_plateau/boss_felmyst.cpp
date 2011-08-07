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
    SAY_INTRO           = -1580036,
    SAY_KILL_1          = -1580037,
    SAY_KILL_2          = -1580038,
    SAY_DEATH           = -1580042,
    SAY_TAKEOFF         = -1580040,
    SAY_BREATH          = -1580039,
    SAY_BERSERK         = -1580041,
    SAY_KALECGOS_OUTRO  = -1580043,
};

enum TransformFelmystOutro
{
    SPELL_TRANSFORM_TRIGGER        = 44885,   // madrigosa to self, trigger 46350
    SPELL_TRANSFORM_VISUAL         = 46350,   // 46411stun?
    SPELL_TRANSFORM_FELMYST        = 45068,   // become fel
    SPELL_FELMYST_SUMMON           = 45069,
};

void AddSC_boss_felmyst()
{
}
