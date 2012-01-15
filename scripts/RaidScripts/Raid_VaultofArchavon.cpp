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
#define SPELL_ROCK_SHARDS_LEFT	58678
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
			SetEnrageInfo(AddSpell(SPELL_ARCHAVON_BERSERK, Target_Self, 0.0f), MINUTE*5*SEC_IN_MS);
		
			AddSpell(SPELL_ROCK_SHARDS, Target_Self, 20.0f);
			AddSpell(SPELL_CRUSHING_LEAP, Target_RandomPlayer, 30.0f);
			AddSpell(SPELL_CHOCKING_CLOUD, Target_RandomPlayer, 30.0f);
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
				_unit->CastSpell(_unit, SPELL_IMPALE_STUN, false);
				_unit->CastSpell(_unit, SPELL_IMPALE, false);
				ResetTimer(mStompTimer, 45*SEC_IN_MS);
			}
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

static Location minionCoords[4] =
{
    {-203.980103f, -281.287720f, 91.650223f, 1.598807f},
    {-233.489410f, -281.139282f, 91.652412f, 1.598807f},
    {-233.267578f, -297.104645f, 91.681915f, 1.598807f},
    {-203.842529f, -297.097015f, 91.745163f, 1.598807f}
};

class EmalonAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(EmalonAI, MoonScriptBossAI);
		EmalonAI(Creature *pCreature) : MoonScriptBossAI(pCreature)
		{
			SetEnrageInfo(AddSpell(SPELL_EMALON_BERSERK, Target_Self, 0), MINUTE*6*SEC_IN_MS);
			AddSpell(SPELL_CHAIN_LIGHTNING, Target_RandomPlayer, 20);
			AddSpell(SPELL_LIGHTNING_NOVA, Target_Self, 30);
			AddSpell(SPELL_OVERCHARGE, Target_RandomFriendly, 99.0f, 0, 45);

			//getting firstly all minions around him
			for(uint8 i = 0; i<4; i++)
			{
				Unit * cMinions = ForceCreatureFind(NPC_TEMPEST_MINION, minionCoords[i].x, minionCoords[i].y, minionCoords[i].z);
				if(cMinions == NULL || !cMinions->isAlive())
					cMinions = SpawnCreature(NPC_TEMPEST_MINION, minionCoords[i].x, minionCoords[i].y, minionCoords[i].z);
			}
		}
};

#define	NPC_TEMPEST_MINION			33998
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
			MoonScriptCreatureAI * pEmalon = GetNearestCreature(NPC_EMALON);
			if(pEmalon != NULL && pEmalon->isAlive())
			{
				MoonScriptCreatureAI * pSummon = pEmalon->SpawnCreature(NPC_TEMPEST_MINION);
				if(pSummon != NULL)
					pSummon->AggroRandomPlayer();
			}
			ParentClass::OnDied(mKiller);
		}

		void AIUpdate()
		{
			if(_unit->GetAuraStackCount(SPELL_OVERCHARGED) < 10)
			{
				OverChargedTimer = AddTimer(2*SEC_IN_MS);
				if(IsTimerFinished(OverChargedTimer))
				{
					_unit->CastSpell(_unit, SPELL_OVERCHARGED_BLAST, true);
					ResetTimer(OverChargedTimer, 2*SEC_IN_MS);
				}
			}else _unit->CastSpell(_unit, SPELL_OVERCHARGED_BLAST, true);
			ParentClass::AIUpdate();
		}

	protected:
		int32 OverChargedTimer;
};

void SetupVaultofArchavon(ScriptMgr * mgr)
{
	mgr->register_creature_script(NPC_ARCHAVON, &ArchavonAI::Create);
	mgr->register_creature_script(NPC_EMALON, &EmalonAI::Create);
	mgr->register_creature_script(NPC_TEMPEST_MINIONN, &EmalonMinionAI::Create);
}
