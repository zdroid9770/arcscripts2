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

class BringMetheEgg : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(BringMetheEgg)
		BringMetheEgg(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player *pPlayer)
		{
			if(pPlayer->HasQuest(10111) && !pPlayer->HasAura(33382))
				pPlayer->CastSpell(pPlayer, 33382, true);
		}
};

class MysteriousEgg : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(MysteriousEgg)
		MysteriousEgg(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player *pPlayer)
		{
			LocationVector vect(pPlayer->GetPositionX()+RandomFloat(2.0f), pPlayer->GetPositionY()+RandomFloat(2.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation());
			if(pPlayer->HasQuest(10111) && sEAS.GetNearestCreature(pPlayer, 19055))
				sEAS.SpawnCreature(pPlayer, 19055, vect.x, vect.y, vect.z, vect.o, DEFAULT_DESPAWN_TIMER);
		}
};

void SetupNagrandGameobjects(ScriptMgr * mgr)
{
	mgr->register_gameobject_script(183146, &BringMetheEgg::Create);	// Jump-a-tron 4000
	mgr->register_gameobject_script(183147, &MysteriousEgg::Create);	// Mysterious Egg
}
