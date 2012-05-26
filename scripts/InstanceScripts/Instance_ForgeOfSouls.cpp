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
	 
// Bronjahm
enum BronjahmData{
	NPC_BRONJAHM		= 36497,
	SPELL_MAGICBANE		= 68793,
	SPELL_CORRUPT_SOUL	= 68839,
	SPELL_CONSUME_SOUL	= 68858,
	SPELL_FEAR			= 68950,
	SPELL_SHADOW_BOLT	= 70043,
	SPELL_SOULSTORM		= 68872,
	SPELL_TELEPORT		= 68988
};

class BronjahmAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BronjahmAI)
		BronjahmAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(SPELL_MAGICBANE, Target_Current, 35, 0, 5);
			AddSpell(SPELL_SHADOW_BOLT, Target_Current, 30, 1, -1);
			SoulStorm = AddSpell(SPELL_SOULSTORM, Target_Self, 0, 4, 0, 0, 0, true, "The vortex of the harvested calls to you!", Text_yell, 16599);
			AddPhaseSpell(2, AddSpell(SPELL_FEAR, Target_RandomPlayer, 40, 0, -1));

			AddEmote(Event_OnCombatStart, "Finally... a captive audience!", Text_Yell, 16595);
			AddEmote(Event_OnTargetDied, "Fodder for the engine!", Text_Yell, 16596);
			AddEmote(Event_OnTargetDied, "Another soul to strengthen the host!", Text_Yell, 16597);
			AddEmote(Event_OnDied, "My soul for you, master.", Text_Yell, 16598);
			BattleSoundTimer = CorruptedSoulTimer = -1;
		}

		void OnCombatStart(Unit * pAttacker)
		{
			CorruptedSoulTimer = AddTimer(25+rand()%11);
			switch(rand()%3)
			{
				case 0:
				{
					_unit->PlaySoundToSet(6077);
					BattleSoundTimer = AddTimer(48*SEC_IN_MS);
				}break;
				case 1:
				{
					_unit->PlaySoundToSet(6078);
					BattleSoundTimer = AddTimer(27*SEC_IN_MS);
				}break;
				case 2:
				{
					_unit->PlaySoundToSet(6078);
					BattleSoundTimer = AddTimer(36*SEC_IN_MS);
				}break;
			}
		}

		void AIUpdate()
		{
			if(IsTimerFinished(CorruptedSoulTimer) && (Unit * pTarget = GetBestPlayerTarget(TargetFilter_Closest)))
			{
				_unit->CastSpell(pTarget, SPELL_CORRUPT_SOUL, true);

				//hack, this should be done by spell
				SpawnTimer = AddTimer(4*SEC_IN_MS);
				if(IsTimerFinished(SpawnTimer))
				{
					Emote("I will sever your soul from your body!", Text_Yell, 16595);
					SpawnCreature(36535, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
					RemoveTimer(SpawnTimer);
				}
			}

			if(GetHealthPercent() == 30 && GetPhase() == 1)
			{
				_unit->CastSpell(_unit, SPELL_TELEPORT, true);
				SetPhase(2, SoulStorm);
			}

			if(IsTimerFinished(BattleSoundTimer))
			{
				switch(rand()%3)
				{
					case 0:
					{
						_unit->PlaySoundToSet(6077);
						ResetTimer(BattleSoundTimer, 48*SEC_IN_MS);
					}break;
					case 1:
					{
						_unit->PlaySoundToSet(6078);
						ResetTimer(BattleSoundTimer, 27*SEC_IN_MS);
					}break;
					case 2:
					{
						_unit->PlaySoundToSet(6078);
						ResetTimer(BattleSoundTimer, 36*SEC_IN_MS);
					}break;
				}
			}
		}

	private:
		int32 BattleSoundTimer, CorruptedSoulTimer, SpawnTimer;
		SpellDesc * SoulStorm;
};


class SoulFragmentAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SoulFragmentAI)
		SoulFragmentAI(Creature* c) : MoonScriptBossAI(c){}

		void OnLoad()
		{
			if(Unit * Boss = ForceCreatureFind(NPC_BRONJAHM))
			{
				_unit->GetAIInterface()->SetUnitToFollow(Boss);
				SetAIUpdateFreq(1*SEC_IN_MS);
			}
			else
				Despawn();
		}

		void AIUpdate()
		{
			if(Unit * Boss = ForceCreatureFind(NPC_BRONJAHM))
			{
				if(GetRangeToUnit(Boss) <= 2.0)
				{
					Boss->CastSpell(Boss, SPELL_CONSUME_SOUL, true);
					Despawn();
				}
			}
			SetAIUpdateFreq(1*SEC_IN_MS);
		}
};

void SetupForgeOfSouls(ScriptMgr * mgr)
{
	mgr->register_creature_script(NPC_BRONJAHM, &BronjahmAI::Create);
	mgr->register_creature_script(36535, &SoulFragmentAI::Create);
}
 