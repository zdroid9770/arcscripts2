/*
 * ArcScripts for ArcEmu MMORPG Server
 * Copyright (C) 2009 ArcEmu Team <http://www.arcemu.org/>
 * Copyright (C) 2008-2009 Sun++ Team <http://www.sunscripting.com/>
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2007-2008 Moon++ Team <http://www.moonplusplus.info/>
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

#include "Setup.h"
	
#define	WARDEN_MELLICHAR 0
#define CN_DALLIAH_THE_DOOMSAYER 20885
#define CN_WRATH_SCRYER_SOCCOTHRATES 20886
enum eUnits
{
    CONTAINMENT_CORE_SECURITY_FIELD_ALPHA = 184318, //door opened when Wrath-Scryer Soccothrates dies
    CONTAINMENT_CORE_SECURITY_FIELD_BETA  = 184319, //door opened when Dalliah the Doomsayer dies
    POD_ALPHA                             = 183961, //pod first boss wave
    POD_BETA                              = 183963, //pod second boss wave
    POD_DELTA                             = 183964, //pod third boss wave
    POD_GAMMA                             = 183962, //pod fourth boss wave
    POD_OMEGA                             = 183965, //pod fifth boss wave
    WARDENS_SHIELD                        = 184802, // warden shield

    MELLICHAR                             = 20904 //skyriss will kill this unit
};

class ArcatrazInstanceScript : public MoonInstanceScript
{
public:
	MOONSCRIPT_INSTANCE_FACTORY_FUNCTION(ArcatrazInstanceScript, MoonInstanceScript);
	ArcatrazInstanceScript(MapMgr* pMapMgr) : MoonInstanceScript(pMapMgr) 
	{
		WardenShieldGuid = CoreSecurityAlphaGuid = CoreSecurityBetaGuid = NULL;
		for(uint32 i=0; i<=3; i++)
			OrbGuid[i] = 0;
	}
	

	void OnGameObjectPushToWorld(GameObject* pGameObject)
	{
		switch(pGameObject->GetEntry())
		{
			case CONTAINMENT_CORE_SECURITY_FIELD_ALPHA: CoreSecurityAlphaGuid = pGameObject->GetGUID(); break;
			case CONTAINMENT_CORE_SECURITY_FIELD_BETA: CoreSecurityBetaGuid = pGameObject->GetGUID(); break;
			case WARDENS_SHIELD: WardenShieldGuid = pGameObject->GetGUID(); break;
			case POD_ALPHA: OrbGuid[0] = pGameObject->GetGUID(); break;
			case POD_BETA: OrbGuid[1] = pGameObject->GetGUID(); break;
			case POD_DELTA: OrbGuid[2] = pGameObject->GetGUID(); break;
			case POD_GAMMA: OrbGuid[3] = pGameObject->GetGUID(); break;
		}
	}

	void OnCreatureDeath(Creature* pCreature, Unit* pUnit)
	{		
		switch(pCreature->GetEntry())
		{
			case CN_DALLIAH_THE_DOOMSAYER:
			{
				GameObject* pGo1 = GetGameObjectByGuid(CoreSecurityBetaGuid);
				if(pGo1 != NULL)
					pGo1->SetState(State_Active);
			}break;
			case CN_WRATH_SCRYER_SOCCOTHRATES:
			{
				GameObject* pGo2 = GetGameObjectByGuid(CoreSecurityAlphaGuid);
				if(pGo2 != NULL)
					pGo2->SetState(State_Active);
			}break;
		}
	}

	void SetInstanceData(uint32 pType, uint32 pIndex, uint32 pData)
	{
		if(pIndex == WARDEN_MELLICHAR)
		{
			switch(pData)
			{
				case 1:	//agroo
				{
					GameObject* pGo1 = GetGameObjectByGuid(WardenShieldGuid);
					if(pGo1 != NULL)
						pGo1->SetState(State_Active);
				}break;
				case 2:	//first orb
				{
					GameObject* pGo2 = GetGameObjectByGuid(OrbGuid[0]);
					if(pGo2 != NULL)
						pGo2->SetState(State_Active);
				}break;
				case 3:	//second orb
				{
					GameObject* pGo3 = GetGameObjectByGuid(OrbGuid[1]);
					if(pGo3 != NULL)
						pGo3->SetState(State_Active);
				}break;
				case 4:	//third orb
				{
					GameObject* pGo4 = GetGameObjectByGuid(OrbGuid[1]);
					if(pGo4 != NULL)
						pGo4->SetState(State_Active);
				}break;
				case 5:	//four orb
				{
					GameObject* pGo5 = GetGameObjectByGuid(OrbGuid[1]);
					if(pGo5 != NULL)
						pGo5->SetState(State_Active);
				}break;
				case 6:	//last orb
				{
					GameObject* pGo6 = GetGameObjectByGuid(OrbGuid[1]);
					if(pGo6 != NULL)
						pGo6->SetState(State_Active);
				}break;
			}
		}
	}

protected:
	uint64 WardenShieldGuid, CoreSecurityAlphaGuid, CoreSecurityBetaGuid, OrbGuid[3];
};

// Zereketh the UnboundAI
#define CN_ZEREKETH			20870
#define CN_VOIDZONEARC		21101

#define SEED_OF_C			36123
#define SHADOW_NOVA			HeroicInt(39005, 36127)
#define CONSUMPTION			HeroicInt(39004, 30498)
#define VOID_ZONE 36119

class ZerekethAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(ZerekethAI, MoonScriptBossAI);
	ZerekethAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddEmote(Event_OnCombatStart, "Life energy to... consume.", Text_Yell, 11250);
		AddEmote(Event_OnTargetDied, "This vessel...is empty.", Text_Yell, 11251);
		AddEmote(Event_OnTargetDied, "No... more... life.", Text_Yell, 11252);
		AddEmote(Event_OnDied, "The Void... beckons.", Text_Yell, 11255);

		AddSpell(SEED_OF_C, Target_RandomPlayer, 6.0f, 2, 20, 0, 100.0f);
		AddSpell(SHADOW_NOVA, Target_Self, 15, 2, 15);
		AddSpell(VOID_ZONE, Target_RandomPlayer, 20, 0, rand()%10+30);
	}

	void OnCombatStart(Unit* mTarget)
	{
		SpeechTimer = AddTimer((rand()%10 + 40) * 1000);

		ParentClass::OnCombatStart(mTarget);
	}

	void AIUpdate()
	{
		if(IsTimerFinished(SpeechTimer))
		{
			switch(rand()%2)
			{
				case 0: Emote("The shadow... will engulf you.", Text_Yell, 11253); break;
				case 1: Emote("Darkness... consumes all.", Text_Yell, 11254); break;
			}
			ResetTimer(SpeechTimer, (rand()%10 + 40) * 1000);
		}

		ParentClass::AIUpdate();
	}

protected:
	int32 SpeechTimer;
};

class VoidZoneARC : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(VoidZoneARC, MoonScriptCreatureAI);
	VoidZoneARC(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
	{
		StopMovement();
		SetCanMove(false);
		SetCanEnterCombat(false);
		RegisterAIUpdateEvent(1000);
	}

	void AIUpdate()
	{
		_unit->CastSpell(_unit, CONSUMPTION, true);
		RemoveAIUpdateEvent();
	}
};

// Dalliah the DoomsayerAI
#define GIFT_OF_THE_DOOMSAYER 36173
#define WHIRLWIND 36175
#define HEAL 36144
#define SHADOW_WAVE 39016	// Heroic mode spell

class DalliahTheDoomsayerAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(DalliahTheDoomsayerAI, MoonScriptBossAI);
	DalliahTheDoomsayerAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddSpell(GIFT_OF_THE_DOOMSAYER, Target_Current, 8.0f, 0.0f, -1);

		SpellDesc* WhirlTemp = AddSpell(WHIRLWIND, Target_Self, 15.0f, 0.0f, -1);
		WhirlTemp->AddEmote("Reap the Whirlwind!", Text_Yell, 11089);
		WhirlTemp->AddEmote("I'll cut you to peices!", Text_Yell, 11090);

		SpellDesc* HealTemp = AddSpell(HEAL, Target_Self, 8.0f, 0, -1);
		HealTemp->AddEmote("That is much better.", Text_Yell, 11091);
		HealTemp->AddEmote("Ah, just what I needed.", Text_Yell, 11092);

		if(IsHeroic())
			AddSpell(SHADOW_WAVE, Target_Current, 8.0f, 0, -1);

		AddEmote(Event_OnCombatStart, "It is unwise to anger me.", Text_Yell, 11086);
		AddEmote(Event_OnTargetDied, "Completely ineffective! Just like someone else I know!", Text_Yell, 11087);
		AddEmote(Event_OnTargetDied, "You chose the wrong opponent!", Text_Yell, 11088);
		AddEmote(Event_OnDied, "Now I'm really... angry...", Text_Yell, 11093);
	}
};

// Wrath-Scryer SoccothratesAI
#define IMMOLATION HeroicInt(39007, 36051)
#define FELFIRE_SHOCK HeroicInt(39006, 35759)
#define FELFIRE_LINE_UP 35770
#define KNOCK_AWAY 20686
#define CHARGE 35754

class WrathScryerSoccothratesAI : public MoonScriptBossAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(WrathScryerSoccothratesAI, MoonScriptBossAI);
	WrathScryerSoccothratesAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
	{
		AddEmote(Event_OnCombatStart, "At last, a target for my frustrations!", Text_Yell, 11238);
		AddEmote(Event_OnTargetDied, "Yes, that was quiet... satisfying.", Text_Yell, 11239);
		AddEmote(Event_OnTargetDied, "Ha! Much better!", Text_Yell, 11240);
		AddEmote(Event_OnDied, "Knew this was... the only way out.", Text_Yell, 11243);

		AddSpell(IMMOLATION, Target_Self, 10.0f, 0, -1);
		AddSpell(FELFIRE_SHOCK, Target_Current, 8.0f, 0, -1);
		AddSpell(FELFIRE_LINE_UP, Target_Self, 8.0f, 0, -1);
		AddSpell(KNOCK_AWAY, Target_Destination, 6.0f, 0, -1);
		AddSpell(CHARGE, Target_Current, 4.0f, 0, -1);
	}
};

// Harbinger SkyrissAI
// Full event must be scripted for this guy.
#define CN_HARBRINGER_SKYRISS 20912

#define MIND_REND 36924 // DBC: 36859, 36924;
#define FEAR 39415
#define DOMINATION 37162
#define SUMMON_ILLUSION_66 36931	// those 2 don't work
#define SUMMON_ILLUSION_33 36932
// BLINK_VISUAL 36937 ?
// SIMPLE_TELEPORT 12980 ?
// Add sounds related to his dialog with mind controlled guy

class HarbringerSkyrissAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(HarbringerSkyrissAI, MoonScriptBossAI);

		HarbringerSkyrissAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			AddSpell(MIND_REND, Target_Current, 15.0f, 0, -1);

			SpellDesc* Fear = AddSpell(FEAR, Target_Current, 8.0f, 0, -1);
			Fear->AddEmote("Flee in terror!", Text_Yell, 11129);
			Fear->AddEmote("I will show you horrors undreamed of.", Text_Yell, 11130);

			SpellDesc* Domination = AddSpell(DOMINATION, Target_Current, 6.0f, 0, -1);
			Domination->AddEmote("You will do my bidding, weakling.", Text_Yell, 11127);
			Domination->AddEmote("Your will is no longer your own.", Text_Yell, 11128);

			Illusion66 = AddSpell(SUMMON_ILLUSION_66, Target_Self, 0, 0, -1, 0, 0, false, "", Text_Yell, 11131);
			Illusion66->mEnabled = false;

			Illusion33 = AddSpell(SUMMON_ILLUSION_33, Target_Self, 0, 0, -1, 0, 0, false, "",  Text_Yell, 11131);
			Illusion33->mEnabled = false;

			AddEmote(Event_OnCombatStart, "Bear witness to the agent of your demise!", Text_Yell, 11123);
			AddEmote(Event_OnTargetDied, "Your fate is written!", Text_Yell, 11124);
			AddEmote(Event_OnTargetDied, "The chaos I have sown here is but a taste....", Text_Yell, 11125);
			AddEmote(Event_OnDied, "I am merely one of... infinite multitudes.", Text_Yell, 11126);

			IllusionCount = 0;
		}

		void OnCombatStart(Unit* mTarget)
		{
			IllusionCount = 0;
			ParentClass::OnCombatStart(mTarget);
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 66 && IllusionCount == 0)
			{
				IllusionCount++;
				CastSpell(Illusion66);
			}
			else if(GetHealthPercent() <= 33 && IllusionCount == 1)
			{
				IllusionCount++;
				CastSpell(Illusion33);
			}
			ParentClass::AIUpdate();
		}


	protected:

		uint32 IllusionCount;
		SpellDesc* Illusion66;
		SpellDesc* Illusion33;
};


enum eWardenSpells
{
    SPELL_TARGET_ALPHA  = 36856,
    SPELL_TARGET_BETA   = 36854,
    SPELL_TARGET_DELTA  = 36857,
    SPELL_TARGET_GAMMA  = 36858,
    SPELL_TARGET_OMEGA  = 36852,
    SPELL_BUBBLE_VISUAL = 36849
};

enum eWardenUnits
{
    //phase 2(acid mobs)
    ENTRY_TRICKSTER    = 20905,
    ENTRY_PH_HUNTER    = 20906,
    //phase 3
    ENTRY_MILLHOUSE    = 20977,
    //phase 4(acid mobs)
    ENTRY_AKKIRIS      = 20908,
    ENTRY_SULFURON     = 20909,
    //phase 5(acid mobs)
    ENTRY_TW_DRAK      = 20910,
    ENTRY_BL_DRAK      = 20911,
    //phase 6
    ENTRY_SKYRISS      = 20912
};

#define CN_WARDEN_MELLICHAR 20904

#define BLAZING_TRICKSTER 20905
#define WARP_STALKER 20906
#define AKKIRIS_LIGHTNING_WAKER 20908
#define SULFURON_MAGMA_THROWER 20909
#define TWILIGHT_DRAKONAAR 20910
#define BLACKWING_DRAKONAAR 20911
#define MILLHOUSE_MANASTORM 20977

class WardenMellicharAI : public MoonScriptBossAI
{
	public:
		MOONSCRIPT_FACTORY_FUNCTION(WardenMellicharAI, MoonScriptBossAI);
		WardenMellicharAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			SetCanMove(false);
			mInstance = GetInstanceScript();
			Phase_Timer = 0;
		}

		void OnCombatStart(Unit* mTarget)
		{
			SetCanEnterCombat(false);
			SetCanMove(false);
			SetAllowMelee(false);
			SetAllowSpell(false);

			Phase_Timer = AddTimer(22000);

			Emote("I knew the prince would be angry but, I... I have not been myself. I had to let them out! The great one speaks to me, you see. Wait--outsiders. Kael'thas did not send you! Good... I'll just tell the prince you released the prisoners!",
			Text_Yell, 11222);
			_unit->CastSpell(_unit, SPELL_BUBBLE_VISUAL, true);
			mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 1);
			ParentClass::OnCombatStart(mTarget);
		}


		void AIUpdate()
		{
			// ORB ONE
			if(IsTimerFinished(Phase_Timer) && GetPhase() == 0)
			{
				Emote("The naaru kept some of the most dangerous beings in existence here in these cells. Let me introduce you to another...", Text_Yell, 11223);
				_unit->CastSpell(_unit, SPELL_TARGET_ALPHA, false);
				mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 2);
				switch(rand()%2)
				{
					case 0: pSummon = SpawnCreature(ENTRY_TRICKSTER, 478.326f, -148.505f, 42.56f, 3.19f); break;
					case 1: pSummon = SpawnCreature(ENTRY_PH_HUNTER, 478.326f, -148.505f, 42.56f, 3.19f); break;
				}

				if(pSummon == NULL)
					return;

				if(!pSummon->IsAlive())
				{
					Emote("Yes, yes... another! Your will is mine! Behold another terrifying creature of incomprehensible power!", Text_Yell, 11224);
					_unit->CastSpell(_unit, SPELL_TARGET_BETA, false);
					mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 3);
					ResetTimer(Phase_Timer, 6000);
					SetPhase(1);
					pSummon = NULL;
				}

			//ORB TWO
			}else if(IsTimerFinished(Phase_Timer) && GetPhase() == 1)
			{
				Millhouse = _unit->GetMapMgr()->GetInterface()->SpawnCreature(ENTRY_MILLHOUSE, 413.292f, -148.378f, 42.56f, 6.27f, false, true, 0, 0);
				if(Millhouse!=NULL)
				{
					Millhouse->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Where in Bonzo's brass buttons am I? And who are-- yaaghh, that's one mother of a headache!", 2000);
					sEventMgr.AddEvent(TO_OBJECT(Millhouse), &Object::PlaySoundToSet, (uint32)11171, EVENT_UNK, 2000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "What is this? A lowly gnome? I will do better, oh great one.", 13000);
					sEventMgr.AddEvent(TO_OBJECT(_unit), &Object::PlaySoundToSet, (uint32)11226, EVENT_UNK, 13000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
					
					SetPhase(2);	//starts another after his talk
					ResetTimer(Phase_Timer, 6000);
					_unit->CastSpell(_unit, SPELL_TARGET_BETA, false);
					mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 4);

					Millhouse->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Lowly? Nobody refers to the mighty Millhouse Manastorm as lowly! I have no idea what goes on here, but I will gladly join your fight against this impudent imbecile!", 22000);
					sEventMgr.AddEvent(TO_OBJECT(Millhouse), &Object::PlaySoundToSet, (uint32)11172, EVENT_UNK, 22000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				}
				
			// ORB THREE
			}else if(IsTimerFinished(Phase_Timer) && GetPhase() == 2)
			{

				switch(rand()%2)
				{
					case 0 : pSummon = SpawnCreature(ENTRY_AKKIRIS, 420.179f, -174.396f, 42.58f, 0.02f); break;
					case 1 : pSummon = SpawnCreature(ENTRY_SULFURON, 420.179f, -174.396f, 42.58f, 0.02f); break;
				}

				if(pSummon == NULL)
					return;
				
				if(!pSummon->IsAlive())
				{
					Emote("Anarchy! Bedlam! Oh, you are so wise! Yes, I see it now, of course!", Text_Yell, 11227);
					_unit->CastSpell(_unit, SPELL_TARGET_GAMMA, false);
					mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 5);
					SetPhase(3);
					ResetTimer(Phase_Timer, 6000);
					pSummon = NULL;
				}

			// ORB FOUR
			}else if(IsTimerFinished(Phase_Timer) && GetPhase() == 3)
			{

				switch(rand()%2)
				{
					case 0: pSummon = SpawnCreature(ENTRY_TW_DRAK , 471.795f, -174.58f, 42.58f, 3.06f); break;
					case 1: pSummon = SpawnCreature(ENTRY_BL_DRAK , 471.795f, -174.58f, 42.58f, 3.06f); break;
				}

				if(pSummon == NULL)
					return;
				
				if(!pSummon->IsAlive())
				{
					mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 6);
					SetPhase(4);
					ResetTimer(Phase_Timer, 6000);
					pSummon = NULL;
				}
			}else if(IsTimerFinished(Phase_Timer) && GetPhase() == 4)
			{
				pSummon = SpawnCreature(ENTRY_SKYRISS , 445.763f, -191.639f, 44.64f, 1.60f);
				if(pSummon!=NULL)
					Emote("Yes, O great one, right away!", Text_Yell, 11228);
			}
			ParentClass::AIUpdate();


}
	protected:

		uint32 Phasepart;
		uint32 NPC_ID_Spawn;
		uint32 Spawncounter;
		int32 Phase_Timer;
		MoonInstanceScript* mInstance;
		MoonScriptCreatureAI* pSummon;
		Creature* Millhouse;
};

void SetupArcatraz(ScriptMgr* mgr)
{
	mgr->register_instance_script(552, &ArcatrazInstanceScript::Create);
	mgr->register_creature_script(CN_ZEREKETH, &ZerekethAI::Create);
	mgr->register_creature_script(CN_VOIDZONEARC, &VoidZoneARC::Create);

	mgr->register_creature_script(CN_DALLIAH_THE_DOOMSAYER, &DalliahTheDoomsayerAI::Create);
	mgr->register_creature_script(CN_WRATH_SCRYER_SOCCOTHRATES, &WrathScryerSoccothratesAI::Create);
	mgr->register_creature_script(CN_HARBRINGER_SKYRISS, &HarbringerSkyrissAI::Create);
	//mgr->register_creature_script(CN_WARDEN_MELLICHAR, &WardenMellicharAI::Create);
}
