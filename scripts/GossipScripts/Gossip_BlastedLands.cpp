/*
 * WhyScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2010 WhyDB Team <http://www.whydb.org/>
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

class FallenHero : public Arcemu::Gossip::Script
{
public:
	void OnHello(Object *pObject, Player *Plr)
	{
		Arcemu::Gossip::Menu menu(pObject->GetGUID(), 1391);
		if(Plr->HasQuest(11708))
			menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I need to speak with Corporal.", 1);

		menu.Send(Plr);
	}
 
	void OnSelectOption(Object *pObject, Player *Plr, uint32 Id, const char *EnteredCode)
	{
		if( sEAS.GetNearestCreature(Plr, 7750 ) == NULL)
			sEAS.SpawnCreature(Plr, 7750, -10630, -2986.98f, 28.9815f, 4.73538f, 600000 );

		if( sEAS.GetNearestGameObject( Plr, 141980 ) == NULL)
			sEAS.SpawnGameobject( Plr, 141980, -10633.4f, -2985.83f, 28.986f, 4.74371f, 1, 0, 0, 0.695946f, -0.718095f );
	}
};

void SetupBlastedLandsGossip(ScriptMgr * mgr)
{
	mgr->register_creature_gossip(7572, new FallenHero);	// Fallen Hero of the Horde
}
