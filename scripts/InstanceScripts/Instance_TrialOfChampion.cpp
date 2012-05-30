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
 
/* Trial Of Champions
Information: http://www.wowhead.com/zone=4723
ISSUES: Need to have a check if alliance or horde player than spawn the correct people.
*/


enum PALETREESData{
	NPC_PALETREES		= 34928,
	SPELL_HOLYSMITE		= 66536,
	SPELL_HOLYNOVA		= 66546,
	SPELL_REFLECTSHIELD	= 66515,
	SPELL_RENEW			= 66537,
	SPELL_MEMORY		= 66543,
	SPELL_CONFESS		= 66680
};

class PaletreesAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(PaletreesAI)
		PaletreesAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(SPELL_HOLYSMITE, Target_RandomPlayer, 60, 2, 0);
			AddSpell(SPELL_HOLYNOVA, Target_Self, 40, 0, 10);
			AddSpell(SPELL_RENEW, Target_Self, 10, 1, 15);
			Confess = AddSpell(SPELL_CONFESS, Target_Self, 0, 5, 0);

			AddEmote(Event_OnCombatStart, "Well then, let us begin.", Text_Yell, 16247);
			AddEmote(Event_OnTargetDied, "Take your rest.", Text_Yell, 16250); // Need sound ID
			AddEmote(Event_OnTargetDied, "Be at ease.", Text_Yell, 16251); // Need sound ID
		}

		void AIUpdate()
		{
			if(GetPhase() == 1 && GetHealthPercent() <= 50)
			{
				_unit->CastSpell(_unit, SPELL_REFLECTSHIELD, true);
				Emote("Take this time to consider your past deeds.", Text_Yell, 16248);
				//need correction, it should be spawned in center of coliseum
				SpawnCreature(34942);
				SetPhase(2, Confess);
			}

			if(GetPhase() == 3 && GetHealthPercent() < 5) // NEED TO ADD THE GAMEOBJECT LOOT.
			{
				_unit->WipeHateList();
				_unit->SetFaction(35);
				Emote("Excellent work!", Text_Yell, 16252);
				// Not suppose to "jump" despawn, she is suppose to walk off the floor then despawn.
				_unit->GetAIInterface()->MoveJump(747.365f, 692.113f, 412.351f);
				_unit->GetMapMgr()->GetInterface()->SpawnGameObject(195323, 748.76f, 618.309f, 411.089f, 1.58f, true, 0, 0, 1);
				_unit->Despawn(10000, 0);
				SetPhase(4);
			}
		}

	private:
		SpellDesc * Confess;
};

class MemoryAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(MemoryAI)
		MemoryAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
		}

		void OnDied(Unit * mKiller)
		{
			if(Creature * mBoss = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), NPC_PALETREES))
			{
				MoonScriptBossAI * pBoss = dynamic_cast<MoonScriptBossAI*>(mBoss->GetScript());
				pBoss->RemoveAura(SPELL_REFLECTSHIELD);
				pBoss->Emote("Even the darkest memory fades when confronted.", Text_Yell, 16249);
				pBoss->SetPhase(3);
			}
		}
};

 void SetupTrialOfChampionHold(ScriptMgr * mgr)
 {
	 mgr->register_creature_script(NPC_PALETREES, &PaletreesAI::Create);
	 mgr->register_creature_script(34942, &MemoryAI::Create);
 }
 