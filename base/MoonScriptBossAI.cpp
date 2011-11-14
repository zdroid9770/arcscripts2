/*
 * Moon++ Scripts for Ascent MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptBossAI
MoonScriptBossAI::MoonScriptBossAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
{
	mPhaseIndex = -1;
	mEnrageSpell = NULL;
	mEnrageTimerDuration = -1;
	mEnrageTimer = INVALIDATE_TIMER;
};

MoonScriptBossAI::~MoonScriptBossAI()
{
	mPhaseSpells.clear();
};

SpellDesc* MoonScriptBossAI::AddPhaseSpell(int32 pPhase, SpellDesc* pSpell)
{
	mPhaseSpells.push_back(std::make_pair(pPhase, pSpell));
	return pSpell;
};

int32 MoonScriptBossAI::GetPhase()
{
	return mPhaseIndex;
};

void MoonScriptBossAI::SetPhase(int32 pPhase, SpellDesc* pPhaseChangeSpell)
{
	if(mPhaseIndex != pPhase)
	{
		//Cancel all spells
		CancelAllSpells();

		//Enable spells related to that phase
		for(PhaseSpellArray::iterator SpellIter = mPhaseSpells.begin(); SpellIter != mPhaseSpells.end(); ++SpellIter)
		{
			if(SpellIter->first == pPhase) SpellIter->second->mEnabled = true;
			else SpellIter->second->mEnabled = false;
		}

		//Remember phase index
		mPhaseIndex = pPhase;

		//Cast phase change spell now if available
		if(pPhaseChangeSpell) CastSpellNowNoScheduling(pPhaseChangeSpell);
	}
};

void MoonScriptBossAI::SetEnrageInfo(SpellDesc* pSpell, int32 pTriggerMilliseconds)
{
	mEnrageSpell = pSpell;
	mEnrageTimerDuration = pTriggerMilliseconds;
};

void MoonScriptBossAI::OnCombatStart(Unit* pTarget)
{
	SetPhase(1);
	if(mEnrageSpell && mEnrageTimerDuration > 0)
	{
		mEnrageTimer = AddTimer(mEnrageTimerDuration);
	}
	TriggerCooldownOnAllSpells();
	MoonScriptCreatureAI::OnCombatStart(pTarget);
};

void MoonScriptBossAI::OnCombatStop(Unit* pTarget)
{
	SetPhase(1);
	RemoveTimer(mEnrageTimer);
	MoonScriptCreatureAI::OnCombatStop(pTarget);
};

void MoonScriptBossAI::AIUpdate()
{
	if(mEnrageSpell && mEnrageTimerDuration > 0 && IsTimerFinished(mEnrageTimer))
	{
		CastSpell(mEnrageSpell);
		RemoveTimer(mEnrageTimer);
	}
	MoonScriptCreatureAI::AIUpdate();
};
