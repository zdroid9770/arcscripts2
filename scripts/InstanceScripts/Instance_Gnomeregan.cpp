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

/****************************************/
/********************************TRASHES*/
/****************************************/
class IrradiatedPillagerAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(IrradiatedPillagerAI, MoonScriptCreatureAI);
		IrradiatedPillagerAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(9771, Target_Current, 100, 3, rand()%5 + 3);
			AddSpell(9770, Target_self, 100, 0, 4);
		}

		void AIUpdate()
		{
			//casts fenzy at 50% health
			if(_unit->GetHealthPch() <= 50 && !_unit->HasAura(8269))
			{
				_unit->CastSpell(_unit, 8269, true);
				Emote("Your bones will break under my boot, $R!", Text_Yell, 0);
			}
			ParentClass::AIUpdate();
		}
		
		void OnDied(Unit* mKiller)
		{
			Emote("%s blood sprays into the air!", Text_Emote, 0);
			if(!_unit->HasAura(9798))
				_unit->CastSpell(_unit, 9798, true);
			ParentClass::OnDied(mKiller);
		}
};

void SetupGnomeregan(ScriptMgr* mgr)
{
	mgr->register_creature_script(6329, &IrradiatedPillagerAI::Create);
}
