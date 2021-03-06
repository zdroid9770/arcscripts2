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

#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, plr); \ Menu->SendTo(plr);

class CuregosGold : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(CuregosGold)
		CuregosGold(GameObject *goinstance) : GameObjectAIScript(goinstance) {}

		void OnActivate(Player *pPlayer)
		{
			if(pPlayer->HasQuest(2882))
				pPlayer->CastSpell(pPlayer, 11462, true); // Cast spell: "Summon Pirate Treasure and Trigger Mob".
		}
};

class SpiritScreeches : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			if(!plr)
				return;

			GossipMenu* Menu;
			Creature* spirit = TO_CREATURE(pObject);
			if(spirit == NULL)
				return;

			if(plr->GetQuestLogForEntry(3520))
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2039, plr);
				Menu->AddItem(0, "Goodbye", 1);

				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* EnteredCode)
		{
			if(!plr)
				return;

			Creature* spirit = TO_CREATURE(pObject);
			if(spirit == NULL)
				return;

			switch(IntId)
			{
				case 0:
					GossipHello(pObject, plr);
					break;

				case 1:
					{
						QuestLogEntry* en = plr->GetQuestLogForEntry(3520);
						if(en && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
						{
							en->SetMobCount(0, en->GetMobCount(0) + 1);
							en->SendUpdateAddKill(0);
							en->UpdatePlayerFields();
						}
						if(!spirit)
							return;

						spirit->Despawn(1, 0);
						return;

					}
			}
		}

};

class ScreecherSpirit : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ScreecherSpirit);

		ScreecherSpirit(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			if(!_unit)
				return;

			Creature* cialo = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 5307);
			if(!cialo)
				return;

			if(!cialo->isAlive())
				cialo->Despawn(1, 6 * 60 * 1000);

			_unit->Despawn(60 * 1000, 0);
		}
};

class StewardOfTime : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			if(plr->GetQuestLogForEntry(10279) || plr->HasFinishedQuest(10279))
			{
				objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9978, plr);
				Menu->AddItem(0, "Please take me to the master's lair", 1);
				Menu->SendTo(plr);
			}
		}

		void GossipSelectOption(Object* pObject, Player* plr, uint32 Id, uint32 IntId, const char* Code)
		{
			Creature* creat = TO_CREATURE(pObject);
			switch(IntId)
			{
				case 1:
					creat->CastSpell(plr, dbcSpell.LookupEntry(34891), true);
					break;
			}
		}

};

void SetupTanaris(ScriptMgr* mgr)
{
	mgr->register_gameobject_script(142189, &CuregosGold::Create);	// Inconspicuous Landmark
	mgr->register_gossip_script(8612, new SpiritScreeches);
	mgr->register_creature_script(8612, &ScreecherSpirit::Create);
	mgr->register_gossip_script(20142, new StewardOfTime);
}
