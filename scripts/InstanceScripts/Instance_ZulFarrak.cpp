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

class thekaAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(thekaAI)
		thekaAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(8600, Target_Current, 20, 4.5f, -1);	//Fevered Plague
			morph = false;
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 30 && !morph)
			{
				morph = true;
				_unit->CastSpell(_unit, 11089, true);	//Theka Transform
			}
			MoonScriptCreatureAI::AIUpdate();
		}

	protected:
		bool morph;
};

#define servants 11894
#define healingward 11889
#define earthgrabward 8376
#define HEALING_WAVE_OF_ANTUSUL	11895
class antusulAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(antusulAI)
		antusulAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Lunch has arrived, my beutiful childern. Tear them to pieces!", Text_Yell, 0);
			AddSpell(healingward, Target_Self, 15, 2, -1);
			AddSpell(earthgrabward, Target_Self, 20, 0.5f, -1);
			AddSpell(HEALING_WAVE_OF_ANTUSUL, Target_WoundedFriendly, 25, 0.5f, -1);
			SpawnCount = 0;
		}

		void AIUpdate()
		{
			if(_unit->GetHealthPct() <= 75 && SpawnCount == 0)
			{
				Emote("Rise and defend your master!", Text_Yell, 0);
				_unit->CastSpell(_unit, servants, true);
				SpawnCount++;
			}

			if(_unit->GetHealthPct() <= 25 && SpawnCount == 1)
			{
				Emote("The children of sul will protect their master. Rise once more Sul'lithuz!", Text_Yell, 0);
				_unit->CastSpell(_unit, servants, true);
				SpawnCount++;
			}
			MoonScriptCreatureAI::AIUpdate();
		}

	protected:
		uint8 SpawnCount;
};

//todo: Ward of Zum'rah (7785)
class WitchDoctorZumrahAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WitchDoctorZumrahAI)
		WitchDoctorZumrahAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(12491, Target_WoundedFriendly, 15, 3, -1);	//Healing Wave
			AddSpell(12739, Target_Current, 20, 3, -1);			//Shadow Bolt
			AddSpell(15245, Target_RandomPlayer, 25, 3, -1);	//Shadow Bolt Volley
			TotemTimer = -1;
		}

		void OnCombatStart(Unit * mAttacker)
		{
			_unit->CastSpell(_unit, 11086, true); //Ward of Zum'rah
			TotemTimer = AddTimer(20*SEC_IN_MS);
			MoonScriptCreatureAI::OnCombatStart(mAttacker);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(TotemTimer))
			{
				_unit->CastSpell(_unit, 11086, true); //Ward of Zum'rah
				ResetTimer(TotemTimer, 20*SEC_IN_MS);
			}
			MoonScriptCreatureAI::AIUpdate();
		}

	protected:
		int32 TotemTimer;
};

void SetupZulFarrak(ScriptMgr* mgr)
{
	mgr->register_creature_script(8127, &antusulAI::Create);
	mgr->register_creature_script(7272, &thekaAI::Create);
	mgr->register_creature_script(7785, &WitchDoctorZumrahAI::Create);
}