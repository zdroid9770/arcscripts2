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

class BarrelOfFilth : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(BarrelOfFilth)
	BarrelOfFilth(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		LocationVector vect( pPlayer->GetPositionX()+RandomFloat(2.0f), pPlayer->GetPositionY()+RandomFloat(2.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation() );
		if( pPlayer->HasQuest(9508) )
			sEAS.SpawnCreature( pPlayer, 17359, vect, DESPAWN_TIME );
	}
};

class Razormaw : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(Razormaw)
	Razormaw(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		if( pPlayer->HasQuest(9689) )
			sEAS.SpawnCreature(pPlayer, 17592, -1203.8f, -12424.7f, 95.36f, 4.7f, DESPAWN_TIME);
	}
};

class SavingPrincessStillpine : public GameObjectAIScript // TODO: Find what it do on retail.
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(SavingPrincessStillpine)
	SavingPrincessStillpine(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		if( !pPlayer->HasQuest(9667) )
			return;

		Creature *Princess = sEAS.GetNearestCreature( pPlayer, 17682 );
		if( Princess != NULL )
			Princess->Despawn( 1000, DESPAWN_TIME );
	}
};

void SetupBloodmystIsleGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 181699, &BarrelOfFilth::Create );				// Barrel of Filth
	mgr->register_gameobject_script( 181988, &Razormaw::Create );					// Ever-burning Pyre
	mgr->register_gameobject_script( 181928, &SavingPrincessStillpine::Create );	// Princess Stillpine's Cage
}
