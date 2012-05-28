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
#define CN_FENRUS 4274
#define CN_NENDOS 3927
#define CN_VOIDWALKER 4627
class ShadowfangKeepInstanceScript : public MoonInstanceScript
{
	public:
		MOONSCRIPT_INSTANCE_FACTORY_FUNCTION(ShadowfangKeepInstanceScript, MoonInstanceScript);
		ShadowfangKeepInstanceScript(MapMgr* pMapMgr) : MoonInstanceScript(pMapMgr){}

		void OnGameObjectActivate(GameObject* pGo, Player* Plr)
		{
			switch(pGo->GetEntry())
			{
				case 18900: AddLeverDoorState(pGo, 18934); break;	//adamant lever
				case 18901: AddLeverDoorState(pGo, 18936); break;	//?
				case 101811: AddLeverDoorState(pGo, 18935); break;//?
			}
		}

		void OnCreatureDeath(Creature* c, Unit* pUnit)
		{
			switch(c->GetEntry())
			{
				case CN_VOIDWALKER: AddGameObjectStateByEntry(18972, GAMEOBJECT_STATE_OPEN); break;
				case CN_NENDOS: AddGameObjectStateByEntry(18971, GAMEOBJECT_STATE_OPEN); break;
			}
		}
};

#define NPC_ADAMANT 3849
#define NPC_SORCERER 3850
#define MAX_PRISONER_WP 13
static Location DeathstalkerAdamantWP[]=
{
	{},
	(-250.923, 2116.26, 81.179, 0),
	(-255.049, 2119.39, 81.179, 0),
	(-254.129, 2123.45, 81.179, 0),
	(-253.898, 2130.87, 81.179, 0),
	(-249.889, 2142.31, 86.972, 0),
	(-248.205, 2144.02, 87.013, 0),
	(-240.553, 2140.55, 87.012, 0),
	(-237.514, 2142.07, 87.012, 0),
	(-235.638, 2149.23, 90.587, 0),
	(-237.188, 2151.95, 90.624, 0),
	(-241.162, 2153.65, 90.624, 0),
	(-241.13, 2154.56, 90.624, 0),
};

static Location SorcererAshcrombeWP[]=
{
	{},
	{-241.817f, 2122.9f, 81.179f, 0},
	{-247.139f, 2124.89f, 81.179f, 0},
	{-253.179f, 2127.41f, 81.179f, 0},
	{-253.898f, 2130.87f, 81.179f, 0},
	{-249.889f, 2142.31f, 86.972f, 0},
	{-248.205f, 2144.02f, 87.013f, 0},
	{-240.553f, 2140.55f, 87.012f, 0},
	{-237.514f, 2142.07f, 87.012f, 0},
	{-235.638f, 2149.23f, 90.587f, 0},
	{-237.188f, 2151.95f, 90.624f, 0},
	{-241.162f, 2153.65f, 90.624f, 0},
	{-241.13f, 2154.56f, 90.624f, 0}
};

class ShadowfangPrisonerGossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* Plr)
		{
			Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr, 1, Arcemu::Gossip::ICON_CHAT, "Please unlock the courtyard door.");
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char * Code)
		{
			MoonScriptCreatureAI* pUnit = dynamic_cast<MoonScriptCreatureAI *>(TO_CREATURE(pObject)->GetScript());
			TO_CREATURE(pObject)->SetUInt32Value(UNIT_NPC_FLAGS, 0);
			pUnit->StartWaypointMovement();
		}
};

class ShadowfangPrisonerAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ShadowfangPrisonerAI)
		ShadowfangPrisonerAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			StopWaypointMovement();
			SetCanEnterCombat(false);
			pEntry = _unit->GetEntry();

			if(pEntry == NPC_ADAMANT)
			{
				for(uint8 i = 1; i<=MAX_PRISONER_WP; i++)
					AddWaypoint(CreateWaypoint(i, 0, Flag_Walk, DeathstalkerAdamantWP[i]));
			}
			else
			{
				for(uint8 i = 1; i<=MAX_PRISONER_WP; i++)
					AddWaypoint(CreateWaypoint(i, 0, Flag_Walk, SorcererAshcrombeWP[i]));
			}
		}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			switch(iWaypointId)
			{
				case 1:
					if(pEntry == NPC_SORCERER)
						Emote("Follow me and I\'ll open the courtyard door for you.", Text_Say, 0);
					else
						Emote("Free from this wretched cell at last! Let me show you to the courtyard....", Text_Say, 0);
					break;
				case 11:
					if(pEntry == NPC_SORCERER)
						Emote("I have just the spell to get this door open. Too bad the cell doors weren\'t locked so haphazardly.", Text_Say, 0);
					else
						Emote("You are indeed courageous for wanting to brave the horrors that lie beyond this door.", Text_Say, 0);
					_unit->GetAIInterface()->setWaypointToMove(iWaypointId + 1);
					break;
				case 12:
					SetMoveType(Move_DontMoveWP);
					GameObject * pDoor = GetNearestGameObject(18895);
					if(pEntry == NPC_SORCERER)
					{
						_unit->CastSpell(_unit, 6421, true);	//Ashcrombe's Unlock
						Emote("There it is! Wide open. Good luck to you conquering what lies beyond. I must report back to the Kirin Tor at once!", Text_Say, 0, EMOTE_ONESHOT_NONE, 4*SEC_IN_MS);
						if(pDoor)
							pDoor->SetState(GAMEOBJECT_STATE_OPEN);
						_unit->CastSpell(_unit, 6422, true);	//Ashcrombe's Teleport
						Emote("%s vanishes.", Text_Say, 0, EMOTE_ONESHOT_NONE, 6*SEC_IN_MS);
						Despawn();
					}else
					{
						_unit->Emote(EMOTE_ONESHOT_USESTANDING);
						if(pDoor)
							pDoor->SetState(GAMEOBJECT_STATE_OPEN);
						Emote("There we go!", Text_Say, 0);
						Emote("Good luck with Arugal. I must hurry back to Hadrec now.", Text_Say, 0, EMOTE_ONESHOT_NONE, 2*SEC_IN_MS);
						Emote("%s vanishes.", Text_Say, 0, EMOTE_ONESHOT_NONE, 3*SEC_IN_MS);
						Despawn();
					}
					break;
			}

				_unit->GetAIInterface()->setWaypointToMove(iWaypointId + 1);
		}

	private:
		uint32 pEntry;
};

// Commander Springvale AI
#define CN_SPRINGVALE 4278
class SpringvaleAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SpringvaleAI)
		SpringvaleAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{	
			AddSpell(1026, Target_Self, 10, 2.5f, 0);			// Holy Light	
			DevoAura = AddSpell(10290, Target_Self, 0, 0, 0);	// Devotion Aura
			DivineProt = AddSpell(498, Target_Self, 0, 0, 0);	// Divine Protection
			AddSpell(5588, Target_Current, 12, 0, 60);			// Hammer of Justice
		}

		void OnCombatStart(Unit* pTarget)
		{
			if(!GetUnit()->HasAura(DevoAura->mInfo->Id))
				CastSpellNowNoScheduling(DevoAura);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 20)
			{
				CastSpellNowNoScheduling(DivineProt);
				DivineProt->mEnabled = false;
			}
		}

	protected:
		SpellDesc* DevoAura;
		SpellDesc* DivineProt;
};

// Odo the Blindwatcher AI
#define CN_BLINDWATCHER 4279
class BlindWatcherAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BlindWatcherAI)
		BlindWatcherAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			HowlingRage1 = AddSpell(7481, Target_Self, 0, 5, 0);
			HowlingRage2 = AddSpell(7483, Target_Self, 0, 1.5f, 0);
			HowlingRage3 = AddSpell(7484, Target_Self, 0, 1.5f, 0);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 75 && GetPhase() == 1)
					SetPhase(2, HowlingRage1);
			else if(GetHealthPercent() <= 45 && GetPhase() == 2)
			{
				if(GetUnit()->HasAura(7481))
					RemoveAura(7481);
				SetPhase(3, HowlingRage2);
			}else if(GetHealthPercent() <= 20 && GetPhase() == 3)
			{
				if(GetUnit()->HasAura(7483))
					RemoveAura(7483);
				SetPhase(4, HowlingRage3);
			}
		}

	protected:
		SpellDesc* HowlingRage1,* HowlingRage2,* HowlingRage3;
};

// Fenrus the Devourer AI
static Location VWSpawns[] =
{
	{ -154.274368f, 2177.196533f, 128.448517f, 5.760980f},
	{ -142.647537f, 2181.019775f, 128.448410f, 4.178475f},
	{ -139.146774f, 2168.201904f, 128.448364f, 2.650803f},
	{ -150.860092f, 2165.156250f, 128.448502f, 0.999966f},
};

class FenrusAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(FenrusAI)
		FenrusAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(7125, Target_Current, 12, 1.5f, 60);
		}

		void OnDied(Unit*  pKiller)
		{
			_unit->SendChatMessageAlternateEntry(4275, CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Who dares interfere with the Sons of Arugal?");
			_unit->PlaySoundToSet(5791);

			MoonScriptCreatureAI* voidwalker = NULL;
			// Spawn 4 x Arugal's Voidwalkers
			for(int x = 0; x < 4; x++)
			{
				voidwalker = SpawnCreature(4627, VWSpawns[x].x, VWSpawns[x].y, VWSpawns[x].z, VWSpawns[x].o);
				if(voidwalker)
				{
					voidwalker->AggroNearestPlayer();
					voidwalker = NULL;
				}
			}
		}
};

// Archmage Arugal AI
#define CN_ARUGAL 4275
class ArugalAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ArugalAI)
		ArugalAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "You, too, shall serve!", Text_Yell, 5793);
			AddEmote(Event_OnTargetDied, "Another falls!", Text_Yell, 5795);

			AddSpell(7588, Target_Current, 25, 3, 0);	// Void Bolt
			AddSpell(7803, Target_Self, 10, 0, 0);		// Thunder Shock
			AddSpell(7621, Target_RandomPlayer, 5, 0, 0, 0, 0, false, "Release your rage!", Text_Yell, 5797);	// Arugal's Curse
			AddSpell(10418, Target_Self, 10, 2, 0);		// Arugal spawn-in spell (Teleport)
		}
};

//Deathstalker Adamant
#define CN_ADAMANT 3849

//Rethilgore AI
#define CN_RETHILGORE 3914
class RETHILGOREAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(RETHILGOREAI)
		RETHILGOREAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnDied(Unit*  pKiller)
		{
			_unit->SendChatMessageAlternateEntry(3849, CHAT_MSG_MONSTER_SAY, LANG_GUTTERSPEAK, "About time someone killed the wretch.");
			_unit->SendChatMessageAlternateEntry(3850, CHAT_MSG_MONSTER_SAY, LANG_COMMON, "For once I agree with you... scum.");      // dont know the allys text yet
		}
};

void SetupShadowfangKeep(ScriptMgr* mgr)
{
	mgr->register_instance_script(33, &ShadowfangKeepInstanceScript::Create);

	//prisoners
	mgr->register_creature_gossip(NPC_ADAMANT, new ShadowfangPrisonerGossip);
	mgr->register_creature_gossip(NPC_SORCERER, new ShadowfangPrisonerGossip);
	mgr->register_creature_script(NPC_ADAMANT, &ShadowfangPrisonerAI::Create);
	mgr->register_creature_script(NPC_SORCERER, &ShadowfangPrisonerAI::Create);

	//creature scripts
	mgr->register_creature_script(CN_SPRINGVALE, &SpringvaleAI::Create);
	mgr->register_creature_script(CN_BLINDWATCHER, &BlindWatcherAI::Create);
	mgr->register_creature_script(CN_FENRUS, &FenrusAI::Create);
	mgr->register_creature_script(CN_ARUGAL, &ArugalAI::Create);
	mgr->register_creature_script(CN_RETHILGORE, &RETHILGOREAI::Create);
}
