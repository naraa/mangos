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
SDName: Boss_Brutallus
SD%Complete: 50
SDComment: Intro ONLY Madrigosa added here ENDING and transform to felmyst will be handled in felmyst script.
SD_Note To DEVS:: currently Madrigosa has a corpse already spawned i wanna switch this him already being where she is summoned but static and use script to set visibilty on and off  also will need to set corpse created after intro last til felmyst event starts
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
    SPELL_FROST_BLAST               = 45203,
    SPELL_ENCAPSULATE               = 44883,
    //NPC_MADRIGOSA                 = 25160,  // should already be defined in sunwell_plateau.h but here to remind myself
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

// intro stuff
        m_uiIntroTimer = 5000;
        m_uiIntroCount = 0;
        m_uiMadrigosaGuid.Clear();

        //TODO: correct me when pre-event implemented
        if (m_pInstance)
            m_pInstance->SetData(TYPE_BRUTALLUS, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        //if(pWho->GetTypeId() != TYPEID_PLAYER)
			//return;

        DoScriptText(YELL_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_BRUTALLUS, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
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
    }

    void SpellHitTarget(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_BURN)
            pCaster->CastSpell(pCaster, SPELL_BURN_AURA_EFFECT, true, NULL, NULL, m_creature->GetObjectGuid());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if(m_pInstance->GetData(TYPE_BRUTALLUS) == SPECIAL && m_bIsIntroNow)
        {
            if(m_uiIntroTimer < uiDiff)
            {
                switch(m_uiIntroCount)
                {
                case 0:
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if(Creature* Madrigosa = m_creature->SummonCreature(NPC_MADRIGOSA, 1465.831f, 647.065f, m_creature->GetPositionZ(), 4.729f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 300000))
                       m_uiMadrigosaGuid = Madrigosa->GetObjectGuid();
                    m_uiIntroTimer = 3000;
                    break;
                case 1:
                    if(Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_ICE_BARRIER, pMadrigosa);
                        m_creature->SetGuidValue(UNIT_FIELD_TARGET, pMadrigosa->GetObjectGuid());
                    }
                    m_uiIntroTimer = 6000;
                    break;
                 case 2:
                     if(Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                         DoScriptText(YELL_MADR_INTRO, pMadrigosa);
                      m_uiIntroTimer = 5000;
                    break;
                 case 3:
                    DoScriptText(YELL_INTRO, m_creature);
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        //m_creature->SetInCombatWith(pMadrigosa);
                        //m_creature->AI()->AttackStart(pMadrigosa);
                        //m_creature->AddThreat(pMadrigosa, 10000.0f);
                        //pMadrigosa->SetInCombatWith(m_creature);
                        //pMadrigosa->AI()->AttackStart(m_creature);
                        //pMadrigosa->AddThreat(m_creature, 10000.0f);
                    }
                    m_uiIntroTimer = 10000;
                    break;
                case 4:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_ICE_BLOCK, pMadrigosa);
                        pMadrigosa->CastSpell(m_creature, SPELL_FROST_BLAST, true);
                    }
                    m_uiIntroTimer = 2000;
                    break;
                case 5:
                    if (Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                        pMadrigosa->CastSpell(m_creature, SPELL_FROST_BLAST, true);
                    m_uiIntroTimer = 2000;
                    break;
                case 6:
                    if(Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                       pMadrigosa->CastSpell(m_creature, SPELL_FROST_BLAST, true);
                       m_uiIntroTimer = 2000;
                    break;
                case 7:
                    DoScriptText(YELL_INTRO_BREAK_ICE, m_creature);
                    m_uiIntroTimer = 5000;
                    break;
                case 8:
                    if(Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        pMadrigosa->CastSpell(m_creature, SPELL_ENCAPSULATE, true);
                        DoScriptText(YELL_MADR_TRAP, pMadrigosa);
                    }
                    m_uiIntroTimer = 15000;
                    break;
                case 9:
                    DoScriptText(YELL_INTRO_CHARGE, m_creature);
                    //if(Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    // m_creature->GetMotionMaster()->MoveChase(pMadrigosa);
                    m_uiIntroTimer = 3000;
                    break;
                case 10:
                    if(Creature* pMadrigosa = m_pInstance->instance->GetCreature(m_uiMadrigosaGuid))
                    {
                        DoScriptText(YELL_MADR_DEATH, pMadrigosa);
                        //pMadrigosa->setDeathState(CORPSE);  either this or line below
                        pMadrigosa->DealDamage(pMadrigosa, pMadrigosa->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                    }
                    m_uiIntroTimer = 5000;
                    break;
                case 11:
                    DoScriptText(YELL_INTRO_KILL_MADRIGOSA, m_creature);
                    m_uiIntroTimer = 6000;
                    break;
                case 12:
                    DoScriptText(YELL_INTRO_TAUNT, m_creature);
                    // should doing something with ice barrier right here or be handled in instance script
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    m_bIsIntroNow = false;
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
            pInstance->SetData(TYPE_BRUTALLUS, SPECIAL);
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
