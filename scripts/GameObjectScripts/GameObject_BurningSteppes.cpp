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

class DreadmaulRock : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(DreadmaulRock)
		DreadmaulRock(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player * pPlayer)
		{
			LocationVector vect(pPlayer->GetPositionX()+RandomFloat(2.0f), pPlayer->GetPositionY()+RandomFloat(2.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation());
			if(pPlayer->HasQuest(3821) && sEAS.GetNearestCreature(pPlayer, 9136) == NULL)
				sEAS.SpawnCreature(pPlayer, 9136, vect.x, vect.y, vect.z, vect.o, DEFAULT_DESPAWN_TIMER);
		}
};

class TabletoftheSeven : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(TabletoftheSeven)
		TabletoftheSeven(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player * pPlayer)
		{
			/*if( pPlayer->HasQuest(4296) && !pPlayer->GetItemInterface()->GetItemCount(11470, true) )
				_gameobject->CastSpell( pPlayer, 15065, true ); // Cast spell: "Create Tablet Transcript".*/
		}
};

void SetupBurningSteppesGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script(160445, &DreadmaulRock::Create);		// Sha'ni Proudtusk's Remains
	mgr->register_gameobject_script(169294, &TabletoftheSeven::Create);	// Tablet of the Seven
}
