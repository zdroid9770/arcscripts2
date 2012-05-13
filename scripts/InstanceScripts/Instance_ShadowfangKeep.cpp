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
				case 18900: AddLeverStateByEntry(18934); break;	//adamant lever
				case 18901: AddLeverStateByEntry(18936); break;	//?
				case 101811: AddLeverStateByEntry(18935); break;//?
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

// Commander Springvale AI
#define CN_SPRINGVALE 4278
class SpringvaleAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(SpringvaleAI, MoonScriptCreatureAI);
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

			ParentClass::OnCombatStart(pTarget);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 20)
			{
				CastSpellNowNoScheduling(DivineProt);
				DivineProt->mEnabled = false;
			}
			ParentClass::AIUpdate();
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
		MOONSCRIPT_FACTORY_FUNCTION(BlindWatcherAI, MoonScriptBossAI);
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
			ParentClass::AIUpdate();
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
		MOONSCRIPT_FACTORY_FUNCTION(FenrusAI, MoonScriptCreatureAI);
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
			ParentClass::OnDied(pKiller);
		}
};

// Archmage Arugal AI
#define CN_ARUGAL 4275
class ArugalAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ArugalAI, MoonScriptCreatureAI);
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
		MOONSCRIPT_FACTORY_FUNCTION(RETHILGOREAI, MoonScriptCreatureAI);
		RETHILGOREAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnDied(Unit*  pKiller)
		{
			_unit->SendChatMessageAlternateEntry(3849, CHAT_MSG_MONSTER_SAY, LANG_GUTTERSPEAK, "About time someone killed the wretch.");
			_unit->SendChatMessageAlternateEntry(3850, CHAT_MSG_MONSTER_SAY, LANG_COMMON, "For once I agree with you... scum.");      // dont know the allys text yet
			ParentClass::OnDied(pKiller);
		}
};

void SetupShadowfangKeep(ScriptMgr* mgr)
{
	mgr->register_instance_script(33, &ShadowfangKeepInstanceScript::Create);

	//creature scripts
	mgr->register_creature_script(CN_SPRINGVALE, &SpringvaleAI::Create);
	mgr->register_creature_script(CN_BLINDWATCHER, &BlindWatcherAI::Create);
	mgr->register_creature_script(CN_FENRUS, &FenrusAI::Create);
	mgr->register_creature_script(CN_ARUGAL, &ArugalAI::Create);
	mgr->register_creature_script(CN_RETHILGORE, &RETHILGOREAI::Create);
}
