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

class WyrmcultBlackwhelp : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WyrmcultBlackwhelp);
		WyrmcultBlackwhelp(Creature* c) : CreatureAIScript(c) {}

		void OnLoad()
		{
			RegisterAIUpdateEvent(1000);
		}

		void AIUpdate()
		{
			// Let's see if we are netted
			Aura* a = _unit->FindAura(38177);
			if(a != NULL)
			{
				Unit* Caster = a->GetUnitCaster();
				if(Caster->IsPlayer())
				{

					QuestLogEntry* qle = TO_PLAYER(Caster)->GetQuestLogForEntry(10747);
					if(qle != NULL)
					{
						// casting the spell that will create the item for the player
						_unit->CastSpell(Caster, 38178, true);
						_unit->Despawn(1000, 360000);
					}
				}
			}
		}
};

// The Bladespire Threat Quest
class BladespireQAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BladespireQAI);
		BladespireQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(mKiller->IsPlayer())
			{
				QuestLogEntry* en = (TO_PLAYER(mKiller))->GetQuestLogForEntry(10503);
				if(en && en->GetMobCount(0) < en->GetQuest()->required_mobcount[0])
				{
					uint32 newcount = en->GetMobCount(0) + 1;
					en->SetMobCount(0, newcount);
					en->SendUpdateAddKill(0);
					en->UpdatePlayerFields();
					return;
				}
			}
		}
};

class IntotheSoulgrinder : public QuestScript
{
	public:
		void OnQuestComplete(Player* mTarget, QuestLogEntry* qLogEntry)
		{
			Creature* qg = mTarget->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(mTarget->GetPositionX(), mTarget->GetPositionY(), 0, 22941);
			if(qg == NULL)
				return;
			qg->GetMapMgr()->GetInterface()->SpawnCreature(23053, 2794.978271f, 5842.185547f, 35.911819f, 0, true, false, 0, 0);
		}
};

class MagnetoAura : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(MagnetoAura);
		MagnetoAura(Creature* pCreature) : CreatureAIScript(pCreature) {}

		void OnLoad()
		{
			_unit->CastSpell(_unit, 37136, true);
		}
};

class BloodmaulQAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BloodmaulQAI);
		BloodmaulQAI(Creature* pCreature) : CreatureAIScript(pCreature)  {}

		void OnDied(Unit* mKiller)
		{
			if(!mKiller->IsPlayer())
				return;

			Player* pPlayer = TO_PLAYER(mKiller);
			QuestLogEntry* pQuest = pPlayer->GetQuestLogForEntry(10502);
			if(pQuest == NULL)
			{
				pQuest = pPlayer->GetQuestLogForEntry(10505);
				if(pQuest == NULL)
				{
					return;
				}
			}

			if(pQuest->GetMobCount(0) < pQuest->GetQuest()->required_mobcount[0])
			{
				uint32 NewCount = pQuest->GetMobCount(0) + 1;
				pQuest->SetMobCount(0, NewCount);
				pQuest->SendUpdateAddKill(0);
				pQuest->UpdatePlayerFields();
			}
		}
};

//////////////////////////////////////////////////////////////////////////
/////// Bladespire Brute/Shaman/Cook
#define CN_BLADESPIRE_OGRE_1				19995
#define CN_BLADESPIRE_OGRE_2				19998
#define CN_BLADESPIRE_OGRE_3				20756

void SetupBladeEdgeMountains(ScriptMgr* mgr)
{
	mgr->register_creature_script(21387, &WyrmcultBlackwhelp::Create);
	mgr->register_creature_script(CN_BLADESPIRE_OGRE_1, &BladespireQAI::Create);
	mgr->register_creature_script(21296, &BladespireQAI::Create);
	mgr->register_creature_script(CN_BLADESPIRE_OGRE_3, &BladespireQAI::Create);
	mgr->register_creature_script(20766, &BladespireQAI::Create);
	mgr->register_creature_script(CN_BLADESPIRE_OGRE_2, &BladespireQAI::Create);
	mgr->register_creature_script(21731, &MagnetoAura::Create);
	mgr->register_creature_script(19957, &BloodmaulQAI::Create);
	mgr->register_creature_script(19991, &BloodmaulQAI::Create);
	mgr->register_creature_script(21238, &BloodmaulQAI::Create);
	mgr->register_creature_script(19952, &BloodmaulQAI::Create);
	mgr->register_creature_script(21294, &BloodmaulQAI::Create);
	mgr->register_creature_script(19956, &BloodmaulQAI::Create);
	mgr->register_creature_script(19993, &BloodmaulQAI::Create);
	mgr->register_creature_script(19992, &BloodmaulQAI::Create);
	mgr->register_creature_script(19948, &BloodmaulQAI::Create);
	mgr->register_creature_script(22384, &BloodmaulQAI::Create);
	mgr->register_creature_script(22160, &BloodmaulQAI::Create);
	mgr->register_creature_script(19994, &BloodmaulQAI::Create);

	mgr->register_quest_script(11000, new IntotheSoulgrinder());

	mgr->register_creature_script(21387, &WyrmcultBlackwhelp::Create);

}
