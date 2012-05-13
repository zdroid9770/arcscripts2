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

//MagisterTerrace Script

//Bosses

//Selin Firehart Encounter

// Creature Entry's
#define TRASH_FelCrystal 24722
#define BOSS_SelinFireheart 24723

// Normal & Heroic Spells

/*
   Mana Rage
   Caster: Fel Crystal
   Details: Empowers the caster with fel energy, restoring their mana for 10 sec.
   Triggers: Increases the target's mana by 10%.
*/
#define FC_MANARAGE 44320
#define FC_MANARAGE_TRIGGER 44321

/*
   Fel Explosion
   Caster Selin Fireheart
   Details: Area of effect damage spell, cast continually until Selin is out of mana
*/
#define SF_FELEXPLOSION 44314
/*
   Drain Life
   Caster Selin Fireheart
   Details: Randomly targeted channeled spell, deals damage and heals Selin.
*/
#define SF_DRAINLIFE 44294

// Heroic Spells
/*
   Drain Mana (Heroic Mode Only)
   Caster Selin Fireheart
   Details: Randomly targeted channeled spell on a player with mana, drain Mana to the player and give it to Selin.
*/
#define SF_DRAINMANA 46153

// Fel Crystal Spawn Locations
static LocationExtra FelCrystals[] =
{
	{225.969f, -20.0775f, -2.9731f, 0.942478f, TRASH_FelCrystal},
	{226.314f, 20.2183f, -2.98127f, 5.32325f, TRASH_FelCrystal},
	{247.888f, -14.6252f, 3.80777f, 2.33874f, TRASH_FelCrystal},
	{248.053f, 14.592f, 3.74882f, 3.94444f, TRASH_FelCrystal},
	{263.149f, 0.309245f, 1.32057f, 3.15905f, TRASH_FelCrystal}
};

class SelinFireheartAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(SelinFireheartAI, MoonScriptCreatureAI);
		SelinFireheartAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(SF_DRAINLIFE, Target_RandomPlayer, 8, 0, 35);

			if(_unit->GetMapMgr()->iInstanceMode == MODE_HEROIC)
				AddSpell(SF_DRAINMANA, Target_RandomPlayer, 8, 0, 35);

			ManaRage = dbcSpell.LookupEntry(FC_MANARAGE);
			ManaRageTrigger = AddSpell(FC_MANARAGE_TRIGGER, Target_Self, 0, 0, 0);
			FelExplosion = AddSpell(SF_FELEXPLOSION, Target_Self, 0, 0, 0);
		}

		void OnCombatStart(Unit* pTarget)
		{
			/*
				Selin Fireheart starts with 0 mana and drains it from the felcrystals in the room
				- ToDo: Set it so mana regen is off
			*/
			_unit->SetUInt32Value(UNIT_FIELD_POWER1, 0);
			ParentClass::OnCombatStart(pTarget);
		}

		/*
			During the AIUpdate() Selin will spam FelExplosion until hes out of mana
			He will then attempt to gain mana from a FelCrystal thats in the room by running to them
		*/
		void AIUpdate()
		{
			// 10% of his mana according to wowhead is 3231 which is whats needed to cast FelExplosion
			if(GetManaPercent() < 10 || FelExplosion->mEnabled == false)
				Mana();
			else if(!IsCasting())// Mana is greater than 10%
				CastFelExplosion();

			ParentClass::AIUpdate();
		}

		void Mana()
		{
			/*
				Attempt to get a Fel Crystal and move to it if not in range.
				Once in range we get the FelCrystal to cast Mana Rage on Selin
			*/
			Unit* FelCrystal = NULL;
			PreventActions(false);

			FelCrystal = FindFelCrystal();

			if(!FelCrystal || !FelCrystal->isAlive())
			{
				PreventActions(true);
				FelCrystal = NULL;
				return;
			}

			// Not in range
			if(_unit->GetDistance2dSq(FelCrystal) > 100)
			{
				MoveTo(FelCrystal->GetPositionX(), FelCrystal->GetPositionY(), FelCrystal->GetPositionZ());
				FelCrystal = NULL;
				return;
			}

			_unit->GetAIInterface()->StopMovement(0);

			if(!FelCrystal->GetCurrentSpell())
				FelCrystal->CastSpell(_unit, ManaRage, false);

			// Mana Rage giving of mana doesnt work so we give 10%(3231) / AIUpdate() Event.
			CastSpellNowNoScheduling(ManaRageTrigger);
			uint32 mana = _unit->GetPower(POWER_TYPE_MANA) + 3231;
			if(mana >= _unit->GetMaxPower(POWER_TYPE_MANA))
				mana = _unit->GetMaxPower(POWER_TYPE_MANA);

			_unit->SetUInt32Value(UNIT_FIELD_POWER1, mana);

			// Re-Enable FelExplosion
			if(GetManaPercent() >= 100)
				PreventActions(true);

			FelCrystal = NULL;
		}

		void PreventActions(bool Allow)
		{
			FelExplosion->mEnabled = Allow;
			SetAllowMelee(Allow);
			SetAllowRanged(Allow);
			SetAllowSpell(Allow);
			SetAllowTargeting(Allow);
		}

		Unit* FindFelCrystal()
		{
			/*
				Find a FelCrystal
			*/
			Unit* FC = NULL;
			for(int x = 0; x < 5; x++)
			{
				FC = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(FelCrystals[x].x, FelCrystals[x].y, FelCrystals[x].z, FelCrystals[x].addition);
				if(!FC || !FC->isAlive() || FC->GetInstanceID() != _unit->GetInstanceID())
					FC = NULL;
				else
					break;
			}
			return FC;
		}

		void CastFelExplosion()
		{
			CastSpellNowNoScheduling(FelExplosion);

			// No Idea why the mana isnt taken when the spell is cast so had to manually take it -_-
			_unit->SetUInt32Value(UNIT_FIELD_POWER1, _unit->GetPower(POWER_TYPE_MANA) - 3231);
		}

		SpellEntry* ManaRage;
		SpellDesc* ManaRageTrigger;
		SpellDesc* FelExplosion;
};

/*
	Vexallus
*/
#define BOSS_VEXALLUS 24744
#define CN_PURE_ENERGY 24745

#define VEXALLUS_CHAIN_LIGHTNING 44318
#define VEXALLUS_OVERLOAD 44353
#define VEXALLUS_ARCANE_SHOCK 44319
#define VEXALLUS_SUMMON_PURE_ENERGY 44322

class VexallusAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(VexallusAI, MoonScriptBossAI);
		VexallusAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddPhaseSpell(1, AddSpell(VEXALLUS_CHAIN_LIGHTNING, Target_Current, 19, 0, 8, 0, 0));
			AddPhaseSpell(1, AddSpell(VEXALLUS_ARCANE_SHOCK, Target_ClosestPlayer, 12, 0, 20, 0, 0, true, "Un...con...tainable.", Text_Yell, 12392));
			AddPhaseSpell(2, AddSpell(VEXALLUS_OVERLOAD, Target_Self, 85, 0, 3, 0, 0));
			mPureEnergy = AddSpell(VEXALLUS_SUMMON_PURE_ENERGY, Target_Self, 85, 0, 3);

			AddEmote(Event_OnTargetDied, "Con...sume.", Text_Yell, 12393);

			mSummon = 0;
		}

		void OnCombatStart(Unit* pTarget)
		{
			Emote("Drain... life...", Text_Yell, 12389);
			SetPhase(1);
			ParentClass::OnCombatStart(pTarget);
		}

		void AIUpdate()
		{
			if((GetHealthPercent() <= 85  && mSummon == 0) ||
			        (GetHealthPercent() <= 70 && mSummon == 1) ||
			        (GetHealthPercent() <= 55 && mSummon == 2) ||
			        (GetHealthPercent() <= 40 && mSummon == 3) ||
			        (GetHealthPercent() <= 25 && mSummon == 4))
			{
				CastSpell(mPureEnergy);
				++mSummon;
				//SpawnCreature(CN_PURE_ENERGY, 231, -207, 6, 0, true);
			}

			if(GetHealthPercent() <= 10 && GetPhase() == 1)
				SetPhase(2);


			ParentClass::AIUpdate();
		}

		SpellDesc*	mPureEnergy;
		uint8		mSummon;
};

//Priestess Delrissa
#define BOSS_Priestess_Delrissa 24560

#define PRIESTESS_DELRISSA_DISPEL_MAGIC 27609
#define PRIESTESS_DELRISSA_FLASH_HEAL 17843
#define PRIESTESS_DELRISSA_SHADOWWORD_PAIN 15654
#define PRIESTESS_DELRISSA_POWERWORD_SHIELD 44291
#define PRIESTESS_DELRISSA_RENEW 44174

class Priestess_DelrissaAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(Priestess_DelrissaAI, MoonScriptBossAI);
		Priestess_DelrissaAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(PRIESTESS_DELRISSA_DISPEL_MAGIC, Target_RandomFriendly, 35, 0, 5, 0, 30);
			AddSpell(PRIESTESS_DELRISSA_FLASH_HEAL, Target_RandomFriendly, 40, 1.5, 7, 0, 40);
			AddSpell(PRIESTESS_DELRISSA_SHADOWWORD_PAIN, Target_RandomPlayer, 45, 0, 18, 0, 30);
			AddSpell(PRIESTESS_DELRISSA_POWERWORD_SHIELD, Target_RandomFriendly, 32, 0, 15, 0, 40);
			AddSpell(PRIESTESS_DELRISSA_RENEW, Target_RandomFriendly, 30, 0, 18, 0, 40);

			AddEmote(Event_OnDied, "Not what I had... planned...", Text_Yell, 12397);

			mClearHateList = AddTimer(15000);
			mKilledPlayers = 0;
		}

		void OnCombatStart(Unit* pTarget)
		{
			Emote("Annihilate them!", Text_Yell, 12395);
			//AggroRandomUnit();	// Want to aggro random unit ? Set it instead of calling premade
			// method that in this case recursively loops this procedure

			ParentClass::OnCombatStart(pTarget);
		}

		void OnTargetDied(Unit* pTarget)
		{
			if(!pTarget || !pTarget->IsPlayer())
				return;

			++mKilledPlayers;

			if(mKilledPlayers == 1)
				Emote("I call that a good start.", Text_Yell, 12405);
			else if(mKilledPlayers == 2)
				Emote("I could have sworn there were more of you.", Text_Yell, 12407);
			else if(mKilledPlayers == 3)
				Emote("Not really much of a group, anymore, is it?", Text_Yell, 12409);
			else if(mKilledPlayers == 4)
				Emote("One is such a lonely number.", Text_Yell, 12410);
			else if(mKilledPlayers == 5)
				Emote("It's been a kick, really.", Text_Yell, 12411);

			ParentClass::OnTargetDied(pTarget);
		}

		void OnCombatStop(Unit* pTarget)
		{
			Emote("It's been a kick, really.", Text_Yell, 12411);
			mKilledPlayers = 0;

			ParentClass::OnCombatStop(pTarget);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mClearHateList))
			{
				ClearHateList();
				AggroRandomUnit();
				ResetTimer(mClearHateList, 15000);
			}
			ParentClass::AIUpdate();
		}

	protected:
		uint8		mKilledPlayers;
		int32		mClearHateList;
};

void SetupMagistersTerrace(ScriptMgr* pScriptMgr)
{
	//Bosses
	pScriptMgr->register_creature_script(BOSS_SelinFireheart, &SelinFireheartAI::Create);
	pScriptMgr->register_creature_script(BOSS_VEXALLUS, &VexallusAI::Create);
	pScriptMgr->register_creature_script(BOSS_Priestess_Delrissa, &Priestess_DelrissaAI::Create);
}
