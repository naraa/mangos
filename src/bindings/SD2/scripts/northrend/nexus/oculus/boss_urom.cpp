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
SDName: oculus
SD%Complete: %
SDComment:
SDCategory: Oculus
EndScriptData */

#include "precompiled.h"
#include "oculus.h"

enum Texts
{
    SAY_AGGRO                                     = -1578012,
    SAY_KILL_1                                    = -1578013,
    SAY_KILL_2                                    = -1578014,
    SAY_KILL_3                                    = -1578015,
    SAY_DEATH                                     = -1578016,
    SAY_EXPLOSION_1                               = -1578017,
    SAY_EXPLOSION_2                               = -1578018,
    SAY_SUMMON_1                                  = -1578019,
    SAY_SUMMON_2                                  = -1578020,
    SAY_SUMMON_3                                  = -1578021,
};

enum Spells
{
    SPELL_SHIELD_CHANNEL     = 53813,  //Dummy --> Channeled, shields the caster from damage.
    SPELL_SUMMON_MENAGERIE_1 = 50476,   //Summons an assortment of creatures and teleports the caster to ring 1.
    SPELL_SUMMON_MENAGERIE_2 = 50495,   //Summons an assortment of creatures and teleports the caster to ring 2.
    SPELL_SUMMON_MENAGERIE_3 = 50496,   //Summons an assortment of creatures and teleports the caster to ring 3.
    SPELL_TELEPORT           = 51112, //Teleports to the center of Oculus  in the center of ring 3

    SPELL_FROSTBOMB          = 51103,  //Urom throws a bomb, hitting its target with the highest aggro which inflict directly 650 frost damage and drops a frost zone on the ground. This zone deals 650 frost damage per second and reduce the movement speed by 35%. Lasts 1 minute.
    SPELL_TIMEBOMB           = 51121,   //Deals arcane damage to a random player, and after 6 seconds, deals zone damage to nearby equal to the health missing of the target afflicted by the debuff.
    SPELL_TIMEBOMB_H         = 59376,
    SPELL_ARCANE_EXPLOSION   = 51110,
    SPELL_ARCANE_EXPLOSION_H = 59377,

    SPELL_TIMEBOMB_DETONATE  = 51132,
};

enum PhazeRings
{
    RING_ONE    = 0,
    RING_TWO    = 1,
    RING_THREE  = 2,
    CENTER      = 3,
};

/*###
#Mage_lord_urom
####*/

struct MANGOS_DLL_DECL boss_uromAI : public ScriptedAI
{
    boss_uromAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_oculus*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_oculus* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiFightPhase;
    bool m_bIsEscaping;
    bool m_bCenterEngaged;

    uint32 m_uiTeleportTimer;
    uint32 m_uiCanCatchCombatTimer;

    uint32 m_uiFrostBombTimer;
    uint32 m_uiTimeBombTimer;
    uint32 m_uiCentralTeleportTimer;
    uint32 m_uiArcaneExplosionTimer;

    Unit* TimeBomb;
    uint32 m_uiTimeBombDetonateTimer;

    void Reset()
    {
        DoCast(m_creature, SPELL_SHIELD_CHANNEL);
        m_uiFightPhase = RING_ONE;

        m_uiTeleportTimer = 0;
        m_uiCanCatchCombatTimer = 0;
        m_bIsEscaping = false;
        m_bCenterEngaged = false;

        m_uiFrostBombTimer = 3000;
        m_uiTimeBombTimer = 6500;
        m_uiCentralTeleportTimer = 9000;
        m_uiArcaneExplosionTimer = 0;

        TimeBomb = NULL;
        m_uiTimeBombDetonateTimer = 0;

        if (m_pInstance)
            m_pInstance->SetData(TYPE_UROM, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
		DoScriptText(SAY_AGGRO,m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_UROM, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_UROM, FAIL);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(1,3))
        {
            case 1: DoScriptText(SAY_KILL_1,m_creature); break;
            case 2: DoScriptText(SAY_KILL_2,m_creature); break;
            case 3: DoScriptText(SAY_KILL_3,m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_UROM, DONE);
    }

    void AttackStart(Unit* pWho)
   {
       if (m_uiFightPhase != CENTER || m_creature->GetPositionZ() > 516.0f || m_uiCanCatchCombatTimer) //hack
           return;

       m_creature->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);

       switch(pWho->GetEntry())
       {
           case 27692:
           case 27755:
           case 27756:
               m_creature->DealDamage(pWho,pWho->GetHealth(),0,DIRECT_DAMAGE,SPELL_SCHOOL_MASK_NORMAL,0,false);
               return;
        }
        m_bCenterEngaged = true;
        ScriptedAI::AttackStart(pWho);
    }

    void MoveInLineOfSight(Unit* pWho)
   {
       if (m_bIsEscaping || m_uiCanCatchCombatTimer || m_creature->getVictim())
           return;

       if (pWho->GetTypeId() == TYPEID_PLAYER && pWho->IsWithinDistInMap(m_creature,20.0f))
       {
           m_creature->InterruptNonMeleeSpells(false);
           m_creature->SetFacingToObject(pWho);

           switch(m_uiFightPhase)
           {
           case RING_ONE:
               DoScriptText(SAY_SUMMON_1,m_creature);
               m_creature->GetMotionMaster()->MoveIdle();;
               DoCast(m_creature,SPELL_SUMMON_MENAGERIE_1);
               m_uiTeleportTimer = 3900;
               m_uiCanCatchCombatTimer = 6000;
               m_bIsEscaping = true;
               break;
           case RING_TWO:
               if (m_creature->GetPositionX() < 1000.0f)
               {
                   DoScriptText(SAY_SUMMON_2,m_creature);
                   m_creature->GetMotionMaster()->MoveIdle();
                   DoCast(m_creature,SPELL_SUMMON_MENAGERIE_2);
                   m_uiTeleportTimer = 3900;
                   m_uiCanCatchCombatTimer = 6000;
                   m_bIsEscaping = true;
               }
               break;
           case RING_THREE:
               if (m_creature->GetPositionX() > 1000.0f)
               {
                   DoScriptText(SAY_SUMMON_3,m_creature);
                   m_creature->GetMotionMaster()->MoveIdle();
                   DoCast(m_creature,SPELL_SUMMON_MENAGERIE_3);
                   m_uiTeleportTimer = 3900;
                   m_uiCanCatchCombatTimer = 6000;
                   m_bIsEscaping = true;
               }
               break;
           case CENTER:
               if (m_creature->GetPositionZ() < 516.0f)
               {
                   if (m_creature->HasAura(SPELL_SHIELD_CHANNEL))
                       m_creature->RemoveAurasDueToSpell(SPELL_SHIELD_CHANNEL);

                   ScriptedAI::MoveInLineOfSight(pWho);
                   AttackStart(pWho);
               }
               break;
            }
        }
    }

    void TimeBombDetonate()
    {
        if (TimeBomb && TimeBomb->isAlive() && m_pInstance)
        {
            TimeBomb->CastSpell(TimeBomb,SPELL_TIMEBOMB_DETONATE,true);

            uint32 damage = TimeBomb->GetMaxHealth() - TimeBomb->GetHealth();

            Map::PlayerList const& PlayerList = m_pInstance->instance->GetPlayers();

            if (PlayerList.isEmpty())
                return;

            for (Map::PlayerList::const_iterator itr = PlayerList.begin(); itr != PlayerList.end(); ++itr)
            {
                if (itr->getSource() && !(TimeBomb->GetTypeId() == TYPEID_PLAYER && ((Player*)TimeBomb) == itr->getSource()) )
                {
                    Player* pTarget = itr->getSource();
                    if (pTarget->isAlive() && pTarget->IsWithinDistInMap(TimeBomb,10.0f))
                        TimeBomb->DealDamage(pTarget,damage,0,DIRECT_DAMAGE,SPELL_SCHOOL_MASK_NORMAL,0,false);
                }
            }
            TimeBomb = NULL;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsEscaping)
        {
            if (m_uiTeleportTimer <= uiDiff)
            {
                switch(m_uiFightPhase)
                {
                case RING_ONE:
                    m_creature->SummonCreature(NPC_PHANTASMAL_AIR, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_FIRE, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_FIRE, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_WATER, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_uiFightPhase = RING_TWO;
                    break;
                case RING_TWO:
                    m_creature->SummonCreature(NPC_PHANTASMAL_CLOUDSCRAPER, 968.941f, 1045.45f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_MAMMOTH, 968.941f, 1042.45f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_WOLF, 966.941f, 1045.45f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_uiFightPhase = RING_THREE;
                    break;
                case RING_THREE:
                    m_creature->SummonCreature(NPC_PHANTASMAL_MURLOC, 1163.637f, 1170.95f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_NAGAL, 1163.637f, 1170.95f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_creature->SummonCreature(NPC_PHANTASMAL_OGRE, 1163.637f, 1170.95f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
                    m_uiFightPhase = CENTER;
                    break;
                }
                m_uiTeleportTimer = 0;
                m_bIsEscaping = false;
            } else m_uiTeleportTimer -= uiDiff;
        }

        if (m_uiCanCatchCombatTimer)
        {
            if (m_uiCanCatchCombatTimer <= uiDiff)
            {
                m_uiCanCatchCombatTimer = 0;
            } else m_uiCanCatchCombatTimer -= uiDiff;
        }

        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget())
        {
            if ((m_uiFightPhase == CENTER) && m_bCenterEngaged)
				EnterEvadeMode();
			return;
        }

        if (m_uiFightPhase == CENTER)
        {
            if (m_uiFrostBombTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0), SPELL_FROSTBOMB) == CAST_OK)
                    m_uiFrostBombTimer = urand(40000,50000);
            } else m_uiFrostBombTimer -= uiDiff;

            if (m_uiTimeBombTimer <= uiDiff)
            {
                TimeBomb = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0);
                if (DoCastSpellIfCan(TimeBomb, m_bIsRegularMode? SPELL_TIMEBOMB : SPELL_TIMEBOMB_H) == CAST_OK)
                {
                    m_uiTimeBombDetonateTimer = 6000;
                    m_uiTimeBombTimer = urand(8000,12000);
                }
            } else m_uiTimeBombTimer -= uiDiff;

            if (m_uiTimeBombDetonateTimer)
            {
                if (m_uiTimeBombDetonateTimer <= uiDiff)
                {
                    TimeBombDetonate();
                    m_uiTimeBombDetonateTimer = 0;
                } else m_uiTimeBombDetonateTimer -= uiDiff;
            }

            if (m_uiCentralTeleportTimer <= uiDiff)
            {
                DoCastSpellIfCan(m_creature,SPELL_TELEPORT);
                m_creature->GetMotionMaster()->MoveIdle();
                m_uiArcaneExplosionTimer = 2000;
                m_uiCentralTeleportTimer = urand(28000,38000);
                m_uiFrostBombTimer += 10000;
                m_uiTimeBombTimer += 10000;
            } else m_uiCentralTeleportTimer -= uiDiff;

            if (m_uiArcaneExplosionTimer)
            {
                if (m_uiArcaneExplosionTimer <= uiDiff)
                {
                    DoScriptText( urand(0,1)? SAY_EXPLOSION_1 : SAY_EXPLOSION_2, m_creature);
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    DoCastSpellIfCan(m_creature, m_bIsRegularMode? SPELL_ARCANE_EXPLOSION : SPELL_ARCANE_EXPLOSION_H);
                    m_uiArcaneExplosionTimer = 0;
                } else m_uiArcaneExplosionTimer -= uiDiff;
            }

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_urom(Creature* pCreature)
{
	return new boss_uromAI(pCreature);
}

void AddSC_boss_urom()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_urom";
    pNewScript->GetAI = &GetAI_boss_urom;
    pNewScript->RegisterSelf();
}
