/*
 * WhyScript Scripts for WhyEmu MMORPG Server
 * Copyright (C) 2010 WhyDB Team <http://www.whydb.org/>
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

// Thundercaller (Og to Uc) zepplin definitions
#define THUNDERCALLER 164871
#define ZAPETTA 9566
#define FREZZA 9564
#define KRAXX 23713
#define KRIXX 23635
#define CLOUDKICKER 25077
#define COPPERNUT 25070
#define RUSTHAMMER 25071
#define SPARKFLY 25074
#define QUICKFIX 25072
#define FAIRWEATHER 25076

// The Iron Eagle (Og to grom'gol) zeppelin definitions
#define IRONEAGLE 175080
#define SNURK 12136
#define NEZRAZ 3149
#define FASTWRENCH 24931
#define GAZZLEGEAR 24930
#define CROSSWIRE 24929

// The Purple Princess ( Undercity to Grom'Gol) zeppelin definitions
#define PURPLEPRINCESS 176495
#define HINDENBURG 3150
#define OVERSPECK 12137
#define HATCH 25104
#define HAMMERFLANGE 25100
#define DUUNA 25106
#define BOLTSHINE 25103
#define CUTPIPE 25101

class Cloudkicker : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Cloudkicker, MoonScriptCreatureAI)
	Cloudkicker(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
	{
		state = -1; // base state, means do nothing
	}

	void AIUpdate()
	{
		// random events
		// random script when starting #1
		if( state == 0 )
		{
			Emote("Mister Copperpot, you may take us out.", Text_Say);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #2
		if( state == 1 )
		{
			Emote("Full spead ahead Mister Copperbolt!", Text_Say);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #3
		if( state == 2 )
		{
			Emote("Take us out nice and fast mister Copperpants.", Text_Say);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #3
		if( state == 3 )
			state = 1;

		// we just arrived to kalimdor, landing
		if( state == 4 )
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );

			if( Rand(50) )
				Emote("I can't believe how lucky we got on that trip! I really am the greatest sky-captain in all realms!", Text_Say);
			else
				Emote("Another successful trip! Come on boys let's buzz the tower!", Text_Say);

			timer = AddTimer(8000);
			state = 5;
		}
		if( state == 5 && IsTimerFinished(timer) )
		{
			RemoveTimer(timer);
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			state = -1;
			RemoveAIUpdateEvent();
		}

		ParentClass::AIUpdate();
	}
/*
	void OnTransporterUpdate(Transporter * pTransporter)
	{
		// we just changed our map, we should shout that we are docking :)
		if( pTransporter->mLastWaypoint->second.teleport || pTransporter->mLastWaypoint->second.mapid != pTransporter->GetMapId() )
		{
			if( Rand(50) )
			{
				// start dialog with state 4
				state = 4;
				RegisterAIUpdateEvent(1000);
			}
		}
		// we are starting our way
		else if( pTransporter->mLastWaypoint->second.delayed )
		{
			// start dialog with random state 0 - 3
			state = pTransporter->start_event;
			RegisterAIUpdateEvent(1000);
		}
		ParentClass::OnTransporterUpdate(pTransporter);
	}
*/
private:
	int8 state;
	int32 timer;
};

class Coppernut : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Coppernut, MoonScriptCreatureAI)
	Coppernut(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
	{
		state = 0;
	}

	void AIUpdate()
	{
		// random script when starting #1
		if( state == 0 )
		{
			timer = AddTimer(4000);
			state = 7;
		}
		if( state == 7 && IsTimerFinished(timer) )
		{
			Emote("Sir, if you could at least get my gender correct...", Text_Say);
			RemoveTimer(timer);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #2
		if( state == 1 )
		{
			timer = AddTimer(4000);
			state = 8;
		}
		if( state == 8 && IsTimerFinished(timer) )
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			Emote("Mister Fairweather, slow ahead if you please!", Text_Say);
			RemoveTimer(timer);
			timer = AddTimer(5000);
			state = 9;
		}
		if( state == 9 && IsTimerFinished(timer) )
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			Emote("Close sir...", Text_Say);
			RemoveTimer(timer);
			state = -1;
			RemoveAIUpdateEvent();
		}
		// random script when starting #3
		if( state == 2 )
		{
			timer = AddTimer(4000);
			state = 10;
		}
		if( state == 10 && IsTimerFinished(timer) )
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			Emote("Mister Fairweather, slow ahead if you please!", Text_Say);
			RemoveTimer(timer);
			timer = AddTimer(5000);
			state = 11;
		}
		if( state == 11 && IsTimerFinished(timer) )
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			Emote("You almost got my name right that time, sir.", Text_Say);
			RemoveTimer(timer);
			state = -1;
			RemoveAIUpdateEvent();
		}
		if( state == 3 )
			state = 1;
		
		// we just arrived to kalimdor, landing script
		if( state == 4 )
		{
			timer = AddTimer(4000);
			state = 5;
		}
		if( state == 5 && IsTimerFinished(timer) )
		{
			RemoveTimer(timer);
			turn_timer = AddTimer(4000);
			state = 6;
				
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			Emote("Prepare to dock!", Text_Say);
			GetUnit()->Emote(EMOTE_ONESHOT_SHOUT);
		}
		if( state == 6 && IsTimerFinished(turn_timer) )
		{
			RemoveTimer(turn_timer);
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			state = -1;
			RemoveAIUpdateEvent();
		}

		ParentClass::AIUpdate();
	}
/*
	void OnTransporterUpdate(Transporter * pTransporter)
	{
		// we just changed our map, we should shout that we are docking :)
		if( pTransporter->mLastWaypoint->second.teleport || pTransporter->mLastWaypoint->second.mapid != pTransporter->GetMapId() )
		{
			// start dialog with state 1
			state = 4;
			RegisterAIUpdateEvent(1000);
		}
		// we are starting our way
		else if( pTransporter->mLastWaypoint->second.delayed )
		{
			// start dialog with random state 0 - 3
			state = pTransporter->start_event;
			RegisterAIUpdateEvent(1000);
		}
		
		ParentClass::OnTransporterUpdate(pTransporter);
	}
*/
private:
	uint8 state;
	int32 timer;
	int32 turn_timer;
};

class Fairweather : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Fairweather, MoonScriptCreatureAI)
	Fairweather(Creature *pCreature) : MoonScriptCreatureAI(pCreature) {}

/*
	void OnTransporterUpdate(Transporter * pTransporter)
	{
		if( pTransporter->state == TRANSPORTER_STATE_JUST_CHANGED_MAP || pTransporter->state == TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING )
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			GetUnit()->SetEmoteState(EMOTE_STATE_USESTANDING);
		}
		else
		{
			GetUnit()->SetFacing( GetUnit()->GetOrientation()+float(M_PI) );
			GetUnit()->SetEmoteState(0);
		}
		ParentClass::OnTransporterUpdate(pTransporter);
	}
*/
};

class Hatch : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Hatch, MoonScriptCreatureAI)
	Hatch(Creature *pCreature) : MoonScriptCreatureAI(pCreature)
	{
		state = 0;
	}

	void AIUpdate()
	{
		if( state == 1 )
		{
			timer = AddTimer(5000);
			state = 2;
		}
		if( state == 2 && IsTimerFinished(timer) )
		{
			RemoveTimer(timer);
			state = 0;
			Emote("It's go time!", Text_Say);
			GetUnit()->SetStandState(0);
			RemoveAIUpdateEvent();
		}

		ParentClass::AIUpdate();
	}
/*
	void OnTransporterUpdate(Transporter * pTransporter)
	{
		// we are docking
		if( pTransporter->mCurrentWaypoint->second.delayed )
		{
			Emote("I'm going to take short nap. Do you think you can handle the ship while she's not moving?", Text_Say);
			GetUnit()->SetStandState(3);
		}
		// we are starting our way
		else if( pTransporter->mLastWaypoint->second.delayed )
		{
			state = 1;
			RegisterAIUpdateEvent(1000);
		}
		ParentClass::OnTransporterUpdate(pTransporter);
	}
*/
private:
	uint8 state;
	int32 timer;
};

class Hammerflange : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Hammerflange, MoonScriptCreatureAI)
	Hammerflange(Creature * pCreature) : MoonScriptCreatureAI(pCreature) {}

/*
	void OnTransporterUpdate(Transporter * pTransporter)
	{
		// we are starting our way
		if( pTransporter->mLastWaypoint->second.delayed )
		{
			Emote("NAP'S OVER!! WE ARE HEADING OUT!", Text_Say);
		}
		ParentClass::OnTransporterUpdate(pTransporter);
	}
*/
};

class Duuna : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Duuna, MoonScriptCreatureAI)
	Duuna(Creature * pCreature) : MoonScriptCreatureAI(pCreature) {}
/*
	void OnTransporterUpdate(Transporter * pTransporter)
	{
		// we are starting our way
		if( pTransporter->mLastWaypoint->second.delayed || pTransporter->mLastWaypoint->second.teleport || pTransporter->mLastWaypoint->second.mapid != pTransporter->GetMapId() )
		{
			// sit
			GetUnit()->SetStandState(1);
		}
		// next waypoint will be docking
		else if( pTransporter->mNextWaypoint->second.delayed )
		{
			// stand up
			GetUnit()->SetStandState(0);
		}
		ParentClass::OnTransporterUpdate(pTransporter);
	}
*/
};

// this is simple worker AI
class Zepp_Worker : public MoonScriptCreatureAI
{
public:
	MOONSCRIPT_FACTORY_FUNCTION(Zepp_Worker, MoonScriptCreatureAI)
	Zepp_Worker(Creature * pCreature) : MoonScriptCreatureAI(pCreature)
	{
		state = 0;
		initiliaze_state = RandomUInt(1); // begin at random state
	}

	void OnLoad()
	{
		RegisterAIUpdateEvent(1000);
		ParentClass::OnLoad();
	}

	void AIUpdate()
	{
		//these are used for initializing
		if( initiliaze_state == 0 || ( IsTimerFinished(timer) && state == 0 ) )
		{
			GetUnit()->SetEmoteState(EMOTE_STATE_WORK);
			timer = AddTimer((RandomUInt(3)+6)*1000);
			state = 2;
			initiliaze_state = 2;
		}
		else if( initiliaze_state == 1 || ( IsTimerFinished(timer) && state == 1 ) )
		{
			RemoveTimer(timer);
			GetUnit()->SetEmoteState(EMOTE_STATE_USESTANDING);
			timer = AddTimer((RandomUInt(3)+6)*1000);
			state = 2;
			initiliaze_state = 2;
		}
		else if( IsTimerFinished(timer) && state == 2 )
		{
			RemoveTimer(timer);
			GetUnit()->SetEmoteState(0);
			timer = AddTimer(2000);
			state = RandomUInt(1);
		}

		ParentClass::AIUpdate();
	}
private:
	uint8 state;
	uint8 initiliaze_state;
	int32 timer;
};

void ZeppelinThundercaller(Transporter * pTransporter, bool delayed)
{
	float x = pTransporter->GetPositionX();
	float y = pTransporter->GetPositionY();
	float z = pTransporter->GetPositionZ();

	// zeppelin just docked
	if(delayed)
	{
		// undercity
		if( pTransporter->GetMapId() == 0 )
		{
			Creature * cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, ZAPETTA);
			if( !cr )
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!");

			if( Rand(35) )
			cr->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_ORCISH, "There goes the zeppelin to Orgrimmar. I hope there's no explosions this time.", 61500);

		}
		else
		// orgrimmar
		{
			Creature * cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, FREZZA);
			if( !cr )
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Undercity has just arrived! All aboard for Tirisfal Glades!");
		}
	}
}

void ZeppelinIronEagle(Transporter * pTransporter, bool delayed)
{
	float x = pTransporter->GetPositionX();
	float y = pTransporter->GetPositionY();
	float z = pTransporter->GetPositionZ();

	// zeppelin just docked
	if(delayed)
	{
		// grom'gol - this one is not announcing it!
		/*if( pTransporter->GetMapId() == 0 )
		{
			Creature * cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, NEZRAZ);
			if( !cr )
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Orgrimmar has just arrived! All aboard for Durotar!");
		}
		else*/
		// orgrimmar
		{
			Creature * cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, SNURK);
			if( !cr )
				return;

			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Grom'gol has just arrived! All aboard for Stranglethorn!");
		}
	}
}

void ZeppelinPurplePrincess(Transporter * pTransporter, bool delayed)
{
	float x = pTransporter->GetPositionX();
	float y = pTransporter->GetPositionY();
	float z = pTransporter->GetPositionZ();

	// zeppelin just docked
	if(delayed)
	{
		// this one is not announcing on retail!
		/*Creature * cr = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, OVERSPECK);
		if( cr )
			cr->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Undercity has just arrived! All aboard for Tirisfal Glades!");*/

		Creature * cr2 = pTransporter->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(x, y, z, HINDENBURG);
		if( cr2 )
			cr2->SendChatMessage(CHAT_MSG_MONSTER_YELL, LANG_ORCISH, "The zeppelin to Grom'gol has just arrived! All aboard for Stranglethorn!");
	}
}

void OnTransporterUpdate(Transporter * pTransporter, bool delayed)
{
	switch( pTransporter->GetEntry() )
	{
		// Thundercaller ( Undercity <-> Orgrimmar )
		case THUNDERCALLER:
			ZeppelinThundercaller(pTransporter, delayed);
		break;
		// Iron Eagle ( Orgrimmar <-> Grom'Gol )
		case IRONEAGLE:
			ZeppelinIronEagle(pTransporter, delayed);
		break;
		// Purple Princess ( Undercity <-> Grom'Gol )
		case PURPLEPRINCESS:
			ZeppelinPurplePrincess(pTransporter, delayed);
		break;
	}
}

/* *************************************************
         ZEPPELIN MASTERS' GOSSIP
   *************************************************
*/

class OG_UC_Gossip : public GossipScript
{
public:
	void GossipHello(Object *pObject, Player *Plr, bool AutoSend)
	{
		GossipMenu * Menu;

		uint32 textid = 1;
		switch( pObject->GetEntry() )
		{
			case ZAPETTA: textid = 2644; break;
			case FREZZA: textid = 2642; break;
			case KRAXX: textid = 11234; break;
			case KRIXX: textid = 11189; break;
		}

		objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), textid, Plr );
		Menu->AddItem( 0, "Where is the zeppelin now?", 1 );
		Menu->SendTo( Plr );
	}
/*
	void GossipSelectOption(Object *pObject, Player *Plr, uint32 Id, uint32 IntId, const char *EnteredCode)
	{
		Transporter * pTransporter = objmgr.GetTransporterByEntry( THUNDERCALLER );
		if( !pTransporter )
			return;

		GossipMenu * Menu = NULL;

		uint32 mapid = pTransporter->GetMapId();

		switch( pTransporter->state )
		{
			case TRANSPORTER_STATE_JUST_CHANGED_MAP:
			{
				if( mapid == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11170, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11182, Plr );
			}
			break;
			case TRANSPORTER_STATE_JUST_ARRIVED_TO_DOCKING:
			{
				if( mapid == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11173, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11169, Plr );
			}
			break;
			case TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING:
			{
				if( mapid == 1 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11170, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11182, Plr );
			}
			break;
		}

		if( Menu )
			Menu->SendTo( Plr );
	}
*/
};

class OG_GG_Gossip : public GossipScript
{
public:
	void GossipHello(Object *pObject, Player *Plr, bool AutoSend)
	{
		GossipMenu * Menu;

		uint32 textid = 1;
		switch( pObject->GetEntry() )
		{
			case SNURK: textid = 4693; break;
			case NEZRAZ: textid = 2644; break;
		}

		objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), textid, Plr );
		Menu->AddItem( 0, "Where is the zeppelin now?", 1 );
		Menu->SendTo( Plr );
	}

/*
	void GossipSelectOption(Object *pObject, Player *Plr, uint32 Id, uint32 IntId, const char *EnteredCode)
	{
		Transporter * pTransporter = objmgr.GetTransporterByEntry( IRONEAGLE );
		if( !pTransporter )
			return;

		GossipMenu * Menu = NULL;

		uint32 mapid = pTransporter->GetMapId();

		switch( pTransporter->state )
		{
			case TRANSPORTER_STATE_JUST_CHANGED_MAP:
			{
				if( mapid == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11170, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11172, Plr );
			}
			break;
			case TRANSPORTER_STATE_JUST_ARRIVED_TO_DOCKING:
			{
				if( mapid == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11167, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11169, Plr );
			}
			break;
			case TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING:
			{
				if( mapid == 1 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11170, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11172, Plr );
			}
			break;
		}

		if( Menu )
			Menu->SendTo( Plr );
	}
*/
};

class UC_GG_Gossip : public GossipScript
{
public:
	void GossipHello(Object *pObject, Player *Plr, bool AutoSend)
	{
		GossipMenu * Menu;

		uint32 textid = 1;
		switch( pObject->GetEntry() )
		{
			case OVERSPECK: textid = 2642; break;
			case HINDENBURG: textid = 2753; break;
		}

		objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), textid, Plr );
		Menu->AddItem( 0, "Where is the zeppelin now?", 1 );
		Menu->SendTo( Plr );
	}
/*
	void GossipSelectOption(Object *pObject, Player *Plr, uint32 Id, uint32 IntId, const char *EnteredCode)
	{
		Transporter * pTransporter = objmgr.GetTransporterByEntry( PURPLEPRINCESS );
		if( !pTransporter )
			return;

		GossipMenu * Menu = NULL;

		// special case, this transporter is still on 1 map, so we must check by position
		float x = pTransporter->GetPositionX();
		float y = pTransporter->GetPositionY();
		float z = pTransporter->GetPositionZ();

		switch( pTransporter->state )
		{
			
			case TRANSPORTER_STATE_JUST_CHANGED_MAP:
			{
				if( 0 == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11175, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11181, Plr );
			}
			break;
			case TRANSPORTER_STATE_JUST_ARRIVED_TO_DOCKING:
			{
				if( 0 == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11180, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11179, Plr );
			}
			break;
			case TRANSPORTER_STATE_JUST_DEPARTED_FROM_DOCKING:
			{
				if( 0 == 0 ) 
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11181, Plr );
				else
					objmgr.CreateGossipMenuForPlayer( &Menu, pObject->GetGUID(), 11175, Plr );
			}
			break;
		}

		if( Menu )
			Menu->SendTo( Plr );
	}
*/
};

void SetupTransportCreatureScripts(ScriptMgr * mgr)
{
	// main script used for zeppelin masters
	//mgr->register_hook( SERVER_HOOK_EVENT_ON_TRANSPORTER_UPDATE, (void *)&OnTransporterUpdate );

	// CREATURE SCRIPTS
	// zeppelin Thundercaller
	mgr->register_creature_script( CLOUDKICKER, &Cloudkicker::Create );
	mgr->register_creature_script( COPPERNUT, &Coppernut::Create );
	mgr->register_creature_script( FAIRWEATHER, &Fairweather::Create );
	mgr->register_creature_script( RUSTHAMMER, &Zepp_Worker::Create );
	mgr->register_creature_script( SPARKFLY, &Zepp_Worker::Create );
	mgr->register_creature_script( QUICKFIX, &Zepp_Worker::Create );

	// zeppelin the purple princess
	mgr->register_creature_script( HATCH, &Hatch::Create );
	mgr->register_creature_script( HAMMERFLANGE, &Hammerflange::Create );
	mgr->register_creature_script( DUUNA, &Duuna::Create );
	mgr->register_creature_script( BOLTSHINE, &Zepp_Worker::Create );
	mgr->register_creature_script( CUTPIPE, &Zepp_Worker::Create );

	// zeppelin the iron eagle
	mgr->register_creature_script( FASTWRENCH, &Zepp_Worker::Create );
	mgr->register_creature_script( GAZZLEGEAR, &Zepp_Worker::Create );
	mgr->register_creature_script( CROSSWIRE, &Zepp_Worker::Create );

	// ZEPPELIN MASTERS
	mgr->register_gossip_script( ZAPETTA, new OG_UC_Gossip() );
	mgr->register_gossip_script( FREZZA, new OG_UC_Gossip() );
	mgr->register_gossip_script( KRIXX, new OG_UC_Gossip() );
	mgr->register_gossip_script( KRAXX, new OG_UC_Gossip() );
	mgr->register_gossip_script( SNURK, new OG_GG_Gossip() );
	mgr->register_gossip_script( NEZRAZ, new OG_GG_Gossip() );
	mgr->register_gossip_script( OVERSPECK, new UC_GG_Gossip() );
	mgr->register_gossip_script( HINDENBURG, new UC_GG_Gossip() );
}