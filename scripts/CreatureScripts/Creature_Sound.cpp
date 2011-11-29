/*
 * WhyScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2010 WhyDB Team <http://www.whydb.org/>
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

class KingMagniBronzebeard : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(KingMagniBronzebeard)
	KingMagniBronzebeard(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit * mTarget)
	{
		GetUnit()->PlaySoundToSet(5896);
	}
};

class CairneBloodhoof : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(CairneBloodhoof)
	CairneBloodhoof(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit * mTarget)
	{
		GetUnit()->PlaySoundToSet(5884);
	}
};

class Thrall : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(Thrall)
	Thrall(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit * mTarget)
	{
		GetUnit()->PlaySoundToSet(5880);
	}
};

class TyrandeWhisperwind : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(TyrandeWhisperwind)
	TyrandeWhisperwind(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit * mTarget)
	{
		GetUnit()->PlaySoundToSet(5885);
	}
};

class LadySylvanasWindrunner : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(LadySylvanasWindrunner)
	LadySylvanasWindrunner(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit * mTarget)
	{
		GetUnit()->PlaySoundToSet(5886);
	}
};

class ProphetVelen : public CreatureAIScript
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(ProphetVelen)
	ProphetVelen(Creature *pCreature) : CreatureAIScript(pCreature) {}

	void OnCombatStart(Unit * mTarget)
	{
		GetUnit()->PlaySoundToSet(10155);
	}
};

void SetupSoundCreature(ScriptMgr * mgr)
{
	mgr->register_creature_script( 2784,  &KingMagniBronzebeard::Create );		// King Magni Bronzebeard
	mgr->register_creature_script( 3057,  &CairneBloodhoof::Create );			// Cairne Bloodhoof
	mgr->register_creature_script( 4949,  &Thrall::Create );					// Thrall
	mgr->register_creature_script( 7999,  &TyrandeWhisperwind::Create );		// Tyrande Whisperwind
	mgr->register_creature_script( 10181, &LadySylvanasWindrunner::Create );	// Lady Sylvanas Windrunner
	mgr->register_creature_script( 17468, &ProphetVelen::Create );				// Prophet Velen
}
