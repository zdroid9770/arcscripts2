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

static LocationExtra PhizzlethorpeWP[]=
{
	(-2077.73f, -2091.17f, 9.49f, 0, 0),
	(-2077.99f, -2105.33f, 13.24f, 0, 0),
	(-2074.60f, -2109.67f, 14.24f, 0, 0),
	(-2076.60f, -2117.46f, 16.67f, 0, 0),
	(-2073.51f, -2123.46f, 18.42f, 0, 2000),
	(-2073.51f, -2123.46f, 18.42f, 0, 4000),
	(-2066.60f, -2131.85f, 21.56f, 0, 0),
	(-2053.85f, -2143.19f, 20.31f, 0, 0),
	(-2043.49f, -2153.73f, 20.20f, 0, 10000),
	(-2043.49f, -2153.73f, 20.20f, 0, 20000),
	(-2043.49f, -2153.73f, 20.20f, 0, 10000),
	(-2043.49f, -2153.73f, 20.20f, 0, 2000),
	(-2053.85f, -2143.19f, 20.31f, 0, 0),
	(-2066.60f, -2131.85f, 21.56f, 0, 0),
	(-2073.51f, -2123.46f, 18.42f, 0, 0),
	(-2076.60f, -2117.46f, 16.67f, 0, 0),
	(-2074.60f, -2109.67f, 14.24f, 0, 0),
	(-2077.99f, -2105.33f, 13.24f, 0, 0),
	(-2077.73f, -2091.17f, 9.49f, 0, 0),
	(-2066.41f, -2086.21f, 8.97f, 0, 6000),
	(-2066.41f, -2086.21f, 8.97f, 0, 2000)
};

class SunkenTreasure : public QuestScript
{
	public:
		void OnQuestStart(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			float SSX = mTarget->GetPositionX();
			float SSY = mTarget->GetPositionY();
			float SSZ = mTarget->GetPositionZ();

			Creature* creat = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ, 2768);
			if(creat == NULL)
				return;

			creat->m_escorter = mTarget;
			creat->GetAIInterface()->setMoveType(11);
			creat->GetAIInterface()->StopMovement(3000);
			creat->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "Ok, $N. Follow me to the cave where I\'ll attempt to harness the power of the rune stone into these goggles.");
			creat->SetUInt32Value(UNIT_NPC_FLAGS, 0);

			sEAS.CreateCustomWaypointMap(creat);
			for(uint8 i = 0; i<21; i++)
			{
				if(i<11)
					sEAS.WaypointCreate(creat, PhizzlethorpeWP[i].x, PhizzlethorpeWP[i].y, PhizzlethorpeWP[i].z, PhizzlethorpeWP[i].o, PhizzlethorpeWP[i].addition, Flag_Walk, 4049);
				else
					sEAS.WaypointCreate(creat, PhizzlethorpeWP[i].x, PhizzlethorpeWP[i].y, PhizzlethorpeWP[i].z, PhizzlethorpeWP[i].o, PhizzlethorpeWP[i].addition, Flag_Run, 4049);
			}
			sEAS.EnableWaypoints(creat);
		}
};

class Professor_Phizzlethorpe : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(Professor_Phizzlethorpe)
		Professor_Phizzlethorpe(Creature * pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Help!!! Get these things off me so I can get my work done!", Text_Yell, 0);
		}

		void OnReachWP(uint32 WpId, bool bForwards)
		{
			switch(WpId)
			{
				case 4: Emote("I discovered this cave on our first day here. I believe the energy in the stone can be used to our advantage.", Text_Yell, 0); break;
				case 5: Emote("I\'ll begin drawing energy from the stone. Your job, $N, is to defend me. This place is cursed... trust me.", Text_Yell, 0); break;
				case 8: Emote("%s begins tinkering with the goggles before the stone.", Text_Yell, 0); break;
				case 9:
				{
					MoonScriptCreatureAI * pCreature1 = SpawnCreature(2776, -2056.41f, -2144.01f, 20.59f, 5.70f);
					if(pCreature1 != NULL)
						pCreature1->SetDespawnWhenInactive(true);

					MoonScriptCreatureAI * pCreature2 = SpawnCreature(2776, -2050.17f, -2140.02f, 19.54f, 5.17f);
					if(pCreature2 != NULL)
						pCreature2->SetDespawnWhenInactive(true);
				}break;
				case 10: Emote("Almost done! Just a little longer!", Text_Yell, 0); break;
				case 11: Emote("I\'ve done it! I have harnessed the power of the stone into the goggles! Let\'s get out of here!", Text_Yell, 0); break;
				case 19: Emote("Phew! Glad to be back from that creepy cave.", Text_Yell, 0); break;
				case 20: 
				{
					Emote("%s hands one glowing goggles over to Doctor Draxlegauge.", Text_Yell, 0);
					Emote("Doctor Draxlegauge will give you further instructions, $N. Many thanks for your help!", Text_Yell, 0);
					_unit->Despawn(5000, 1000);
					sEAS.DeleteWaypoints(_unit);
					if(_unit->m_escorter == NULL)
						return;
					Player* plr = _unit->m_escorter;
					_unit->m_escorter = NULL;
					plr->GetQuestLogForEntry(665)->SendQuestComplete();
				}break;
			}
		}
};

void SetupArathiHighlands(ScriptMgr* mgr)
{
	mgr->register_creature_script(2768, &Professor_Phizzlethorpe::Create);
	mgr->register_quest_script(665, new SunkenTreasure);
}
