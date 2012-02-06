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

// Event of Hallowen control
//#define EVENT_HALLOWEEN		// Decomment this for enable the event on Innkeepers

#define SPELL_TRICK_OR_TREATED  24755
#define SPELL_TREAT             24715
#define	INNKEEPERASK			83
#define	TRICKORTREAT			84
// -------------------------

class InnkeeperGossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* Plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);

// Halloween control
		tm * ct = localtime(&UNIXTIME);
		if( ct->tm_mon == 9 && ( ct->tm_mday > 17 && ct->tm_mday <= 31 ) )
		{
			if(!Plr->HasAura(SPELL_TRICK_OR_TREATED))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Trick or Treat!", 4);
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, Plr->GetSession()->LocalizedWorldSrv(TRICKORTREAT), 4);
		}
// End of Halloween control

			if(TO_CREATURE(pObject)->isVendor())
				menu.AddItem(Arcemu::Gossip::ICON_VENDOR, Plr->GetSession()->LocalizedWorldSrv(Arcemu::Gossip::VENDOR), 1);

			menu.AddItem(Arcemu::Gossip::ICON_CHAT, Plr->GetSession()->LocalizedWorldSrv(Arcemu::Gossip::INNKEEPER), 2);
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, Plr->GetSession()->LocalizedWorldSrv(INNKEEPERASK), 3);

			sQuestMgr.FillQuestMenu(TO_CREATURE(pObject), Plr, menu);

			menu.Send(Plr);
		}
		
		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* Code)
		{
			Creature* pCreature = (pObject->IsCreature()) ? (TO_CREATURE(pObject)) : NULL;
			if(pCreature == NULL)
				return;

			switch(Id)
			{
				case 1:	Plr->GetSession()->SendInventoryList(pCreature); break;// VENDOR
				case 2:	Plr->GetSession()->SendInnkeeperBind(pCreature); break;// BINDER
				case 3:     // WHAT CAN I DO ?
					// Prepare second menu
					Arcemu::Gossip::Menu::SendQuickMenu(pCreature->GetGUID(), 1853, Plr, 2, Arcemu::Gossip::ICON_CHAT, Plr->GetSession()->LocalizedWorldSrv(Arcemu::Gossip::INNKEEPER));
					break;
				case 4:     // EVENT OF HALLOWEEN
					{
						if(!Plr->HasAura(SPELL_TRICK_OR_TREATED))
						{
							pCreature->CastSpell(Plr, SPELL_TRICK_OR_TREATED, true);

							// either trick or treat, 50% chance
							if(rand() % 2)
								Plr->CastSpell(Plr, SPELL_TREAT, true);
							else
							{
								int32 trickspell = 0;
								switch(rand()%6)
								{
									case 0:	trickspell = 24753; break;	// cannot cast, random 30sec
									case 1:	trickspell = 24713; break;	//lepper gnome costume
									case 2:	trickspell = Plr->getGender() == 0 ? 24735 : 24736; break;	//ghost costume
									case 3:	trickspell = Plr->getGender() == 0 ? 24711 : 24710; break;	//ninja costume
									case 4:	trickspell = Plr->getGender() == 0 ? 24708 : 24709; break;	//pirate costume
									case 5:	trickspell = 24723;	break;	// skeleton costume	
								}
								pCreature->CastSpell(Plr, trickspell, true);
							}
						}
						Arcemu::Gossip::Menu::Complete(Plr);
					}break;
			}
		}

		void Destroy() { delete this; }
};

void SetupInnkeepers(ScriptMgr* mgr)
{
	Arcemu::Gossip::Script* gs = new InnkeeperGossip();
	/* Innkeeper List */
	mgr->register_creature_gossip(26596, gs);     //"Charlie" Northtop
	mgr->register_creature_gossip(24208, gs);     //"Little" Logok
	mgr->register_creature_gossip(32418, gs);     //Abohba
	mgr->register_creature_gossip(32411, gs);     //Afsaneh Asrar
	mgr->register_creature_gossip(26680, gs);     //Aiyan Coldwind
	mgr->register_creature_gossip(29532, gs);     //Ajay Green
	mgr->register_creature_gossip(28687, gs);     //Amisi Azuregaze
	mgr->register_creature_gossip(23995, gs);     //Axle
	mgr->register_creature_gossip(26985, gs);     //Barracks Master Harga
	mgr->register_creature_gossip(27125, gs);     //Barracks Master Rhekku
	mgr->register_creature_gossip(24149, gs);     //Basil Osgood
	mgr->register_creature_gossip(24033, gs);     //Bori Wintertotem
	mgr->register_creature_gossip(15174, gs);     //Calandrath
	mgr->register_creature_gossip(28686, gs);     //Caliel Brightwillow
	mgr->register_creature_gossip(18251, gs);     //Caregiver Abidaar
	mgr->register_creature_gossip(16739, gs);     //Caregiver Breel
	mgr->register_creature_gossip(16553, gs);     //Caregiver Chellan
	mgr->register_creature_gossip(25036, gs);     //Caregiver Inaara
	mgr->register_creature_gossip(27148, gs);     //Caregiver Iqniq
	mgr->register_creature_gossip(18914, gs);     //Caregiver Isel
	mgr->register_creature_gossip(27174, gs);     //Caregiver Mumik
	mgr->register_creature_gossip(18906, gs);     //Caregiver Ophera Windfury
	mgr->register_creature_gossip(27187, gs);     //Caregiver Poallu
	mgr->register_creature_gossip(17553, gs);     //Caregiver Topher Loaal
	mgr->register_creature_gossip(21746, gs);     //Caretaker Aluuro
	mgr->register_creature_gossip(33970, gs);     //Caris Sunlance
	mgr->register_creature_gossip(24057, gs);     //Christina Daniels
	mgr->register_creature_gossip(27950, gs);     //Demestrasz
	mgr->register_creature_gossip(19352, gs);     //Dreg Cloudsweeper
	mgr->register_creature_gossip(19531, gs);     //Eyonix
	mgr->register_creature_gossip(21110, gs);     //Fizit "Doc" Clocktock
	mgr->register_creature_gossip(16602, gs);     //Floyd Pinkus
	mgr->register_creature_gossip(19470, gs);     //Gholah
	mgr->register_creature_gossip(29926, gs);     //Gunda Boldhammer
	mgr->register_creature_gossip(27042, gs);     //Illusia Lune
	mgr->register_creature_gossip(30308, gs);     //Initiate Brenners
	mgr->register_creature_gossip(11116, gs);     //Innkeeper Abeqwa
	mgr->register_creature_gossip(9501, gs);      //Innkeeper Adegwa
	mgr->register_creature_gossip(22922, gs);     //Innkeeper Aelerya
	mgr->register_creature_gossip(6740, gs);      //Innkeeper Allison
	mgr->register_creature_gossip(2352, gs);      //Innkeeper Anderson
	mgr->register_creature_gossip(6739, gs);      //Innkeeper Bates
	mgr->register_creature_gossip(18905, gs);     //Innkeeper Bazil Olof'tazun
	mgr->register_creature_gossip(1247, gs);      //Innkeeper Belm
	mgr->register_creature_gossip(19296, gs);     //Innkeeper Biribi
	mgr->register_creature_gossip(3934, gs);      //Innkeeper Boorand Plainswind
	mgr->register_creature_gossip(6727, gs);      //Innkeeper Brianna
	mgr->register_creature_gossip(7714, gs);      //Innkeeper Byula
	mgr->register_creature_gossip(23937, gs);     //Innkeeper Celeste Goodhutch
	mgr->register_creature_gossip(18907, gs);     //Innkeeper Coryth Stoktron
	mgr->register_creature_gossip(19319, gs);     //Innkeeper Darg Bloodclaw
	mgr->register_creature_gossip(15433, gs);     //Innkeeper Delaniel
	mgr->register_creature_gossip(16458, gs);     //Innkeeper Faralia
	mgr->register_creature_gossip(295, gs);       //Innkeeper Farley
	mgr->register_creature_gossip(5111, gs);      //Innkeeper Firebrew
	mgr->register_creature_gossip(7733, gs);      //Innkeeper Fizzgrimble
	mgr->register_creature_gossip(7737, gs);      //Innkeeper Greul
	mgr->register_creature_gossip(18957, gs);     //Innkeeper Grilka
	mgr->register_creature_gossip(6928, gs);      //Innkeeper Grosk
	mgr->register_creature_gossip(6929, gs);      //Innkeeper Gryshka
	mgr->register_creature_gossip(19232, gs);     //Innkeeper Haelthol
	mgr->register_creature_gossip(23731, gs);     //Innkeeper Hazel Lagras
	mgr->register_creature_gossip(6734, gs);      //Innkeeper Hearthstove
	mgr->register_creature_gossip(8931, gs);      //Innkeeper Heather
	mgr->register_creature_gossip(1464, gs);      //Innkeeper Helbrek
	mgr->register_creature_gossip(6272, gs);      //Innkeeper Janene
	mgr->register_creature_gossip(7731, gs);      //Innkeeper Jayka
	mgr->register_creature_gossip(17630, gs);     //Innkeeper Jovia
	mgr->register_creature_gossip(16542, gs);     //Innkeeper Kalarin
	mgr->register_creature_gossip(6930, gs);      //Innkeeper Karakul
	mgr->register_creature_gossip(6747, gs);      //Innkeeper Kauth
	mgr->register_creature_gossip(12196, gs);     //Innkeeper Kaylisk
	mgr->register_creature_gossip(6736, gs);      //Innkeeper Keldamyr
	mgr->register_creature_gossip(18908, gs);     //Innkeeper Kerp
	mgr->register_creature_gossip(6738, gs);      //Innkeeper Kimlya
	mgr->register_creature_gossip(11103, gs);     //Innkeeper Lyshaerya
	mgr->register_creature_gossip(6741, gs);      //Innkeeper Norman
	mgr->register_creature_gossip(6746, gs);      //Innkeeper Pala
	mgr->register_creature_gossip(19571, gs);     //Innkeeper Remi Dodoso
	mgr->register_creature_gossip(5688, gs);      //Innkeeper Renee
	mgr->register_creature_gossip(6735, gs);      //Innkeeper Saelienne
	mgr->register_creature_gossip(19495, gs);     //Innkeeper Shaunessy
	mgr->register_creature_gossip(6737, gs);      //Innkeeper Shaussiy
	mgr->register_creature_gossip(2388, gs);      //Innkeeper Shay
	mgr->register_creature_gossip(9356, gs);      //Innkeeper Shul'kar
	mgr->register_creature_gossip(7736, gs);      //Innkeeper Shyria
	mgr->register_creature_gossip(11106, gs);     //Innkeeper Sikewa
	mgr->register_creature_gossip(6807, gs);      //Innkeeper Skindle
	mgr->register_creature_gossip(5814, gs);      //Innkeeper Thulbek
	mgr->register_creature_gossip(7744, gs);      //Innkeeper Thulfram
	mgr->register_creature_gossip(6790, gs);      //Innkeeper Trelayne
	mgr->register_creature_gossip(16618, gs);     //Innkeeper Velandra
	mgr->register_creature_gossip(11118, gs);     //Innkeeper Vizzie
	mgr->register_creature_gossip(6791, gs);      //Innkeeper Wiley
	mgr->register_creature_gossip(32413, gs);     //Isirami Fairwind
	mgr->register_creature_gossip(25245, gs);     //James Deacon
	mgr->register_creature_gossip(33971, gs);     //Jarin Dawnglow
	mgr->register_creature_gossip(27066, gs);     //Jennifer Bell
	mgr->register_creature_gossip(16256, gs);     //Jessica Chambers
	mgr->register_creature_gossip(14731, gs);     //Lard
	mgr->register_creature_gossip(30005, gs);     //Lodge-Matron Embla
	mgr->register_creature_gossip(29963, gs);     //Magorn
	mgr->register_creature_gossip(28791, gs);     //Marissa Everwatch
	mgr->register_creature_gossip(15397, gs);     //Marniel Amberlight
	mgr->register_creature_gossip(27069, gs);     //Matron Magah
	mgr->register_creature_gossip(18913, gs);     //Matron Tikkit
	mgr->register_creature_gossip(21088, gs);     //Matron Varah
	mgr->register_creature_gossip(6778, gs);      //Melika Isenstrider
	mgr->register_creature_gossip(18245, gs);     //Merajit
	mgr->register_creature_gossip(19046, gs);     //Minalei
	mgr->register_creature_gossip(27027, gs);     //Mrs. Winterby
	mgr->register_creature_gossip(27052, gs);     //Naohain
	mgr->register_creature_gossip(26709, gs);     //Pahu Frosthoof
	mgr->register_creature_gossip(29583, gs);     //Pan'ya
	mgr->register_creature_gossip(29944, gs);     //Peon Gakra
	mgr->register_creature_gossip(28038, gs);     //Purser Boulian
	mgr->register_creature_gossip(26375, gs);     //Quartermaster McCarty
	mgr->register_creature_gossip(21744, gs);     //Roldemar
	mgr->register_creature_gossip(16826, gs);     //Sid Limbardi
	mgr->register_creature_gossip(29904, gs);     //Smilin' Slirk Brassknob
	mgr->register_creature_gossip(6806, gs);      //Tannok Frosthammer
	mgr->register_creature_gossip(24342, gs);     //Timothy Holland
	mgr->register_creature_gossip(31557, gs);     //Uda the Beast
	mgr->register_creature_gossip(29971, gs);     //Wabada Whiteflower
	mgr->register_creature_gossip(25278, gs);     //Williamson

    //note: Innkeeper Monica (18649) does not have a gossip option as she is from Old Hillsbrad Foothills
}
