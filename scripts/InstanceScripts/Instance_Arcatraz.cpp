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

#include "Setup.h"

#define	WARDEN_MELLICHAR 0
#define CN_DALLIAH_THE_DOOMSAYER 20885
#define CN_WRATH_SCRYER_SOCCOTHRATES 20886
#define CN_WARDEN_MELLICHAR	20904

enum InstanceArcatraz
{
    CONTAINMENT_CORE_SECURITY_FIELD_ALPHA = 184318, //door opened when Wrath-Scryer Soccothrates dies
    CONTAINMENT_CORE_SECURITY_FIELD_BETA  = 184319, //door opened when Dalliah the Doomsayer dies
    POD_ALPHA                             = 183961, //pod first boss wave
    POD_BETA                              = 183963, //pod second boss wave
    POD_DELTA                             = 183964, //pod third boss wave
    POD_GAMMA                             = 183962, //pod fourth boss wave
    POD_OMEGA                             = 183965, //pod fifth boss wave
    WARDENS_SHIELD                        = 184802, // warden shield

    NPC_MELLICHAR						= 20904 //skyriss will kill this unit
};

static Location pWardenSummons[]=
{
	{},
    {478.326f, -148.505f, 42.56f, 3.19f},                   // Trickster or Phase Hunter
    {413.292f, -148.378f, 42.56f, 6.27f},                   // Millhouse
    {420.179f, -174.396f, 42.58f, 0.02f},                   // Akkiris or Sulfuron
    {471.795f, -174.58f, 42.58f, 3.06f},                    // Twilight or Blackwing Drakonaar
    {445.763f, -191.639f, 44.64f, 1.60f}                    // Skyriss
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
    NPC_SKYRISS      = 20912
};

// Zereketh the UnboundAI
#define CN_ZEREKETH			20870
#define CN_VOIDZONEARC		21101

#define SEED_OF_C			36123
#define SHADOW_NOVA			36127
#define CONSUMPTION			30498
#define VOID_ZONE 36119

class ZerekethAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ZerekethAI)
		ZerekethAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			SpeechTimer = (40+rand()%11) * 1000;
			SeedTimer		= (14+rand()%14)*1000;
			ShadowNovaTimer	= (15+rand()%6)*1000;
			VoidZoneTimer	= (21+rand()%12)*1000;
			AddEmote(Event_OnCombatStart, "Life energy to... consume.", Text_Yell, 11250);
			AddEmote(Event_OnTargetDied, "This vessel...is empty.", Text_Yell, 11251);
			AddEmote(Event_OnTargetDied, "No... more... life.", Text_Yell, 11252);
			AddEmote(Event_OnDied, "The Void... beckons.", Text_Yell, 11255);
			AddSpell(VOID_ZONE, Target_Destination, 20, 0, -1);
			AddSpell(SEED_OF_C, Target_RandomPlayer, 25, 3, -1);
			SpellDesc* mShadowNova = AddSpell(SHADOW_NOVA, Target_RandomPlayer, 25, 3, -1);
				mShadowNova->AddEmote("The shadow... will engulf you.", Text_Yell, 11253);
				mShadowNova->AddEmote("Darkness...consumes...all.", Text_Yell, 11254);
		}

		void AIUpdate()
		{
			if(SpeechTimer < mAIUpdateFrequency)
			{
				if(rand()%2)
					Emote("The shadow... will engulf you.", Text_Yell, 11253);
				else 
					Emote("Darkness... consumes all.", Text_Yell, 11254);

				SpeechTimer = (40+rand()%11) * 1000;
			}
			else 
				SpeechTimer -= mAIUpdateFrequency;
			MoonScriptCreatureAI::AIUpdate();
		}

	protected:
		uint32 SpeechTimer;
		uint32 SeedTimer;
		uint32 ShadowNovaTimer;
		uint32 VoidZoneTimer;
};

class VoidZoneARC : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(VoidZoneARC)
		VoidZoneARC(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			_unit->Unroot();
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			RegisterAIUpdateEvent(1000);
		}

		void AIUpdate()
		{
			_unit->CastSpell(_unit, dbcSpell.LookupEntry(CONSUMPTION), true);
			RemoveAIUpdateEvent();
			MoonScriptCreatureAI::AIUpdate();
		}
};

// Dalliah the DoomsayerAI
#define GIFT_OF_THE_DOOMSAYER 36173
#define WHIRLWIND 36175
#define HEAL 36144
#define SHADOW_WAVE 39016	// Heroic mode spell

class DalliahTheDoomsayerAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(DalliahTheDoomsayerAI)
		DalliahTheDoomsayerAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
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

class WrathScryerSoccothratesAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WrathScryerSoccothratesAI)
		WrathScryerSoccothratesAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
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

class HarbringerSkyrissAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(HarbringerSkyrissAI)
		HarbringerSkyrissAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			AddEmote(Event_OnCombatStart, "Bear witness to the agent of your demise!", Text_Yell, 11123);
			AddEmote(Event_OnTargetDied, "Your fate is written!", Text_Yell, 11124);
			AddEmote(Event_OnTargetDied, "The chaos I have sown here is but a taste....", Text_Yell, 11125);
			AddEmote(Event_OnDied, "I am merely one of... infinite multitudes.", Text_Yell, 11126);

			AddSpell(MIND_REND, Target_Current, 15.0f, 0, -1);
			SpellDesc* Fear = AddSpell(FEAR, Target_Current, 8.0f, 0, -1);
				Fear->AddEmote("Flee in terror!", Text_Yell, 11129);
				Fear->AddEmote("I will show you horrors undreamed of.", Text_Yell, 11130);

			SpellDesc* Domination = AddSpell(DOMINATION, Target_Current, 6.0f, 0, -1);
				Domination->AddEmote("You will do my bidding, weakling.", Text_Yell, 11127);
				Domination->AddEmote("Your will is no longer your own.", Text_Yell, 11128);

			IllusionCount = 0;
		}

		void OnCombatStop(Unit* pUnit)
		{
			IllusionCount = 0;
		}

		void AIUpdate()
		{
			if(GetHealthPercent() <= 66 && IllusionCount == 0)
			{
				_unit->CastSpell(_unit, SUMMON_ILLUSION_66, true);
				_unit->PlaySoundToSet(11131);
				IllusionCount++;
			}
			else if(GetHealthPercent() <= 33 && IllusionCount == 1)
			{
				_unit->CastSpell(_unit, SUMMON_ILLUSION_33, true);
				_unit->PlaySoundToSet(11131);
				IllusionCount++;
			}
		}

	private:
		uint32 IllusionCount;
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

class WardenMellicharAI : public MoonScriptBossAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(WardenMellicharAI)
		WardenMellicharAI(Creature* pCreature) : MoonScriptBossAI(pCreature)
		{
			SetCanMove(false);
			mInstance = GetInstanceScript();
			mIntroSpell = 0;
			pMainGO = GetNearestGameObject(POD_OMEGA);
		}

		void OnCombatStart(Unit* mTarget)
		{
			SetCanEnterCombat(false);
			SetCanMove(false);
			SetAllowMelee(false);
			SetAllowSpell(false);
			_unit->Emote(EMOTE_ONESHOT_NONE);

			Phase_Timer = AddTimer(22000);

			Emote("I knew the prince would be angry but, I... I have not been myself. I had to let them out! The great one speaks to me, you see. Wait--outsiders. Kael'thas did not send you! Good... I'll just tell the prince you released the prisoners!", Text_Yell, 11222);
			if(mIntroSpell == 0)
			{
				_unit->CastSpell(_unit, dbcSpell.LookupEntryForced(SPELL_BUBBLE_VISUAL), true);
				mIntroSpell++;
			}

			if(mInstance)
				mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 0);

			MoonScriptBossAI::OnCombatStop(mTarget);
		}

		void AIUpdate()
		{
			switch(GetPhase())
			{
				case 1:
				{
					if(IsTimerFinished(Phase_Timer) && mInstance)
					{
						Emote("The naaru kept some of the most dangerous beings in existence here in these cells. Let me introduce you to another...", Text_Yell, 11223);
						if(mIntroSpell == 1)
						{
							_unit->CastSpell(_unit, dbcSpell.LookupEntryForced(SPELL_TARGET_ALPHA), true);
							mInstance->SetInstanceData(WARDEN_MELLICHAR, 1);
							mIntroSpell++;
						}
					}
				}break;
				case 2:
				{
					Emote("Yes, yes... another! Your will is mine! Behold another terrifying creature of incomprehensible power!", Text_Yell, 11224);
					
					if(mIntroSpell == 2 && mInstance)
					{
						_unit->CastSpell(_unit, SPELL_TARGET_BETA, true);
						mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 2);
						mIntroSpell++;
					}

					ResetTimer(Phase_Timer, 13*SEC_IN_MS);
					SetPhase(3);
				case 3:
					MoonScriptCreatureAI* Millhouse = SpawnCreature(ENTRY_MILLHOUSE, pWardenSummons[1].x, pWardenSummons[1].y, pWardenSummons[1].z, pWardenSummons[1].o);
					if(!Millhouse)
						return;

					uint32 TalkTimer = 2*SEC_IN_MS;
					Millhouse->Emote("Where in Bonzo's brass buttons am I? And who are-- yaaghh, that's one mother of a headache!", Text_Yell, 11171, EMOTE_ONESHOT_NONE, TalkTimer);
					TalkTimer += 11*SEC_IN_MS;
					Emote("What is this? A lowly gnome? I will do better, oh great one.", Text_Yell, 11226, EMOTE_ONESHOT_NONE, TalkTimer);
					TalkTimer += 9*SEC_IN_MS;
					Millhouse->Emote("Lowly? Nobody refers to the mighty Millhouse Manastorm as lowly! I have no idea what goes on here, but I will gladly join your fight against this impudent imbecile!", Text_Yell, 11172, EMOTE_ONESHOT_NONE, TalkTimer);


					if(IsTimerFinished(Phase_Timer))
					{
						if(mIntroSpell == 3 && mInstance)
						{
							_unit->CastSpell(_unit, dbcSpell.LookupEntryForced(SPELL_TARGET_DELTA), true);
							mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 3);
							mIntroSpell++;
						}

						SetPhase(4);
					}
				}break;
				case 4:
				{
					Emote("Anarchy! Bedlam! Oh, you are so wise! Yes, I see it now, of course!", Text_Yell, 11227);
					if(mIntroSpell == 3 && mInstance)
					{
						_unit->CastSpell(_unit, dbcSpell.LookupEntryForced(SPELL_TARGET_DELTA), true);
						mInstance->SetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR, 4);
						mIntroSpell++;
					}
				}break;
				case 5: Emote("Yes, O great one, right away!", Text_Yell, 11228); break;	//need correction
			}
			_unit->CastSpell(_unit, dbcSpell.LookupEntryForced(SPELL_TARGET_OMEGA), true);
		}

	protected:
		uint8 mIntroSpell;
		int32 Phase_Timer;
		MoonInstanceScript* mInstance;
		GameObject* pMainGO;
};

class ArcatrazInstanceScript : public MoonInstanceScript
{
	public:
		MOONSCRIPT_INSTANCE_FACTORY_FUNCTION(ArcatrazInstanceScript, MoonInstanceScript);
		ArcatrazInstanceScript(MapMgr* pMapMgr) : MoonInstanceScript(pMapMgr) 
		{
			WardenShieldGuid = 0;
			CoreSecurityAlphaGuid = 0;
			CoreSecurityBetaGuid = 0;

			for(uint32 i=0; i<4; i++)
				OrbGuid[i] = 0;

			WardenMilicharGuid = 0;

			SummonTimer = -1;
		}

		friend class WardenMellicharAI;

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

		void OnCreaturePushToWorld(Creature* pCreature)
		{
			if(pCreature->GetEntry() == CN_WARDEN_MELLICHAR)
				WardenMilicharGuid = pCreature->GetLowGUID();
		}

		void OnCreatureDeath(Creature* pCreature, Unit* pUnit)
		{		
			switch(pCreature->GetEntry())
			{
				case CN_DALLIAH_THE_DOOMSAYER:
				{
					if(GameObject* pGo = GetGameObjectByGuid(CoreSecurityBetaGuid))
						pGo->SetState(GAMEOBJECT_STATE_OPEN);
				}break;
				case CN_WRATH_SCRYER_SOCCOTHRATES:
				{
					if(GameObject* pGo2 = GetGameObjectByGuid(CoreSecurityAlphaGuid))
						pGo2->SetState(GAMEOBJECT_STATE_OPEN);
				}break;
				//warden milchar event related
				case ENTRY_TRICKSTER:
				case ENTRY_PH_HUNTER:
				{
					WardenMellicharAI* pWarden = (WardenMellicharAI *)GetCreatureByGuid(WardenMilicharGuid)->GetScript();
					if(pWarden)
						pWarden->SetPhase(2);
				}break;
				case ENTRY_AKKIRIS:
				case ENTRY_SULFURON:
				{
					WardenMellicharAI* pWarden = (WardenMellicharAI *)GetCreatureByGuid(WardenMilicharGuid)->GetScript();
					if(pWarden)
						pWarden->SetPhase(4);
				}break;
				case ENTRY_TW_DRAK:
				case ENTRY_BL_DRAK:
				{
					WardenMellicharAI* pWarden = (WardenMellicharAI *)GetCreatureByGuid(WardenMilicharGuid)->GetScript();
					if(pWarden)
						pWarden->SetPhase(5);
				}break;
			}
		}

		uint32 GetInstanceData(uint32 pType, uint32 pIndex)
		{
			return mEncounters[pIndex];
		}

		void SetInstanceData(uint32 pType, uint32 pIndex, uint32 pData)
		{
			if(pIndex == WARDEN_MELLICHAR)
			{
				WardenMellicharAI* pWarden = (WardenMellicharAI *)GetCreatureByGuid(WardenMilicharGuid)->GetScript();
				switch(pData)
				{
					case 0:	//OnCombat
					{
						if(GameObject* pGo = GetGameObjectByGuid(WardenShieldGuid))
						{
							if(pWarden)
								pWarden->SetFacingToObject(pGo);

							pGo->SetState(GAMEOBJECT_STATE_OPEN);
						}
					}break;
					case 1:	//first orb
					{
						if(GameObject* pGo = GetGameObjectByGuid(OrbGuid[0]))
						{
							if(pWarden)
								pWarden->SetFacingToObject(pGo);
							pGo->SetState(GAMEOBJECT_STATE_OPEN);
						}
					}break;
					case 2:	//second orb
					{
						if(GameObject* pGo = GetGameObjectByGuid(OrbGuid[1]))
						{
							if(pWarden)
								pWarden->SetFacingToObject(pGo);
							pGo->SetState(GAMEOBJECT_STATE_OPEN);
						}
					}break;
					case 3:	//third orb
					{
						if(GameObject* pGo = GetGameObjectByGuid(OrbGuid[2]))
						{
							if(pWarden)
								pWarden->SetFacingToObject(pGo);
							pGo->SetState(GAMEOBJECT_STATE_OPEN);
						}
					}break;
					case 4:	//four orb
					{
						if(GameObject* pGo = GetGameObjectByGuid(OrbGuid[3]))
						{
							if(pWarden)
								pWarden->SetFacingToObject(pGo);
							pGo->SetState(GAMEOBJECT_STATE_OPEN);
						}
					}break;
				}

				//no need on 0 (agroo event)
				if(pData > 0)
					SummonTimer = AddTimer(10*SEC_IN_MS);
			}
			mEncounters[pIndex] = pData;
		}

		void UpdateEvent()
		{
			uint32 pSummonEntry = 0;
			uint32 pData = GetInstanceData(Data_UnspecifiedType, WARDEN_MELLICHAR);
			if(IsTimerFinished(SummonTimer))
			{
				switch(pData)
				{
					case 1: pSummonEntry = rand()%2 ? ENTRY_TRICKSTER : ENTRY_PH_HUNTER; break;
					case 3: pSummonEntry = rand()%2 ? ENTRY_AKKIRIS : ENTRY_SULFURON; break;
					case 4: pSummonEntry = rand()%2 ? ENTRY_TW_DRAK : ENTRY_BL_DRAK; break;
					default:
						break;
				}

				SpawnCreature(pSummonEntry, pWardenSummons[pData].x, pWardenSummons[pData].y, pWardenSummons[pData].z, pWardenSummons[pData].o);
				RemoveTimer(SummonTimer);
			}
			MoonInstanceScript::UpdateEvent();
		}

	private:
		int32 SummonTimer;
		uint32 WardenShieldGuid;
		uint32 CoreSecurityAlphaGuid;
		uint32 CoreSecurityBetaGuid;
		uint32 OrbGuid[3];
		uint32 mEncounters[1];
		uint32 WardenMilicharGuid;
};

void SetupArcatraz(ScriptMgr* mgr)
{
	mgr->register_instance_script(552, &ArcatrazInstanceScript::Create);
	mgr->register_creature_script(CN_ZEREKETH, &ZerekethAI::Create);
	mgr->register_creature_script(CN_VOIDZONEARC, &VoidZoneARC::Create);

	mgr->register_creature_script(CN_DALLIAH_THE_DOOMSAYER, &DalliahTheDoomsayerAI::Create);
	mgr->register_creature_script(CN_WRATH_SCRYER_SOCCOTHRATES, &WrathScryerSoccothratesAI::Create);
	mgr->register_creature_script(NPC_SKYRISS, &HarbringerSkyrissAI::Create);
	mgr->register_creature_script(NPC_MELLICHAR, &WardenMellicharAI::Create);
}
