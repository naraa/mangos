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
SDName: Boss_Brutallus
SD%Complete: 85%
SDComment: Intro ONLY Madrigosa  -> Supported here (look to felmyst for outro and transform)
GO_ICE_Barrier needs work
SDCategory: Sunwell Plateau
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

enum BrutallusTexts
{
    YELL_INTRO                      = -1580017,
    YELL_INTRO_BREAK_ICE            = -1580018,
    YELL_INTRO_CHARGE               = -1580019,
    YELL_INTRO_KILL_MADRIGOSA       = -1580020,
    YELL_INTRO_TAUNT                = -1580021,

    YELL_MADR_ICE_BARRIER           = -1580031,
    YELL_MADR_INTRO                 = -1580032,
    YELL_MADR_ICE_BLOCK             = -1580033,
    YELL_MADR_TRAP                  = -1580034,
    YELL_MADR_DEATH                 = -1580035,

    YELL_AGGRO                      = -1580022,
    YELL_KILL1                      = -1580023,
    YELL_KILL2                      = -1580024,
    YELL_KILL3                      = -1580025,
    YELL_LOVE1                      = -1580026,
    YELL_LOVE2                      = -1580027,
    YELL_LOVE3                      = -1580028,
    YELL_BERSERK                    = -1580029,
    YELL_DEATH                      = -1580030,
};

enum BrutallusSpells
{
    SPELL_METEOR_SLASH              = 45150,
    SPELL_BURN                      = 45141,
    SPELL_BURN_AURA_EFFECT          = 46394,
    SPELL_STOMP                     = 45185,
    SPELL_BERSERK                   = 26662,
};

enum MadrigosaSpells
{
    SPELL_FROST_BLAST               = 44843,
    SPELL_ENCAPSULATE               = 44883,    // gotta be the wrong encapsulate for intro
    SPELL_FROST_DOOR              = 45203,   Starting to think madrigosa casthis at game object ice barrier doodad to make the ice barrier door at intro
    //SPELL_BREAK_ICE               = 46650,  // Graphic of spell when Ice Barrier Breaks
    //SPELL_OPEN_DOOR               = 46652, // outro
    //SPELL_INTRO_ENCAPSULATE            =   45665,   used in intro
    //SPELL_INTRO_ENCAPSULATE_CHANELLING =   45661    used in intro
    SPELL_FELMYST_SUMMON            = 45069, //  Madrigosa uses this spell to summon invis base of felmyst --- Invis base needs to hide(spawn in center of madri corpse) he shouldnt be a static spawn
};

struct MANGOS_DLL_DECL boss_brutallusAI : public ScriptedAI
{
    boss_brutallusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsIntroNow = true;
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiSlashTimer;
    uint32 m_uiBurnTimer;
    uint32 m_uiStompTimer;
    uint32 m_uiBerserkTimer;
    uint32 m_uiLoveTimer;

// Intro stuff
    uint32 m_uiIntroCount;
    uint32 m_uiIntroTimer;
    bool m_bIsIntroNow;
    ObjectGuid m_uiMadrigosaGuid;

    void Reset()
    {
        m_uiSlashTimer = 11000;
        m_uiStompTimer = 30000;
        m_uiBurnTimer = 60000;
        m_uiBerserkTimer = 360000;
        m_uiLoveTimer = urand(10000, 17000);

// Intro stuff
        m_uiIntroTimer = 5000;
        m_uiIntroCount = 0;
        m_uiMadrigosaGuid.Clear();

        //if (m_pInstance)
          //  m_pInstance->SetData(TYPE_BRUTALLUS, NOT_STARTED);

        if (m_pInstance->GetData(TYPE_BRUTALLUS) == NOT_STARTED)
        {
            if (Creature* pMadrigosa = m_pInstance->GetSingleCreatureFromStorage(NPC_MADRIGOSA))
            {
                pMadrigosa->SetDeathState(ALIVE);
                pMadrigosa->SetHealth(424900);
            }
        }
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance->GetData(TYPE_BRUTALLUS) == IN_PROGRESS)
           DoScriptText(YELL_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        //won't yell killing pet/other unit
        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        switch(urand(0, 2))
        {
            case 0: DoScriptText(YELL_KILL1, m_creature); break;
            case 1: DoScriptText(YELL_KILL2, m_creature); break;
            case 2: DoScriptText(YELL_KILL3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(YELL_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_BRUTALLUS, DONE);

// should spawn felmyst Invis base inside madrigosa corpse
// Upon Brutallus Death his bloods runs over to madrigosa corpse and felmyst is born
        if (Creature* pMadrigosa = m_pInstance->GetSingleCreatureFromStorage(NPC_MADRIGOSA))
            pMadrigosa->CastSpell(pMadrigosa->GetPositionX(),pMadrigosa->GetPositionY(),pMadrigosa->GetPositionZ(),SPELL_FELMYST_SUMMON, true);
    }

    void SpellHitTarget(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_BURN)
            pCaster->CastSpell(pCaster, SPELL_BURN_AURA_EFFECT, true, NULL, NULL, m_creature->GetObjectGuid());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance->GetData(TYPE_BRUTALLUS) == SPECIAL && m_bIsIntroNow)
        {
            if (m_uiIntroTimer < uiDiff)
            {
                switch(m_uiIntroCount)
                {
                case 0:
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Creature* pMadrigosa = m_pInstance->GetSingleCreatureFromStorage(NPC_MADRIGOSA))
                        m_uiMadrigosaGuid = pMadrigosa->GetObjectGuid();
                    m_uiIntroTimer = 3000;
                    break;
                case 1:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_ICE_BARRIER, pMadrigosa);
                        m_creature->SetGuidValue(UNIT_FIELD_TARGET, pMadrigosa->GetObjectGuid());
                    }
                    m_uiIntroTimer = 6000;
                    break;
                case 2:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                        DoScriptText(YELL_MADR_INTRO, pMadrigosa);
                    m_uiIntroTimer = 5000;
                    break;
                case 3:
                    DoScriptText(YELL_INTRO, m_creature);
                    m_uiIntroTimer = 10000;
                    break;
                case 4:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_ICE_BLOCK, pMadrigosa);
                        pMadrigosa->CastSpell(m_creature, SPELL_FROST_DOOR, true);
                    }
                    m_uiIntroTimer = 2000;
                    break;
                case 5:
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                            m_creature->SetInCombatWith(pMadrigosa);
                            m_creature->AI()->AttackStart(pMadrigosa);
                            m_creature->AddThreat(pMadrigosa, 10000.0f);
                            pMadrigosa->SetInCombatWith(m_creature);
                            pMadrigosa->AI()->AttackStart(m_creature);
                            pMadrigosa->AddThreat(m_creature, 10000.0f);
                            m_creature->GetMotionMaster()->MoveChase(pMadrigosa);
                            pMadrigosa->CastSpell(m_creature, SPELL_FROST_BLAST, true);
                    }
                    m_uiIntroTimer = 4000;
                    break;
                case 6:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                       pMadrigosa->CastSpell(m_creature, SPELL_FROST_DOOR, true);
                       m_uiIntroTimer = 2000;
                    break;
                case 7:
                    DoScriptText(YELL_INTRO_BREAK_ICE, m_creature);
                    m_uiIntroTimer = 5000;
                    break;
                case 8:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_TRAP, pMadrigosa);
                    }
                    m_uiIntroTimer = 3000;
                    break;
                case 9:
                    DoScriptText(YELL_INTRO_CHARGE, m_creature);
                    m_uiIntroTimer = 3000;
                    break;
                case 10:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_DEATH, pMadrigosa);
                        pMadrigosa->SetDeathState(JUST_DIED);
                        pMadrigosa->SetHealth(0);
                        m_creature->GetMotionMaster()->Clear();
                    }
                    m_uiIntroTimer = 5000;
                    break;
                case 11:
                    DoScriptText(YELL_INTRO_KILL_MADRIGOSA, m_creature);
                    m_creature->GetMotionMaster()->Clear();
// His Yell here suppose to break Ice Barrier players by the barrier arent hit and knocked back in room  == 0 damge its all for show
                    m_uiIntroTimer = 6000;
                    break;
                case 12:
                    DoScriptText(YELL_INTRO_TAUNT, m_creature);
                    m_creature->GetMotionMaster()->Clear();
                    m_bIsIntroNow = false;
                    if (m_pInstance)
                        m_pInstance->SetData(TYPE_BRUTALLUS, IN_PROGRESS);
                    break;
                }
                ++m_uiIntroCount;
            }
            else m_uiIntroTimer -= uiDiff;

            DoMeleeAttackIfReady();

             return;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiLoveTimer < uiDiff)
        {
            switch(urand(0, 2))
            {
                case 0: DoScriptText(YELL_LOVE1, m_creature); break;
                case 1: DoScriptText(YELL_LOVE2, m_creature); break;
                case 2: DoScriptText(YELL_LOVE3, m_creature); break;
            }
            m_uiLoveTimer = urand(15000, 23000);
        }
        else
            m_uiLoveTimer -= uiDiff;

        if (m_uiSlashTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0)) // small walk around to keep meteorslash a frontal ability
           {
               DoCast(pTarget,SPELL_METEOR_SLASH);
               m_uiSlashTimer = 11000;
           }
        }
        else
            m_uiSlashTimer -= uiDiff;

        if (m_uiStompTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0)) //Stomp needs to be focus on main tank target
            {
                DoCastSpellIfCan(pTarget,SPELL_STOMP);

                if (pTarget->HasAura(SPELL_BURN_AURA_EFFECT, EFFECT_INDEX_0))
                    pTarget->RemoveAurasDueToSpell(SPELL_BURN_AURA_EFFECT);
            }

            m_uiStompTimer = 30000;
        }
        else
            m_uiStompTimer -= uiDiff;

        if (m_uiBurnTimer < uiDiff)
        {
            //returns any unit
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                //so we get owner, in case unit was pet/totem/etc
                if (Player* pPlayer = pTarget->GetCharmerOrOwnerPlayerOrPlayerItself())
                    DoCastSpellIfCan(pPlayer, SPELL_BURN);
            }

            m_uiBurnTimer = 60000;
        }
        else
            m_uiBurnTimer -= uiDiff;

        if (m_uiBerserkTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature,SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(YELL_BERSERK, m_creature);
                m_uiBerserkTimer = 20000;
            }
        }
        else
            m_uiBerserkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_brutallus(Creature* pCreature)
{
    return new boss_brutallusAI(pCreature);
}

bool AreaTrigger_at_madrigosa(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (ScriptedInstance* pInstance = (ScriptedInstance*)pPlayer->GetInstanceData())
    {
        //this simply set encounter state, and trigger ice barrier become active
        //bosses can start pre-event based on this new state
        if (pInstance->GetData(TYPE_BRUTALLUS) == NOT_STARTED)
            pInstance->SetData(TYPE_BRUTALLUS, SPECIAL); // in use in script above
    }

    return false;
}

void AddSC_boss_brutallus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_brutallus";
    pNewScript->GetAI = &GetAI_boss_brutallus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_madrigosa";
    pNewScript->pAreaTrigger = &AreaTrigger_at_madrigosa;
    pNewScript->RegisterSelf();
}
