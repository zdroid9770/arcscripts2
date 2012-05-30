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

class Lady_Jaina : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			if(plr->GetQuestLogForEntry(558))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Lady Jaina, this may sound like an odd request... but I have a young ward who is quite shy. You are a hero to him, and he asked me to get your autograph.", 1);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 1)
				TO_CREATURE(pObject)->CastSpell(plr, 23122, true);
			plr->Gossip_Complete();
		}
};

class Cairne : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			if(plr->GetQuestLogForEntry(925))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Give me hoofprint.", 1);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 1)
			{
				Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 7014, plr);
				TO_CREATURE(pObject)->CastSpell(plr, 23123, true);
			}
		}
};

class TeleportQ_Gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr);
			if(plr->GetQuestLogForEntry(12791) || plr->GetQuestLogForEntry(12794) || plr->GetQuestLogForEntry(12796))
				TO_CREATURE(pObject)->CastSpell(plr, 68328, false);	//Teleport spell
		}
};

void SetupQuestGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(4968, new Lady_Jaina);
	mgr->register_creature_gossip(3057, new Cairne);

	// Horde
	mgr->register_creature_gossip(26471, new TeleportQ_Gossip);
	mgr->register_creature_gossip(29155, new TeleportQ_Gossip);
	mgr->register_creature_gossip(29159, new TeleportQ_Gossip);
	mgr->register_creature_gossip(29160, new TeleportQ_Gossip);
	mgr->register_creature_gossip(29162, new TeleportQ_Gossip);

	// Alliance
	mgr->register_creature_gossip(23729, new TeleportQ_Gossip);
	mgr->register_creature_gossip(26673, new TeleportQ_Gossip);
	mgr->register_creature_gossip(27158, new TeleportQ_Gossip);
	mgr->register_creature_gossip(29158, new TeleportQ_Gossip);
	mgr->register_creature_gossip(29161, new TeleportQ_Gossip);

	// Both
	mgr->register_creature_gossip(29169, new TeleportQ_Gossip);
}
