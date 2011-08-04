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
SDName: Icecrown
SD%Complete: 100
SDComment: Vendor support: 34885 Quest Support: 14107
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_dame_evniki_kapsalis
npc_scourge_conventor
npc_fallen_hero_spirit
EndContentData */

#include "precompiled.h"

/*######
## npc_dame_evniki_kapsalis
######*/

enum
{
    TITLE_CRUSADER    = 123
};

bool GossipHello_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->HasTitle(TITLE_CRUSADER))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_dame_evniki_kapsalis(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
    return true;
}

/*######
## npc_scourge_conventor  //quest 14107
######*/

// grip of scourge still needs implented and used

enum QuestFate // shared enum by conventor mob and fallen hero mob
{
    QUEST_THE_FATE_OF_THE_FALLEN        = 14107,
    NPC_FALLEN_HERO_SPIRIT              = 32149,
    NPC_FALLEN_HERO_SPIRIT_PROXY        = 35055,
};

enum
{
    SPELL_CONE_OF_COLD              = 20828,
    SPELL_FORST_NOVA                = 11831,
    SPELL_FROSTBOLT                 = 20822,
    SPELL_GRIP_OF_THE_SCOURGE       = 60212,     // spell casted by mob
};

struct MANGOS_DLL_DECL npc_scourge_conventorAI : public ScriptedAI
{
    npc_scourge_conventorAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiConeofCold_Timer;
    uint32 m_uiFrostNova_Timer;
    uint32 m_uiFrostBolt_Timer;
    //uint32 m_uiGrip_Timer;

    void Reset()
    {
        m_uiConeofCold_Timer  = 10000;
        m_uiFrostNova_Timer    = 11000;
        m_uiFrostBolt_Timer    = 9000;
        //m_uiGrip_Timer = 10000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiConeofCold_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CONE_OF_COLD);
            m_uiConeofCold_Timer = 10000;
        }
        else
            m_uiConeofCold_Timer -= uiDiff;

        if (m_uiFrostNova_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_FORST_NOVA);
            m_uiFrostNova_Timer = 11000;
        }
        else
            m_uiFrostNova_Timer -= uiDiff;

        if (m_uiFrostBolt_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_FROSTBOLT);
            m_uiFrostBolt_Timer = 9000;
        }
        else
            m_uiFrostBolt_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_npc_scourge_conventor(Creature* pCreature)
{
    return new npc_scourge_conventorAI(pCreature);
}

/*######
## npc_fallen_hero_spirit  //quest 14107
######*/

enum
{
    SAY_BLESS_1                         = -1000594,
    SAY_BLESS_2                         = -1000595,
    SAY_BLESS_3                         = -1000596,
    SAY_BLESS_4                         = -1000597,
    SAY_BLESS_5                         = -1000598,

    SPELL_STRIKE                        = 11976,
    SPELL_BLESSING_OF_PEACE             = 66719,     //spell casted from relic of light
    GRIP_OF_THE_SCOURGE_AURA            = 60231      //might need server side spell script support (when mob has this spell it's immune to fate of light spell)
};


struct MANGOS_DLL_DECL npc_fallen_hero_spiritAI : public ScriptedAI
{
    npc_fallen_hero_spiritAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiStrike_Timer;

    void Reset()
    {
        m_uiStrike_Timer = 10000;
    }

    void SpellHit(Unit *pCaster, const SpellEntry *pSpell)
    {
        // if (m_creature->HasAura(GRIP_OF_THE_SCOURGE_AURA))
        //     return fasle;

        if (pCaster->GetTypeId() == TYPEID_PLAYER && m_creature->isAlive() && ((pSpell->Id == SPELL_BLESSING_OF_PEACE)))
        {
            if (((Player*)pCaster)->GetQuestStatus(QUEST_THE_FATE_OF_THE_FALLEN) == QUEST_STATUS_INCOMPLETE)
            {
                ((Player*)pCaster)->KilledMonsterCredit(NPC_FALLEN_HERO_SPIRIT_PROXY);
                m_creature->ForcedDespawn();
                switch(urand(0, 4))
                {
                    case 0: DoScriptText(SAY_BLESS_1, m_creature); break;
                    case 1: DoScriptText(SAY_BLESS_2, m_creature); break;
                    case 2: DoScriptText(SAY_BLESS_3, m_creature); break;
                    case 3: DoScriptText(SAY_BLESS_4, m_creature); break;
                    case 4: DoScriptText(SAY_BLESS_5, m_creature); break;
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiStrike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_STRIKE);
            m_uiStrike_Timer = 10000;
        }
        else
            m_uiStrike_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_npc_fallen_hero_spirit(Creature* pCreature)
{
    return new npc_fallen_hero_spiritAI(pCreature);
}


void AddSC_icecrown()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_dame_evniki_kapsalis";
    pNewScript->pGossipHello = &GossipHello_npc_dame_evniki_kapsalis;
    pNewScript->pGossipSelect = &GossipSelect_npc_dame_evniki_kapsalis;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_scourge_conventor";
    pNewScript->GetAI = &GetAI_npc_scourge_conventor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_fallen_hero_spirit";
    pNewScript->GetAI = &GetAI_npc_fallen_hero_spirit;
    pNewScript->RegisterSelf();
}
