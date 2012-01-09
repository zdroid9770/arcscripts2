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

class NerubarEggSac : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(NerubarEggSac)
	NerubarEggSac(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		if( !pPlayer->HasQuest(11602) )
			return;

		switch( rand()%3 )
		{
			case 0:
				break; // 33% of chance get nothing...
			case 1:
				sEAS.SpawnCreature( pPlayer, 24562, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionY(), _gameobject->GetOrientation(), DEFAULT_DESPAWN_TIMER ); break; // 33% to spawn a Nerub'ar Invader...
			case 2:
				sEAS.SpawnCreature( pPlayer, 25652, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionY(), _gameobject->GetOrientation(), DEFAULT_DESPAWN_TIMER ); // and 33% to spawn 3 Nerub'ar Scarab
				sEAS.SpawnCreature( pPlayer, 25652, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionY(), _gameobject->GetOrientation(), DEFAULT_DESPAWN_TIMER );
				sEAS.SpawnCreature( pPlayer, 25652, _gameobject->GetPositionX(), _gameobject->GetPositionY(), _gameobject->GetPositionY(), _gameobject->GetOrientation(), DEFAULT_DESPAWN_TIMER );
				break;
		}
		_gameobject->Despawn( 500, 60000 );
	}
};

void SetupBoreanTundraGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 187655, &NerubarEggSac::Create );	// Nerub'ar Egg Sac
}
