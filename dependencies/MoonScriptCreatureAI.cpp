/*
 * Moon++ Scripts for Ascent MMORPG Server
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class TargetType
TargetType::TargetType(uint32 pTargetGen, TargetFilter pTargetFilter, uint32 pMinTargetNumber, uint32 pMaxTargetNumber)
{
	mTargetGenerator = pTargetGen;
	mTargetFilter = pTargetFilter;
	mTargetNumber[ 0 ] = pMinTargetNumber;	// Unused array for now
	mTargetNumber[ 1 ] = pMaxTargetNumber;
}

TargetType::~TargetType()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class SpellDesc
SpellDesc::SpellDesc(SpellEntry* pInfo, SpellFunc pFnc, TargetType pTargetType, float pChance, float pCastTime, int32 pCooldown, float pMinRange, float pMaxRange, bool pStrictRange, const char* pText, TextType pTextType, uint32 pSoundId, const char* pAnnouncement)
{
	mInfo = pInfo;
	mSpellFunc = pFnc;
	mTargetType = pTargetType;
	mChance = max(min(pChance, 100.0f), 0.0f);
	mCastTime = pCastTime;
	mCooldown = pCooldown;
	mMinRange = pMinRange;
	mMaxRange = pMaxRange;
	mStrictRange = pStrictRange;
	mEnabled = true;
	mPredefinedTarget = NULL;
	mLastCastTime = 0;
	AddAnnouncement(pAnnouncement);
	AddEmote(pText, pTextType, pSoundId);
}

SpellDesc::~SpellDesc()
{
	DeleteArray(mEmotes);
}

EmoteDesc* SpellDesc::AddEmote(const char* pText, TextType pType, uint32 pSoundId)
{
	EmoteDesc* NewEmote = NULL;
	if(pText || pSoundId)
	{
		NewEmote = new EmoteDesc(pText, pType, pSoundId);
		mEmotes.push_back(NewEmote);
	}
	return NewEmote;
}

void SpellDesc::TriggerCooldown(uint32 pCurrentTime)
{
	uint32 CurrentTime = (pCurrentTime == 0) ? (uint32)time(NULL) : pCurrentTime;
	mLastCastTime = CurrentTime;
}

void SpellDesc::AddAnnouncement(const char* pText)
{
	mAnnouncement = (pText && strlen(pText) > 0) ? pText : "" ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class MoonScriptCreatureAI
MoonScriptCreatureAI::MoonScriptCreatureAI(Creature* pCreature) : CreatureAIScript(pCreature)
{
	mRunToTargetCache = NULL;
	mRunToTargetSpellCache = NULL;
	mTimerIdCounter = 0;
	mAIUpdateFrequency = DEFAULT_UPDATE_FREQUENCY;
	mBaseAttackTime = _unit->GetBaseAttackTime(MELEE);
	mDespawnWhenInactive = false;
}

MoonScriptCreatureAI::~MoonScriptCreatureAI()
{
	DeleteArray(mOnDiedEmotes);
	DeleteArray(mOnTargetDiedEmotes);
	DeleteArray(mOnCombatStartEmotes);
	DeleteArray(mOnCombatStopEmotes);
	DeleteArray(mOnTauntEmotes);
	DeleteArray(mSpells);
	DeleteArray(mEvents);
}

bool MoonScriptCreatureAI::GetCanMove()
{
	return _unit->GetAIInterface()->m_canMove;
};

void MoonScriptCreatureAI::SetCanMove(bool pCanMove)
{
	pCanMove ? _unit->Unroot() : _unit->Root();
}

void MoonScriptCreatureAI::MoveTo(MoonScriptCreatureAI* pCreature, RangeStatusPair pRangeStatus)
{
	MoveTo(pCreature->_unit, pRangeStatus);
}

void MoonScriptCreatureAI::MoveTo(Unit* pUnit, RangeStatusPair pRangeStatus)
{
	if(pRangeStatus.first == RangeStatus_TooClose)
		_unit->GetAIInterface()->_CalcDestinationAndMove(pUnit, pRangeStatus.second);
	else if(pRangeStatus.first == RangeStatus_TooFar)
		MoveTo(pUnit->GetPositionX(), pUnit->GetPositionY(), pUnit->GetPositionZ());
}

void MoonScriptCreatureAI::MoveTo(float pX, float pY, float pZ, float pO, bool pRun)
{
	if(pRun)
		_unit->GetAIInterface()->SetRun();

	_unit->GetAIInterface()->MoveTo(pX, pY, pZ, pO);
}

void MoonScriptCreatureAI::MoveToSpawnOrigin()
{
	MoveTo(_unit->GetSpawnX(), _unit->GetSpawnY(), _unit->GetSpawnZ());
}

void MoonScriptCreatureAI::StopMovement()
{
	_unit->GetAIInterface()->StopMovement(0);
}

void MoonScriptCreatureAI::SetFlyMode(bool pValue)
{
	if(pValue && !_unit->GetAIInterface()->Flying())
	{
		WorldPacket data(SMSG_MOVE_SET_HOVER, 13);
		data << _unit->GetNewGUID();
		data << uint32(0);
		_unit->SendMessageToSet(&data, false);
		_unit->GetAIInterface()->StopFlying();
	}else if(!pValue && _unit->GetAIInterface()->Flying())
	{
		WorldPacket data(SMSG_MOVE_UNSET_HOVER, 13);
		data << _unit->GetNewGUID();
		data << uint32(0);
		_unit->SendMessageToSet(&data, false);
		_unit->GetAIInterface()->SetFly();
	}
}

void MoonScriptCreatureAI::SetFacingToObject(Object * pObject)
{
	float Facing = _unit->calcRadAngle(_unit->GetPositionX(), _unit->GetPositionY(), pObject->GetPositionX(), pObject->GetPositionY());
	_unit->SetFacing(Facing);
}

bool MoonScriptCreatureAI::GetCanEnterCombat()
{
	return _unit->GetAIInterface()->GetAllowedToEnterCombat();
}

void MoonScriptCreatureAI::SetCanEnterCombat(bool pCanEnterCombat)
{
	_unit->SetUInt64Value(UNIT_FIELD_FLAGS, (pCanEnterCombat) ? 0 : UNIT_FLAG_NOT_ATTACKABLE_9);
	_unit->GetAIInterface()->SetAllowedToEnterCombat(pCanEnterCombat);
}

bool MoonScriptCreatureAI::IsInCombat()
{
	return _unit->CombatStatus.IsInCombat();
}

void MoonScriptCreatureAI::DelayNextAttack(int32 pMilliseconds)
{
	_unit->setAttackTimer(pMilliseconds, false);
}

void MoonScriptCreatureAI::SetDespawnWhenInactive(bool pValue)
{
	mDespawnWhenInactive = pValue;
}

void MoonScriptCreatureAI::SetBehavior(BehaviorType pBehavior)
{
	switch(pBehavior)
	{
		case Behavior_Default: _unit->GetAIInterface()->setCurrentAgent(AGENT_NULL); break;
		case Behavior_Melee: _unit->GetAIInterface()->setCurrentAgent(AGENT_MELEE); break;
		case Behavior_Ranged: _unit->GetAIInterface()->setCurrentAgent(AGENT_RANGED); break;
		case Behavior_Spell: _unit->GetAIInterface()->setCurrentAgent(AGENT_SPELL); break;
		case Behavior_Flee: _unit->GetAIInterface()->setCurrentAgent(AGENT_FLEE); break;
		case Behavior_CallForHelp: _unit->GetAIInterface()->setCurrentAgent(AGENT_CALLFORHELP); break;
		default: sLog.outDebug("ArcScript: MoonScriptCreatureAI::SetBehavior() : Invalid behavior type!"); break;
	}
}

BehaviorType MoonScriptCreatureAI::GetBehavior()
{
	switch(_unit->GetAIInterface()->getCurrentAgent())
	{
		case AGENT_NULL: return Behavior_Default;
		case AGENT_MELEE: return Behavior_Melee;
		case AGENT_RANGED: return Behavior_Ranged;
		case AGENT_FLEE: return Behavior_Flee;
		case AGENT_SPELL: return Behavior_Spell;
		case AGENT_CALLFORHELP: return Behavior_CallForHelp;
		default: sLog.outDebug("ArcScript: MoonScriptCreatureAI::SetBehavior() : Invalid behavior type!"); return Behavior_Default;
	}
}

void MoonScriptCreatureAI::SetAllowMelee(bool pAllow)
{
	_unit->GetAIInterface()->disable_melee = !pAllow;
}

bool MoonScriptCreatureAI::GetAllowMelee()
{
	return !_unit->GetAIInterface()->disable_melee;
}

void MoonScriptCreatureAI::SetAllowRanged(bool pAllow)
{
	_unit->GetAIInterface()->disable_ranged = !pAllow;
}

bool MoonScriptCreatureAI::GetAllowRanged()
{
	return !_unit->GetAIInterface()->disable_ranged;
}

void MoonScriptCreatureAI::SetAllowSpell(bool pAllow)
{
	_unit->GetAIInterface()->disable_spell = !pAllow;
}

bool MoonScriptCreatureAI::GetAllowSpell()
{
	return !_unit->GetAIInterface()->disable_spell;
}

void MoonScriptCreatureAI::SetAllowTargeting(bool pAllow)
{
	_unit->GetAIInterface()->disable_targeting = !pAllow;
}

bool MoonScriptCreatureAI::GetAllowTargeting()
{
	return !_unit->GetAIInterface()->disable_targeting;
}

void MoonScriptCreatureAI::AggroNearestUnit(int pInitialThreat)
{
	//Pay attention: if this is called before pushing the Creature to world, OnCombatStart will NOT be called.
	Unit* NearestRandomTarget = GetBestUnitTarget(TargetFilter_Closest);

	if(NearestRandomTarget)
		_unit->GetAIInterface()->AttackReaction(NearestRandomTarget, pInitialThreat);
}

void MoonScriptCreatureAI::AggroRandomUnit(int pInitialThreat)
{
	Unit* RandomTarget = GetBestUnitTarget();

	if(RandomTarget)
	{
		_unit->GetAIInterface()->AttackReaction(RandomTarget, pInitialThreat);
		if(!IsInCombat())
			OnCombatStart(RandomTarget);	//Patch, for some reason, OnCombatStart isn't called in this case
	}
}

void MoonScriptCreatureAI::AggroNearestPlayer(int pInitialThreat)
{
	Unit* NearestRandomPlayer = GetBestPlayerTarget(TargetFilter_Closest);

	if(NearestRandomPlayer)
	{
		_unit->GetAIInterface()->AttackReaction(NearestRandomPlayer, pInitialThreat);

		if(!IsInCombat())
			OnCombatStart(NearestRandomPlayer);	//Patch, for some reason, OnCombatStart isn't called in this case
	}
}

void MoonScriptCreatureAI::AggroRandomPlayer(int pInitialThreat)
{
	Unit* RandomPlayer = GetBestPlayerTarget();

	if(RandomPlayer)
	{
		_unit->GetAIInterface()->AttackReaction(RandomPlayer, pInitialThreat);

		if(!IsInCombat())
			OnCombatStart(RandomPlayer);	//Patch, for some reason, OnCombatStart isn't called in this case
	}
}

void MoonScriptCreatureAI::ClearHateList()
{
	_unit->GetAIInterface()->ClearHateList();	//without leaving combat
}

void MoonScriptCreatureAI::WipeHateList()
{
	_unit->GetAIInterface()->WipeHateList();
}

uint8 MoonScriptCreatureAI::GetHealthPercent()
{
	return _unit->GetHealthPct();
}

uint8 MoonScriptCreatureAI::GetManaPercent()
{
	return _unit->GetManaPct();
}

void MoonScriptCreatureAI::Regenerate()
{
	_unit->RegenerateHealth();
	_unit->RegeneratePower(false);
}

void MoonScriptCreatureAI::SetScale(float pScale)
{
	_unit->SetFloatValue(OBJECT_FIELD_SCALE_X, pScale);
}

float MoonScriptCreatureAI::GetScale()
{
	return _unit->GetFloatValue(OBJECT_FIELD_SCALE_X);
}

void MoonScriptCreatureAI::SetDisplayId(uint32 pDisplayId)
{
	_unit->SetDisplayId(pDisplayId);
}

void MoonScriptCreatureAI::SetWieldWeapon(bool pValue)
{
	if(pValue && _unit->GetUInt32Value(UNIT_FIELD_BYTES_2) != 1)
		_unit->SetUInt32Value(UNIT_FIELD_BYTES_2, 1);
	else if(!pValue && _unit->GetUInt32Value(UNIT_FIELD_BYTES_2) != 0)
		_unit->SetUInt32Value(UNIT_FIELD_BYTES_2, 0);
}

void MoonScriptCreatureAI::SetDisplayWeapon(bool pMainHand, bool pOffHand, bool pRanged)
{
	SetDisplayWeaponIds(pMainHand ? _unit->GetEquippedItem(MELEE) : 0, pOffHand ? _unit->GetEquippedItem(OFFHAND) : 0, pRanged ? _unit->GetEquippedItem(RANGED) : 0);
}

void MoonScriptCreatureAI::SetDisplayWeaponIds(uint32 mainhand, uint32 offhand, uint32 ranged)
{
	_unit->SetEquippedItem(MELEE, mainhand);	//Main Hand
	_unit->SetEquippedItem(OFFHAND, offhand);	//Off Hand
	_unit->SetEquippedItem(RANGED, ranged);		//Ranged
}

float MoonScriptCreatureAI::GetRange(MoonScriptCreatureAI* pCreature)
{
	return (_unit != pCreature->_unit) ? _unit->CalcDistance(pCreature->_unit) : 0;
}

float MoonScriptCreatureAI::GetRangeToUnit(Unit* pUnit)
{
	return _unit->CalcDistance(pUnit);
}

float MoonScriptCreatureAI::GetRangeToObject(Object* pObject)
{
	return _unit->CalcDistance(pObject);
}

bool MoonScriptCreatureAI::IsHeroic()
{
	if(_unit->GetMapMgr() == NULL)
		return false;

	if(_unit->GetMapMgr()->iInstanceMode != MODE_HEROIC)
		return false;

	return true;
}

uint32 MoonScriptCreatureAI::HeroicInt(uint32 pNormal, uint32 pHeroic)
{
	return IsHeroic() ? pHeroic : pNormal;
}

bool MoonScriptCreatureAI::Is25ManRaid()
{
	if(_unit->GetMapMgr() == NULL)
		return false;

	if(_unit->GetMapMgr()->iInstanceMode != MODE_NORMAL_25MEN || _unit->GetMapMgr()->iInstanceMode != MODE_HEROIC_25MEN)
		return false;

	return true;
}

uint32 MoonScriptCreatureAI::Raid25manInst(uint32 p10manSpell, uint32 p25manSpell)
{
	return Is25ManRaid() ? p25manSpell : p10manSpell;
}

uint8 MoonScriptCreatureAI::GetInstanceMode()
{
	return _unit->GetMapMgr()->iInstanceMode;
}

MoonInstanceScript* MoonScriptCreatureAI::GetInstanceScript()
{
	MapMgr* pInstance = _unit->GetMapMgr();
	return (pInstance) ? TO< MoonInstanceScript* >(pInstance->GetScript()) : NULL;
}

void MoonScriptCreatureAI::CastOnAllInrangePlayers(uint32 pSpellId, bool pTriggered)
{
	for(set< Object* >::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter)
		_unit->CastSpell(TO< Player* >(*PlayerIter), pSpellId, pTriggered);
}

void MoonScriptCreatureAI::CastOnInrangePlayers(float pDistanceMin, float pDistanceMax, uint32 pSpellId, bool pTriggered)
{
	for(set< Object* >::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter)
	{
		float PlayerDistance = (*PlayerIter)->GetDistance2dSq(this->GetUnit());
		if(PlayerDistance >= pDistanceMin && PlayerDistance <= pDistanceMax)
			_unit->CastSpell(TO< Player* >(*PlayerIter), pSpellId, pTriggered);
	}
}

Player* MoonScriptCreatureAI::GetNearestPlayer()
{
	return _unit->GetMapMgr()->GetInterface()->GetPlayerNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ());
}

GameObject* MoonScriptCreatureAI::GetNearestGameObject(uint32 pGameObjectId)
{
	return _unit->GetMapMgr()->GetInterface()->GetGameObjectNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), pGameObjectId);
}

MoonScriptCreatureAI* MoonScriptCreatureAI::GetNearestCreature(uint32 pCreatureId)
{
	Creature* NearestCreature = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), pCreatureId);
	return (NearestCreature) ? TO< MoonScriptCreatureAI* >(NearestCreature->GetScript()) : NULL;
}

MoonScriptCreatureAI* MoonScriptCreatureAI::SpawnCreature(uint32 pCreatureId, bool pForceSameFaction)
{
	return SpawnCreature(pCreatureId, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation(), pForceSameFaction);
}

MoonScriptCreatureAI* MoonScriptCreatureAI::SpawnCreature(uint32 pCreatureId, float pX, float pY, float pZ, float pO, bool pForceSameFaction, uint32 pPhase)
{
	Creature* NewCreature = _unit->GetMapMgr()->GetInterface()->SpawnCreature(pCreatureId, pX, pY, pZ, pO, true, false, 0, 0, pPhase);
	MoonScriptCreatureAI* CreatureScriptAI = (NewCreature) ? TO< MoonScriptCreatureAI* >(NewCreature->GetScript()) : NULL;

	if(pForceSameFaction && NewCreature)
	{
		uint32 FactionTemplate = _unit->GetFaction();
		NewCreature->SetFaction(FactionTemplate);
	}
	return CreatureScriptAI;
}

Unit* MoonScriptCreatureAI::ForceCreatureFind(uint32 pCreatureId)
{
	return ForceCreatureFind(pCreatureId, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ());
}

Unit* MoonScriptCreatureAI::ForceCreatureFind(uint32 pCreatureId, float pX, float pY, float pZ)
{
	Unit* UnitPtr = NULL;
	MapMgr* Mgr = _unit->GetMapMgr();
	if(Mgr == NULL)
		return UnitPtr;

	UnitPtr = Mgr->GetInterface()->GetCreatureNearestCoords(pX, pY, pZ, pCreatureId);

	if(UnitPtr == NULL)
	{
		UnitArray Array;
		for(std::vector< Creature* >::iterator UnitIter = Mgr->CreatureStorage.begin(); UnitIter != Mgr->CreatureStorage.end(); ++UnitIter)
		{
			UnitPtr = TO< Unit* >(*UnitIter);
			if(UnitPtr != NULL)
			{
				if(UnitPtr->GetEntry() == pCreatureId && UnitPtr != _unit)
					Array.push_back(UnitPtr);
			}
		}

		if(Array.size() == 1)
			return Array[ 0 ];

		UnitPtr = NULL;
		float Distance, NearestDistance = 99999;
		for(UnitArray::iterator UnitIter = Array.begin(); UnitIter != Array.end(); ++UnitIter)
		{
			Distance = _unit->CalcDistance(pX, pY, pZ, (*UnitIter)->GetPositionX(), (*UnitIter)->GetPositionY(), (*UnitIter)->GetPositionZ());
			if(Distance < NearestDistance)
			{
				NearestDistance = Distance;
				UnitPtr = (*UnitIter);
			}
		}
	}
	return UnitPtr;
}

void MoonScriptCreatureAI::Despawn(uint32 pDelay, uint32 pRespawnTime)
{
	_unit->Despawn(pDelay, pRespawnTime);
}

SpellDesc* MoonScriptCreatureAI::AddSpell(uint32 pSpellId, TargetType pTargetType, float pChance, float pCastTime, int32 pCooldown, float pMinRange, float pMaxRange, bool pStrictRange, const char* pText, TextType pTextType, uint32 pSoundId, const char* pAnnouncement)
{
	//Cannot add twice same spell id	- M4ksiu: Disabled, until I rewrite SetPhase(...) function to not disable same spells that are in different phases
	//SpellDesc* NewSpell = FindSpellById(pSpellId);
	//if( NewSpell ) return NewSpell;
	SpellDesc* NewSpell = NULL;

	//Find spell info from spell id
	SpellEntry* Info = dbcSpell.LookupEntry(pSpellId);

#ifdef USE_DBC_SPELL_INFO
	float CastTime = (Info->CastingTimeIndex) ? GetCastTime(dbcSpellCastTime.LookupEntry(Info->CastingTimeIndex)) : pCastTime;
	int32 Cooldown = Info->RecoveryTime;
	float MinRange = (Info->rangeIndex) ? GetMinRange(dbcSpellRange.LookupEntry(Info->rangeIndex)) : pMinRange;
	float MaxRange = (Info->rangeIndex) ? GetMaxRange(dbcSpellRange.LookupEntry(Info->rangeIndex)) : pMaxRange;
	sLog.outDebug("MoonScriptCreatureAI::AddSpell(%u) : casttime=%.1f cooldown=%d minrange=%.1f maxrange=%.1f", pSpellId, CastTime, Cooldown, MinRange, MaxRange);
#else
	float CastTime = pCastTime;
	int32 Cooldown = pCooldown;
	float MinRange = pMinRange;
	float MaxRange = pMaxRange;
#endif

	//Create new spell
	NewSpell = new SpellDesc(Info, NULL, pTargetType, pChance, CastTime, Cooldown, MinRange, MaxRange, pStrictRange, pText, pTextType, pSoundId, pAnnouncement);
	mSpells.push_back(NewSpell);
	return NewSpell;
}

SpellDesc* MoonScriptCreatureAI::AddSpellFunc(SpellFunc pFnc, TargetType pTargetType, float pChance, float pCastTime, int32 pCooldown, float pMinRange, float pMaxRange, bool pStrictRange, const char* pText, TextType pTextType, uint32 pSoundId, const char* pAnnouncement)
{
	if(!pFnc)
		return NULL;

	//Create new spell
	SpellDesc* NewSpell = new SpellDesc(NULL, pFnc, pTargetType, pChance, pCastTime, pCooldown, pMinRange, pMaxRange, pStrictRange, pText, pTextType, pSoundId, pAnnouncement);
	mSpells.push_back(NewSpell);
	return NewSpell;
}

void MoonScriptCreatureAI::CastSpell(SpellDesc* pSpell)
{
	if(!IsSpellScheduled(pSpell)) 
		mQueuedSpells.push_back(pSpell);
}

void MoonScriptCreatureAI::CastSpellNowNoScheduling(SpellDesc* pSpell)
{
	if(CastSpellInternal(pSpell))
		DelayNextAttack(CalcSpellAttackTime(pSpell));
}

SpellDesc* MoonScriptCreatureAI::FindSpellById(uint32 pSpellId)
{
	for(SpellDescArray::iterator SpellIter = mSpells.begin(); SpellIter != mSpells.end(); ++SpellIter)
	{
		if((*SpellIter)->mInfo && (*SpellIter)->mInfo->Id == pSpellId)
			return (*SpellIter);
	}
	return NULL;
}

SpellDesc* MoonScriptCreatureAI::FindSpellByFunc(SpellFunc pFnc)
{
	for(SpellDescArray::iterator SpellIter = mSpells.begin(); SpellIter != mSpells.end(); ++SpellIter)
	{
		if((*SpellIter)->mSpellFunc == pFnc) 
			return (*SpellIter);
	}
	return NULL;
}

bool MoonScriptCreatureAI::IsCasting()
{
	return _unit->IsCasting();
}

void MoonScriptCreatureAI::ApplyAura(uint32 pSpellId)
{
	_unit->CastSpell(_unit, dbcSpell.LookupEntry(pSpellId), true);
}

void MoonScriptCreatureAI::RemoveAura(uint32 pSpellId)
{
	_unit->RemoveAura(pSpellId);
}

void MoonScriptCreatureAI::RemoveAuraOnPlayers(uint32 pSpellId)
{
	for(std::set< Object* >::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter)
		(TO< Player* >(*PlayerIter))->RemoveAura(pSpellId);
}

void MoonScriptCreatureAI::RemoveAllAuras()
{
	_unit->RemoveAllAuras();
}

void MoonScriptCreatureAI::TriggerCooldownOnAllSpells()
{
	uint32 CurrentTime = (uint32)time(NULL);
	for(SpellDescArray::iterator SpellIter = mSpells.begin(); SpellIter != mSpells.end(); ++SpellIter)
		(*SpellIter)->TriggerCooldown(CurrentTime);
}

void MoonScriptCreatureAI::CancelAllCooldowns()
{
	for(SpellDescArray::iterator SpellIter = mSpells.begin(); SpellIter != mSpells.end(); ++SpellIter)
		(*SpellIter)->mLastCastTime = 0;
}

EmoteDesc* MoonScriptCreatureAI::AddEmote(EventType pEventType, const char* pText, TextType pType, uint32 pSoundId)
{
	EmoteDesc* NewEmote = NULL;
	if(pText || pSoundId)
	{
		NewEmote = new EmoteDesc(pText, pType, pSoundId);
		switch(pEventType)
		{
			case Event_OnCombatStart:
				mOnCombatStartEmotes.push_back(NewEmote);
				break;
			case Event_OnCombatStop:
				mOnCombatStopEmotes.push_back(NewEmote);
				break;
			case Event_OnTargetDied:
				mOnTargetDiedEmotes.push_back(NewEmote);
				break;
			case Event_OnDied:
				mOnDiedEmotes.push_back(NewEmote);
				break;
			case Event_OnTaunt:
				mOnTauntEmotes.push_back(NewEmote);
				break;
			default:
				sLog.outDebug("MoonScriptCreatureAI::AddEmote() : Invalid event type!");
				break;
		}
	}
	return NewEmote;
}

void MoonScriptCreatureAI::RemoveEmote(EventType pEventType, EmoteDesc* pEmote)
{
	switch(pEventType)
	{
		case Event_OnCombatStart: DeleteItem(mOnCombatStartEmotes, pEmote); break;
		case Event_OnCombatStop: DeleteItem(mOnCombatStopEmotes, pEmote); break;
		case Event_OnTargetDied: DeleteItem(mOnTargetDiedEmotes, pEmote); break;
		case Event_OnDied: DeleteItem(mOnDiedEmotes, pEmote); break;
		case Event_OnTaunt: DeleteItem(mOnTauntEmotes, pEmote); break;
		default: sLog.outDebug("MoonScriptCreatureAI::RemoveEmote() : Invalid event type!"); break;
	}
}

void MoonScriptCreatureAI::RemoveAllEmotes(EventType pEventType)
{
	switch(pEventType)
	{
		case Event_OnCombatStart: DeleteArray(mOnCombatStartEmotes); break;
		case Event_OnCombatStop: DeleteArray(mOnCombatStopEmotes); break;
		case Event_OnTargetDied: DeleteArray(mOnTargetDiedEmotes); break;
		case Event_OnDied: DeleteArray(mOnDiedEmotes); break;
		case Event_OnTaunt: DeleteArray(mOnTauntEmotes); break;
		default: sLog.outDebug("MoonScriptCreatureAI::RemoveAllEmotes() : Invalid event type!"); break;
	}
}

void MoonScriptCreatureAI::Emote(const char* pText, TextType pType, uint32 pSoundId, EmoteType pEmote, uint32 Time)
{
	if(pText && strlen(pText) > 0)
	{
		switch(pType)
		{
			case Text_Say: _unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, pText, Time); break;
			case Text_Yell: _unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, pText, Time); break;
			case Text_Emote: _unit->SendChatMessage(CHAT_MSG_MONSTER_EMOTE, LANG_UNIVERSAL, pText, Time); break;
			default: sLog.outDebug("MoonScriptCreatureAI::Emote() : Invalid text type!"); break;
		}
	}

	if(pSoundId > 0)
	{
		if(Time > 0)
			sEventMgr.AddEvent(TO_OBJECT(_unit), &Object::PlaySoundToSet, (uint32)pSoundId, EVENT_UNK, Time, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		else
			_unit->PlaySoundToSet(pSoundId);
	}

	if(pEmote != EMOTE_ONESHOT_NONE)
		_unit->Emote(pEmote);
}

void MoonScriptCreatureAI::Announce(const char* pText)
{
	if(pText && strlen(pText) > 0)
		_unit->SendChatMessage(CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, pText);
}

void MoonScriptCreatureAI::TextEmote(int32 pEntry)
{
	if(pEntry>=0)
	{
		Log.Debug("ArcScripts2","TextEmote entry should be negative value");
		return;
	}

	StringTextData const* pData = pSystem->GetTextData(pEntry);
	if(!pData)
	{
		sLog.outDebug("ArcScripts2", "TextEmote entry %i data not found", pEntry);
		return;
	}

	//preparing data
	const char * pText = pData->uiText;
	uint8 pType = pData->uiType;
	uint32 pSound = pData->uiSoundId;
	uint32 pEmote = pData->uiEmote;

	//pushing emote
	Emote(pText, (TextType)pType, pSound);

	//text emote
	if(pEmote>0)
		_unit->Emote((EmoteType)pEmote);
}

void MoonScriptCreatureAI::AddTextEmote(int32 pEntry, EventType pEventType)
{
	if(pEntry>=0)
	{
		sLog.outDebug("AddTextEmote entry  %i should be negative value", pEntry);
		return;
	}

	StringTextData const* pData = pSystem->GetTextData(pEntry);
	if(pData == NULL)
	{
		sLog.outDebug("AddTextEmote entry %i data not found", pEntry);
		return;
	}

	//preparing data
	//all other checks has been dealed on load
	const char*pText = pData->uiText;
	uint8 pType = pData->uiType;
	uint32 pSound = pData->uiSoundId;

	AddEmote(pEventType, pText, (TextType)pType, pSound);
}

int32 MoonScriptCreatureAI::AddTimer(int32 pDurationMillisec)
{
	int32 Index = mTimerIdCounter++;
	mTimers.push_back(std::make_pair(Index, pDurationMillisec));
	++mTimerCount;
	return Index;
}

int32 MoonScriptCreatureAI::GetTimer(int32 pTimerId)
{
	for(TimerArray::iterator TimerIter = mTimers.begin(); TimerIter != mTimers.end(); ++TimerIter)
	{
		if(TimerIter->first == pTimerId)
			return TimerIter->second;
	}
	return 0;
}

void MoonScriptCreatureAI::RemoveTimer(int32 & pTimerId)
{
	for(TimerArray::iterator TimerIter = mTimers.begin(); TimerIter != mTimers.end(); ++TimerIter)
	{
		if(TimerIter->first == pTimerId)
		{
			mTimers.erase(TimerIter);
			pTimerId = INVALIDATE_TIMER;
			--mTimerCount;
			break;
		}
	}
}

void MoonScriptCreatureAI::ResetTimer(int32 pTimerId, int32 pDurationMillisec)
{
	for(TimerArray::iterator TimerIter = mTimers.begin(); TimerIter != mTimers.end(); ++TimerIter)
	{
		if(TimerIter->first == pTimerId)
		{
			TimerIter->second = pDurationMillisec;
			break;
		}
	}
}

bool MoonScriptCreatureAI::IsTimerFinished(int32 pTimerId)
{
	for(TimerArray::iterator TimerIter = mTimers.begin(); TimerIter != mTimers.end(); ++TimerIter)
	{
		if(TimerIter->first == pTimerId)
			return (TimerIter->second <= 0) ? true : false;
	}
	return false;
}

void MoonScriptCreatureAI::CancelAllTimers()
{
	mTimers.clear();
	mTimerIdCounter = 0;
	mTimerCount = 0;
}

int32 MoonScriptCreatureAI::AddEvent(uint32 pEventId, int32 pTriggerTimer, EventFunc pEvent, int32 pMiscVal, bool pRepeatable)
{
	EventStruct* newEvent = new EventStruct(pEventId, pTriggerTimer, pEvent, pRepeatable, false, pTriggerTimer, pMiscVal);
	mEvents.push_back(newEvent);
	++mEventCount;
	return newEvent->mEventId;
}

void MoonScriptCreatureAI::ResetEvent(uint32 pEventId, int32 pNewTriggerTimer, bool pRepeatable)
{
	for(EventArray::iterator EventIter = mEvents.begin(); EventIter != mEvents.end(); ++ EventIter)
	{
		if((*EventIter)->mEventId == int32(pEventId))
		{
			(*EventIter)->mEventTimer = pNewTriggerTimer;
			(*EventIter)->mEventTimerConst = pNewTriggerTimer;
			(*EventIter)->mFinished = false;
			(*EventIter)->mRepeatable = pRepeatable; // dont repeat if someone cares for it!
			break;
		}
	}
}

void MoonScriptCreatureAI::RemoveEvent(uint32 pEventId)
{
	for(EventArray::iterator EventIter = mEvents.begin(); EventIter != mEvents.end(); ++EventIter)
	{
		if((*EventIter)->mEventId == int32(pEventId))
		{
			mEvents.erase(EventIter);
			--mEventCount;
			break;
		}
	}
}

void MoonScriptCreatureAI::RemoveAllEvents()
{
	mEvents.clear();
	mEventCount = 0;
}

void MoonScriptCreatureAI::SetTargetToChannel(Unit* pTarget, uint32 pSpellId)
{
	_unit->SetChannelSpellTargetGUID(pTarget == NULL ? 0 : pTarget->GetGUID());
	_unit->SetChannelSpellId(pSpellId);
}

Unit* MoonScriptCreatureAI::GetTargetToChannel()
{
	return _unit->GetMapMgr()->GetUnit(_unit->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
}

void MoonScriptCreatureAI::SetAIUpdateFreq(uint32 pUpdateFreq)
{
	if(mAIUpdateFrequency != pUpdateFreq)
	{
		mAIUpdateFrequency = pUpdateFreq;
		ModifyAIUpdateEvent(mAIUpdateFrequency);
	}
}

uint32 MoonScriptCreatureAI::GetAIUpdateFreq()
{
	return mAIUpdateFrequency;
}

void MoonScriptCreatureAI::SetGoldLoot(Unit* pTarget, uint32 pMinGold, uint32 pMaxGold)
{
	pTarget->loot.gold = RandomUInt(pMaxGold - pMinGold) + pMinGold;
}

void MoonScriptCreatureAI::AddLoot(Unit* pTarget, uint32 pItemID, uint32 pMinCount, uint32 pMaxCount)
{
	LootMgr::getSingleton().AddLoot(&pTarget->loot, pItemID, pMinCount, pMaxCount);
}

WayPoint* MoonScriptCreatureAI::CreateWaypoint(int pId, uint32 pWaittime, uint32 pMoveFlag, Location pCoords)
{
	WayPoint* wp = _unit->CreateWaypointStruct();
	wp->id = pId;
	wp->x = pCoords.x;
	wp->y = pCoords.y;
	wp->z = pCoords.z;
	wp->o = pCoords.o;
	wp->waittime = pWaittime;
	wp->flags = pMoveFlag;
	wp->forwardemoteoneshot = false;
	wp->forwardemoteid = 0;
	wp->backwardemoteoneshot = false;
	wp->backwardemoteid = 0;
	wp->forwardskinid = 0;
	wp->backwardskinid = 0;
	return wp;
}

WayPoint* MoonScriptCreatureAI::CreateWaypoint(int pId, uint32 pWaittime, uint32 pMoveFlag, LocationExtra pCoords)
{
	WayPoint* wp = _unit->CreateWaypointStruct();
	wp->id = pId;
	wp->x = pCoords.x;
	wp->y = pCoords.y;
	wp->z = pCoords.z;
	wp->o = pCoords.o;
	wp->waittime = pWaittime;
	wp->flags = pMoveFlag;
	wp->forwardemoteoneshot = false;
	wp->forwardemoteid = 0;
	wp->backwardemoteoneshot = false;
	wp->backwardemoteid = 0;
	wp->forwardskinid = 0;
	wp->backwardskinid = 0;
	return wp;
}

void MoonScriptCreatureAI::AddWaypoint(WayPoint* pWayPoint)
{
	_unit->GetAIInterface()->addWayPoint(pWayPoint);
}

void MoonScriptCreatureAI::ForceWaypointMove(uint32 pWaypointId)
{
	if(GetCanEnterCombat())
		_unit->GetAIInterface()->SetAllowedToEnterCombat(false);

	if(!GetCanMove())
		SetCanMove(true);

	StopMovement();
	_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
	SetMoveType(Move_WantedWP);
	SetWaypointToMove(pWaypointId);
}

void MoonScriptCreatureAI::SetWaypointToMove(uint32 pWaypointId)
{
	_unit->GetAIInterface()->setWaypointToMove(pWaypointId);
}

void MoonScriptCreatureAI::StopWaypointMovement()
{
	SetBehavior(Behavior_Default);
	_unit->GetAIInterface()->SetAIState(STATE_SCRIPTIDLE);
	SetMoveType(Move_DontMoveWP);
	SetWaypointToMove(0);
}

void MoonScriptCreatureAI::StartWaypointMovement()
{
	SetBehavior(Behavior_Default);
	_unit->GetAIInterface()->SetAIState(STATE_SCRIPTMOVE);
	SetMoveType(Move_WantedWP);
	SetWaypointToMove(1);
}

void MoonScriptCreatureAI::SetMoveType(MoveType pMoveType)
{
	switch(pMoveType)
	{
		case Move_None: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_NONE); break;
		case Move_RandomWP: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_RANDOMWP); break;
		case Move_CircleWP: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_CIRCLEWP); break;
		case Move_WantedWP: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_WANTEDWP); break;
		case Move_DontMoveWP: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP); break;
		case Move_Quest: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_QUEST); break;
		case Move_ForwardThenStop: _unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_FORWARDTHANSTOP); break;
		default: sLog.outDebug("ArcScript: MoonScriptCreatureAI::SetMoveType() : Invalid move type!"); break;
	}
}

MoveType MoonScriptCreatureAI::GetMoveType()
{
	switch(_unit->GetAIInterface()->getMoveType())
	{
		case MOVEMENTTYPE_NONE: return Move_None;
		case MOVEMENTTYPE_RANDOMWP: return Move_RandomWP;
		case MOVEMENTTYPE_CIRCLEWP: return Move_CircleWP;
		case MOVEMENTTYPE_WANTEDWP: return Move_WantedWP;
		case MOVEMENTTYPE_DONTMOVEWP: return Move_DontMoveWP;
		case MOVEMENTTYPE_QUEST: return Move_Quest;
		case MOVEMENTTYPE_FORWARDTHANSTOP: return Move_ForwardThenStop;
		default: sLog.outDebug("ArcScript: MoonScriptCreatureAI::GetMoveType() : Invalid move type!"); return Move_None;
	}
}

uint32 MoonScriptCreatureAI::GetCurrentWaypoint()
{
	return _unit->GetAIInterface()->getCurrentWaypoint();
}

size_t MoonScriptCreatureAI::GetWaypointCount()
{
	return _unit->GetAIInterface()->GetWayPointsCount();
}

bool MoonScriptCreatureAI::HasWaypoints()
{
	return _unit->GetAIInterface()->hasWaypoints();
}

void MoonScriptCreatureAI::OnCombatStart(Unit* pTarget)
{
	RandomEmote(mOnCombatStartEmotes);
	SetBehavior(Behavior_Melee);
	RegisterAIUpdateEvent(mAIUpdateFrequency);
}

void MoonScriptCreatureAI::OnCombatStop(Unit* pTarget)
{
	RandomEmote(mOnCombatStopEmotes);
	CancelAllSpells();
	CancelAllTimers();
	RemoveAllEvents();
	RemoveAllAuras();
	SetBehavior(Behavior_Default);
	RemoveAIUpdateEvent();

	if(mDespawnWhenInactive)
		Despawn(DEFAULT_DESPAWN_TIMER);
}

void MoonScriptCreatureAI::OnTargetDied(Unit* pTarget)
{
	if(GetHealthPercent() > 0)	//Prevent double yelling (OnDied and OnTargetDied)
		RandomEmote(mOnTargetDiedEmotes);
}

void MoonScriptCreatureAI::OnDied(Unit* pKiller)
{
	RandomEmote(mOnDiedEmotes);
	CancelAllSpells();
	CancelAllTimers();
	RemoveAllEvents();
	RemoveAllAuras();
	RemoveAIUpdateEvent();
	if(mDespawnWhenInactive)
		Despawn(DEFAULT_DESPAWN_TIMER);
}

void MoonScriptCreatureAI::AIUpdate()
{
	SpellDesc*	Spell;
	uint32		CurrentTime = (uint32)time(NULL);

	//Elapse timers
	for(TimerArray::iterator TimerIter = mTimers.begin(); TimerIter != mTimers.end(); ++TimerIter)
		TimerIter->second -= mAIUpdateFrequency;

	// update events
	for(EventArray::iterator EventIter = mEvents.begin(); EventIter != mEvents.end(); ++ EventIter)
	{
		(*EventIter)->mEventTimer -= mAIUpdateFrequency;
		if((*EventIter)->mEventTimer < static_cast< int32 >(mAIUpdateFrequency))
		{
			(*EventIter)->mEvent(this, (*EventIter)->mMiscVal);
			(*EventIter)->mRepeatable ? ResetEvent((*EventIter)->mEventId, (*EventIter)->mEventTimerConst, (*EventIter)->mRepeatable) : RemoveEvent((*EventIter)->mEventId);
		}
	}

	if(!IsInCombat())
		return;

	//Check if we have a spell scheduled to be cast
	for(SpellDescList::iterator SpellIter = mScheduledSpells.begin(); SpellIter != mScheduledSpells.end();)
	{
		Spell = (*SpellIter);
		if(CastSpellInternal(Spell, CurrentTime))	//Can fail if we are already casting a spell, or if the spell is on cooldown
		{
			if(!mScheduledSpells.empty())  //temporary crashfix, we should use mutax here, but it needs more investigation
				mScheduledSpells.erase(SpellIter);

			break;
		}else
			++SpellIter;
	}

	//Do not schedule spell if we are *currently* casting a non-instant cast spell
	if(!IsCasting() && !mRunToTargetCache)
	{
		//Check if have queued spells that needs to be scheduled before we go back to random casting
		if(!mQueuedSpells.empty())
		{
			Spell = mQueuedSpells.front();
			mScheduledSpells.push_back(Spell);
			mQueuedSpells.pop_front();

			//Stop melee attack for a short while for scheduled spell cast
			if(Spell->mCastTime >= 0)
			{
				DelayNextAttack(mAIUpdateFrequency);
				if(Spell->mCastTime > 0)
				{
					SetCanMove(false);
					SetBehavior(Behavior_Spell);
				}
			}
			return;	//Scheduling one spell at a time, exit now
		}

		//Try our chance at casting a spell (Will actually be cast on next ai update, so we just
		//schedule it. This is needed to avoid next dealt melee damage while we cast the spell.)
		float ChanceRoll = RandomFloat(100), ChanceTotal = 0;
		for(SpellDescArray::iterator SpellIter = mSpells.begin(); SpellIter != mSpells.end(); ++SpellIter)
		{
			Spell = (*SpellIter);
			if(Spell->mEnabled == false) continue;
			if(Spell->mChance == 0) continue;

			//Check if spell won the roll
			if((Spell->mChance == 100 || (ChanceRoll >= ChanceTotal && ChanceRoll < ChanceTotal + Spell->mChance)) &&
			        (Spell->mLastCastTime + Spell->mCooldown <= CurrentTime) &&
			        !IsSpellScheduled(Spell))
			{
				mScheduledSpells.push_back(Spell);

				//Stop melee attack for a short while for scheduled spell cast
				if(Spell->mCastTime >= 0)
				{
					DelayNextAttack(mAIUpdateFrequency + CalcSpellAttackTime(Spell));
					if(Spell->mCastTime > 0)
					{
						SetCanMove(false);
						SetBehavior(Behavior_Spell);
					}
				}
				return;	//Scheduling one spell at a time, exit now
			}
			else if(Spell->mChance != 100) 
				ChanceTotal += Spell->mChance;	//Only add spells that aren't 100% chance of casting
		}

		//Go back to default behavior since we didn't decide anything
		SetCanMove(true);
		SetBehavior(Behavior_Melee);

		//Random taunts
		if(ChanceRoll >= 95)
			RandomEmote(mOnTauntEmotes);
	}
}

void MoonScriptCreatureAI::Destroy()
{
	delete this;
}

bool MoonScriptCreatureAI::IsSpellScheduled(SpellDesc* pSpell)
{
	return (std::find(mScheduledSpells.begin(), mScheduledSpells.end(), pSpell) == mScheduledSpells.end()) ? false : true;
}

void MoonScriptCreatureAI::CancelAllSpells()
{
	mQueuedSpells.clear();
	mScheduledSpells.clear();
	PopRunToTargetCache();
}

bool MoonScriptCreatureAI::CastSpellInternal(SpellDesc* pSpell, uint32 pCurrentTime)
{
	if(pSpell == NULL)
		return false;

	//Do not cast if we are already casting
	if(IsCasting())
		return false;

	//We do not cast in special states such as : stunned, feared, silenced, charmed, asleep, confused and if they are not ignored
	if((~pSpell->mTargetType.mTargetFilter & TargetFilter_IgnoreSpecialStates) && _unit->m_special_state & (UNIT_STATE_STUN | UNIT_STATE_FEAR | UNIT_STATE_SLEEP | UNIT_STATE_SILENCE | UNIT_STATE_CHARM | UNIT_STATE_CONFUSE))
		return false;

	//Do not cast if we are in cooldown
	uint32 CurrentTime = (pCurrentTime == 0) ? (uint32)time(NULL) : pCurrentTime;
	if(pSpell->mLastCastTime + pSpell->mCooldown > CurrentTime) 
		return false;

	//Check range before casting
	Unit* Target = GetTargetForSpell(pSpell);
	if(Target)
	{
		RangeStatusPair Status;
		if(pSpell->mTargetType.mTargetFilter & TargetFilter_InRangeOnly || (Status = GetSpellRangeStatusToUnit(Target, pSpell)).first == RangeStatus_Ok)
		{
			//Safe-delay if we got special state flag before
			DelayNextAttack(CalcSpellAttackTime(pSpell));

			//If we were running to a target, stop because we're in range now
			PopRunToTargetCache();

			//Do emote associated with this spell
			RandomEmote(pSpell->mEmotes);
			Announce(pSpell->mAnnouncement);

			//Cast spell now
			if(pSpell->mInfo)
				CastSpellOnTarget(Target, pSpell->mTargetType, pSpell->mInfo, (pSpell->mCastTime == 0) ? true : false);
			else if(pSpell->mSpellFunc)
				pSpell->mSpellFunc(pSpell, this, Target, pSpell->mTargetType);
			else 
				sLog.outDebug("ArcScript: MoonScriptCreatureAI::CastSpellInternal() : Invalid spell!");

			//Store cast time for cooldown
			pSpell->mLastCastTime = CurrentTime;
			return true;
		}else if(!pSpell->mStrictRange)   //Target is out of range, run to it
		{
			PushRunToTargetCache(Target, pSpell, Status);
			return false;
		}
	}

	//If we get here, its because the RunToTarget changed type, so its no longer valid, clear it
	PopRunToTargetCache();
	DelayNextAttack(0);		//Cancel attack delay
	return true;			//No targets possible? Consider spell casted nonetheless
}

void MoonScriptCreatureAI::CastSpellOnTarget(Unit* pTarget, TargetType pType, SpellEntry* pEntry, bool pInstant)
{
	switch(pType.mTargetGenerator)
	{
		case TargetGen_Self:
		case TargetGen_Current:
		case TargetGen_Predefined:
		case TargetGen_RandomUnit:
		case TargetGen_RandomPlayer:
		case TargetGen_RandomUnitApplyAura:
		case TargetGen_RandomPlayerApplyAura:
			pTarget->CastSpell(pTarget, pEntry, pInstant);
			break;
		case TargetGen_Destination:
		case TargetGen_RandomUnitDestination:
		case TargetGen_RandomPlayerDestination:
			_unit->CastSpellAoF(pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pEntry, pInstant);
			break;
		default:
			sLog.outDebug("ArcScript: MoonScriptCreatureAI::CastSpellOnTarget() : Invalid target type!");
			break;
	}
}

int32 MoonScriptCreatureAI::CalcSpellAttackTime(SpellDesc* pSpell)
{
	return mBaseAttackTime + int32(pSpell->mCastTime);
}

RangeStatusPair MoonScriptCreatureAI::GetSpellRangeStatusToUnit(Unit* pTarget, SpellDesc* pSpell)
{
	if(pSpell->mTargetType.mTargetGenerator != TargetGen_Self && pTarget != _unit && (pSpell->mMinRange > 0 || pSpell->mMaxRange > 0))
	{
		float Range = GetRangeToUnit(pTarget);
		if(pSpell->mMinRange > 0 && (Range < pSpell->mMinRange))
			return make_pair(RangeStatus_TooClose, pSpell->mMinRange);

		if(pSpell->mMaxRange > 0 && (Range > pSpell->mMaxRange))
			return make_pair(RangeStatus_TooFar, pSpell->mMaxRange);
	}
	return make_pair(RangeStatus_Ok, 0.0f);
}

Unit* MoonScriptCreatureAI::GetTargetForSpell(SpellDesc* pSpell)
{
	//Check if run-to-target cache and return it if its valid
	if(mRunToTargetCache && mRunToTargetSpellCache == pSpell && IsValidUnitTarget(mRunToTargetCache, TargetFilter_None))
		return mRunToTargetCache;

	//Find a suitable target for the described situation :)
	switch(pSpell->mTargetType.mTargetGenerator)
	{
		case TargetGen_Self:
			if(!IsAlive())
				return NULL;

			if((pSpell->mTargetType.mTargetFilter & TargetFilter_Wounded) && GetHealthPercent() >= 99)
				return NULL;

			return _unit;
		case TargetGen_SecondMostHated:
			return _unit->GetAIInterface()->GetSecondHated();
		case TargetGen_Current:
		case TargetGen_Destination:
			return _unit->GetAIInterface()->getNextTarget();
		case TargetGen_Predefined:
			return pSpell->mPredefinedTarget;
		case TargetGen_RandomPlayer:
		case TargetGen_RandomPlayerApplyAura:
		case TargetGen_RandomPlayerDestination:
			return GetBestPlayerTarget(pSpell->mTargetType.mTargetFilter, pSpell->mMinRange, pSpell->mMaxRange);
		case TargetGen_RandomUnit:
		case TargetGen_RandomUnitApplyAura:
		case TargetGen_RandomUnitDestination:
			return GetBestUnitTarget(pSpell->mTargetType.mTargetFilter, pSpell->mMinRange, pSpell->mMaxRange);
		default:
			sLog.outDebug("ArcScript: MoonScriptCreatureAI::GetTargetForSpell() : Invalid target type!");
			return NULL;
	}
}

Unit* MoonScriptCreatureAI::GetBestPlayerTarget(TargetFilter pTargetFilter, float pMinRange, float pMaxRange)
{
	//Build potential target list
	UnitArray TargetArray;
	for(set< Object* >::iterator PlayerIter = _unit->GetInRangePlayerSetBegin(); PlayerIter != _unit->GetInRangePlayerSetEnd(); ++PlayerIter)
	{
		if(IsValidUnitTarget(*PlayerIter, pTargetFilter, pMinRange, pMaxRange))
			TargetArray.push_back(TO_UNIT(*PlayerIter));
	}

	return ChooseBestTargetInArray(TargetArray, pTargetFilter);
}

Unit* MoonScriptCreatureAI::GetBestUnitTarget(TargetFilter pTargetFilter, float pMinRange, float pMaxRange)
{
	//Build potential target list
	UnitArray TargetArray;
	if(pTargetFilter & TargetFilter_Friendly)
	{
		for(set< Object* >::iterator ObjectIter = _unit->GetInRangeSetBegin(); ObjectIter != _unit->GetInRangeSetEnd(); ++ObjectIter)
		{
			if(IsValidUnitTarget(*ObjectIter, pTargetFilter, pMinRange, pMaxRange))
				TargetArray.push_back(TO_UNIT(*ObjectIter));
		}

		if(IsValidUnitTarget(_unit, pTargetFilter))
			TargetArray.push_back(_unit);	//Also add self as possible friendly target
	}else
	{
		for(set< Object* >::iterator ObjectIter = _unit->GetInRangeOppFactsSetBegin(); ObjectIter != _unit->GetInRangeOppFactsSetEnd(); ++ObjectIter)
		{
			if(IsValidUnitTarget(*ObjectIter, pTargetFilter, pMinRange, pMaxRange))
				TargetArray.push_back(TO_UNIT(*ObjectIter));
		}
	}

	return ChooseBestTargetInArray(TargetArray, pTargetFilter);
}

Unit* MoonScriptCreatureAI::ChooseBestTargetInArray(UnitArray & pTargetArray, TargetFilter pTargetFilter)
{
	//If only one possible target, return it
	if(pTargetArray.size() == 1)
		return pTargetArray[ 0 ];

	//Find closest unit if requested
	if(pTargetFilter & TargetFilter_Closest)
		return GetNearestTargetInArray(pTargetArray);

	//Find second most hated if requested
	if(pTargetFilter & TargetFilter_SecondMostHated)
		return GetSecondMostHatedTargetInArray(pTargetArray);

	//Choose random unit in array
	return (pTargetArray.size() > 1) ? pTargetArray[ RandomUInt((uint32)pTargetArray.size() - 1) ] : NULL;
}

Unit* MoonScriptCreatureAI::GetNearestTargetInArray(UnitArray & pTargetArray)
{
	Unit* NearestUnit = NULL;
	float Distance, NearestDistance = 99999;
	for(UnitArray::iterator UnitIter = pTargetArray.begin(); UnitIter != pTargetArray.end(); ++UnitIter)
	{
		Distance = GetRangeToUnit(TO_UNIT(*UnitIter));
		if(Distance < NearestDistance)
		{
			NearestDistance = Distance;
			NearestUnit = (*UnitIter);
		}
	}
	return NearestUnit;
}

Unit* MoonScriptCreatureAI::GetSecondMostHatedTargetInArray(UnitArray & pTargetArray)
{
	Unit*	TargetUnit = NULL;
	Unit*	MostHatedUnit = NULL;
	Unit*	CurrentTarget = TO_UNIT(_unit->GetAIInterface()->getNextTarget());
	uint32	Threat = 0, HighestThreat = 0;
	for(UnitArray::iterator UnitIter = pTargetArray.begin(); UnitIter != pTargetArray.end(); ++UnitIter)
	{
		TargetUnit = TO_UNIT(*UnitIter);
		if(TargetUnit != CurrentTarget)
		{
			Threat = _unit->GetAIInterface()->getThreatByPtr(TargetUnit);
			if(Threat > HighestThreat)
			{
				MostHatedUnit = TargetUnit;
				HighestThreat = Threat;
			}
		}
	}
	return MostHatedUnit;
}

bool MoonScriptCreatureAI::IsValidUnitTarget(Object* pObject, TargetFilter pFilter, float pMinRange, float pMaxRange)
{
	//Make sure its a valid unit
	if(!pObject->IsUnit())
		return false;

	if(pObject->GetInstanceID() != _unit->GetInstanceID())
		return false;

	Unit* UnitTarget = TO_UNIT(pObject);
	//Skip dead ( if required ), feign death or invisible targets
	if(pFilter & TargetFilter_Corpse)
	{
		if(UnitTarget->isAlive() || !UnitTarget->IsCreature() || TO_CREATURE(UnitTarget)->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
			return false;
	}else if(!UnitTarget->isAlive())
		return false;

	if(UnitTarget->IsPlayer() && TO_PLAYER(UnitTarget)->m_isGmInvisible)
		return false;
	if(UnitTarget->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FEIGN_DEATH))
		return false;

	//Check if we apply target filtering
	if(pFilter != TargetFilter_None)
	{
		//Skip units not on threat list
		if((pFilter & TargetFilter_Aggroed) && _unit->GetAIInterface()->getThreatByPtr(UnitTarget) == 0)
			return false;

		//Skip current attacking target if requested
		if((pFilter & TargetFilter_NotCurrent) && UnitTarget == _unit->GetAIInterface()->getNextTarget())
			return false;

		//Keep only wounded targets if requested
		if((pFilter & TargetFilter_Wounded) && UnitTarget->GetHealthPct() >= 99)
			return false;

		//Skip targets not in melee range if requested
		if((pFilter & TargetFilter_InMeleeRange) && GetRangeToUnit(UnitTarget) > _unit->GetAIInterface()->_CalcCombatRange(UnitTarget, false))
			return false;

		//Skip targets not in strict range if requested
		if((pFilter & TargetFilter_InRangeOnly) && (pMinRange > 0 || pMaxRange > 0))
		{
			float Range = GetRangeToUnit(UnitTarget);
			if(pMinRange > 0 && Range < pMinRange)
				return false;
			if(pMaxRange > 0 && Range > pMaxRange)
				return false;
		}

		//Skip targets not in Line Of Sight if requested
		if((~pFilter & TargetFilter_IgnoreLineOfSight) && !_unit->IsWithinLOSInMap(UnitTarget))
			return false;

		//Handle hostile/friendly
		if((~pFilter & TargetFilter_Corpse) && (pFilter & TargetFilter_Friendly))
		{
			if(!UnitTarget->CombatStatus.IsInCombat())
				return false; //Skip not-in-combat targets if friendly
			if(isHostile(_unit, UnitTarget) || _unit->GetAIInterface()->getThreatByPtr(UnitTarget) > 0)
				return false;
		}
	}
	return true; //This is a valid unit target
}

void MoonScriptCreatureAI::PushRunToTargetCache(Unit* pTarget, SpellDesc* pSpell, RangeStatusPair pRangeStatus)
{
	if(mRunToTargetCache != pTarget)
	{
		mRunToTargetCache = pTarget;
		mRunToTargetSpellCache = pSpell;
		SetCanMove(true);
		SetAllowMelee(false);
		SetAllowRanged(false);
		SetAllowSpell(false);
	}

	if(mRunToTargetCache)
		MoveTo(mRunToTargetCache, pRangeStatus);
}

void MoonScriptCreatureAI::PopRunToTargetCache()
{
	if(mRunToTargetCache)
	{
		mRunToTargetCache = NULL;
		mRunToTargetSpellCache = NULL;
		SetAllowMelee(true);
		SetAllowRanged(true);
		SetAllowSpell(true);
		StopMovement();
	}
}

void MoonScriptCreatureAI::RandomEmote(EmoteArray & pEmoteArray)
{
	int32 ArraySize = (int32)pEmoteArray.size();
	if(ArraySize > 0)
	{
		uint32 Roll = (ArraySize > 1) ? RandomUInt(ArraySize - 1) : 0;
		Emote(pEmoteArray[ Roll ]->mText.c_str(), pEmoteArray[ Roll ]->mType, pEmoteArray[ Roll ]->mSoundId);
	}
}

void MoonScriptCreatureAI::GetCurrentPosition(float &x, float &y, float &z) const
{
    x = _unit->GetPositionX();
    y = _unit->GetPositionY();
	z = _unit->GetPositionZ();
}