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

struct StringTextData
{
    uint32 Id;
	const char *Text;
    uint8  Type;
    uint32 SoundId;
    uint32 Emote;
};

struct WaypointsData
{
	uint32 entry;
	WayPoint * wpData;
};

#define pSystem ArcScripts2::Instance()

class ArcScripts2
{
	public:
		ArcScripts2(){}
		~ArcScripts2(){}

		static ArcScripts2& Instance()
		{
			static ArcScripts2 System;
			return System;
		}

		typedef std::map<uint32, std::vector<StringTextData>> TextDataMap;

        void LoadScriptTexts();

        //Retrive text data from storage
        std::vector<StringTextData> const &GetTextData(uint32 Entry) const
        {
            static std::vector<StringTextData> vEmpty;

            TextDataMap::const_iterator itr = mTextData.find(Entry);

            if (itr == mTextData.end())
                return vEmpty;

            return itr->second;
        }

		//Retrive specific text id data from storage
		StringTextData const * GetTextDataById(std::vector<StringTextData> Data, uint32 Id)
		{
			if(Data.empty())
				return NULL;

			for (std::vector<StringTextData>::const_iterator itr = Data.begin(); itr != Data.end(); ++itr)
			{
				if(itr->Id == Id)
				{
					StringTextData * TextData = NULL;
					TextData->Id = itr->Id;
					TextData->Text = itr->Text;
					TextData->Type = itr->Type;
					TextData->SoundId = itr->SoundId;
					TextData->Emote = itr->Emote;
					return TextData;
				}
			}
			return NULL;
		}

        TextDataMap	mTextData;                     //additional data for text strings
};

#endif
