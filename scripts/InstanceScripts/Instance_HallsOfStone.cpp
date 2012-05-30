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

//Maiden of Grief
#define BOSS_MAIDEN_OF_GRIEF 27975

#define MAIDEN_PILLAR_OF_WOE 50761 //apply at long/min range (all in that void zone should get it )
#define MAIDEN_SHOCK_OF_SORROW 50760
#define MAIDEN_STORM_OF_GRIEF 50752

class MaidenOfGriefAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(MaidenOfGriefAI)
		MaidenOfGriefAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(MAIDEN_STORM_OF_GRIEF, Target_RandomPlayerDestination, 100, 0, 19);
			AddSpell(MAIDEN_PILLAR_OF_WOE, Target_RandomPlayerNotCurrent, 30, 0, 8);
			mShock = AddSpell(MAIDEN_SHOCK_OF_SORROW, Target_Self, 20, 0, 18);
			mShock->AddEmote("So much lost time... that you'll never get back!", Text_Yell, 13492);

			//EMOTES
			AddEmote(Event_OnCombatStart, "You shouldn't have come...now you will die! ", Text_Yell, 13487);
			AddEmote(Event_OnTargetDied, "My burden grows heavier.", Text_Yell, 13488);
			AddEmote(Event_OnTargetDied, "This is your own fault!", Text_Yell, 13489);
			AddEmote(Event_OnTargetDied, "You had it coming!", Text_Yell, 13490);
			AddEmote(Event_OnTargetDied, "Why must it be this way?", Text_Yell, 13491);
			AddEmote(Event_OnDied, "I hope you all rot! I never...wanted...this.", Text_Yell, 13493);
		}

		void OnCombatStart(Unit* pTarget)
		{
			mShock->TriggerCooldown();
		}

	protected:
		SpellDesc* mShock;
};

// Krystallus
#define BOSS_KRYSTALLUS 27977

#define KRYSTALLUS_BOULDER_TOSS 50843
#define KRYSTALLUS_SHATTER 50810
#define KRYSTALLUS_STOMP 50868

// some macros
#define STOMP_TIMER	    35000
#define SHATTER_TIMER	4500

class KrystallusAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(KrystallusAI)
		KrystallusAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(KRYSTALLUS_BOULDER_TOSS, Target_ClosestPlayer, 35, 1, 4);
			mShatter = AddSpell(KRYSTALLUS_SHATTER, Target_Self, 0, 0, 0);
			mStomp = AddSpell(KRYSTALLUS_STOMP, Target_Self, 0, 0, 0);
			mShatter->AddEmote("Break.... you....", Text_Yell, 14178);

			//EMOTES
			AddEmote(Event_OnCombatStart, "Crush....", Text_Yell, 14176);
			AddEmote(Event_OnTargetDied, "Ha.... ha... hah....", Text_Yell, 14177);
			AddEmote(Event_OnDied, "Uuuuhhhhhhhhhh......", Text_Yell, 14179);

			mStompTimer = INVALIDATE_TIMER;
			mShatterTimer = INVALIDATE_TIMER;
		}

		void OnCombatStart(Unit* pTarget)
		{
			mStompTimer = AddTimer(STOMP_TIMER);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mStompTimer))
			{
				CastSpellNowNoScheduling(mStomp);
				SetCanMove(false);
				ResetTimer(mStompTimer, (STOMP_TIMER + SHATTER_TIMER));
				mShatterTimer = AddTimer(SHATTER_TIMER);

			}

			if(IsTimerFinished(mShatterTimer))
			{
				CastSpellNowNoScheduling(mShatter);
				SetCanMove(true);
				RemoveTimer(mShatterTimer);
			}
		}

	protected:
		SpellDesc* mStomp;
		SpellDesc* mShatter;

		int32 mStompTimer;
		int32 mShatterTimer;
};


void SetupHallsOfStone(ScriptMgr* mgr)
{
	mgr->register_creature_script(BOSS_MAIDEN_OF_GRIEF, &MaidenOfGriefAI::Create);
	mgr->register_creature_script(BOSS_KRYSTALLUS, &KrystallusAI::Create);
}
