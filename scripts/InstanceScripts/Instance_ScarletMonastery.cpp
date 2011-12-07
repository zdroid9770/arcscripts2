/*
 * ArcScripts for ArcEmu MMORPG Server
 * Copyright (C) 2009-2010 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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
		MOONSCRIPT_FACTORY_FUNCTION(VishasAI, MoonScriptCreatureAI);
		VishasAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(SHADOW_WORD, Target_RandomPlayer, 20, 0, 8);

			AddEmote(Event_OnCombatStart, "Tell me... tell me everything!", Text_Yell, 5847);
			AddEmote(Event_OnTargetDied, "Purged by pain!", Text_Yell, 5848);

			m_uiSay = 0;
		};

		void OnCombatStop(Unit* pTarget)
		{
			m_uiSay = 0;

			ParentClass::OnCombatStop(pTarget);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 75.0f && m_uiSay == 0)
			{
				Emote("Naughty secrets!", Text_Yell, 5849);
				m_uiSay++;
			}

			if(GetHealthPercent() <= 25.0f && m_uiSay == 1)
			{
				Emote("I'll rip the secrets from your flesh!", Text_Yell, 5850);
				m_uiSay++;
			}

			ParentClass::AIUpdate();
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
		MOONSCRIPT_FACTORY_FUNCTION(ThalnosAI, MoonScriptCreatureAI);
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
			if(GetHealthPercent() <= 50.0f && m_bEmoted == false)
			{
				Emote("No rest, for the angry dead.", Text_Yell, 5846);
				m_bEmoted = true;
			}

			ParentClass::AIUpdate();
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
		MOONSCRIPT_FACTORY_FUNCTION(LokseyAI, MoonScriptCreatureAI);
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
		MOONSCRIPT_FACTORY_FUNCTION(DoanAI, MoonScriptCreatureAI);
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
			if(GetHealthPercent() <= 50.0f && !m_bShielded)
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
		MOONSCRIPT_FACTORY_FUNCTION(HerodAI, MoonScriptCreatureAI);
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

			ParentClass::OnCombatStop(pTarget);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 40.0f && m_bEnraged == false)
			{
				ApplyAura(ENRAGESPELL);
				Emote("Light, give me strength!", Text_Yell,  5833);
			}

			ParentClass::AIUpdate();
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
		MOONSCRIPT_FACTORY_FUNCTION(MograineAI, MoonScriptCreatureAI);
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
			GameObject * pDoor = _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1173.01f, 1389.91f, 31.9723f, 104600);
			if(pDoor != NULL
				pDoor->SetState(State_Active);
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
		MOONSCRIPT_FACTORY_FUNCTION(WhitemaneAI, MoonScriptBossAI);
		WhitemaneAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Mograine has fallen? You shall pay for this treachery!", Text_Yell, 5838);
			AddEmote(Event_OnTargetDied, "The light has spoken!", Text_Yell, 5839);
			AddSpell(SMITE, Target_Current, 15.0f, 2.5f, 0);
			
			SetPhase(1);
		}

		void OnDamageTaken(Unit* mAttacker, uint32 fAmount)
		{
			if(fAmount < 5)
				return;
	
			// <50% hp -> We go to phase 1
			if(GetHealthPercent() <= 50.0f && GetPhase() == 1)
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
#define BLOOD 40412 //Need a better spell
#define PWS 11647 //PWS = Power Word: Shield 

class FairbanksAI : public CreatureAIScript
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(WhitemaneAI, MoonScriptBossAI);
		WhitemaneAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddEmote(Event_OnTargetDied, "Ha! Had enough?", Text_Yell, 0);
			AddSpell(BLOOD, 15.0f, 0, 0);
			AddSpell(PWS, 15.0f, 0, 0);
		}
};

class ScarletTorch : public GameObjectAIScript
{
	public:
		ScarletTorch(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new ScarletTorch(GO); }

		void OnActivate(Player* pPlayer)
		{
			GameObject* SecretDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(1167.79f, 1347.26f, 31.5494f, 97700);
			if(SecretDoor != NULL)
				SecretDoor->SetState(SecretDoor->GetState() == State_Inactive ? State_Active : State_Inactive);
		}
};

class ArmoryLever : public GameObjectAIScript
{
	public:
		ArmoryLever(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new ArmoryLever(GO); }

		void OnActivate(Player* pPlayer)
		{
			GameObject* ArmoryDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2886.31f, -827.261f, 160.336f, 101851);
			if(ArmoryDoor != NULL)
				ArmoryDoor->SetState(ArmoryDoor->GetState() == State_Inactive ? State_Active : State_Inactive);
		}
};

class CathedralLever: public GameObjectAIScript
{
	public:
		CathedralLever(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new CathedralLever(GO); }

		void OnActivate(Player* pPlayer)
		{
			GameObject* CathedralDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2908.18f, -818.203f, 160.332f, 101850);
			if(CathedralDoor != NULL)
				CathedralDoor->SetState(CathedralDoor->GetState() == State_Inactive ? State_Active : State_Inactive);
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
