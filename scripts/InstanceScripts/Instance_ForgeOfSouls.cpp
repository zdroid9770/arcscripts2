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

//TODO: Script Devourer of Souls
// In 3.3.5a blizz changed how emblems dropped it should give the player the emblem not have it on its body.
	 
// Bronjahm
#define NPC_BRONJAHM 36497
#define MAGICBANE 68793
#define CORRUPTSOUL	68839
#define PHASE_1	36814

class BRONJAHMAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BRONJAHMAI)
		BRONJAHMAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(MAGICBANE, Target_Current, 35, 0, 5);
			AddSpell(CORRUPTSOUL, Target_RandomPlayer, 20, 0, 15, 5, 40, true, "I will sever your soul from your body!", Text_Yell, 16595);
			AddPhaseSpell(2, AddSpell(68872, Target_Self, 100, 4, 0));
			AddPhaseSpell(2, AddSpell(70043, Target_Current, 100, 1, 0));
			AddEmote(Event_OnCombatStart, "Finally... a captive audience!", Text_Yell, 16595);
			AddEmote(Event_OnTargetDied, "Fodder for the engine!", Text_Yell, 16596);
			AddEmote(Event_OnTargetDied, "Another soul to strengthen the host!", Text_Yell, 16597);
		}

		void OnDied(Unit* mKiller)
		{
			_unit->PlaySoundToSet(16598);
		}

		void AIUpdate()
		{
			if(GetPhase() == 1)
			{
				if(_unit->GetHealthPct() <= 30 )
				{
					Emote("The vortex of the harvested calls to you!");
					_unit->PlaySoundToSet(16599);
					_unit->Root();
					SetPhase(2);
				}
		}
};

void SetupForgeOfSouls(ScriptMgr * mgr)
{
	mgr->register_creature_script(NPC_BRONJAHM, &BRONJAHMAI::Create);
}
 