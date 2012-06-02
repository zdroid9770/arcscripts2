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

#ifndef CREATURE_AI
#define CREATURE_AI


class SCRIPT_DECL CreatureAI : public CreatureAIScript
{
	public:
		explicit CreatureAI(Creature* pCreature);
		~CreatureAI(){}

		void					Emote(Unit* pUnit, const char* pText, uint8 pType, uint32 pSoundId, EmoteType pEmote = EMOTE_ONESHOT_NONE);

		Creature*				SummonCreature(Unit* pUnit, uint32 pEntry, float x, float y, float z, float o, uint32 DespawnTimr, uint8 Phase = 1);
		GameObject*				SummonGameobject(Unit* pUnit, uint32 pEntry, float x, float y, float z, float o, uint32 DespawnTimer, uint8 Phase = 1);
		//Unit*					GetTarget(TargetType Type);

		void					OnCombatStart(Unit* pTarget) override;
		void					OnCombatStop(Unit* pTarget) override;
		void					OnTargetDied(Unit* pTarget) override;
		void					OnDied(Unit* pKiller) override;
		void					AIUpdate() override;

	protected:
		uint32					mAIUpdateFrequency;
		uint32					mSpellsCount;
};

#endif CREATURE_AI
