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

class GreganBrewspewer_Gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			if(plr->HasQuest(3909))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Buy somethin', will ya?", 0);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 0)
				Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 2434, plr, 1, Arcemu::Gossip::VENDOR, Plr->GetSession()->LocalizedWorldSrv(Arcemu::Gossip::VENDOR));
			else if(Id == 1)
				plr->GetSession()->SendInventoryList(TO_CREATURE(pObject));
		}
};

void Setup_FeralasQuest(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(7775, new GreganBrewspewer_Gossip);
}
