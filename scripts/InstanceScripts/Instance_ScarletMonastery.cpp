/*
 * ArcScripts2 Scripts for Arcemu MMORPG Server
 * Copyright (C) 2011-2012 ArcScripts2 team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Setup.h"

/************************************************************************/
/* Instance_ScarletMonastery.cpp Script									*/
/************************************************************************/

/*
	Graveyard
*/

// Interrogator Vishas
#define VISHAS 3983
#define SHADOW_WORD 2767

class VishasAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(VishasAI)
		VishasAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(SHADOW_WORD, Target_RandomPlayer, 20, 0, 8);

			AddEmote(Event_OnCombatStart, "Tell me... tell me everything!", Text_Yell, 5847);
			AddEmote(Event_OnTargetDied, "Purged by pain!", Text_Yell, 5848);

			m_uiSay = 0;
		}

		void OnCombatStop(Unit* pTarget)
		{
			m_uiSay = 0;
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 75 && m_uiSay == 0)
			{
				Emote("Naughty secrets!", Text_Yell, 5849);
				m_uiSay++;
			}

			if(GetHealthPercent() <= 25 && m_uiSay == 1)
			{
				Emote("I'll rip the secrets from your flesh!", Text_Yell, 5850);
				m_uiSay++;
			}
		}

	private:
		uint8 m_uiSay;
};

// Bloodmage Thalnos
#define THALNOS 4543
#define SHADOW_BOLT 9613
#define FLAME_SPIKE 8814

class ThalnosAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ThalnosAI)
		ThalnosAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(SHADOW_BOLT, Target_RandomPlayer, 20, 3.0f, 2);
			AddSpell(FLAME_SPIKE, Target_RandomPlayerDestination, 20, 3.0f, 14);

			AddEmote(Event_OnCombatStart, "We hunger for vengeance.", Text_Yell, 5844);
			AddEmote(Event_OnTargetDied, "More... More souls.", Text_Yell, 5845);

			m_bEmoted = false;
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 50 && m_bEmoted == false)
			{
				Emote("No rest, for the angry dead.", Text_Yell, 5846);
				m_bEmoted = true;
			}
		}

	private:
		bool m_bEmoted;
};

/*
	Library
*/
//Houndmaster Loksey

#define LOKSEY 3974

class LokseyAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(LokseyAI)
		LokseyAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(6742, Target_Self, 5, 0, 40);
			AddEmote(Event_OnCombatStart, "Release the hounds!", Text_Yell, 5841);
		}
};

// Arcanist Doan

#define DOAN 6487
#define SHIELD 9438
#define NOVA 9435
#define POLY 13323
#define SILENCE 30225
#define ARCANE_EXP 9433

class DoanAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DoanAI)
		DoanAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(SILENCE, Target_Self, 25, 1.5f, 14);
			AddSpell(POLY, Target_SecondMostHated, 15, 1.5f, 10);
			AddSpell(ARCANE_EXP, Target_Self, 20, 0, 10);

			AddEmote(Event_OnCombatStart, "You will not defile these mysteries!", Text_Yell, 5842);

			m_bShielded = false;
		}

		void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
		{
			if(GetHealthPercent() <= 50 && !m_bShielded)
			{
				ApplyAura(SHIELD);
				Emote("Burn in righteous fire!", Text_Yell, 5843);
				_unit->CastSpell(_unit, NOVA, false);
				m_bShielded = true;
			}
		}

	private:
		bool m_bShielded;
};

/*
	Armory
*/

// Herod
#define HEROD 3975
#define WHIRLWINDSPELL 9632
#define CHARGE 22911
#define ENRAGESPELL 8269
#define AGGRO4 5830
#define KILL 5831
#define WHIRLWIND 5832
#define HEROD_ENRAGE 5833

class HerodAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(HerodAI)
		HerodAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(WHIRLWINDSPELL, Target_Self, 12, 0, 12)->AddEmote("Blades of Light!", Text_Yell, 5832);
			AddSpell(CHARGE, Target_RandomPlayer, 6, 0, 20);

			AddEmote(Event_OnCombatStart, "Ah, I've been waiting for a real challenge!", Text_Yell, 5830);
			AddEmote(Event_OnTargetDied, "Ha, is that all?", Text_Yell, 5831);

			m_bEnraged = false;
		}

		void OnCombatStop(Unit* pTarget)
		{
			m_bEnraged = false;
			RemoveAura(ENRAGESPELL);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 40 && m_bEnraged == false)
			{
				ApplyAura(ENRAGESPELL);
				Emote("Light, give me strength!", Text_Yell,  5833);
			}
		}

	protected:
		bool    m_bEnraged;
};

/*
	Cathedral
*/

// Scarlet Commander Mograine

#define COMMANDER_MOGRAINE 3976
#define HAMMER 32416
#define CRUSADER 14517
#define RESTALK 5835

class MograineAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(MograineAI)
		MograineAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Infidels. They must be purified!", Text_Yell, 5835);
			AddEmote(Event_OnTargetDied, "Unworthy.", Text_Yell, 5836);
			AddSpell(SHIELD, Target_Self, 5.0f, 0, 0);
			AddSpell(HAMMER, Target_Self, 10.0f, 0, 0);
			AddSpell(CRUSADER, Target_Current, 30.0f, 0, 0);
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);
			RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			if(GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1173.01f, 1389.91f, 31.9723f, 104600))
				pDoor->SetState(GAMEOBJECT_STATE_OPEN);
		}
};

// High Inquisitor Whitemane

#define WHITEMANE 3977
#define SMITE 9481
#define SLEEP 9256
#define RESURRECTION 25435

class WhitemaneAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WhitemaneAI)
		WhitemaneAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Mograine has fallen? You shall pay for this treachery!", Text_Yell, 5838);
			AddEmote(Event_OnTargetDied, "The light has spoken!", Text_Yell, 5839);
			AddSpell(SMITE, Target_Current, 15.0f, 2.5f, 0);
			
			SetPhase(1);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 50 && GetPhase() == 1)
			{
				SetPhase(2);
				_unit->GetAIInterface()->MoveTo(1154.85f,1403.92f,32.25f,3.466254f);
				ApplyAura(SLEEP);
				// Play sound, and send text.
				/*_unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Light, give me strength!");
					   ^^ Notes for myself */
				Emote("Arise, my champion!", Text_Yell, 5840);
				_unit->CastSpell(_unit, RESURRECTION, false);				
			}
		}

	protected:
		uint32 mPhase;  // NPC has 2 phases
		int nrspells;
		int Timer;
};

// High Inquisitor Fairbanks

//he has another event, he should tell ashbringer history and where in outlands he can just make to corrupted ashbringer,
//need equiped ashbringer, but as base this event has been removed since wotlk.

//TODO: check his texts
#define FAIRBANKS 4542
#define PWS 11647 //PWS = Power Word: Shield 

class FairbanksAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(FairbanksAI)
		FairbanksAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnTargetDied, "Ha! Had enough?", Text_Yell, 0);
			AddSpell(PWS, Target_Self, 15.0f, 0, 0);
		}
};

class ScarletTorch : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ScarletTorch)
		ScarletTorch(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player* pPlayer)
		{
			if(GameObject* SecretDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1167.79f, 1347.26f, 31.5494f, 97700))
				SecretDoor->SetState(SecretDoor->GetState() == GAMEOBJECT_STATE_CLOSED ? GAMEOBJECT_STATE_OPEN : GAMEOBJECT_STATE_CLOSED);
		}
};

class ArmoryLever : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ArmoryLever)
		ArmoryLever(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player* pPlayer)
		{
			if(GameObject* ArmoryDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2886.31f, -827.261f, 160.336f, 101851))
				ArmoryDoor->SetState(ArmoryDoor->GetState() == GAMEOBJECT_STATE_CLOSED ? GAMEOBJECT_STATE_OPEN : GAMEOBJECT_STATE_CLOSED);
		}
};

class CathedralLever: public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(CathedralLever)
		CathedralLever(GameObject* goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player* pPlayer)
		{
			if(GameObject* CathedralDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2908.18f, -818.203f, 160.332f, 101850))
				CathedralDoor->SetState(CathedralDoor->GetState() == GAMEOBJECT_STATE_CLOSED ? GAMEOBJECT_STATE_OPEN : GAMEOBJECT_STATE_CLOSED);
		}
};

void SetupScarletMonastery(ScriptMgr* mgr)
{
	mgr->register_creature_script(LOKSEY, &LokseyAI::Create);
	mgr->register_creature_script(VISHAS, &VishasAI::Create);
	mgr->register_creature_script(THALNOS, &ThalnosAI::Create);
	mgr->register_creature_script(COMMANDER_MOGRAINE, &MograineAI::Create);
	mgr->register_creature_script(WHITEMANE, &WhitemaneAI::Create);
	mgr->register_creature_script(FAIRBANKS, &FairbanksAI::Create);
	mgr->register_creature_script(HEROD, &HerodAI::Create);
	mgr->register_creature_script(DOAN, &DoanAI::Create);
	mgr->register_gameobject_script(97701, &ScarletTorch::Create);
	mgr->register_gameobject_script(101853, &CathedralLever::Create);
	mgr->register_gameobject_script(101852, &ArmoryLever::Create);
}
