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

class UlagTheCleaver : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(UlagTheCleaver)
	UlagTheCleaver(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		Creature* Ulag = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(2390.101807f, 336.676788f, 40.015614f, 6390);
		GameObject* pDoor = pPlayer->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(2388.480029f, 338.3901f, 40.092899f, 176594);

		if( !pPlayer->HasQuest(1819) || !pDoor || Ulag )
			return;

		Ulag = sEAS.SpawnCreature(pPlayer, 6390, 2390.101807f, 336.676788f, 40.015614f, 2.259590f, DESPAWN_TIME);
		Ulag->GetAIInterface()->setNextTarget(pPlayer);
		Ulag->GetAIInterface()->AttackReaction(pPlayer, 1);
		pDoor->SetUInt32Value(GAMEOBJECT_FLAGS, 0x21); // GO_FLAG_NODESPAWN|GO_FLAG_IN_USE
		pDoor->SetState(0);
	}
};

void SetupTirisfalGladesGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 104593, &UlagTheCleaver::Create );	// Mausoleum Trigger
}
