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

CreatureAI::CreatureAI(Creature* pCreature) : CreatureAIScript(pCreature)
{
	mAIUpdateFrequency = DEFAULT_UPDATE_FREQUENCY;
}

CreatureAI::~CreatureAI()
{
}

void CreatureAI::Emote(Unit* pUnit, const char* pText, TextType pType, uint32 pSoundId, EmoteType pEmote, uint32 Time)
{
	if(pText && strlen(pText) > 0)
	{
		switch(pType)
		{
			case Text_Say: pUnit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, pText, Time); break;
			case Text_Yell: pUnit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, pText, Time); break;
			case Text_Emote: pUnit->SendChatMessage(CHAT_MSG_MONSTER_EMOTE, LANG_UNIVERSAL, pText, Time); break;
			case Text_Announce: pUnit->SendChatMessage(CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, pText); break;
			default: sLog.outDebug("CreatureAI::Emote() : Invalid text type!"); break;
		}
	}

	if(pSoundId > 0)
	{
		if(Time > 0)
			sEventMgr.AddEvent(TO_OBJECT(pUnit), &Object::PlaySoundToSet, (uint32)pSoundId, EVENT_UNK, Time, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		else
			pUnit->PlaySoundToSet(pSoundId);
	}

	if(pEmote != EMOTE_ONESHOT_NONE)
		pUnit->Emote(pEmote);
}


void CreatureAI::OnCombatStart(Unit* pTarget)
{
	RegisterAIUpdateEvent(mAIUpdateFrequency);
}

void CreatureAI::OnCombatStop(Unit* pTarget)
{
	RemoveAIUpdateEvent();
}

void CreatureAI::OnTargetDied(Unit* pTarget)
{
}

void CreatureAI::OnDied(Unit* pKiller)
{
	RemoveAIUpdateEvent();
}

void CreatureAI::AIUpdate()
{
	if(!IsInCombat())
		return;
}
