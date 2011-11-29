/*
 * WhyScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2010 WhyDB Team <http://www.whydb.org/>
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

class TrollRoofStalker : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(TrollRoofStalker)
	TrollRoofStalker(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		GetUnit()->CastSpell( GetUnit(), 30991, true );
	}
};

void SetupOrgrimmarCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script( 23090, &TrollRoofStalker::Create );	// Troll Roof Stalker
}
