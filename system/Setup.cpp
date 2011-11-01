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

#include "Setup.h"
#define SKIP_ALLOCATOR_SHARING 1
#include <ScriptSetup.h>

extern "C" SCRIPT_DECL uint32 _exp_get_script_type()
{
	return SCRIPT_TYPE_MISC;
}

extern "C" SCRIPT_DECL void _exp_script_register(ScriptMgr* mgr)	// Comment any script to disable it
{
	//EVENTS
	SetupWinterVeil(mgr);
	SetupHalloween(mgr);

	//EXTRA
	SetupNeutralGuards(mgr);

	//GOSSIP
	SetupInnkeepers(mgr);
	SetupGuardGossip(mgr);
	SetupTrainerScript(mgr);
	SetupMulgoreGossip(mgr);
	SetupShattrathGossip(mgr);
	SetupTanarisGossip(mgr);
	SetupMoongladeGossip(mgr);
	SetupStormwindGossip(mgr);
	SetupTheramoreGossip(mgr);
	SetupTeldrassilGossip(mgr);
	SetupDarkmoonFaireGossip(mgr);
	SetupDarkmoonFaireBarker(mgr);
	SetupBoreanTundraGossip(mgr);
	SetupWyrmrestTempleGossip(mgr);
	SetupXpEliminatorGossip(mgr);

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
	SetupDeadmines(mgr);
	SetupDireMaul(mgr);
	SetupGundrak(mgr);
	SetupHellfireRamparts(mgr);
	SetupHallsOfStone(mgr);
	SetupHallsOfLightning(mgr);
	SetupManaTombs(mgr);
	SetupMaraudon(mgr);
	SetupNexus(mgr);
	SetupOldHillsbradFoothills(mgr);
	SetupRagefireChasm(mgr);
	SetupRazorfenDowns(mgr);
	SetupScarletMonastery(mgr);
	SetupScholomance(mgr);
	SetupSethekkHalls(mgr);
	SetupShadowfangKeep(mgr);
	SetupShadowLabyrinth(mgr);
	SetupTheMechanar(mgr);
	SetupTheShatteredHalls(mgr);
	SetupTheSlavePens(mgr);
	SetupTheSteamvault(mgr);
	SetupTheUnderbog(mgr);
	SetupUldaman(mgr);
	SetupUtgardeKeep(mgr);
	SetupTheStockade(mgr);
	SetupWailingCaverns(mgr);
	SetupMagistersTerrace(mgr);
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

	//MISC
	SetupGoHandlers(mgr);
	SetupRandomScripts(mgr);
	SetupMiscCreatures(mgr);
	SetupDarkmoonFaireObjects(mgr);

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