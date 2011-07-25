/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2011 MangosR2 Scriptdev2
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
SDName: Boss_Akilzon
SD%Complete: 70%
SDComment: TODO: prisoner event and misc
SDCategory: Zul'Aman
EndScriptData */

#include "precompiled.h"
#include "zulaman.h"
#include "spell.h"
#include "weather.h"

enum
{
    SAY_EVENT1              = -1568024,
    SAY_EVENT2              = -1568025,
    SAY_AGGRO               = -1568026,
    SAY_SUMMON              = -1568027,
    SAY_SUMMON_ALT          = -1568028,
    SAY_ENRAGE              = -1568029,
    SAY_SLAY1               = -1568030,
    SAY_SLAY2               = -1568031,
    SAY_DEATH               = -1568032,
    EMOTE_STORM             = -1568033,

    SPELL_STATIC_DISRUPTION = 43622,
    SPELL_STATIC_VISUAL     = 45265,

    SPELL_CALL_LIGHTNING    = 43661,
    SPELL_GUST_OF_WIND      = 43621,

    SPELL_ELECTRICAL_STORM  = 43648,
    SPELL_STORMCLOUD_VISUAL = 45213,

    SPELL_BERSERK           = 45078,

    NPC_SOARING_EAGLE       = 24858,
    MAX_EAGLE_COUNT         = 6,

    SE_LOC_X_MAX            = 400,
    SE_LOC_X_MIN            = 335,
    SE_LOC_Y_MAX            = 1435,
    SE_LOC_Y_MIN            = 1370,
    MOB_TEMP_TRIGGER        = 23920
};

struct MANGOS_DLL_DECL boss_akilzonAI : public ScriptedAI
{
    boss_akilzonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiStaticDisruptTimer;
    uint32 m_uiCallLightTimer;
    uint32 m_uiGustOfWindTimer;
    uint32 m_uiElectricalStorm_Timer;
    uint32 m_uiSummonEagleTimer;
    uint32 m_uiBerserkTimer;
    bool m_bIsBerserk;

    ObjectGuid TargetGUID;
    ObjectGuid CycloneGUID;
    ObjectGuid CloudGUID;
    uint32 StormCount;
    uint32 StormSequenceTimer;
    bool isRaining;

    void Reset()
    {
        m_uiStaticDisruptTimer = urand(7000, 14000);
        m_uiCallLightTimer = urand(15000, 25000);
        m_uiGustOfWindTimer = urand(20000, 30000);
        m_uiElectricalStorm_Timer = 50000;
        m_uiSummonEagleTimer = 65000;
        m_uiBerserkTimer = MINUTE*8*IN_MILLISECONDS;
        m_bIsBerserk = false;

        TargetGUID.Clear();
        CloudGUID.Clear();
        CycloneGUID.Clear();

        StormCount = 0;
        StormSequenceTimer = 0;

        isRaining = false;

        DespawnSummons(NPC_SOARING_EAGLE);
        SetWeather(WEATHER_STATE_FINE, 0.0f);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        m_creature->SetInCombatWithZone();
        SetWeather(WEATHER_STATE_THUNDERS, 0.0f);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_AKILZON, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY1 : SAY_SLAY2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        DespawnSummons(NPC_SOARING_EAGLE);
        SetWeather(WEATHER_STATE_FINE, 0.0f);

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_AKILZON, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AKILZON, FAIL);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_SOARING_EAGLE)
            pSummoned->SetInCombatWithZone();
    }

    void DoSummonEagles()
    {
        for(uint32 i = 0; i < MAX_EAGLE_COUNT; ++i)
        {
            float fX, fY, fZ;
            m_creature->GetRandomPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+15.0f, 30.0f, fX, fY, fZ);

            m_creature->SummonCreature(NPC_SOARING_EAGLE, fX, fY, fZ, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
        }
    }

    void DespawnSummons(uint32 entry)
    {
        std::list<Creature*> templist;
        float x, y, z;
        m_creature->GetPosition(x, y, z);

        {
            CellPair pair(MaNGOS::ComputeCellPair(x, y));
            Cell cell(pair);
            cell.SetNoCreate();

            AllCreaturesOfEntryInRangeCheck check(m_creature, entry, 100);
            MaNGOS::CreatureListSearcher<AllCreaturesOfEntryInRangeCheck> searcher(templist, check);

            TypeContainerVisitor<MaNGOS::CreatureListSearcher<AllCreaturesOfEntryInRangeCheck>, GridTypeMapContainer> cSearcher(searcher);

            // cellVisit<GridReadGuard> cell.Visit(cell, pair);
            cell.Visit(pair, cSearcher, *(m_creature->GetMap()),*m_creature,100);
        }

        for(std::list<Creature*>::iterator i = templist.begin(); i != templist.end(); ++i)
        {
            (*i)->SetVisibility(VISIBILITY_OFF);
            (*i)->SetDeathState(JUST_DIED);
        }
    }

    Player* SelectRandomPlayer(float range = 0.0f, bool alive = true)
    {
        Map *map = m_creature->GetMap();
        if (!map->IsDungeon())
            return NULL;

        Map::PlayerList const &PlayerList = map->GetPlayers();
        if (PlayerList.isEmpty())
            return NULL;

        std::list<Player*> temp;
        std::list<Player*>::iterator j;

        for(Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
			if((range == 0.0f || m_creature->IsWithinDistInMap(i->getSource(), range))
				&& (!alive || i->getSource()->isTargetableForAttack()))
				temp.push_back(i->getSource());

		if (temp.size())
        {
			j = temp.begin();
		    advance(j, rand()%temp.size());
		    return (*j);
		}
        return NULL;

    }

    void SetWeather(uint32 weather, float grade)
    {
        Map *map = m_creature->GetMap();
        if (!map->IsDungeon())
            return;

        WorldPacket data(SMSG_WEATHER, (4+4+4));
        data << uint32(weather) << (float)grade << uint8(0);

        ((DungeonMap*)map)->SendToPlayers(&data);
    }

    void HandleStormSequence(Unit *Cloud) // 1: begin, 2-9: tick, 10: end
    {
        if(StormCount < 10 && StormCount > 1)
        {
            // deal damage
            int32 bp0 = 800;
            for(uint8 i = 2; i < StormCount; ++i)
                bp0 *= 2;

            CellPair p(MaNGOS::ComputeCellPair(m_creature->GetPositionX(), m_creature->GetPositionY()));
            Cell cell(p);
            cell.SetNoCreate();

            std::list<Unit *> tempUnitMap;

            {
                MaNGOS::AnyAoETargetUnitInObjectRangeCheck u_check(m_creature, 999);
                MaNGOS::UnitListSearcher<MaNGOS::AnyAoETargetUnitInObjectRangeCheck> searcher(tempUnitMap, u_check);

                TypeContainerVisitor<MaNGOS::UnitListSearcher<MaNGOS::AnyAoETargetUnitInObjectRangeCheck>, WorldTypeMapContainer > world_unit_searcher(searcher);
                TypeContainerVisitor<MaNGOS::UnitListSearcher<MaNGOS::AnyAoETargetUnitInObjectRangeCheck>, GridTypeMapContainer >  grid_unit_searcher(searcher);

                //CellLock<GridReadGuard> cell_lock(cell, p);
                cell.Visit(p, world_unit_searcher, *(m_creature->GetMap()),*m_creature,100);
                cell.Visit(p, grid_unit_searcher, *(m_creature->GetMap()),*m_creature,100);
            }

            for(std::list<Unit*>::iterator i = tempUnitMap.begin(); i != tempUnitMap.end(); ++i)
            {
                if(!Cloud->IsWithinDistInMap(*i, 15))
                {
                    float x, y, z;
                    (*i)->GetPosition(x, y, z);
                    x = rand()%2 ? x + rand()%5 : x - rand()%5;
                    y = rand()%2 ? y + rand()%5 : y - rand()%5;
                    z = Cloud->GetPositionZ() + 2 - rand()%4;

                    if(Creature *trigger = m_creature->SummonCreature(MOB_TEMP_TRIGGER, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 2000))
                    {
                        trigger->StopMoving();
                        trigger->CastSpell(trigger, 37248, true);
                        trigger->CastCustomSpell(*i, 43137, &bp0, NULL, NULL, true, 0, 0, m_creature->GetObjectGuid());
                    }
                }
            }

            // visual
            float x, y, z;
            for(uint8 i = 0; i < StormCount; ++i)
            {
                Cloud->GetPosition(x, y, z);
                x = rand()%2 ? x + rand()%10 : x - rand()%10;
                y = rand()%2 ? y + rand()%10 : y - rand()%10;
                z = z + 2 - rand()%4;

                if(Unit *trigger = m_creature->SummonCreature(MOB_TEMP_TRIGGER, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 2000))
                {
                    trigger->addUnitState(MOVEFLAG_LEVITATING);
                    trigger->StopMoving();
                    trigger->CastSpell(trigger, 37248, true);
                }

                Cloud->GetPosition(x, y, z);
                x = rand()%2 ? x + 10 + rand()%10 : x - 10 - rand()%10;
                y = rand()%2 ? y + 10 + rand()%10 : y - 10 - rand()%10;

                if(Unit *trigger = m_creature->SummonCreature(MOB_TEMP_TRIGGER, x, y, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 2000))
                {
                    trigger->SetMaxHealth(9999999);
                    trigger->SetHealth(9999999);
                    trigger->CastSpell(trigger, 43661, true);
                }
            }
        }

        StormCount++;

        if (StormCount > 10)
        {
            StormCount = 0; // finish
            m_creature->InterruptNonMeleeSpells(false);
            Cloud->RemoveAurasDueToSpell(45213);
            CloudGUID.Clear();

            if (Unit* Cyclone = m_creature->GetMap()->GetUnit( CycloneGUID))
                Cyclone->RemoveAurasDueToSpell(25160);

            SetWeather(WEATHER_STATE_FINE, 0.0f);
            isRaining = false;
        }

        StormSequenceTimer = 1000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(StormCount)
        {
            Unit* target = m_creature->GetMap()->GetUnit(CloudGUID);
            if (!target || !target->isAlive())
            {
                EnterEvadeMode();
                return;
            }
            else if (Unit* Cyclone = m_creature->GetMap()->GetUnit(CycloneGUID))
                Cyclone->CastSpell(target, 25160, true); // keep casting or...

            if(StormSequenceTimer < uiDiff)
            {
                HandleStormSequence(target);
            }else StormSequenceTimer -= uiDiff;

            return;
        }

        if (m_uiCallLightTimer < uiDiff)
        {
            m_creature->CastSpell(m_creature->getVictim(), SPELL_CALL_LIGHTNING, false);
            m_uiCallLightTimer = urand(15000, 25000);
        }else m_uiCallLightTimer -= uiDiff;

        if (m_uiStaticDisruptTimer < uiDiff)
        {
            Unit* SDVictim = m_creature->GetMap()->GetUnit( TargetGUID);
            if(SDVictim && SDVictim->isAlive())
                SDVictim->CastSpell(SDVictim, SPELL_STATIC_VISUAL, true);

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                m_creature->CastSpell(pTarget, SPELL_STATIC_DISRUPTION, false);

            m_uiStaticDisruptTimer = urand(7000, 14000);
        }else m_uiStaticDisruptTimer -= uiDiff;

        if (m_uiGustOfWindTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                m_creature->CastSpell(pTarget, SPELL_GUST_OF_WIND, false);

            m_uiGustOfWindTimer = urand(20000, 30000);
        }else m_uiGustOfWindTimer -= uiDiff;

        if (!isRaining && m_uiElectricalStorm_Timer < uint32(8000 + rand()%5000))
        {
            SetWeather(WEATHER_STATE_HEAVY_RAIN, 0.9999f);
            isRaining = true;
        }

        if (m_uiElectricalStorm_Timer < uiDiff)
        {
            Unit* target = SelectRandomPlayer(50);
            if(!target)
                target = m_creature->getVictim();

            float x, y, z;
            target->GetPosition(x, y, z);
            Unit *Cloud = m_creature->SummonCreature(MOB_TEMP_TRIGGER, x, y, m_creature->GetPositionZ() + 10, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);

            if(Cloud)
            {
                CloudGUID = Cloud->GetObjectGuid();
                Cloud->addUnitState(MOVE_FLIGHT);
                Cloud->StopMoving();
                Cloud->SetFloatValue(OBJECT_FIELD_SCALE_X, 3.0f);
                Cloud->setFaction(35);
                Cloud->SetMaxHealth(9999999);
                Cloud->SetHealth(9999999);
                Cloud->CastSpell(Cloud, 45213, true); // cloud visual
                m_creature->StopMoving();
                Cloud->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoScriptText(EMOTE_STORM, m_creature);
                m_creature->CastSpell(Cloud, SPELL_ELECTRICAL_STORM, false); // siphon soul
            }

            Unit *Cyclone = m_creature->SummonCreature(MOB_TEMP_TRIGGER, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 15000);
            if(Cyclone)
            {
                Cyclone->CastSpell(Cyclone, 25160, true); // wind visual
                CycloneGUID = Cyclone->GetObjectGuid();
            }

            m_uiElectricalStorm_Timer = 60000; //60 seconds(bosskillers)
            StormCount = 1;
            StormSequenceTimer = 0;
        } else m_uiElectricalStorm_Timer -= uiDiff;

        if (m_uiSummonEagleTimer < uiDiff)
        {
            DoScriptText(urand(0,1) ? SAY_SUMMON : SAY_SUMMON_ALT, m_creature);
            DoSummonEagles();
            m_uiSummonEagleTimer = 60000;
        }else m_uiSummonEagleTimer -= uiDiff;

        if (!m_bIsBerserk && m_uiBerserkTimer < uiDiff)
        {
            DoScriptText(SAY_ENRAGE, m_creature);
            m_creature->CastSpell(m_creature, SPELL_BERSERK, true);
            m_bIsBerserk = true;
        }else m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_akilzon(Creature* pCreature)
{
    return new boss_akilzonAI(pCreature);
}

enum
{
    SPELL_EAGLE_SWOOP       = 44732,
    POINT_ID_RANDOM         = 1
};

struct MANGOS_DLL_DECL mob_soaring_eagleAI : public ScriptedAI
{
    mob_soaring_eagleAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiEagleSwoopTimer;
    uint32 m_uiReturnTimer;
    bool m_bCanMoveToRandom;
    bool m_bCanCast;

    void Reset()
    {
        m_uiEagleSwoopTimer = urand(2000, 6000);
        m_uiReturnTimer = 800;
        m_bCanMoveToRandom = false;
        m_bCanCast = true;

    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, false))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);
        }
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        m_bCanCast = true;
    }

    void DoMoveToRandom()
    {
        if (!m_pInstance)
            return;

        if (Creature* pAzkil = m_pInstance->GetSingleCreatureFromStorage(NPC_AKILZON))
        {
            float fX, fY, fZ;
            pAzkil->GetRandomPoint(pAzkil->GetPositionX(), pAzkil->GetPositionY(), pAzkil->GetPositionZ()+15.0f, 30.0f, fX, fY, fZ);

            m_creature->SetWalk(false);
            m_creature->GetMotionMaster()->MovePoint(POINT_ID_RANDOM, fX, fY, fZ);

            m_bCanMoveToRandom = false;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanMoveToRandom)
        {
            if (m_uiReturnTimer < uiDiff)
            {
                DoMoveToRandom();
                m_uiReturnTimer = 800;
            }else m_uiReturnTimer -= uiDiff;
        }

        if (!m_bCanCast)
            return;

        if (m_uiEagleSwoopTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0))
            {
                DoCastSpellIfCan(pTarget,SPELL_EAGLE_SWOOP);

                m_bCanMoveToRandom = true;
                m_bCanCast = false;
            }

            m_uiEagleSwoopTimer = urand(4000, 6000);
        }else m_uiEagleSwoopTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_soaring_eagle(Creature* pCreature)
{
    return new mob_soaring_eagleAI(pCreature);
}

void AddSC_boss_akilzon()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_akilzon";
    pNewScript->GetAI = &GetAI_boss_akilzon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_soaring_eagle";
    pNewScript->GetAI = &GetAI_mob_soaring_eagle;
    pNewScript->RegisterSelf();
}
