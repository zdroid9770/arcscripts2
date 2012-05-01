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

class ragged_john_gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object *pObject, Player *Plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);
			if(Plr->GetQuestLogForEntry(4224))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Official buisness, John. I need some information about Marsha Windsor. Tell me about the last time you saw him.", 1);
	
			sQuestMgr.FillQuestMenu(TO_CREATURE(pObject), Plr, menu);
			menu.Send(Plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 1: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2714, Plr, 2, Arcemu::Gossip::ICON_CHAT, "So what did you do?"); break;
				case 2: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2715, Plr, 3, Arcemu::Gossip::ICON_CHAT, "Start making sense, dwarf. I don't want to have anything to do with your cracker, your pappy, or any sort of 'discreditin'."); break;
				case 3: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2716, Plr, 4, Arcemu::Gossip::ICON_CHAT, "Ironfoe?"); break;
				case 4: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2717, Plr, 5, Arcemu::Gossip::ICON_CHAT, "Interesting... continue John."); break;
				case 5: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2718, Plr, 6, Arcemu::Gossip::ICON_CHAT, "So that's how Windsor died..."); break;
				case 6: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2719, Plr, 7, Arcemu::Gossip::ICON_CHAT, "So how did he die?"); break;
				case 7: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2720, Plr, 8, Arcemu::Gossip::ICON_CHAT, "Ok so where the hell is he? Wait a minute! Are you drunk?"); break;
				case 8: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2721, Plr, 9, Arcemu::Gossip::ICON_CHAT, "WHY is he in Blackrock Depths?"); break;
				case 9: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2722, Plr, 10, Arcemu::Gossip::ICON_CHAT, "300? So the Dark Irons killed him and dragged him into the Depths?"); break;
				case 10: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2723, Plr, 11, Arcemu::Gossip::ICON_CHAT, "Ahh... Ironfoe"); break;
				case 11: Arcemu::Gossip::Menu::SendQuickMenu(Plr->GetGUID(), 2725, Plr, 12, Arcemu::Gossip::ICON_CHAT, "Thanks, Ragged John. Your story was very uplifting and informative"); break;
				case 12:
				{
					QuestLogEntry* qle = Plr->GetQuestLogForEntry(4224);

					if(!qle)
						return;

					qle->SendQuestComplete();
					Arcemu::Gossip::Menu::Complete(Plr);
				}
			}
		}
};

class TabletOfTheSeven : public QuestScript
{
	public:
		void OnGameObjectActivate(uint32 entry, Player* mTarget, QuestLogEntry* qLogEntry)
		{
			if(mTarget == NULL || qLogEntry == NULL || entry != 169294)
				return;

			if(mTarget->GetItemInterface()->GetItemCount(11470) < qLogEntry->GetQuest()->required_itemcount[0])
				mTarget->CastSpell(mTarget, 15065, false);
		}
};

class DreadmaulRock : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(DreadmaulRock)
		DreadmaulRock(GameObject * goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player * pPlayer)
		{
			LocationVector vect(pPlayer->GetPositionX()+RandomFloat(2.0f), pPlayer->GetPositionY()+RandomFloat(2.0f), pPlayer->GetPositionZ(), pPlayer->GetOrientation());
			if(pPlayer->HasQuest(3821) && sEAS.GetNearestCreature(pPlayer, 9136) == NULL)
				sEAS.SpawnCreature(pPlayer, 9136, vect.x, vect.y, vect.z, vect.o, DEFAULT_DESPAWN_TIMER);
		}
};

void SetupBurningSteppes(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(26596, new ragged_john_gossip);
	mgr->register_quest_script(4296, new TabletOfTheSeven);
	mgr->register_gameobject_script(160445, &DreadmaulRock::Create);		// Sha'ni Proudtusk's Remains
}