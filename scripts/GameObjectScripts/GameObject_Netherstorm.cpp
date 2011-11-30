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

class EthereumTransponderZeta : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(EthereumTransponderZeta)
	EthereumTransponderZeta(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		if( pPlayer->HasQuest(10339) && sEAS.GetNearestCreature(pPlayer, 20482) == NULL )
			sEAS.SpawnCreature( pPlayer, 20482, 4017.96f, 2315.91f, 116.418f, pPlayer->GetOrientation()+3.14f, DEFAULT_DESPAWN_TIMER );
	}
};

class TyraliusPrison : public GameObjectAIScript{
public:
	TyraliusPrison( GameObject *goinstance ) : GameObjectAIScript( goinstance ){}
	
	static GameObjectAIScript* Create( GameObject *GO ){ return new TyraliusPrison( GO ); }

	void OnActivate( Player *p ){
		// Spawning Captain Tyralius
		sEAS.SpawnCreature( p, 20787, p->GetPositionX(), p->GetPositionY(), p->GetPositionZ(), p->GetOrientation(), 2 * 60 * 1000 );
	}
};

void SetupNetherstormGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 184383, &EthereumTransponderZeta::Create );	// Ethereum Transponder Zeta
	mgr->register_gameobject_script( 184588, &TyraliusPrison::Create );
}
