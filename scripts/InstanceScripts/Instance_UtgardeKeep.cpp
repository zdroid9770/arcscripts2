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
/*
	To-Do:
	Ingvar the Plunderer - Ressurection Event
	Fix despawn(i think all bosses)
	Add sound ID's
*/
#include "Setup.h"

//////////////////////////////////////////////////////////////////////////
//////// Utgarde Keep Instance script
//#define ZADNJI_DOORS_MOZDA 186612

#define CN_PRINCE_KELESETH 23953
#define CN_SKARVALD 24200
#define CN_DALRONN 24201
#define CN_INGVAR 23954

#define DALRONN_DOORS		186608

#define INGVAR_DOORS_1		186756
#define INGVAR_DOORS_2		186694

#define BELLOW_1			186688
#define BELLOW_2			186689
#define BELLOW_3			186690

#define FORGEFIRE_1			186692
#define FORGEFIRE_2			186693
#define FORGEFIRE_3			186691

#define GLOWING_ANVIL_1		186609
#define GLOWING_ANVIL_2		186610
#define GLOWING_ANVIL_3		186611


enum UtgardeData
{
    UTGARDE_FORGE_MASTER,

    // Bosses
    UTGARDE_KELESETH,
    UTGARDE_SKARVALD_AND_DALRONN,
    UTGARDE_INGVAR,

    UTGARDE_DATA_END
};

struct ForgeMasterData
{
	ForgeMasterData(uint32 pB = 0, uint32 pF = 0, uint32 pA = 0)
	{
		mBellow = pB;
		mFire = pF;
		mAnvil = pA;
	}

	uint32 mBellow;
	uint32 mFire;
	uint32 mAnvil;
};

class UtgardeKeepScript : public MoonInstanceScript
{
	public:
		MOONSCRIPT_INSTANCE_FACTORY_FUNCTION(UtgardeKeepScript, MoonInstanceScript);
		UtgardeKeepScript(MapMgr* pMapMgr) : MoonInstanceScript(pMapMgr)
		{
			mKelesethGUID = 0;
			mSkarvaldGUID = 0;
			mDalronnGUID = 0;
			mIngvarGUID = 0;

			for(int i = 0; i < 3; ++i)
				m_fmData[i] = ForgeMasterData();

			mDalronnDoorsGUID = 0;

			for(int i = 0; i < 2; ++i)
				mIngvarDoors[i] = 0;

			for(int i = 0; i < UTGARDE_DATA_END; ++i)
				mUtgardeData[i] = 0;
		}

		void OnCreaturePushToWorld(Creature* pCreature)
		{
			switch(pCreature->GetEntry())
			{
				case CN_PRINCE_KELESETH: mKelesethGUID = pCreature->GetLowGUID(); break;
				case CN_SKARVALD: mSkarvaldGUID = pCreature->GetLowGUID(); break;
				case CN_DALRONN: mDalronnGUID = pCreature->GetLowGUID(); break;
				case CN_INGVAR: mIngvarGUID = pCreature->GetLowGUID(); break;
			}
		}

		void OnGameObjectPushToWorld(GameObject* pGameObject)
		{
			switch(pGameObject->GetEntry())
			{
				case BELLOW_1: m_fmData[0].mBellow = pGameObject->GetLowGUID(); break;
				case BELLOW_2: m_fmData[1].mBellow = pGameObject->GetLowGUID(); break;
				case BELLOW_3: m_fmData[2].mBellow = pGameObject->GetLowGUID(); break;
				case FORGEFIRE_1: m_fmData[0].mFire = pGameObject->GetLowGUID(); break;
				case FORGEFIRE_2: m_fmData[1].mFire = pGameObject->GetLowGUID(); break;
				case FORGEFIRE_3: m_fmData[2].mFire = pGameObject->GetLowGUID(); break;
				case GLOWING_ANVIL_1: m_fmData[0].mAnvil = pGameObject->GetLowGUID(); break;
				case GLOWING_ANVIL_2: m_fmData[1].mAnvil = pGameObject->GetLowGUID(); break;
				case GLOWING_ANVIL_3: m_fmData[2].mAnvil = pGameObject->GetLowGUID(); break;
				case DALRONN_DOORS: mDalronnDoorsGUID = pGameObject->GetLowGUID(); break;
				case INGVAR_DOORS_1: mIngvarDoors[0] = pGameObject->GetLowGUID(); break;
				case INGVAR_DOORS_2: mIngvarDoors[1] = pGameObject->GetLowGUID(); break;
			}
		}

		void SetInstanceData(uint32 pType, uint32 pIndex, uint32 pData)
		{
			switch(pIndex)
			{
				case UTGARDE_FORGE_MASTER:
					{
						mUtgardeData[UTGARDE_FORGE_MASTER]++;
						HandleForge();
					}break;
				case UTGARDE_INGVAR:
					{
						mUtgardeData[UTGARDE_INGVAR] = pData;

						if(pData == State_Finished)
						{
							GameObject* pGO = NULL;
							for(int i = 0; i < 2; ++i)
							{
								pGO = GetGameObjectByGuid(mIngvarDoors[i]);
								if(pGO)
									pGO->SetState(pGO->GetState() == 1 ? 0 : 1);
							}
						}
					}break;
			}
		}

		void HandleForge()
		{
			if(GameObject* pGO = GetGameObjectByGuid(m_fmData[ mUtgardeData[UTGARDE_FORGE_MASTER] - 1 ].mBellow))
				pGO->SetState(pGO->GetState() == 1 ? 0 : 1);

			if(GameObject* pGO = GetGameObjectByGuid(m_fmData[ mUtgardeData[UTGARDE_FORGE_MASTER] - 1 ].mFire))
				pGO->SetState(pGO->GetState() == 1 ? 0 : 1);

			if(GameObject* pGO = GetGameObjectByGuid(m_fmData[ mUtgardeData[UTGARDE_FORGE_MASTER] - 1 ].mAnvil))
				pGO->SetState(pGO->GetState() == 1 ? 0 : 1);
		}

	private:
		uint32		mKelesethGUID;
		uint32		mSkarvaldGUID;
		uint32		mDalronnGUID;
		uint32		mIngvarGUID;

		ForgeMasterData m_fmData[3];
		uint32		mDalronnDoorsGUID;
		uint32		mIngvarDoors[2];

		uint8		mUtgardeData[UTGARDE_DATA_END];
};

//////////////////////////////////////////////////////////////////////////
//////// Dragonflayer Forge Master

#define CN_DRAGONFLAYER_FORGE_MASTER				24079
#define DRAGONFLAYER_FORGE_MASTER_BURNING_BRAND		43757

class DragonflayerForgeMasterAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DragonflayerForgeMasterAI)
		DragonflayerForgeMasterAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			mInstance = GetInstanceScript();

			AddSpell(DRAGONFLAYER_FORGE_MASTER_BURNING_BRAND, Target_Current, 8, 0, 40, 0, 30);
		}

		void OnDied(Unit* pKiller)
		{
			if(mInstance)
				mInstance->SetInstanceData(Data_UnspecifiedType, UTGARDE_FORGE_MASTER, 0);
		}

		MoonInstanceScript* mInstance;
};

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// Skarvald the Constructor  & Dalronn the Controller  ///////////////////
//////////////////////////////////////////////////////////////////////////////////////////

// Skarvald the Constructor
#define CN_SKARVALD_GHOST 27390
#define SKARVALD_CHARGE 43651
#define STONE_STRIKE 48583

// Dalronn the Controller
#define CN_DALRONN_GHOST 27389
#define DEBILITATE 43650
#define SHADOW_BOLT 43649
#define SKELETON_ADD 28878

class SkarvaldTheConstructorAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SkarvaldTheConstructorAI)
		SkarvaldTheConstructorAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(SKARVALD_CHARGE, Target_RandomPlayerNotCurrent, 35, 0, 8);
			AddSpell(STONE_STRIKE, Target_ClosestPlayer, 25, 0, 10);

			AddEmote(Event_OnCombatStart, "Dalronn! See if you can muster the nerve to join my attack!", Text_Yell, 13229);

			mReplyTimer = INVALIDATE_TIMER;
			pDalronn = NULL;
			pDalronnGhost = NULL;
		}

		void OnCombatStart(Unit* pTarget)
		{
			pDalronn = GetNearestCreature(CN_DALRONN);
			mReplyTimer = AddTimer(2500);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mReplyTimer) && pDalronn != NULL)
			{
				pDalronn->Emote("By all means, don't assess the situation, you halfwit! Just jump into the fray!", Text_Yell, 13199);
				RemoveTimer(mReplyTimer);
			}
		}

		void OnDied(Unit* pKiller)
		{
			if(pDalronn != NULL && pDalronn->IsAlive())
			{
				Emote("Not... over... yet.", Text_Yell, 0);
				pDalronn->Emote("Skarvald, you incompetent slug! Return and make yourself useful!", Text_Yell, 13203);
				SpawnCreature(CN_SKARVALD_GHOST, true);
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

			}
			else if(pDalronn != NULL && !pDalronn->IsAlive())
			{
				Emote("A warrior's death.", Text_Yell, 13231);

				pDalronnGhost = GetNearestCreature(CN_DALRONN_GHOST);

				if(pDalronnGhost != NULL)
				{
					pDalronnGhost->Despawn(1000, 0);
					pDalronnGhost = NULL;
				}
			}
		}

		void OnCombatStop(Unit* pTarget)
		{
			if(pDalronn != NULL)
			{
				if(pDalronn->IsAlive())
					MoveToSpawnOrigin();
				else
					SpawnCreature(CN_DALRONN, pDalronn->GetUnit()->GetSpawnX(), pDalronn->GetUnit()->GetSpawnY(), pDalronn->GetUnit()->GetSpawnZ(), pDalronn->GetUnit()->GetSpawnO());
			}

			if(pDalronnGhost != NULL && pDalronnGhost->IsAlive())
			{
				pDalronnGhost->Despawn();
				pDalronnGhost = NULL;
			}
		}

	private:
		int32					mReplyTimer;
		CreatureAI*	pDalronn;
		CreatureAI*	pDalronnGhost;
};

class DalronnTheControllerAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DalronnTheControllerAI)
		DalronnTheControllerAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(SHADOW_BOLT, Target_RandomPlayer, 35, 2, 8);
			AddSpell(DEBILITATE, Target_RandomPlayer, 25, 0, 12);
			mSummonTimer = AddTimer(15000);
			pSkarvald = NULL;
			pSkarvaldGhost = NULL;
		}

		void OnCombatStart(Unit* pTarget)
		{
			pSkarvald = GetNearestCreature(CN_SKARVALD);
		}

		void AIUpdate()
		{
			if(IsTimerFinished(mSummonTimer))
			{
				SpawnCreature(SKELETON_ADD, _unit->GetPositionX() + 6, _unit->GetPositionY() + 4, _unit->GetPositionZ(), 0, true);
				SpawnCreature(SKELETON_ADD, _unit->GetPositionX() - 6, _unit->GetPositionY() + 4, _unit->GetPositionZ(), 0, true);
				ResetTimer(mSummonTimer, 15000);
			}
		}

		void OnDied(Unit* pKiller)
		{
			if(pSkarvald != NULL && pSkarvald->IsAlive())
			{
				Emote("See... you... soon.", Text_Yell, 0);
				pSkarvald->Emote("Pagh! What sort of necromancer lets death stop him? I knew you were worthless!", Text_Yell, 13233);
				SpawnCreature(CN_DALRONN_GHOST, true);
				_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			}
			else if(pSkarvald != NULL && !pSkarvald->IsAlive())
			{
				Emote("There's no... greater... glory.", Text_Yell, 13201);

				pSkarvaldGhost = GetNearestCreature(CN_SKARVALD_GHOST);

				if(pSkarvaldGhost != NULL)
				{
					pSkarvaldGhost->Despawn(1000, 0);
					pSkarvaldGhost = NULL;
				}
			}
		}

		void OnCombatStop(Unit* pTarget)
		{
			if(pSkarvald != NULL)
			{
				if(pSkarvald->IsAlive())
					MoveToSpawnOrigin();
				else
					SpawnCreature(CN_DALRONN, pSkarvald->GetUnit()->GetSpawnX(), pSkarvald->GetUnit()->GetSpawnY(), pSkarvald->GetUnit()->GetSpawnZ(), pSkarvald->GetUnit()->GetSpawnO());
			}

			if(pSkarvaldGhost != NULL && pSkarvaldGhost->IsAlive())
			{
				pSkarvaldGhost->Despawn();
				pSkarvaldGhost = NULL;
			}
		}

	private:
		int32					mSummonTimer;
		CreatureAI*	pSkarvald;
		CreatureAI*	pSkarvaldGhost;
};

class SkarvaldTheConstructorGhostAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SkarvaldTheConstructorGhostAI)
		SkarvaldTheConstructorGhostAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(SKARVALD_CHARGE, Target_RandomPlayerNotCurrent, 35, 0, 8);
			AddSpell(STONE_STRIKE, Target_ClosestPlayer, 25, 0, 10);
		}

		void OnLoad()
		{
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);

			if(Player* pTarget = GetNearestPlayer())
				_unit->GetAIInterface()->AttackReaction(pTarget, 50, 0);
		}
};

class DalronnTheControllerGhostAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DalronnTheControllerGhostAI)
		DalronnTheControllerGhostAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(SHADOW_BOLT, Target_RandomPlayer, 35, 2, 8);
			AddSpell(DEBILITATE, Target_RandomPlayer, 25, 0, 12);
		}

		void OnLoad()
		{
			_unit->SetUInt64Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9);

			if(Player* pTarget = GetNearestPlayer())
				_unit->GetAIInterface()->AttackReaction(pTarget, 50, 0);
		}

};

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Prince Keleseth ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define CN_FROST_TOMB 23965
#define KELESETH_SHADOW_BOLT 43667
#define KELESETH_SHADOW_BOLT_HC 59389
#define FROST_TOMB_SPELL 48400

#define KELESETH_SKELETON_ADD 23970
#define DECREPIFY 42702
#define DECREPIFY_HC 59397

void SpellFunc_KelesethFrostTomb(SpellDesc* pThis, CreatureAI* pCreatureAI, Unit* pTarget, TargetType pType)
{
	if(pCreatureAI != NULL)
	{
		if(pTarget == NULL || !pTarget->IsPlayer() || pTarget->IsDead())
			return;

		pCreatureAI->GetUnit()->CastSpell(pTarget, FROST_TOMB_SPELL, true);
		pTarget->GetMapMgr()->GetInterface()->SpawnCreature(CN_FROST_TOMB, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pTarget->GetOrientation(), true, false, 0, 0);
		pCreatureAI->Emote("Not so fast.", Text_Yell, 0);
	}
};


void SpellFunc_KelesethAddSummon(SpellDesc* pThis, CreatureAI* pCreatureAI, Unit* pTarget, TargetType pType)
{
	if(pCreatureAI != NULL)
	{
		for(uint32 i = 0; i < 5; ++i)
			pCreatureAI->SpawnCreature(KELESETH_SKELETON_ADD, 163.376f + i + 4, 252.901f - i + 5, 42.868f, 0, true);
	}
};

class PrinceKelesethAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(PrinceKelesethAI)
		PrinceKelesethAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			mFrostTomb = AddSpellFunc(&SpellFunc_KelesethFrostTomb, Target_RandomPlayer, 25, 0, 15, 0, 20);
			mAddSummon = AddSpellFunc(&SpellFunc_KelesethAddSummon, Target_Self, 0, 0, 0);

			mShadowBolt = AddSpell(KELESETH_SHADOW_BOLT, Target_Current, 100, 2, 2);

			AddEmote(Event_OnDied, "I join... the night.", Text_Yell, 13225);
		}

		void OnCombatStart(Unit* pTarget)
		{
			CastSpellNowNoScheduling(mAddSummon);
			Emote("Your blood is mine!", Text_Yell, 13221);
		}

		SpellDesc*			mAddSummon;
		SpellDesc*			mShadowBolt;
		SpellDesc*			mFrostTomb;
};

class FrostTombAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(FrostTombAI)
		FrostTombAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			SetAIUpdateFreq(1000);
		}

		void OnLoad()
		{
			SetCanMove(false);
			plr = GetNearestPlayer();
		}

		void AIUpdate()
		{
			if(plr == NULL || plr->IsDead() || !plr->HasAura(FROST_TOMB_SPELL))
				Despawn();
		}

		void OnDied(Unit* pKilled)
		{
			if(plr != NULL && plr->HasAura(FROST_TOMB_SPELL))
				plr->RemoveAura(FROST_TOMB_SPELL);

			Despawn(1);
		}

	private:
		Player* plr;
};

class SkeletonAddAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SkeletonAddAI)
		SkeletonAddAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(DECREPIFY, Target_Current, 8, 0, 40);
		}

		void OnLoad()
		{
			if(Player* pTarget = GetNearestPlayer())
				_unit->GetAIInterface()->AttackReaction(pTarget, 50, 0);
		}

		void OnCombatStop(Unit* pTarget)
		{
			Despawn(1);
		}

		void OnDied(Unit* pKiller)
		{
			Despawn(1);
		}
};

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Ingvar the Plunderer //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#define CN_INGVAR_UNDEAD 23980
#define CN_SHADOW_AXE 23996
//#define NPC_ANNHYLDE_SPAWN 24068

// Phase 1 spells (Human Form)
#define INGVAR_CLEAVE 42724
#define INGVAR_ENRAGE 59707
#define INGVAR_SMASH 42669
#define INGVAR_ROAR 42708
#define INGVAR_ENRAGE_HC 42705
#define INGVAR_SMASH_HC 59706
#define INGVAR_ROAR_HC 59708

// Phase 2 spells (Undead Form)
#define INGVAR_DARK_SMASH 42723
#define INGVAR_DREADFUL_ROAR 42729
#define INGVAR_WOE_STRIKE 42730
#define INGVAR_DREADFUL_ROAR_HC 59734
#define INGVAR_WOE_STRIKE_HC 59735

#define SHADOW_AXE_SPELL 42751

void SpellFunc_ShadowAxe(SpellDesc* pThis, CreatureAI* pCreatureAI, Unit* pTarget, TargetType pType)
{
	if(pCreatureAI != NULL)
	{
		if(pTarget == NULL || !pTarget->IsPlayer() || pTarget->IsDead())
			return;

		Creature* pShadowAxe = pTarget->GetMapMgr()->GetInterface()->SpawnCreature(CN_SHADOW_AXE, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pTarget->GetOrientation(), true, false, 0, 0);

		if(pShadowAxe == NULL)
			return;

		pShadowAxe->CastSpell(pShadowAxe, SHADOW_AXE_SPELL, true);
		pShadowAxe->Despawn(10000, 0);
	};
};

class IngvarThePlundererAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(IngvarThePlundererAI)
		IngvarThePlundererAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			AddSpell(INGVAR_CLEAVE, Target_Current, 24, 0, 6);
			AddSpell(INGVAR_ENRAGE, Target_Self, 45, 0, 4);
			AddSpell(INGVAR_SMASH, Target_Self, 25, 3, 18);
			AddSpell(INGVAR_ROAR, Target_Self, 25, 2, 10);

			AddEmote(Event_OnTargetDied, "Mjul orm agn gjor!", Text_Yell, 13212);
			AddEmote(Event_OnCombatStart, "I'll paint my face with your blood!", Text_Yell, 13207);
			AddEmote(Event_OnDied, "My life for the... death god!", Text_Yell, 13213);

			SetAIUpdateFreq(1000);
		}

		void OnDied(Unit* pKiller)
		{
			//Ressurect event
			SpawnCreature(CN_INGVAR_UNDEAD, true);
			_unit->Despawn(1000, 0);
		}
};
/* MAY BE USEFUL LATER!
class AnnhyldeAI : public CreatureAI
{
public:
	ADD_CREATURE_FACTORY_FUNCTION(AnnhlydeAI)
		AnnhlydeAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			_unit->AddAura(50236);
	}

	void SpellFunc_SpawnIngvar(SpellDesc* pThis, CreatureAI* pCreatureAI, Unit* pTarget, TargetType pType)
	{
		SpawnCreature(CN_INGVAR_UNDEAD, true);
	};

	void OnLoad()
	{
		_unit->SetFaction(35); // Shes suppose to be hostile and untargetable & flying this is temp.
		Emote("Ingvar! Your pathetic failure will serve as a warning to all... you are damned! Arise and carry out the master's will!", Text_Yell, 13754);
		_unit->Despawn(20000, 0);
	};
*/
class IngvarUndeadAI : public CreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(IngvarUndeadAI)
		IngvarUndeadAI(Creature* pCreature) : CreatureAI(pCreature)
		{
			mInstance = GetInstanceScript();

			AddSpellFunc(&SpellFunc_ShadowAxe, Target_RandomPlayerNotCurrent, 15, 0, 21);
			AddSpell(INGVAR_DARK_SMASH, Target_Self, 12, 3, 16);

			if(IsHeroic())
			{
				AddSpell(INGVAR_DREADFUL_ROAR, Target_Self, 25, 2, 10);
				AddSpell(INGVAR_WOE_STRIKE, Target_ClosestUnit, 18, 0, 16);
			}

			AddEmote(Event_OnCombatStart, "I return a second chance to carve your skulls!", Text_Yell, 13209);
			AddEmote(Event_OnDied, "No! I can do... better! I can...", Text_Yell, 13211);
		}

		void OnLoad()
		{
			if(Player* pTarget = GetNearestPlayer())
				_unit->GetAIInterface()->AttackReaction(pTarget, 50, 0);
		}

		void OnDied(Unit* pKiller)
		{
			if(mInstance)
				mInstance->SetInstanceData(Data_EncounterState, _unit->GetEntry(), State_Finished);
		}

		MoonInstanceScript* mInstance;
};

void SetupUtgardeKeep(ScriptMgr* mgr)
{
	mgr->register_instance_script(574, &UtgardeKeepScript::Create);
	//////////////////////////////////////////////////////////////////////////////////////////
	///////// Mobs
	mgr->register_creature_script(CN_DRAGONFLAYER_FORGE_MASTER, &DragonflayerForgeMasterAI::Create);
	//////////////////////////////////////////////////////////////////////////////////////////
	///////// Bosses

	// Skarvald & Dalronn Encounter
	mgr->register_creature_script(CN_SKARVALD, &SkarvaldTheConstructorAI::Create);
	mgr->register_creature_script(CN_DALRONN, &DalronnTheControllerAI::Create);
	mgr->register_creature_script(CN_SKARVALD_GHOST, &SkarvaldTheConstructorGhostAI::Create);
	mgr->register_creature_script(CN_DALRONN_GHOST, &DalronnTheControllerGhostAI::Create);

	// Prince Keleseth Encounter
	mgr->register_creature_script(CN_PRINCE_KELESETH, &PrinceKelesethAI::Create);
	mgr->register_creature_script(CN_FROST_TOMB, &FrostTombAI::Create);
	mgr->register_creature_script(KELESETH_SKELETON_ADD, &SkeletonAddAI::Create);

	// Ingvar the Plunderer Encounter
	mgr->register_creature_script(CN_INGVAR, &IngvarThePlundererAI::Create);
	mgr->register_creature_script(CN_INGVAR_UNDEAD, &IngvarUndeadAI::Create);
};
