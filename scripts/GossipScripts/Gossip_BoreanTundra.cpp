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

class TiareGossipScript : public Arcemu::Gossip::Script
{
public:
	void OnHello(Object* pObject, Player* Plr)
	{
		Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 1, Plr, 1, Arcemu::Gossip::ICON_CHAT, "Teleport me to Amber Ledge!");
	}

	void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* EnteredCode)
	{
		Arcemu::Gossip::Menu::Complete(plr);
		TO_CREATURE(pObject)->CastSpell(plr, dbcSpell.LookupEntry(50135), true);
	}
};

class FizzcrankGossip : public Arcemu::Gossip::Script
{
public:
	void OnHello(Object *pObject, Player *Plr)
	{
		Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);
		if( Plr->HasQuest(11708))
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Tell me what's going on out here, Fizzcrank.", 1);
		menu.Send(Plr);
	}

	void OnSelectOption(Object *pObject, Player *Plr, uint32 Id, const char *EnteredCode)
	{
		Arcemu::Gossip::Menu menu(pObject->GetGUID(), 12455+Id);
		if(Id != 9)
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Go on.", ++Id);

		menu.Send(Plr);
	}
};

class SurristraszGossip : public Arcemu::Gossip::Script
{
public:
	void OnHello(Object *pObject, Player *Plr)
	{
		Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I'd like passage to the Transitus Shield.", 1); 
		menu.AddItem(Arcemu::Gossip::ICON_FLIGHTMASTER, "May I use a drake to fly elsewhere?", 2);
		menu.Send(Plr);
	}

	void OnSelectOption(Object *pObject, Player *Plr, uint32 Id, const char *EnteredCode)
	{
		Creature *pCreature = TO_CREATURE(pObject);

		if(Id == 1)
		{
			Arcemu::Gossip::Menu::Complete(Plr);
			pCreature->CastSpell(Plr, 46064, true);
		}else Plr->GetSession()->SendTaxiList(pCreature);
	}
};

void SetupBoreanTundraGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(30051, new TiareGossipScript);	// Tiare
	mgr->register_creature_gossip(25590, new FizzcrankGossip);		// Fizzcrank Fullthrottle
	mgr->register_creature_gossip(24795, new SurristraszGossip);	// Surristrasz
}