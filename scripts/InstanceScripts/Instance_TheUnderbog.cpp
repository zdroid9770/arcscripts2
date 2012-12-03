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

/*****************************/
/*                           */
/*         Boss AIs          */
/*                           */
/*****************************/

// HungarfenAI

#define CN_HUNGARFEN 17770

#define UNDERBOG_MUSHROOM 31693 // still not idea *confused* //34588 // No idea if this is right spell, but should be correct (also aditional core support needed!)
#define FOUL_SPORES 31673 //DBC: 31673, 31697 // this one needs additional core support too
// Putrid Mushroom Primer 31693 ?
// Despawn Underbog Mushrooms 34874 ?

class HUNGARFENAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(HUNGARFENAI);
		SP_AI_Spell spells[2];
		bool m_spellcheck[2];

		HUNGARFENAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			nrspells = 1;
			for(int i = 0; i < nrspells; i++)
			{
				m_spellcheck[i] = false;
			}

			spells[0].info = dbcSpell.LookupEntry(UNDERBOG_MUSHROOM);	// need to have more fun with it?
			spells[0].targettype = TARGET_RANDOM_DESTINATION;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 0.0f;//100.0f;
			spells[0].attackstoptimer = 1000;

			spells[1].info = dbcSpell.LookupEntry(FOUL_SPORES);
			spells[1].targettype = TARGET_VARIOUS;
			spells[1].instant = false;
			spells[1].cooldown = 0;
			spells[1].perctrigger = 0.0f;
			spells[1].attackstoptimer = 1000;

			FourSpores = false;
		}

		void OnCombatStart(Unit* mTarget)
		{
			spells[0].casttime = 0;

			FourSpores = false;

			RegisterAIUpdateEvent(_unit->GetBaseAttackTime(MELEE));
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);

			RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			FourSpores = false;

			RemoveAIUpdateEvent();
		}

		void AIUpdate()
		{
			if(_unit->GetHealthPct() <= 20 && !FourSpores)
			{
				_unit->GetAIInterface()->StopMovement(11000);
				_unit->setAttackTimer(1200, false);

				_unit->CastSpell(_unit, spells[1].info, spells[1].instant);

				FourSpores = true;
			}

			else if(!_unit->FindAura(FOUL_SPORES))
			{
				uint32 t = (uint32)time(NULL);
				if(t > spells[0].casttime)
				{
					// Not yet added
					//CastSpellOnRandomTarget(0, 0.0f, 40.0f, 0, 100);

					spells[0].casttime = t + spells[0].cooldown;
				}
			}
		}

		void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
		{
			if(!maxdist2cast) maxdist2cast = 100.0f;
			if(!maxhp2cast) maxhp2cast = 100;

			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())
			{
				std::vector<Unit*> TargetTable;		/* From M4ksiu - Big THX to Capt who helped me with std stuff to make it simple and fully working <3 */
				/* If anyone wants to use this function, then leave this note!										 */
				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)
				{
					if(isHostile(_unit, (*itr)) && (*itr) != _unit && (*itr)->IsUnit())
					{
						Unit* RandomTarget = NULL;
						RandomTarget = TO_UNIT(*itr);

						if(RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast * mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast * maxdist2cast)
						{
							TargetTable.push_back(RandomTarget);
						}
					}
				}

				if(!TargetTable.size())
					return;

				size_t RandTarget = rand() % TargetTable.size();

				Unit*  RTarget = TargetTable[RandTarget];

				if(!RTarget)
				{
					TargetTable.clear();
					return;
				}
				/* Spawning mushroom - TO DO */

				TargetTable.clear();
			}
		}

	protected:

		bool FourSpores;
		int nrspells;
};

// Ghaz'anAI

#define CN_GHAZAN 18105

#define ACID_SPIT		34290
#define TAIL_SWEEP		34267
#define ACID_BREATH		24839
#define ENRAGE			15716 // Not sure to id as always in Enrage case: 34409, 34970

class GhazanAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(GhazanAI);
		SP_AI_Spell spells[4];
		bool m_spellcheck[4];

		GhazanAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			nrspells = 3;
			for(int i = 0; i < nrspells; i++)
			{
				m_spellcheck[i] = false;

			}

			spells[0].info = dbcSpell.LookupEntry(ACID_SPIT);
			spells[0].targettype = TARGET_VARIOUS;
			spells[0].instant = true;
			spells[0].cooldown = 20;
			spells[0].perctrigger = 8.0f;
			spells[0].attackstoptimer = 1000;

			spells[1].info = dbcSpell.LookupEntry(TAIL_SWEEP);
			spells[1].targettype = TARGET_VARIOUS;
			spells[1].instant = true;
			spells[1].cooldown = 25;
			spells[1].perctrigger = 7.0f;
			spells[1].attackstoptimer = 1000;

			spells[2].info = dbcSpell.LookupEntry(ACID_BREATH);
			spells[2].targettype = TARGET_VARIOUS;
			spells[2].instant = true;
			spells[2].cooldown = 15;
			spells[2].perctrigger = 10.0f;
			spells[2].attackstoptimer = 1000;

			spells[3].info = dbcSpell.LookupEntry(ENRAGE);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = 0;
			spells[3].perctrigger = 0.0f;
			spells[3].attackstoptimer = 1000;

			Enraged = false;
		}

		void OnCombatStart(Unit* mTarget)
		{
			for(int i = 0; i < nrspells; i++)
				spells[i].casttime = 0;

			Enraged = false;

			RegisterAIUpdateEvent(_unit->GetBaseAttackTime(MELEE));
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);

			RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
		}

		void AIUpdate()
		{
			if(_unit->GetHealthPct() <= 20 && !Enraged && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(_unit, spells[3].info, spells[3].instant);

				Enraged = true;
				return;
			}

			float val = RandomFloat(100.0f);
			SpellCast(val);
		}

		void SpellCast(float val)
		{
			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())
			{
				float comulativeperc = 0;
				Unit* target = NULL;
				for(int i = 0; i < nrspells; i++)
				{
					spells[i].casttime--;

					if(m_spellcheck[i])
					{
						spells[i].casttime = spells[i].cooldown;
						target = _unit->GetAIInterface()->getNextTarget();
						switch(spells[i].targettype)
						{
							case TARGET_SELF:
							case TARGET_VARIOUS:
								_unit->CastSpell(_unit, spells[i].info, spells[i].instant);
								break;
							case TARGET_ATTACKING:
								_unit->CastSpell(target, spells[i].info, spells[i].instant);
								break;
							case TARGET_DESTINATION:
								_unit->CastSpellAoF(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), spells[i].info, spells[i].instant);
								break;
						}

						if(spells[i].speech != "")
						{
							_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
							_unit->PlaySoundToSet(spells[i].soundid);
						}

						m_spellcheck[i] = false;
						return;
					}

					if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
					{
						_unit->setAttackTimer(spells[i].attackstoptimer, false);
						m_spellcheck[i] = true;
					}
					comulativeperc += spells[i].perctrigger;
				}
			}
		}

	protected:

		bool Enraged;
		int nrspells;
};

// ClawAI

#define CN_CLAW 17827

#define MAUL				34298
#define CL_ECHOING_ROAR		31429
#define FERAL_CHARGE		39435
#define CL_ENRAGE			34971

class ClawAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ClawAI);
		SP_AI_Spell spells[4];
		bool m_spellcheck[4];

		ClawAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			nrspells = 4;
			for(int i = 0; i < nrspells; i++)
			{
				m_spellcheck[i] = false;
			}

			spells[0].info = dbcSpell.LookupEntry(MAUL);
			spells[0].targettype = TARGET_ATTACKING;
			spells[0].instant = true;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 15.0f;
			spells[0].attackstoptimer = 1000;

			spells[1].info = dbcSpell.LookupEntry(CL_ECHOING_ROAR);
			spells[1].targettype = TARGET_VARIOUS;
			spells[1].instant = true;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 8.0f;
			spells[1].attackstoptimer = 1000;

			spells[2].info = dbcSpell.LookupEntry(FERAL_CHARGE);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 3;
			spells[2].perctrigger = 18.0f;
			spells[2].attackstoptimer = 2000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 40.0f;

			spells[3].info = dbcSpell.LookupEntry(CL_ENRAGE);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = 30;
			spells[3].perctrigger = 15.0f;
			spells[3].attackstoptimer = 1000;
		}

		void OnCombatStart(Unit* mTarget)
		{
			for(int i = 0; i < nrspells; i++)
				spells[i].casttime = 0;

			spells[3].casttime = (uint32)time(NULL) + RandomUInt(10);

			RegisterAIUpdateEvent(_unit->GetBaseAttackTime(MELEE));
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);

			RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
		}

		void AIUpdate()
		{
			float val = RandomFloat(100.0f);
			SpellCast(val);
		}

		void SpellCast(float val)
		{
			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())
			{
				float comulativeperc = 0;
				Unit* target = NULL;
				for(int i = 0; i < nrspells; i++)
				{
					if(!spells[i].perctrigger) continue;

					if(m_spellcheck[i])
					{
						target = _unit->GetAIInterface()->getNextTarget();
						switch(spells[i].targettype)
						{
							case TARGET_SELF:
							case TARGET_VARIOUS:
								_unit->CastSpell(_unit, spells[i].info, spells[i].instant);
								break;
							case TARGET_ATTACKING:
								_unit->CastSpell(target, spells[i].info, spells[i].instant);
								break;
							case TARGET_DESTINATION:
								_unit->CastSpellAoF(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), spells[i].info, spells[i].instant);
								break;
							case TARGET_RANDOM_FRIEND:
							case TARGET_RANDOM_SINGLE:
							case TARGET_RANDOM_DESTINATION:
								CastSpellOnRandomTarget(i, spells[i].mindist2cast, spells[i].maxdist2cast, spells[i].minhp2cast, spells[i].maxhp2cast);
								break;
						}

						if(i == 1)
						{
							Unit* Swamplord = NULL;
							Swamplord = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 17826);
							if(Swamplord && Swamplord->isAlive())
							{
								_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Beast, obey me! Kill them at once!");
								_unit->PlaySoundToSet(10383);
							}
						}

						m_spellcheck[i] = false;
						return;
					}

					uint32 t = (uint32)time(NULL);
					if(val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger) && t > spells[i].casttime)
					{
						_unit->setAttackTimer(spells[i].attackstoptimer, false);
						spells[i].casttime = t + spells[i].cooldown;
						m_spellcheck[i] = true;
					}
					comulativeperc += spells[i].perctrigger;
				}
			}
		}

		void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
		{
			if(!maxdist2cast) maxdist2cast = 100.0f;
			if(!maxhp2cast) maxhp2cast = 100;

			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())
			{
				std::vector<Unit*> TargetTable;		/* From M4ksiu - Big THX to Capt who helped me with std stuff to make it simple and fully working <3 */
				/* If anyone wants to use this function, then leave this note!										 */
				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)
				{
					if(((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && (*itr)->IsUnit())  // isAttackable(_unit, (*itr)) &&
					{
						Unit* RandomTarget = NULL;
						RandomTarget = TO_UNIT(*itr);

						if(RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast * mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast * maxdist2cast && ((RandomTarget->GetHealthPct() >= minhp2cast && RandomTarget->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND) || isHostile(_unit, RandomTarget)))
						{
							TargetTable.push_back(RandomTarget);
						}
					}
				}

				if(_unit->GetHealthPct() >= minhp2cast && _unit->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND)
					TargetTable.push_back(_unit);

				if(!TargetTable.size())
					return;

				size_t RandTarget = rand() % TargetTable.size();

				Unit*  RTarget = TargetTable[RandTarget];

				if(!RTarget)
					return;

				switch(spells[i].targettype)
				{
					case TARGET_RANDOM_FRIEND:
					case TARGET_RANDOM_SINGLE:
						_unit->CastSpell(RTarget, spells[i].info, spells[i].instant);
						break;
					case TARGET_RANDOM_DESTINATION:
						_unit->CastSpellAoF(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), spells[i].info, spells[i].instant);
						break;
				}

				TargetTable.clear();
			}
		}

	protected:

		int nrspells;
};

// Swamplord Musel'ekAI
#define CN_SWAMPLORD_MUSELEK 17826

#define THROW_FREEZING_TRAP		31946	// needs more core support
#define KNOCK_AWAY_MUSELEK		18813
#define AIMED_SHOT				31623
#define MULTI_SHOT				30990
#define SHOT					32103

class SwamplordMuselekAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(SwamplordMuselekAI);
		SP_AI_Spell spells[5];
		bool m_spellcheck[5];

		SwamplordMuselekAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			nrspells = 2;
			for(int i = 0; i < nrspells; i++)
			{
				m_spellcheck[i] = false;
			}

			spells[0].info = dbcSpell.LookupEntry(THROW_FREEZING_TRAP);
			spells[0].targettype = TARGET_RANDOM_SINGLE; // not sure to target type
			spells[0].instant = true;
			spells[0].cooldown = 30;
			spells[0].perctrigger = 8.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;

			spells[1].info = dbcSpell.LookupEntry(KNOCK_AWAY_MUSELEK);
			spells[1].targettype = TARGET_ATTACKING;
			spells[1].instant = true;
			spells[1].cooldown = 20;
			spells[1].perctrigger = 12.0f;
			spells[1].attackstoptimer = 1000;

			spells[2].info = dbcSpell.LookupEntry(AIMED_SHOT);
			spells[2].targettype = TARGET_ATTACKING;
			spells[2].instant = false;
			spells[2].cooldown = 20;
			spells[2].perctrigger = 0.0f;
			spells[2].attackstoptimer = 6500;

			spells[3].info = dbcSpell.LookupEntry(MULTI_SHOT);
			spells[3].targettype = TARGET_ATTACKING; // changed from VARIOUS to prevent crashes
			spells[3].instant = true;
			spells[3].cooldown = 15;
			spells[3].perctrigger = 0.0f;
			spells[3].attackstoptimer = 1000;

			spells[4].info = dbcSpell.LookupEntry(SHOT);
			spells[4].targettype = TARGET_ATTACKING;
			spells[4].instant = true;
			spells[4].cooldown = 0;
			spells[4].perctrigger = 0.0f;
			spells[4].attackstoptimer = 1000;
		}

		void OnCombatStart(Unit* mTarget)
		{
			for(int i = 0; i < 5; i++)
				spells[i].casttime = 0;

			int RandomSpeach = rand() % 3;
			switch(RandomSpeach)
			{
				case 0:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "We fight to the death!");
					_unit->PlaySoundToSet(10384);
					break;
				case 1:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "I will end this quickly...");//http://www.wowwiki.com/Swamplord_Musel%27ek
					_unit->PlaySoundToSet(10385);
					break;
				case 2:
					_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Acalah pek ecta!");//http://www.wowwiki.com/Swamplord_Musel%27ek
					_unit->PlaySoundToSet(10386);
					break;
			}

			Unit* Bear = NULL;
			Bear = _unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), 17827);
			if(Bear && Bear->isAlive())
			{
				Bear->GetAIInterface()->AttackReaction(mTarget, 1, 0);
			}

			RegisterAIUpdateEvent(_unit->GetBaseAttackTime(MELEE));
		}

		void OnTargetDied(Unit* mTarget)
		{
			if(_unit->GetHealthPct() > 0)	// Hack to prevent double yelling (OnDied and OnTargetDied when creature is dying)
			{
				int RandomSpeach = rand() % 2;
				switch(RandomSpeach)
				{
					case 0:
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Krypta!");
						_unit->PlaySoundToSet(10387);
						break;
					case 1:
						_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "It is finished.");//http://www.wowwiki.com/Swamplord_Musel%27ek
						_unit->PlaySoundToSet(10388);
						break;
				}
			}
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);

			RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, "Well... done...");
			_unit->PlaySoundToSet(10389);

			RemoveAIUpdateEvent();
		}

		void AIUpdate()
		{
			if(_unit->GetAIInterface()->getNextTarget())
			{
				Unit* target = NULL;
				target = _unit->GetAIInterface()->getNextTarget();
				if(_unit->GetDistance2dSq(target) >= 100.0f && _unit->GetDistanceSq(target) <= 900.0f && RandomUInt(3) != 1)
				{
					_unit->GetAIInterface()->StopMovement(2000);
					if(_unit->GetCurrentSpell() == NULL)
					{
						uint32 t = (uint32)time(NULL);
						int RangedSpell = rand() % 100;
						if(RangedSpell >= 0 && RangedSpell <= 20 && t > spells[2].casttime)
						{
							_unit->CastSpell(target, spells[2].info, spells[2].instant);
							_unit->setAttackTimer(spells[2].attackstoptimer, false);

							spells[2].casttime = t + spells[2].cooldown;
						}

						if(RangedSpell > 20 && RangedSpell <= 40 && t > spells[3].casttime)
						{
							_unit->CastSpell(target, spells[3].info, spells[3].instant);
							_unit->setAttackTimer(spells[3].attackstoptimer, false);

							spells[3].casttime = t + spells[3].cooldown;
						}

						else
						{
							_unit->CastSpell(target, spells[4].info, spells[4].instant);
							_unit->setAttackTimer(spells[4].attackstoptimer, false);
						}
					}
				}

				else if(_unit->GetDistance2dSq(target) < 100.0f)
				{
					float val = RandomFloat(100.0f);
					SpellCast(val);
				}
			}

			else return;
		}

		void SpellCast(float val)
		{
			if(_unit->GetCurrentSpell() == NULL)
			{
				float comulativeperc = 0;
				Unit* target = NULL;
				for(int i = 0; i < nrspells; i++)
				{
					spells[i].casttime--;

					if(m_spellcheck[i])
					{
						spells[i].casttime = spells[i].cooldown;
						target = _unit->GetAIInterface()->getNextTarget();
						if(i != 1 || (i == 1 && _unit->GetDistance2dSq(target) <= 100.0f))
						{
							if(!spells[i].instant)
								_unit->GetAIInterface()->StopMovement(1);

							switch(spells[i].targettype)
							{
								case TARGET_SELF:
								case TARGET_VARIOUS:
									_unit->CastSpell(_unit, spells[i].info, spells[i].instant);
									break;
								case TARGET_ATTACKING:
									_unit->CastSpell(target, spells[i].info, spells[i].instant);
									break;
								case TARGET_DESTINATION:
									_unit->CastSpellAoF(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), spells[i].info, spells[i].instant);
									break;
							}
						}

						if(spells[i].speech != "")
						{
							_unit->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_UNIVERSAL, spells[i].speech.c_str());
							_unit->PlaySoundToSet(spells[i].soundid);
						}

						m_spellcheck[i] = false;
						return;
					}

					if((val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger)) || !spells[i].casttime)
					{
						_unit->setAttackTimer(spells[i].attackstoptimer, false);
						m_spellcheck[i] = true;
					}
					comulativeperc += spells[i].perctrigger;
				}
			}
		}

	protected:

		int nrspells;
};


// The Black StalkerAI

#define CN_THE_BLACK_STALKER 17882

#define CHAIN_LIGHTNING			31717 //39066 // 28167, 39066
#define LEVITATE				31704 // Not sure to id
#define STATIC_CHARGE			31715
#define SUMMON_SPORE_STRIDER	38755 // spawning adds only on Heroic! lack of core support =/

class TheBlackStalkerAI : public CreatureAIScript
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(TheBlackStalkerAI);
		SP_AI_Spell spells[4];
		bool m_spellcheck[4];

		TheBlackStalkerAI(Creature* pCreature) : CreatureAIScript(pCreature)
		{
			nrspells = 3;
			for(int i = 0; i < nrspells; i++)
			{
				m_spellcheck[i] = false;
			}

			spells[0].info = dbcSpell.LookupEntry(CHAIN_LIGHTNING);
			spells[0].targettype = TARGET_RANDOM_SINGLE;
			spells[0].instant = false;
			spells[0].cooldown = 15;
			spells[0].perctrigger = 12.0f;
			spells[0].attackstoptimer = 1000;
			spells[0].mindist2cast = 0.0f;
			spells[0].maxdist2cast = 40.0f;

			spells[1].info = dbcSpell.LookupEntry(LEVITATE);
			spells[1].targettype = TARGET_RANDOM_SINGLE;
			spells[1].instant = true;
			spells[1].cooldown = 30;
			spells[1].perctrigger = 8.0f;
			spells[1].attackstoptimer = 1000;
			spells[1].mindist2cast = 0.0f;
			spells[1].maxdist2cast = 40.0f;

			spells[2].info = dbcSpell.LookupEntry(STATIC_CHARGE);
			spells[2].targettype = TARGET_RANDOM_SINGLE;
			spells[2].instant = true;
			spells[2].cooldown = 25;
			spells[2].perctrigger = 8.0f;
			spells[2].attackstoptimer = 1000;
			spells[2].mindist2cast = 0.0f;
			spells[2].maxdist2cast = 40.0f;

			spells[3].info = dbcSpell.LookupEntry(SUMMON_SPORE_STRIDER);
			spells[3].targettype = TARGET_SELF;
			spells[3].instant = true;
			spells[3].cooldown = 10;
			spells[3].perctrigger = 0.0f;
			spells[3].attackstoptimer = 1000;
		}

		void OnCombatStart(Unit* mTarget)
		{
			for(int i = 0; i < nrspells; i++)
				spells[i].casttime = 0;

			spells[3].casttime = (uint32)time(NULL) + spells[3].cooldown + rand() % 6;

			RegisterAIUpdateEvent(_unit->GetBaseAttackTime(MELEE));
		}

		void OnCombatStop(Unit* mTarget)
		{
			_unit->GetAIInterface()->setCurrentAgent(AGENT_NULL);
			_unit->GetAIInterface()->SetAIState(STATE_IDLE);

			RemoveAIUpdateEvent();
		}

		void OnDied(Unit* mKiller)
		{
			RemoveAIUpdateEvent();
		}

		void AIUpdate()
		{
			uint32 t = (uint32)time(NULL);
			if(t > spells[3].casttime && _unit->GetCurrentSpell() == NULL)
			{
				_unit->CastSpell(_unit, spells[3].info, spells[3].instant);

				spells[3].casttime = (uint32)time(NULL) + spells[3].cooldown + rand() % 6;
			}

			float val = RandomFloat(100.0f);
			SpellCast(val);
		}

		void SpellCast(float val)
		{
			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())
			{
				float comulativeperc = 0;
				Unit* target = NULL;
				for(int i = 0; i < nrspells; i++)
				{
					if(!spells[i].perctrigger) continue;

					if(m_spellcheck[i])
					{
						if(!spells[i].instant)
							_unit->GetAIInterface()->StopMovement(1);

						target = _unit->GetAIInterface()->getNextTarget();
						switch(spells[i].targettype)
						{
							case TARGET_SELF:
							case TARGET_VARIOUS:
								_unit->CastSpell(_unit, spells[i].info, spells[i].instant);
								break;
							case TARGET_ATTACKING:
								_unit->CastSpell(target, spells[i].info, spells[i].instant);
								break;
							case TARGET_DESTINATION:
								_unit->CastSpellAoF(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), spells[i].info, spells[i].instant);
								break;
							case TARGET_RANDOM_FRIEND:
							case TARGET_RANDOM_SINGLE:
							case TARGET_RANDOM_DESTINATION:
								CastSpellOnRandomTarget(i, spells[i].mindist2cast, spells[i].maxdist2cast, spells[i].minhp2cast, spells[i].maxhp2cast);
								break;
						}

						m_spellcheck[i] = false;
						return;
					}

					uint32 t = (uint32)time(NULL);
					if(val > comulativeperc && val <= (comulativeperc + spells[i].perctrigger) && t > spells[i].casttime)
					{
						_unit->setAttackTimer(spells[i].attackstoptimer, false);
						spells[i].casttime = t + spells[i].cooldown;
						m_spellcheck[i] = true;
					}
					comulativeperc += spells[i].perctrigger;
				}
			}
		}

		void CastSpellOnRandomTarget(uint32 i, float mindist2cast, float maxdist2cast, int minhp2cast, int maxhp2cast)
		{
			if(!maxdist2cast) maxdist2cast = 100.0f;
			if(!maxhp2cast) maxhp2cast = 100;

			if(_unit->GetCurrentSpell() == NULL && _unit->GetAIInterface()->getNextTarget())
			{
				std::vector<Unit*> TargetTable;		/* From M4ksiu - Big THX to Capt who helped me with std stuff to make it simple and fully working <3 */
				/* If anyone wants to use this function, then leave this note!										 */
				for(set<Object*>::iterator itr = _unit->GetInRangeSetBegin(); itr != _unit->GetInRangeSetEnd(); ++itr)
				{
					if(((spells[i].targettype == TARGET_RANDOM_FRIEND && isFriendly(_unit, (*itr))) || (spells[i].targettype != TARGET_RANDOM_FRIEND && isHostile(_unit, (*itr)) && (*itr) != _unit)) && (*itr)->IsUnit())  // isAttackable(_unit, (*itr)) &&
					{
						Unit* RandomTarget = NULL;
						RandomTarget = TO_UNIT(*itr);

						if(RandomTarget->isAlive() && _unit->GetDistance2dSq(RandomTarget) >= mindist2cast * mindist2cast && _unit->GetDistance2dSq(RandomTarget) <= maxdist2cast * maxdist2cast && ((RandomTarget->GetHealthPct() >= minhp2cast && RandomTarget->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND) || (_unit->GetAIInterface()->getThreatByPtr(RandomTarget) > 0 && isHostile(_unit, RandomTarget))))
						{
							TargetTable.push_back(RandomTarget);
						}
					}
				}

				if(_unit->GetHealthPct() >= minhp2cast && _unit->GetHealthPct() <= maxhp2cast && spells[i].targettype == TARGET_RANDOM_FRIEND)
					TargetTable.push_back(_unit);

				if(!TargetTable.size())
					return;

				size_t RandTarget = rand() % TargetTable.size();

				Unit*  RTarget = TargetTable[RandTarget];

				if(!RTarget)
					return;

				switch(spells[i].targettype)
				{
					case TARGET_RANDOM_FRIEND:
					case TARGET_RANDOM_SINGLE:
						_unit->CastSpell(RTarget, spells[i].info, spells[i].instant);
						break;
					case TARGET_RANDOM_DESTINATION:
						_unit->CastSpellAoF(RTarget->GetPositionX(), RTarget->GetPositionY(), RTarget->GetPositionZ(), spells[i].info, spells[i].instant);
						break;
				}

				TargetTable.clear();
			}
		}

	protected:

		int nrspells;
};

void SetupTheUnderbog(ScriptMgr* mgr)
{
	mgr->register_creature_script(CN_HUNGARFEN, &HUNGARFENAI::Create);
	mgr->register_creature_script(CN_GHAZAN, &GhazanAI::Create);
	mgr->register_creature_script(CN_CLAW, &ClawAI::Create);
	mgr->register_creature_script(CN_SWAMPLORD_MUSELEK, &SwamplordMuselekAI::Create);
	mgr->register_creature_script(CN_THE_BLACK_STALKER, &TheBlackStalkerAI::Create);
}
