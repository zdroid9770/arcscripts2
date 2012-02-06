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

class Aeranas : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(Aeranas, MoonScriptCreatureAI)
		Aeranas(Creature * pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(15535, Target_Current, 30.0f, 2.0f, 20);
			AddSpell(12553, Target_Current, 50.0f, 0, 10);
		}

		void OnCombatStop(Unit * mTarget)
		{
			ParentClass::OnCombatStop(mTarget);
			GetUnit()->Despawn(0,0);
		}

		void AIUpdate()
		{
			if(GetUnit()->GetHealthPct() <= 30)
			{
				WipeHateList();
				GetUnit()->SetFaction(35);
			}
			ParentClass::AIUpdate();
		}
};

void SetupHellfireCreatures(ScriptMgr * mgr)
{
	mgr->register_creature_script(17085, &Aeranas::Create);
}
