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

// Searing Blade Warlock AI by Soulshifter
#define CN_SEARING_BLADE_WARLOCK	11324
class SearingBladeWarlockAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(SearingBladeWarlockAI, MoonScriptCreatureAI);
		SearingBladeWarlockAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			// Shadow Bolt
			AddSpell(20791, Target_Current, 20, 3, 0);
			// Summon Voidwalker -- Doesnt work (Disabled for now)
			//CastSpellNowNoScheduling(AddSpell(12746, Target_Self, 0, 0, 0));
		}
};

/* GAMEOBJECTS */
class BloodFilledOrb : public GameObjectAIScript
{
	public:
		BloodFilledOrb(GameObject*  goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject*  GO) { return new BloodFilledOrb(GO); }

		void OnActivate(Player*  pPlayer)
		{
			// Make sure player has the quest and Zelemar isn't spawned yet
			if(!pPlayer->HasQuest(9692)) // The Path of the Adept
			{
				pPlayer->GetSession()->SendNotification("Request quest `The Path of the Adept`.");
				return;
			}

			Creature* Zelemar = _gameobject->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(-370.133f, 162.519f, -21.1299f, 17830);
			if(Zelemar == NULL)
			{
				Zelemar = _gameobject->GetMapMgr()->GetInterface()->SpawnCreature(17830, -370.133f, 162.519f, -21.1299f, -1.29154f, true, false, 0, 0);
				if(Zelemar!=NULL)
				{
					Zelemar->m_noRespawn = true;
					Zelemar = NULL;
				}
			}
			
		}
};

void SetupRagefireChasm(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_SEARING_BLADE_WARLOCK, &SearingBladeWarlockAI::Create);
	mgr->register_gameobject_script(182024, &BloodFilledOrb::Create);
}