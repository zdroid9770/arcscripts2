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
 
#include "setup.h"
#define MAP_ICC	631

enum IccEncounters{
    ICC_LORD_MARROWGAR      = 0,
	ICC_LADY_DEATHWHISPER,
	ICC_GUNSHIP,
	ICC_SAURFANG,
	ICC_SINDRAGOSA,
	ICC_LICH_KING,
    ICC_END
};

enum IcecrownCitadel_Creatures{
	NPC_LICH_KING				= 36597,
	NPC_LORD_MARROWGAR			= 36612,
	NPC_FESTERGUT				= 36626,
	NPC_ROTFACE					= 36627,
	NPC_PROFESSOR_PUTRICIDE		= 36678,
	NPC_VALITRA_DREAMWALKER		= 36789,
	NPC_SINDRAGOSA				= 36853,
	NPC_LADY_DEATHWHISPER		= 36855,
	NPC_DEATHBRINGER_SAURFANG	= 37813,
	NPC_BLOOD_QUEEN_LANATHEL	= 37955,
	NPC_PRINCE_VALANAR			= 37970
};

enum IcecrownCitadel_GameObjects{
	GO_SCIENTIST_AIRLOCK_DOOR_GREEN	= 201614,
	GO_OOZE_RELEASE_VALVE		= 201615,
	GO_GAS_RELEASE_VALVE		= 201616,
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
		IcecrownCitadelInstanceScript(MapMgr* pMapMgr) : MoonInstanceScript(pMapMgr){}

		void OnPlayerEnter(Player* pPlayer)
		{
			pPlayer->CastSpell(pPlayer, 69127, true);	//chill of throne
		}

		void OnCreatureDeath(Creature* c, Unit* pUnit)
		{
			switch(c->GetEntry())
			{
				case NPC_LORD_MARROWGAR :
				{
					AddGameObjectStateByEntry(GO_MARROWGAR_ENTRANCE, State_Active);
					AddGameObjectStateByEntry(GO_ICEBLOCK_1, State_Active);
					AddGameObjectStateByEntry(GO_ICEBLOCK_2, State_Active);
					AddGameObjectStateByEntry(GO_DAMMED_ENTRANCE, State_Active);
				}break;
				case NPC_ROTFACE : 
				{
					GameObject * pGo1 = FindClosestGameObjectOnMap(GO_OOZE_RELEASE_VALVE, 4432.27f, 3090.88f, 362.253f);
					if(pGo1 != NULL)
						pGo1->SetFlags(0);
				}break;
				case NPC_FESTERGUT : 
				{
					GameObject * pGo2 = FindClosestGameObjectOnMap(GO_GAS_RELEASE_VALVE, 4280.84f, 3090.88f, 362.335f);
					if(pGo2 != NULL)
						pGo2->SetFlags(0);
				}break;
				default : 
					break;
			}
		}

		void OnGameObjectActivate(GameObject* pGO, Player* pPlayer)
		{
			switch(pGO->GetEntry())
			{
				case GO_OOZE_RELEASE_VALVE :
				{
					pGO->SetState(State_Active);
					AddGameObjectStateByEntry(GO_SCIENTIST_AIRLOCK_DOOR_GREEN, State_Active);
					pGO->SetFlags(16);
					RegisterScriptUpdateEvent();
				}break;
				case GO_GAS_RELEASE_VALVE :
				{
					pGO->SetState(State_Active);
					AddGameObjectStateByEntry(GO_SCIENTIST_AIRLOCK_DOOR_ORANGE, State_Active);
					pGO->SetFlags(16);
					RegisterScriptUpdateEvent();
				}break;
				default:
					break;
			}
		}

		void UpdateEvent()
		{
			GameObject * pGO1 = FindClosestGameObjectOnMap(GO_OOZE_RELEASE_VALVE, 4432.27f, 3090.88f, 362.253f);
			if(pGO1 == NULL)
				return;

			GameObject * pGO2 = FindClosestGameObjectOnMap(GO_GAS_RELEASE_VALVE, 4280.84f, 3090.88f, 362.335f);
			if(pGO2 == NULL)
				return;

			if((pGO1->GetState() == State_Active) && (pGO2->GetState() == State_Active))
				AddGameObjectStateByEntry(GO_SCIENTIST_ENTRANCE, State_Active);
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



enum TeleporterSpells{
    LIGHT_S_HAMMER_TELEPORT         = 70781,
    ORATORY_OF_THE_DAMNED_TELEPORT  = 70856,
    RAMPART_OF_SKULLS_TELEPORT      = 70857,
    DEATHBRINGER_S_RISE_TELEPORT    = 70858,
    UPPER_SPIRE_TELEPORT            = 70859,
    FROZEN_THRONE_TELEPORT          = 70860,
    SINDRAGOSA_S_LAIR_TELEPORT      = 70861
};

static LocationExtra ScourgeTelePos[7]=
{
	{-17.1928f, 2211.44f, 30.1158f, 3.14f, LIGHT_S_HAMMER_TELEPORT},
	{-503.62f, 2211.47f, 62.8235f, 3.14f, ORATORY_OF_THE_DAMNED_TELEPORT},
	{-615.145f, 2211.47f, 199.972f, 0, RAMPART_OF_SKULLS_TELEPORT},
	{-549.131f, 2211.29f, 539.291f, 0, DEATHBRINGER_S_RISE_TELEPORT},
	{4198.42f, 2769.22f, 351.065f, 0, UPPER_SPIRE_TELEPORT},
	{4356.580078f, 2565.75f, 220.401993f, 4.90f, SINDRAGOSA_S_LAIR_TELEPORT},
	{528.767273f, -2124.845947f, 1043.1f, 3.14f, FROZEN_THRONE_TELEPORT}
};

class ScourgeTeleporterAI : public GameObjectAIScript
{
	public:
		ADD_GAMEOBJECT_FACTORY_FUNCTION(ScourgeTeleporterAI)
		ScourgeTeleporterAI(GameObject* go) : GameObjectAIScript(go){}
		~ScourgeTeleporterAI() {}

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
			if(Id > 6)
				return;

			Arcemu::Gossip::Menu::Complete(player);
			player->CastSpell(player, ScourgeTelePos[Id].addition, true);
			player->SafeTeleport(MAP_ICC, player->GetInstanceID(), ScourgeTelePos[Id].x, ScourgeTelePos[Id].y,  ScourgeTelePos[Id].z, ScourgeTelePos[Id].o);
		}
};

enum MarrowgarSpells
{
	SPELL_LM_BERSERK		= 47008,
	SPELL_BONE_SLICE		= 69055,
	SPELL_BONE_STORM		= 69076,
	SPELL_BONE_STORM_EFFECT	= 69075,
	SPELL_BONE_SPIKE		= 69057,
	SPELL_COLDFLAME			= 69140,
	SPELL_COLDFLAME_BONESTORM	= 72705
};

enum LM_Summons
{
	MAX_COLDFLAMES_XFORM	= 20,
    NPC_BONE_SPIKE			= 38711,
    NPC_COLD_FLAME			= 36672
};

class LordMarrowgar : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(LordMarrowgar, MoonScriptBossAI);
		LordMarrowgar(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			mInstance = GetInstanceScript();
			switch(GetInstanceMode())
			{
				case MODE_NORMAL_10MEN : _unit->SetHealth(6972500); break;
				case MODE_NORMAL_25MEN : _unit->SetHealth(23706500); break;
				case MODE_HEROIC_10MEN : _unit->SetHealth(10458750); break;
				case MODE_HEROIC_25MEN : _unit->SetHealth(31376250); break;
				default :
					break;
			}

			Reset();

			//Bone Storm!
			sBoneStorm = AddSpell(SPELL_BONE_STORM, Target_Self, 0, 3, 0, 0, 0, false, "BONE STORM!", Text_Yell, 16946, "Lord Marrowgar creates a whirling of bone!");
			AddPhaseSpell(2, AddSpell(SPELL_COLDFLAME_BONESTORM, Target_Self, 100.0f, 0, 5));

			SetEnrageInfo(AddSpell(SPELL_LM_BERSERK, Target_Self, 0, 0, 0, 0, 0, false, "THE MASTER'S RAGE COURSES THROUGH ME!", Text_Yell, 16945), MINUTE*10*SEC_IN_MS);

			//normal phase
			AddPhaseSpell(1, AddSpell(SPELL_BONE_SLICE, Target_Current, 25.0f, 0, rand()%10+1));
			AddPhaseSpell(1, AddSpell(SPELL_COLDFLAME, Target_RandomPlayer, 100.0f, 0, 5));

			if((GetInstanceMode() == MODE_HEROIC_10MEN) || (GetInstanceMode() == MODE_HEROIC_25MEN))
			{
				SpellDesc* sBoneSpike = AddPhaseSpell(1, AddSpell(SPELL_BONE_SPIKE, Target_RandomPlayer, 25.0f, 0, rand()%20+15));
				sBoneSpike->AddEmote("Bound by bone!", Text_Yell, 16947);
				sBoneSpike->AddEmote("Stick Around!", Text_Yell, 16948);
				sBoneSpike->AddEmote("The only escape is death!", Text_Yell, 16949);
			}

			Emote("This is the beginning AND the end, mortals. None may enter the master's sanctum!", Text_Yell, 16950);
			AddEmote(Event_OnCombatStart, "The Scourge will wash over this world as a swarm of death and destruction!", Text_Yell, 16941);
			AddEmote(Event_OnTargetDied, "More bones for the offering!", Text_Yell, 16942);
			AddEmote(Event_OnTargetDied, "Languish in damnation!", Text_Yell, 16943);
			AddEmote(Event_OnDied, "I see... only darkness...", Text_Yell, 16944);
		}

		void Reset()
		{
			IsBoneStormSet = false;
			BoneStormTimer = BoneStormInitTimer = ChargeTimer = INVALIDATE_TIMER;
			SetBehavior(Behavior_Default);
			_unit->SetSpeeds(RUN, 8.0f);
		}

		void OnCombatStart(Unit* pUnit)
		{
			BoneStormTimer = AddTimer(30*SEC_IN_MS);

			if(mInstance)
				mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_InProgress);

			ParentClass::OnCombatStart(pUnit);
		}

		void OnCombatStop(Unit* mTarget)
		{
			Reset();

			if(mInstance)
				mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_NotStarted);

			ParentClass::OnCombatStop(mTarget);
		}

		void OnDied(Unit* mKiller)
		{
			if(mInstance)
				mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_Finished);

			ParentClass::OnDied(mKiller);
		}

		void AIUpdate()
		{
			switch(GetPhase())
			{
				case 1:	//Initial bone storm
				{
					if(IsTimerFinished(BoneStormTimer))
					{
						ClearHateList();
						SetBehavior(Behavior_Spell);
						_unit->SetSpeeds(RUN, 18.0f);
						SetPhase(2, sBoneStorm);
					}
				}break;
				case 2:	//perform bone storm
				{
					BoneStormInitTimer = AddTimer(3*SEC_IN_MS);
					if(IsTimerFinished(BoneStormInitTimer))
					{
						SetPhase(3);
						RemoveTimer(BoneStormInitTimer);
					}
				}break;
				case 3: //bone storm phase
				{
					if(!IsBoneStormSet)
					{
						SpawnColdFlame();
						ChargeTimer = AddTimer(5*SEC_IN_MS);
						IsBoneStormSet = true;
					}

					_unit->CastSpell(_unit, SPELL_BONE_STORM_EFFECT, false);

					if(IsTimerFinished(ChargeTimer))
					{
						Unit* pTarget = GetBestPlayerTarget(TargetFilter_ClosestNotCurrent, 0, 70.0f);
						if(pTarget != NULL)
						{
							MoveTo(pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
							SpawnColdFlame();
						}
						pTarget = NULL;
						ResetTimer(ChargeTimer, 5*SEC_IN_MS);
					}

					if(!_unit->HasAura(SPELL_BONE_STORM))
						SetPhase(4);
				}break;
				case 4:	//removing bone storm phase
				{
					_unit->SetSpeeds(RUN, 8.0f);
					SetBehavior(Behavior_Default);
					RemoveTimer(ChargeTimer);
					IsBoneStormSet = false;
					ResetTimer(BoneStormTimer, 60*SEC_IN_MS);
					AggroRandomPlayer();
					SetPhase(1);
				}break;
			}
			ParentClass::AIUpdate();
		}

		void SpawnColdFlame()
		{
			//Spawn cold flame x form
			float PosX, PosY, PosZ;
			float IncrValue = 5.0f;

			GetCurrentPosition(PosX, PosY, PosZ);

			//creating loop to spawn x
			for(uint8 ColdFlameCount = 0; ColdFlameCount<MAX_COLDFLAMES_XFORM; ColdFlameCount++)
			{
				SpawnCreature(NPC_COLD_FLAME, PosX+IncrValue, PosY, PosZ);
				SpawnCreature(NPC_COLD_FLAME, PosX, PosY-IncrValue, PosZ);
				SpawnCreature(NPC_COLD_FLAME, PosX-IncrValue, PosY, PosZ);
				SpawnCreature(NPC_COLD_FLAME, PosX, PosY+IncrValue, PosZ);
				IncrValue += 5.0f;
			}
		}

	protected:
		SpellDesc *sBoneStorm;
		int32 BoneStormTimer, BoneStormInitTimer, ChargeTimer;
		bool IsBoneStormSet;
		MoonInstanceScript* mInstance;
};

enum ColdFlameSpells
{
    SPELL_COLD_FLAME_0	= 69145,
    SPELL_COLD_FLAME_1	= 69147
};

class ColdFlameAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ColdFlameAI, MoonScriptCreatureAI);
		ColdFlameAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SetCanEnterCombat(false);
			_unit->CastSpell(_unit, SPELL_COLD_FLAME_0, false);
			Despawn(15*SEC_IN_MS);
		}
};

void SetupIcecrownCitadel(ScriptMgr* mgr)
{
	mgr->register_instance_script(MAP_ICC, &IcecrownCitadelInstanceScript::Create);
	mgr->register_gameobject_script(202235, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip_script(202235, new ScourgeTeleporterGossip);
	mgr->register_gameobject_script(202223, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip_script(202223, new ScourgeTeleporterGossip);

	for(uint8 i = 0; i<5; i++)
	{
		mgr->register_gameobject_script(202242+i, &ScourgeTeleporterAI::Create);
		mgr->register_go_gossip(202242+i, new ScourgeTeleporterGossip);
	}

	//Lord marrowgar event related
	mgr->register_creature_script(NPC_LORD_MARROWGAR, &LordMarrowgar::Create);
	mgr->register_creature_script(NPC_COLD_FLAME, &ColdFlameAI::Create);
}