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

class ArmyofDeadGhoul : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ArmyofDeadGhoul)
		ArmyofDeadGhoul(Creature * pCreature) : CreatureAIScript(pCreature)
		{
			GetUnit()->GetAIInterface()->m_canMove = false;
		}

		void OnLoad()
		{
			RegisterAIUpdateEvent(200);
		}

		void AIUpdate()
		{
			GetUnit()->CastSpell(GetUnit(), 20480, false);
			GetUnit()->GetAIInterface()->m_canMove = true;
			RemoveAIUpdateEvent();
		}
};

class EranikusTheChained : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(EranikusTheChained)
		EranikusTheChained(Creature * pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			Player * plr = sEAS.GetNearestPlayer(GetUnit());
			switch( rand()%8 )
			{
				case 0:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Will the nightmare ever end?! I cannot force myself awake!", plr );
					break;
				case 1:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My soul is not a trinket! Mortal, you must release me from these chains!", plr );
					break;
				case 2:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My eyes! It burns... it burns...", plr );
					break;
				case 3:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Torture me no more! Release me, mortal! The Swamp of Sorrows... mortal... please...", plr );
					break;
				case 4:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Foolish mortal, I will rend your soul in two once I am released!", plr );
					break;
				case 5:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Foolish mortals you do not yet see the potential of that Artifact.", plr );
					break;
				case 6:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You are an agent of their wicked god, fool. I will see you destroyed!", plr );
					break;
				case 7:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "It hurts so much... Itharius, my old friend... Please help me...", plr );
					break;
				case 8:
					GetUnit()->SendChatMessageToPlayer( CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "My charge to watch the temple has failed... my corrupted soul knows no peace...", plr );
					break;
			}
		}
};

void SetupMiscCreatures(ScriptMgr * mgr)
{
	mgr->register_creature_script(24207, &ArmyofDeadGhoul::Create);		// Army of the Dead Ghoul
	mgr->register_creature_script(8506,  &EranikusTheChained::Create);	// Eranikus the Chained
}
