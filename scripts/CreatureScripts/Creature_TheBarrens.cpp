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

class SavannahProwler : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(SavannahProwler)
	SavannahProwler(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		if( RandomUInt(3) == 1 )
			GetUnit()->SetStandState(STANDSTATE_SLEEP); 
	}
};

void SetupTheBarrensCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script( 3425,  &SavannahProwler::Create );	// Savannah Prowler
}
