
#include "Setup.h"
#include "System.h"

// Lnaguage structures and definitions
// thanks for mangos and sd2

static LanguageDesc lang_description[] =
{
    { LANG_UNIVERSAL,       0, 0                       },
    { LANG_ORCISH,        669, SKILL_LANG_ORCISH       },
    { LANG_DARNASSIAN,    671, SKILL_LANG_DARNASSIAN   },
    { LANG_TAURAHE,       670, SKILL_LANG_TAURAHE      },
    { LANG_DWARVISH,      672, SKILL_LANG_DWARVEN      },
    { LANG_COMMON,        668, SKILL_LANG_COMMON       },
    { LANG_DEMONIC,       815, SKILL_LANG_DEMON_TONGUE },
    { LANG_TITAN,         816, SKILL_LANG_TITAN        },
    //{ LANG_THALASSIAN,    813, SKILL_LANG_THALASSIAN   },
    { LANG_DRACONIC,      814, SKILL_LANG_DRACONIC     },
    { LANG_KALIMAG,       817, SKILL_LANG_OLD_TONGUE   },
    { LANG_GNOMISH,      7340, SKILL_LANG_GNOMISH      },
    { LANG_TROLL,        7341, SKILL_LANG_TROLL        },
    { LANG_GUTTERSPEAK, 17737, SKILL_LANG_GUTTERSPEAK  },
    { LANG_DRAENEI,     29932, SKILL_LANG_DRAENEI      }
};

LanguageDesc const* GetLanguageDescByID(uint32 lang)
{
    for(int i = 0; i < NUM_LANGUAGES; ++i)
    {
        if(uint32(lang_description[i].lang_id) == lang)
            return &lang_description[i];
    }

    return NULL;
}

//not sure, does it will look well with old moonscriptfunctions
void ArcScripts2::LoadScriptTexts()
{
    QueryResult* pResult = WorldDatabase.Query("SELECT entry, text, sound, type, language, emote FROM script_texts WHERE entry BETWEEN %i AND %i", TEXT_SOURCE_TEXT_END, TEXT_SOURCE_TEXT_START);
	if(!pResult)
	{
		LOG_ERROR("ArcScripts2: Loaded 0 additional Script Texts data. DB table `script_texts` is empty");
		return;
	}

	uint32 count = 0;

    do
    {
		Field* pFields = pResult->Fetch();
		if(!pFields)
		{
			LOG_ERROR("ArcScripts2: Wrong script_texts structure. Update it or report to devs!");
			return;
		}

		StringTextData pTemp;
		int32 iId           = pFields[0].GetInt32();
		pTemp.uiText        = pFields[1].GetString();
		pTemp.uiSoundId     = pFields[2].GetUInt32();
		pTemp.uiType        = pFields[3].GetUInt32();
		pTemp.uiLanguage    = pFields[4].GetUInt32();
		pTemp.uiEmote       = pFields[5].GetUInt32();

		if(pTemp.uiText == NULL)
		{
			LOG_ERROR("ArcScripts2: Entry %i in table `script_texts` text data can't be null", iId);
			continue;
		}

		if(iId >= 0)
		{
			LOG_ERROR("ArcScripts2: Entry %i in table `script_texts` is not a negative value.", iId);
			continue;
		}

        if(!GetLanguageDescByID(pTemp.uiLanguage))
            LOG_ERROR("ArcScripts2: Entry %i in table `script_texts` using Language %u but Language does not exist.", iId, pTemp.uiLanguage);

        /*if(pTemp.uiType > Text_Emote)
            LOG_ERROR("ArcScripts2: Entry %i in table `script_texts` has Type %u but this Chat Type does not exist.", iId, pTemp.uiType);
*/
        m_mTextDataMap[iId] = pTemp;
		count++;
    } while (pResult->NextRow());

    delete pResult;
    Log.Success("ArcScripts2:", "Loaded %u additional Script Texts data.", count);
}