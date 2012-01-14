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

#ifndef SC_SYSTEM_H
#define SC_SYSTEM_H

#define TEXT_SOURCE_RANGE -1000000                          //the amount of entries each text source has available
#define TEXT_SOURCE_TEXT_START      TEXT_SOURCE_RANGE
#define TEXT_SOURCE_TEXT_END        TEXT_SOURCE_RANGE*2 + 1

struct StringTextData
{
	const char *uiText;
    uint8  uiType;
    uint32 uiSoundId;
    uint32 uiEmote;
};

class ArcScripts2 : public ThreadBase
{
	public:
		ArcScripts2();
		~ArcScripts2();

		typedef std::unordered_map<uint32, StringTextData> TextDataMap;

		bool run();
        void LoadScriptTexts();

        //Retrive from storage
        StringTextData const* GetTextData(int32 uiTextId) const;

        TextDataMap	m_mTextDataMap;                     //additional data for text strings
};

#endif
