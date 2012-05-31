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

void mOnEmote(Player *pPlayer, uint32 Emote, Unit *pUnit)
{
	if(!pUnit || pUnit->IsDead() || pUnit->CombatStatus.IsInCombat() || !pUnit->GetAIInterface())
		return;

	switch(Emote)
	{
		case EMOTE_ONESHOT_SALUTE:
		case EMOTE_ONESHOT_WAVE:
		case EMOTE_ONESHOT_KISS:
			if(pUnit->GetAIInterface()->m_isGuard)
			{
				if(Emote == EMOTE_ONESHOT_KISS)
					Emote = EMOTE_ONESHOT_BOW;

				if(RandomUInt(100) <= 33 && pPlayer->GetStandingRank( pUnit->m_factionDBC->ID ) >= STANDING_FRIENDLY)
					pUnit->Emote(static_cast<EmoteType>(Emote));
			}
			break;
	}
}

void SetupEmoteCreatures(ScriptMgr * mgr)
{
	mgr->register_hook(SERVER_HOOK_EVENT_ON_EMOTE, &mOnEmote);
}
