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
	mAIUpdateFrequency = DEFAULT_UPDATE_FREQUENCY
}

void CreatureAI::Emote(Unit* pUnit, const char* pText, TextType pType, uint32 pSoundId, EmoteType pEmote)
{
	if(pText && strlen(pText) > 0)
	{
		switch(pType)
		{
			case Text_Say: pUnit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, pText, 0); break;
			case Text_Yell: pUnit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, pText, 0); break;
			case Text_Emote: pUnit->SendChatMessage(CHAT_MSG_MONSTER_EMOTE, LANG_UNIVERSAL, pText, 0); break;
			case Text_Announce: pUnit->SendChatMessage(CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, 0); break;
			default: sLog.outDebug("CreatureAI::Emote() : Invalid text type!"); break;
		}
	}

	if(pSoundId > 0)
			pUnit->PlaySoundToSet(pSoundId);

	if(pEmote != EMOTE_ONESHOT_NONE)
		pUnit->Emote(pEmote);
}

Creature* CreatureAI::SummonCreature(Unit* pUnit, uint32 pEntry, float x, float y, float z, float o, uint32 DespawnTimr, uint8 Phase)
{
	if(Creature * pCreature = pUnit->GetMapMgr()->GetInterface()->SpawnCreature(pEntry, x, y, z, o, false, true, 0, 0, Phase))
	{
		pCreature->Despawn(DespawnTimr, 0);
		return pCreature;
	}
	return NULL;
}

GameObject * CreatureAI::SummonGameobject(Unit* pUnit, uint32 pEntry, float x, float y, float z, float o, uint32 DespawnTimer, uint8 Phase)
{
	if(GameObject* pGameObject = pUnit->GetMapMgr()->GetInterface()->SpawnGameObject(pEntry, x, y, z, o, true, 0, Phase))
	{
		pGameObject->Despawn(DespawnTimer, 0);
		return pGameObject;
	}
	return NULL;
}


Unit* CreatureAI::GetTarget(Unit * pUnit, TargetType Type)
{
	switch(Type)
	{
		case TARGET_SELF:
		case TARGET_VARIOUS:
			return pUnit;
		case TARGET_ATTACKING:
		case TARGET_DESTINATION:
			return pUnit->GetAIInterface()->getNextTarget();
		case TARGET_RANDOM_SINGLE:
			{
				std::vector<Player* > TargetTable;
				for(set< Object* >::iterator itr = pUnit->GetInRangePlayerSetBegin(); itr != pUnit->GetInRangePlayerSetEnd(); ++itr)
				{
					Player* RandomTarget = TO< Player* >(*itr);
					if(RandomTarget && RandomTarget->isAlive())
						TargetTable.push_back(RandomTarget);
					RandomTarget = NULL;
				}

				if(!TargetTable.size())
					return NULL;

				Unit* RandomTarget = TargetTable[rand()%TargetTable.size()];

				if(!RandomTarget)
					return NULL;
				else
					return RandomTarget;
			}
		default:
			{
				sLog.Error("ArcScripts2", "Creature (%i) is trying to get invalid type target", pUnit->GetEntry());
				return NULL;
			}
	}
}

void CreatureAI::CastSpell(Unit* pUnit, Unit* pTarget, uint32 SpellId, bool Triggered)
{
	SpellEntry * pSpell = dbcSpell.LookupEntry(SpellId);
	if(!pSpell)
	{
		sLog.Error("ArcScripts2", "Creature (%i) is trying to cast non existing spell (%i)", pUnit->GetEntry(), SpellId);
		return;
	}

	pUnit->setAttackTimer(pUnit->GetCurrentSpell()->GetDuration(), false);
	pUnit->CastSpell(pTarget, pSpell, Triggered);
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
	if(!_unit->CombatStatus.IsInCombat())
		return;
}
