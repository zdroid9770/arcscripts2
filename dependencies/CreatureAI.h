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

#ifndef MOON_SCRIPT_CREATURE_AI
#define MOON_SCRIPT_CREATURE_AI

enum TextType
{
    Text_Say,
    Text_Yell,
    Text_Emote,
	Max_Emote_type
};

enum MoveFlag
{
    Flag_Walk = 0,
    Flag_Run = 256,
    Flag_Fly = 768
};

struct Location
{
	float	x;
	float	y;
	float	z;
	float	o;
};

struct LocationExtra
{
	float	x;
	float	y;
	float	z;
	float	o;
	uint32	addition;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptCreatureAI
class SCRIPT_DECL MoonScriptCreatureAI : public CreatureAIScript
{
	public:
		explicit MoonScriptCreatureAI(Creature* pCreature);
		~MoonScriptCreatureAI()
		{
		}

		void					SetFacingToObject(Object * pObject);

		//Waypoints
		WayPoint*				CreateWaypoint(int pId, uint32 pWaittime, uint32 pMoveFlag, Location pCoords);
		WayPoint*				CreateWaypoint(int pId, uint32 pWaittime, uint32 pMoveFlag, LocationExtra pCoords);
		void					AddWaypoint(WayPoint* pWayPoint);

		void					OnCombatStart(Unit* pTarget) override;
		void					OnCombatStop(Unit* pTarget) override;
		void					OnTargetDied(Unit* pTarget) override;
		void					OnDied(Unit* pKiller) override;
		void					AIUpdate() override;

	protected:
		uint32					mAIUpdateFrequency;
};

#endif MOON_SCRIPT_CREATURE_AI
