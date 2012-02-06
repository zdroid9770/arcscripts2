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
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)	// Comment any script to disable it
{
	ThreadPool.ExecuteTask(new ArcScripts2());

	//CREATURE
	SetupArathiHighlandsCreature(mgr);
	SetupBladeEdgeMountainsCreature(mgr);
	SetupBlastedLandsCreature(mgr);
	SetupBloodmystIsleCreature(mgr);
	SetupBoreanTundraCreature(mgr);
	SetupDarkmoonFaireCreatures(mgr);
	SetupDurotarCreature(mgr);
	SetupElwynForestCreature(mgr);
	SetupEmoteCreatures(mgr);
	SetupFlightMasterCreatures(mgr);
	SetupHellfireCreatures(mgr);
	SetupMiscCreatures(mgr);
	SetupOrgrimmarCreature(mgr);
	SetupShadowmoonValleyCreature(mgr);
	SetupSilverpineForestCreature(mgr);
	SetupSoundCreature(mgr);
	SetupTanarisCreature(mgr);
	SetupTheBarrensCreature(mgr);
	SetupTheScarletEnclaveCreature(mgr);
	SetupWesternPlaguelandsCreature(mgr);

	//EVENTS
	SetupWinterVeil(mgr);
	SetupHalloween(mgr);

	//EXTRA
	SetupNeutralGuards(mgr);

	//GAME OBJECT
	SetupAzuremystIsleGameobjects(mgr);
	SetupBlackrockMountainGameobjects(mgr);
	SetupBladeEdgeMountainsGameobjects(mgr);
	SetupBloodmystIsleGameobjects(mgr);
	SetupBoreanTundraGameobjects(mgr);
	SetupBurningSteppesGameobjects(mgr);
	SetupCrystalsongForestGameobjects(mgr);
	SetupDarkshoreGameobjects(mgr);
	SetupDesolaceGameobjects(mgr);
	SetupHellfirePeninsulaGameobjects(mgr);
	SetupMiscGameobjects(mgr);
	SetupNagrandGameobjects(mgr);
	SetupNetherstormGameobjects(mgr);
	SetupSilverpineForestGameobjects(mgr);
	SetupTanarisGameobjects(mgr);
	SetupTerokkarForestGameobjects(mgr);
	SetupTheHinterlandsGameobjects(mgr);
	SetupTheScarletEnclaveGameObject(mgr);
	SetupThousandNeedlesGameobjects(mgr);
	SetupTirisfalGladesGameobjects(mgr);
	SetupWesternPlaguelandsGameobjects(mgr);
	SetupZulDrakGameobjects(mgr);

	//GOSSIP
	SetupCrystalsongForestGossip(mgr);
	SetupInnkeepers(mgr);
	SetupTrainerScript(mgr);
	SetupMulgoreGossip(mgr);
	SetupTerrokarForestGossip(mgr);
	SetupTanarisGossip(mgr);
	SetupMoongladeGossip(mgr);
	SetupElwynForestGossip(mgr);
	SetupTeldrassilGossip(mgr);
	SetupTirisfalGladesGossip(mgr);
	SetupDunMoroghGossip(mgr);
	SetupCrystalsongForestGossip(mgr);
	SetupTheramoreGossip(mgr);
	SetupDarkmoonFaireGossip(mgr);
	SetupBoreanTundraGossip(mgr);
	SetupDragonblightGossip(mgr);
	SetupGeneralGossip(mgr);
	SetupBlastedLandsGossip(mgr);
	SetupAzureMystIsleGossip(mgr);
	SetupDuratorGossip(mgr);
	SetupEversongWoodsGossip(mgr);

	//INSTANCES
	SetupArcatraz(mgr);
	SetupAuchenaiCrypts(mgr);
	SetupAzjolNerub(mgr);
	SetupTheBlackMorass(mgr);
	SetupBlackfathomDeeps(mgr);
	SetupBlackrockDepths(mgr);
	SetupBlackrockSpire(mgr);
	SetupBloodFurnace(mgr);
	SetupBotanica(mgr);
	SetupCullingOfStratholme(mgr);
	SetupDrakTharonKeep(mgr);
	SetupForgeOfSouls(mgr);
	SetupDeadmines(mgr);
	SetupDireMaul(mgr);
	SetupGundrak(mgr);
	SetupHellfireRamparts(mgr);
	SetupHallsOfStone(mgr);
	SetupHallsOfLightning(mgr);
	SetupHallsOfReflection(mgr);
	SetupManaTombs(mgr);
	SetupMaraudon(mgr);
	SetupNexus(mgr);
	SetupOldHillsbradFoothills(mgr);
	SetupPitOfSaron(mgr);
	SetupRagefireChasm(mgr);
	SetupRazorfenDowns(mgr);
	SetupScarletMonastery(mgr);
	SetupScholomance(mgr);
	SetupSethekkHalls(mgr);
	SetupShadowfangKeep(mgr);
	SetupShadowLabyrinth(mgr);
	SetupTrialOfChampionHold(mgr);
	SetupTheMechanar(mgr);
	SetupTheOculus(mgr);
	SetupTheShatteredHalls(mgr);
	SetupTheSlavePens(mgr);
	SetupTheSteamvault(mgr);
	SetupTheUnderbog(mgr);
	SetupUldaman(mgr);
	SetupUtgardeKeep(mgr);
	SetupTheStockade(mgr);
	SetupVioletHold(mgr);
	SetupWailingCaverns(mgr);
	SetupMagistersTerrace(mgr);

	//RAIDS
	SetupBlackTemple(mgr);
	SetupBlackwingLair(mgr);
	SetupBattleOfMountHyjal(mgr);
	SetupGruulsLair(mgr);
	SetupKarazhan(mgr);
	SetupMoltenCore(mgr);
	SetupNaxxramas(mgr);
	SetupOnyxiasLair(mgr);
	SetupTheEye(mgr);
	SetupTheObsidianSanctum(mgr);
	SetupUlduar(mgr);
	SetupZulFarrak(mgr);
	SetupZulGurub(mgr);
	SetupSerpentshrineCavern(mgr);
	SetupMagtheridonsLair(mgr);
	SetupSunwellPlateau(mgr);
	SetupWorldBosses(mgr);
	SetupZulAman(mgr);
	SetupIcecrownCitadel(mgr);
	SetupRubySanctum(mgr);
	SetupRuinsOfAhnQiraj(mgr);
	SetupTempleOfAhnQiraj(mgr);
	SetupRuinsOfAhnQiraj(mgr);
	SetupVaultOfArchavon(mgr);

	//QUEST
	SetupDruid(mgr);
	SetupMage(mgr);
	SetupPaladin(mgr);
	SetupWarrior(mgr);
	SetupFirstAid(mgr);
	SetupArathiHighlands(mgr);
	SetupAzshara(mgr);
	SetupAzuremystIsle(mgr);
	SetupBladeEdgeMountains(mgr);
	SetupBlastedLands(mgr);
	SetupBloodmystIsle(mgr);
	SetupBurningSteppes(mgr);
	SetupDarkshore(mgr);
	SetupDeathKnight(mgr);
	SetupDesolace(mgr);
	SetupDragonblight(mgr);
	SetupDuskwood(mgr);
	SetupDustwallowMarsh(mgr);
	SetupEasternPlaguelands(mgr);
	SetupEversongWoods(mgr);
	SetupGhostlands(mgr);
	SetupHellfirePeninsula(mgr);
	SetupHillsbradFoothills(mgr);
	SetupHowlingFjord(mgr);
	SetupIsleOfQuelDanas(mgr);
	SetupLochModan(mgr);
	SetupMulgore(mgr);
	SetupNagrand(mgr);
	SetupNetherstorm(mgr);
	SetupRedrigeMountains(mgr);
	SetupShadowmoon(mgr);
	SetupSilithus(mgr);
	SetupSilvermoonCity(mgr);
	SetupSilverpineForest(mgr);
	SetupStormwind(mgr);
	SetupStranglethornVale(mgr);
	SetupTanaris(mgr);
	SetupTeldrassil(mgr);
	SetupTerrokarForest(mgr);
	SetupTheStormPeaks(mgr);
	SetupThousandNeedles(mgr);
	SetupTirisfalGlades(mgr);
	SetupUndercity(mgr);
	SetupUnGoro(mgr);
	SetupWestfall(mgr);
	SetupWinterspring(mgr);
	SetupZangarmarsh(mgr);
	SetupBarrens(mgr);
	SetupBoreanTundra(mgr);
	SetupSholazarBasin(mgr);
	SetupQuestGossip(mgr);
	SetupQuestHooks(mgr);
	SetupUnsorted(mgr);
	SetupZulDrak(mgr);
	SetupIcecrown(mgr);
}

#ifdef WIN32

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

#endif

SP_AI_Spell::SP_AI_Spell()
{
	info					= NULL;
	targettype				= 0;
	instant					= false;
	perctrigger				= 0.0f;
	attackstoptimer			= 0;
	soundid					= 0;
	cooldown				= 0;
	casttime				= 0;
	reqlvl					= 0;
	hpreqtocast				= 0.0f;
	mindist2cast			= 0.0f;
	maxdist2cast			= 0.0f;
	minhp2cast				= 0;
	maxhp2cast				= 0;
}