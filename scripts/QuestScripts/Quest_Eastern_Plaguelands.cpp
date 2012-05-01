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
class Darrowshire_Spirit : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			QuestLogEntry* en = plr->GetQuestLogForEntry(5211);

			if(en && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
			{
				uint32 newcount = en->GetMobCount(0) + 1;

				en->SetMobCount(0, newcount);
				en->SendUpdateAddKill(0);
				en->UpdatePlayerFields();
			}

			Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3873, plr);

			if(!pObject || !pObject->IsCreature())
				return;

			Creature* Spirit = TO_CREATURE(pObject);

			Spirit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			Spirit->Despawn(4000, 0);
		}
};

//Tirion Fordring (1855)
class TirionFordringEastern : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			QuestLogEntry* quest = plr->GetQuestLogForEntry(5742);
			if(plr->HasQuest(5742) && plr->getStandState() == STANDSTATE_SIT)
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I am ready to hear your tale, Tirion.", 1);
			sQuestMgr.FillQuestMenu(TO_CREATURE(pObject), plr, menu);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 1: Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 4493, Plr, 2, Arcemu::Gossip::ICON_CHAT, "Thank you, Tirion.  What of your identity?"); break;
				case 2: Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 4494, Plr, 3, Arcemu::Gossip::ICON_CHAT, "That is terrible."); break;
				case 3: Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 4495, Plr, 4, Arcemu::Gossip::ICON_CHAT, "I will, Tirion."); break;
				case 4: Plr->GetQuestLogForEntry(5742)->SendQuestComplete(); break;
			}
		}
};

void SetupEasternPlaguelands(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(11064, new Darrowshire_Spirit);
	mgr->register_creature_gossip(1855, new TirionFordringEastern);
}
