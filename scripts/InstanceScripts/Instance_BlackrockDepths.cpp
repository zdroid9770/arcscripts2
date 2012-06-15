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

class AmbassadorFlamelash : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(AmbassadorFlamelash)
		AmbassadorFlamelash(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SummonTimer = INVALIDATE_TIMER;
		}

		void OnCombatStart(Unit* mTarget)
		{
			SummonTimer = AddTimer(24000);
			MoonScriptCreatureAI::OnCombatStart(mTarget);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(SummonTimer))
			{
				for(uint8 i = 0; i<4; i++)
				{
					MoonScriptCreatureAI* pSummon = SpawnCreature(9178, _unit->GetPositionX()-rand()%10, _unit->GetPositionY()-rand()%10, _unit->GetPositionZ(), 0);
					if(pSummon != NULL)
					{
						pSummon->MoveTo(_unit);
						pSummon->SetDespawnWhenInactive(true);
					}

					pSummon = NULL;
				}
				ResetTimer(SummonTimer, 30000);
			}
			MoonScriptCreatureAI::AIUpdate();
		}
	
	protected:
		int32 SummonTimer;
};

void SetupBlackrockDepths(ScriptMgr* mgr)
{
	mgr->register_creature_script(9156, &AmbassadorFlamelash::Create);
}