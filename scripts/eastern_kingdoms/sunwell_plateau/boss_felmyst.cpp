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
SD%Complete: 30%
SDComment:
SDCategory: Sunwell Plateau
EndScriptData */

/* Status
GroundPhase = 60%
FlyingPhase = 0%
DeathCloud  = 0%
Demonic Vapor = 0%
Madrigosa_transform/outro = 95%  // missing graphics and minor
*/

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
//Flying phase

    // Nothing Yet

// Special Timers and Stuff
    uint8 m_uiPhase;
    uint32 m_uiEncounterCheckTimer;
    bool m_bHasChecked;

    void Reset()
    {
// Special Timers and Stuff Reset
        m_uiPhase               = PHASE_IDLE;
        m_uiEncounterCheckTimer = 10000;
//Ground Phase Timers Reset
        m_uiCorrosionTimer      = 10000;
        m_uiCleaveTimer         = 4000;
        m_uiGasNovaTimer        = 20000;
        m_uiEncapsulateTimer    = 15000;
        m_uiEncapsulateGUID.Clear();
//Flying Phase
        // Nothing Yet

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
        m_creature->SetLevitate(false);
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

    void KilledUnit(Unit* victim)
    {
        switch(rand()%2)
        {
            case 0: DoScriptText(YELL_SLAY1, m_creature); break;
            case 1: DoScriptText(YELL_SLAY2, m_creature); break;
        }
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(YELL_DEATH, m_creature);

        //if (Creature* pKalecgos = m_creature->SummonCreature(NPC_KALECGOS, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ() + 30, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 20000))
            //DoScriptText(YELL_KALECGOS, pKalecgos);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_FELMYST, DONE);
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
                }
                else m_uiEncounterCheckTimer -= uiDiff;
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

// Ground Phase
        if (m_uiPhase == PHASE_GROUND)
        {
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
                }
                m_uiEncapsulateTimer = 30000;
            }
            else m_uiEncapsulateTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
// Flying Phase
    }
};

CreatureAI* GetAI_boss_felmyst(Creature *pCreature)
{
    return new boss_felmystAI(pCreature);
}

void AddSC_boss_felmyst()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_felmyst";
    pNewScript->GetAI = &GetAI_boss_felmyst;
    pNewScript->RegisterSelf();
}