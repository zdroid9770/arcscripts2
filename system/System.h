/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
* This program is free software licensed under GPL version 2
* Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_SYSTEM_H
#define SC_SYSTEM_H

#define TEXT_SOURCE_RANGE -1000000                          //the amount of entries each text source has available
#define TEXT_SOURCE_TEXT_START      TEXT_SOURCE_RANGE
#define TEXT_SOURCE_TEXT_END        TEXT_SOURCE_RANGE*2 + 1

struct StringTextData
{
    uint32 uiSoundId;
	const char *uiText;
    uint8  uiType;
    uint32 uiLanguage;
    uint32 uiEmote;
};

struct LanguageDesc
{
    Languages lang_id;
    uint32   spell_id;
    uint32   skill_id;
};

class ArcScripts2 : public ThreadBase
{
	public:
		ArcScripts2(){}
		~ArcScripts2(){}

		bool run()
		{
			Log.Success("ArcScripts2","");
			Log.Success("ArcScripts2","");
			Log.Success("ArcScripts2", "Engine has Started");
			LoadScriptTexts();
			Log.Success("ArcScripts2","");
			Log.Success("ArcScripts2","");
			return true;
		}

		typedef std::unordered_map<uint32, StringTextData> TextDataMap;

        //Database
        void LoadScriptTexts();

        //Retrive from storage
        StringTextData const* GetTextData(int32 uiTextId) const
        {
            TextDataMap::const_iterator itr = m_mTextDataMap.find(uiTextId);

            if (itr == m_mTextDataMap.end())
                return NULL;

            return &itr->second;
        }

    protected:
        TextDataMap     m_mTextDataMap;                     //additional data for text strings
};

#endif
