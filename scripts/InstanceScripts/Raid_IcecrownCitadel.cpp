/*
 * ArcScripts2 scripts for ArcEmu MMORPG Server
 * Copyright (C) 2011 ArcScripts2 Team
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
 
#include "setup.h"

enum IccEncounters
{
    ICC_LORD_MARROWGAR      = 0,
	ICC_LADY_DEATHWHISPER,
	ICC_GUNSHIP,
	ICC_SAURFANG,
	ICC_SINDRAGOSA,
	ICC_LICH_KING,
    ICC_END,
};

enum IcecrownCitadel
{
	GO_SCOURGE_TELEPORTER1		= 202242,
	GO_SCOURGE_TELEPORTER2		= 202243,
	GO_SCOURGE_TELEPORTER3		= 202244,
	GO_SCOURGE_TELEPORTER4		= 202245,
	GO_SCOURGE_TELEPORTER5		= 202235,
	GO_MARROWGAR_ENTRANCE		= 201857,
	GO_ICEBLOCK_1				= 201910,
	GO_ICEBLOCK_2				= 201911,
	GO_DAMMED_ENTRANCE			= 201563,
	GO_LADY_DEATHWISPER_ELEVATOR	= 202220,
	GO_SAURFANGS_DOOR			= 201825,
	GO_GREEN_PLAGUE_ENTRANCE	= 201370,
	GO_ORANGE_PLAGUE_ENTRANCE	= 201371,
	GO_SCIENTIST_AIRLOCK_DOOR_ORANGE = 201613,
	GO_SCIENTIST_ENTRANCE		= 201372,
	GO_CRIMSON_HALL_DOOR		= 201376,
	GO_BLOOD_ELF_COUNCIL_DOOR_L	= 201378,
	GO_BLOOD_ELF_COUNCIL_DOOR_R	= 201377,
	GO_GREEN_DRAGON_ENTRANCE	= 201375,
	GO_CACHE_OF_THE_DREAMWALKER	= 202339,
	GO_GREEN_DRAGON_BOSS_EXIT	= 201374,
	GO_SINDRAGOSA_ENTRANCE_DOOR	= 201373,
	GO_SINDRAGOSA_SHORTCUT_EXIT_DOOR = 201379,
	
	
	GO_BLOODWING_DOOR	= 201920,
	GO_FROSTWING_DOOR	= 201919
	
};

class IcecrownCitadelInstanceScript : public MoonInstanceScript
{
public:
	MOONSCRIPT_INSTANCE_FACTORY_FUNCTION(IcecrownCitadelInstanceScript, MoonInstanceScript);
	IcecrownCitadelInstanceScript(MapMgr* pMapMgr) : MoonInstanceScript(pMapMgr)
	{}

	void OnCreatureDeath(Creature* c, Unit* pUnit)
	{
		if(c->GetEntry() == 36612)
		{
			AddGameObjectStateByEntry(GO_MARROWGAR_ENTRANCE, State_Active);
			AddGameObjectStateByEntry(GO_ICEBLOCK_1, State_Active);
			AddGameObjectStateByEntry(GO_ICEBLOCK_2, State_Active);
			AddGameObjectStateByEntry(GO_DAMMED_ENTRANCE, State_Active);
		}
	}

	uint32 GetInstanceData(uint32 pType, uint32 pIndex)
	{
		return mEncounters[pIndex];
	}

	void SetInstanceData(uint32 pType, uint32 pIndex, uint32 pData)
	{
		if(pType != Data_EncounterState)
			return;

		if(pIndex >= ICC_END)
			return;

		switch(pIndex)
		{
			case ICC_LORD_MARROWGAR:
			{
				if(pData == State_InProgress)
					AddGameObjectStateByEntry(GO_MARROWGAR_ENTRANCE, State_Inactive);
				else if(pData == State_NotStarted)
					AddGameObjectStateByEntry(GO_MARROWGAR_ENTRANCE, State_Active);
			}break;
			default:
				break;
		}

		mEncounters[pIndex] = pData;
	}

protected:
	uint32 mEncounters[ICC_END];
};


enum TeleporterSpells
{
    LIGHT_S_HAMMER_TELEPORT         = 70781,
    ORATORY_OF_THE_DAMNED_TELEPORT  = 70856,
    RAMPART_OF_SKULLS_TELEPORT      = 70857,
    DEATHBRINGER_S_RISE_TELEPORT    = 70858,
    UPPER_SPIRE_TELEPORT            = 70859,
    FROZEN_THRONE_TELEPORT          = 70860,
    SINDRAGOSA_S_LAIR_TELEPORT      = 70861
};

class ScourgeTeleporterAI : public GameObjectAIScript
{
public:
	ScourgeTeleporterAI(GameObject* go) : GameObjectAIScript(go){}
	~ScourgeTeleporterAI() 
	{
	}
	static GameObjectAIScript* Create(GameObject* go) { return new ScourgeTeleporterAI(go); }

	void OnActivate(Player* player)
	{
		GossipMenu* menu = NULL;
		objmgr.CreateGossipMenuForPlayer(&menu, _gameobject->GetGUID(), 0, player);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Light's Hammer.", 0);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Oratory of the Damned.", 1);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Rampart of Skulls.", 2);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Deathbringer's Rise.", 3);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Upper Spire.", 4);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Sindragosa's Lair", 5);
		menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Frozen Throne", 6);
		menu->SendTo(player);
	}
};

class ScourgeTeleporterGossip : public GossipScript
{
public:
	ScourgeTeleporterGossip() : GossipScript(){}

	void OnSelectOption(Object* object, Player* player, uint32 Id, const char* enteredcode)
	{
		Arcemu::Gossip::Menu::Complete(player);
		switch(Id)
		{
			case 0: player->CastSpell(player, LIGHT_S_HAMMER_TELEPORT, true); break;
			case 1: player->CastSpell(player, ORATORY_OF_THE_DAMNED_TELEPORT, true); break;
			case 2: player->CastSpell(player, RAMPART_OF_SKULLS_TELEPORT, true); break;
			case 3: player->CastSpell(player, DEATHBRINGER_S_RISE_TELEPORT, true); break;
			case 4: player->CastSpell(player, UPPER_SPIRE_TELEPORT, true); break;
			case 5: player->CastSpell(player, ORATORY_OF_THE_DAMNED_TELEPORT, true); break;
			case 6: player->CastSpell(player, FROZEN_THRONE_TELEPORT, true); break;
		}
	}
};

uint32 MarrowgarSpells[6][4]=
{
	//10man 25man  10manhc 25manhc
	{47008,	47008, 47008, 47008},	//Berserk
	{69055, 70814, 69055, 70814},	//Bone Slice
	{69076, 69076, 69076, 69076},	//Bone Storm
	{69057, 70826, 69057, 70826},	//Bone Spike Graveyard
	{69140, 69140, 69140, 69140},	//ColdFlame normal (todo: added correct other difficulties entries)
	{72705, 72705, 72705, 72705}	//ColdFlame (bone storm phase) (todo: added correct other difficulties entries)
};

enum Spells
{
    // Bone Spike
	NPC_BONE_SPIKE              = 38711,
    SPELL_IMPALED               = 69065,
    SPELL_RIDE_VEHICLE          = 46598,

    // Coldflame
	NPC_COLD_FLAME				= 36672,
    SPELL_COLDFLAME_PASSIVE     = 69145,
    SPELL_COLDFLAME_SUMMON      = 69147
};

#define	MAX_COLDFLAMES_XFORM	20
class LordMarrowgar : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(LordMarrowgar, MoonScriptCreatureAI);
	LordMarrowgar(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		mInstance = GetInstanceScript();
		pMode = _unit->GetMapMgr()->iInstanceMode;
		if(pMode == NULL)
			return;

		Emote("This is the beginning AND the end, mortals. None may enter the master's sanctum!", Text_Yell, 16950);
		AddEmote(Event_OnCombatStart, "The Scourge will wash over this world as a swarm of death and destruction!", Text_Yell, 16941);
		AddEmote(Event_OnTargetDied, "More bones for the offering!", Text_Yell, 16942);
		AddEmote(Event_OnTargetDied, "Languish in damnation!", Text_Yell, 16943);
		AddEmote(Event_OnDied, "I see... only darkness...", Text_Yell, 16944);
		//normal phase
		sBoneSlice = AddSpell(MarrowgarSpells[1][pMode], Target_Current, 100.0f, 0, 1);
		sBoneSlice->mEnabled = false;	//should be casted after 10 seconds of encounter start
		AddSpell(MarrowgarSpells[4][pMode], Target_RandomPlayerNotCurrent, 100.0f, 0, rand()%6+6);
		SpellDesc* sBoneSpike = AddSpell(MarrowgarSpells[3][pMode], Target_Self, 100.0f, 0, rand()%17+10);
			sBoneSpike->AddEmote("Bound by bone!", Text_Yell, 16947);
			sBoneSpike->AddEmote("Stick Around!", Text_Yell, 16948);
			sBoneSpike->AddEmote("The only escape is death!", Text_Yell, 16949);

		//bone storm phase
		sBoneStorm = AddSpell(MarrowgarSpells[2][pMode], Target_Self, 0, 3, 0, 0, 0, false, "BONE STORM!", Text_Yell, 16946);

		ChargesMaxCount = 4;
		Phase=1;
		IsSpawnedColdFlameXForm = false;
		SetAllowMelee(true);	//melee damage should be replaced by Bone Slice after 10 sec
		sEnrage = AddSpell(MarrowgarSpells[0][pMode], Target_Self, 0, 0, 0, 0, 0, false, "THE MASTER'S RAGE COURSES THROUGH ME!", Text_Yell, 16945);	//10 min
	}

	void OnCombatStart(Unit* pUnit)
	{
		mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_InProgress);
		BoneStormTimer = AddTimer(30000);
		EnrageTimer = AddTimer(600000);	//10min
		BoneSliceTimer = AddTimer(10000);

		ParentClass::OnCombatStart(pUnit);
	}

	void OnCombatStop(Unit* mTarget)
	{
		mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_NotStarted);
		ParentClass::OnCombatStop(mTarget);
	}

	void SpawnColdFlameXForm()
	{
        float PosX = _unit->GetPositionX();
		float PosY = _unit->GetPositionY();
		float PosZ = _unit->GetPositionZ();
		float IncrValue = 5.0f;
		uint8 ColdFlameCount = 0;
		for(uint8 i = 0; i<MAX_COLDFLAMES_XFORM; i++)
		{
			SpawnCreature(NPC_COLD_FLAME, PosX+IncrValue, PosY, PosZ);
			SpawnCreature(NPC_COLD_FLAME, PosX, PosY+IncrValue, PosZ);
			SpawnCreature(NPC_COLD_FLAME, PosX-IncrValue, PosY, PosZ);
			SpawnCreature(NPC_COLD_FLAME, PosX, PosY-IncrValue, PosZ);
			IncrValue = IncrValue+5.0f;
			ColdFlameCount++;
		}
		
		if(ColdFlameCount == MAX_COLDFLAMES_XFORM)
		{
			RemoveAura(MarrowgarSpells[2][pMode]);	//BoneStorm
			ResetTimer(BoneStormTimer, 30000);
			ColdFlameCount = 0;
		}
	}

	void RandomChargeToUnit()
	{
		if(!IsSpawnedColdFlameXForm)
		{
			SpawnColdFlameXForm();
			IsSpawnedColdFlameXForm = true;
		}

		uint8 i = 0;
		while(i<ChargesMaxCount)
		{
			if(IsTimerFinished(ChargeTimer))
			{
				IsSpawnedColdFlameXForm = false;
				Unit* pTarget = GetBestUnitTarget(TargetFilter_ClosestNotCurrent);
				if(pTarget!=NULL)
				{
					ClearHateList();
					_unit->GetAIInterface()->setNextTarget(pTarget);
					_unit->GetAIInterface()->AttackReaction(pTarget, 100.0f);
				}
				ResetTimer(ChargeTimer, 3000);
				i++;
			}

			if(!_unit->HasAura(MarrowgarSpells[2][pMode]))	//BoneStorm
				i=ChargesMaxCount;
		}
	}

	void AIUpdate()
	{
		switch(Phase)
		{
			case 1:	//normal phase
			{
				if(IsTimerFinished(BoneStormTimer))
					Phase++;
			}break;
			case 2://preparation
			{
				SetAllowMelee(true);
				sBoneSlice->mEnabled = false;
				ClearHateList();
				RemoveAllAuras();
				SetBehavior(Behavior_Spell);
				CastSpellNowNoScheduling(sBoneStorm);
				_unit->SetSpeeds(RUN, 18.0f);
				Phase++;
			}break;
			case 3://BONE STORM!
			{
				ChargeTimer = AddTimer(4000);
				RandomChargeToUnit();
				if(!_unit->HasAura(MarrowgarSpells[2][pMode]))	//BoneStorm
				{
					_unit->SetSpeeds(RUN, 8.0f);
					SetBehavior(Behavior_Default);
					Phase=1;
					ResetTimer(BoneStormTimer, 30000);
					ResetTimer(BoneSliceTimer, 10000);
				}
			}break;
		}

		//ENRAGE!
		if(IsTimerFinished(EnrageTimer))
		{
			RemoveAllAuras();
			CastSpellNowNoScheduling(sEnrage);
		}

		if(IsTimerFinished(BoneSliceTimer) && !sBoneSlice->mEnabled)
		{
			SetAllowMelee(false);
			CastSpellNowNoScheduling(sBoneSlice);
			sBoneSlice->mEnabled = true;
		}

		ParentClass::AIUpdate();
	}

protected:
	SpellDesc *sBoneStorm, *sBoneStormStrike, *sEnrage, *sBoneSlice;
	uint32 EnrageTimer, BoneStormTimer, ChargeTimer, BoneSliceTimer;
	uint8 Phase, ChargesMaxCount, pMode;
    bool BoneStorm, IsSpawnedColdFlameXForm;
	MoonInstanceScript* mInstance;
};

void SetupIcecrownCitadel(ScriptMgr* mgr)
{
	mgr->register_instance_script(631, &IcecrownCitadelInstanceScript::Create);
	mgr->register_gameobject_script(202235, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip_script(202235, new ScourgeTeleporterGossip);
	mgr->register_gameobject_script(202223, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip_script(202223, new ScourgeTeleporterGossip);
	for(uint8 i = 0; i<4; i++)
	{
		mgr->register_gameobject_script(202242+i, &ScourgeTeleporterAI::Create);
		mgr->register_go_gossip(202242+i, new ScourgeTeleporterGossip);
	}

	mgr->register_creature_script(36612, &LordMarrowgar::Create);
}