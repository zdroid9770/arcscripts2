/*
 * ArcScripts2 for ArcEmu MMORPG Server
 * Copyright (C) 2011 ArcScripts2 Team <http://www.arcemu.org/>
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

#include "StdAfx.h"
#include "System.h"
#include "../dependencies/EasyFunctions.h"
#include "../dependencies/MoonInstanceScript.h"
#include "../dependencies/MoonScriptBossAI.h"
#include "../dependencies/MoonScriptCreatureAI.h"

//////////////////Macros
//used on creature ai scripts
#define MOONSCRIPT_FACTORY_FUNCTION(ClassName, ParentClassName)\
	ADD_CREATURE_FACTORY_FUNCTION(ClassName);\
	typedef ParentClassName ParentClass;

//used on instance scripts
#define MOONSCRIPT_INSTANCE_FACTORY_FUNCTION( ClassName, ParentClassName ) \
public:\
	ADD_INSTANCE_FACTORY_FUNCTION( ClassName );\
	typedef ParentClassName ParentClass;

////////////////Timers
#define INVALIDATE_TIMER			-1
#define DEFAULT_UPDATE_FREQUENCY	1000	//milliseconds
#define DEFAULT_DESPAWN_TIMER		2000	//milliseconds
#define MINUTE						60		//1 min = 60 seconds
#define SEC_IN_MS					1000	//1 sec = 1000 milliseconds


#ifndef SETUP
#define SETUP

//CREATURES
void SetupArathiHighlandsCreature(ScriptMgr * mgr);
void SetupBladeEdgeMountainsCreature(ScriptMgr * mgr);
void SetupBlastedLandsCreature(ScriptMgr * mgr);
void SetupBloodmystIsleCreature(ScriptMgr * mgr);
void SetupBoreanTundraCreature(ScriptMgr * mgr);
void SetupDarkmoonFaireCreatures(ScriptMgr * mgr);
void SetupDurotarCreature(ScriptMgr * mgr);
void SetupElwynForestCreature(ScriptMgr * mgr);
void SetupEmoteCreatures(ScriptMgr * mgr);
void SetupFlightMasterCreatures(ScriptMgr * mgr);
void SetupHellfireCreatures(ScriptMgr * mgr);
void SetupMiscCreatures(ScriptMgr * mgr);
void SetupOrgrimmarCreature(ScriptMgr * mgr);
void SetupShadowmoonValleyCreature(ScriptMgr * mgr);
void SetupSilverpineForestCreature(ScriptMgr * mgr);
void SetupSoundCreature(ScriptMgr * mgr);
void SetupTanarisCreature(ScriptMgr * mgr);
void SetupTheBarrensCreature(ScriptMgr * mgr);
void SetupTheScarletEnclaveCreature(ScriptMgr * mgr);
void SetupWesternPlaguelandsCreature(ScriptMgr * mgr);
void SetupTransportCreatureScripts(ScriptMgr * mgr);

//EVENT
void SetupWinterVeil(ScriptMgr* mgr);
void SetupHalloween(ScriptMgr* mgr);

//EXTRA
void SetupNeutralGuards(ScriptMgr* mgr);

//GAME OBJECTS
void SetupAzuremystIsleGameobjects(ScriptMgr * mgr);
void SetupBlackrockMountainGameobjects(ScriptMgr * mgr);
void SetupBladeEdgeMountainsGameobjects(ScriptMgr * mgr);
void SetupBloodmystIsleGameobjects(ScriptMgr * mgr);
void SetupBoreanTundraGameobjects(ScriptMgr * mgr);
void SetupBurningSteppesGameobjects(ScriptMgr * mgr);
void SetupDarkshoreGameobjects(ScriptMgr * mgr);
void SetupDesolaceGameobjects(ScriptMgr * mgr);
void SetupHellfirePeninsulaGameobjects(ScriptMgr * mgr);
void SetupMiscGameobjects(ScriptMgr * mgr);
void SetupNagrandGameobjects(ScriptMgr * mgr);
void SetupNetherstormGameobjects(ScriptMgr * mgr);
void SetupSilverpineForestGameobjects(ScriptMgr * mgr);
void SetupTanarisGameobjects(ScriptMgr * mgr);
void SetupTerokkarForestGameobjects(ScriptMgr * mgr);
void SetupTheHinterlandsGameobjects(ScriptMgr * mgr);
void SetupTheScarletEnclaveGameObject(ScriptMgr * mgr);
void SetupThousandNeedlesGameobjects(ScriptMgr * mgr);
void SetupTirisfalGladesGameobjects(ScriptMgr * mgr);
void SetupWesternPlaguelandsGameobjects(ScriptMgr * mgr);
void SetupZulDrakGameobjects(ScriptMgr * mgr);

//GOSSIP
void SetupInnkeepers(ScriptMgr* mgr);
void SetupGuardGossip(ScriptMgr* mgr);
void SetupTrainerScript(ScriptMgr* mgr);
void SetupMulgoreGossip(ScriptMgr* mgr);
void SetupShattrathGossip(ScriptMgr* mgr);
void SetupTanarisGossip(ScriptMgr* mgr);
void SetupMoongladeGossip(ScriptMgr* mgr);
void SetupStormwindGossip(ScriptMgr* mgr);
void SetupDarnassusGossip(ScriptMgr* mgr);
void SetupUndercityGossip(ScriptMgr* mgr);
void SetupIronforgeGossip(ScriptMgr* mgr);
void SetupDalaranGossip(ScriptMgr* mgr);
void SetupTheramoreGossip(ScriptMgr* mgr);
void SetupDarkmoonFaireGossip(ScriptMgr* mgr);
void SetupTeldrassilGossip(ScriptMgr* mgr);
void SetupBoreanTundraGossip(ScriptMgr* mgr);
void SetupDragonblightGossip(ScriptMgr* mgr);
void SetupGeneralGossip(ScriptMgr* mgr);
void SetupBlastedLandsGossip(ScriptMgr* mgr);

//INSTANCE
void SetupArcatraz(ScriptMgr* mgr);
void SetupAuchenaiCrypts(ScriptMgr* mgr);
void SetupAzjolNerub(ScriptMgr* mgr) ;
void SetupTheBlackMorass(ScriptMgr* mgr);
void SetupBlackfathomDeeps( ScriptMgr *mgr );
void SetupBlackrockSpire(ScriptMgr* mgr);
void SetupBlackrockDepths(ScriptMgr* mgr);
void SetupBloodFurnace(ScriptMgr* mgr);
void SetupBotanica(ScriptMgr* mgr);
void SetupCullingOfStratholme(ScriptMgr* mgr);
void SetupDrakTharonKeep(ScriptMgr* pScriptMgr);
void SetupForgeOfSouls(ScriptMgr * mgr);
void SetupDeadmines(ScriptMgr* mgr);
void SetupDireMaul(ScriptMgr* mgr);
void SetupGundrak(ScriptMgr* mgr);
void SetupHellfireRamparts(ScriptMgr* mgr);
void SetupHallsOfStone(ScriptMgr* mgr);
void SetupHallsOfLightning(ScriptMgr* mgr);
void SetupHallsOfReflection(ScriptMgr * mgr);
void SetupManaTombs(ScriptMgr* mgr);
void SetupMaraudon(ScriptMgr* mgr);
void SetupNexus(ScriptMgr* mgr);
void SetupOldHillsbradFoothills(ScriptMgr* mgr);
void SetupPitOfSaron(ScriptMgr * mgr);
void SetupRagefireChasm(ScriptMgr* mgr);
void SetupRazorfenDowns(ScriptMgr* mgr);
void SetupScarletMonastery(ScriptMgr* mgr);
void SetupScholomance(ScriptMgr* mgr);
void SetupSethekkHalls(ScriptMgr* mgr);
void SetupShadowfangKeep(ScriptMgr* mgr);
void SetupShadowLabyrinth(ScriptMgr* mgr);
void SetupTrialOfChampionHold(ScriptMgr * mgr);
void SetupTheMechanar(ScriptMgr* mgr);
void SetupTheOculus(ScriptMgr * mgr);
void SetupTheShatteredHalls(ScriptMgr* mgr);
void SetupTheSlavePens(ScriptMgr* mgr);
void SetupTheSteamvault(ScriptMgr* mgr);
void SetupTheUnderbog(ScriptMgr* mgr);
void SetupUldaman(ScriptMgr* mgr);
void SetupUtgardeKeep(ScriptMgr* mgr);
void SetupTheStockade(ScriptMgr* mgr);
void SetupVioletHold(ScriptMgr * mgr);
void SetupWailingCaverns(ScriptMgr* mgr);
void SetupMagistersTerrace(ScriptMgr* mgr);

//RAIDS
void SetupBlackTemple(ScriptMgr* mgr);
void SetupBlackwingLair(ScriptMgr* mgr);
void SetupBattleOfMountHyjal(ScriptMgr* mgr);
void SetupGruulsLair(ScriptMgr* mgr);
void SetupKarazhan(ScriptMgr* mgr);
void SetupMoltenCore(ScriptMgr* mgr);
void SetupNaxxramas(ScriptMgr* mgr);
void SetupOnyxiasLair(ScriptMgr* mgr);
void SetupTheEye(ScriptMgr* mgr);
void SetupTheObsidianSanctum(ScriptMgr* mgr);
void SetupUlduar(ScriptMgr* mgr);
void SetupZulFarrak(ScriptMgr* mgr);
void SetupZulGurub(ScriptMgr* mgr);
void SetupSerpentshrineCavern(ScriptMgr* mgr);
void SetupMagtheridonsLair(ScriptMgr* mgr);
void SetupSunwellPlateau(ScriptMgr* pScriptMgr);
void SetupWorldBosses(ScriptMgr* mgr);
void SetupZulAman(ScriptMgr* mgr);
void SetupIcecrownCitadel(ScriptMgr* mgr);
void SetupRubySanctum(ScriptMgr* mgr);
void SetupTempleOfAhnQiraj(ScriptMgr* mgr);
void SetupRuinsOfAhnQiraj(ScriptMgr* mgr);

//QUEST
void SetupDruid(ScriptMgr* mgr);
void SetupMage(ScriptMgr* mgr);
void SetupPaladin(ScriptMgr* mgr);
void SetupWarrior(ScriptMgr* mgr);
void SetupFirstAid(ScriptMgr* mgr);
void SetupArathiHighlands(ScriptMgr* mgr);
void SetupAzshara(ScriptMgr* mgr);
void SetupAzuremystIsle(ScriptMgr* mgr);
void SetupBladeEdgeMountains(ScriptMgr* mgr);
void SetupBlastedLands(ScriptMgr* mgr);
void SetupBloodmystIsle(ScriptMgr* mgr);
void SetupBurningSteppes(ScriptMgr* mgr);
void SetupDarkshore(ScriptMgr * mg);
void SetupDeathKnight(ScriptMgr* mgr);
void SetupDesolace(ScriptMgr* mgr);
void SetupDragonblight(ScriptMgr* mgr);
void SetupDuskwood(ScriptMgr* mgr);
void SetupDustwallowMarsh(ScriptMgr* mgr);
void SetupEasternPlaguelands(ScriptMgr* mgr);
void SetupEversongWoods(ScriptMgr* mgr);
void SetupGhostlands(ScriptMgr* mgr);
void SetupHellfirePeninsula(ScriptMgr* mgr);
void SetupHillsbradFoothills(ScriptMgr* mgr);
void SetupHowlingFjord(ScriptMgr* mgr);
void SetupIsleOfQuelDanas(ScriptMgr* mgr);
void SetupLochModan(ScriptMgr* mgr);
void SetupMulgore(ScriptMgr* mgr);
void SetupNagrand(ScriptMgr* mgr);
void SetupNetherstorm(ScriptMgr* mgr);
void SetupRedrigeMountains(ScriptMgr* mgr);
void SetupShadowmoon(ScriptMgr* mgr);
void SetupSilithus(ScriptMgr* mgr);
void SetupSilvermoonCity(ScriptMgr* mgr);
void SetupSilverpineForest(ScriptMgr* mgr);
void SetupStormwind(ScriptMgr* mgr);
void SetupStranglethornVale(ScriptMgr* mgr);
void SetupTanaris(ScriptMgr* mgr);
void SetupTeldrassil(ScriptMgr* mgr);
void SetupTerrokarForest(ScriptMgr* mgr);
void SetupTheStormPeaks(ScriptMgr* mgr);
void SetupThousandNeedles(ScriptMgr* mgr);
void SetupTirisfalGlades(ScriptMgr* mgr);
void SetupUndercity(ScriptMgr* mgr);
void SetupUnGoro(ScriptMgr* mgr);
void SetupWestfall(ScriptMgr* mgr);
void SetupWinterspring(ScriptMgr* mgr);
void SetupZangarmarsh(ScriptMgr* mgr);
void SetupBarrens(ScriptMgr* mgr);
void SetupBoreanTundra(ScriptMgr* mgr);
void SetupSholazarBasin(ScriptMgr* mgr);
void SetupQuestGossip(ScriptMgr* mgr);
void SetupQuestHooks(ScriptMgr* mgr);
void SetupUnsorted(ScriptMgr* mgr);



struct ScriptSpell
{
	uint32 normal_spellid;
	uint32 heroic_spellid;
	uint32 timer;
	uint32 time;
	uint32 chance;
	uint32 target;
	uint32 phase;
};

enum SPELL_TARGETS
{
    SPELL_TARGET_SELF,
    SPELL_TARGET_CURRENT_ENEMY,
    SPELL_TARGET_RANDOM_PLAYER,
    SPELL_TARGET_SUMMONER,
    SPELL_TARGET_RANDOM_PLAYER_POSITION,
    SPELL_TARGET_GENERATE, // this will send null as target
    SPELL_TARGET_LOWEST_THREAT,
    SPELL_TARGET_CUSTOM,
};

struct SP_AI_Spell
{

	SP_AI_Spell();
	SpellEntry* info;		// spell info
	char targettype;		// 0-self , 1-attaking target, ....
	bool instant;			// does it is instant or not?
	float perctrigger;		// % of the cast of this spell in a total of 100% of the attacks
	int attackstoptimer;	// stop the creature from attacking
	int soundid;			// sound id from DBC
	std::string speech;		// text displaied when spell was casted
	uint32 cooldown;		// spell cooldown
	uint32 casttime;		// "time" left to cast spell
	uint32 reqlvl;			// required level ? needed?
	float hpreqtocast;		// ? needed?
	float mindist2cast;		// min dist from caster to victim to perform cast (dist from caster >= mindist2cast)
	float maxdist2cast;		// max dist from caster to victim to perform cast (dist from caster <= maxdist2cast)
	int minhp2cast;			// min hp amount of victim to perform cast on it (health >= minhp2cast)
	int maxhp2cast;			// max hp amount of victim to perform cast on it (health <= maxhp2cast)
};

enum
{
    TARGET_SELF,
    TARGET_VARIOUS,
    TARGET_ATTACKING,
    TARGET_DESTINATION,
    TARGET_SOURCE,
    TARGET_RANDOM_FRIEND,	// doesn't work yet
    TARGET_RANDOM_SINGLE,
    TARGET_RANDOM_DESTINATION,

    //.....add
};
#endif