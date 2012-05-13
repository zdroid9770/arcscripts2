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

#define DISEASE_CLOUD	12627
#define FRENZY			12795

class Glutton : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(Glutton, MoonScriptCreatureAI);
		Glutton(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			//spells
			mDiseaseCloud = AddSpell(DISEASE_CLOUD, Target_Self, 0, 0, 0, 0, 0);
			mFrenzy = AddSpell(FRENZY, Target_Self, 10, 0, 20, 0, 0);
			mFrenzy->AddEmote("Glutton is getting hungry!", Text_Yell);
		}

		void OnCombatStart(Unit* pTarget)
		{
			CastSpellNowNoScheduling(mDiseaseCloud);

			ParentClass::OnCombatStart(pTarget);
		}

	private:
		SpellDesc*      mDiseaseCloud;
		SpellDesc*      mFrenzy;
};

void SetupRazorfenDowns(ScriptMgr* mgr)
{
	mgr->register_creature_script(8567, &Glutton::Create);
}