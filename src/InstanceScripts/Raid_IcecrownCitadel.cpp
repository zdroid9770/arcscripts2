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
	{
		BuildEncounterMap();

	}

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

uint32 MarrowgarSpells[2][4]=
{
	{69055, 70814, 69055, 70814},	//Bone Slice
	{69057, 70826, 69057, 70826}	//Bone Spike Graveyard
};

#define	SPELL_BERSERK	47008
#define SPELL_BONE_STORM_STRIKE	69075
#define	SPELL_BONE_STORM	69076
#define	SPELL_COLD_FLAME	69146
#define	SPELL_CALL_COLD_FLAME	69138
#define NPC_BONE_SPIKE	38711
#define NPC_COLD_FLAME	36672

#define	MAX_COLDFLAMES_XFORM	20
class LordMarrowgar : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(LordMarrowgar, MoonScriptBossAI);
	LordMarrowgar(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		mInstance = GetInstanceScript();
		uint8 pMode = _unit->GetMapMgr()->iInstanceMode;

		Emote("This is the beginning AND the end, mortals. None may enter the master's sanctum!", Text_Yell, 16950);
		AddEmote(Event_OnCombatStart, "The Scourge will wash over this world as a swarm of death and destruction!", Text_Yell, 16941);
		AddEmote(Event_OnTargetDied, "More bones for the offering!", Text_Yell, 16942);
		AddEmote(Event_OnTargetDied, "Languish in damnation!", Text_Yell, 16943);
		AddEmote(Event_OnDied, "I see... only darkness...", Text_Yell, 16944);

		//both phases
		AddSpell(SPELL_CALL_COLD_FLAME, Target_Self, 20.0f, 0, 5);

		/*SpellDesc* sBoneSpike = AddSpell(MarrowgarSpells[1][pMode], Target_RandomPlayer, 20.0f, 0, 30);
			sBoneSpike->AddEmote("Bound by bone!", Text_Yell, 16947);
			sBoneSpike->AddEmote("Stick Around!", Text_Yell, 16948);
			sBoneSpike->AddEmote("The only escape is death!", Text_Yell, 16949);*/

		//normal phase
		AddPhaseSpell(1, AddSpell(MarrowgarSpells[0][pMode], Target_Current, 20.0f, 0, -1));
		AddPhaseSpell(1, AddSpell(SPELL_COLD_FLAME, Target_Self, 20.0f, 0, -1));

		//bone storm phase
		sBoneStorm = AddSpell(SPELL_BONE_STORM, Target_RandomPlayer, 0, 3, 0, 0, 0, false, "BONE STORM!", Text_Yell, 16946);
		AddPhaseSpell(2, AddSpell(SPELL_BONE_STORM_STRIKE, Target_Self, 100.0f, 0, -1));

		ChargesMaxCount = 4;
		SetPhase(1);

		SetEnrageInfo(AddSpell(SPELL_BERSERK, Target_Self, 0, 0, 0, 0, 0, false, "THE MASTER'S RAGE COURSES THROUGH ME!", Text_Yell, 16945), 10*60*1000);	//10 min
	}

	void OnCombatStart(Unit* pUnit)
	{
		mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_InProgress);
		BoneStormTimer = AddTimer(30000);
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
			RemoveAura(SPELL_BONE_STORM_STRIKE);
			RemoveAura(SPELL_BONE_STORM);
			ResetTimer(BoneStormTimer, 30000);
		}
	}

	void AIUpdate()
	{
		if(IsTimerFinished(BoneStormTimer))
		{
			ClearHateList();
			SetBehavior(Behavior_Spell);
			CastSpell(sBoneStorm);
			_unit->SetSpeeds(RUN, 18.0f);
			SetPhase(2);
			ChargeTimer = AddTimer(4000);

			//Charges part
			if(!IsSpawnedXForm)
			{
				SpawnColdFlameXForm();
				IsSpawnedXForm = true;
			}

			uint8 i = 0;
			while(i<ChargesMaxCount)
			{
				if(IsTimerFinished(ChargeTimer))
				{
					IsSpawnedXForm = false;
					Unit* pTarget = GetBestUnitTarget();
					if(pTarget!=NULL)
					{
						ClearHateList();
						_unit->GetAIInterface()->setNextTarget(pTarget);
						_unit->GetAIInterface()->AttackReaction(pTarget, 100.0f);
					}
					ResetTimer(ChargeTimer, 3000);
					i++;
				}
					
				if(!_unit->HasAura(SPELL_BONE_STORM))
					i=ChargesMaxCount;
			}

			ResetTimer(BoneStormTimer, 45000);
		}

		if(!_unit->HasAura(SPELL_BONE_STORM))
		{
			_unit->SetSpeeds(RUN, 8.0f);
			SetBehavior(Behavior_Default);
			SetPhase(1);
		}
		ParentClass::AIUpdate();
	}

protected:
	SpellDesc* sBoneStorm, *sBoneStormStrike;
	uint32 BoneStormTimer, ChargeTimer;
	uint8 ChargesMaxCount;
    bool BoneStorm, IsSpawnedXForm;
	MoonInstanceScript* mInstance;
};

static Location PortalLoc[7][4]=
{
	{-17.1928f, 2211.44f, 30.1158f,3.14f}, //
	{-503.62f, 2211.47f, 62.8235f,3.14f},  //
	{-615.145f, 2211.47f, 199.972f,0}, //
	{-549.131f, 2211.29f, 539.291f,0}, //
	{4198.42f, 2769.22f, 351.065f,0}, //
	{4356.580078f, 2565.75f, 220.401993f,4.90f}, //
	{528.767273f, -2124.845947f, 1043.1f,3.14f}
};

class ScourgeTeleporterAI : public GameObjectAIScript
{
public:
	ScourgeTeleporterAI(GameObject* go) : GameObjectAIScript(go){}
	~ScourgeTeleporterAI() {}
	static GameObjectAIScript* Create(GameObject* go) { return new ScourgeTeleporterAI(go); }

	void OnActivate(Player* player)
	{
		Arcemu::Gossip::Menu menu(_gameobject->GetGUID(), 0);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Oratory of the Damned.", 0);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Light's Hammer.", 1);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Rampart of Skulls.", 2);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Deathbringer's Rise.", 3);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Upper Spire.", 4);
		menu.AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Sindragosa's Lair", 5);
		menu.Send(player);
	}
};

class ScourgeTeleporterGossip : public GossipScript
{
public:
	ScourgeTeleporterGossip() : GossipScript(){}

	void OnSelectOption(Object* object, Player* player, uint32 Id, const char* enteredcode)
	{
		Arcemu::Gossip::Menu::Complete(player);

		if(Id >= 7)
			return;
		else
			player->SafeTeleport(631, player->GetInstanceID(), PortalLoc[Id][0].x, PortalLoc[Id][1].y,  PortalLoc[Id][2].z, PortalLoc[Id][3].o);
	}
};

void SetupIcecrownCitadel(ScriptMgr* mgr)
{
	mgr->register_instance_script(631, &IcecrownCitadelInstanceScript::Create);
	mgr->register_creature_script(36612, &LordMarrowgar::Create);

	for(uint8 i = 0; i<4; i++)
	{
		mgr->register_gameobject_script(202242+i, &ScourgeTeleporterAI::Create);
		mgr->register_go_gossip(202242+i, new ScourgeTeleporterGossip());
	}

	mgr->register_gameobject_script(202235, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip(202235, new ScourgeTeleporterGossip());
}