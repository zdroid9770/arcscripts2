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

/*
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
	Add_CREATURE_FACTORY_FUNCTION(PaletreesAI)
	PaletreesAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
	AddSpell(SPELL_HOLYSMITE, Target_RandomPlayer, 60, 0, 0);
	AddSpell(SPELL_HOLYNOVA, Target_Self, 40, 0, 10);
	AddSpell(SPELL_RENEW, Target_Self, 10, 0, 15);

	AddEmote(Event_OnCombatStart, "Well then, let us begin.", Text_Yell, 0); // Need sound ID
	AddEmote(Event_OnTargetDied, "Take your rest.", Text_Yell, 0); // Need sound ID
	AddEmote(Event_OnTargetDied, "Be at ease.", Text_Yell, 0); // Need sound ID
	}

	void AIUpdate()
	{
		if(GetPhase() == 1 && GetHealthPercent() <= 50)
		{
			_unit->CastSpell(_unit, SPELL_REFLECTSHIELD, true);
			Emote("Take this time to consider your past deeds.", Text_Yell, 0); // Need sound ID
			_unit->CastSpell(_unit, SPELL_CONFESS, false);
			SetPhase(2);
*/
 void SetupTrialOfChampionHold(ScriptMgr * mgr)
 {
 }
 