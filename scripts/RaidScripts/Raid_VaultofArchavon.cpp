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

#define	NPC_ARCHAVON			31125
#define SPELL_ROCK_SHARDS		58678
#define	SPELL_CRUSHING_LEAP		Raid25manInst(58963, 60895)
#define	SPELL_STOMP				Raid25manInst(58663, 60880)
#define SPELL_IMPALE			Raid25manInst(58666, 60882)
#define	SPELL_CHOCKING_CLOUD	Raid25manInst(58965, 61672)
#define	SPELL_ARCHAVON_BERSERK	47008

class ArchavonAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ArchavonAI, MoonScriptBossAI);
		ArchavonAI(Creature *pCreature) : MoonScriptBossAI(pCreature)
		{
			mStompTimer = INVALIDATE_TIMER;
			SetEnrageInfo(AddSpell(SPELL_ARCHAVON_BERSERK, Target_Self, 0.0f, 0, 0), MINUTE*5*SEC_IN_MS);
		
			AddSpell(SPELL_ROCK_SHARDS, Target_Self, 20.0f, 0, 0);
			AddSpell(SPELL_CRUSHING_LEAP, Target_RandomPlayer, 30.0f, 0, 0);
			AddSpell(SPELL_CHOCKING_CLOUD, Target_RandomPlayer, 30.0f, 0, 0);
		}

		void OnCombatStart(Unit *mTarget)
		{
			mStompTimer = AddTimer(45*SEC_IN_MS);
			ParentClass::OnCombatStart(mTarget);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mStompTimer))
			{
				_unit->CastSpell(_unit, SPELL_STOMP, false);
				_unit->CastSpell(_unit, SPELL_IMPALE, false);
				ResetTimer(mStompTimer, 45*SEC_IN_MS);
			}

			if(_unit->GetCurrentSpell() == (Spell*)SPELL_CRUSHING_LEAP)
				_unit->CastSpell(_unit, SPELL_CHOCKING_CLOUD, false);

			ParentClass::AIUpdate();
		}

	private:
		SpellDesc * sRockShardsLeft, *sRockShardsRight;
		int32 mStompTimer;
};

#define	NPC_EMALON				33993
#define	SPELL_CHAIN_LIGHTNING	Raid25manInst(64213, 64215)
#define SPELL_LIGHTNING_NOVA	Raid25manInst(64216, 65279)
#define SPELL_EMALON_BERSERK	26662
#define SPELL_OVERCHARGE		64218
#define	NPC_TEMPEST_MINION		33998

class EmalonAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(EmalonAI, MoonScriptBossAI);
		EmalonAI(Creature *pCreature) : MoonScriptBossAI(pCreature)
		{
			SetEnrageInfo(AddSpell(SPELL_EMALON_BERSERK, Target_Self, 0.0f, 0, 0), MINUTE*6*SEC_IN_MS);
			AddSpell(SPELL_CHAIN_LIGHTNING, Target_RandomPlayer, 20, 0, 0);
			AddSpell(SPELL_LIGHTNING_NOVA, Target_Self, 30, 0, 0);

			mSpellOverchargeTimer = -1;
		}

		void OnCombatStart(Unit* mAttacker)
		{
			mSpellOverchargeTimer = AddTimer(45*SEC_IN_MS);
			ParentClass::OnCombatStart(mAttacker);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mSpellOverchargeTimer))
			{
				Unit * pMinion = ForceCreatureFind(NPC_TEMPEST_MINION);
				if(pMinion != NULL)
					_unit->CastSpell(pMinion, SPELL_OVERCHARGE, true);
				ResetTimer(mSpellOverchargeTimer, 45*SEC_IN_MS);
			}
			ParentClass::AIUpdate();
		}

	private:
		int32 mSpellOverchargeTimer;
};

#define	SPELL_SHOCK					64363
#define	SPELL_OVERCHARGED			64217
#define	SPELL_OVERCHARGED_BLAST		64219    // Cast when Overcharged reaches 10 stacks. Mob dies after that

class EmalonMinionAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(EmalonMinionAI, MoonScriptBossAI);
		EmalonMinionAI(Creature *pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(SPELL_SHOCK, Target_Current, 99, 0, 20);
		}

		void OnDied(Unit* mKiller)
		{
			Creature * pEmalon = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), NPC_EMALON);
			if(pEmalon != NULL && pEmalon->isAlive())
			{
				MoonScriptCreatureAI * pSummon = (MoonScriptCreatureAI*)pEmalon->GetMapMgr()->GetInterface()->SpawnCreature(NPC_TEMPEST_MINION, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), false, true, 0, 0, 1);
				if(pSummon != NULL)
					pSummon->AggroRandomPlayer();
			}
			ParentClass::OnDied(mKiller);
		}

		void OnCombatStop(Unit*pUnit)
		{
			RemoveAllAuras();
			ParentClass::OnCombatStop(pUnit);
		}

		void AIUpdate()
		{
			if(_unit->GetAuraStackCount(SPELL_OVERCHARGED) < 10)
			{
				_unit->CastSpell(_unit, SPELL_OVERCHARGED_BLAST, true);
			}else
			{
				_unit->CastSpell(_unit, SPELL_OVERCHARGED_BLAST, false);
				_unit->Die(_unit, 0, SPELL_OVERCHARGED_BLAST);	//not sure
			}
			ParentClass::AIUpdate();
		}

	protected:
		int32 OverChargedTimer;
};

void SetupVaultOfArchavon(ScriptMgr * mgr)
{
	mgr->register_creature_script(NPC_ARCHAVON, &ArchavonAI::Create);
	mgr->register_creature_script(NPC_EMALON, &EmalonAI::Create);
	mgr->register_creature_script(NPC_TEMPEST_MINION, &EmalonMinionAI::Create);
}
