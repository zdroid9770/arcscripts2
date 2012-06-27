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

class EthereumTransponderZeta : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(EthereumTransponderZeta)
		EthereumTransponderZeta(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player * pPlayer)
		{
			if(pPlayer->HasQuest(10339) && sEAS.GetNearestCreature(pPlayer, 20482) == NULL)
				sEAS.SpawnCreature(pPlayer, 20482, 4017.96f, 2315.91f, 116.418f, pPlayer->GetOrientation()+3.14f, DEFAULT_DESPAWN_TIMER);
		}
};

class Veronia : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			if(plr->GetQuestLogForEntry(10652))
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 1, plr);
				Menu->AddItem(0, "I'm ready", 1);
				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* creat = TO_CREATURE(pObject);
			switch(IntId)
			{
				case 1:
					creat->CastSpell(plr, dbcSpell.LookupEntry(34905), true);
					break;
			}
		}
};

class ProtectorateNetherDrake_Gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			if(plr->HasQuest(10438))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Fly me to Ultris", 0);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			if(Id == 0)
			{
				TaxiPath * mPatch = sTaxiMgr.GetTaxiPath(627);
				uint32 mount_display_id = plr->GetTeam() == TEAM_ALLIANCE ? sTaxiMgr.GetTaxiNode(mPatch->GetSourceNode())->alliance_mount : sTaxiMgr.GetTaxiNode(mPatch->GetSourceNode())->horde_mount;
				plr->TaxiStart(mPatch, mount_display_id, 0);
			}
		}
};

void SetupNetherstorm(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(184383, &EthereumTransponderZeta::Create);	// Ethereum Transponder Zeta
	mgr->register_gossip_script(20162, new Veronia);
	mgr->register_creature_gossip(20903, new ProtectorateNetherDrake_Gossip);
}
