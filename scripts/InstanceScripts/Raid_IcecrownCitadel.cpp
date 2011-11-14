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
    ICC_END
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

//special thanks for rsa and TrinityCore for information
enum LM_SpellEnum
{
	SPELL_LM_BERSERK	= 0,
	SPELL_LM_BONE_SLICE,
	SPELL_LM_BONESTORM,
	SPELL_LM_BONESTORM_EFFECT,
	SPELL_LM_BONE_SPIKE_GRAVEYARD,
	SPELL_LM_COLDFLAME
};

uint32 MarrowgarSpells[7][4]=
{
	//10man 25man  10manhc 25manhc
	{47008,	47008, 47008, 47008},	//Berserk
	{69055, 69055, 70814, 70814},	//Bone Slice
	{69076, 69076, 70835, 70835},	//Bone Storm
	{69075, 69075, 69075, 69075},	//Bone Storm effect
	{69057, 69057, 70826, 70826},	//Bone Spike Graveyard
	{69138, 69138, 69138, 69138}	//Call ColdFlame
};

enum LM_Summons
{
	MAX_COLDFLAMES_XFORM	= 20,
    NPC_BONE_SPIKE			= 38711,
    NPC_COLD_FLAME			= 36672
};

class LordMarrowgar : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(LordMarrowgar, MoonScriptCreatureAI);
	LordMarrowgar(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		mInstance = GetInstanceScript();

		Emote("This is the beginning AND the end, mortals. None may enter the master's sanctum!", Text_Yell, 16950);
		AddEmote(Event_OnCombatStart, "The Scourge will wash over this world as a swarm of death and destruction!", Text_Yell, 16941);
		AddEmote(Event_OnTargetDied, "More bones for the offering!", Text_Yell, 16942);
		AddEmote(Event_OnTargetDied, "Languish in damnation!", Text_Yell, 16943);
		AddEmote(Event_OnDied, "I see... only darkness...", Text_Yell, 16944);

		pMode = _unit->GetMapMgr()->iInstanceMode;
		if(pMode == NULL)
			return;	//spells can't be casted without this

		sEnrage = AddSpell(MarrowgarSpells[SPELL_LM_BERSERK][pMode], Target_Self, 0, 0, 0, 0, 0, false, "THE MASTER'S RAGE COURSES THROUGH ME!", Text_Yell, 16945);	//10 min
		//sBoneStorm = AddSpell(MarrowgarSpells[SPELL_LM_BONESTORM][pMode], Target_Self, 0, 3, 0, 0, 0, false, "BONE STORM!", Text_Yell, 16946, "BONE STORM!");
		sBoneSlice = AddSpell(MarrowgarSpells[SPELL_LM_BONE_SLICE][pMode], Target_Current, 25.0f, 0, -1);
		sColdFlame = AddSpell(MarrowgarSpells[SPELL_LM_COLDFLAME][pMode], Target_RandomPlayer, 100.0f, 0, -1);
		//SpellDesc* sBoneSpike = AddSpell(MarrowgarSpells[SPELL_LM_BONE_SPIKE_GRAVEYARD][pMode], Target_Self, 25.0f, 0, rand()%17+10);
			//sBoneSpike->AddEmote("Bound by bone!", Text_Yell, 16947);
			//sBoneSpike->AddEmote("Stick Around!", Text_Yell, 16948);
			//sBoneSpike->AddEmote("The only escape is death!", Text_Yell, 16949);
		Reset();
	}

	void Reset()
	{
		Enraged = IsBoneStormPhase = SpawnXColdFlame = false;
		SetCanMove(true);
	}

	void OnCombatStart(Unit* pUnit)
	{
		mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_InProgress);
		//BoneStormTimer = AddTimer(30000);
		EnrageTimer = AddTimer(600000);	//10min
		Reset();
		ParentClass::OnCombatStart(pUnit);
	}

	void OnCombatStop(Unit* mTarget)
	{
		mInstance->SetInstanceData(Data_EncounterState, ICC_LORD_MARROWGAR, State_NotStarted);
		Reset();
		ParentClass::OnCombatStop(mTarget);
	}

	void AIUpdate()
	{
		/*
		if(!_unit->HasAura(MarrowgarSpells[SPELL_LM_BONESTORM][pMode]) && IsBoneStormPhase)
		{
			RemoveTimer(ChargeTimer);
			SetCanMove(true);
			_unit->InterruptSpell();
			_unit->SetSpeeds(RUN, 8.0f);
			ClearHateList();
			sBoneSlice->mEnabled = true;	
			ResetTimer(BoneStormTimer, 30000);
			SpawnXColdFlame = IsBoneStormPhase = false;
		}

		if(IsTimerFinished(BoneStormTimer))
		{
			_unit->InterruptSpell();
			SetCanMove(false);	//he moves only on charge
			_unit->SetSpeeds(RUN, 18.0f);
			sBoneSlice->mEnabled = false;
			ClearHateList();
			CastSpellNowNoScheduling(sBoneStorm);
			ChargeTimer = AddTimer(4000);
			IsBoneStormPhase = true;
			SpawnXColdFlame = true;
		}

		if(IsTimerFinished(ChargeTimer) && SpawnXColdFlame)
		{
			Unit* pTarget = GetBestUnitTarget(TargetFilter_ClosestNotCurrent);
			if(pTarget!=NULL)
			{
				ClearHateList();
				_unit->GetAIInterface()->setNextTarget(pTarget);
				_unit->GetAIInterface()->AttackReaction(pTarget, 100.0f);
				MoveTo(pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), true);

				//Spawn cold flame x form
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
			}
			ResetTimer(ChargeTimer, 3000);
		}*/

		//ENRAGE!
		if(IsTimerFinished(EnrageTimer) && !Enraged)
		{
			CastSpellNowNoScheduling(sEnrage);
			Enraged = true;
		}

		ParentClass::AIUpdate();
	}

protected:
	SpellDesc *sBoneStorm, *sEnrage, *sBoneSlice, *sColdFlame;
	int32 EnrageTimer, BoneStormTimer, ChargeTimer;
	uint8 Phase, ChargesMaxCount, pMode;
    bool IsBoneStormPhase, SpawnXColdFlame, Enraged;
	MoonInstanceScript* mInstance;
};

enum ColdFlameSpells
{
    SPELL_COLD_FLAME_0	= 69145,
    SPELL_COLD_FLAME_1	= 69147
};

class ColdFlame : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(ColdFlame, MoonScriptCreatureAI);
	ColdFlame(Creature* pCreature) : MoonScriptCreatureAI(pCreature){}

	void OnLoad()
	{
		_unit->Despawn(5000, 0);
		ApplyAura(SPELL_COLD_FLAME_0);
	}
};

bool BoneStorm(uint32 i, Spell* s)
{
/*	comented temporally
if(s->u_caster == NULL)
		return true;

	SpellEntry* pSpell;
	if(s)
		pSpell = dbcSpell.LookupEntry((uint32)s);

	uint32 Dmg = s->u_caster->GetSpellDidHitResult(s->u_caster, s->GetType(), s->GetProto());
	Dmg += Dmg/10.0f;
	s->u_caster->HandleProc(PROC_ON_SPELL_HIT, s->u_caster, pSpell, false, Dmg);
*/
	return true;
};

void SetupIcecrownCitadel(ScriptMgr* mgr)
{
	mgr->register_instance_script(631, &IcecrownCitadelInstanceScript::Create);
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
	mgr->register_creature_script(36612, &LordMarrowgar::Create);
	mgr->register_creature_script(NPC_COLD_FLAME, &ColdFlame::Create);
	mgr->register_dummy_spell(69075, &BoneStorm);
}