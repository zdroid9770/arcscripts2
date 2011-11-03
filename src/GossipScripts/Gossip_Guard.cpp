/*
 * Moon++ Scripts for Ascent MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

/************************************************************************/
/* GENERAL GUARD SCRIPT                                                 */
/************************************************************************/

// Covers *all* guard types, scripting their texts to guide players around.
// Enable this define to make all gossip texts have a "back" / "I was looking
// for somethinge else" button added.

#define BACK_BUTTON

#ifdef BACK_BUTTON

// Make code neater with this define.
#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, Plr); \
    Menu->SendTo(Plr);

#else

// Make code neater with this define.
#define SendQuickMenu(textid) objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), textid, Plr); \
    Menu->AddItem(0, "I was looking for something else.", 0); \
    Menu->SendTo(Plr);

#endif

class TeldrassilGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4316, plr);

			Menu->AddItem(0, "The Bank", 1);
			Menu->AddItem(0, "Rut'Theran Ferry", 2);
			Menu->AddItem(0, "The Guild Master", 3);
			Menu->AddItem(0, "The Inn", 4);
			Menu->AddItem(0, "Stable Master", 5);
			Menu->AddItem(0, "Class Trainer", 6);
			Menu->AddItem(0, "Profession Trainer", 7);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // The Bank
					SendQuickMenu(4317);
					break;

				case 2:		// Rut'theran erry
					SendQuickMenu(4318);
					break;

				case 3:		// The Guild Master
					SendQuickMenu(4319);
					break;

				case 4:		// The Inn
					Plr->Gossip_SendPOI(9821.49f, 960.13f, 7, 6, 0, "Dolanaar Inn");
					SendQuickMenu(4320);
					break;

				case 5:		// Stable Master
					Plr->Gossip_SendPOI(9808.37f, 931.1f, 7, 6, 0, "Seriadne");
					SendQuickMenu(5982);
					break;

				case 6:    // Class Trainers
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4264, Plr);
						Menu->AddItem(0, "Druid"       , 8);
						Menu->AddItem(0, "Hunter"      , 9);
						Menu->AddItem(0, "Priest"     , 10);
						Menu->AddItem(0, "Rogue"      , 11);
						Menu->AddItem(0, "Warrior"    , 12);
						Menu->SendTo(Plr);
					}
					break;

				case 7:    // Profession Trainers
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4273, Plr);
						Menu->AddItem(0, "Alchemy"           , 13);
						Menu->AddItem(0, "Cooking"           , 14);
						Menu->AddItem(0, "Enchanting"        , 15);
						Menu->AddItem(0, "First Aid"         , 16);
						Menu->AddItem(0, "Fishing"           , 17);
						Menu->AddItem(0, "Herbalism"         , 18);
						Menu->AddItem(0, "Inscription"       , 19);
						Menu->AddItem(0, "Leatherworking"    , 20);
						Menu->AddItem(0, "Skinning"          , 21);
						Menu->AddItem(0, "Tailoring"         , 22);
						Menu->SendTo(Plr);
					}
					break;

					////////////////
					// Class trainer submenu
					////////

				case 8: //Druid
					{
						Plr->Gossip_SendPOI(9741.58f, 963.7f, 7, 6, 0, "Kal");
						SendQuickMenu(4323);
					}
					break;

				case 9: // Hunter
					{
						Plr->Gossip_SendPOI(9815.12f, 926.28f, 7, 6, 0, "Dazalar");
						SendQuickMenu(4324);
					}
					break;

				case 10: // Priest
					{
						Plr->Gossip_SendPOI(9906.16f, 986.63f, 7, 6, 0, "Laurna Morninglight");
						SendQuickMenu(4325);
					}
					break;

				case 11: // Rogue
					{
						Plr->Gossip_SendPOI(9789, 942.86f, 7, 6, 0, "Jannok Breezesong");
						SendQuickMenu(4326);
					}
					break;

				case 12: // Warrior
					{
						Plr->Gossip_SendPOI(9821.96f, 950.61f, 7, 6, 0, "Kyra Windblade");
						SendQuickMenu(4327);
					}
					break;

				case 13: // Alchemy
					{
						Plr->Gossip_SendPOI(9767.59f, 878.81f, 7, 6, 0, "Cyndra Kindwhisper");
						SendQuickMenu(4329);
					}
					break;

				case 14: // Cooking
					{
						Plr->Gossip_SendPOI(9751.19f, 906.13f, 7, 6, 0, "Zarrin");
						SendQuickMenu(4330);
					}
					break;

				case 15: // Enchanting
					{
						Plr->Gossip_SendPOI(10677.59f, 1946.56f, 7, 6, 0, "Alanna Raveneye");
						SendQuickMenu(4331);
					}
					break;

				case 16: // First Aid
					{
						Plr->Gossip_SendPOI(9903.12f, 999, 7, 6, 0, "Byancie");
						SendQuickMenu(4332);
					}
					break;

				case 17: // Fishing
					{
						SendQuickMenu(4333);
					}
					break;

				case 18: // Herbalism
					{
						Plr->Gossip_SendPOI(9773.78f, 875.88f, 7, 6, 0, "Malorne Bladeleaf");
						SendQuickMenu(4334);
					}
					break;

				case 19: // Inscription
					{
						Plr->Gossip_SendPOI(10146.09f, 2313.42f, 7, 6, 0, "Darnassus Inscription Trainer");
						SendQuickMenu(13886);
					}
					break;

				case 20: // Leatherworking
					{
						Plr->Gossip_SendPOI(10152.59f, 1681.46f, 7, 6, 0, "Nadyia Maneweaver");
						SendQuickMenu(4335);
					}
					break;

				case 21: // Skinning
					{
						Plr->Gossip_SendPOI(10135.59f, 1673.18f, 7, 6, 0, "Radnaal Maneweaver");
						SendQuickMenu(4336);
					}
					break;

				case 22: // Tailoring
					{
						SendQuickMenu(4337);
					}
					break;
			}
		}
};

class SilvermoonGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9316, plr);

			Menu->AddItem(0, "Auction House"		, 1);
			Menu->AddItem(0, "The Bank"				, 2);
			Menu->AddItem(0, "Dragonhawk Master"	, 3);
			Menu->AddItem(0, "Guild Master"			, 4);
			Menu->AddItem(0, "The Inn"				, 5);
			Menu->AddItem(0, "Mailbox"				, 6);
			Menu->AddItem(0, "Stable Master"		, 7);
			Menu->AddItem(0, "Weapon Master"		, 8);
			Menu->AddItem(0, "Battlemaster"			, 9);
			Menu->AddItem(0, "Class Trainer"		, 10);
			Menu->AddItem(0, "Profession Trainer"	, 11);
			Menu->AddItem(0, "Mana Loom"			, 12);
			Menu->AddItem(0, "Lexicon of Power"		, 40);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // Auction House
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9317, Plr);
					Menu->AddItem(0, "To the west."  , 13);
					Menu->AddItem(0, "To the east."    , 14);
					Menu->SendTo(Plr);
					break;

				case 2:     // The Bank
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9320, Plr);
					Menu->AddItem(0, "The west."  , 15);
					Menu->AddItem(0, "The east."    , 16);
					Menu->SendTo(Plr);
					break;

				case 3:     // Dragonhawk Master
					SendQuickMenu(9323);
					Plr->Gossip_SendPOI(9378.45f, -7163.94f, 7, 6, 0, "Silvermoon City, Flight Master");
					break;

				case 4:     // Guild Master
					SendQuickMenu(9324);
					Plr->Gossip_SendPOI(9480.75f, -7345.587f, 7, 6, 0, "Silvermoon City, Guild Master");
					break;

				case 5:     // The Inn
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9325, Plr);
					Menu->AddItem(0, "The Silvermoon City Inn."  , 17);
					Menu->AddItem(0, "The Wayfarer's Rest tavern."    , 18);
					Menu->SendTo(Plr);
					break;

				case 6:     // Mailbox
					SendQuickMenu(9326);
					Plr->Gossip_SendPOI(9743.078f, -7466.4f, 7, 6, 0, "Silvermoon City, Mailbox");
					break;

				case 7:     // Stable Master
					SendQuickMenu(9327);
					Plr->Gossip_SendPOI(9904.95f, -7404.31f, 7, 6, 0, "Silvermoon City, Stable Master");
					break;

				case 8:     // Weapon Master
					SendQuickMenu(9328);
					Plr->Gossip_SendPOI(9841.17f, -7505.13f, 7, 6, 0, "Silvermoon City, Weapon Master");
					break;

				case 9:     // Battlemasters
					SendQuickMenu(9329);
					Plr->Gossip_SendPOI(9850.74f, -7563.84f, 7, 6, 0, "Silvermoon City, Battlemasters");
					break;

				case 10:    // Class Trainers
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9331, Plr);
						Menu->AddItem(0, "Druid"       , 19);
						Menu->AddItem(0, "Hunter"      , 20);
						Menu->AddItem(0, "Mage"        , 21);
						Menu->AddItem(0, "Paladin"     , 22);
						Menu->AddItem(0, "Priest"      , 23);
						Menu->AddItem(0, "Rogue"       , 24);
						Menu->AddItem(0, "Warlock"     , 25);
						Menu->SendTo(Plr);
					}
					break;

				case 11:    // Profession Trainers
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9338, Plr);
						Menu->AddItem(0, "Alchemy"           , 26);
						Menu->AddItem(0, "Blacksmithing"     , 27);
						Menu->AddItem(0, "Cooking"           , 28);
						Menu->AddItem(0, "Enchanting"        , 29);
						Menu->AddItem(0, "Engineering"       , 30);
						Menu->AddItem(0, "First Aid"         , 31);
						Menu->AddItem(0, "Fishing"           , 32);
						Menu->AddItem(0, "Herbalism"         , 33);
						Menu->AddItem(0, "Inscription"       , 34);
						Menu->AddItem(0, "Jewelcrafting"     , 35);
						Menu->AddItem(0, "Leatherworking"    , 36);
						Menu->AddItem(0, "Mining"            , 37);
						Menu->AddItem(0, "Skinning"          , 38);
						Menu->AddItem(0, "Tailoring"         , 39);
						Menu->SendTo(Plr);
					}
					break;

				case 12: //Mana Loom
					{
						Plr->Gossip_SendPOI(9751.013f, -7074.85f, 7, 6, 0, "Silvermoon City, Mana Loom");
						SendQuickMenu(10502);
					}
					break;

				case 13: //To the west - Auction House no. 1
					{
						Plr->Gossip_SendPOI(9649.429f, -7134.027f, 7, 6, 0, "Silvermoon City, Auction House");
						SendQuickMenu(9318);
					}
					break;

				case 14: //To the east - Auction House no. 2
					{
						Plr->Gossip_SendPOI(9682.864f, -7515.786f, 7, 6, 0, "Silvermoon City, Auction House");
						SendQuickMenu(9319);
					}
					break;

				case 15:     // The bank - The west.
					SendQuickMenu(9321);
					Plr->Gossip_SendPOI(9522.104f, -7208.878f, 7, 6, 0, "Silvermoon City, Bank");
					break;

				case 16:     // The bank - The east.
					SendQuickMenu(9322);
					Plr->Gossip_SendPOI(9791.07f, -7488.041f, 7, 6, 0, "Silvermoon City, Bank");
					break;

				case 17: //The Silvermoon City Inn
					{
						Plr->Gossip_SendPOI(9677.113f, -7367.575f, 7, 6, 0, "Silvermoon City, Inn");
						SendQuickMenu(9325);
					}
					break;

				case 18: //The Wayfarer's Rest tavern
					{
						Plr->Gossip_SendPOI(9562.813f, -7218.63f, 7, 6, 0, "Silvermoon City, Inn");
						SendQuickMenu(9603);
					}
					break;

				case 19: //Druid
					{
						Plr->Gossip_SendPOI(9700.55f, -7262.57f, 7, 6, 0, "Silvermoon City, Druid Trainer");
						SendQuickMenu(9330);
					}
					break;

				case 20: //Hunter
					{
						Plr->Gossip_SendPOI(9930.568f, -7412.115f, 7, 6, 0, "Silvermoon City, Hunter Trainer");
						SendQuickMenu(9332);
					}
					break;

				case 21: //Mage
					{
						Plr->Gossip_SendPOI(9996.914f, -7104.803f, 7, 6, 0, "Silvermoon City, Mage Trainer");
						SendQuickMenu(9333);
					}
					break;

				case 22: //Paladin
					{
						Plr->Gossip_SendPOI(9850.22f, -7516.93f, 7, 6, 0, "Silvermoon City, Paladin Trainer");
						SendQuickMenu(9334);
					}
					break;

				case 23: //Priest
					{
						Plr->Gossip_SendPOI(9935.37f, -7131.14f, 7, 6, 0, "Silvermoon City, Priest Trainer");
						SendQuickMenu(9335);
					}
					break;

				case 24: //Rogue
					{
						Plr->Gossip_SendPOI(9739.88f, -7374.33f, 7, 6, 0, "Silvermoon City, Rogue Trainer");
						SendQuickMenu(9336);
					}
					break;

				case 25: //Warlock
					{
						Plr->Gossip_SendPOI(9803.052f, -7316.967f, 7, 6, 0, "Silvermoon City, Warlock Trainer");
						SendQuickMenu(9337);
					}
					break;

				case 26: //Alchemy
					{
						Plr->Gossip_SendPOI(10000.9f, -7216.63f, 7, 6, 0, "Silvermoon City, Alchemy");
						SendQuickMenu(9339);
					}
					break;

				case 27: //Blacksmithing
					{
						Plr->Gossip_SendPOI(9841.43f, -7361.53f, 7, 6, 0, "Silvermoon City, Blacksmithing");
						SendQuickMenu(9340);
					}
					break;

				case 28: //Cooking
					{
						Plr->Gossip_SendPOI(9577.26f, -7243.6f, 7, 6, 0, "Silvermoon City, Cooking");
						SendQuickMenu(9624);
					}
					break;

				case 29: //Enchanting
					{
						Plr->Gossip_SendPOI(9962.57f, -7246.18f, 7, 6, 0, "Silvermoon City, Enchanting");
						SendQuickMenu(9341);
					}
					break;

				case 30: //Engineering
					{
						Plr->Gossip_SendPOI(9808.85f, -7287.31f, 7, 6, 0, "Silvermoon City, Engineering");
						SendQuickMenu(9342);
					}
					break;

				case 31: //First Aid
					{
						Plr->Gossip_SendPOI(9588.61f, -7337.526f, 7, 6, 0, "Silvermoon City, First Aid");
						SendQuickMenu(9343);
					}
					break;

				case 32: //Fishing
					{
						Plr->Gossip_SendPOI(9601.97f, -7332.34f, 7, 6, 0, "Silvermoon City, Fishing");
						SendQuickMenu(9344);
					}
					break;

				case 33: //Herbalism
					{
						Plr->Gossip_SendPOI(9996.96f, -7208.39f, 7, 6, 0, "Silvermoon City, Herbalism");
						SendQuickMenu(9345);
					}
					break;
				case 34: //Inscription
					{
						Plr->Gossip_SendPOI(9957.12f, -7242.85f, 7, 6, 0, "Silvermoon City, Inscription");
						SendQuickMenu(13893);
					}
					break;

				case 35: //Jewelcrafting
					{
						Plr->Gossip_SendPOI(9552.8f, -7502.12f, 7, 6, 0, "Silvermoon City, Jewelcrafting");
						SendQuickMenu(9346);
					}
					break;

				case 36: //Leatherworking
					{
						Plr->Gossip_SendPOI(9502.486f, -7425.51f, 7, 6, 0, "Silvermoon City, Leatherworking");
						SendQuickMenu(9347);
					}
					break;

				case 37: //Mining
					{
						Plr->Gossip_SendPOI(9813.73f, -7360.19f, 7, 6, 0, "Silvermoon City, Mining");
						SendQuickMenu(9348);
					}
					break;

				case 38: //Skinning
					{
						Plr->Gossip_SendPOI(9513.37f, -7429.4f, 7, 6, 0, "Silvermoon City, Skinning");
						SendQuickMenu(9349);
					}
					break;

				case 39: //Tailoring
					{
						Plr->Gossip_SendPOI(9727.56f, -7086.65f, 7, 6, 0, "Silvermoon City, Tailoring");
						SendQuickMenu(9350);
					}
					break;
				case 40: //Lexicon of Power
					{
						Plr->Gossip_SendPOI(9957.12f, -7242.85f, 7, 6, 0, "Silvermoon City, Inscription");
						SendQuickMenu(14174);
					}
					break;
			}
		}
};

class ExodarGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9551, plr);
			Menu->AddItem(0, "Auction House"		, 1);
			Menu->AddItem(0, "The Bank"				, 2);
			Menu->AddItem(0, "Hippogryph Master"	, 3);
			Menu->AddItem(0, "Guild Master"			, 4);
			Menu->AddItem(0, "The Inn"				, 5);
			Menu->AddItem(0, "Mailbox"				, 6);
			Menu->AddItem(0, "Stable Master"		, 7);
			Menu->AddItem(0, "Weapon Master"		, 8);
			Menu->AddItem(0, "Battlemasters"		, 9);
			Menu->AddItem(0, "Class Trainer"		, 10);
			Menu->AddItem(0, "Profession Trainer"	, 11);
			Menu->AddItem(0, "Lexicon of Power"		, 34);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // Auction House
					SendQuickMenu(9528);
					Plr->Gossip_SendPOI(-4013.82f, -11729.64f, 7, 6, 0, "Exodar, Auctioneer");
					break;

				case 2:     // The Bank
					SendQuickMenu(9529);
					Plr->Gossip_SendPOI(-3923.89f, -11544.5f, 7, 6, 0, "Exodar, bank");
					break;

				case 3:     // Hippogryph Master
					SendQuickMenu(9530);
					Plr->Gossip_SendPOI(-4058.45f, -11789.7f, 7, 6, 0, "Exodar, Hippogryph Master");
					break;

				case 4:     // Guild Master
					SendQuickMenu(9539);
					Plr->Gossip_SendPOI(-4093.38f, -11630.39f, 7, 6, 0, "Exodar, Guild Master");
					break;

				case 5:     // The Inn
					SendQuickMenu(9545);
					Plr->Gossip_SendPOI(-3765.34f, -11695.8f, 7, 6, 0, "Exodar, Inn");
					break;

				case 6:     // Mailbox
					SendQuickMenu(10254);
					Plr->Gossip_SendPOI(-3913.75f, -11606.83f, 7, 6, 0, "Exodar, Mailbox");
					break;

				case 7:     // Stable Master
					SendQuickMenu(9558);
					Plr->Gossip_SendPOI(-3787.01f, -11702.7f, 7, 6, 0, "Exodar, Stable Master");
					break;

				case 8:     // Weapon Master
					SendQuickMenu(9565);
					Plr->Gossip_SendPOI(-4215.68f, -11628.9f, 7, 6, 0, "Exodar, Weapon Master");
					break;

				case 9:     // Battlemasters
					Plr->Gossip_SendPOI(-3999.82f, -11368.33f, 7, 6, 0, "Exodar, Battlemasters");
					objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9531, Plr);
					Menu->AddItem(0, "Arena Battlemaster"  , 12);
					Menu->SendTo(Plr);
					break;

				case 10:    // Class Trainers
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9533, Plr);
						Menu->AddItem(0, "Druid"       , 13);
						Menu->AddItem(0, "Hunter"      , 14);
						Menu->AddItem(0, "Mage"        , 15);
						Menu->AddItem(0, "Paladin"     , 16);
						Menu->AddItem(0, "Priest"      , 17);
						Menu->AddItem(0, "Shaman"      , 18);
						Menu->AddItem(0, "Warrior"     , 19);
						Menu->SendTo(Plr);
					}
					break;

				case 11:    // Profession Trainers
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 9555, Plr);
						Menu->AddItem(0, "Alchemy"           , 20);
						Menu->AddItem(0, "Blacksmithing"     , 21);
						Menu->AddItem(0, "Enchanting"        , 22);
						Menu->AddItem(0, "Engineering"       , 23);
						Menu->AddItem(0, "First Aid"         , 24);
						Menu->AddItem(0, "Fishing"           , 25);
						Menu->AddItem(0, "Herbalism"         , 26);
						Menu->AddItem(0, "Inscription"       , 27);
						Menu->AddItem(0, "Jewelcrafting"     , 28);
						Menu->AddItem(0, "Leatherworking"    , 29);
						Menu->AddItem(0, "Mining"            , 30);
						Menu->AddItem(0, "Skinning"          , 31);
						Menu->AddItem(0, "Tailoring"         , 32);
						Menu->AddItem(0, "Cooking"           , 33);
						Menu->SendTo(Plr);
					}
					break;

					//////////////////
					// Battlemaster submenu
					////////

				case 12://Arena Battlemaster Exodar
					{
						Plr->Gossip_SendPOI(-3725.25f, -11688.3f, 7, 6, 0, "Arena Battlemaster Exodar");
						SendQuickMenu(10223);
					}
					break;

				case 13: //Druid
					{
						Plr->Gossip_SendPOI(-4274.81f, -11495.3f, 7, 6, 0, "Exodar, Druid Trainer");
						SendQuickMenu(9534);
					}
					break;

				case 14: //Hunter
					{
						Plr->Gossip_SendPOI(-4229.36f, -11563.36f, 7, 6, 0, "Exodar, Hunter Trainers");
						SendQuickMenu(9544);
					}
					break;

				case 15: //Mage
					{
						Plr->Gossip_SendPOI(-4048.8f, -11559.02f, 7, 6, 0, "Exodar, Mage Trainers");
						SendQuickMenu(9550);
					}
					break;

				case 16: //Paladin
					{
						Plr->Gossip_SendPOI(-4176.57f, -11476.46f, 7, 6, 0, "Exodar, Paladin Trainers");
						SendQuickMenu(9553);
					}
					break;

				case 17: //Priest
					{
						Plr->Gossip_SendPOI(-3972.38f, -11483.2f, 7, 6, 0, "Exodar, Priest Trainers");
						SendQuickMenu(9554);
					}
					break;

				case 18: //Shaman
					{
						Plr->Gossip_SendPOI(-3843.8f, -11390.75f, 7, 6, 0, "Exodar, Shaman Trainer");
						SendQuickMenu(9556);
					}
					break;

				case 19: //Warrior
					{
						Plr->Gossip_SendPOI(-4191.11f, -11650.45f, 7, 6, 0, "Exodar, Warrior Trainers");
						SendQuickMenu(9562);
					}
					break;

				case 20: //Alchemy
					{
						Plr->Gossip_SendPOI(-4042.37f, -11366.3f, 7, 6, 0, "Exodar, Alchemist Trainers");
						SendQuickMenu(9527);
					}
					break;

				case 21: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-4232.4f, -11705.23f, 7, 6, 0, "Exodar, Blacksmithing Trainers");
						SendQuickMenu(9532);
					}
					break;

				case 22: //Enchanting
					{
						Plr->Gossip_SendPOI(-3889.3f, -11495, 7, 6, 0, "Exodar, Enchanters");
						SendQuickMenu(9535);
					}
					break;

				case 23: //Engineering
					{
						Plr->Gossip_SendPOI(-4257.93f, -11636.53f, 7, 6, 0, "Exodar, Engineering");
						SendQuickMenu(9536);
					}
					break;

				case 24: //First Aid
					{
						Plr->Gossip_SendPOI(-3766.05f, -11481.8f, 7, 6, 0, "Exodar, First Aid Trainer");
						SendQuickMenu(9537);
					}
					break;

				case 25: //Fishing
					{
						Plr->Gossip_SendPOI(-3726.64f, -11384.43f, 7, 6, 0, "Exodar, Fishing Trainer");
						SendQuickMenu(9538);
					}
					break;

				case 26: //Herbalism
					{
						Plr->Gossip_SendPOI(-4052.5f, -11356.6f, 7, 6, 0, "Exodar, Herbalism Trainer");
						SendQuickMenu(9543);
					}
					break;

				case 27: //Inscription
					{
						Plr->Gossip_SendPOI(-3889.3f, -11495, 7, 6, 0, "Exodar, Inscription");
						SendQuickMenu(13887);
					}
					break;

				case 28: //Jewelcrafting
					{
						Plr->Gossip_SendPOI(-3786.27f, -11541.33f, 7, 6, 0, "Exodar, Jewelcrafters");
						SendQuickMenu(9547);
					}
					break;

				case 29: //Leatherworking
					{
						Plr->Gossip_SendPOI(-4134.42f, -11772.93f, 7, 6, 0, "Exodar, Leatherworking");
						SendQuickMenu(9549);
					}
					break;

				case 30: //Mining
					{
						Plr->Gossip_SendPOI(-4220.31f, -11694.29f, 7, 6, 0, "Exodar, Mining Trainers");
						SendQuickMenu(9552);
					}
					break;

				case 31: //Skinning
					{
						Plr->Gossip_SendPOI(-4134.97f, -11760.5f, 7, 6, 0, "Exodar, Skinning Trainer");
						SendQuickMenu(9557);
					}
					break;

				case 32: //Tailoring
					{
						Plr->Gossip_SendPOI(-4095.78f, -11746.9f, 7, 6, 0, "Exodar, Tailors");
						SendQuickMenu(9350);
					}
					break;

				case 33: //Cooking
					{
						Plr->Gossip_SendPOI(-3799.69f, -11650.51f, 7, 6, 0, "Exodar, Cook");
						SendQuickMenu(9559);
					}
					break;

				case 34: //Lexicon of Power
					{
						Plr->Gossip_SendPOI(-3889.3f, -11495, 7, 6, 0, "Exodar, Inscription");
						SendQuickMenu(14174);
					}
					break;
			}
		}
};

class OrgrimmarGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);
			Menu->AddItem(0, "The bank", 1);
			Menu->AddItem(0, "The wind rider master", 2);
			Menu->AddItem(0, "The guild master", 3);
			Menu->AddItem(0, "The inn", 4);
			Menu->AddItem(0, "The mailbox", 5);
			Menu->AddItem(0, "The auction house", 6);
			Menu->AddItem(0, "The zeppelin master", 7);
			Menu->AddItem(0, "The weapon master", 8);
			Menu->AddItem(0, "The stable master", 9);
			Menu->AddItem(0, "The officers' lounge", 10);
			Menu->AddItem(0, "The battlemaster", 11);
			Menu->AddItem(0, "A class trainer", 12);
			Menu->AddItem(0, "A profession trainer", 13);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // The bank
					SendQuickMenu(2554);
					Plr->Gossip_SendPOI(1631.51f, -4375.33f, 7, 6, 0, "Bank of Orgrimmar");
					break;

				case 2:     // The wind rider master
					SendQuickMenu(2555);
					Plr->Gossip_SendPOI(1676.6f, -4332.72f, 7, 6, 0, "The Sky Tower");
					break;

				case 3:     // The guild master
					SendQuickMenu(2556);
					Plr->Gossip_SendPOI(1576.93f, -4294.75f, 7, 6, 0, "Horde Embassy");
					break;

				case 4:     // The inn
					SendQuickMenu(2557);
					Plr->Gossip_SendPOI(1644.51f, -4447.27f, 7, 6, 0, "Orgrimmar Inn");
					break;

				case 5:     // The mailbox
					SendQuickMenu(2558);
					Plr->Gossip_SendPOI(1622.53f, -4388.79f, 7, 6, 0, "Orgrimmar Mailbox");
					break;

				case 6:     // The auction house
					SendQuickMenu(3075);
					Plr->Gossip_SendPOI(1679.21f, -4450.1f, 7, 6, 0, "Orgrimmar Auction House");
					break;

				case 7:     // The zeppelin master
					SendQuickMenu(3173);
					Plr->Gossip_SendPOI(1337.36f, -4632.7f, 7, 6, 0, "Orgrimmar Zeppelin Tower");
					break;

				case 8:     // The weapon master
					SendQuickMenu(4519);
					Plr->Gossip_SendPOI(2092.56f, -4823.95f, 7, 6, 0, "Sayoc & Hanashi");
					break;

				case 9:     // The stable master
					SendQuickMenu(5974);
					Plr->Gossip_SendPOI(2133.12f, -4663.93f, 7, 6, 0, "Xon'cha");
					break;

				case 10:    // The officers' lounge
					SendQuickMenu(7046);
					Plr->Gossip_SendPOI(1633.56f, -4249.37f, 7, 6, 0, "Hall of Legends");
					break;

				case 11:    // The battlemaster
					SendQuickMenu(7521);
					Plr->Gossip_SendPOI(1990.41f, -4794.15f, 7, 6, 0, "Battlemasters Orgrimmar");
					break;

				case 12:    // A class trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2599, Plr);
						Menu->AddItem(0, "Hunter"       , 14);
						Menu->AddItem(0, "Mage"         , 15);
						Menu->AddItem(0, "Priest"       , 16);
						Menu->AddItem(0, "Shaman"       , 17);
						Menu->AddItem(0, "Rogue"        , 18);
						Menu->AddItem(0, "Warlock"      , 19);
						Menu->AddItem(0, "Warrior"      , 20);
						Menu->AddItem(0, "Paladin"      , 21);
						Menu->SendTo(Plr);
					}
					break;

				case 13:    // A profession trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2594, Plr);
						Menu->AddItem(0, "Alchemy"           , 22);
						Menu->AddItem(0, "Blacksmithing"     , 23);
						Menu->AddItem(0, "Cooking"           , 24);
						Menu->AddItem(0, "Enchanting"        , 25);
						Menu->AddItem(0, "Engineering"       , 26);
						Menu->AddItem(0, "First Aid"         , 27);
						Menu->AddItem(0, "Fishing"           , 28);
						Menu->AddItem(0, "Herbalism"         , 29);
						Menu->AddItem(0, "Leatherworking"    , 30);
						Menu->AddItem(0, "Mining"            , 31);
						Menu->AddItem(0, "Skinning"          , 32);
						Menu->AddItem(0, "Tailoring"         , 33);
						Menu->SendTo(Plr);
					}
					break;

					////////////////
					// Class trainer submenu
					////////

				case 14: //Hunter
					{
						Plr->Gossip_SendPOI(2114.84f, -4625.31f, 7, 6, 0, "Orgrimmar Hunter's Hall");
						SendQuickMenu(2559);
					}
					break;

				case 15: //Mage
					{
						Plr->Gossip_SendPOI(1451.26f, -4223.33f, 7, 6, 0, "Darkbriar Lodge");
						SendQuickMenu(2560);
					}
					break;

				case 16: //Priest
					{
						Plr->Gossip_SendPOI(1442.21f, -4183.24f, 7, 6, 0, "Spirit Lodge");
						SendQuickMenu(2561);
					}
					break;

				case 17: //Shaman
					{
						Plr->Gossip_SendPOI(1925.34f, -4181.89f, 7, 6, 0, "Thrall's Fortress");
						SendQuickMenu(2562);
					}
					break;

				case 18: //Rogue
					{
						Plr->Gossip_SendPOI(1773.39f, -4278.97f, 7, 6, 0, "Shadowswift Brotherhood");
						SendQuickMenu(2563);
					}
					break;

				case 19: //Warlock
					{
						Plr->Gossip_SendPOI(1849.57f, -4359.68f, 7, 6, 0, "Darkfire Enclave");
						SendQuickMenu(2564);
					}
					break;

				case 20: //Warrior
					{
						Plr->Gossip_SendPOI(1983.92f, -4794.2f, 7, 6, 0, "Hall of the Brave");
						SendQuickMenu(2565);
					}
					break;

				case 21: //Paladin
					{
						Plr->Gossip_SendPOI(1937.53f, -4141.0f, 7, 6, 0, "Thrall's Fortress");
						SendQuickMenu(2566);
					}
					break;

				case 22: //Alchemy
					{
						Plr->Gossip_SendPOI(1955.17f, -4475.79f, 7, 6, 0, "Yelmak's Alchemy and Potions");
						SendQuickMenu(2497);
					}
					break;

				case 23: //Blacksmithing
					{
						Plr->Gossip_SendPOI(2054.34f, -4831.85f, 7, 6, 0, "The Burning Anvil");
						SendQuickMenu(2499);
					}
					break;

				case 24: //Cooking
					{
						Plr->Gossip_SendPOI(1780.96f, -4481.31f, 7, 6, 0, "Borstan's Firepit");
						SendQuickMenu(2500);
					}
					break;

				case 25: //Enchanting
					{
						Plr->Gossip_SendPOI(1917.5f, -4434.95f, 7, 6, 0, "Godan's Runeworks");
						SendQuickMenu(2501);
					}
					break;

				case 26: //Engineering
					{
						Plr->Gossip_SendPOI(2038.45f, -4744.75f, 7, 6, 0, "Nogg's Machine Shop");
						SendQuickMenu(2653);
					}
					break;

				case 27: //First Aid
					{
						Plr->Gossip_SendPOI(1485.21f, -4160.91f, 7, 6, 0, "Survival of the Fittest");
						SendQuickMenu(2502);
					}
					break;

				case 28: //Fishing
					{
						Plr->Gossip_SendPOI(1994.15f, -4655.7f, 7, 6, 0, "Lumak's Fishing");
						SendQuickMenu(2503);
					}
					break;

				case 29: //Herbalism
					{
						Plr->Gossip_SendPOI(1898.61f, -4454.93f, 7, 6, 0, "Jandi's Arboretum");
						SendQuickMenu(2504);
					}
					break;

				case 30: //Leatherworking
					{
						Plr->Gossip_SendPOI(1852.82f, -4562.31f, 7, 6, 0, "Kodohide Leatherworkers");
						SendQuickMenu(2513);
					}
					break;

				case 31: //Mining
					{
						Plr->Gossip_SendPOI(2029.79f, -4704, 7, 6, 0, "Red Canyon Mining");
						SendQuickMenu(2515);
					}
					break;

				case 32: //Skinning
					{
						Plr->Gossip_SendPOI(1852.82f, -4562.31f, 7, 6, 0, "Kodohide Leatherworkers");
						SendQuickMenu(2516);
					}
					break;

				case 33: //Tailoring
					{
						Plr->Gossip_SendPOI(1802.66f, -4560.66f, 7, 6, 0, "Magar's Cloth Goods");
						SendQuickMenu(2518);
					}
					break;
			}
		}
};

class ThunderbluffGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3543, plr);
			Menu->AddItem(0, "The bank", 1);
			Menu->AddItem(0, "The wind rider master", 2);
			Menu->AddItem(0, "The guild master", 3);
			Menu->AddItem(0, "The inn", 4);
			Menu->AddItem(0, "The mailbox", 5);
			Menu->AddItem(0, "The auction house", 6);
			Menu->AddItem(0, "The weapon master", 7);
			Menu->AddItem(0, "The stable master", 8);
			Menu->AddItem(0, "The battlemaster", 9);
			Menu->AddItem(0, "A class trainer", 10);
			Menu->AddItem(0, "A profession trainer", 11);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // The bank
					SendQuickMenu(1292);
					Plr->Gossip_SendPOI(-1257.8f, 24.14f, 7, 6, 0, "Thunder Bluff Bank");
					break;

				case 2:     // The wind rider master
					SendQuickMenu(1293);
					Plr->Gossip_SendPOI(-1196.43f, 28.26f, 7, 6, 0, "Wind Rider Roost");
					break;

				case 3:     // The guild master
					SendQuickMenu(1291);
					Plr->Gossip_SendPOI(-1296.5f, 127.57f, 7, 6, 0, "Thunder Bluff Civic Information");
					break;

				case 4:     // The inn
					SendQuickMenu(3153);
					Plr->Gossip_SendPOI(-1296, 39.7f, 7, 6, 0, "Thunder Bluff Inn");
					break;

				case 5:     // The mailbox
					SendQuickMenu(3154);
					Plr->Gossip_SendPOI(-1263.59f, 44.36f, 7, 6, 0, "Thunder Bluff Mailbox");
					break;

				case 6:     // The auction house
					SendQuickMenu(3155);
					Plr->Gossip_SendPOI(-1205.51f, 105.74f, 7, 6, 0, "Thunder Bluff Auction house");
					break;

				case 7:     // The weapon master
					SendQuickMenu(4520);
					Plr->Gossip_SendPOI(-1282.31f, 89.56f, 7, 6, 0, "Ansekhwa");
					break;

				case 8:     // The stable master
					SendQuickMenu(5977);
					Plr->Gossip_SendPOI(-1270.19f, 48.84f, 7, 6, 0, "Bulrug");
					break;

				case 9:    // The battlemaster
					SendQuickMenu(7527);
					Plr->Gossip_SendPOI(-1391.22f, -81.33f, 7, 6, 0, "Battlemasters Thunder Bluff");
					break;

				case 10:    // A class trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3542, Plr);
						Menu->AddItem(0, "Druid"       , 12);
						Menu->AddItem(0, "Hunter"      , 13);
						Menu->AddItem(0, "Mage"        , 14);
						Menu->AddItem(0, "Priest"      , 15);
						Menu->AddItem(0, "Shaman"      , 16);
						Menu->AddItem(0, "Warrior"     , 17);
						Menu->SendTo(Plr);
					}
					break;

				case 11:    // A profession trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
						Menu->AddItem(0, "Alchemy"           , 18);
						Menu->AddItem(0, "Blacksmithing"     , 19);
						Menu->AddItem(0, "Cooking"           , 20);
						Menu->AddItem(0, "Enchanting"        , 21);
						Menu->AddItem(0, "First Aid"         , 22);
						Menu->AddItem(0, "Fishing"           , 23);
						Menu->AddItem(0, "Herbalism"         , 24);
						Menu->AddItem(0, "Leatherworking"    , 25);
						Menu->AddItem(0, "Mining"            , 26);
						Menu->AddItem(0, "Skinning"          , 27);
						Menu->AddItem(0, "Tailoring"         , 28);
						Menu->SendTo(Plr);
					}
					break;

					////////////////
					// Class trainer submenu
					////////

				case 12: //Druid
					{
						Plr->Gossip_SendPOI(-1054.47f, -285, 7, 6, 0, "Hall of Elders");
						SendQuickMenu(1294);
					}
					break;

				case 13: //Hunter
					{
						Plr->Gossip_SendPOI(-1416.32f, -114.28f, 7, 6, 0, "Hunter's Hall");
						SendQuickMenu(1295);
					}
					break;

				case 14: //Mage
					{
						Plr->Gossip_SendPOI(-1061.2f, 195.5f, 7, 6, 0, "Pools of Vision");
						SendQuickMenu(1296);
					}
					break;

				case 15: //Priest
					{
						Plr->Gossip_SendPOI(-1061.2f, 195.5f, 7, 6, 0, "Pools of Vision");
						SendQuickMenu(1297);
					}
					break;

				case 16: //Shaman
					{
						Plr->Gossip_SendPOI(-989.54f, 278.25f, 7, 6, 0, "Hall of Spirits");
						SendQuickMenu(1298);
					}
					break;

				case 17: //Warrior
					{
						Plr->Gossip_SendPOI(-1416.32f, -114.28f, 7, 6, 0, "Hunter's Hall");
						SendQuickMenu(1299);
					}
					break;

				case 18: //Alchemy
					{
						Plr->Gossip_SendPOI(-1085.56f, 27.29f, 7, 6, 0, "Bena's Alchemy");
						SendQuickMenu(1332);
					}
					break;

				case 19: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-1239.75f, 104.88f, 7, 6, 0, "Karn's Smithy");
						SendQuickMenu(1333);
					}
					break;

				case 20: //Cooking
					{
						Plr->Gossip_SendPOI(-1214.5f, -21.23f, 7, 6, 0, "Aska's Kitchen");
						SendQuickMenu(1334);
					}
					break;

				case 21: //Enchanting
					{
						Plr->Gossip_SendPOI(-1112.65f, 48.26f, 7, 6, 0, "Dawnstrider Enchanters");
						SendQuickMenu(1335);
					}
					break;

				case 22: //First Aid
					{
						Plr->Gossip_SendPOI(-996.58f, 200.5f, 7, 6, 0, "Spiritual Healing");
						SendQuickMenu(1336);
					}
					break;

				case 23: //Fishing
					{
						Plr->Gossip_SendPOI(-1169.35f, -68.87f, 7, 6, 0, "Mountaintop Bait & Tackle");
						SendQuickMenu(1337);
					}
					break;

				case 24: //Herbalism
					{
						Plr->Gossip_SendPOI(-1137.7f, -1.51f, 7, 6, 0, "Holistic Herbalism");
						SendQuickMenu(1338);
					}
					break;

				case 25: //Leatherworking
					{
						Plr->Gossip_SendPOI(-1156.22f, 66.86f, 7, 6, 0, "Thunder Bluff Armorers");
						SendQuickMenu(1339);
					}
					break;

				case 26: //Mining
					{
						Plr->Gossip_SendPOI(-1249.17f, 155, 7, 6, 0, "Stonehoof Geology");
						SendQuickMenu(1340);
					}
					break;

				case 27: //Skinning
					{
						Plr->Gossip_SendPOI(-1148.56f, 51.18f, 7, 6, 0, "Mooranta");
						SendQuickMenu(1343);
					}
					break;

				case 28: //Tailoring
					{
						Plr->Gossip_SendPOI(-1156.22f, 66.86f, 7, 6, 0, "Thunder Bluff Armorers");
						SendQuickMenu(1341);
					}
					break;
			}
		}
};

class BloodhoofGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3543, plr);
			Menu->AddItem(0, "The bank", 1);
			Menu->AddItem(0, "The wind rider master", 2);
			Menu->AddItem(0, "The inn", 3);
			Menu->AddItem(0, "The stable master", 4);
			Menu->AddItem(0, "A class trainer", 5);
			Menu->AddItem(0, "A profession trainer", 6);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // The bank
					SendQuickMenu(4051);
					break;

				case 2:     // The wind rider master
					SendQuickMenu(4052);
					break;

				case 3:     // The inn
					SendQuickMenu(4053);
					Plr->Gossip_SendPOI(-2361.38f, -349.19f, 7, 6, 0, "Bloodhoof Village Inn");
					break;

				case 4:     // The stable master
					SendQuickMenu(5976);
					Plr->Gossip_SendPOI(-2338.86f, -357.56f, 7, 6, 0, "Seikwa");
					break;

				case 5:     // A class trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4069, Plr);
						Menu->AddItem(0, "Druid"       , 7);
						Menu->AddItem(0, "Hunter"      , 8);
						Menu->AddItem(0, "Shaman"      , 9);
						Menu->AddItem(0, "Warrior"    , 10);
						Menu->SendTo(Plr);
					}
					break;

				case 6:     // A profession trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
						Menu->AddItem(0, "Alchemy"           , 11);
						Menu->AddItem(0, "Blacksmithing"     , 12);
						Menu->AddItem(0, "Cooking"           , 13);
						Menu->AddItem(0, "Enchanting"        , 14);
						Menu->AddItem(0, "First Aid"         , 15);
						Menu->AddItem(0, "Fishing"           , 16);
						Menu->AddItem(0, "Herbalism"         , 17);
						Menu->AddItem(0, "Leatherworking"    , 18);
						Menu->AddItem(0, "Mining"            , 19);
						Menu->AddItem(0, "Skinning"          , 20);
						Menu->AddItem(0, "Tailoring"         , 21);
						Menu->SendTo(Plr);
					}
					break;


					////////////////
					// Class trainer submenu
					////////

				case 7: //Druid
					{
						Plr->Gossip_SendPOI(-2312.15f, -443.69f, 7, 6, 0, "Gennia Runetotem");
						SendQuickMenu(4054);
					}
					break;

				case 8: //Hunter
					{
						Plr->Gossip_SendPOI(-2178.14f, -406.14f, 7, 6, 0, "Yaw Sharpmane");
						SendQuickMenu(4055);
					}
					break;

				case 9: //Shaman
					{
						Plr->Gossip_SendPOI(-2301.5f, -439.87f, 7, 6, 0, "Narm Skychaser");
						SendQuickMenu(4056);
					}
					break;

				case 10: //Warrior
					{
						Plr->Gossip_SendPOI(-2345.43f, -494.11f, 7, 6, 0, "Krang Stonehoof");
						SendQuickMenu(4057);
					}
					break;

				case 11: //Alchemy
					{
						SendQuickMenu(4058);
					}
					break;

				case 12: //Blacksmithing
					{
						SendQuickMenu(4059);
					}
					break;

				case 13: //Cooking
					{
						Plr->Gossip_SendPOI(-2263.34f, -287.91f, 7, 6, 0, "Pyall Silentstride");
						SendQuickMenu(4060);
					}
					break;

				case 14: //Enchanting
					{
						SendQuickMenu(4061);
					}
					break;

				case 15: //First Aid
					{
						Plr->Gossip_SendPOI(-2353.52f, -355.82f, 7, 6, 0, "Vira Younghoof");
						SendQuickMenu(4062);
					}
					break;

				case 16: //Fishing
					{
						Plr->Gossip_SendPOI(-2349.21f, -241.37f, 7, 6, 0, "Uthan Stillwater");
						SendQuickMenu(4063);
					}
					break;

				case 17: //Herbalism
					{
						SendQuickMenu(4064);
					}
					break;

				case 18: //Leatherworking
					{
						Plr->Gossip_SendPOI(-2257.12f, -288.63f, 7, 6, 0, "Chaw Stronghide");
						SendQuickMenu(4065);
					}
					break;

				case 19: //Mining
					{
						SendQuickMenu(4066);
					}
					break;

				case 20: //Skinning
					{
						Plr->Gossip_SendPOI(-2252.94f, -291.32f, 7, 6, 0, "Yonn Deepcut");
						SendQuickMenu(4067);
					}
					break;

				case 21: //Tailoring
					{
						SendQuickMenu(4068);
					}
					break;
			}
		}
};

class RazorHillGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4037, plr);
			Menu->AddItem(0, "The bank", 1);
			Menu->AddItem(0, "The wind rider master", 2);
			Menu->AddItem(0, "The inn", 3);
			Menu->AddItem(0, "The stable master", 4);
			Menu->AddItem(0, "A class trainer", 5);
			Menu->AddItem(0, "A profession trainer", 6);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // The bank
					SendQuickMenu(4032);
					break;

				case 2:     // The wind rider master
					SendQuickMenu(4033);
					break;

				case 3:     // The inn
					SendQuickMenu(4034);
					Plr->Gossip_SendPOI(338.7f, -4688.87f, 7, 6, 0, "Razor Hill Inn");
					break;

				case 4:     // The stable master
					SendQuickMenu(5973);
					Plr->Gossip_SendPOI(330.31f, -4710.66f, 7, 6, 0, "Shoja'my");
					break;

				case 5:     // A class trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4035, Plr);
						Menu->AddItem(0, "Hunter"       , 7);
						Menu->AddItem(0, "Mage"         , 8);
						Menu->AddItem(0, "Priest"       , 9);
						Menu->AddItem(0, "Rogue"       , 10);
						Menu->AddItem(0, "Shaman"      , 11);
						Menu->AddItem(0, "Warlock"     , 12);
						Menu->AddItem(0, "Warrior"     , 13);
						Menu->SendTo(Plr);
					}
					break;

				case 6:     // A profession trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 3541, Plr);
						Menu->AddItem(0, "Alchemy"           , 14);
						Menu->AddItem(0, "Blacksmithing"     , 15);
						Menu->AddItem(0, "Cooking"           , 16);
						Menu->AddItem(0, "Enchanting"        , 17);
						Menu->AddItem(0, "Engineering"       , 18);
						Menu->AddItem(0, "First Aid"         , 19);
						Menu->AddItem(0, "Fishing"           , 20);
						Menu->AddItem(0, "Herbalism"         , 21);
						Menu->AddItem(0, "Leatherworking"    , 22);
						Menu->AddItem(0, "Mining"            , 23);
						Menu->AddItem(0, "Skinning"          , 24);
						Menu->AddItem(0, "Tailoring"         , 25);
						Menu->SendTo(Plr);
					}
					break;


					////////////////
					// Class trainer submenu
					////////

				case 7: //Hunter
					{
						Plr->Gossip_SendPOI(276, -4706.72f, 7, 6, 0, "Thotar");
						SendQuickMenu(4013);
					}
					break;

				case 8: //Mage
					{
						Plr->Gossip_SendPOI(-839.33f, -4935.6f, 7, 6, 0, "Un'Thuwa");
						SendQuickMenu(4014);
					}
					break;

				case 9: //Priest
					{
						Plr->Gossip_SendPOI(296.22f, -4828.1f, 7, 6, 0, "Tai'jin");
						SendQuickMenu(4015);
					}
					break;

				case 10: //Rogue
					{
						Plr->Gossip_SendPOI(265.76f, -4709, 7, 6, 0, "Kaplak");
						SendQuickMenu(4016);
					}
					break;

				case 11: //Shaman
					{
						Plr->Gossip_SendPOI(307.79f, -4836.97f, 7, 6, 0, "Swart");
						SendQuickMenu(4017);
					}
					break;

				case 12: //Warlock
					{
						Plr->Gossip_SendPOI(355.88f, -4836.45f, 7, 6, 0, "Dhugru Gorelust");
						SendQuickMenu(4018);
					}
					break;

				case 13: //Warrior
					{
						Plr->Gossip_SendPOI(312.3f, -4824.66f, 7, 6, 0, "Tarshaw Jaggedscar");
						SendQuickMenu(4019);
					}
					break;

				case 14: //Alchemy
					{
						Plr->Gossip_SendPOI(-800.25f, -4894.33f, 7, 6, 0, "Miao'zan");
						SendQuickMenu(4020);
					}
					break;

				case 15: //Blacksmithing
					{
						Plr->Gossip_SendPOI(373.24f, -4716.45f, 7, 6, 0, "Dwukk");
						SendQuickMenu(4021);
					}
					break;

				case 16: //Cooking
					{
						SendQuickMenu(4022);
					}
					break;

				case 17: //Enchanting
					{
						SendQuickMenu(4023);
					}
					break;

				case 18: //Engineering
					{
						Plr->Gossip_SendPOI(368.95f, -4723.95f, 7, 6, 0, "Mukdrak");
						SendQuickMenu(4024);
					}
					break;

				case 19: //First Aid
					{
						Plr->Gossip_SendPOI(327.17f, -4825.62f, 7, 6, 0, "Rawrk");
						SendQuickMenu(4025);
					}
					break;

				case 20: //Fishing
					{
						Plr->Gossip_SendPOI(-1065.48f, -4777.43f, 7, 6, 0, "Lau'Tiki");
						SendQuickMenu(4026);
					}
					break;

				case 21: //Herbalism
					{
						Plr->Gossip_SendPOI(-836.25f, -4896.89f, 7, 6, 0, "Mishiki");
						SendQuickMenu(4027);
					}
					break;

				case 22: //Leatherworking
					{
						SendQuickMenu(4028);
					}
					break;

				case 23: //Mining
					{
						Plr->Gossip_SendPOI(366.94f, -4705, 7, 6, 0, "Krunn");
						SendQuickMenu(4029);
					}
					break;

				case 24: //Skinning
					{
						Plr->Gossip_SendPOI(-2252.94f, -291.32f, 7, 6, 0, "Yonn Deepcut");
						SendQuickMenu(4030);
					}
					break;

				case 25: //Tailoring
					{
						SendQuickMenu(4031);
					}
					break;
			}
		}
};

class BrillGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);
			Menu->AddItem(0, "The bank", 1);
			Menu->AddItem(0, "The bat handler", 2);
			Menu->AddItem(0, "The inn", 3);
			Menu->AddItem(0, "The stable master", 4);
			Menu->AddItem(0, "A class trainer", 5);
			Menu->AddItem(0, "A profession trainer", 6);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     // The bank
					SendQuickMenu(4074);
					break;

				case 2:     // The bat handler
					SendQuickMenu(4075);
					break;

				case 3:     // The inn
					SendQuickMenu(4076);
					Plr->Gossip_SendPOI(2246.68f, 241.89f, 7, 6, 0, "Gallows` End Tavern");
					break;

				case 4:     // The stable master
					SendQuickMenu(5978);
					Plr->Gossip_SendPOI(2267.66f, 319.32f, 7, 6, 0, "Morganus");
					break;

				case 5:     // A class trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4292, Plr);
						Menu->AddItem(0, "Mage"         , 7);
						Menu->AddItem(0, "Paladin"      , 8);
						Menu->AddItem(0, "Priest"       , 9);
						Menu->AddItem(0, "Rogue"       , 10);
						Menu->AddItem(0, "Warlock"     , 11);
						Menu->AddItem(0, "Warrior"     , 12);
						Menu->SendTo(Plr);
					}
					break;

				case 6:     // A profession trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4300, Plr);
						Menu->AddItem(0, "Alchemy"           , 13);
						Menu->AddItem(0, "Blacksmithing"     , 14);
						Menu->AddItem(0, "Cooking"           , 15);
						Menu->AddItem(0, "Enchanting"        , 16);
						Menu->AddItem(0, "Engineering"       , 17);
						Menu->AddItem(0, "First Aid"         , 18);
						Menu->AddItem(0, "Fishing"           , 19);
						Menu->AddItem(0, "Herbalism"         , 20);
						Menu->AddItem(0, "Leatherworking"    , 21);
						Menu->AddItem(0, "Mining"            , 22);
						Menu->AddItem(0, "Skinning"          , 23);
						Menu->AddItem(0, "Tailoring"         , 24);
						Menu->SendTo(Plr);
					}
					break;


					////////////////
					// Class trainer submenu
					////////

				case 7: //Mage
					{
						Plr->Gossip_SendPOI(2259.18f, 240.93f, 7, 6, 0, "Cain Firesong");
						SendQuickMenu(4077);
					}
					break;

				case 8: //Paladin
					{
						SendQuickMenu(0); // Need to add correct text
					}
					break;

				case 9: //Priest
					{
						Plr->Gossip_SendPOI(2259.18f, 240.93f, 7, 6, 0, "Dark Cleric Beryl");
						SendQuickMenu(4078);
					}
					break;

				case 10: //Rogue
					{
						Plr->Gossip_SendPOI(2259.18f, 240.93f, 7, 6, 0, "Marion Call");
						SendQuickMenu(4079);
					}
					break;

				case 11: //Warlock
					{
						Plr->Gossip_SendPOI(2259.18f, 240.93f, 7, 6, 0, "Rupert Boch");
						SendQuickMenu(4080);
					}
					break;

				case 12: //Warrior
					{
						Plr->Gossip_SendPOI(2256.48f, 240.32f, 7, 6, 0, "Austil de Mon");
						SendQuickMenu(4081);
					}
					break;

				case 13: //Alchemy
					{
						Plr->Gossip_SendPOI(2263.25f, 344.23f, 7, 6, 0, "Carolai Anise");
						SendQuickMenu(4082);
					}
					break;

				case 14: //Blacksmithing
					{
						SendQuickMenu(4083);
					}
					break;

				case 15: //Cooking
					{
						SendQuickMenu(4084);
					}
					break;

				case 16: //Enchanting
					{
						Plr->Gossip_SendPOI(2250.35f, 249.12f, 7, 6, 0, "Vance Undergloom");
						SendQuickMenu(4085);
					}
					break;

				case 17: //Engineering
					{
						SendQuickMenu(4086);
					}
					break;

				case 18: //First Aid
					{
						Plr->Gossip_SendPOI(2246.68f, 241.89f, 7, 6, 0, "Nurse Neela");
						SendQuickMenu(4087);
					}
					break;

				case 19: //Fishing
					{
						Plr->Gossip_SendPOI(2292.37f, -10.72f, 7, 6, 0, "Clyde Kellen");
						SendQuickMenu(4088);
					}
					break;

				case 20: //Herbalism
					{
						Plr->Gossip_SendPOI(2268.21f, 331.69f, 7, 6, 0, "Faruza");
						SendQuickMenu(4089);
					}
					break;

				case 21: //Leatherworking
					{
						Plr->Gossip_SendPOI(2027, 78.72f, 7, 6, 0, "Shelene Rhobart");
						SendQuickMenu(4090);
					}
					break;

				case 22: //Mining
					{
						SendQuickMenu(4091);
					}
					break;

				case 23: //Skinning
					{
						Plr->Gossip_SendPOI(2027, 78.72f, 7, 6, 0, "Rand Rhobart");
						SendQuickMenu(4092);
					}
					break;

				case 24: //Tailoring
					{
						Plr->Gossip_SendPOI(2160.45f, 659.93f, 7, 6, 0, "Bowen Brisboise");
						SendQuickMenu(4093);
					}
					break;
			}
		}
};

class KharanosGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4287, plr);
			Menu->AddItem(0, "Bank", 1);
			Menu->AddItem(0, "Gryphon Master", 2);
			Menu->AddItem(0, "Guild Master", 3);
			Menu->AddItem(0, "The Inn", 4);
			Menu->AddItem(0, "Stable Master", 5);
			Menu->AddItem(0, "Class Trainer", 6);
			Menu->AddItem(0, "Profession Trainer", 7);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     //Bank
					SendQuickMenu(4288);
					break;

				case 2:     //Gryphon Master
					SendQuickMenu(4289);
					break;

				case 3:     //Guild Master
					SendQuickMenu(4290);
					break;

				case 4:     //The Inn
					SendQuickMenu(4291);
					Plr->Gossip_SendPOI(-5582.66f, -525.89f, 7, 6, 0, "Thunderbrew Distillery");
					break;

				case 5:     //Stable Master
					SendQuickMenu(5985);
					Plr->Gossip_SendPOI(-5604, -509.58f, 7, 6, 0, "Shelby Stoneflint");
					break;

				case 6:     //Class Trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4292, Plr);
						Menu->AddItem(0, "Hunter"       , 8);
						Menu->AddItem(0, "Mage"         , 9);
						Menu->AddItem(0, "Paladin"      , 10);
						Menu->AddItem(0, "Priest"      , 11);
						Menu->AddItem(0, "Rogue"       , 12);
						Menu->AddItem(0, "Warlock"     , 13);
						Menu->AddItem(0, "Warrior"     , 14);
						Menu->SendTo(Plr);
					}
					break;

				case 7:     // Profession Trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4300, Plr);
						Menu->AddItem(0, "Alchemy"           , 15);
						Menu->AddItem(0, "Blacksmithing"     , 16);
						Menu->AddItem(0, "Cooking"           , 17);
						Menu->AddItem(0, "Enchanting"        , 18);
						Menu->AddItem(0, "Engineering"       , 19);
						Menu->AddItem(0, "First Aid"         , 20);
						Menu->AddItem(0, "Fishing"           , 21);
						Menu->AddItem(0, "Herbalism"         , 22);
						Menu->AddItem(0, "Inscription"		  , 23);
						Menu->AddItem(0, "Leatherworking"    , 24);
						Menu->AddItem(0, "Mining"            , 25);
						Menu->AddItem(0, "Skinning"          , 26);
						Menu->AddItem(0, "Tailoring"         , 27);
						Menu->SendTo(Plr);
					}
					break;


					////////////////
					// Class trainer submenu
					////////

				case 8: //Hunter
					{
						Plr->Gossip_SendPOI(-5618.29f, -454.25f, 7, 6, 0, "Grif Wildheart");
						SendQuickMenu(4293);
					}
					break;

				case 9: //Mage
					{
						Plr->Gossip_SendPOI(-5585.6f, -539.99f, 7, 6, 0, "Magis Sparkmantle");
						SendQuickMenu(4294);
					}
					break;

				case 10: //Paladin
					{
						Plr->Gossip_SendPOI(-5585.6f, -539.99f, 7, 6, 0, "Azar Stronghammer");
						SendQuickMenu(4295);
					}
					break;

				case 11: //Priest
					{
						Plr->Gossip_SendPOI(-5591.74f, -525.61f, 7, 6, 0, "Maxan Anvol");
						SendQuickMenu(4296);
					}
					break;

				case 12: //Rogue
					{
						Plr->Gossip_SendPOI(-5602.75f, -542.4f, 7, 6, 0, "Hogral Bakkan");
						SendQuickMenu(4297);
					}
					break;

				case 13: //Warlock
					{
						Plr->Gossip_SendPOI(-5641.97f, -523.76f, 7, 6, 0, "Gimrizz Shadowcog");
						SendQuickMenu(4298);
					}
					break;

				case 14: //Warrior
					{
						Plr->Gossip_SendPOI(-5604.79f, -529.38f, 7, 6, 0, "Granis Swiftaxe");
						SendQuickMenu(4299);
					}
					break;

				case 15: //Alchemy
					{
						SendQuickMenu(4301);
					}
					break;

				case 16: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-5584.72f, -428.41f, 7, 6, 0, "Tognus Flintfire");
						SendQuickMenu(4302);
					}
					break;

				case 17: //Cooking
					{
						Plr->Gossip_SendPOI(-5596.85f, -541.43f, 7, 6, 0, "Gremlock Pilsnor");
						SendQuickMenu(4303);
					}
					break;

				case 18: //Enchanting
					{
						SendQuickMenu(4304);
					}
					break;

				case 19: //Engineering
					{
						SendQuickMenu(4305);
					}
					break;

				case 20: //First Aid
					{
						Plr->Gossip_SendPOI(-5603.67f, -523.57f, 7, 6, 0, "Thamner Pol");
						SendQuickMenu(4306);
					}
					break;

				case 21: //Fishing
					{
						Plr->Gossip_SendPOI(-5202.39f, -51.36f, 7, 6, 0, "Paxton Ganter");
						SendQuickMenu(4307);
					}
					break;

				case 22: //Herbalism
					{
						SendQuickMenu(4308);
					}
					break;

				case 23: //Inscription
					{
						Plr->Gossip_SendPOI(-4801.72f, -1189.41f, 7, 6, 0, "Ironforge Inscription");
						SendQuickMenu(13884);
					}
					break;

				case 24: //Leatherworking
					{
						SendQuickMenu(4310);
					}
					break;

				case 25: //Mining
					{
						Plr->Gossip_SendPOI(-5531, -666.53f, 7, 6, 0, "Yarr Hamerstone");
						SendQuickMenu(4311);
					}
					break;

				case 26: //Skinning
					{
						SendQuickMenu(4312);
					}
					break;

				case 27: //Tailoring
					{
						SendQuickMenu(4313);
					}
					break;
			}
		}
};

class FalconwingGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, plr);
			Menu->AddItem(0, "Bat Handler", 1);
			Menu->AddItem(0, "Guild Master", 2);
			Menu->AddItem(0, "The Inn", 3);
			Menu->AddItem(0, "Stable Master", 4);
			Menu->AddItem(0, "Class Trainer", 5);
			Menu->AddItem(0, "Profession Trainer", 6);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     //Bat Handler
					SendQuickMenu(2593);
					Plr->Gossip_SendPOI(9376.4f, -7164.92f, 7, 6, 0, "Silvermoon City, Flight Master");
					break;

				case 2:     //Guild Master
					SendQuickMenu(2593);
					break;

				case 3:     //The Inn
					SendQuickMenu(2593);
					Plr->Gossip_SendPOI(9476.916f, -6859.2f, 7, 6, 0, "Falconwing Square, Innkeeper");
					break;

				case 4:     //Stable Master
					SendQuickMenu(2593);
					Plr->Gossip_SendPOI(9487.6f, -6830.59f, 7, 6, 0, "Falconwing Square, Stable Master");
					break;

				case 5:     //Class Trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 4292, Plr);
						Menu->AddItem(0, "Druid"        , 7);
						Menu->AddItem(0, "Hunter"       , 8);
						Menu->AddItem(0, "Mage"         , 9);
						Menu->AddItem(0, "Paladin"     , 10);
						Menu->AddItem(0, "Priest"      , 11);
						Menu->AddItem(0, "Rogue"       , 12);
						Menu->AddItem(0, "Warlock"     , 13);
						Menu->SendTo(Plr);
					}
					break;

				case 6:     // Profession Trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 2593, Plr);
						Menu->AddItem(0, "Alchemy"           , 14);
						Menu->AddItem(0, "Blacksmithing"     , 15);
						Menu->AddItem(0, "Cooking"           , 16);
						Menu->AddItem(0, "Enchanting"        , 17);
						Menu->AddItem(0, "Engineering"       , 18);
						Menu->AddItem(0, "First Aid"         , 19);
						Menu->AddItem(0, "Fishing"           , 20);
						Menu->AddItem(0, "Herbalism"         , 21);
						Menu->AddItem(0, "Jewelcrafting"     , 22);
						Menu->AddItem(0, "Leatherworking"    , 23);
						Menu->AddItem(0, "Mining"            , 24);
						Menu->AddItem(0, "Skinning"          , 25);
						Menu->AddItem(0, "Tailoring"         , 26);
						Menu->SendTo(Plr);
					}
					break;


					////////////////
					// Class trainer submenu
					////////

				case 7: //Druid
					{
						SendQuickMenu(2593);
					}
					break;

				case 8: //Hunter
					{
						Plr->Gossip_SendPOI(9529.2f, -6864.58f, 7, 6, 0, "Falconwing Square, Hunter Trainer");
						SendQuickMenu(2593);
					}
					break;

				case 9: //Mage
					{
						Plr->Gossip_SendPOI(9462.24f, -6853.45f, 7, 6, 0, "Falconwing Square, Mage Trainer");
						SendQuickMenu(2593);
					}
					break;

				case 10: //Paladin <-- Needs to change flag to other sign (don't know how to describe it)
					{
						Plr->Gossip_SendPOI(9516.05f, -6870.96f, 7, 6, 0, "Falconwing Square, Paladin Trainer");
						SendQuickMenu(2593);
					}
					break;

				case 11: //Priest
					{
						Plr->Gossip_SendPOI(9466.62f, -6844.23f, 7, 6, 0, "Falconwing Square, Priest Trainer");
						SendQuickMenu(2593);
					}
					break;

				case 12: //Rogue
					{
						Plr->Gossip_SendPOI(9534.15f, -6876.0f, 7, 6, 0, "Falconwing Square, Rogue Trainer");
						SendQuickMenu(2593);
					}
					break;

				case 13: //Warlock
					{
						Plr->Gossip_SendPOI(9467.63f, -6862.82f, 7, 6, 0, "Falconwing Square, Warlock Trainer");
						SendQuickMenu(2593);
					}
					break;

				case 14: //Alchemy
					{
						Plr->Gossip_SendPOI(8661.36f, -6367.0f, 7, 6, 0, "Saltheril's Haven, Alchemist");
						SendQuickMenu(2593);
					}
					break;

				case 15: //Blacksmithing
					{
						Plr->Gossip_SendPOI(8986.43f, -7419.07f, 7, 6, 0, "Farstrider Retreat, Blacksmith");
						SendQuickMenu(2593);
					}
					break;

				case 16: //Cooking
					{
						Plr->Gossip_SendPOI(9494.86f, -6879.45f, 7, 6, 0, "Falconwing Square, Cook");
						SendQuickMenu(2593);
					}
					break;

				case 17: //Enchanting
					{
						Plr->Gossip_SendPOI(8657.6f, -6366.7f, 7, 6, 0, "Saltheril's Haven, Enchanter");
						SendQuickMenu(2593);
					}
					break;

				case 18: //Engineering
					{
						SendQuickMenu(2593);
					}
					break;

				case 19: //First Aid
					{
						Plr->Gossip_SendPOI(9479.53f, -6880.07f, 7, 6, 0, "Falconwing Square, First Aid");
						SendQuickMenu(2593);
					}
					break;

				case 20: //Fishing
					{
						SendQuickMenu(2593);
					}
					break;

				case 21: //Herbalism
					{
						Plr->Gossip_SendPOI(8678.92f, -6329.09f, 7, 6, 0, "Saltheril's Haven, Herbalist");
						SendQuickMenu(2593);
					}
					break;

				case 22: //Jewelcrafting
					{
						Plr->Gossip_SendPOI(9484.79f, -6876.58f, 7, 6, 0, "Falconwing Square, Jewelcrafter");
						SendQuickMenu(2593);
					}
					break;

				case 23: //Leatherworking
					{
						Plr->Gossip_SendPOI(9363.75f, -7130.75f, 7, 6, 0, "Eversong Woods, Leatherworker");
						SendQuickMenu(2593);
					}
					break;

				case 24: //Mining
					{
						SendQuickMenu(2593);
					}
					break;

				case 25: //Skinning
					{
						Plr->Gossip_SendPOI(9362.89f, -7134.58f, 7, 6, 0, "Eversong Woods, Skinner");
						SendQuickMenu(2593);
					}
					break;

				case 26: //Tailoring
					{
						Plr->Gossip_SendPOI(8680.36f, -6327.51f, 7, 6, 0, "Saltheril's Haven, Tailor");
						SendQuickMenu(2593);
					}
					break;
			}
		}
};

class AzureWatchGuard : public GossipScript
{
	public:
		void GossipHello(Object* pObject, Player* plr)
		{
			GossipMenu* Menu;
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10066, plr);
			Menu->AddItem(0, "Bank"					, 1);
			Menu->AddItem(0, "Hippogryph Master"	, 2);
			Menu->AddItem(0, "Guild Master"			, 3);
			Menu->AddItem(0, "Inn"					, 4);
			Menu->AddItem(0, "Stable"				, 5);
			Menu->AddItem(0, "Class Trainer"		, 6);
			Menu->AddItem(0, "Profession Trainer"	, 7);

			Menu->SendTo(plr);
		}

		void GossipSelectOption(Object* pObject, Player* Plr, uint32 Id, uint32 IntId, const char* Code)
		{
			GossipMenu* Menu;
			switch(IntId)
			{
				case 0:     // Return to start
					GossipHello(pObject, Plr);
					break;

					//////////////////////
					// Main menu handlers
					/////

				case 1:     //Bank
					SendQuickMenu(10067);
					break;

				case 2:     //Hippogryph Master
					SendQuickMenu(10071);
					break;

				case 3:     //Guild Master
					SendQuickMenu(10073);
					break;

				case 4:     //Inn
					SendQuickMenu(10074);
					Plr->Gossip_SendPOI(-4127.81f, -12467.7f, 7, 6, 0, "Azure Watch, Innkeeper");
					break;

				case 5:     //Stable Master
					SendQuickMenu(10075);
					Plr->Gossip_SendPOI(-4146.42f, -12492.7f, 7, 6, 0, "Azure Watch, Stable Master");
					break;

				case 6:     //Class Trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10076, Plr);
						Menu->AddItem(0, "Druid"       , 8);
						Menu->AddItem(0, "Hunter"      , 9);
						Menu->AddItem(0, "Mage"		, 10);
						Menu->AddItem(0, "Paladin"     , 11);
						Menu->AddItem(0, "Priest"      , 12);
						Menu->AddItem(0, "Shaman"      , 13);
						Menu->AddItem(0, "Warrior"     , 14);
						Menu->SendTo(Plr);
					}
					break;

				case 7:     //Profession Trainer
					{
						objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 10087, Plr);
						Menu->AddItem(0, "Alchemy"           , 15);
						Menu->AddItem(0, "Blacksmithing"     , 16);
						Menu->AddItem(0, "Cooking"           , 17);
						Menu->AddItem(0, "Enchanting"        , 18);
						Menu->AddItem(0, "Engineering"       , 19);
						Menu->AddItem(0, "First Aid"         , 20);
						Menu->AddItem(0, "Fishing"           , 21);
						Menu->AddItem(0, "Herbalism"         , 22);
						Menu->AddItem(0, "Inscription"       , 23);
						Menu->AddItem(0, "Jewelcrafting"     , 24);
						Menu->AddItem(0, "Leatherworking"    , 25);
						Menu->AddItem(0, "Mining"            , 26);
						Menu->AddItem(0, "Skinning"          , 27);
						Menu->AddItem(0, "Tailoring"         , 28);
						Menu->SendTo(Plr);
					}
					break;


					////////////////
					// Class trainer submenu
					////////

				case 8: //Druid
					{
						SendQuickMenu(10077);
					}
					break;

				case 9: //Hunter
					{
						Plr->Gossip_SendPOI(-4203.65f, -12467.7f, 7, 6, 0, "Azure Watch, Hunter Trainer");
						SendQuickMenu(10078);
					}
					break;

				case 10: //Mage
					{
						Plr->Gossip_SendPOI(-4149.62f, -12530.1f, 7, 6, 0, "Azure Watch, Mage Trainer");
						SendQuickMenu(10081);
					}
					break;

				case 11: //Paladin
					{
						Plr->Gossip_SendPOI(-4138.98f, -12468.5f, 7, 6, 0, "Azure Watch, Paladin Trainer");
						SendQuickMenu(10083);
					}
					break;

				case 12: //Priest
					{
						Plr->Gossip_SendPOI(-4131.66f, -12478.6f, 7, 6, 0, "Azure Watch, Priest Trainer");
						SendQuickMenu(10084);
					}
					break;

				case 13: //Shaman
					{
						Plr->Gossip_SendPOI(-4162.33f, -12456.1f, 7, 6, 0, "Azure Watch, Shaman Trainer");
						SendQuickMenu(10085);
					}
					break;

				case 14: //Warrior
					{
						Plr->Gossip_SendPOI(-4165.05f, -12536.4f, 7, 6, 0, "Azure Watch, Warrior Trainer");
						SendQuickMenu(10086);
					}
					break;

				case 15: //Alchemy
					{
						Plr->Gossip_SendPOI(-4191.15f, -12470, 7, 6, 0, "Azure Watch, Alchemist");
						SendQuickMenu(10088);
					}
					break;

				case 16: //Blacksmithing
					{
						Plr->Gossip_SendPOI(-4726.29f, -12387.0f, 7, 6, 0, "Odesyus' Landing, Blacksmith");
						SendQuickMenu(10089);
					}
					break;

				case 17: //Cooking
					{
						Plr->Gossip_SendPOI(-4708.59f, -12400.3f, 7, 6, 0, "Odesyus' Landing, Cook");
						SendQuickMenu(10090);
					}
					break;

				case 18: //Enchanting
					{
						SendQuickMenu(10091);
					}
					break;

				case 19: //Engineering
					{
						Plr->Gossip_SendPOI(-4157.57f, -12470.2f, 7, 6, 0, "Azure Watch, Engineering Trainer");
						SendQuickMenu(10092);
					}
					break;

				case 20: //First Aid
					{
						Plr->Gossip_SendPOI(-4199.1f, -12469.9f, 7, 6, 0, "Azure Watch, First Aid Trainer");
						SendQuickMenu(10093);
					}
					break;

				case 21: //Fishing
					{
						Plr->Gossip_SendPOI(-4266.34f, -12985.4f, 7, 6, 0, "Ammen Ford, Fisherwoman");
						SendQuickMenu(10094);
					}
					break;

				case 22: //Herbalism
					{
						Plr->Gossip_SendPOI(-4189.43f, -12459.4f, 7, 6, 0, "Azure Watch, Herbalist");
						SendQuickMenu(10095);
					}
					break;

				case 23: //Inscription
					{
						Plr->Gossip_SendPOI(-3889.3f, -11495, 7, 6, 0, "Exodar, Inscription");
						SendQuickMenu(13887);
					}
					break;

				case 24: //Jewelcrafting
					{
						SendQuickMenu(10100);
					}
					break;

				case 25: //Leatherworking
					{
						Plr->Gossip_SendPOI(-3442.68f, -12322.2f, 7, 6, 0, "Stillpine Hold, Leatherworker");
						SendQuickMenu(10096);
					}
					break;

				case 26: //Mining
					{
						Plr->Gossip_SendPOI(-4179.89f, -12493.1f, 7, 6, 0, "Azure Watch, Mining Trainer");
						SendQuickMenu(10097);
					}
					break;

				case 27: //Skinning
					{
						Plr->Gossip_SendPOI(-3431.17f, -12316.5f, 7, 6, 0, "Stillpine Hold, Skinner");
						SendQuickMenu(10098);
					}
					break;

				case 28: //Tailoring
					{
						Plr->Gossip_SendPOI(-4711.54f, -12386.7f, 7, 6, 0, "Odesyus' Landing, Tailor");
						SendQuickMenu(10099);
					}
					break;
			}
		}
};

void SetupGuardGossip(ScriptMgr* mgr)
{
	GossipScript* teldra = new TeldrassilGuard();
	GossipScript* blood = new BloodhoofGuard();
	GossipScript* razor = new RazorHillGuard();
	GossipScript* brill = new BrillGuard();
	GossipScript* khar = new KharanosGuard();
	GossipScript* falcon = new FalconwingGuard();
	GossipScript* azure = new AzureWatchGuard();
	GossipScript* silver = new SilvermoonGuard();
	GossipScript* exodar = new ExodarGuard();
	GossipScript* ogri = new OrgrimmarGuard();
	GossipScript* thun = new ThunderbluffGuard();

	/* Guard List */
	mgr->register_gossip_script(3571,  teldra);			// Teldrassil Sentinel
	mgr->register_gossip_script(16222, silver);			// Silvermoon City Guardian
	mgr->register_gossip_script(16733, exodar);	        // Exodar Peacekeeper
	mgr->register_gossip_script(20674, exodar);	        // Shield of Velen
	mgr->register_gossip_script(3296, ogri);	        // Orgrimmar Grunt
	mgr->register_gossip_script(3084, thun);			// Bluffwatcher
	mgr->register_gossip_script(3222, blood);			// Brave Wildrunner
	mgr->register_gossip_script(3224, blood);			// Brave Cloudmane
	mgr->register_gossip_script(3220, blood);			// Brave Darksky
	mgr->register_gossip_script(3219, blood);			// Brave Leaping Deer
	mgr->register_gossip_script(3217, blood);			// Brave Dawneagle
	mgr->register_gossip_script(3215, blood);			// Brave Strongbash
	mgr->register_gossip_script(3218, blood);			// Brave Swiftwind
	mgr->register_gossip_script(3221, blood);			// Brave Rockhorn
	mgr->register_gossip_script(3223, blood);			// Brave Rainchaser
	mgr->register_gossip_script(3212, blood);			// Brave Ironhorn
	mgr->register_gossip_script(5953, razor);			// Razor Hill Grunt
	mgr->register_gossip_script(5725, brill);			// Deathguard Lundmark
	mgr->register_gossip_script(1738, brill);			// Deathguard Terrence
	mgr->register_gossip_script(1652, brill);			// Deathguard Burgess
	mgr->register_gossip_script(1746, brill);			// Deathguard Cyrus
	mgr->register_gossip_script(1745, brill);			// Deathguard Morris
	mgr->register_gossip_script(1743, brill);			// Deathguard Lawrence
	mgr->register_gossip_script(1744, brill);			// Deathguard Mort
	mgr->register_gossip_script(1496, brill);			// Deathguard Dillinger
	mgr->register_gossip_script(1742, brill);			// Deathguard Bartholomew
	mgr->register_gossip_script(727,  khar);			// Ironforge Mountaineer
	mgr->register_gossip_script(16221, falcon);			// Silvermoon Guardian
	mgr->register_gossip_script(18038, azure);			// Azuremyst Peacekeeper
}

// To Bloodhoof Guards - I don't know if those are all guards with dialog menu,
// but they were all I could find. Same to Deathguards.

// To do:
//	- Add (eventually) missing guards which should use one of those guard menus.
//	- Check all scripts + add guard text to DB and connect them with correct scripts.
