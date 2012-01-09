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
 
class DarnassusGuard : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), 3016);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Auction House"      , 1);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The Bank"           , 2);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Hippogryph Master"  , 3);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Guild Master"       , 4);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The Inn"            , 5);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mailbox"            , 6);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Stable Master"      , 7);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Weapons Trainer"    , 8);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Battlemaster"       , 9);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Class Trainer"      , 10);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Profession Trainer" , 11);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Lexicon of Power"   , 27);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 0:	OnHello(pObject, Plr); break;
				case 1:     // Auction House
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3833, Plr);
						Plr->Gossip_SendPOI(9861.23f, 2334.55f, 7, 99, 0, "Darnassus Auction House");
					}break;
				case 2:		// The Bank
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3017, Plr);
						Plr->Gossip_SendPOI(9938.45f, 2512.35f, 7, 99, 0, "Darnassus Bank");
					}break;
				case 3:		// Hippogryph Master
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3018, Plr);
						Plr->Gossip_SendPOI(9945.65f, 2618.94f, 7, 99, 0, "Rut'theran Village");
					}break;
				case 4:		// Guild Master
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3019, Plr);
						Plr->Gossip_SendPOI(10076.40f, 2199.59f, 7, 99, 0, "Darnassus Guild Master");
					}break;
				case 5:		// The Inn
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3020, Plr);
						Plr->Gossip_SendPOI(10133.29f, 2222.52f, 7, 99, 0, "Darnassus Inn");
					}break;
				case 6:		// Mailbox
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3021, Plr);
						Plr->Gossip_SendPOI(9942.17f, 2495.48f, 7, 99, 0, "Darnassus Mailbox");
					}break;
				case 7:		// Stable Master
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 5980, Plr);
						Plr->Gossip_SendPOI(10167.20f, 2522.66f, 7, 99, 0, "Alassin");
					}break;
				case 8:		// Weapons Trainer
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4517, Plr);
						Plr->Gossip_SendPOI(9907.11f, 2329.70f, 7, 99, 0, "Ilyenia Moonfire");
					}break;
				case 9:    // Battlemaster
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 7519, Plr);
						Plr->Gossip_SendPOI(9981.9f, 2325.9f, 7, 99, 0, "Battlemasters Darnassus");
					}break;
				case 10:    // Class Trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 4264);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Druid"       , 12);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Hunter"      , 13);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Priest"      , 14);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Rogue"       , 15);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Warrior"     , 16);
						menu.Send(Plr);
					}break;
				case 11:    // Profession Trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 4273);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Alchemy"           , 17);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Cooking"           , 18);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Enchanting"        , 19);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "First Aid"         , 20);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Fishing"           , 21);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Herbalism"         , 22);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Inscription"       , 23);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Leatherworking"    , 24);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Skinning"          , 25);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Tailoring"         , 26);
						menu.Send(Plr);
					}break;
				case 12:	// Druid
					{
						Plr->Gossip_SendPOI(10186, 2570.46f, 7, 99, 0, "Darnassus Druid Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3024, Plr);
					}break;
				case 13:	// Hunter
					{
						Plr->Gossip_SendPOI(10177.29f, 2511.10f, 7, 99, 0, "Darnassus Hunter Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3023, Plr);
					}break;
				case 14:	// Priest
					{
						Plr->Gossip_SendPOI(9659.12f, 2524.88f, 7, 99, 0, "Temple of the Moon");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3025, Plr);
					}break;
				case 15:	// Rogue
					{
						Plr->Gossip_SendPOI(10122, 2599.12f, 7, 99, 0, "Darnassus Rogue Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3026, Plr);
					}break;
				case 16:	// Warrior
					{
						Plr->Gossip_SendPOI(9951.91f, 2280.38f, 7, 99, 0, "Warrior's Terrace");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3033, Plr);
					}
					break;
				case 17: //Alchemy
					{
						Plr->Gossip_SendPOI(10075.90f, 2356.76f, 7, 99, 0, "Darnassus Alchemy Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3035, Plr);
					}break;
				case 18: //Cooking
					{
						Plr->Gossip_SendPOI(10088.59f, 2419.21f, 7, 99, 0, "Darnassus Cooking Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3036, Plr);
					}break;
				case 19: //Enchanting
					{
						Plr->Gossip_SendPOI(10146.09f, 2313.42f, 7, 99, 0, "Darnassus Enchanting Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3337, Plr);
					}break;
				case 20: //First Aid
					{
						Plr->Gossip_SendPOI(10150.09f, 2390.43f, 7, 99, 0, "Darnassus First Aid Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3037, Plr);
					}break;
				case 21: //Fishing
					{
						Plr->Gossip_SendPOI(9836.20f, 2432.17f, 7, 99, 0, "Darnassus Fishing Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3038, Plr);
					}break;
				case 22: //Herbalism
					{
						Plr->Gossip_SendPOI(9757.17f, 2430.16f, 7, 99, 0, "Darnassus Herbalism Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3039, Plr);
					}break;
				case 23: //Inscription
					{
						Plr->Gossip_SendPOI(10146.09f, 2313.42f, 7, 99, 0, "Darnassus Inscription Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 13886, Plr);
					}break;
				case 24: //Leatherworking
					{
						Plr->Gossip_SendPOI(10086.59f, 2255.77f, 7, 99, 0, "Darnassus Leatherworking Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3040, Plr);
					}break;
				case 25: //Skinning
					{
						Plr->Gossip_SendPOI(10081.40f, 2257.18f, 7, 99, 0, "Darnassus Skinning Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3042, Plr);
					}break;
				case 26: //Tailoring
					{
						Plr->Gossip_SendPOI(10079.70f, 2268.19f, 7, 99, 0, "Darnassus Tailor");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3044, Plr);
					}break;
				case 27: //Lexicon of Power
					{
						Plr->Gossip_SendPOI(10146.09f, 2313.42f, 7, 99, 0, "Darnassus Inscription Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 14174, Plr);
					}break;
			}
		}
};

void SetupDarnassusGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(4262, new DarnassusGuard);			// Darnassus Sentinel
}