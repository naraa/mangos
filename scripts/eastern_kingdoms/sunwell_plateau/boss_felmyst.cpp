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
SD%Complete: 80%
SDComment:
SDCategory: Sunwell Plateau
EndScriptData */

/* Status
GroundPhase = 95%
FlyingPhase = 95%
DeathCloud  = 50%
Demonic Vapor = 90%
Madrigosa_transform/outro = 95%  // missing graphics and minor
*/

#include "precompiled.h"
#include "sunwell_plateau.h"
#include "../../../game/TemporarySummon.h"

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
	SPELL_ENRAGE                = 26662, // ?? SPELL_BERSERK = 45078,

    //Land Phase
    SPELL_CLEAVE                = 19983,
    SPELL_CORROSION             = 45866,
    SPELL_GASNOVA               = 45855,
    SPELL_ENCAPSULATE           = 45665,
    SPELL_ENCAPSULATE_AOE       = 45662,
    SPELL_ENCAPSULATE_CHANNEL   = 45661,

    //Flight Phase
//fog(deathcloud)
    SPELL_FOG_OF_CORRUPTION     = 45582, // Visual Effect (fog to self, trigger 45782)
    SPELL_FOG_CHARM             = 45717, // fel to player
    PELL_FOG_BREATH             = 45495,   // fel to self, speed burst
    SPELL_FOG_TRIGGER           = 45582,   // fog to self, trigger 45782
    SPELL_FOG_FORCE             = 45782,   // fog to player, force cast 45714
    SPELL_FOG_INFORM            = 45714,   // player let fel cast 45717, script effect
    SPELL_FOG_CHARM2            = 45726,   // link to 45717

    //SPELL_SOUL_SEVER            = 45917,
//demonic vapor

// Handle mostly by DB here as a refence
    SPELL_VAPOR_TRIGGER         = 45411, // linked to 45389, vapor to self, trigger 45410 and 46931
    SPELL_DEMONIC_VAPOR_TRIGG   = 45399, // trail to self, trigger 45402
    SPELL_SUMMON_VAPOR_TRIAL    = 45410, // vapor summon trail
    SPELL_VAPOR_DAMAGE          = 46931, // vapor damage, 4000
    SPELL_VAPOR_TRAIL_DAMAGE    = 45402, // trail damage, 2000 + 2000 dot
// Handle mostly by DB here as a refence

    SPELL_START_VAPOR           = 45391, // demonic vapor start spell (fel to player, force cast 45392, 50000y select target)
    SPELL_VAPOR_SUMMON          = 45392, // player summon vapor, radius around caster, 5y,
    SPELL_SUMMON_DEATH          = 45400, // demonic vapor, unyielding death summon (5 mins)

    SPELL_DEAD_PASSIVE          = 45415,

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
    {1489.307f, 701.451f, 40.5f},   // right - 0
    {1447.672f, 649.917f, 40.5f},   // right - 1
    {1430.092f, 604.318f, 40.5f},   // center - 2
    {1462.899f, 536.334f, 40.5f},   //left - 3
    {1537.197f, 522.199f, 40.5f},   // left - 4
};

/*######
## boss_felmyst
######*/

struct MANGOS_DLL_DECL boss_felmystAI : public ScriptedAI
{
    boss_felmystAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        m_bHasChecked = false;
        Reset();
    }

    ScriptedInstance* m_pInstance;

    //timers,bools,ect\\

// Ground Phase
    uint32 m_uiCorrosionTimer;
    uint32 m_uiCleaveTimer;
    ObjectGuid m_uiEncapsulateGUID;
    uint32 m_uiEncapsulateTimer;
    uint32 m_uiGasNovaTimer;
    uint32 m_uiFlyPhaseTimer;
//Flying phase
    uint8  m_uiBreathCount;    // 3 breath attacks a air phase(deathCloud Attacks)
    uint8  m_uiVaporCount;     // 2 of these attacks during air phase
    uint32 m_uiLastPointId;
    uint32 m_uiDemonicVaporTimer;
    uint32 m_uiFogOfCorruptionTimer;
    uint32 m_uiFogSummonTimer;
    bool m_bIsBreath;
    bool m_bDemonicVapor;

// Special Timers and Stuff
    uint8 m_uiPhase;
    uint32 m_uiMovemetnTimer;
    uint32 m_uiEncounterCheckTimer;
    bool m_bHasChecked;

    void Reset()
    {
// Special Timers and Stuff Reset
        m_uiPhase               = PHASE_IDLE;
        m_uiEncounterCheckTimer = 10000;
        m_uiMovemetnTimer       = 11000;
//Ground Phase Timers Reset
        m_uiCorrosionTimer      = 10000;
        m_uiCleaveTimer         = 4000;
        m_uiGasNovaTimer        = 20000;
        m_uiEncapsulateTimer    = 15000;
        m_uiEncapsulateGUID.Clear();
        m_uiFlyPhaseTimer       = 60000;
//Flying Phase
        m_uiFogOfCorruptionTimer = 30000;
        m_uiFogSummonTimer       = 1000;
        m_bIsBreath              = false;
        m_uiDemonicVaporTimer    = 10000;
        m_uiVaporCount           = 0;
        m_uiBreathCount          = 0;
//ect Resets
        if (!m_creature->HasAura(SPELL_SUNWELL_RADIANCE_AURA))
            DoCast(m_creature, SPELL_SUNWELL_RADIANCE_AURA);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
           m_pInstance->SetData(TYPE_FELMYST, NOT_STARTED);
    }

    void Aggro(Unit *pWho)
    {
        m_uiPhase = PHASE_GROUND;
        m_creature->SetInCombatWithZone();
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
        //m_creature->SetLevitate(false);
        DoCast(m_creature, SPELL_NOXIOUSFUMES);    // needs to not target boss only players from raid
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FELMYST, IN_PROGRESS);
    }

    void AttackStart(Unit* pWho)
    {
        if (m_pInstance->GetData(TYPE_BRUTALLUS) != DONE)
            return;

        if (!pWho)
            return;

        if (m_creature->Attack(pWho, true))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);
            DoStartMovement(pWho);
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        //won't yell killing pet/other unit
        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        switch(rand()%2)
        {
            case 0: DoScriptText(YELL_SLAY1, m_creature); break;
            case 1: DoScriptText(YELL_SLAY2, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(YELL_DEATH, m_creature);

        //if (Creature* pKalecgos = m_creature->SummonCreature(NPC_KALECGOS, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ() + 30, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 20000))
            //DoScriptText(YELL_KALECGOS, pKalecgos);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FELMYST, DONE);
    }

     void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == 1 && m_uiPhase == PHASE_IDLE)
            m_uiMovemetnTimer = 300;

        if (uiPointId == 1 && m_uiPhase == PHASE_AIR)
        {
            m_bIsBreath = false;
            m_uiFogOfCorruptionTimer = 5000;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiPhase == PHASE_IDLE)
        {
            // make boss visible & Transform after brutallus is defeated
            if (m_pInstance && m_pInstance->GetData(TYPE_BRUTALLUS) == DONE && m_pInstance->GetData(TYPE_FELMYST) == NOT_STARTED)
            {
                if (m_uiEncounterCheckTimer < uiDiff && !m_bHasChecked)
                {
                    //m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    DoScriptText(YELL_REBIRTH, m_creature);
// need to figure out how the graphic and brutal blood graphics and ect work ere
                   // DoCast(m_creature, SPELL_TRANSFORM_TRIGGER);
                   // DoCast(m_creature, SPELL_TRANSFORM_VISUAL);
                    DoCast(m_creature, SPELL_TRANSFORM_FELMYST);
                    if (Creature* pMadrigosa = m_pInstance->GetSingleCreatureFromStorage(NPC_MADRIGOSA))
                        pMadrigosa->ForcedDespawn();
                    m_bHasChecked = true;
                    // start flying
                    m_creature->SetLevitate(true);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
                    m_uiLastPointId = urand(0, 4);
                    m_creature->GetMotionMaster()->MovePoint(1, MoveLoc[m_uiLastPointId].x, MoveLoc[m_uiLastPointId].y, MoveLoc[m_uiLastPointId].z);
                    m_uiMovemetnTimer = 60000;
                }
                else m_uiEncounterCheckTimer -= uiDiff;
            }

            if (m_uiMovemetnTimer < uiDiff && m_bHasChecked)
            {
				m_creature->SetLevitate(true);
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
                // movement
                if (m_uiLastPointId < 2)
                    m_uiLastPointId = urand(2, 4);
                else if (m_uiLastPointId > 2)
                    m_uiLastPointId = urand(0, 2);
                else while (m_uiLastPointId == 2)
                    m_uiLastPointId = urand(0, 4);
                m_creature->GetMotionMaster()->MovePoint(1, MoveLoc[m_uiLastPointId].x, MoveLoc[m_uiLastPointId].y, MoveLoc[m_uiLastPointId].z);
                m_uiMovemetnTimer = 60000;
            }
            else m_uiMovemetnTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

// Ground Phase
        if (m_uiPhase == PHASE_GROUND)
        {
            m_creature->SetLevitate(false);
            if (m_uiCleaveTimer < uiDiff)
            {
                DoCast(m_creature->getVictim(), SPELL_CLEAVE);
                m_uiCleaveTimer = urand(4000, 6000);
            }
            else m_uiCleaveTimer -= uiDiff;

            if (m_uiCorrosionTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
                    DoCast(pTarget, SPELL_CORROSION);
                m_uiCorrosionTimer = urand(15000, 20000);
            }
            else m_uiCorrosionTimer -= uiDiff;

            if (m_uiGasNovaTimer < uiDiff)
            {
                DoCast(m_creature, SPELL_GASNOVA);
                m_uiGasNovaTimer = urand(3000, 35000);
            }
            else m_uiGasNovaTimer -= uiDiff;

            if (m_uiEncapsulateTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    m_uiEncapsulateGUID = pTarget->GetObjectGuid();
                    DoCastSpellIfCan(pTarget, SPELL_ENCAPSULATE_CHANNEL);
                    pTarget->CastSpell(pTarget, SPELL_ENCAPSULATE, true);
                    pTarget->CastSpell(pTarget, SPELL_ENCAPSULATE_AOE, true);
                }
                m_uiEncapsulateTimer = 30000;
            }
            else m_uiEncapsulateTimer -= uiDiff;

            if (m_uiFlyPhaseTimer < uiDiff)
            {
                m_creature->GetMotionMaster()->Clear();
                SetCombatMovement(false);
                m_creature->SetLevitate(true);
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
                m_uiLastPointId = urand(0, 4);
                m_creature->GetMotionMaster()->MovePoint(0, MoveLoc[m_uiLastPointId].x, MoveLoc[m_uiLastPointId].y, MoveLoc[m_uiLastPointId].z);
                DoScriptText(YELL_TAKEOFF, m_creature);
                m_uiPhase = PHASE_AIR;
                m_uiDemonicVaporTimer       = 10000;
                m_uiFogOfCorruptionTimer    = 35000;
                m_uiBreathCount             = 0;
                m_uiVaporCount              = 0;
            }
            else m_uiFlyPhaseTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }

// Air phase
        else if (m_uiPhase == PHASE_AIR)
        {
            if (m_uiFogOfCorruptionTimer < uiDiff)
            {
                ++m_uiBreathCount;
                if (m_uiBreathCount == 3)
                {
                    SetCombatMovement(true);
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_creature->SetLevitate(false);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    m_uiPhase = PHASE_GROUND;
                    m_uiFlyPhaseTimer = 60000;
                    return;
                }
                else
                {
                    DoScriptText(YELL_BREATH, m_creature);
                    m_uiFogSummonTimer = 1000;
                    m_uiFogOfCorruptionTimer = 60000;
                    m_bIsBreath = true;
                    // movement
                    if (m_uiLastPointId < 2)
                        m_uiLastPointId = urand(2, 4);
                    else if (m_uiLastPointId > 2)
						m_uiLastPointId = urand(0, 2);
                    else while (m_uiLastPointId == 2)
                        m_uiLastPointId = urand(0, 4);
                    m_creature->GetMotionMaster()->MovePoint(1, MoveLoc[m_uiLastPointId].x, MoveLoc[m_uiLastPointId].y, MoveLoc[m_uiLastPointId].z);
                }
            }
            else m_uiFogOfCorruptionTimer -= uiDiff;

            if (m_uiFogSummonTimer < uiDiff && m_bIsBreath)
            {
                DoCast(m_creature, SPELL_SUMMON_DEATH_CLOUD);
                //m_creature->SummonCreature(NPC_DEATH_CLOUD, m_creature->GetPositionX(), m_creature->GetPositionY(), 25.5f, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
                m_uiFogSummonTimer = 2000;
            }
            else m_uiFogSummonTimer -= uiDiff;

// need to implent only 2 of these per air phase
            if (m_uiDemonicVaporTimer < uiDiff && m_uiVaporCount <= 2)
            {
                m_bDemonicVapor = true;

                if (m_uiVaporCount < 2)
                    DoCast(m_creature, SPELL_START_VAPOR);

                if (m_uiVaporCount++ == 2)
                {
                    SetCombatMovement(true);
                    m_bDemonicVapor      = false;
                    m_creature->GetMotionMaster()->Clear();
                }
                else
                    m_uiDemonicVaporTimer=10000;
            }
            else m_uiDemonicVaporTimer -= uiDiff;

            if (m_bDemonicVapor)
            {
                m_creature->StopMoving();
                SetCombatMovement(false);
            }
        }
    }
};

CreatureAI* GetAI_boss_felmyst(Creature *pCreature)
{
    return new boss_felmystAI(pCreature);
}

/*######
## felmyst_vapor
######*/

enum Beams
{
    SPELL_VAPOR_BEAM            = 45389, // fel to vapor, green beam channel
    SPELL_FELMYST_FORCE_BEAM    = 45388, // demonic vapor, force beam cast spell ( vapor to fel, force cast 45389 )
};

struct MANGOS_DLL_DECL npc_felmyst_vaporAI : public ScriptedAI
{
    npc_felmyst_vaporAI(Creature* pCreature) : ScriptedAI(pCreature)
   {
       m_creature->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 0.0f);
       m_creature->SetFloatValue(UNIT_FIELD_COMBATREACH, 0.0f );
       m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
       Reset();
   }

    ScriptedInstance* m_pInstance;
    ObjectGuid m_uiFelmystGuid;

    void Reset()
    {

        m_uiFelmystGuid.Clear();

        // workaround, to select a close victim (== summoner in this case)
        if (m_creature->IsTemporarySummon())
            AttackStart(m_creature->GetMap()->GetUnit(((TemporarySummon*)m_creature)->GetCreatorGuid()));

        // force felmyst to cast visual beam
        //DoCast(m_creature, SPELL_FELMYST_FORCE_BEAM, true);  // needs to be targeting/casting at fel
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // ignore threat list
        if (!m_creature->getVictim())
        {
            Unit* pTarget =  GetClosestAttackableUnit(m_creature, 100.0f);  // maybe we need to exclude pets?
            // unsummon if no unit is present
            if (!pTarget && m_creature->IsTemporarySummon())
                ((TemporarySummon*)m_creature)->UnSummon();
            AttackStart(pTarget);
        }

        if (Creature* pFelmyst = m_pInstance->GetSingleCreatureFromStorage(NPC_FELMYST))
            m_uiFelmystGuid = pFelmyst->GetObjectGuid();

        if (Creature* pFelmyst = m_pInstance->instance->GetCreature(m_uiFelmystGuid))
        {
            m_creature->SetInCombatWith(pFelmyst);
            m_creature->AddThreat(pFelmyst, 10000.0f);
            m_creature->CastSpell(pFelmyst, SPELL_FELMYST_FORCE_BEAM, true);
            pFelmyst->SetInCombatWith(m_creature);
            pFelmyst->AddThreat(m_creature, 10000.0f);
            pFelmyst->CastSpell(m_creature, SPELL_VAPOR_BEAM, true);
        }

        // no melee attack
    }
};

CreatureAI* GetAI_npc_felmyst_vapor(Creature* pCreature)
{
    return new npc_felmyst_vaporAI(pCreature);
}

/*######
## felmyst_vapor_Cloud  ==  this is the cloud(npc) left behind by the demonic vapor beam attack
######*/

struct MANGOS_DLL_DECL npc_felmyst_vapor_cloudAI : public ScriptedAI
{
    npc_felmyst_vapor_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        SetCombatMovement(false);
    }

    uint32 m_summonTimer;
    uint32 m_createSkeletonTimer;
    uint32 m_cloudlifeTimer;

    void Reset()
    {
        // some delay to give a chance to flee from the skeletons
        m_createSkeletonTimer = 5000;
        m_summonTimer = 1500;
        m_cloudlifeTimer = 25000;
    }

    // CreatureNullAI
    void AttackStart(Unit *) {}
    void AttackedBy( Unit *) {}
    void EnterEvadeMode() {}

    void MoveInLineOfSight(Unit* pWho)    // change this and use void update INTERACTION_DISTANCE to player from Vapor cloud to spawn skellys
    {
        // summon skeleton if unit is close
        if (!m_summonTimer && m_creature->IsHostileTo(pWho) && m_creature->IsWithinDistInMap(pWho, 3))
        {
            // 50% chance - to not make spawns to much as there are many of this mobs in a VaporCloud
            if (!urand(0,2))
                m_creature->SummonCreature(NPC_UNYELDING_DEAD,m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),m_creature->GetOrientation(),TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,10000);
                //DoCast(pWho, SPELL_SUMMON_DEATH, true);  // needs tested
            m_summonTimer = 1000;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // on-create summon
        if (m_createSkeletonTimer)
        {
            m_createSkeletonTimer -= uiDiff;
            if (m_createSkeletonTimer <= 0)
            {
                m_creature->SummonCreature(NPC_UNYELDING_DEAD,m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),m_creature->GetOrientation(),TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,10000);
                //DoCast(m_creature, SPELL_SUMMON_DEATH, true);  //needs tested
                m_createSkeletonTimer = 0;
            }
        }

        // movement cooldown
        if (m_summonTimer)
        {
            m_summonTimer -= uiDiff;
            if (m_summonTimer <= 0)
                m_summonTimer = 0;
        }

        //despawn after 25 seconds
        if(m_cloudlifeTimer < uiDiff)
        {
            m_creature->ForcedDespawn();
        } else m_cloudlifeTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_felmyst_vapor_cloud(Creature* pCreature)
{
    return new npc_felmyst_vapor_cloudAI(pCreature);
}

/*######
## mob_fog_of_corruption
######*/

struct MANGOS_DLL_DECL npc_fog_of_corruptionAI : public Scripted_NoMovementAI
{
    npc_fog_of_corruptionAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_FoglifeTimer;

    void Reset()
    {
        m_FoglifeTimer = 25000;
        DoCast(m_creature, SPELL_FOG_OF_CORRUPTION);
    }

	void AttackStart(Unit* pWho)
	{
        return;
	}

	void MoveInLineOfSight(Unit* pWho)
	{
        if(pWho->GetTypeId() == TYPEID_PLAYER && !pWho->HasAura(SPELL_FOG_CHARM, EFFECT_INDEX_0) && pWho->IsWithinDist2d(m_creature->GetPositionX(), m_creature->GetPositionY(), 20.0f))
        {
            //pWho->CastSpell(pWho, SPELL_FOG_CHARM, false);
           // pWho->CastSpell(pWho, SPELL_SOUL_SEVER, false);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //despawn after 25 seconds
        if(m_FoglifeTimer < uiDiff)
        {
            m_creature->ForcedDespawn();
        } else m_FoglifeTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_fog_of_corruption(Creature* pCreature)
{
    return new npc_fog_of_corruptionAI(pCreature);
}

void AddSC_boss_felmyst()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_felmyst";
    pNewScript->GetAI = &GetAI_boss_felmyst;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="npc_felmyst_vapor";
    pNewScript->GetAI = &GetAI_npc_felmyst_vapor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="npc_felmyst_vapor_cloud";
    pNewScript->GetAI = &GetAI_npc_felmyst_vapor_cloud;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_fog_of_corruption";
    pNewScript->GetAI = &GetAI_npc_fog_of_corruption;
    pNewScript->RegisterSelf();
}