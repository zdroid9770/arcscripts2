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

uint32 BristlelimbKilled = 0; // TODO: This variable should be unique for each player
class HighChiefBristlelimb : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(HighChiefBristlelimb)
	HighChiefBristlelimb(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnDamageDealt()
	{
		if( GetUnit()->GetHealthPct() <= 10 )
			GetUnit()->SendChatMessage( CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Chief, we need your help!" );
	}

	void OnDied(Unit *mKiller)
	{
		if( !mKiller->IsPlayer() || !TO_PLAYER(mKiller)->HasQuest(9667) )
			return;

		++BristlelimbKilled;
		if( BristlelimbKilled > 8 && (rand()%80) )
			sEAS.SpawnCreature( mKiller, 17702, -2419, -12166, 33, 3.45f, DESPAWN_TIME );
	}
};

class WebbedCreature : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION( WebbedCreature )
	WebbedCreature( Creature *pCreature ) : CreatureAIScript( pCreature ) {};

	void OnCombatStart(Unit *pTarget)
	{
		GetUnit()->GetAIInterface()->disable_melee = true;
		GetUnit()->Root();
		GetUnit()->GetAIInterface()->StopMovement( 0 );
	}

	void OnDied(Unit *pKiller)
	{
		Player *pPlayer = NULL;
		if ( pKiller->IsPlayer() )
			pPlayer = TO_PLAYER( pKiller );
		else if ( pKiller->IsPet() && TO_PET( pKiller )->GetPetOwner() != NULL )
			pPlayer = TO_PET( pKiller )->GetPetOwner();

		if ( pPlayer == NULL )
			return;

		// TODO: I don't think the method is correct, but it can stay the way it was until someone gives proper infos
		LocationVector vec( GetUnit()->GetPositionX(), GetUnit()->GetPositionY(), GetUnit()->GetPositionZ(), GetUnit()->GetOrientation() );
		if( !pPlayer->HasQuest(9670) )
		{
			// Creatures from Bloodmyst Isle
			uint32 Id[51] = { 17681, 17887, 17550, 17323, 17338, 17341, 17333, 17340, 17353, 17320, 17339, 17337, 17715, 17322, 17494, 17654, 17342, 17328, 17331, 17325, 17321, 17330, 17522, 17329, 17524, 17327, 17661, 17352, 17334, 17326, 17324, 17673, 17336, 17346, 17589, 17609, 17608, 17345, 17527, 17344, 17347, 17525, 17713, 17523, 17348, 17606, 17604, 17607, 17610, 17358, 17588 };
			sEAS.SpawnCreature( pPlayer, Id[RandomUInt(50)], vec, DESPAWN_TIME );
		}
		else
		{
			uint32 Id[8] = { 17681, 17321, 17330, 17522, 17673, 17336, 17346, 17589 };
			Creature *RandomCreature = sEAS.SpawnCreature( pPlayer, Id[RandomUInt(7)], vec, DESPAWN_TIME );
			if( RandomCreature != NULL && RandomCreature->GetEntry() == 17681 )
			{
				sEAS.KillMobForQuest( pPlayer, 9670, 0 );
				switch( rand()%4 )
				{
					case 0:
						RandomCreature->SendChatMessage( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "I knew cornelius wouldn't leave us behind!" );
						break;
					case 1:
						RandomCreature->SendChatMessage( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "By the forehead signet of Velen, I am saved!" );
						break;
					case 2:
						RandomCreature->SendChatMessage( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "We're free! We're free!" );
						break;
					case 3:
						RandomCreature->SendChatMessage( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Woot! Thanks!" );
						break;
				}
			}
		}
	}
};

void SetupBloodmystIsleCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script( 17320, &HighChiefBristlelimb::Create );	// Bristlelimb Shaman
	mgr->register_creature_script( 17321, &HighChiefBristlelimb::Create );	// Bristlelimb Warrior
	mgr->register_creature_script( 17680, &WebbedCreature::Create );		// Webbed Creature
}