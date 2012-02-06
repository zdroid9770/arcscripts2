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

class NihilTheBanished : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(NihilTheBanished)
	NihilTheBanished(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnLoad()
	{
		RegisterAIUpdateEvent(5000);
		GetUnit()->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);
		GetUnit()->GetAIInterface()->SetAllowedToEnterCombat(false);
		GetUnit()->GetAIInterface()->setCurrentAgent(AGENT_NULL);
		GetUnit()->GetAIInterface()->disable_melee = true;
		GetUnit()->GetAIInterface()->m_canMove = false;

		sEAS.EventCreatureSay( GetUnit(), "Muahahahahaha! You fool! you've released me from my banishment in the interstices between space and time!", 5000 );
		sEAS.EventCreatureSay( GetUnit(), "All of Draenor shall quake beneath my feet! i Will destroy this world and reshape it in my immage!", 10000 );
		sEAS.EventCreatureSay( GetUnit(), "Where shall i Begin? i cannot bother myself with a worm such as yourself. Theres a World to be Conquered!", 15000 );
		sEAS.EventCreatureSay( GetUnit(), "No doubt the fools that banished me are long dead. i shall take the wing and survey my new demense, Pray to whatever gods you hold dear that we do not meet again.", 20000 );

		GetUnit()->Despawn( 25000, 0 );
	}
};

class BrutebaneStoutTrigger : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BrutebaneStoutTrigger)
		BrutebaneStoutTrigger(Creature *pCreature) : CreatureAIScript(pCreature)
		{
			GetUnit()->Root();
			Plr = _unit->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ());

			uint32 BladespireOgres[] = {19995, 19998, 20756, 0};
			Ogre = sEAS.GetNearestCreature(GetUnit(), BladespireOgres);
			if(Ogre != NULL)
				Ogre->GetAIInterface()->_CalcDestinationAndMove(GetUnit(), 0.3f);

			RegisterAIUpdateEvent(1000);
		}

		void AIUpdate()
		{
			if(Ogre == NULL)
				return;

			if(GetUnit()->CalcDistance(Ogre) <= 5)
			{
				Ogre->SetEquippedItem(MELEE, 28562);
				Ogre->SetEmoteState(EMOTE_ONESHOT_EAT_NOSHEATHE);
				Ogre->SetFaction(35);
				Ogre->SetStandState(STANDSTATE_SIT);
				Ogre->Despawn(60000, 3*60*1000);

				GameObject *Mug = sEAS.GetNearestGameObject( GetUnit(), 184315 );
				if(Mug != NULL)
					Mug->Despawn(0, 0);

				if(Plr != NULL)
					sEAS.KillMobForQuest(Plr, 10512, 0);

				GetUnit()->Despawn(0, 0);
			}
		}

	protected:
		Player* Plr;
		Creature* Ogre;
};

void SetupBladeEdgeMountainsCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script(21823, &NihilTheBanished::Create);		// Nihil the Banished
	mgr->register_creature_script(21241, &BrutebaneStoutTrigger::Create);	// Bloodmaul Brutebane Stout Trigger
}
