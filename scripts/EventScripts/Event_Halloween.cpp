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

/*
Event : Halloween
Author: Angelis
Team  : Sun++
*/

//Black Cat
class BlackCat : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(BlackCat)
		BlackCat(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

		void OnDied(Unit* pKiller)
		{
			pKiller->CastSpell(pKiller, dbcSpell.LookupEntry(39477), true);
		}
};

// HEADLESS HORSEMAN ENCOUNTER
#define	WPCount	30

static Location WaypointGoldshire[] =
{
	{ -9502.733398f, 31.395960f, 60.433193f, 1.217366f }, //1
	{ -9493.925781f, 55.272415f, 60.433193f, 0.781469f },
	{ -9483.589844f, 63.685684f, 60.433193f, 6.224273f },
	{ -9463.258789f, 62.515587f, 60.433193f, 6.204639f },
	{ -9457.368164f, 48.343132f, 66.931587f, 4.641701f },
	{ -9458.772461f, 27.414370f, 77.199722f, 4.001603f },
	{ -9473.457031f, 29.496262f, 77.199722f, 1.394081f },
	{ -9471.234275f, 44.239151f, 75.393852f, 1.241714f },
	{ -9459.474609f, 81.118446f, 71.725540f, 1.720021f },
	{ -9467.220703f, 88.311104f, 71.786453f, 2.572178f },	//10
	{ -9486.188477f, 83.939690f, 82.718826f, 3.569634f }, //11 Starting round (3 rounds left)
	{ -9506.228516f, 36.876194f, 89.180916f, 6.167746f },
	{ -9437.569396f, 34.403599f, 75.426025f, 1.270783f },
	{ -9448.488281f, 85.930862f, 75.290497f, 2.909909f },
	{ -9477.427734f, 86.952667f, 70.950249f, 3.318317f }, //15
	{ -9486.188477f, 83.939690f, 82.718826f, 3.569634f }, //16 Next round (2 rounds left)
	{ -9506.228516f, 36.876194f, 89.180916f, 6.167746f },
	{ -9437.569396f, 34.403599f, 75.426025f, 1.270783f },
	{ -9448.488281f, 85.930862f, 75.290497f, 2.909909f },
	{ -9477.427734f, 86.952667f, 70.950249f, 3.318317f }, //20
	{ -9486.188477f, 83.939690f, 82.718826f, 3.569634f }, //21 Next round (1 rounds left)
	{ -9506.228516f, 36.876194f, 89.180916f, 6.167746f },
	{ -9437.569396f, 34.403599f, 75.426025f, 1.270783f },
	{ -9448.488281f, 85.930862f, 75.290497f, 2.909909f },
	{ -9477.427734f, 86.952667f, 70.950249f, 3.318317f }, //25
	{ -9486.188477f, 83.939690f, 82.718826f, 3.569634f }, //26 Next round (0 rounds left)
	{ -9506.228516f, 36.876194f, 89.180916f, 6.167746f },
	{ -9437.569396f, 34.403599f, 75.426025f, 1.270783f },
	{ -9448.488281f, 85.930862f, 75.290497f, 2.909909f },
	{ -9477.427734f, 86.952667f, 70.950249f, 3.318317f } // 30
};

// Shade of the HorsemanAI
#define CN_SHADE_OF_THE_HORSEMAN				23543
#define SHADE_OF_THE_HORSEMAN_SUMMON			42394  //Don't think this one is the correct spell
#define CN_HEADLESS_HORSEMAN_FIRE				23537
/*
 * Research
 * NPC:
 * http://www.wowhead.com/?npc=23537 Headless Horseman - Fire (DND) should be invisible? created by ->
 * http://www.wowhead.com/?spell=42118
 * I guess this is the target of the water spells
 * Need to check all visual auras for these http://www.wowhead.com/?search=horseman#uncategorized-spells
 */
class ShadeOfTheHorsemanAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(ShadeOfTheHorsemanAI)
		ShadeOfTheHorsemanAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature)
		{
			_unit->GetAIInterface()->SetAllowedToEnterCombat(false);
			_unit->SetMount(22653);

			//Emotes
			Emote("Prepare yourselves, the bells have tolled! Shelter your weak, your young, and your old! Each of you shall pay the final sum. Cry for mercy, the reckoning has come!", Text_Yell, 11966);	//On Spawn?

			for(uint32 i=0; i<WPCount; ++i)
			{
				WayPoint* wp = _unit->CreateWaypointStruct();
				wp->id = i;
				wp->x = WaypointGoldshire[i].x;
				wp->y = WaypointGoldshire[i].y;
				wp->z = WaypointGoldshire[i].z;
				wp->o = WaypointGoldshire[i].o;
				wp->waittime = 0;
				wp->flags = Flag_Fly;
				wp->forwardemoteoneshot = false;
				wp->forwardemoteid = 0;
				wp->backwardemoteoneshot = false;
				wp->backwardemoteid = 0;
				wp->forwardskinid = 0;
				wp->backwardskinid = 0;
				_unit->GetAIInterface()->addWayPoint(wp);
			}
		}

		void OnReachWP(uint32 iWaypointId, bool bForwards)
		{
			if(iWaypointId == WPCount)   // Reached end
			{
				_unit->GetAIInterface()->setMoveType(MOVEMENTTYPE_DONTMOVEWP);
				if(_unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), CN_HEADLESS_HORSEMAN_FIRE))     // CASE players win
				{
					Emote( "My flames have died, left not a spark! I shall send you now to the lifeless dark!", Text_Yell, 11968);
					_unit->Despawn(30000, 0); //Despawn after 30 secs
				}else // CASE players lost
				{
					Emote("Fire consumes! You've tried and failed. Let there be no doubt, justice prevailed!", Text_Yell, 11967);
					_unit->Despawn(12000, 0); //Despawn after 12 secs
				}
			}else if(_unit->GetMapMgr()->GetAreaID(_unit->GetPositionX(), _unit->GetPositionY()) == 87)
			{
				if(iWaypointId == 6)
					_unit->CastSpell(_unit, dbcSpell.LookupEntry(42118), true);
			}
		}

		void OnDied(Unit* pKiller)
		{
			Emote("So eager you are, for my blood to spill. Yet to vanquish me, 'tis my head you must kill!", Text_Yell, 11969);
			
			if(GameObject* Pumpkin = _unit->GetMapMgr()->GetInterface()->SpawnGameObject(2883, _unit->GetPositionX() + RandomFloat(5.0f), _unit->GetPositionY() + RandomFloat(5.0f), _unit->GetPositionZ(), _unit->GetOrientation(), true, 0, 0, 1))
				_unit->CastSpell(Pumpkin->GetGUID(), dbcSpell.LookupEntry(42277), true);
		}
};

// Headless Horseman - Wisp Invis
#define CN_HEADLESS_HORSEMAN_WISP_INVIS				24034//						42394

class HeadlessHorsemanWispInvisAI : public MoonScriptCreatureAI
{
	public:
		ADD_CREATURE_FACTORY_FUNCTION(HeadlessHorsemanWispInvisAI)
		HeadlessHorsemanWispInvisAI(Creature* pCreature) : MoonScriptCreatureAI(pCreature) {}

		void AIUpdate()
		{
			time_t tiempo;
			struct tm* tmPtr;
			tiempo = UNIXTIME;
			tmPtr = localtime(&tiempo);
			if(tmPtr->tm_min == 0 && (tmPtr->tm_hour % 4) == 0)   // All check for the time
			{
				if(_unit->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(_unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), CN_SHADE_OF_THE_HORSEMAN))
				{
					SpawnCreature(CN_SHADE_OF_THE_HORSEMAN, _unit->GetPositionX(), _unit->GetPositionY(), _unit->GetPositionZ(), _unit->GetOrientation());
					ModifyAIUpdateEvent(4 * 60 * 1000);
				}
			}
		}
};

class WaterBarrel : public GameObjectAIScript
{
	public:
		WaterBarrel(GameObject*  goinstance) : GameObjectAIScript(goinstance) {}
		static GameObjectAIScript* Create(GameObject* GO) { return new WaterBarrel(GO); }

		void OnActivate(Player* pPlayer)
		{
			SlotResult slotresult;
			ItemPrototype* proto = ItemPrototypeStorage.LookupEntry(32971);
			if(!proto)
				return;

			slotresult = pPlayer->GetItemInterface()->FindFreeInventorySlot(proto);

			if(!slotresult.Result)
			{
				pPlayer->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
				return;
			}else
			{
				if(pPlayer->GetItemInterface()->GetItemCount(32971, false) == 0)
				{
					Item* itm = objmgr.CreateItem(32971, pPlayer);
					pPlayer->GetItemInterface()->SafeAddItem(itm, slotresult.ContainerSlot, slotresult.Slot);
				}else
				{
					pPlayer->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
					return;
				}
			}
		}
};

void SetupHalloween(ScriptMgr* mgr)
{
	mgr->register_creature_script(22816, &BlackCat::Create);
	mgr->register_creature_script(CN_HEADLESS_HORSEMAN_WISP_INVIS, &HeadlessHorsemanWispInvisAI::Create);
	mgr->register_creature_script(CN_SHADE_OF_THE_HORSEMAN, &ShadeOfTheHorsemanAI::Create);
	mgr->register_gameobject_script(186234, &WaterBarrel::Create);
}
