/*
 * ArcScripts for ArcEmu MMORPG Server
 * Copyright (C) 2009 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (C) 2008 WEmu Team
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

bool BendingShinbone(uint32 i, Spell *pSpell)
{
	if(pSpell->p_caster)
	{
		if(RandomUInt(100) < 17) // 17% chance
			pSpell->p_caster->GetItemInterface()->AddItemById(7134, 1, 0);	//Sturdy Shinbone
		else
			pSpell->p_caster->GetItemInterface()->AddItemById(7135, 1, 0);	//Broken Shinbone
	}
	return true;
}

void SetupWetlands(ScriptMgr *mgr)
{
	mgr->register_script_effect(8856, &BendingShinbone);
}
