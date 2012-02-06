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

class CorruptMinorManifestationWater : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(CorruptMinorManifestationWater)
		CorruptMinorManifestationWater(Creature *pCreature) : CreatureAIScript(pCreature) {}

		void OnDied(Unit *mKiller)
		{
			LocationVector vect(GetUnit()->GetPositionX()+2, GetUnit()->GetPositionY()+2, GetUnit()->GetPositionZ(), GetUnit()->GetOrientation());
			sEAS.SpawnCreature(TO_PLAYER(mKiller), 5895, vect.x, vect.y, vect.z, vect.o, DEFAULT_DESPAWN_TIMER);
		}
};

void SetupSilverpineForestCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script(5894,  &CorruptMinorManifestationWater::Create);	// Corrupt Minor Manifestation of Water
}
