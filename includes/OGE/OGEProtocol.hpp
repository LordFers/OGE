/*****************************************************************************
*   Open-source Game Engine (OGE) 0.1.0 programmed in C++
******************************************************************************
*   Copyright (C) 2016 - Fernando Alan Quinteros, 10th Dec 2015.
*   http://email:lordfers@gmail.com
******************************************************************************
*   This program is open-source and free software.
*   OGE used the standard libraries CEGUI 8.4.x and DirectX 9.
*   https://github.com/LordFers/OGE.git
*****************************************************************************/
#pragma once
#include "OGEByteQueue.hpp"
#include "OGEGame.hpp"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

enum ServerPacketID {
	Logged,
	RemoveDialogs,
	RemoveCharDialog,
	NavigateToggle,
	Disconnect,
	CommerceEnd,
	BankEnd,
	CommerceInit,
	BankInit,
	UserCommerceInit,
	UserCommerceEnd,
	UserOfferConfirm,
	CommerceChat,
	ShowBlacksmithForm,
	ShowCarpenterForm,
	UpdateSta,
	UpdateMana,
	UpdateHP,
	UpdateGold,
	UpdateBankGold,
	UpdateExp,
	ChangeMap,
	PosUpdate,
	ChatOverHead,
	ConsoleMsg,
	GuildChat,
	ShowMessageBox,
	UserIndexInServer,
	UserCharIndexInServer,
	CharacterCreate,
	CharacterRemove,
	CharacterChangeNick,
	CharacterMove,
	ForceCharMove,
	CharacterChange,
	ObjectCreate,
	ObjectDelete,
	BlockPosition,
	PlayMidi,
	PlayWave,
	guildList,
	AreaChanged,
	PauseToggle,
	RainToggle,
	CreateFX,
	UpdateUserStats,
	WorkRequestTarget,
	ChangeInventorySlot,
	ChangeBankSlot,
	ChangeSpellSlot,
	Atributes,
	BlacksmithWeapons,
	BlacksmithArmors,
	CarpenterObjects,
	RestOK,
	ErrorMsg,
	Blind,
	Dumb,
	ShowSignal,
	ChangeNPCInventorySlot,
	UpdateHungerAndThirst,
	Fame,
	MiniStats,
	LevelUp,
	AddForumMsg,
	ShowForumForm,
	SetInvisible,
	DiceRoll,
	MeditateToggle,
	BlindNoMore,
	DumbNoMore,
	SendSkills,
	TrainerCreatureList,
	guildNews,
	OfferDetails,
	AlianceProposalsList,
	PeaceProposalsList,
	CharacterInfo,
	GuildLeaderInfo,
	GuildMemberInfo,
	GuildDetails,
	ShowGuildFundationForm,
	ParalizeOK,
	ShowUserRequest,
	TradeOK,
	BankOK,
	ChangeUserTradeSlot,
	SendNight,
	Pong,
	UpdateTagAndStatus,
	SpawnList,
	ShowSOSForm,
	ShowMOTDEditionForm,
	ShowGMPanelForm,
	UserNameList,
	ShowDenounces,
	RecordList,
	RecordDetails,
	ShowGuildAlign,
	ShowPartyForm,
	UpdateStrenghtAndDexterity,
	UpdateStrenght,
	UpdateDexterity,
	AddSlots,
	MultiMessage,
	StopWorking,
	CancelOfferItem
};

enum ClientPacketID {
	ClientPacketID_LoginExistingChar,
	ClientPacketID_ThrowDices,
	ClientPacketID_LoginNewChar,
	ClientPacketID_Talk,
	ClientPacketID_Yell,
	ClientPacketID_Whisper,
	ClientPacketID_Walk,
	ClientPacketID_RequestPositionUpdate,
	ClientPacketID_Attack,
	ClientPacketID_PickUp,
	ClientPacketID_SafeToggle,
	ClientPacketID_ResuscitationSafeToggle,
	ClientPacketID_RequestGuildLeaderInfo,
	ClientPacketID_RequestAtributes,
	ClientPacketID_RequestFame,
	ClientPacketID_RequestSkills,
	ClientPacketID_RequestMiniStats,
	ClientPacketID_CommerceEnd,
	ClientPacketID_UserCommerceEnd,
	ClientPacketID_UserCommerceConfirm,
	ClientPacketID_CommerceChat,
	ClientPacketID_BankEnd,
	ClientPacketID_UserCommerceOk,
	ClientPacketID_UserCommerceReject,
	ClientPacketID_Drop,
	ClientPacketID_CastSpell,
	ClientPacketID_LeftClick,
	ClientPacketID_RightClick,
	ClientPacketID_Work,
	ClientPacketID_UseSpellMacro,
	ClientPacketID_UseItem,
	ClientPacketID_CraftBlacksmith,
	ClientPacketID_CraftCarpenter,
	ClientPacketID_WorkLeftClick,
	ClientPacketID_CreateNewGuild,
	ClientPacketID_SpellInfo,
	ClientPacketID_EquipItem,
	ClientPacketID_ChangeHeading,
	ClientPacketID_ModifySkills,
	ClientPacketID_Train,
	ClientPacketID_CommerceBuy,
	ClientPacketID_BankExtractItem,
	ClientPacketID_CommerceSell,
	ClientPacketID_BankDeposit,
	ClientPacketID_ForumPost,
	ClientPacketID_MoveSpell,
	ClientPacketID_MoveBank,
	ClientPacketID_ClanCodexUpdate,
	ClientPacketID_UserCommerceOffer,
	ClientPacketID_GuildAcceptPeace,
	ClientPacketID_GuildRejectAlliance,
	ClientPacketID_GuildRejectPeace,
	ClientPacketID_GuildAcceptAlliance,
	ClientPacketID_GuildOfferPeace,
	ClientPacketID_GuildOfferAlliance,
	ClientPacketID_GuildAllianceDetails,
	ClientPacketID_GuildPeaceDetails,
	ClientPacketID_GuildRequestJoinerInfo,
	ClientPacketID_GuildAlliancePropList,
	ClientPacketID_GuildPeacePropList,
	ClientPacketID_GuildDeclareWar,
	ClientPacketID_GuildNewWebsite,
	ClientPacketID_GuildAcceptNewMember,
	ClientPacketID_GuildRejectNewMember,
	ClientPacketID_GuildKickMember,
	ClientPacketID_GuildUpdateNews,
	ClientPacketID_GuildMemberInfo,
	ClientPacketID_GuildOpenElections,
	ClientPacketID_GuildRequestMembership,
	ClientPacketID_GuildRequestDetails,
	ClientPacketID_Online,
	ClientPacketID_Quit,
	ClientPacketID_GuildLeave,
	ClientPacketID_RequestAccountState,
	ClientPacketID_PetStand,
	ClientPacketID_PetFollow,
	ClientPacketID_ReleasePet,
	ClientPacketID_TrainList,
	ClientPacketID_Rest,
	ClientPacketID_Meditate,
	ClientPacketID_Resucitate,
	ClientPacketID_Heal,
	ClientPacketID_Help,
	ClientPacketID_RequestStats,
	ClientPacketID_CommerceStart,
	ClientPacketID_BankStart,
	ClientPacketID_Enlist,
	ClientPacketID_Information,
	ClientPacketID_Reward,
	ClientPacketID_RequestMOTD,
	ClientPacketID_UpTime,
	ClientPacketID_PartyLeave,
	ClientPacketID_PartyCreate,
	ClientPacketID_PartyJoin,
	ClientPacketID_Inquiry,
	ClientPacketID_GuildMessage,
	ClientPacketID_PartyMessage,
	ClientPacketID_CentinelReport,
	ClientPacketID_GuildOnline,
	ClientPacketID_PartyOnline,
	ClientPacketID_CouncilMessage,
	ClientPacketID_RoleMasterRequest,
	ClientPacketID_GMRequest,
	ClientPacketID_bugReport,
	ClientPacketID_ChangeDescription,
	ClientPacketID_GuildVote,
	ClientPacketID_Punishments,
	ClientPacketID_ChangePassword,
	ClientPacketID_Gamble,
	ClientPacketID_InquiryVote,
	ClientPacketID_LeaveFaction,
	ClientPacketID_BankExtractGold,
	ClientPacketID_BankDepositGold,
	ClientPacketID_Denounce,
	ClientPacketID_GuildFundate,
	ClientPacketID_GuildFundation,
	ClientPacketID_PartyKick,
	ClientPacketID_PartySetLeader,
	ClientPacketID_PartyAcceptMember,
	ClientPacketID_Ping,
	ClientPacketID_RequestPartyForm,
	ClientPacketID_ItemUpgrade,
	ClientPacketID_GMCommands,
	ClientPacketID_InitCrafting,
	ClientPacketID_Home,
	ClientPacketID_ShowGuildNews,
	ClientPacketID_ShareNpc,
	ClientPacketID_StopSharingNpc,
	ClientPacketID_Consultation,
	ClientPacketID_moveItem,

	LAST_CLIENT_PACKET_ID
};

class OGEGame;

class OGEProtocol {
	public:
		OGEProtocol::OGEProtocol(OGEGame *m_Game) { this->m_Game = m_Game; }

	public:
		void OGEProtocol::Connect();
		void OGEProtocol::SocketReceive();

	public:
		static int OGEProtocol::sendMessage(SOCKET curSocket, char * message, int messageSize);
		static int OGEProtocol::receiveMessage(SOCKET curSocket, char * buffer, int bufSize);

	public:
		void OGEProtocol::HandleLogged();
		void OGEProtocol::HandleDisconnect();
		void OGEProtocol::HandleUpdateSta();
		void OGEProtocol::HandleChangeMap();
		void OGEProtocol::HandlePosUpdate();
		void OGEProtocol::HandleChatOverHead();
		void OGEProtocol::HandleConsoleMessage();
		void OGEProtocol::HandleGuildChat();
		void OGEProtocol::HandleUserIndexInServer();
		void OGEProtocol::HandleUserCharIndexInServer();
		void OGEProtocol::HandleCharacterCreate();
		void OGEProtocol::HandleCharacterMove();
		void OGEProtocol::HandleCharacterChange();
		void OGEProtocol::HandleObjectCreate();
		void OGEProtocol::HandleBlockPosition();
		void OGEProtocol::HandlePlayMIDI();
		void OGEProtocol::HandlePlayWAV();
		void OGEProtocol::HandleAreaChanged();
		void OGEProtocol::HandleCreateFX();
		void OGEProtocol::HandleUpdateUserStats();
		void OGEProtocol::HandleChangeInventorySlot();
		void OGEProtocol::HandleChangeSpellSlot();
		void OGEProtocol::HandleErrorMessage();
		void OGEProtocol::HandleUpdateHungerAndThirst();
		void OGEProtocol::HandleLevelUp();
		void OGEProtocol::HandleSetInvisible();
		void OGEProtocol::HandleDiceRoll();
		void OGEProtocol::HandleSendSkills();
		void OGEProtocol::HandleUpdateStrenghtAndDexterity();
		void OGEProtocol::HandleMultiMessage();

	public:
		void OGEProtocol::HandleIncomingData();
		void OGEProtocol::FlushBuffer();
		void OGEProtocol::ParseUserCommand(std::string m_RawCommand);

	public:
		void OGEProtocol::WriteLoginExistingChar(const char* m_Name, const char* m_Password);
		void OGEProtocol::WriteThrowDices();
		void OGEProtocol::WriteLoginNewChar(const char* m_Name, const char* m_Password, char m_Raza,
											char m_Genero, char m_Class, short m_Head, const char* m_EMail, char m_City);
		void OGEProtocol::WriteWalk(char m_Heading);
		void OGEProtocol::WriteAttack();
		void OGEProtocol::WriteLeftClick(unsigned char m_X, unsigned char m_Y);
		void OGEProtocol::WriteRightClick(unsigned char m_X, unsigned char m_Y);
		void OGEProtocol::WriteChangeHeading(char m_Heading);
		void OGEProtocol::WriteTalk(std::string m_Message);
		void OGEProtocol::WriteQuit();

	private:
		OGEGame *m_Game;
		OGEByteQueue incomingData;
		OGEByteQueue outgoingData;
		SOCKET Socket;
		char network_data[1000000];
		int iResult;
		
};