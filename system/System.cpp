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
#include "System.h"

void ArcScripts2::LoadScriptTexts()
{
    QueryResult* pResult = WorldDatabase.Query("SELECT entry, id, text, type, sound, emote FROM script_texts");
	if(!pResult)
	{
		LOG_ERROR("ArcScripts2: Loaded 0 additional Script Texts data. DB table `script_texts` is empty. Scripts can work not correctly");
		return;
	}

	uint32 count = 0;

    do
    {
		Field* pFields = pResult->Fetch();
		StringTextData pTemp;
		uint32 Entry	= pFields[0].GetUInt32();	//npc entry
		pTemp.Id		= pFields[1].GetUInt32();	//Text id
		pTemp.Text		= pFields[2].GetString();	//Text
		pTemp.Type		= pFields[3].GetUInt32();	//Text type
		pTemp.SoundId	= pFields[4].GetUInt32();	//Sound id
		pTemp.Emote		= pFields[5].GetUInt32();	//Emote

		if(!CreatureNameStorage.LookupEntry(Entry))
		{
			LOG_ERROR("ArcScripts2: script text data exists in `script_texts` for non existing creature %i", Entry);
			continue;
		}

		if(pTemp.Text == "" && pTemp.Emote == 0)
		{
			LOG_ERROR("ArcScripts2: Entry %i, id %i in table `script_texts` has no text data", Entry, pTemp.Id);
			continue;
		}

		if(pTemp.Type >= Max_Emote_type)
		{
			LOG_ERROR("ArcScripts2: Entry %i id %i in table `script_texts` has wrong text type", Entry, pTemp.Id);
			continue;
		}

		mTextData[Entry].push_back(pTemp);
    } while (pResult->NextRow());

    delete pResult;
    Log.Success("ArcScripts2:", "Loaded %u additional Script Texts data.", count);
}
