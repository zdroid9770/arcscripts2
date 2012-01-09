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

class InServiceOfLichKing : public QuestScript
{
public:
	void OnQuestStart(Player * mTarget, QuestLogEntry * qLogEntry)
	{
		mTarget->PlaySound(14734);
		sEventMgr.AddEvent(mTarget, &Player::PlaySound, (uint32)14735, EVENT_UNK, 23000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		sEventMgr.AddEvent(mTarget, &Player::PlaySound, (uint32)14736, EVENT_UNK, 49000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
};

#define CN_INITIATE_1				29519
#define CN_INITIATE_2				29565
#define CN_INITIATE_3				29567
#define CN_INITIATE_4				29520

class AcherusSoulPrison : GameObjectAIScript
{
public:
	AcherusSoulPrison(GameObject* goinstance) : GameObjectAIScript(goinstance) {}
	static GameObjectAIScript* Create(GameObject* GO){return new AcherusSoulPrison(GO);}

	void OnActivate(Player* pPlayer)
	{
		QuestLogEntry* en = pPlayer->GetQuestLogForEntry(12848);
		if(!en)
			return;

		float SSX = pPlayer->GetPositionX();
		float SSY = pPlayer->GetPositionY();
		float SSZ = pPlayer->GetPositionZ();

		Creature* pCreature = pPlayer->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(SSX, SSY, SSZ);

		if(!pCreature || !pCreature->isAlive())
			return;

		if(pCreature->GetEntry() == CN_INITIATE_1 || pCreature->GetEntry() == CN_INITIATE_2 || pCreature->GetEntry() == CN_INITIATE_3 || pCreature->GetEntry() == CN_INITIATE_4)
		{
			pPlayer->SendChatMessage(CHAT_MSG_SAY, LANG_UNIVERSAL, "I give you the key to your salvation");
			pCreature->SetUInt64Value(UNIT_FIELD_FLAGS, 0);
			pCreature->GetAIInterface()->setNextTarget(pPlayer);
			pCreature->GetAIInterface()->AttackReaction(pPlayer, 1, 0);
			pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, "You have committed a big mistake, demon");

			if(en->GetMobCount(0) != 0)
				return;

			en->SetMobCount(0, 1);
			en->SendUpdateAddKill(0);
			en->UpdatePlayerFields();
		}
	}
};

class Salanar : public Arcemu::Gossip::Script
{
public:
	void OnHello(Object* pObject, Player * plr)
	{
		if(plr->GetQuestLogForEntry(12687))
			Arcemu::Gossip::Menu::SendQuickMenu(pObject->GetGUID(), 13355, plr, 0, Arcemu::Gossip::ICON_CHAT, "Salanar, I must return to the Realm of Shadows.");
	}

	void OnSelectOption(Object* pObject, Player* plr, uint32 Id, const char * Code)
    {
		TO_UNIT(pObject)->CastSpell(plr, 52693, false); // i am unsure if its not the: 52275 but i think no
    }
};

const char * DKInitiate_texts[]=
{
	{"Remember this day, $N, for it is the day that you will be thoroughly owned."},
	{"You have challenged death itself!"},
	{"Don't make me laugh."},
	{"Here come the tears..."},
	{"No potions!"},
	{"I'm going to tear your heart out, cupcake!"}
};

class DKInitiate : public GossipScript
{
public:
	void GossipHello(Object * pObject, Player * plr, bool AutoSend)
	{
		GossipMenu * Menu;
		if(plr->GetQuestLogForEntry(12733))
		{
			objmgr.CreateGossipMenuForPlayer(&Menu, pObject->GetGUID(), 13433, plr);
			Menu->AddItem(0, "I Challenge you, death knight!", 1);

			if( AutoSend )
				Menu->SendTo(plr);
		}
	}

	void GossipSelectOption(Object * pObject, Player * plr, uint32 Id, uint32 IntId, const char * Code)
	{
		Creature *  pCreature = pObject->GetTypeId() == TYPEID_UNIT ? TO_CREATURE(pObject) : NULL;

		if(pCreature!= NULL && Id == 1) // Attack
		{
			plr->Gossip_Complete();
			// At first change their orientation after gossip ends
			pCreature->SetFacing( plr->GetOrientation()+3.14f );

			// Spawn duel flag - taken from source from normal duel
			float dist = plr->CalcDistance(pCreature);
			dist = dist * 0.5f; //half way
			float x = (plr->GetPositionX() + pCreature->GetPositionX()*dist)/(1+dist) + cos(plr->GetOrientation()+(float(M_PI)/2))*2;
			float y = (plr->GetPositionY() + pCreature->GetPositionY()*dist)/(1+dist) + sin(plr->GetOrientation()+(float(M_PI)/2))*2;
			float z = (plr->GetPositionZ() + pCreature->GetPositionZ()*dist)/(1+dist);

			//Create flag/arbiter
			GameObject * pGameObj = plr->GetMapMgr()->CreateGameObject(194306);
			pGameObj->CreateFromProto(194306,plr->GetMapId(), x, y, z, plr->GetOrientation()+3.14f);
			pGameObj->SetInstanceID(plr->GetInstanceID());

			//Spawn the Flag
			pGameObj->SetUInt64Value(OBJECT_FIELD_CREATED_BY, plr->GetGUID());
			pGameObj->SetFaction(plr->GetFaction());
			pGameObj->SetLevel(plr->getLevel());
			pGameObj->PushToWorld(plr->GetMapMgr());

			plr->SetDuelArbiter(pGameObj->GetGUID()); // used later for removing flag ;)

				/*************************************/
				uint32 msgtype = CHAT_MSG_RAID_WARNING; // FIXME: This one is BAD! find a real type or packet
				/*************************************/

				pCreature->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, DKInitiate_texts[rand()%5]);
				WorldPacket * data, * data2, * data3, * data4;
				data = sChatHandler.FillMessageData( msgtype, LANG_UNIVERSAL,  "The duel will begin in...", plr->GetGUID(), 0 );
				data2 = sChatHandler.FillMessageData( msgtype, LANG_UNIVERSAL,  "3...", plr->GetGUID(), 0 );
				data3 = sChatHandler.FillMessageData( msgtype, LANG_UNIVERSAL,  "2...", plr->GetGUID(), 0 );
				data4 = sChatHandler.FillMessageData( msgtype, LANG_UNIVERSAL,  "1...", plr->GetGUID(), 0 );

				plr->SendPacket(data);
				sEventMgr.AddEvent(plr, &Player::SendPacket, data2, EVENT_PLAYER_SEND_PACKET, 1000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				sEventMgr.AddEvent(plr, &Player::SendPacket, data3, EVENT_PLAYER_SEND_PACKET, 2000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				sEventMgr.AddEvent(plr, &Player::SendPacket, data4, EVENT_PLAYER_SEND_PACKET, 3000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

				//sEventMgr.AddEvent(TO_UNIT(pCreature), &Unit::SendChatMessage, uint8(CHAT_MSG_MONSTER_SAY), uint32(LANG_UNIVERSAL), message, EVENT_UNIT_CHAT_MSG, 4000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				sEventMgr.AddEvent(TO_OBJECT(pCreature), &Object::SetUInt32Value, uint32(UNIT_FIELD_FACTIONTEMPLATE), uint32(14), EVENT_CREATURE_UPDATE, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT); 
				//sEventMgr.AddEvent(pCreature, &Creature::EventAttack, TO_UNIT(plr), EVENT_UNK, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		
		}
	}
};

class IntoTheRealmOfShadows : public QuestScript
{
public:
	void OnQuestComplete(Player *mTarget, QuestLogEntry *qLogEntry)
	{
		mTarget->PlaySound( 12985 );
	}
};

class ScourgeGryphonOne : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr)
	{
		if(plr->GetQuestLogForEntry(12670) || plr->HasFinishedQuest(12670))
			plr->TaxiStart(sTaxiMgr.GetTaxiPath(1053), 26308, 0);
	}
};

class ScourgeGryphonTwo : public GossipScript
{
public:
	void GossipHello(Object* pObject, Player* plr)
	{
		plr->TaxiStart(sTaxiMgr.GetTaxiPath(1054), 26308, 0);
	}
};

#define CN_INITIATE_1				29519
#define CN_INITIATE_2				29565
#define CN_INITIATE_3				29567
#define CN_INITIATE_4				29520

void SetupDeathKnight(ScriptMgr* mgr)
{
	//Gryphons
	mgr->register_gossip_script(29488, new ScourgeGryphonOne());
	mgr->register_gossip_script(29501, new ScourgeGryphonTwo());

	mgr->register_gameobject_script(191588, &AcherusSoulPrison::Create);
	mgr->register_gameobject_script(191577, &AcherusSoulPrison::Create);
	for(uint32 i = 191580; i<=191587; i++)
		mgr->register_gameobject_script(i, &AcherusSoulPrison::Create); 
	mgr->register_gameobject_script(191589, &AcherusSoulPrison::Create);
	mgr->register_gameobject_script(191590, &AcherusSoulPrison::Create);
	mgr->register_quest_script(12687, new IntoTheRealmOfShadows);
	mgr->register_quest_script(12593, new InServiceOfLichKing);
}
