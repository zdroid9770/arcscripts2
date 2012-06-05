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

// PandemoniusAI

#define CN_PANDEMONIUS 18341

#define VOID_BLAST 32325 //38760
#define DARK_SHELL 32358 //38759

class PANDEMONIUSAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(PANDEMONIUSAI)
		PANDEMONIUSAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(DARK_SHELL, Target_Self, 20, 1, 20);
			AddEmote(Event_OnCombatStart, "I will feed on your soul!", Text_Yell, 10561);
			AddEmote(Event_OnCombatStart, "So... full of life!", Text_Yell, 10562);
			AddEmote(Event_OnCombatStart, "Do not... resist!", Text_Yell, 10563);
			AddEmote(Event_OnTargetDied, "Yes! I am... empowered!", Text_Yell, 10564);
			AddEmote(Event_OnTargetDied, "More... I must have more!", Text_Yell, 10565);
			AddEmote(Event_OnDied, "To the void... once... more.", Text_Yell, 10566);
			Counter = 0;
			VoidTimer = 0;
		}

		void OnCombatStart(Unit* pAttacker)
		{
			VoidTimer = AddTimer((8+rand()%15)*SEC_IN_MS);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(VoidTimer))
			{
				_unit->CastSpell(GetBestPlayerTarget(TargetFilter_Wounded), VOID_BLAST, true);
				Counter++;
				ResetTimer(VoidTimer, 500);
			}

			if(Counter == 5)
			{
				Counter = 0;
				ResetTimer(VoidTimer, (8+rand()%15)*SEC_IN_MS);
			}
		}

	protected:
		uint8 Counter;
		int32 VoidTimer;
};

// Nexus-Prince ShaffarAI

#define CN_NEXUS_PRINCE_SHAFFAR 18344

#define FIREBALL				32363
#define FROSTBOLT				32364 // Also can be: 40430 or 32370
#define FROST_NOVA				32365 // Also worth to try: 30094
#define BLINK					34605 // 36109 - forward 20yard, 36718 - 5yard, behind target, 29883 - random target // still doesn't tp boss
#define SUMMON_ETEREAL_BECON	32371 // not sure about spawning way
// TO DO: Work on beacons and find out if my current way of spawning them is correct

class NEXUSPRINCESHAFFARAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(NEXUSPRINCESHAFFARAI)
		NEXUSPRINCESHAFFARAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(FIREBALL, Target_RandomPlayer, 35, 1, 5);
			AddSpell(FROSTBOLT, Target_RandomPlayer, 35, 1, 5);
			AddSpell(FROST_NOVA, Target_Self, 15, 0, 15);
			AddSpell(BLINK, Target_Self, 5, 0, 20);
			AddSpell(SUMMON_ETEREAL_BECON, Target_Self, 10, 0, 10);
			AddEmote(Event_OnCombatStart, "We have not yet been properly introduced.", Text_Yell, 10541);
			AddEmote(Event_OnCombatStart, "An epic battle, How exciting!", Text_Yell, 10542);
			AddEmote(Event_OnCombatStart, "I have longed for a good adventure!", Text_Yell, 10543);
			AddEmote(Event_OnTargetDied, "And now, we part company.", Text_Yell, 10544);
			AddEmote(Event_OnTargetDied, "It has been... entertaining.", Text_Yell, 10545);
			AddEmote(Event_OnDied, "I must bid you... farewell.", Text_Yell, 10545);
		}
};

void SetupManaTombs(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_PANDEMONIUS, &PANDEMONIUSAI::Create);
	mgr->register_creature_script(CN_NEXUS_PRINCE_SHAFFAR, &NEXUSPRINCESHAFFARAI::Create);
}
