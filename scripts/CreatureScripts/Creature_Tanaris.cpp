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

class PirateTreasureTrigger : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(PirateTreasureTrigger)
	PirateTreasureTrigger(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		GetUnit()->CastSpell( GetUnit(), 11485, true ); // Cast spell: "Summon Treasure Hunting Bucanneer".
		GetUnit()->CastSpell( GetUnit(), 11487, true ); // Cast spell: "Summon Treasure Hunting Swashbuckler".
		GetUnit()->CastSpell( GetUnit(), 11487, true ); // Cast spell: "Summon Treasure Hunting Swashbuckler".
		GetUnit()->CastSpell( GetUnit(), 11463, true ); // Cast spell: "Summon Treasure Hunting Pirate".
		GetUnit()->CastSpell( GetUnit(), 11463, true ); // Cast spell: "Summon Treasure Hunting Pirate".
	}
};

void SetupTanarisCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script( 7898, &PirateTreasureTrigger::Create );	// Pirate treasure trigger mob
}
