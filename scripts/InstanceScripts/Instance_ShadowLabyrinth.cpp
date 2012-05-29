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

// Ambassador HellmawAI

#define CN_AMBASSADOR_HELLMAW 18731

#define CORROSIVE_ACID 33551
#define AOE_FEAR 33547
// Help sound

class AMBASSADORHELLMAWAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(AMBASSADORHELLMAWAI)
		AMBASSADORHELLMAWAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(CORROSIVE_ACID, Target_Self, 10, 2, 15);
			AddSpell(AOE_FEAR, Target_Self, 15, 0, 25);
			AddEmote(Event_OnCombatStart, "Pathetic mortals! you will pay dearly!", Text_Yell, 10475); // http://www.wowwiki.com/Ambassador_Hellmaw
			AddEmote(Event_OnCombatStart, "I will break you!", Text_Yell, 10476); // http://www.wowwiki.com/Ambassador_Hellmaw 
			AddEmote(Event_OnCombatStart, "Finally, something to relieve the tedium.", Text_Yell, 10477); // http://www.wowwiki.com/Ambassador_Hellmaw
			AddEmote(Event_OnTargetDied, "Do you fear death?", Text_Yell, 10478); // http://www.wowwiki.com/Ambassador_Hellmaw
			AddEmote(Event_OnTargetDied, "This is the part I enjoy most...", Text_Yell, 10479); // http://www.wowwiki.com/Ambassador_Hellmaw
			AddEmote(Event_OnDied, "Do not... grow... overconfident, mortal.", Text_Yell, 10480); // http://www.wowwiki.com/Ambassador_Hellmaw
		}
};


// Blackheart the InciterAI

#define CN_BLACKHEART_THE_INCITER 18667

#define INCITE_CHAOS 33684 // 33684 or 33676?
#define CHARGE 39574 //39574 (HM) or 38461 // couldn't find more accurate
#define WAR_STOMP 33707
//#define AOE_KNOCKBACK 30056 // 30056, 37317 or 38576
// Help sound? And other (as there were sounds like _BlckHrt02_ (and I used only with 01)
// Is sound id 10488 for aggro or mind control?

class BLACKHEARTTHEINCITERAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BLACKHEARTTHEINCITERAI)
		BLACKHEARTTHEINCITERAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(CHARGE, Target_RandomPlayer, 10, 0, 15);
			AddSpell(WAR_STOMP, Target_Self, 10, 0, 20);
			//AddSpell(INCITE_CHAOS, Target_Self, 15, 0, 20);
			AddEmote(Event_OnCombatStart, "You'll be sorry!", Text_Yell, 10486);
			AddEmote(Event_OnCombatStart, "I see dead people!", Text_Yell, 10488); //http://www.wowwiki.com/Blackheart_the_Inciter
			AddEmote(Event_OnCombatStart, "Time for fun!", Text_Yell, 10487);
			AddEmote(Event_OnTargetDied, "No coming back for you!", Text_Yell, 10489); //http://www.wowwiki.com/Blackheart_the_Inciter
			AddEmote(Event_OnTargetDied, "Nice try!", Text_Yell, 10490);
			AddEmote(Event_OnDied, "This...no...good...", Text_Yell, 10491);//http://www.wowwiki.com/Blackheart_the_Inciter
		}
};

// Grandmaster VorpilAI

#define CN_GRANDMASTER_VORPIL 18732

#define SHADOW_BOLT_VOLLEY	33841
#define DRAW_SHADOWS		33563 // can't find it =/
#define RAIN_OF_FIRE		33617 // 33617 or 34360	// breaks model behavior
#define VOID_PORTAL_VISUAL	33569 // must work on that 33566
// Help sound and it's case?
// Should OnCombatStart should spawn 3 portals for Voidwalkers? (33569 ?)
/*The fight starts as soon as one of the players moves close enough
to Vorpil to aggro him. Vorpil will immediately open the Void Rifts
around him, and Voidwalkers will start spawning, at an increasingly
faster rate as the battle progresses.*/

class GRANDMASTERVORPILAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(GRANDMASTERVORPILAI)
		GRANDMASTERVORPILAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddSpell(SHADOW_BOLT_VOLLEY, Target_Self, 15, 0, 10);
			AddSpell(DRAW_SHADOWS, Target_Self, 8, 0, 25);
			AddSpell(RAIN_OF_FIRE, Target_Destination, 8, 7, 25);

			AddEmote(Event_OnCombatStart, "I'll make an offering of your blood.", Text_Yell, 10524);//http://www.wowwiki.com/Grandmaster_Vorpil
			AddEmote(Event_OnCombatStart, "You'll be a fine examplemfor the others.", Text_Yell, 10525);//http://www.wowwiki.com/Grandmaster_Vorpil
			AddEmote(Event_OnCombatStart, "Good! a worthy sacrifice.", Text_Yell, 10526);//http://www.wowwiki.com/Grandmaster_Vorpil
			AddEmote(Event_OnTargetDied, "I serve with pride!", Text_Yell, 10527);//http://www.wowwiki.com/Grandmaster_Vorpil
			AddEmote(Event_OnTargetDied, "Your death is for the greater cause!", Text_Yell, 10528);
			AddEmote(Event_OnDied, "I give my life... gladly...", Text_Yell, 10529);//http://www.wowwiki.com/Grandmaster_Vorpil
		}
};

// MurmurAI

#define CN_MURMUR 18708

#define SHOCKWAVE			33686	// 25425
#define MURMURS_TOUCH		33711
#define SONIC_BOOM1			33923	// anything missed? additional dmging spell?
#define SONIC_BOOM2			33666
#define RESONANCE			33657	// should be applied only when no target in melee combat range (each 5 sec)

/*#define THUNDERING_STORM 39365

#define SUPPRESSION_BLAST 33332*/
// #define SONIC_BOOM 33666
// 33666 or 38795 (I think it's dummy (33923); it should be connected with Murmur's Touch; Murmur should say
// Murmur draws energy from the air then use Murmur's Touch (33711), Sonic Boom (33923) and
// release Sonic Boom (38052); it also shouldn't attack during all those casts;

class MURMURAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(MURMURAI);
		MURMURAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			_unit->SetHealthPct(40);
			AddSpell(SONIC_BOOM1, Target_Self, 10, 7, 25, 0, 0, false, NULL, Text_Emote, 0, "Murmur draws energy from the air...");
			AddSpell(SHOCKWAVE, Target_Self, 6, 0, 15);
			AddSpell(MURMURS_TOUCH, Target_Self, 10, 1, 20);
			//AddSpell(RESONANCE, Target_Self, 0, 0, 5);
		}
};

void SetupShadowLabyrinth(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_AMBASSADOR_HELLMAW, &AMBASSADORHELLMAWAI::Create);
	mgr->register_creature_script(CN_BLACKHEART_THE_INCITER, &BLACKHEARTTHEINCITERAI::Create);
	mgr->register_creature_script(CN_GRANDMASTER_VORPIL, &GRANDMASTERVORPILAI::Create);
	mgr->register_creature_script(CN_MURMUR, &MURMURAI::Create);
}
