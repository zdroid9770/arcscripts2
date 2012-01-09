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

class SerpentStatue : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(SerpentStatue)
	SerpentStatue(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		if( pPlayer->HasQuest(6027) )
			sEAS.SpawnCreature( pPlayer, 12369, 246.741f, 2953.3f, 5.8631f, 1.078f, DEFAULT_DESPAWN_TIMER );
	}
};

class HandofIruxos : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(HandofIruxos)
	HandofIruxos(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		if( pPlayer->HasQuest(5381) )
			sEAS.SpawnCreature( pPlayer, 11876, -348.231f, 1763.85f, 138.371f, 4.42728f, DEFAULT_DESPAWN_TIMER );
	}
};

void SetupDesolaceGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 177673, &SerpentStatue::Create );	// Serpent Statue
	mgr->register_gameobject_script( 176581, &HandofIruxos::Create );	// Hand of Iruxos Crystal
}
