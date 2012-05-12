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
#include "Raid_IcecrownCitadel.h"

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
				case NPC_LORD_MARROWGAR:
				{
					AddGameObjectStateByEntry(GO_MARROWGAR_ENTRANCE, State_Active);
					AddGameObjectStateByEntry(GO_ICEBLOCK_1, State_Active);
					AddGameObjectStateByEntry(GO_ICEBLOCK_2, State_Active);
					AddGameObjectStateByEntry(GO_DAMMED_ENTRANCE, State_Active);
				}break;
				case NPC_ROTFACE: 
				{
					GameObject * pGo1 = FindClosestGameObjectOnMap(GO_OOZE_RELEASE_VALVE, 4432.27f, 3090.88f, 362.253f);
					if(pGo1 != NULL)
						pGo1->SetFlags(0);
				}break;
				case NPC_FESTERGUT: 
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
			{
				AddGameObjectStateByEntry(GO_SCIENTIST_DOOR_COLLISION, State_Active);
				AddGameObjectStateByEntry(GO_SCIENTIST_ENTRANCE, State_Active);
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
			if(player->getcombatstatus())
				return;

			IcecrownCitadelInstanceScript * pInstance = (IcecrownCitadelInstanceScript*)player->GetMapMgr()->GetScript();
			if(pInstance == NULL)
				return;

			GossipMenu* menu;
			objmgr.CreateGossipMenuForPlayer(&menu, _gameobject->GetGUID(), 0, player);
			menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Light's Hammer.", 0);
			if(pInstance->GetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR) == State_Finished)
				menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Oratory of the Damned.", 1);
			if(pInstance->GetInstanceData(Data_EncounterState, ICC_LADY_DEATHWHISPER) == State_Finished)
				menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Rampart of Skulls.", 2);
			if(pInstance->GetInstanceData(Data_EncounterState, ICC_GUNSHIP) == State_Finished)
				menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Deathbringer's Rise.", 3);
			if(pInstance->GetInstanceData(Data_EncounterState, ICC_SAURFANG) == State_Finished)
				menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to the Upper Spire.", 4);
			if(pInstance->GetInstanceData(Data_EncounterState, ICC_SAURFANG) == State_Finished
				&& pInstance->GetInstanceData(Data_EncounterState, ICC_PROFESSOR_PUTRICIDE) == State_Finished
				&& pInstance->GetInstanceData(Data_EncounterState, ICC_BLOOD_QUEEN_LANATHEL) == State_Finished
				&& pInstance->GetInstanceData(Data_EncounterState, ICC_VALITRA_DREAMWALKER) == State_Finished)
				menu->AddItem(Arcemu::Gossip::ICON_CHAT, "Teleport to Sindragosa's Lair", 5);
			if(pInstance->GetInstanceData(Data_EncounterState, ICC_PROFESSOR_PUTRICIDE) == State_Finished
				&& pInstance->GetInstanceData(Data_EncounterState, ICC_BLOOD_QUEEN_LANATHEL) == State_Finished
				&& pInstance->GetInstanceData(Data_EncounterState, ICC_VALITRA_DREAMWALKER) == State_Finished
				&& pInstance->GetInstanceData(Data_EncounterState, ICC_SINDRAGOSA) == State_Finished)
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

			SetEnrageInfo(AddSpell(SPELL_LM_BERSERK, Target_Self, 0, 0, 0, 0, 0, false, "THE MASTER'S RAGE COURSES THROUGH ME!", Text_Yell, 16945), MINUTE*10*SEC_IN_MS);

			//normal phase
			AddPhaseSpell(1, AddSpell(SPELL_BONE_SLICE, Target_Current, 25.0f, 0, 10));
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
			BoneStormTimer = ChargeTimer = INVALIDATE_TIMER;
			Stage = -1;
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
			if(IsTimerFinished(BoneStormTimer) && GetPhase() == 1 && Stage == -1)
				Stage++;

			if(Stage == 0)
			{
				ClearHateList();
				SetBehavior(Behavior_Spell);
				_unit->SetSpeeds(RUN, 18.0f);
				SetPhase(2, sBoneStorm);
				if(_unit->HasAura(SPELL_BONE_STORM))
				{
					_unit->CastSpell(_unit, SPELL_COLDFLAME_BONESTORM, false);
					ChargeTimer = AddTimer(5*SEC_IN_MS);
					Stage++;
				}
			}
			else if(Stage == 1)
			{
				if(IsTimerFinished(ChargeTimer))
				{
					Unit* pTarget = GetBestPlayerTarget(TargetFilter_Closest/*NotCurrent*/, 0, 70.0f);	//only for testing!
					if(pTarget != NULL)
					{
						MoveTo(pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
						_unit->CastSpell(_unit, SPELL_COLDFLAME_BONESTORM, false);
					}
					pTarget = NULL;
					ResetTimer(ChargeTimer, 5*SEC_IN_MS);
				}
			}

			if(!_unit->HasAura(SPELL_BONE_STORM) && Stage == 1)
			{
				_unit->SetSpeeds(RUN, 8.0f);
				SetBehavior(Behavior_Default);
				RemoveTimer(ChargeTimer);
				AggroRandomPlayer();
				ResetTimer(BoneStormTimer, 60*SEC_IN_MS);
				Stage = -1;
				SetPhase(1);
			}
		ParentClass::AIUpdate();
	}

	protected:
		SpellDesc *sBoneStorm;
		int8 Stage;
		int32 BoneStormTimer, ChargeTimer;
		MoonInstanceScript* mInstance;
};

class ColdFlameAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(ColdFlameAI, MoonScriptCreatureAI);
		ColdFlameAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SetCanEnterCombat(false);
			Despawn(15*SEC_IN_MS);
		}

		void AIUpdate()
		{
			_unit->CastSpell(_unit, 69145, false);
			ParentClass::AIUpdate();
		}
};

class BoneSpikeAI : public MoonScriptCreatureAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(BoneSpikeAI, MoonScriptCreatureAI);
		BoneSpikeAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnLoad()
		{
			_unit->CastSpell(GetNearestPlayer(), 46598, true);	//Ride vehicle
			_unit->CastSpell(_unit, 69065, false);	//impaled
			ParentClass::OnLoad();
		}

		void OnDied(Unit * mKiller)
		{
			mKiller->RemoveAura(69065);	//impaled
			_unit->Despawn(0, 0);
			ParentClass::OnDied(mKiller);
		}

		void OnTargetDied(Unit * pUnit)
		{
			_unit->Despawn(0, 0);
			ParentClass::OnTargetDied(pUnit);
		}
};

bool ColdFlame_BoneStorm(uint32 i, Spell* s)
{
	s->u_caster->CastSpell(s->u_caster, 72700, false);
	s->u_caster->CastSpell(s->u_caster, 72701, false);
	s->u_caster->CastSpell(s->u_caster, 72702, false);
	return true;
};

bool ColdFlame(uint32 i, Spell* s)
{
	s->u_caster->CastSpell(s->u_caster, 69146, false);
	//s->u_caster->CastSpell(s->u_caster, 33801, false);	need more information about this
	return true;
};

bool ColdFlameRandom(uint32 i, Spell* s)
{
	s->u_caster->CastSpell(s->u_caster, 69138, false);
	return true;
};

void SetupIcecrownCitadel(ScriptMgr* mgr)
{
	mgr->register_instance_script(MAP_ICC, &IcecrownCitadelInstanceScript::Create);
	mgr->register_gameobject_script(202235, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip_script(202235, new ScourgeTeleporterGossip);
	mgr->register_gameobject_script(202223, &ScourgeTeleporterAI::Create);
	mgr->register_go_gossip_script(202223, new ScourgeTeleporterGossip);

	for(uint8 i = 0; i < 5; i++)
	{
		mgr->register_gameobject_script(202242+i, &ScourgeTeleporterAI::Create);
		mgr->register_go_gossip(202242+i, new ScourgeTeleporterGossip);
	}

	//Lord marrowgar event related
	mgr->register_creature_script(NPC_LORD_MARROWGAR, &LordMarrowgar::Create);
	mgr->register_creature_script(NPC_COLD_FLAME, &ColdFlameAI::Create);
	mgr->register_creature_script(NPC_BONE_SPIKE, &BoneSpikeAI::Create);
	mgr->register_script_effect(SPELL_COLDFLAME_BONESTORM, &ColdFlame_BoneStorm);
	mgr->register_script_effect(69147, &ColdFlame);
	mgr->register_script_effect(69140, &ColdFlameRandom);
}