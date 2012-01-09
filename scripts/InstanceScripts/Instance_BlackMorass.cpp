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

#define CN_CHRONO_LORD_DEJA 17879
 
#define ARCANE_BLAST		HeroicInt(38538, 31457)
#define TIME_LAPSE			31467
#define ARCANE_DISCHARGE	HeroicInt(38539, 31472)
#define ATTRACTION			38540

//"You have outstayed your welcome, Timekeeper. Begone!" 10413 text, when he starts fight with timekeeper
class ChronoLordDejaAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ChronoLordDejaAI, MoonScriptCreatureAI);
		ChronoLordDejaAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			Emote("Why do you aid the Magus? Just think of how many lives could be saved if the portal is never opened, if the resulting wars could be erased ...", Text_Yell, 10412);
			AddEmote(Event_OnCombatStart, "If you will not cease this foolish quest, then you will die!", Text_Yell, 10412);
			AddEmote(Event_OnTargetDied, "I told you it was a fool's quest!", Text_Yell, 10415);
			AddEmote(Event_OnTargetDied, "Leaving so soon?", Text_Yell, 10416);
			AddEmote(Event_OnDied, "Time ... is on our side.", Text_Yell, 10417);

			AddSpell(ARCANE_BLAST, Target_Current, 5.0f, 0, 10);
			AddSpell(TIME_LAPSE, Target_Current, 7.0f, 0, 8);
			AddSpell(ARCANE_DISCHARGE, Target_Self, 10.0f, 2, 8);

			if(IsHeroic())
				AddSpell(ATTRACTION, Target_Self, 11.0f, 0, 25);
		}
};

#define CN_TEMPORUS 17880

#define TEMPORUS_HASTEN			31458
#define TEMPORUS_WING_BUFFET	HeroicInt(38593, 31475)
#define TEMPORUS_MORTAL_WOUND	31464
#define TEMPORUS_REFLECT		38592

//"Time... sands of time is run out for you." 10443 when attacks keeper
class TemporusAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(TemporusAI, MoonScriptCreatureAI);
		TemporusAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			Emote("Why do you persist? Surely you can see the futility of it all. It is not too late! You may still leave with your lives ...", Text_Yell, 10442);
			AddEmote(Event_OnCombatStart, "So be it ... you have been warned.", Text_Yell, 10444);
			AddEmote(Event_OnTargetDied, "You should have left when you had the chance.", Text_Yell, 10445);
			AddEmote(Event_OnTargetDied, "Your days are done.", Text_Yell, 10446);
			AddEmote(Event_OnDied, "My death means ... little.", Text_Yell, 10447);

			AddSpell(TEMPORUS_HASTEN, Target_Self, 10.0f, 0, 10);
			AddSpell(TEMPORUS_MORTAL_WOUND, Target_Current, 8.0f, 0, 10);
			AddSpell(TEMPORUS_WING_BUFFET, Target_Self, 11.0f, 0, 20);
			
			if(IsHeroic())
				AddSpell(TEMPORUS_REFLECT, Target_Self, 13.0f, 0, 20);
		}
};

#define CN_AEONUS			17881
#define AEONUS_CLEAVE		40504
#define AEONUS_SAN_BREATH	HeroicInt(39049, 31473)
#define AEONUS_TIME_STOP	31422
#define AEONUS_ENRAGE		37605

class AeonusAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(AeonusAI, MoonScriptCreatureAI);
		AeonusAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			Emote("The time has come to shatter this clockwork universe forever! Let us no longer be slaves of the hourglass! I warn you: those who do not embrace the greater path shall become victims of its passing!", Text_Yell, 10400);
			AddEmote(Event_OnCombatStart, "Let us see what fate lays in store...", Text_Yell, 10402);
			AddEmote(Event_OnTargetDied, "One less obstacle in our way!", Text_Yell, 10403);
			AddEmote(Event_OnTargetDied, "No one can stop us! No one!", Text_Yell, 10404);
			AddEmote(Event_OnDied, "It is only a matter...of time.", Text_Yell, 10405);

			AddSpell(AEONUS_CLEAVE, Target_Current, 13.0f, 0, 15);
			AddSpell(AEONUS_SAN_BREATH, Target_Destination, 11.0f, 0, 15, 0, 20.0f);
			AddSpell(AEONUS_ENRAGE, Target_Self, 14.0f, 0, 20);
			AddSpell(AEONUS_TIME_STOP, Target_Self, 12.0f, 0, 25, 0, 50.0f);
		}
};

void SetupTheBlackMorass(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_CHRONO_LORD_DEJA, &ChronoLordDejaAI::Create);
	mgr->register_creature_script(CN_TEMPORUS, &TemporusAI::Create);
	mgr->register_creature_script(CN_AEONUS, &AeonusAI::Create);
}