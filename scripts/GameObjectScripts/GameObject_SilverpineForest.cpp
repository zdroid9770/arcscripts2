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

class BrazierOfEverfount : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(BrazierOfEverfount)
	BrazierOfEverfount(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player *pPlayer)
	{
		LocationVector vect( pPlayer->GetPositionX()+RandomFloat(2.0f), pPlayer->GetPositionY()+RandomFloat(2.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation() );
		if( pPlayer->HasQuest(63) )
			sEAS.SpawnCreature(pPlayer, 5894, vect, DESPAWN_TIME);
	}
};

class DustySpellbooks : public GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(DustySpellbooks)
	DustySpellbooks(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

	void OnLootTaken(Player *pLooter, ItemPrototype *pItemInfo)
	{
		if( pLooter->HasQuest(422) )
		{
			LocationVector vect( pLooter->GetPositionX()+RandomFloat(2.0f), pLooter->GetPositionY()+RandomFloat(2.0f), pLooter->GetPositionZ(), pLooter->GetOrientation() );
			Creature* NewCreature = sEAS.SpawnCreature(pLooter, 1770, vect, DESPAWN_TIME);
			NewCreature->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "The Sons of Arugal will rise against all who challenge the power of the Moonrage!");
		}
	}
};

void SetupSilverpineForestGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script( 113791, &BrazierOfEverfount::Create );	// Brazier of Everfount
	mgr->register_gameobject_script( 1571,   &DustySpellbooks::Create );	// Dusty Spellbooks
}
