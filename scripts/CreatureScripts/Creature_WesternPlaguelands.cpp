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

class RottingCadaver : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(RottingCadaver)
		RottingCadaver(Creature *pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnDied(Unit *mKiller)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(17064), true); // Cast spell: "Summon Rotting Worms".
		}
};

class SummonOozeling : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SummonOozeling)
		SummonOozeling(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
		{
			CrimsonFuryTimer = (5+rand()%9)*1000;
		}

		void OnDied(Unit *mKiller)
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(12018), true); // Cast spell: "Summon Oozeling".
		}

		void AIUpdate()
		{
			if(CrimsonFuryTimer <= mAIUpdateFrequency)
			{
				_unit->CastSpell(GetTarget(TARGET_ATTACKING), dbcSpell.LookupEntry(12745), true);
				CrimsonFuryTimer = (8+rand()%7)*1000;
			}else CrimsonFuryTimer -= mAIUpdateFrequency;
		}

	private:
		uint32 CrimsonFuryTimer;
};

void SetupWesternPlaguelandsCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script(4474,  &RottingCadaver::Create);		// Rotting Cadaver
	mgr->register_creature_script(1806,  &SummonOozeling::Create);	// Vile Slime
	mgr->register_creature_script(1808,  &SummonOozeling::Create);	// Devouring Ooze
}

