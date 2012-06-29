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

/****************************************/
/********************************TRASHES*/
/****************************************/
class IrradiatedPillagerAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(IrradiatedPillagerAI, MoonScriptCreatureAI);
		IrradiatedPillagerAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(9771, Target_RandomPlayer, 100, 0, 4);
		}

		void AIUpdate()
		{
			//casts fenzy at 50% health
			if(_unit->GetHealthPct() <= 50 && !_unit->HasAura(8269))
			{
				_unit->CastSpell(_unit, 8269, true);
				Emote("Your bones will break under my boot, $R!", Text_Yell, 0);
			}
			_unit->CastSpell(_unit, 9770, false);
			ParentClass::AIUpdate();
		}
		
		void OnDied(Unit* mKiller)
		{
			Emote("%s blood sprays into the air!", Text_Emote, 0);
			if(!_unit->HasAura(9798))
				_unit->CastSpell(_unit, 9798, true);
			ParentClass::OnDied(mKiller);
		}
};

class MobileAlertSystemAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(MobileAlertSystemAI, MoonScriptCreatureAI);
		MobileAlertSystemAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Warning! Warning! Intruder alert! Intruder alert!", Text_Yell, 5805);
			SummonTimer = -1;
			AlertTimer = -1;
			SetBehavior(Behavior_Flee);
		}

		void OnCombatStart(Unit* pUnit)
		{
			SummonTimer = AddTimer(60*SEC_IN_MS);
			AlertTimer = AddTimer(3*SEC_IN_MS);
			ParentClass::OnCombatStart(pUnit);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(SummonTimer))
			{
				_unit->PlaySoundToSet(5806);
				//summoning 2x Mechanized Sentry
				SpawnCreature(6233, _unit->GetPositionX()+rand()%5, _unit->GetPositionY()+rand()%5, _unit->GetPositionZ(), _unit->GetOrientation());
				SpawnCreature(6233, _unit->GetPositionX()+rand()%5, _unit->GetPositionY()+rand()%5, _unit->GetPositionZ(), _unit->GetOrientation());
				ResetTimer(SummonTimer, 60*SEC_IN_MS);
			}

			if(IsTimerFinished(AlertTimer))
			{
				Emote("Warning! Warning! Intruder alert! Intruder alert!", Text_Yell, 5805);
				_unit->CastSpell(_unit, 1543, false);
				ResetTimer(AlertTimer, 3*SEC_IN_MS);
			}
			ParentClass::AIUpdate();
		}

	private:
		int32 SummonTimer;
		int32 AlertTimer;
};

/****************************************/
/*********************************BOSSES*/
/****************************************/
class Electrocutioner6000AI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(Electrocutioner6000AI, MoonScriptCreatureAI);
		Electrocutioner6000AI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Electric justice!", Text_Yell, 5811);
			AddSpell(11082, Target_Current, 100, 2, 15); //megavolt
			AddSpell(11084, Target_RandomPlayer, 100, 0, 10); //shock
			AddSpell(11085, Target_RandomPlayer, 100, 2.5f, 17); //Chain Bolt
		}
};

void SetupGnomeregan(ScriptMgr* mgr)
{
	//trashes
	mgr->register_creature_script(6329, &IrradiatedPillagerAI::Create);
	mgr->register_creature_script(7849, &MobileAlertSystemAI::Create);

	//bosses
	mgr->register_creature_script(6235, &Electrocutioner6000AI::Create);
}
