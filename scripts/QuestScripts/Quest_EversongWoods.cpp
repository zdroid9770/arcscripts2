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

static LocationExtra ProspectorAnvilwardWaypoints[]=
{
	{9294.78f, -6682.51f, 22.42f, 	0},
	{9298.27f, -6667.99f, 22.42f, 	0},
	{9309.63f, -6658.84f, 22.43f, 	0},
	{9304.43f, -6649.31f, 26.46f, 	0},
	{9298.83f, -6648.00f, 28.61f, 	0},
	{9291.06f, -6653.46f, 31.83f,	2500},
	{9289.08f, -6660.17f, 31.85f,	5000},
	{9291.06f, -6653.46f, 31.83f, 	0}
};

class ProspectorAnvilwardGossip : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* Plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);
			if(Plr->HasQuest(8483))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I need a moment of your time, sir.", 1);
			menu.Send(Plr);
		}

		void OnSelectOption(Object* pObject, Player* Plr, uint32 Id, const char* EnteredCode)
		{
			switch(Id)
			{
				case 1: Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 8240, Plr, 2, Arcemu::Gossip::ICON_CHAT, "Why... yes, of course. I've something to show you right inside this building, Mr. Anvilward."); break;
				case 2:
				{
					Arcemu::Gossip::Menu::Complete(Plr);
					TO_CREATURE(pObject)->GetAIInterface()->setMoveType(MOVEMENTTYPE_FORWARDTHANSTOP);
				}break;
			}
		}
};

class ProspectorAnvilwardAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ProspectorAnvilwardAI, MoonScriptCreatureAI)
		ProspectorAnvilwardAI(Creature * pCreature) : MoonScriptCreatureAI(pCreature)
		{
			for(uint8 i = 0; i<8; i++)
				AddWaypoint(CreateWaypoint(i, ProspectorAnvilwardWaypoints[i].addition, Flag_Walk, ProspectorAnvilwardWaypoints[i]));

			SetMoveType(Move_None);
		}

		void OnReachWP(uint32 Id, bool bForwards)
		{
			switch(Id)
			{
				case 0: Emote("Very well. Let\'s see what you have to show me, $N.", Text_Yell, 0); break;
				case 5: Emote("What manner of trick is this, $R? If you seek to ambush me, I warn you I will not go down quietly!", Text_Yell, 0);
				case 6: _unit->SetFaction(24); break;
			}
		}

		void OnDied(Unit* mKiller)
		{
			_unit->SetFaction(35);
			ParentClass::OnDied(mKiller);
		}

		void OnCombatStop(Unit* pTarget)
		{
			_unit->SetFaction(35);
			ParentClass::OnCombatStop(pTarget);
		}
};

void SetupEversongWoods(ScriptMgr* mgr)
{
	mgr->register_creature_gossip(15420, new ProspectorAnvilwardGossip);
	mgr->register_creature_script(15420, &ProspectorAnvilwardAI::Create);
}
