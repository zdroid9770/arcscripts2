/*
 * ArcScripts for ArcEmu MMORPG Server
 * Copyright (C) 2009 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
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

class AmbassadorFlamelash : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(BaronAquanisAI, MoonScriptCreatureAI);
		BaronAquanisAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SummonTimer = INVALIDATE_TIMER;
		}

		void OnCombatStart(Unit* mTarget)
		{
			SummonTimer = AddTimer(24000);
			ParentClass::OnCombatStart(mTarget);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(SummonTimer))
			{
				for(uint8 i = 0; i<4; i++)
				{
					MoonScriptCreatureAI* pSummon = SpawnCreature(9178, _unit->GetPositionX()-rand()%10, _unit->GetPositionY()-rand()%10, _unit->GetPositionZ(), 0);
					if(pSummon!=NULL)
						pSummon->MoveTo(_unit);

					pSummon = NULL;
				}
				ResetTimer(SummonTimer, 30000);
			}
			ParentClass::AIUpdate();
		}
	
	protected:
		int32 SummonTimer;
};

void SetupBlackrockDepths(ScriptMgr* mgr)
{
	mgr->register_creature_script(9156, &AmbassadorFlamelash::Create);
}