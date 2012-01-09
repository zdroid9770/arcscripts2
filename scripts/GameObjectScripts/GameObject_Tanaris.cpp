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

class CuregosGold : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(CuregosGold)
	CuregosGold(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		if( pPlayer->HasQuest(2882) )
			pPlayer->CastSpell( pPlayer, 11462, true ); // Cast spell: "Summon Pirate Treasure and Trigger Mob".
	}
};

void SetupTanarisGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 142189, &CuregosGold::Create );	// Inconspicuous Landmark
}
