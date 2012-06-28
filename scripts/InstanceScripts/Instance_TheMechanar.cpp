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

// Gatewatcher Gyro-Kill AI
enum GatewatcherGyroKill{
	CN_GATEWATCHER_GYRO_KILL	= 19218,

	SAW_BLADE					= 35318,
	SHADOW_POWER_GKILL			= 35322,
	STEAM_OF_MACHINE_FLUID_GKILL	= 35311
};

class GatewatcherGyroKillAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(GatewatcherGyroKillAI, MoonScriptCreatureAI);
		GatewatcherGyroKillAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SpellDesc * sSawBlade = AddSpell(SAW_BLADE, Target_Current, 13.0f, 0, -1);
			sSawBlade->AddEmote("Measure twice; cut once.", Text_Yell, 11104);
			sSawBlade->AddEmote("If my division is correct, you should be quite dead!", Text_Yell, 11105);

			AddSpell(SHADOW_POWER_GKILL, Target_Self, 7, 2, -1);
			AddSpell(STEAM_OF_MACHINE_FLUID_GKILL, Target_Self, 9, 0, -1);

			AddEmote(Event_OnCombatStart, "I predict a painful death.", Text_Yell, 11101);
			//AddEmote(Event_OnTargetDied, "Your strategy was flat!", Text_Yell, 11102); <- Don't see this on wowwiki.
			AddEmote(Event_OnTargetDied, "Yes, the only logical outcome.", Text_Yell, 11103); //http://www.wowwiki.com/Gatewatcher_Gyro-Kill
			AddEmote(Event_OnDied, "An unforseen... contingency.", Text_Yell, 11106);
		}
};

// Gatewatcher Iron-Hand AI
enum Gatewatcher_IronHand{
	CN_GATEWATCHER_IRON_HAND		= 19710,
	JACK_HAMMER						= 35327,
	HAMMER_PUNCH					= 35326,
	STREAM_OF_MACHINE_FLUID_IHAND	= 35311,
	SHADOW_POWER_IHAND				= 35322
};

class GatewatcherIronHandAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(GatewatcherIronHandAI, MoonScriptCreatureAI);
		GatewatcherIronHandAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SpellDesc * sHammer = AddSpell(JACK_HAMMER, Target_Current, 7, 1.5f, -1);
			sHammer->AddEmote("With the precise angle and velocity...", Text_Yell, 11112);
			sHammer->AddEmote("Low tech yet quiet effective!", Text_Yell, 11113);

			AddSpell(HAMMER_PUNCH, Target_Current, 9, 0, -1); 
			AddSpell(STREAM_OF_MACHINE_FLUID_IHAND, Target_RandomPlayer, 7, 0, -1); 
			AddSpell(SHADOW_POWER_IHAND, Target_Self, 7, 2, -1);
			AddEmote(Event_OnCombatStart, "You have approximately five seconds to live.", Text_Yell, 11109); // http://www.wowwiki.com/Gatewatcher_Iron-Hand
			AddEmote(Event_OnTargetDied, "A foregone conclusion.", Text_Yell, 11110);//http://www.wowwiki.com/Gatewatcher_Iron-Hand
			//AddEmote(Event_OnTargetDied, "The processing will continue as scheduled!", Text_Yell, 11111); <- Don't see this on wowwiki
			AddEmote(Event_OnDied, "My calculations did not...", Text_Yell, 11114);//http://www.wowwiki.com/Gatewatcher_Iron-Hand
		}
};

// Mechano-Lord Capacitus AI
enum MechanoLordCapacitus{
	CN_MECHANO_LORD_CAPACITUS	= 19219,

	HEAD_CRACK					= 35161,
	REFLECTIVE_DAMAGE_SHIELD	= 35159,
	REFLECTIVE_MAGIC_SHIELD		= 35158,
	SEED_OF_CORRUPTION			= 37826
};
class MechanoLordCapacitusAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(MechanoLordCapacitusAI, MoonScriptCreatureAI);
		MechanoLordCapacitusAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(HEAD_CRACK, Target_Current, 8, 0, -1);
			AddSpell(REFLECTIVE_DAMAGE_SHIELD, Target_Self, 7, 0, -1, 0, 0, false, "Think you can hurt me, huh? Think I'm afraid a' you?", Text_Yell, 11165);
			AddSpell(REFLECTIVE_MAGIC_SHIELD, Target_Self, 7, 0, -1, 0, 0, false, "Go ahead, gimme your best shot. I can take it!", Text_Yell, 11166);
			AddSpell(SEED_OF_CORRUPTION, Target_Self, 5, 0, -1);
			AddEmote(Event_OnCombatStart, "You should split while you can.", Text_Yell, 11162);
			//AddEmote(Event_OnTargetDied, "Can't say I didn't warn you!", Text_Yell, 11163); <- Didn't see this on wowwiki
			AddEmote(Event_OnTargetDied, "Damn, I'm good!", Text_Yell, 11164);
			AddEmote(Event_OnDied, "Bully!", Text_Yell, 11167);
		}
};

// Nethermancer Sepethrea AI

#define CN_NETHERMANCER_SEPETHREA 19221

#define SUMMON_RAGIN_FLAMES 35275	// must add despawning after death!
#define FROST_ATTACK 35263
#define ARCANE_BLAST 35314
#define DRAGONS_BREATH 35250
//#define KNOCKBACK 37317	// not sure to this one!

class NethermancerSepethreaAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(NethermancerSepethreaAI, MoonScriptCreatureAI);
		NethermancerSepethreaAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(FROST_ATTACK, Target_Current, 9, 0, -1);
			AddSpell(ARCANE_BLAST, Target_Current, 3, 0, -1);
			SpellDesc * sDragonBreath = AddSpell(DRAGONS_BREATH, Target_Current, 8, 0, -1);
			sDragonBreath->AddEmote("Think you can take the heat?", Text_Yell, 11189);
			sDragonBreath->AddEmote("Anar'endal dracon!", Text_Yell, 11190);
			AddEmote(Event_OnCombatStart, "Don't value your life very much, do you?", Text_Yell, 11186);
			AddEmote(Event_OnTargetDied, "And don't come back!", Text_Yell, 11187);
			AddEmote(Event_OnTargetDied, "Endala finel endal!", Text_Yell, 11188);
			AddEmote(Event_OnDied, "Anu... bala belore...alon.", Text_Yell, 11192);
		}

		void OnCombatStart(Unit* mTarget)
		{
			_unit->CastSpell(_unit, SUMMON_RAGIN_FLAMES, true);
			//Emote("I am not alone!", Text_Yell, 11191); <- Don't see this on wowwiki
			ParentClass::OnCombatStart(mTarget);
		}
};

// Pathaleon the Calculator AI

#define CN_PATHALEON_THE_CALCULATOR 19220

#define MANA_TRAP 36021 // I am not sure to any of those ids =(
#define DOMINATION 36866
#define SILENCE 38491
#define SUMMON_NETHER_WRAITH1 35285	// not the best way, but blizzlike :) (but they don't work for now =()
#define SUMMON_NETHER_WRAITH2 35286
#define SUMMON_NETHER_WRAITH3 35287
#define SUMMON_NETHER_WRAITH4 35288
// hmm... he switches weapons and there is sound for it, but I must know when he does that, how it looks like etc.
// before adding weapon switching =/	(Sound: 11199; speech: "I prefer to be hands-on...";)

class PathaleonTheCalculatorAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(PathaleonTheCalculatorAI, MoonScriptCreatureAI);
		PathaleonTheCalculatorAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SummonTimer = -1;
			AddSpell(MANA_TRAP, Target_Current, 8, 0, -1);
			SpellDesc* sDomination = AddSpell(DOMINATION, Target_Current, 4, 0, -1);
			sDomination->AddEmote("I'm looking for a team player...", Text_Yell, 11197);
			sDomination->AddEmote("You work for me now!", Text_Yell, 11198);
			AddSpell(SILENCE, Target_Self, 6, 0, -1);
			AddEmote(Event_OnCombatStart, "We are on a strict timetable. You will not interfere!", Text_Yell, 11193);
			AddEmote(Event_OnTargetDied, "A minor inconvenience.", Text_Yell, 11194);
			AddEmote(Event_OnTargetDied, "Looks like you lose.", Text_Yell, 11195);
			AddEmote(Event_OnDied, "The project will... continue.", Text_Yell, 11200);
		}

		void OnCombatStart(Unit * pAttacker)
		{
			SummonTimer = AddTimer((rand()%16 + 30)*SEC_IN_MS);
			ParentClass::OnCombatStart(pAttacker);
		}

		void AIUpdate()
		{
			if(!SummonTimer)
			{
				_unit->CastSpell(_unit, SUMMON_NETHER_WRAITH1, true);
				_unit->CastSpell(_unit, SUMMON_NETHER_WRAITH2, true);
				_unit->CastSpell(_unit, SUMMON_NETHER_WRAITH3, true);
				_unit->CastSpell(_unit, SUMMON_NETHER_WRAITH4, true);
				Emote("Time to supplement my workforce.", Text_Yell, 11196);//http://www.wowwiki.com/Pathaleon_the_Calculator
				ResetTimer(SummonTimer, (rand()%16 + 30)*SEC_IN_MS);
			}
			ParentClass::AIUpdate();
		}

	private:
		int32 SummonTimer;
};

void SetupTheMechanar(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_GATEWATCHER_GYRO_KILL, &GatewatcherGyroKillAI::Create);
	mgr->register_creature_script(CN_GATEWATCHER_IRON_HAND, &GatewatcherIronHandAI::Create);
	mgr->register_creature_script(CN_MECHANO_LORD_CAPACITUS, &MechanoLordCapacitusAI::Create);
	mgr->register_creature_script(CN_NETHERMANCER_SEPETHREA, &NethermancerSepethreaAI::Create);
	mgr->register_creature_script(CN_PATHALEON_THE_CALCULATOR, &PathaleonTheCalculatorAI::Create);
}
