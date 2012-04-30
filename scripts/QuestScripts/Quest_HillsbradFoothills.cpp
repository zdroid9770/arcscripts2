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

bool BaronVardusAllowSpawn = true;

class WantedBaronVardus : public QuestScript
{
	public:

		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			if(BaronVardusAllowSpawn == true)
			{
				uint32 rand = RandomUInt(3);
				switch(rand)
				{
					case 0:
						mTarget->GetMapMgr()->GetInterface()->SpawnCreature(2306, 692.64f, -904.74f, 157.79f, 0, true, false, 0, 0)->Despawn(1800000, 0);
					case 1:
						mTarget->GetMapMgr()->GetInterface()->SpawnCreature(2306, 939.0f, -852.46f, 114.644f, 0, true, false, 0, 0)->Despawn(1800000, 0);
					case 2:
						mTarget->GetMapMgr()->GetInterface()->SpawnCreature(2306, 1184.07f, -553.43f, 71.3346f, 0, true, false, 0, 0)->Despawn(1800000, 0);
					case 3:
						mTarget->GetMapMgr()->GetInterface()->SpawnCreature(2306, 1001.20f, -793.93f, 108.65f, 0, true, false, 0, 0)->Despawn(1800000, 0);
				}
				BaronVardusAllowSpawn = false;
			}
		}
};

class Baron_Vardus : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Baron_Vardus);
		Baron_Vardus(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnDied(Unit* mKiller)
		{
			BaronVardusAllowSpawn = true;
		}
};

class Flame_of_Azel : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(Flame_of_Azel)
		Flame_of_Azel(GameObject *g) : GameObjectAIScript(g) {}

		void OnActivate(Player *pPlayer)
		{
			QuestLogEntry *pQuests = pPlayer->GetQuestLogForEntry(553);
			if(pQuests == NULL)
				return;

			if(!pPlayer->HasItemCount(3710, 1))
				return;

			if(pQuests->GetMobCount(0) < pQuests->GetQuest()->required_mobcount[0])
			{
				pQuests->SetMobCount(0, pQuests->GetMobCount(0)+1);
				pQuests->SendUpdateAddKill(0);
				pQuests->UpdatePlayerFields();
			}
		}
};

class Flame_of_Veraz : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(Flame_of_Veraz)
		Flame_of_Veraz(GameObject *g) : GameObjectAIScript(g) {}

		void OnActivate(Player *pPlayer)
		{
			QuestLogEntry *pQuests = pPlayer->GetQuestLogForEntry(553);
			if(pQuests == NULL)
				return;

			if(!pPlayer->HasItemCount(3710, 1))
				return;

			if(pQuests->GetMobCount(1) < pQuests->GetQuest()->required_mobcount[1])
			{
				pQuests->SetMobCount(1, pQuests->GetMobCount(1)+1);
				pQuests->SendUpdateAddKill(1);
				pQuests->UpdatePlayerFields();
			}
		}
};

class Flame_of_Uzel : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(Flame_of_Uzel)
		Flame_of_Uzel(GameObject *g) : GameObjectAIScript(g) {}

		void OnActivate(Player *pPlayer)
		{
			QuestLogEntry *pQuests = pPlayer->GetQuestLogForEntry(553);
			if(pQuests == NULL)
				return;

			if(!pPlayer->HasItemCount(3710, 1))
				return;

			if(pQuests->GetMobCount(2) < pQuests->GetQuest()->required_mobcount[2])
			{
				pQuests->SetMobCount(2, pQuests->GetMobCount(2)+1);
				pQuests->SendUpdateAddKill(2);
				pQuests->UpdatePlayerFields();
			}
		}
};

void SetupHillsbradFoothills(ScriptMgr* mgr){
	mgr->register_creature_script(2306, &Baron_Vardus::Create);
	mgr->register_quest_script(566, new WantedBaronVardus);
	mgr->register_gameobject_script(1768, &Flame_of_Azel::Create);
	mgr->register_gameobject_script(1769, &Flame_of_Veraz::Create);
	mgr->register_gameobject_script(1770, &Flame_of_Uzel::Create);
}
