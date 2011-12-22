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
    SPELL_ARCANE_BARRIER                          = 53813, //Dummy --> Channeled, shields the caster from damage.
    SPELL_EMPOWERED_ARCANE_EXPLOSION              = 51110,
    SPELL_EMPOWERED_ARCANE_EXPLOSION_H            = 59377,
    SPELL_FROSTBOMB                               = 51103, //Urom throws a bomb, hitting its target with the highest aggro which inflict directly 650 frost damage and drops a frost zone on the ground. This zone deals 650 frost damage per second and reduce the movement speed by 35%. Lasts 1 minute.
    SPELL_SUMMON_MENAGERIE                        = 50476, //Summons an assortment of creatures and teleports the caster to safety.
    SPELL_SUMMON_MENAGERIE_2                      = 50495,
    SPELL_SUMMON_MENAGERIE_3                      = 50496,
    SPELL_TELEPORT                                = 51112, //Teleports to the center of Oculus
    SPELL_TIME_BOMB                               = 51121, //Deals arcane damage to a random player, and after 6 seconds, deals zone damage to nearby equal to the health missing of the target afflicted by the debuff.
    SPELL_TIME_BOMB_H                             = 59376,
};

enum PhazeRings
{
    PHASE_PLATFORM_1    = 0,
    PHASE_PLATFORM_2    = 1,
    PHASE_PLATFORM_3    = 2,
    PHASE_CENTER        = 3,
};

struct MANGOS_DLL_DECL boss_uromAI : public ScriptedAI
{
    boss_uromAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_oculus*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_creature->addUnitState(UNIT_STAT_IGNORE_PATHFINDING);
        Reset();
    }

    instance_oculus* m_pInstance;
    bool m_bIsRegularMode;

    uint8 m_uiPhase;

    void Reset()
    {
        m_uiPhase = PHASE_PLATFORM_1;
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

    void SummonPack_1()
    {
        m_creature->SummonCreature(NPC_PHANTASMAL_AIR, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_creature->SummonCreature(NPC_PHANTASMAL_FIRE, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_creature->SummonCreature(NPC_PHANTASMAL_FIRE, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_creature->SummonCreature(NPC_PHANTASMAL_WATER, 1177.505f,  937.96f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_uiPhase = PHASE_PLATFORM_2;
    }

    void SummonPack_2()
    {
       m_creature->SummonCreature(NPC_PHANTASMAL_CLOUDSCRAPER, 968.941f, 1045.45f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
       m_creature->SummonCreature(NPC_PHANTASMAL_MAMMOTH, 968.941f, 1042.45f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
       m_creature->SummonCreature(NPC_PHANTASMAL_WOLF, 966.941f, 1045.45f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
       m_uiPhase = PHASE_PLATFORM_3;
    }

    void SummonPack_3()
    {
        m_creature->SummonCreature(NPC_PHANTASMAL_MURLOC, 1163.637f, 1170.95f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_creature->SummonCreature(NPC_PHANTASMAL_NAGAL, 1163.637f, 1170.95f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_creature->SummonCreature(NPC_PHANTASMAL_OGRE, 1163.637f, 1170.95f, 527.32f,0,TEMPSUMMON_DEAD_DESPAWN,0);
        m_uiPhase = PHASE_CENTER;
    }

    void UpdateAI(const uint32 uiDiff)
	{
        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_urom(Creature* pCreature)
{
    return new boss_uromAI (pCreature);
}

void AddSC_boss_urom()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_urom";
    pNewScript->GetAI = &GetAI_boss_urom;
    pNewScript->RegisterSelf();
}
