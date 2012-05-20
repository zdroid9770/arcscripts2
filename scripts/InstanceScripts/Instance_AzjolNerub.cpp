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

/* To-Do:
	Finish Kritkhir Encounter, needs more blizzlike, may need InstanceScript
	Anuburak
	Add's AI and trash
*/

#include "Setup.h"

//Krikthir The Gatewatcher BOSS
#define BOSS_KRIKTHIR 28684

#define KRIKTHIR_MINDFLAY HeroicInt(59367, 52586)
#define KRIKTHIR_CURSEOFFATIGUE HeroicInt(59368, 52592)
#define KRIKTHIR_ENRAGE 28747

class KrikthirAI : public MoonScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KrikthirAI)
	KrikthirAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddEmote(Event_OnCombatStart, "This kingdom belongs to the Scourge! Only the dead may enter.", Text_Yell, 14075);
		AddEmote(Event_OnTargetDied, "You were foolish to come.", Text_Yell, 14077);
		AddEmote(Event_OnTargetDied, "As Anub'Arak commands!", Text_Yell, 14078);
		AddEmote(Event_OnDied, "I should be grateful. But I long ago lost the capacity.", Text_Yell, 14087);

		AddSpell(KRIKTHIR_CURSEOFFATIGUE, Target_Self, 100, 0, 10);
		AddSpell(KRIKTHIR_MINDFLAY, Target_RandomPlayer, 100, 0, 7, 0, 30);

		mEnraged = false;
	}

	void AIUpdate()
	{
		if(GetHealthPercent() <= 10 && !mEnraged)
		{
			ApplyAura(KRIKTHIR_ENRAGE);
			mEnraged = true;
		}
	}

	void OnDied(Unit* pKiller)
	{
		GameObject* Doors = GetNearestGameObject(192395);
		if(Doors != NULL)
			Doors->SetState(GAMEOBJECT_STATE_OPEN);
	}

protected:
	bool mEnraged;
};

//boss Hadronox
#define BOSS_HADRONOX 28921
#define HADRONOX_WEBGRAB HeroicInt(59421, 53406)
#define HADRONOX_PIERCEARMOR HeroicInt(59417, 53418)
#define HADRONOX_LEECHPOISON HeroicInt(59419, 53030)
#define HADRONOX_ACIDCLOUD 53400

class HadronoxAI : public MoonScriptCreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(HadronoxAI)
	HadronoxAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		AddSpell(HADRONOX_WEBGRAB, Target_RandomPlayer, 22.0f, 0, 14);
		AddSpell(HADRONOX_LEECHPOISON, Target_Self, 14.0f, 0, 25, 0, 20);
		AddSpell(HADRONOX_ACIDCLOUD, Target_RandomPlayer, 18.0f, 0, 20, 0, 60);
		AddSpell(HADRONOX_PIERCEARMOR, Target_ClosestPlayer, 20.0f, 0, 5);
	}

	void OnTargetDied(Unit* pTarget)
	{
		if(pTarget!=NULL && pTarget->HasAura(HADRONOX_LEECHPOISON) && IsAlive())
			_unit->SetHealthPct(_unit->GetHealthPct()+10.0f);
	}
};

void SetupAzjolNerub(ScriptMgr* mgr)
{
	//Bosses
	mgr->register_creature_script(BOSS_KRIKTHIR, &KrikthirAI::Create);
	mgr->register_creature_script(BOSS_HADRONOX, &HadronoxAI::Create);
}
