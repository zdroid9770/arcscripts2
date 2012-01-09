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

class AcherusSoulPrison : GameObjectAIScript
{
public:
	ADD_GAMEOBJECT_FACTORY_FUNCTION(AcherusSoulPrison)
	AcherusSoulPrison(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

	void OnActivate(Player * pPlayer)
	{
		if( !pPlayer->HasQuest(12848) )
			return;

		uint32 InitiateIds[] = { 29519, 29520, 29565, 29567, 0 };
		Creature *pCreature = sEAS.GetNearestCreature( pPlayer, InitiateIds );
		if( pCreature == NULL || pCreature->IsDead() )
			return;

		pPlayer->SendChatMessage( CHAT_MSG_SAY, LANG_UNIVERSAL, "I give you the key to your salvation" );
		pCreature->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
		pCreature->GetAIInterface()->setNextTarget( pPlayer );
		pCreature->GetAIInterface()->AttackReaction( pPlayer, 1 );
		pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You have committed a big mistake, demon");
	}
};

void SetupTheScarletEnclaveGameObject(ScriptMgr * mgr)
{
	uint32 SoulPrisonIds[] = { 191577, 191580, 191581, 191582, 191583, 191584, 191585, 191586, 191587, 191588, 191589, 191590, 0};
	mgr->register_gameobject_script( SoulPrisonIds, &AcherusSoulPrison::Create );	// Acherus Soul Prison
}
