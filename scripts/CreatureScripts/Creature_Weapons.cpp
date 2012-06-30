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

// Elwynn Forest
class KoboldVerminAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(KoboldVerminAI, MoonScriptCreatureAI);
		KoboldVerminAI(Creature *pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnLoad()
		{
			SetDisplayWeaponIds(3262, 0);
			ParentClass::OnLoad();
		}
};

class KoboldWorkerAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(KoboldWorkerAI, MoonScriptCreatureAI);
		KoboldWorkerAI(Creature *pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnLoad()
		{
			SetDisplayWeaponIds(50431, 0);
			ParentClass::OnLoad();
		}
};

void SetupCreatureWeapons(ScriptMgr * mgr)
{
	mgr->register_creature_script(6, &KoboldVerminAI::Create);
	mgr->register_creature_script(257, &KoboldWorkerAI::Create);
}