/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: boss_lord_marrowgar
SD%Complete: 85%
SDComment: by /dev/rsa
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum
{
    //common
    SPELL_BERSERK                           = 47008,

    //summons
    NPC_BONE_SPIKE                          = 38711,
    NPC_COLD_FLAME                          = 36672,

    SPELL_BONE_SLICE                        = 69055,
    SPELL_CALL_COLD_FLAME                   = 69138,
    SPELL_CALL_COLD_FLAME_1                 = 71580,
    SPELL_COLD_FLAME                        = 69146,
    SPELL_COLD_FLAME_0                      = 69145,
    SPELL_COLD_FLAME_1                      = 69147,
    SPELL_BONE_STORM                        = 69076,
    SPELL_BONE_SPIKE                        = 69057,
    SPELL_BONE_SPIKE_BONE_STORM             = 73144,
    SPELL_BONE_SPIKE_IMPALE                 = 69065,
    SPELL_VEHICLE_HARDCODED                 = 46598,
    SPELL_BONE_STORM_STRIKE                 = 69075
};


/*####
# Lord Marrowgar
####*/
struct MANGOS_DLL_DECL boss_lord_marrowgarAI : public BSWScriptedAI
{
    boss_lord_marrowgarAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;
    bool m_bSaidIntro;

    uint32 m_uiSliceTimer;
    uint32 m_uiBoneStormChargeTimer;
    uint8 m_uiColdFlameCounter;
    bool m_bIsColdFlameXCast;

    float targetPosX, targetPosY, targetPosZ; // used for checking Bone Storm charging (checking MovePoint id doesn't work?)

    void Reset()
    {
        resetTimers();
        m_uiSliceTimer = 10000;
        m_uiBoneStormChargeTimer = 4000;
        m_bIsColdFlameXCast = false;
        m_uiColdFlameCounter = 0;

        m_creature->SetSpeedRate(MOVE_RUN, 1.0f);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        ScriptedAI::MoveInLineOfSight(pWho);

        if (m_bSaidIntro)
            return;

        DoScriptText(-1631000,m_creature);
        m_bSaidIntro = true;
    }

    void JustSummoned(Creature* pCreature)
    {
        if(!pCreature)
            return;

        pCreature->SetCreatorGuid(m_creature->GetObjectGuid());
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MARROWGAR, FAIL);
    }

    void Aggro(Unit* pWho)
    {
        if(!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_MARROWGAR, IN_PROGRESS);
        DoScriptText(-1631001,m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(-1631006 - urand(0, 1),m_creature,pVictim);
    }

    void JustDied(Unit *killer)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_MARROWGAR, DONE);

        DoScriptText(-1631009,m_creature);
    }

    void DoSummonSpike(Unit* pTarget)
    {
        if (!pTarget || !pTarget->isAlive())
            return;

        float fPosX, fPosY, fPosZ;

        pTarget->GetPosition(fPosX, fPosY, fPosZ);

        if (Unit* pSpike = doSummon(NPC_BONE_SPIKE, fPosX, fPosY, fPosZ + 1.0f))
        {
            pSpike->SetOwnerGuid(m_creature->GetObjectGuid());
            pSpike->SetInCombatWith(pTarget);
            pSpike->AddThreat(pTarget, 1000.0f);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(getStage())
        {
            case 0: // Bone Slice and single Coldflames phase
            {
                if (timedQuery(SPELL_BONE_SPIKE, diff))
                {
                    if (Unit* pTarget = doSelectRandomPlayer(SPELL_BONE_SPIKE_IMPALE, false, 60.0f, isHeroic()))
                    {
                        doCast(pTarget, SPELL_BONE_SPIKE);
                        DoSummonSpike(pTarget);
                        DoScriptText(-1631003 - urand(0,2), m_creature, pTarget);
                    }
                }

                if (timedQuery(SPELL_BONE_STORM, diff))
                    setStage(1);

                if (timedQuery(SPELL_CALL_COLD_FLAME, diff))
                    doCast(SPELL_CALL_COLD_FLAME);

                if (m_uiSliceTimer <= 1000)
                {
                    if (m_uiSliceTimer <= diff)
                    {
                        doCast(SPELL_BONE_SLICE, m_creature->getVictim());
                        m_uiSliceTimer = 1000;
                    }
                    else
                        m_uiSliceTimer -= diff;
                }
                else
                    m_uiSliceTimer -= diff;

                DoMeleeAttackIfReady();
                break;
            }
            case 1: // Bone Storm initialization phase
            {
                m_creature->InterruptNonMeleeSpells(true);
                doCast(SPELL_BONE_STORM);
                DoScriptText(-1631002,m_creature);
                SetCombatMovement(false);
                m_creature->GetMotionMaster()->Clear();
                m_creature->SetSpeedRate(MOVE_RUN, 3);
                // initial X Coldflames are in Marrowgar's place
                m_creature->GetPosition(targetPosX, targetPosY, targetPosZ);
                setStage(2);
                break;
            }
            case 2: // Bone Storm waiting to end casting the spell
            {
                if (!m_creature->IsNonMeleeSpellCasted(false))
                    setStage(3);
                break;
            }
            case 3: // Whirling in Bone Storm and casting Cold Flames
            {
                if (isHeroic())
                {
                    if (timedQuery(SPELL_BONE_SPIKE, diff))
                    {
                        if (Unit* pTarget = doSelectRandomPlayer(SPELL_BONE_SPIKE_IMPALE, false, 60.0f, isHeroic()))
                        {
                            doCast(pTarget, SPELL_BONE_SPIKE);
                            DoSummonSpike(pTarget);
                            DoScriptText(-1631003 - urand(0,2), m_creature, pTarget);
                        }
                    }
                }

                if (m_creature->GetDistance2d(targetPosX, targetPosY) < 5.0f)
                {
                    if (!m_bIsColdFlameXCast)
                    {
                        
                        float myPosX, myPosY, myPosZ;

                        m_creature->GetPosition(myPosX, myPosY, myPosZ);

                        m_pInstance->SetData(DATA_DIRECTION, (uint32)(1000*2.0f*M_PI_F*((float)urand(1,16)/16.0f)));
                        doCast(SPELL_CALL_COLD_FLAME);
                        doSummon(NPC_COLD_FLAME, myPosX, myPosY, myPosZ);

                        if (++m_uiColdFlameCounter >= 4 + isHeroic())
                        {
                            doRemove(SPELL_BONE_STORM_STRIKE);
                            doRemove(SPELL_BONE_STORM);
                        }
                        m_bIsColdFlameXCast = true;
                    }

                    if (m_uiBoneStormChargeTimer <= diff)
                    {
                        if (Unit* pTarget = doSelectRandomPlayerAtRange(60.0f))
                        {
                            pTarget->GetPosition(targetPosX, targetPosY, targetPosZ);
                            m_creature->GetMotionMaster()->MovePoint(0, targetPosX, targetPosY, targetPosZ);
                            m_bIsColdFlameXCast = false;
                            m_uiBoneStormChargeTimer = 3000;
                        }
                    }
                    else
                        m_uiBoneStormChargeTimer -= diff;
                }

                if (!hasAura(SPELL_BONE_STORM_STRIKE, m_creature) && !hasAura(SPELL_BONE_STORM, m_creature))
                    setStage(4);

                break;
            }
            case 4:
            {
                m_pInstance->SetData(DATA_DIRECTION, 0);
                m_creature->SetSpeedRate(MOVE_RUN, 1);
                m_uiColdFlameCounter = 0;
                SetCombatMovement(true);
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                m_uiSliceTimer = 10000;
                setStage(0);
                break;
            }
            default:
                break;
        }

        if (timedQuery(SPELL_BERSERK, diff))
        {
            doCast(SPELL_BERSERK);
            DoScriptText(-1631008, m_creature);
        }
    }
};

/*####
# Coldflame
####*/
struct MANGOS_DLL_DECL mob_coldflameAI : public BSWScriptedAI
{
    mob_coldflameAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsFirst;
    bool m_bIsXmode;
    bool m_bIsCreator;
    float m_fDirection;

    void Reset()
    {
        if(!m_pInstance)
            return;

        m_creature->SetRespawnDelay(7*DAY);

        setStage(0);
        m_bIsCreator = false;

        SetCombatMovement(false);
        doCast(SPELL_COLD_FLAME_0);
    }

    void AttackStart(Unit *who){}

    void JustSummoned(Creature* pSummoned)
    {
        if(!m_pInstance || !pSummoned)
            return;

        pSummoned->SetCreatorGuid(m_creature->GetObjectGuid());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->GetCreatorGuid().IsEmpty())
            return;

        if (!m_bIsCreator)
        {
            Creature *pLord = m_pInstance->GetSingleCreatureFromStorage(NPC_LORD_MARROWGAR);

            if (pLord && m_creature->GetCreatorGuid() == pLord->GetObjectGuid())
            {
                uint32 m_tmpDirection = m_pInstance->GetData(DATA_DIRECTION);

                m_pInstance->SetData(DATA_DIRECTION,0);
                m_bIsFirst = true;

                if (m_tmpDirection)
                {
                    m_fDirection = m_tmpDirection/1000.0f;
                    m_bIsXmode = true;
                }
                else
                {
                    m_fDirection = 2.0f*M_PI_F*((float)urand(1,16)/16.0f);
                    m_bIsXmode = false;
                }
            }
            else
                m_bIsFirst = false;

            m_bIsCreator = true;
        }

        if (timedQuery(SPELL_COLD_FLAME_0, uiDiff) && !m_bIsFirst)
        {
            m_creature->ForcedDespawn();
            return;
        }

        if (m_bIsFirst && timedQuery(SPELL_COLD_FLAME_1, uiDiff, true))
        {
            if (getStage() < getSpellData(SPELL_COLD_FLAME_0))
            {
                float x, y, radius;

                radius = getStage()*5;
                m_creature->GetNearPoint2D(x, y, radius, m_fDirection);
                doSummon(NPC_COLD_FLAME, x, y, m_creature->GetPositionZ(), TEMPSUMMON_TIMED_DESPAWN, getSpellData(SPELL_COLD_FLAME_1));

                setStage(getStage()+1);

                if (m_bIsXmode)
                {
                    m_creature->GetNearPoint2D(x, y, radius, m_fDirection+M_PI_F/2);
                    doSummon(NPC_COLD_FLAME, x, y, m_creature->GetPositionZ(), TEMPSUMMON_TIMED_DESPAWN, getSpellData(SPELL_COLD_FLAME_1));
                    m_creature->GetNearPoint2D(x, y, radius, m_fDirection+M_PI_F);
                    doSummon(NPC_COLD_FLAME, x, y, m_creature->GetPositionZ(), TEMPSUMMON_TIMED_DESPAWN, getSpellData(SPELL_COLD_FLAME_1));
                    m_creature->GetNearPoint2D(x, y, radius, m_fDirection+M_PI_F*1.5f);
                    doSummon(NPC_COLD_FLAME, x, y, m_creature->GetPositionZ(), TEMPSUMMON_TIMED_DESPAWN, getSpellData(SPELL_COLD_FLAME_1));
                }
            }
            else
            {
                m_creature->ForcedDespawn();
                return;
            }
        }
        else
            timedCast(SPELL_COLD_FLAME, uiDiff);
    }
};

/*####
# Bone Spike
####*/
struct MANGOS_DLL_DECL mob_bone_spikeAI : public BSWScriptedAI
{
    mob_bone_spikeAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;
    ObjectGuid m_victimGuid;
    bool m_bEmerged;

    void Reset()
    {
        m_bEmerged = false;
        SetCombatMovement(false);
        m_creature->SetRespawnDelay(7*DAY);
        m_victimGuid = ObjectGuid();
        m_creature->SetInCombatWithZone();
    }

    void Aggro(Unit* pWho)
    {
        if (m_victimGuid.IsEmpty() && pWho && pWho->GetTypeId() == TYPEID_PLAYER)
        {
            m_victimGuid = pWho->GetObjectGuid();
            m_creature->SetInCombatWith(pWho);
            doCast(SPELL_BONE_SPIKE_IMPALE,pWho);
            doCast(SPELL_VEHICLE_HARDCODED,pWho);
        }
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            if (Player* pVictim = m_creature->GetMap()->GetPlayer(m_victimGuid))
                doRemove(SPELL_BONE_SPIKE_IMPALE, pVictim);
        }
    }

    void AttackStart(Unit *pWho){}

    void KilledUnit(Unit* pWho)
    {
        if (Player* pVictim = m_creature->GetMap()->GetPlayer(m_victimGuid))
        {
            if (pVictim->GetObjectGuid() == m_victimGuid)
                doRemove(SPELL_BONE_SPIKE_IMPALE,pVictim);
        }
    }

    void JustDied(Unit* Killer)
    {
        if (Player* pVictim = m_creature->GetMap()->GetPlayer(m_victimGuid))
            doRemove(SPELL_BONE_SPIKE_IMPALE, pVictim);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bEmerged)
        {
            m_creature->HandleEmote(EMOTE_ONESHOT_EMERGE);
            m_bEmerged = true;
        }

        if(m_pInstance && m_pInstance->GetData(TYPE_MARROWGAR) != IN_PROGRESS)
        {
            if (Player* pVictim = m_creature->GetMap()->GetPlayer(m_victimGuid))
                doRemove(SPELL_BONE_SPIKE_IMPALE,pVictim);

            m_creature->ForcedDespawn();
            return;
        }

        if (m_victimGuid.IsEmpty())
            return;

        if (Player* pVictim = m_creature->GetMap()->GetPlayer(m_victimGuid))
        {
            if(!pVictim->isAlive())
            {
                m_creature->ForcedDespawn();
                return;
            }
        }
        else
        {
            m_creature->ForcedDespawn();
            return;
        }
    }
};

CreatureAI* GetAI_mob_bone_spike(Creature* pCreature)
{
    return new mob_bone_spikeAI(pCreature);
}

CreatureAI* GetAI_mob_coldflame(Creature* pCreature)
{
    return new mob_coldflameAI(pCreature);
}

CreatureAI* GetAI_boss_lord_marrowgar(Creature* pCreature)
{
    return new boss_lord_marrowgarAI(pCreature);
}

void AddSC_boss_lord_marrowgar()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_lord_marrowgar";
    newscript->GetAI = &GetAI_boss_lord_marrowgar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_coldflame";
    newscript->GetAI = &GetAI_mob_coldflame;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_bone_spike";
    newscript->GetAI = &GetAI_mob_bone_spike;
    newscript->RegisterSelf();

}
