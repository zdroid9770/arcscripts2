/*
 * ArcScripts2 Scripts for Ascent MMORPG Server
 * Copyright (C) 2011 ArcScripts2 Team
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

class IronforgeGuard : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), 2760);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Auction House"			, 1);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Bank of Ironforge"		, 2);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Deeprun Tram"				, 3);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Gryphon Master"			, 4);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Guild Master"				, 5);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The Inn"					, 6);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mailbox"					, 7);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Stable Master"			, 8);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Weapons Trainer"			, 9);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Battlemaster"				, 10);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Barber"					, 11);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Class Trainer"			, 12);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Profession Trainer"		, 13);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Lexicon of Power"			, 35);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 0:	OnHello(pObject, Plr);	break;
				case 1:     // Auction House
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3014, Plr);
						Plr->Gossip_SendPOI(-4957.39f, -911.6f, 7, 6, 0, "Ironforge Auction House");
					}break;
				case 2:     // Bank of Ironforge
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2761, Plr);
						Plr->Gossip_SendPOI(-4891.91f, -991.47f, 7, 6, 0, "The Vault");
					}break;
				case 3:     // Deeprun Tram
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3814, Plr);
						Plr->Gossip_SendPOI(-4835.27f, -1294.69f, 7, 6, 0, "Deeprun Tram");
					}break;
				case 4:     // Gryphon Master
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2762, Plr);
						Plr->Gossip_SendPOI(-4821.52f, -1152.3f, 7, 6, 0, "Ironforge Gryphon Master");
					}break;
				case 5:     // Guild Master
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2764, Plr);
						Plr->Gossip_SendPOI(-5021, -996.45f, 7, 6, 0, "Ironforge Visitor's Center");
					}break;
				case 6:     // The Inn
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2768, Plr);
						Plr->Gossip_SendPOI(-4850.47f, -872.57f, 7, 6, 0, "Stonefire Tavern");
					}break;
				case 7:     // Mailbox
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2769, Plr);
						Plr->Gossip_SendPOI(-4845.7f, -880.55f, 7, 6, 0, "Ironforge Mailbox");
					}break;
				case 8:     // Stable Master
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 5986, Plr);
						Plr->Gossip_SendPOI(-5010.2f, -1262, 7, 6, 0, "Ulbrek Firehand");
					}break;
				case 9:    // Weapon Trainer
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4518, Plr);
						Plr->Gossip_SendPOI(-5040, -1201.88f, 7, 6, 0, "Bixi and Buliwyf");
					}break;
				case 10:    // Battlemaster
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 10216, Plr);
						Plr->Gossip_SendPOI(-5038.54f, -1266.44f, 7, 6, 0, "Battlemasters Ironforge");
					}break;
				case 11:    // Barber
					{
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 13885, Plr);
						Plr->Gossip_SendPOI(-4838.49f, -919.18f, 7, 6, 0, "Ironforge Barber");
					}break;
				case 12:    // A class trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 2766);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Hunter"      , 14);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mage"        , 15);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Paladin"     , 16);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Priest"      , 17);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Rogue"       , 18);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Warlock"     , 19);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Warrior"     , 20);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Shaman"      , 21);
						menu.Send(Plr);
					}break;
				case 13:    // A profession trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 2793);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Alchemy"           , 22);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Blacksmithing"     , 23);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Cooking"           , 24);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Enchanting"        , 25);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Engineering"       , 26);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "First Aid"         , 27);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Fishing"           , 28);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Herbalism"         , 29);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Inscription"		, 30);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Leatherworking"    , 31);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mining"            , 32);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Skinning"          , 33);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Tailoring"         , 34);
						menu.Send(Plr);
					}break;
				case 14: //Hunter
					{
						Plr->Gossip_SendPOI(-5023, -1253.68f, 7, 6, 0, "Hall of Arms");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2770, Plr);
					}break;
				case 15: //Mage
					{
						Plr->Gossip_SendPOI(-4627, -926.45f, 7, 6, 0, "Hall of Mysteries");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2771, Plr);
					}break;
				case 16: //Paladin
					{
						Plr->Gossip_SendPOI(-4627.02f, -926.45f, 7, 6, 0, "Hall of Mysteries");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2773, Plr);
					}break;
				case 17: //Priest
					{
						Plr->Gossip_SendPOI(-4627, -926.45f, 7, 6, 0, "Hall of Mysteries");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2772, Plr);
					}break;
				case 18: //Rogue
					{
						Plr->Gossip_SendPOI(-4647.83f, -1124, 7, 6, 0, "Ironforge Rogue Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2774, Plr);
					}break;
				case 19: //Warlock
					{
						Plr->Gossip_SendPOI(-4605, -1110.45f, 7, 6, 0, "Ironforge Warlock Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2775, Plr);
					}break;
				case 20: //Warrior
					{
						Plr->Gossip_SendPOI(-5023.08f, -1253.68f, 7, 6, 0, "Hall of Arms");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2776, Plr);
					}break;
				case 21: //Shaman
					{
						Plr->Gossip_SendPOI(-4722.02f, -1150.66f, 7, 6, 0, "Ironforge Shaman Trainer");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 10842, Plr);
					}break;
				case 22: //Alchemy
					{
						Plr->Gossip_SendPOI(-4858.5f, -1241.83f, 7, 6, 0, "Berryfizz's Potions and Mixed Drinks");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2794, Plr);
					}break;
				case 23: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-4796.97f, -1110.17f, 7, 6, 0, "The Great Forge");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2795, Plr);
					}break;
				case 24: //Cooking
					{
						Plr->Gossip_SendPOI(-4767.83f, -1184.59f, 7, 6, 0, "The Bronze Kettle");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2796, Plr);
					}break;
				case 25: //Enchanting
					{
						Plr->Gossip_SendPOI(-4803.72f, -1196.53f, 7, 6, 0, "Thistlefuzz Arcanery");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2797, Plr);
					}break;
				case 26: //Engineering
					{
						Plr->Gossip_SendPOI(-4799.56f, -1250.23f, 7, 6, 0, "Springspindle's Gadgets");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2798, Plr);
					}break;
				case 27: //First Aid
					{
						Plr->Gossip_SendPOI(-4881.6f, -1153.13f, 7, 6, 0, "Ironforge Physician");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2799, Plr);
					}break;
				case 28: //Fishing
					{
						Plr->Gossip_SendPOI(-4597.91f, -1091.93f, 7, 6, 0, "Traveling Fisherman");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2800, Plr);
					}break;
				case 29: //Herbalism
					{
						Plr->Gossip_SendPOI(-4876.9f, -1151.92f, 7, 6, 0, "Ironforge Physician");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2801, Plr);
					}break;
				case 30: //Inscription
					{
						Plr->Gossip_SendPOI(-4801.72f, -1189.41f, 7, 6, 0, "Ironforge Inscription");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 13884, Plr);
					}break;
				case 31: //Leatherworking
					{
						Plr->Gossip_SendPOI(-4745, -1027.57f, 7, 6, 0, "Finespindle's Leather Goods");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2802, Plr);
					}break;
				case 32: //Mining
					{
						Plr->Gossip_SendPOI(-4705.06f, -1116.43f, 7, 6, 0, "Deepmountain Mining Guild");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2804, Plr);
					}break;
				case 33: //Skinning
					{
						Plr->Gossip_SendPOI(-4745, -1027.57f, 7, 6, 0, "Finespindle's Leather Goods");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2805, Plr);
					}break;
				case 34: //Tailoring
					{
						Plr->Gossip_SendPOI(-4719.60f, -1056.96f, 7, 6, 0, "Stonebrow's Clothier");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 2807, Plr);
					}break;
				case 35: //Lexicon of Power
					{
						Plr->Gossip_SendPOI(-4801.72f, -1189.41f, 7, 6, 0, "Ironforge Inscription");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 14174, Plr);
					}break;
			}
		}
};

void SetupIronforgeGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(5595, new IronforgeGuard);				// Ironforge Guard
}
