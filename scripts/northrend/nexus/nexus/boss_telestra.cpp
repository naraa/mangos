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
SDName: Boss_Magus_Telestra
SD%Complete: 95%
SDComment:
SDCategory: The Nexus, The Nexus
EndScriptData */

#include "precompiled.h"
#include "nexus.h"

enum eEnums
{
    // Spells
    SPELL_ICE_NOVA_N          = 47772,
    SPELL_ICE_NOVA_H          = 56935,
    SPELL_FIREBOMB_N          = 47773,
    SPELL_FIREBOMB_H          = 56934,
    SPELL_GRAVITY_WELL        = 47756,
    SPELL_TELESTRA_BACK       = 47714,
    SPELL_FIRE_MAGUS_VISUAL   = 47705,
    SPELL_FROST_MAGUS_VISUAL  = 47706,
    SPELL_ARCANE_MAGUS_VISUAL = 47704,

    // NPC's
    NPC_FIRE_MAGUS            = 26928,
    NPC_FROST_MAGUS           = 26930,
    NPC_ARCANE_MAGUS          = 26929,

    // Texts
    SAY_AGGRO                 = -1576000,
    SAY_KILL                  = -1576001,
    SAY_DEATH                 = -1576002,
    SAY_MERGE                 = -1576003,
    SAY_SPLIT_1               = -1576004,
    SAY_SPLIT_2               = -1576005,

    // Achievements
    ACHIEV_SPLIT_PERSONALITY  = 2150,

    // Others
    ACHIEV_TIMER              = 5000
};

float CenterOfRoom[1][4] =
{
    {504.80f, 89.07f, -16.12f, 6.27f}
};

struct MANGOS_DLL_DECL boss_telestraAI : public ScriptedAI
{
    boss_telestraAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    bool m_bAppearDelay;
    bool m_bFireMagusDead;
    bool m_bFrostMagusDead;
    bool m_bArcaneMagusDead;
    bool m_bIsAchievementTimerRunning;
    uint8 m_uiPhase;
    uint8 m_uiAchievementProgress;
    uint32 m_uiCooldownTimer;
    uint32 m_uiAppearDelayTimer;
    uint32 m_uiAchievementTimer;
    uint32 m_uiIceNovaTimer;
    uint32 m_uiFirebombTimer;
    uint32 m_uiGravityWellTimer;
    ObjectGuid m_pFireMagusGuid;
    ObjectGuid m_pFrostMagusGuid;
    ObjectGuid m_pArcaneMagusGuid;

    void Reset()
    {
        m_bAppearDelay = false;
        m_bFireMagusDead = false;
        m_bFrostMagusDead = false;
        m_bArcaneMagusDead = false;
        m_bIsAchievementTimerRunning = false;
        m_uiPhase = 0;
        m_uiAchievementProgress = 0;
        m_uiCooldownTimer = 0;
        m_uiAppearDelayTimer = 0;
        m_uiAchievementTimer = 0;
        m_uiIceNovaTimer = 7*IN_MILLISECONDS;
        m_uiFirebombTimer = 0;
        m_uiGravityWellTimer = 15*IN_MILLISECONDS;
        m_pFireMagusGuid.Clear();
        m_pFrostMagusGuid.Clear();
        m_pArcaneMagusGuid.Clear();

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_ON);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TELESTRA, NOT_STARTED);
    }

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* killer)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (!m_bIsRegularMode && m_uiAchievementProgress == 2)
        {
            AchievementEntry const *AchievSplitPersonality = GetAchievementStore()->LookupEntry(ACHIEV_SPLIT_PERSONALITY);
            if (AchievSplitPersonality)
            {
                Map* pMap = m_creature->GetMap();
                if (pMap && pMap->IsDungeon())
                {
                    Map::PlayerList const &players = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        itr->getSource()->CompletedAchievement(AchievSplitPersonality);
                }
            }
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TELESTRA, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    ObjectGuid SplitPersonality(uint32 entry)
    {
        Creature* pSummoned = m_creature->SummonCreature(entry, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000);
        if (pSummoned)
        {
            switch (entry)
            {
                case NPC_FIRE_MAGUS:
                {
                    pSummoned->CastSpell(pSummoned, SPELL_FIRE_MAGUS_VISUAL, false);
                    break;
                }
                case NPC_FROST_MAGUS:
                {
                    pSummoned->CastSpell(pSummoned, SPELL_FROST_MAGUS_VISUAL, false);
                    break;
                }
                case NPC_ARCANE_MAGUS:
                {
                    pSummoned->CastSpell(pSummoned, SPELL_ARCANE_MAGUS_VISUAL, false);
                    break;
                }
                default:
                    break;
           }

           if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);

            return pSummoned->GetObjectGuid();
        }

        return ObjectGuid();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bAppearDelay)
        {
            m_creature->StopMoving();
            m_creature->AttackStop();

            if (m_uiAppearDelayTimer <= uiDiff)
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_bAppearDelay = false;
            }
            else
                m_uiAppearDelayTimer -= uiDiff;

            return;
        }

        if ((m_uiPhase == 1) || (m_uiPhase == 3))
        {
            Unit* pFireMagus;
            Unit* pFrostMagus;
            Unit* pArcaneMagus;

            if (!m_pFireMagusGuid.IsEmpty())
                pFireMagus = m_creature->GetMap()->GetUnit(m_pFireMagusGuid);

            if (!m_pFrostMagusGuid.IsEmpty())
                pFrostMagus = m_creature->GetMap()->GetUnit(m_pFrostMagusGuid);

            if (!m_pArcaneMagusGuid.IsEmpty())
                pArcaneMagus = m_creature->GetMap()->GetUnit(m_pArcaneMagusGuid);

            if (pFireMagus && pFireMagus->isDead())
            {
                m_bFireMagusDead = true;
                if (!m_bIsAchievementTimerRunning)
                    m_bIsAchievementTimerRunning = true;
            }

            if (pFrostMagus && pFrostMagus->isDead())
            {
                m_bFrostMagusDead = true;
                if (!m_bIsAchievementTimerRunning)
                    m_bIsAchievementTimerRunning = true;
            }

            if (pArcaneMagus && pArcaneMagus->isDead())
            {
                m_bArcaneMagusDead = true;
                if (!m_bIsAchievementTimerRunning)
                    m_bIsAchievementTimerRunning = true;
            }

            if (m_bIsAchievementTimerRunning)
                m_uiAchievementTimer += uiDiff;

            if (m_bFireMagusDead && m_bFrostMagusDead && m_bArcaneMagusDead)
            {
                if (m_uiAchievementTimer <= ACHIEV_TIMER)
                    m_uiAchievementProgress +=1;

                m_creature->GetMotionMaster()->Clear();
                m_creature->GetMap()->CreatureRelocation(m_creature, CenterOfRoom[0][0], CenterOfRoom[0][1], CenterOfRoom[0][2], CenterOfRoom[0][3]);
                DoCast(m_creature, SPELL_TELESTRA_BACK);
                DoScriptText(SAY_MERGE, m_creature);
                m_creature->SetVisibility(VISIBILITY_ON);

                if (m_uiPhase == 1)
                    m_uiPhase = 2;
                else if (m_uiPhase == 3)
                    m_uiPhase = 4;

                m_bAppearDelay = true;
                m_bIsAchievementTimerRunning = false;
                m_uiAppearDelayTimer = 4*IN_MILLISECONDS;
                m_uiAchievementTimer = 0;
                m_pFireMagusGuid.Clear();
                m_pFrostMagusGuid.Clear();
                m_pArcaneMagusGuid.Clear();
            }
            else
                return;
        }

        if (((m_uiPhase == 0) && (m_creature->GetHealth() <= (m_creature->GetMaxHealth() * 0.5)))
           || (!m_bIsRegularMode && (m_uiPhase == 2) && (m_creature->GetHealth() <= (m_creature->GetMaxHealth() * 0.1))))
        {
            DoScriptText(urand(SAY_SPLIT_1,SAY_SPLIT_2), m_creature);
            m_creature->CastStop();
            m_creature->RemoveAllAuras();
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            m_bFireMagusDead = false;
            m_bFrostMagusDead = false;
            m_bArcaneMagusDead = false;
            m_uiPhase++;
            m_pFireMagusGuid = SplitPersonality(NPC_FIRE_MAGUS);
            m_pFrostMagusGuid = SplitPersonality(NPC_FROST_MAGUS);
            m_pArcaneMagusGuid = SplitPersonality(NPC_ARCANE_MAGUS);
            return;
        }

        if (m_uiCooldownTimer)
        {
            if (m_uiCooldownTimer <= uiDiff)
                m_uiCooldownTimer = 0;
            else
            {
                m_uiCooldownTimer -= uiDiff;
                return;
            }
        }

        if (m_uiIceNovaTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCast(pTarget, m_bIsRegularMode ? SPELL_ICE_NOVA_N : SPELL_ICE_NOVA_H);
                m_uiCooldownTimer = 1.5*IN_MILLISECONDS;
            }
            m_uiIceNovaTimer = 15*IN_MILLISECONDS;
        }
        else
            m_uiIceNovaTimer -= uiDiff;

        if (m_uiGravityWellTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->getVictim())
            {
                DoCast(pTarget, SPELL_GRAVITY_WELL);
                m_uiCooldownTimer = 6*IN_MILLISECONDS;
            }
            m_uiGravityWellTimer = 15*IN_MILLISECONDS;
        }
        else
            m_uiGravityWellTimer -= uiDiff;

        if (m_uiFirebombTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCast(pTarget, m_bIsRegularMode ? SPELL_FIREBOMB_N : SPELL_FIREBOMB_H);
                m_uiCooldownTimer = 2*IN_MILLISECONDS;
            }
            m_uiFirebombTimer = 2*IN_MILLISECONDS;
        }
        else
            m_uiFirebombTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_telestra(Creature* pCreature)
{
    return new boss_telestraAI (pCreature);
}

void AddSC_boss_telestra()
{
    Script *pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_telestra";
    pNewScript->GetAI = &GetAI_boss_telestra;
    pNewScript->RegisterSelf();
}
