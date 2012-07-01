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

// Quest 11221
class DeathstalkerRazaelGossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			if(plr->HasQuest(11221))
				Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 11562, plr, 0, Arcemu::Gossip::ICON_CHAT, "High Executor Anselm requests your report.");
			else
				Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 0)
				TO_CREATURE(pObject)->CastSpell(plr, 42756, true);
			plr->Gossip_Complete();
		}
};

class DarkRangerLyanaGossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			if(plr->HasQuest(11221))
				Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 11586, plr, 0, Arcemu::Gossip::ICON_CHAT, "High Executor Anselm requests your report.");
			else
				Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 0)
				TO_CREATURE(pObject)->CastSpell(plr, 42799, true);
			plr->Gossip_Complete();
		}
};
 
//Quest 11230
class NorthFleet : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(NorthFleet);
		NorthFleet(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* qle = TO_PLAYER(mKiller)->GetQuestLogForEntry(11230);
				if(qle != NULL)
				{
					if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[ 0 ])
					{
						uint32 newcount = qle->GetMobCount(0) + 1;
						qle->SetMobCount(0, newcount);
						qle->SendUpdateAddKill(0);
						qle->UpdatePlayerFields();
						return;
					}
				}
			}
		}
};

//Quest 11397
class ChillmereScourge : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ChillmereScourge);
		ChillmereScourge(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* qle = TO_PLAYER(mKiller)->GetQuestLogForEntry(11397);
				if(qle != NULL)
				{
					if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[ 0 ])
					{
						uint32 newcount = qle->GetMobCount(0) + 1;
						qle->SetMobCount(0, newcount);
						qle->SendUpdateAddKill(0);
						qle->UpdatePlayerFields();
						return;
					}
				}
			}
		}
};

// Quest 11154
class FeknutsFirecrackersBunnyAI : public MoonScriptCreatureAI
{
    public:
		MOONSCRIPT_FACTORY_FUNCTION(FeknutsFirecrackersBunnyAI, MoonScriptCreatureAI);
		FeknutsFirecrackersBunnyAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			isContainerSpawned = false;
		}

		void OnLoad()
		{
			DarkClawBat = GetNearestCreature(23959);
			if(DarkClawBat && GetRange(DarkClawBat) <= 20.0f)
				DarkClawBat->MoveTo(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
			RegisterAIUpdateEvent(0);
			ParentClass::OnLoad();
		}

		void AIUpdate()
		{
			do
			{
				if(GetRange(DarkClawBat) <= 10.0f)
				{
					_unit->GetMapMgr()->MapScriptInterface()->SpawnGameObject(186325, _unit->GetPositionX(), _unit->GetPositionY(), _unit->getPositionZ(), _unit->getOrientation(), true, 0, 0);
					isContainerSpawned = true;
				}
			}while(!isContainerSpawned && DarkClawBat);

			ParentClass::AIUpdate();
		}

	private:
		bool isContainerSpawned;
		MoonScriptCreatureAI* DarkClawBat;
};

//Quest 11283
class Baleheim : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Baleheim);
		Baleheim(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* qle = TO_PLAYER(mKiller)->GetQuestLogForEntry(11283);
				if(qle != NULL)
				{
					if(qle->GetMobCount(0) < qle->GetQuest()->required_mobcount[ 0 ])
					{
						uint32 newcount = qle->GetMobCount(0) + 1;
						qle->SetMobCount(0, newcount);
						qle->SendUpdateAddKill(0);
						qle->UpdatePlayerFields();
						return;
					}
				}
			}
		}
};

//Quest 11332
class Plaguethis_Gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Where would you like to fly too ?", 2);
			if(plr->GetQuestLogForEntry(11332) != NULL)
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Greer, i need a gryphon to ride and some bombs to drop on New Agamand!", 1);

			//He is quest giver
			sQuestMgr.FillQuestMenu(TO_CREATURE(pObject), plr, menu);

			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 1:
					{
						Item* item;
						item = objmgr.CreateItem(33634 , plr);
						item->SetStackCount(10);

						if(!plr->GetItemInterface()->AddItemToFreeSlot(item))
						{
							//World Strings?
							plr->GetSession()->SendNotification("No free slots were found in your inventory!");
							item->DeleteMe();
						}
						else
						{
							plr->SendItemPushResult(false, true, false, true, plr->GetItemInterface()->LastSearchResult()->ContainerSlot,
							plr->GetItemInterface()->LastSearchResult()->Slot, 1, item->GetEntry(), item->GetItemRandomSuffixFactor(),
							item->GetItemRandomPropertyId(), item->GetStackCount());

						}
						plr->TaxiStart(sTaxiMgr.GetTaxiPath(745), 17759, 0);
					}break;
				case 2: plr->GetSession()->SendTaxiList(TO_CREATURE(pObject)); break;
			}
			plr->Gossip_Complete();
		}

};

void SetupHowlingFjord(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(23998, new DeathstalkerRazaelGossip);
	mgr->register_creature_gossip(23778, new DarkRangerLyanaGossip);
	mgr->register_creature_gossip(23859, new Plaguethis_Gossip); // thx  Dzjhenghiz

	mgr->register_creature_script(23643, &ChillmereScourge::Create);
	mgr->register_creature_script(23645, &ChillmereScourge::Create);
	mgr->register_creature_script(23644, &ChillmereScourge::Create);
	mgr->register_creature_script(24540, &ChillmereScourge::Create);
	mgr->register_creature_script(24485, &ChillmereScourge::Create);
	mgr->register_creature_script(23653, &Baleheim::Create);
	mgr->register_creature_script(23655, &Baleheim::Create);
	mgr->register_creature_script(24015, &Baleheim::Create);
	mgr->register_creature_script(23866, &NorthFleet::Create);
	mgr->register_creature_script(23934, &NorthFleet::Create);
	mgr->register_creature_script(23946, &NorthFleet::Create);
	mgr->register_creature_script(23794, &NorthFleet::Create);
	mgr->register_creature_script(23793, &NorthFleet::Create);
	mgr->register_creature_script(24230, &FeknutsFirecrackersBunnyAI::Create);
}
