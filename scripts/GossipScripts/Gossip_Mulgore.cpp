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

class ThunderbluffGuard : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), 3543);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The bank", 1);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The wind rider master", 2);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The guild master", 3);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The inn", 4);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The mailbox", 5);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The auction house", 6);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The weapon master", 7);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The stable master", 8);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The battlemaster", 9);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "A class trainer", 10);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "A profession trainer", 11);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 0:  OnHello(pObject, Plr); break;// Return to start
				case 1:     // The bank
					{
						Plr->Gossip_SendPOI(-1257.8f, 24.14f, 7, 99, 0, "Thunder Bluff Bank");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1292, Plr);
					}break;
				case 2:     // The wind rider master
					{
						Plr->Gossip_SendPOI(-1196.43f, 28.26f, 7, 99, 0, "Wind Rider Roost");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1293, Plr);
					}break;
				case 3:     // The guild master
					{
						Plr->Gossip_SendPOI(-1296.5f, 127.57f, 7, 99, 0, "Thunder Bluff Civic Information");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1291, Plr);
					}break;
				case 4:     // The inn
					{
						Plr->Gossip_SendPOI(-1296, 39.7f, 7, 99, 0, "Thunder Bluff Inn");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3153, Plr);
					}break;
				case 5:     // The mailbox
					{
						Plr->Gossip_SendPOI(-1263.59f, 44.36f, 7, 99, 0, "Thunder Bluff Mailbox");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3154, Plr);
					}break;
				case 6:     // The auction house
					{
						Plr->Gossip_SendPOI(-1205.51f, 105.74f, 7, 99, 0, "Thunder Bluff Auction house");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 3155, Plr);
					}break;
				case 7:     // The weapon master
					{
						Plr->Gossip_SendPOI(-1282.31f, 89.56f, 7, 99, 0, "Ansekhwa");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4520, Plr);
					}break;
				case 8:     // The stable master
					{
						Plr->Gossip_SendPOI(-1270.19f, 48.84f, 7, 99, 0, "Bulrug");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 5977, Plr);
					}break;
				case 9:    // The battlemaster
					{
						Plr->Gossip_SendPOI(-1391.22f, -81.33f, 7, 99, 0, "Battlemasters Thunder Bluff");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 7527, Plr);
					}break;
				case 10:    // A class trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 3542);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Druid"       , 12);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Hunter"      , 13);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mage"        , 14);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Priest"      , 15);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Shaman"      , 16);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Warrior"     , 17);
						menu.Send(Plr);
					}break;
				case 11:    // A profession trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 3541);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Alchemy"           , 18);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Blacksmithing"     , 19);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Cooking"           , 20);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Enchanting"        , 21);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "First Aid"         , 22);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Fishing"           , 23);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Herbalism"         , 24);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Leatherworking"    , 25);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mining"            , 26);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Skinning"          , 27);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Tailoring"         , 28);
						menu.Send(Plr);
					}break;
				case 12: //Druid
					{
						Plr->Gossip_SendPOI(-1054.47f, -285, 7, 99, 0, "Hall of Elders");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1294, Plr);
					}break;
				case 13: //Hunter
					{
						Plr->Gossip_SendPOI(-1416.32f, -114.28f, 7, 99, 0, "Hunter's Hall");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1295, Plr);
					}break;
				case 14: //Mage
					{
						Plr->Gossip_SendPOI(-1061.2f, 195.5f, 7, 99, 0, "Pools of Vision");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1296, Plr);
					}break;
				case 15: //Priest
					{
						Plr->Gossip_SendPOI(-1061.2f, 195.5f, 7, 99, 0, "Pools of Vision");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1297, Plr);
					}break;
				case 16: //Shaman
					{
						Plr->Gossip_SendPOI(-989.54f, 278.25f, 7, 99, 0, "Hall of Spirits");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1298, Plr);
					}break;
				case 17: //Warrior
					{
						Plr->Gossip_SendPOI(-1416.32f, -114.28f, 7, 99, 0, "Hunter's Hall");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1299, Plr);
					}break;
				case 18: //Alchemy
					{
						Plr->Gossip_SendPOI(-1085.56f, 27.29f, 7, 99, 0, "Bena's Alchemy");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1332, Plr);
					}break;
				case 19: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-1239.75f, 104.88f, 7, 99, 0, "Karn's Smithy");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1333, Plr);
					}break;
				case 20: //Cooking
					{
						Plr->Gossip_SendPOI(-1214.5f, -21.23f, 7, 99, 0, "Aska's Kitchen");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1334, Plr);
					}break;
				case 21: //Enchanting
					{
						Plr->Gossip_SendPOI(-1112.65f, 48.26f, 7, 99, 0, "Dawnstrider Enchanters");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1335, Plr);
					}break;
				case 22: //First Aid
					{
						Plr->Gossip_SendPOI(-996.58f, 200.5f, 7, 99, 0, "Spiritual Healing");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1336, Plr);
					}break;
				case 23: //Fishing
					{
						Plr->Gossip_SendPOI(-1169.35f, -68.87f, 7, 99, 0, "Mountaintop Bait & Tackle");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1337, Plr);
					}break;
				case 24: //Herbalism
					{
						Plr->Gossip_SendPOI(-1137.7f, -1.51f, 7, 99, 0, "Holistic Herbalism");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1338, Plr);
					}break;
				case 25: //Leatherworking
					{
						Plr->Gossip_SendPOI(-1156.22f, 66.86f, 7, 99, 0, "Thunder Bluff Armorers");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1339, Plr);
					}break;
				case 26: //Mining
					{
						Plr->Gossip_SendPOI(-1249.17f, 155, 7, 99, 0, "Stonehoof Geology");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1340, Plr);
					}break;
				case 27: //Skinning
					{
						Plr->Gossip_SendPOI(-1148.56f, 51.18f, 7, 99, 0, "Mooranta");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1343, Plr);
					}break;
				case 28: //Tailoring
					{
						Plr->Gossip_SendPOI(-1156.22f, 66.86f, 7, 99, 0, "Thunder Bluff Armorers");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 1341, Plr);
					}break;
			}
		}
};


class BloodhoofGuard : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), 3543);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The bank", 1);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The wind rider master", 2);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The inn", 3);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "The stable master", 4);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "A class trainer", 5);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "A profession trainer", 6);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			switch(Id)
			{
				case 0: OnHello(pObject, Plr); break;	// Return to start
				case 1:     // The bank
					{
						Plr->Gossip_SendPOI(-1257.8f, 24.14f, 7, 99, 0, "Thunder Bluff Bank");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4051, Plr);
					}break;
				case 2:     // The wind rider master
					{
						Plr->Gossip_SendPOI(-1196.43f, 28.26f, 7, 99, 0, "Wind Rider Roost");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4052, Plr);
					}break;
				case 3:     // The inn
					{
						Plr->Gossip_SendPOI(-2361.38f, -349.19f, 7, 99, 0, "Bloodhoof Village Inn");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4053, Plr);
					}break;
				case 4:     // The stable master
					{
						Plr->Gossip_SendPOI(-2338.86f, -357.56f, 7, 99, 0, "Seikwa");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 5976, Plr);
					}break;
				case 5:     // A class trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 4069);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Druid"       , 7);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Hunter"      , 8);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Shaman"      , 9);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Warrior"    , 10);
						menu.Send(Plr);
					}break;
				case 6:     // A profession trainer
					{
						Arcemu::Gossip::Menu menu(pObject->GetGUID(), 3541);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Alchemy"           , 11);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Blacksmithing"     , 12);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Cooking"           , 13);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Enchanting"        , 14);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "First Aid"         , 15);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Fishing"           , 16);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Herbalism"         , 17);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Leatherworking"    , 18);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Mining"            , 19);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Skinning"          , 20);
						menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Tailoring"         , 21);
						menu.Send(Plr);
					}break;
				case 7: //Druid
					{
						Plr->Gossip_SendPOI(-2312.15f, -443.69f, 7, 99, 0, "Gennia Runetotem");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4054, Plr);
					}break;
				case 8: //Hunter
					{
						Plr->Gossip_SendPOI(-2178.14f, -406.14f, 7, 99, 0, "Yaw Sharpmane");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4055, Plr);
					}break;
				case 9: //Shaman
					{
						Plr->Gossip_SendPOI(-2301.5f, -439.87f, 7, 99, 0, "Narm Skychaser");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4056, Plr);
					}break;
				case 10: //Warrior
					{
						Plr->Gossip_SendPOI(-2345.43f, -494.11f, 7, 99, 0, "Krang Stonehoof");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4057, Plr);
					}break;
				case 11: //Alchemy
					{
						Plr->Gossip_SendPOI(-1085.56f, 27.29f, 7, 99, 0, "Bena's Alchemy");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4058, Plr);
					}break;
				case 12: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-1239.75f, 104.88f, 7, 99, 0, "Karn's Smithy");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4059, Plr);
					}break;
				case 13: //Cooking
					{
						Plr->Gossip_SendPOI(-2263.34f, -287.91f, 7, 99, 0, "Pyall Silentstride");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4060, Plr);
					}break;
				case 14: //Enchanting
					{
						Plr->Gossip_SendPOI(-1112.65f, 48.26f, 7, 99, 0, "Dawnstrider Enchanters");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4061, Plr);
					}break;
				case 15: //First Aid
					{
						Plr->Gossip_SendPOI(-2353.52f, -355.82f, 7, 99, 0, "Vira Younghoof");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4062, Plr);
					}break;
				case 16: //Fishing
					{
						Plr->Gossip_SendPOI(-2349.21f, -241.37f, 7, 99, 0, "Uthan Stillwater");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4063, Plr);
					}break;
				case 17: //Herbalism
					{
						Plr->Gossip_SendPOI(-1137.7f, -1.51f, 7, 99, 0, "Holistic Herbalism");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4064, Plr);
					}break;
				case 18: //Leatherworking
					{
						Plr->Gossip_SendPOI(-2257.12f, -288.63f, 7, 99, 0, "Chaw Stronghide");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4065, Plr);
					}break;
				case 19: //Mining
					{
						Plr->Gossip_SendPOI(-1249.17f, 155, 7, 99, 0, "Stonehoof Geology");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4066, Plr);
					}break;
				case 20: //Skinning
					{
						Plr->Gossip_SendPOI(-2252.94f, -291.32f, 7, 99, 0, "Yonn Deepcut");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4067, Plr);
					}break;
				case 21: //Tailoring
					{
						Plr->Gossip_SendPOI(-1156.22f, 66.86f, 7, 99, 0, "Thunder Bluff Armorers");
						Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 4068, Plr);
					}break;
			}
		}
};

class SkornWhitecloud_Gossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 522, plr, 1, Arcemu::Gossip::ICON_CHAT, "Tell me a story, Skorn.");
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* Code)
		{
			Arcemu::Gossip::Menu::SendSimpleMenu(pObject->GetGUID(), 523, plr);
		}
};

void SetupMulgoreGossip(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(3084, new ThunderbluffGuard);			// Bluffwatcher
	Arcemu::Gossip::Script* blood = new BloodhoofGuard;
	mgr->register_creature_gossip(3222, blood);			// Brave Wildrunner
	mgr->register_creature_gossip(3224, blood);			// Brave Cloudmane
	mgr->register_creature_gossip(3220, blood);			// Brave Darksky
	mgr->register_creature_gossip(3219, blood);			// Brave Leaping Deer
	mgr->register_creature_gossip(3217, blood);			// Brave Dawneagle
	mgr->register_creature_gossip(3215, blood);			// Brave Strongbash
	mgr->register_creature_gossip(3218, blood);			// Brave Swiftwind
	mgr->register_creature_gossip(3221, blood);			// Brave Rockhorn
	mgr->register_creature_gossip(3223, blood);			// Brave Rainchaser
	mgr->register_creature_gossip(3212, blood);			// Brave Ironhorn
	mgr->register_creature_gossip(3052, new SkornWhitecloud_Gossip); // Skorn Whitecloud
}
