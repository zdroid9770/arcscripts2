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

class HeroesofOld : public QuestScript
{
	public:
		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			Creature* spawncheckcr = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(mTarget->GetPositionX(), mTarget->GetPositionY(), mTarget->GetPositionZ(), 7750);

			if(!spawncheckcr)
			{
				Creature* general = sEAS.SpawnCreature(mTarget, 7750, -10619, -2997, 28.8f, 4, 0);
				general->Despawn(3 * 60 * 1000, 0);
			}

			GameObject* spawncheckgobj = mTarget->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(mTarget->GetPositionX(), mTarget->GetPositionY(), mTarget->GetPositionZ(), 141980);

			if(!spawncheckgobj)
			{
				GameObject* generalsbox = sEAS.SpawnGameobject(mTarget, 141980, -10622, -2994, 28.6f, 4, 4, 0, 0, 0, 0);
				sEAS.GameobjectDelete(generalsbox, 3 * 60 * 1000);
			}
		}
};

class HeroesofOld1 : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object* pObject, Player* plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), plr->GetSession()->language);
			if(plr->GetQuestLogForEntry(2702) || plr->HasFinishedQuest(2702))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I need to speak with Corporal.", 1);
			menu.Send(plr);
		}

		void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char* EnteredCode)
		{
			Creature* general = TO_CREATURE(pObject);
			Creature* spawncheckcr = plr->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), 7750);

			if(!spawncheckcr)
			{
				general = sEAS.SpawnCreature(plr, 7750, -10619.0f, -2997.0f, 28.8f, 4, 0);
				general->Despawn(3 * 60 * 1000, 0);
			}

			GameObject* spawncheckgobj = plr->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ(), 141980);

			if(!spawncheckgobj)
			{
				GameObject* generalsbox = sEAS.SpawnGameobject(plr, 141980, -10622.0f, -2994.0f, 28.6f, 4, 4, 0, 0, 0, 0);
				sEAS.GameobjectDelete(generalsbox, 3 * 60 * 1000);
			}
		}
};

class FallenHero : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object *pObject, Player *Plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);
			if(Plr->GetQuestLogForEntry(11708))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I need to speak with Corporal.", 1);

			menu.Send(Plr);
		}
	 
		void OnSelectOption(Object *pObject, Player *Plr, uint32 Id, const char *EnteredCode)
		{
			Arcemu::Gossip::Menu::Complete(Plr);

			if(sEAS.GetNearestCreature(Plr, 7750) == NULL)
				sEAS.SpawnCreature(Plr, 7750, -10630, -2986.98f, 28.9815f, 4.73538f, 600000 );

			if(sEAS.GetNearestGameObject(Plr, 141980) == NULL)
				sEAS.SpawnGameobject( Plr, 141980, -10633.4f, -2985.83f, 28.986f, 4.74371f, 1, 0, 0, 0.695946f, -0.718095f );
		}
};

class DeathlyUsher : public Arcemu::Gossip::Script
{
	public:
		void OnHello(Object *pObject, Player *Plr)
		{
			Arcemu::Gossip::Menu menu(pObject->GetGUID(), objmgr.GetGossipTextForNpc(pObject->GetEntry()), Plr->GetSession()->language);
			if(Plr->GetQuestLogForEntry(3628) && Plr->HasItemCount(10757, 1))
				menu.AddItem(Arcemu::Gossip::ICON_CHAT, "I wish to to visit the Rise of the Defiler.", 1);
			menu.Send(Plr);
		}
	 
		void OnSelectOption(Object *pObject, Player *Plr, uint32 Id, const char *EnteredCode)
		{
			Arcemu::Gossip::Menu::Complete(Plr);
			TO_CREATURE(pObject)->CastSpell(Plr, 12885, true);
		}
};

void SetupBlastedLands(ScriptMgr* mgr)
{
	mgr->register_quest_script(2702, new HeroesofOld);
	mgr->register_creature_gossip(7572, new HeroesofOld1);
	mgr->register_creature_gossip(7572, new FallenHero);	// Fallen Hero of the Horde
	mgr->register_creature_gossip(8816, new DeathlyUsher);
}
