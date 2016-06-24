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
#include "OGEProtocol.hpp"

void OGEProtocol::Connect(){
	WSADATA wsaData;
	Socket = INVALID_SOCKET;

	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		const char* msgnow = "Falló al intentar conectar con el Servidor. Error (WSAStartup): ";
		msgnow += iResult;
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);
		return;
	}

	// set address info
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("127.0.0.1", "7666", &hints, &result);

	if (iResult != 0)
	{
		WSACleanup();
		const char* msgnow = "El servidor no se encuentra Online, por favor intenta más tarde.";
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);
		//exit(1);
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		Socket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (Socket == INVALID_SOCKET) {
			WSACleanup();
			exit(1);
		}

		// Connect to server.
		iResult = connect(Socket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (iResult == SOCKET_ERROR)
		{
			const char* msgnow = "Socket Out. Invalid Operation.";
			MessageBoxA(NULL, msgnow, "Argentum Online", NULL);

			closesocket(Socket);
			Socket = INVALID_SOCKET;
			return;
		}
	}

	// no longer need address info for server
	freeaddrinfo(result);

	// if connection failed
	if (Socket == INVALID_SOCKET)
	{
		const char* msgnow = "Socket Out. Invalid Operation.";
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);
		WSACleanup();
		return;
	}

	// Set the mode of the socket to be nonblocking
	u_long iMode = 1;

	iResult = ioctlsocket(Socket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR)
	{
		const char* msgnow = "Socket Out. Invalid Operation.";
		MessageBoxA(NULL, msgnow, "Argentum Online", NULL);

		closesocket(Socket);
		WSACleanup();
		return;
	}

	//disable nagle
	char value = 1;
	setsockopt(Socket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}

int OGEProtocol::sendMessage(SOCKET curSocket, char * message, int messageSize){
	return send(curSocket, message, messageSize, 0);
}

int OGEProtocol::receiveMessage(SOCKET curSocket, char * buffer, int bufSize){
	return recv(curSocket, buffer, bufSize, 0);
}

void OGEProtocol::SocketReceive(){
	if (incomingData.length() <= 0){
		char* data = network_data;
		iResult = this->receiveMessage(Socket, data, 1000000);
		
		if (iResult <= 0)
			return;

		incomingData.WriteBlock(data, iResult);
		HandleIncomingData();
	}
}


void OGEProtocol::HandleIncomingData(){
	unsigned char m_Packet = incomingData.PeekByte();
	/*if ((int)m_Packet < 158)
		std::cout << (int)m_Packet << std::endl;*/

	switch (m_Packet){
		case ServerPacketID::Logged:                  // LOGGED
			HandleLogged();
			break;/*
		case ServerPacketID::RemoveDialogs:           // QTDL
			HandleRemoveDialogs();
			break;
		case ServerPacketID::RemoveCharDialog:        // QDL
			HandleRemoveCharDialog();
			break;
		case ServerPacketID::NavigateToggle:          // NAVEG
			HandleNavigateToggle();
			break;*/
		case ServerPacketID::Disconnect:              // FINOK
			HandleDisconnect();
			break;/*
		case ServerPacketID::CommerceEnd:             // FINCOMOK
			HandleCommerceEnd();
			break;
		case ServerPacketID::CommerceChat:
			HandleCommerceChat();
			break;
		case ServerPacketID::BankEnd:                 // FINBANOK
			HandleBankEnd();
			break;
		case ServerPacketID::CommerceInit:            // INITCOM
			HandleCommerceInit();
			break;
		case ServerPacketID::BankInit:                // INITBANCO
			HandleBankInit();
			break;
		case ServerPacketID::UserCommerceInit:        // INITCOMUSU
			HandleUserCommerceInit();
			break;
		case ServerPacketID::UserCommerceEnd:         // FINCOMUSUOK
			HandleUserCommerceEnd();
			break;
		case ServerPacketID::UserOfferConfirm:
			HandleUserOfferConfirm();
			break;
		case ServerPacketID::ShowBlacksmithForm:      // SFH
			HandleShowBlacksmithForm();
			break;
		case ServerPacketID::ShowCarpenterForm:       // SFC
			HandleShowCarpenterForm();
			break;*/
		case ServerPacketID::UpdateSta:               // ASS
			HandleUpdateSta();
			break;/*
		case ServerPacketID::UpdateMana:              // ASM
			HandleUpdateMana();
			break;
		case ServerPacketID::UpdateHP:                // ASH
			HandleUpdateHP();
			break;
		case ServerPacketID::UpdateGold:              // ASG
			HandleUpdateGold();
			break;
		case ServerPacketID::UpdateBankGold:
			HandleUpdateBankGold();
			break;
		case ServerPacketID::UpdateExp:               // ASE
			HandleUpdateExp();
			break;*/
		case ServerPacketID::ChangeMap:               // CM
			HandleChangeMap();
			break;
		case ServerPacketID::PosUpdate:               // PU
			HandlePosUpdate();
			break;
		case ServerPacketID::ChatOverHead:            // ||
			HandleChatOverHead();
			break;
		case ServerPacketID::ConsoleMsg:              // || - Beware!! its the same as above, but it was properly splitted
			HandleConsoleMessage();
			break;
		case ServerPacketID::GuildChat:               // |+
			HandleGuildChat();
			break;/*
		case ServerPacketID::ShowMessageBox:          // !!
			HandleShowMessageBox();
			break;*/
		case ServerPacketID::UserIndexInServer:       // IU
			HandleUserIndexInServer();
			break;
		case ServerPacketID::UserCharIndexInServer:   // IP
			HandleUserCharIndexInServer();
			break;
		case ServerPacketID::CharacterCreate:         // CC
			HandleCharacterCreate();
			break;/*
		case ServerPacketID::CharacterRemove:         // BP
			HandleCharacterRemove();
			break;
		case ServerPacketID::CharacterChangeNick:
			HandleCharacterChangeNick();
			break;*/
		case ServerPacketID::CharacterMove:           // MP, +, * and _ //
			HandleCharacterMove();
			break;/*
		case ServerPacketID::ForceCharMove:
			HandleForceCharMove();
			break;*/
		case ServerPacketID::CharacterChange:         // CP
			HandleCharacterChange();
			break;
		case ServerPacketID::ObjectCreate:            // HO
			HandleObjectCreate();
			break;/*
		case ServerPacketID::ObjectDelete:            // BO
			HandleObjectDelete();
			break;*/
		case ServerPacketID::BlockPosition:           // BQ
			HandleBlockPosition();
			break;
		case ServerPacketID::PlayMidi:                // TM
			HandlePlayMIDI();
			break;
		case ServerPacketID::PlayWave:                // TW
			HandlePlayWAV();
			break;/*
		case ServerPacketID::guildList:               // GL
			HandleGuildList();
			break;*/
		case ServerPacketID::AreaChanged:             // CA
			HandleAreaChanged();
			break;/*
		case ServerPacketID::PauseToggle:             // BKW
			HandlePauseToggle();
			break;
		case ServerPacketID::RainToggle:              // LLU
			HandleRainToggle();
			break;*/
		case ServerPacketID::CreateFX:                // CFX
			HandleCreateFX();
			break;
		case ServerPacketID::UpdateUserStats:         // EST
			HandleUpdateUserStats();
			break;/*
		case ServerPacketID::WorkRequestTarget:       // T01
			HandleWorkRequestTarget();
			break;*/
		case ServerPacketID::ChangeInventorySlot:     // CSI
			HandleChangeInventorySlot();
			break;/*
		case ServerPacketID::ChangeBankSlot:          // SBO
			HandleChangeBankSlot();
			break;*/
		case ServerPacketID::ChangeSpellSlot:         // SHS
			HandleChangeSpellSlot();
			break;/*
		case ServerPacketID::Atributes:               // ATR
			HandleAtributes();
			break;
		case ServerPacketID::BlacksmithWeapons:       // LAH
			HandleBlacksmithWeapons();
			break;
		case ServerPacketID::BlacksmithArmors:        // LAR
			HandleBlacksmithArmors();
			break;
		case ServerPacketID::CarpenterObjects:        // OBR
			HandleCarpenterObjects();
			break;
		case ServerPacketID::RestOK:                  // DOK
			HandleRestOK();
			break;*/
		case ServerPacketID::ErrorMsg:                // ERR
			HandleErrorMessage();
			break;/*
		case ServerPacketID::Blind:                   // CEGU
			HandleBlind();
			break;
		case ServerPacketID::Dumb:                    // DUMB
			HandleDumb();
			break;
		case ServerPacketID::ShowSignal:              // MCAR
			HandleShowSignal();
			break;
		case ServerPacketID::ChangeNPCInventorySlot:  // NPCI
			HandleChangeNPCInventorySlot();
			break;*/
		case ServerPacketID::UpdateHungerAndThirst:   // EHYS
			HandleUpdateHungerAndThirst();
			break;/*
		case ServerPacketID::Fame:                    // FAMA
			HandleFame();
			break;
		case ServerPacketID::MiniStats:               // MEST
			HandleMiniStats();
			break;*/
		case ServerPacketID::LevelUp:                 // SUNI
			HandleLevelUp();
			break;/*
		case ServerPacketID::AddForumMsg:             // FMSG
			HandleAddForumMessage();
			break;
		case ServerPacketID::ShowForumForm:           // MFOR
			HandleShowForumForm();
			break;*/
		case ServerPacketID::SetInvisible:            // NOVER
			HandleSetInvisible();
			break;
		case ServerPacketID::DiceRoll:                // DADOS
			HandleDiceRoll();
			break;/*
		case ServerPacketID::MeditateToggle:          // MEDOK
			HandleMeditateToggle();
			break;
		case ServerPacketID::BlindNoMore:             // NSEGUE
			HandleBlindNoMore();
			break;
		case ServerPacketID::DumbNoMore:              // NESTUP
			HandleDumbNoMore();
			break;*/
		case ServerPacketID::SendSkills:              // SKILLS
			HandleSendSkills();
			break;/*
		case ServerPacketID::TrainerCreatureList:     // LSTCRI
			HandleTrainerCreatureList();
			break;
		case ServerPacketID::guildNews:               // GUILDNE
			HandleGuildNews();
			break;
		case ServerPacketID::OfferDetails:            // PEACEDE and ALLIEDE
			HandleOfferDetails();
			break;
		case ServerPacketID::AlianceProposalsList:    // ALLIEPR
			HandleAlianceProposalsList();
			break;
		case ServerPacketID::PeaceProposalsList:      // PEACEPR
			HandlePeaceProposalsList();
			break;
		case ServerPacketID::CharacterInfo:           // CHRINFO
			HandleCharacterInfo();
			break;
		case ServerPacketID::GuildLeaderInfo:         // LEADERI
			HandleGuildLeaderInfo();
			break;
		case ServerPacketID::GuildDetails:            // CLANDET
			HandleGuildDetails();
			break;
		case ServerPacketID::ShowGuildFundationForm:  // SHOWFUN
			HandleShowGuildFundationForm();
			break;
		case ServerPacketID::ParalizeOK:              // PARADOK
			HandleParalizeOK();
			break;
		case ServerPacketID::ShowUserRequest:         // PETICIO
			HandleShowUserRequest();
			break;
		case ServerPacketID::TradeOK:                 // TRANSOK
			HandleTradeOK();
			break;
		case ServerPacketID::BankOK:                  // BANCOOK
			HandleBankOK();
			break;
		case ServerPacketID::ChangeUserTradeSlot:     // COMUSUINV
			HandleChangeUserTradeSlot();
			break;
		case ServerPacketID::SendNight:               // NOC
			HandleSendNight();
			break;
		case ServerPacketID::Pong:
			HandlePong();
			break;
		case ServerPacketID::UpdateTagAndStatus:
			HandleUpdateTagAndStatus();
			break;
		case ServerPacketID::GuildMemberInfo:
			HandleGuildMemberInfo();
			break;
			//*******************
			//GM messages
			//*******************
		case ServerPacketID::SpawnList:               // SPL
			HandleSpawnList();
			break;
		case ServerPacketID::ShowSOSForm:             // RSOS and MSOS
			HandleShowSOSForm();
			break;
		case ServerPacketID::ShowDenounces:
			HandleShowDenounces();
			break;
		case ServerPacketID::RecordDetails:
			HandleRecordDetails();
			break;
		case ServerPacketID::RecordList:
			HandleRecordList();
			break;
		case ServerPacketID::ShowMOTDEditionForm:     // ZMOTD
			HandleShowMOTDEditionForm();
			break;
		case ServerPacketID::ShowGMPanelForm:         // ABPANEL
			HandleShowGMPanelForm();
			break;
		case ServerPacketID::UserNameList:            // LISTUSU
			HandleUserNameList();
			break;
		case ServerPacketID::ShowGuildAlign:
			HandleShowGuildAlign();
			break;
		case ServerPacketID::ShowPartyForm:
			HandleShowPartyForm();
			break;*/
		case ServerPacketID::UpdateStrenghtAndDexterity:
			HandleUpdateStrenghtAndDexterity();
			break;/*
		case ServerPacketID::UpdateStrenght:
			HandleUpdateStrenght();
			break;
		case ServerPacketID::UpdateDexterity:
			HandleUpdateDexterity();
			break;
		case ServerPacketID::AddSlots:
			HandleAddSlots();
			break;*/
		case ServerPacketID::MultiMessage:
			HandleMultiMessage();
			break;/*
		case ServerPacketID::StopWorking:
			HandleStopWorking();
			break;
		case ServerPacketID::CancelOfferItem:
			HandleCancelOfferItem();
			break;*/
	}

	if (incomingData.length() > 0)
		HandleIncomingData();
}
void OGEProtocol::HandleLogged() {
	incomingData.ReadByte();
	char m_UserClass = incomingData.ReadByte();
	m_Game->SetUserClass(m_UserClass);
	m_Game->SetConnected(true);
	m_Game->GetForms()->FConnect_Visible(false);
	m_Game->GetForms()->FCreateCharacter_Visible(false);
	m_Game->GetForms()->FMain_Visible(true);
	//Aca es donde creas todo el openform, close form, etc.
}

void OGEProtocol::HandleDisconnect() {
	incomingData.ReadByte();
	m_Game->ResetAllInfo();
}

void OGEProtocol::HandleUpdateSta() {
	incomingData.ReadByte();
	incomingData.ReadInteger(); //UpdateStamina UserMinSta = ;
}

void OGEProtocol::HandleChangeMap() {
	incomingData.ReadByte();

	short m_UserMap = incomingData.ReadInteger();
	incomingData.ReadInteger();

	m_Game->LoadMap(m_UserMap);
}

void OGEProtocol::HandlePosUpdate() {
	incomingData.ReadByte();

	char m_PosX = incomingData.ReadByte();
	char m_PosY = incomingData.ReadByte();

	if (m_Game->GetWorld()[m_Game->GetUserPosX()][m_Game->GetUserPosY()]->isCharIndex() == m_Game->GetUserCharIndex()) {
		m_Game->GetWorld()[m_Game->GetUserPosX()][m_Game->GetUserPosY()]->setCharIndex(0);
	}

	m_Game->SetUserPosition(m_PosX, m_PosY);
	m_Game->GetWorld()[m_PosX][m_PosY]->setCharIndex(m_Game->GetUserCharIndex());
	m_Game->GetUser(m_Game->GetUserCharIndex())->SetPosition(m_PosX, m_PosY);
}

void OGEProtocol::HandleChatOverHead() {
	incomingData.ReadByte();

	std::string m_Message = incomingData.ReadUnicodeString();
	short m_CharIndex = incomingData.ReadInteger();

	unsigned char m_R = incomingData.ReadByte();
	unsigned char m_G = incomingData.ReadByte();
	unsigned char m_B = incomingData.ReadByte();

	m_Game->GetUser(m_CharIndex)->SetDialog(m_Message, (int)D3DCOLOR_ARGB(255, m_R, m_G, m_B), 1, 10, 0.0f);
}

void OGEProtocol::HandleConsoleMessage() {
	incomingData.ReadByte();
	std::string m_Message = incomingData.ReadUnicodeString();
	char m_Font = incomingData.ReadByte();
	CFONT m_FontType = m_Game->GetData()->m_FontTypes[m_Font];
	m_Game->GetForms()->FMain_AddItem_Console(m_Message, m_FontType.m_Color, m_FontType.m_Bold, m_FontType.m_Italic);
}

void OGEProtocol::HandleGuildChat() {
	incomingData.ReadByte();

	std::string m_Message = incomingData.ReadUnicodeString();
	CFONT m_FontType = m_Game->GetData()->m_FontTypes[10];
	m_Game->GetForms()->FMain_AddItem_Console(m_Message, m_FontType.m_Color, m_FontType.m_Bold, m_FontType.m_Italic);
}

void OGEProtocol::HandleUserIndexInServer() {
	incomingData.ReadByte();
	short m_UserIndex = incomingData.ReadInteger();
}

void OGEProtocol::HandleUserCharIndexInServer() {
	incomingData.ReadByte();
	short m_UserCharIndex = incomingData.ReadInteger();
	m_Game->SetUserCharIndex(m_UserCharIndex);
	m_Game->SetUserPosition(m_Game->GetUser(m_UserCharIndex)->GetPosX(), m_Game->GetUser(m_UserCharIndex)->GetPosY());

	//Actualizar bTecho;
}

void OGEProtocol::HandleCharacterCreate() {
	incomingData.ReadByte();

	short m_CharIndex = incomingData.ReadInteger();
	short m_Body = incomingData.ReadInteger();
	short m_Head = incomingData.ReadInteger();
	char m_Heading = incomingData.ReadByte();
	char m_PosX = incomingData.ReadByte();
	char m_PosY = incomingData.ReadByte();
	short m_Weapon = incomingData.ReadInteger();
	short m_Shield = incomingData.ReadInteger();
	short m_Helmet = incomingData.ReadInteger();

	//SetCharFX
	incomingData.ReadInteger(); incomingData.ReadInteger();
	//SetCharFX
	std::string m_Name = incomingData.ReadUnicodeString();
	char m_Color = incomingData.ReadByte();
	char m_Priv = incomingData.ReadByte();

	m_Game->CreateUser(m_CharIndex, m_Name, m_Heading, m_PosX, m_PosY, m_Body, m_Head, m_Helmet, m_Weapon, m_Shield);
}

void OGEProtocol::HandleCharacterMove() {
	incomingData.ReadByte();

	short m_CharIndex = incomingData.ReadInteger();
	char m_X = incomingData.ReadByte();
	char m_Y = incomingData.ReadByte();

	//IF MEDITANDO, IF PARA DOPASOSFX, TERMINAR DE REVISAR Y HACER!
	if (m_Game->GetUser(m_CharIndex)->GetFXIndex() >= 40 && m_Game->GetUser(m_CharIndex)->GetFXIndex() <= 49)
		m_Game->GetUser(m_CharIndex)->SetFXIndex(0);

	m_Game->DoPasosFX(m_CharIndex);
	m_Game->MoveCharByPos(m_CharIndex, m_X, m_Y);
	m_Game->RefreshAllChars();
}

void OGEProtocol::HandleCharacterChange() {
	incomingData.ReadByte();
	
	short m_CharIndex = incomingData.ReadInteger();
	OGEUser *m_User = m_Game->GetUser(m_CharIndex);
	BODYDATA *m_Bodys = m_Game->GetData()->m_BodyData;
	HEADDATA *m_Heads = m_Game->GetData()->m_HeadData;
	
	short m_Temp = incomingData.ReadInteger();
	short m_HeadIndex = incomingData.ReadInteger();

	if (m_Temp < 1 || m_Temp > m_Game->GetDeclares()->GetNumBodys()) {
		m_User->SetBody(m_Bodys[0]);
	}
	else {
		m_User->SetBody(m_Bodys[m_Temp]);
	}

	if (m_HeadIndex < 1 || m_HeadIndex > m_Game->GetDeclares()->GetNumHeads()) {
		m_User->SetHead(m_Heads[0]);
	}
	else {
		m_User->SetHead(m_Heads[m_HeadIndex]);
	}

	//SetMuerto->((HeadIndex == CASPER_HEAD));

	char m_Heading = incomingData.ReadByte();
	m_User->SetHeading(m_Heading);

	//TEMP:
	m_Temp = incomingData.ReadInteger();
	if (m_Temp < 1 || m_Temp == 2 || m_Temp > m_Game->GetDeclares()->GetNumWeapons()) {
		m_User->SetWeapon(m_Game->GetData()->m_WeaponData[0]);
	}
	else {
		m_User->SetWeapon(m_Game->GetData()->m_WeaponData[m_Temp]);
	}

	m_Temp = incomingData.ReadInteger();
	if (m_Temp < 1 || m_Temp == 2 || m_Temp > m_Game->GetDeclares()->GetNumShields()) {
		m_User->SetShield(m_Game->GetData()->m_ShieldData[0]);
	}
	else {
		m_User->SetShield(m_Game->GetData()->m_ShieldData[m_Temp]);
	}

	m_Temp = incomingData.ReadInteger();
	if (m_Temp < 1 || m_Temp == 2 || m_Temp > m_Game->GetDeclares()->GetNumHelmets()) {
		m_User->SetHelmet(m_Game->GetData()->m_HelmetData[0]);
	}
	else {
		m_User->SetHelmet(m_Game->GetData()->m_HelmetData[m_Temp]);
	}

	//SetCharFX
	incomingData.ReadInteger(); //Todavia hay que ver bien cómo hacerlo de la mejor forma.
	incomingData.ReadInteger();
	//SetCharFX

	m_Game->RefreshAllChars();
}

void OGEProtocol::HandleObjectCreate() {
	incomingData.ReadByte();
	char m_PosX = incomingData.ReadByte();
	char m_PosY = incomingData.ReadByte();
	short m_GrhIndex = incomingData.ReadInteger();

	m_Game->GetWorld()[m_PosX][m_PosY]->setObjGrh(m_GrhIndex);
	m_Game->InitGrh(m_Game->GetWorld()[m_PosX][m_PosY]->isObjGrh(), m_GrhIndex, false);
}

void OGEProtocol::HandleBlockPosition() {
	incomingData.ReadByte();
	char m_PosX = incomingData.ReadByte();
	char m_PosY = incomingData.ReadByte();
	bool m_Blocked = incomingData.ReadBoolean();

	m_Game->GetWorld()[m_PosX][m_PosY]->setBlocked(m_Blocked);
}

void OGEProtocol::HandlePlayMIDI() {
	incomingData.ReadByte();
	short m_Midi = incomingData.ReadInteger();
	short m_Loops = incomingData.ReadInteger();

	std::stringstream m_sMidi;
	m_sMidi << m_Midi << ".ogg";

	m_Game->GetAudio()->PlayMIDI(m_sMidi.str());
}

void OGEProtocol::HandlePlayWAV() {
	incomingData.ReadByte();
	unsigned char m_Wav = incomingData.ReadByte();
	char m_X = incomingData.ReadByte();
	char m_Y = incomingData.ReadByte();

	std::stringstream m_sWav;
	m_sWav << (int)m_Wav << ".wav";

	m_Game->GetAudio()->PlayWAV(m_sWav.str());
}

void OGEProtocol::HandleAreaChanged() {
	incomingData.ReadByte();
	char m_PosX = incomingData.ReadByte();
	char m_PosY = incomingData.ReadByte();

	m_Game->ChangeArea(m_PosX, m_PosY);
}

void OGEProtocol::HandleCreateFX() {
	incomingData.ReadByte();

	short m_CharIndex = incomingData.ReadInteger();
	short m_FX = incomingData.ReadInteger();
	short m_Loops = incomingData.ReadInteger();

	//m_Game->GetUser(m_CharIndex)->SetFX(); hay que verlo bien en el código de ao vb6.
}

void OGEProtocol::HandleUpdateUserStats() {
	incomingData.ReadByte();

	incomingData.ReadInteger();
	incomingData.ReadInteger();
	incomingData.ReadInteger();
	incomingData.ReadInteger();
	incomingData.ReadInteger();
	incomingData.ReadInteger();

	incomingData.ReadLong();

	incomingData.ReadByte();

	incomingData.ReadLong();
	incomingData.ReadLong();
}

void OGEProtocol::HandleChangeInventorySlot() {
	incomingData.ReadByte();

	unsigned char slot = incomingData.ReadByte();
	short OBJIndex = incomingData.ReadInteger();
	std::string name = incomingData.ReadUnicodeString();
	
	short amount = incomingData.ReadInteger();
	bool equipped = incomingData.ReadBoolean();
	short grhIndex = incomingData.ReadInteger();
	unsigned char objtype = incomingData.ReadByte();
	short maxhit = incomingData.ReadInteger();
	short minhit = incomingData.ReadInteger();
	short maxdef = incomingData.ReadInteger();
	short mindef = incomingData.ReadInteger();
	float value = incomingData.ReadSingle();

	//std::cout << "Valor: " << value << std::endl;
	//m_Game->CharInventory.SetItem(slot, OBJIndex, amount, equipped, grhIndex, objtype, maxhit, minhit, maxdef, mindef, value, name);
}

void OGEProtocol::HandleChangeSpellSlot() {
	incomingData.ReadByte();

	unsigned char m_Slot = incomingData.ReadByte();
	short m_SpellIndex = incomingData.ReadInteger();
	//m_Game->SetUserSpells(m_Slot, m_SpellIndex);

	std::string m_SpellName = incomingData.ReadUnicodeString();
	//m_GUI->AddItem(m_SpellName);
}

void OGEProtocol::HandleErrorMessage() {
	incomingData.ReadByte();
	std::string m_Message = incomingData.ReadUnicodeString();
	MessageBoxA(NULL, m_Message.c_str(), "Argentum Online", NULL);
}

void OGEProtocol::HandleUpdateHungerAndThirst() {
	incomingData.ReadByte();

	incomingData.ReadByte();
	incomingData.ReadByte();
	incomingData.ReadByte();
	incomingData.ReadByte();
}

void OGEProtocol::HandleLevelUp() {
	incomingData.ReadByte();
	int m_SkillPoints = incomingData.ReadInteger(); // skills = skills + new_skills
}

void OGEProtocol::HandleSetInvisible() {
	incomingData.ReadByte();
	short m_CharIndex = incomingData.ReadInteger();
	bool m_Invisible = incomingData.ReadBoolean();
	m_Game->GetUser(m_CharIndex)->SetInvisible(m_Invisible);
}

void OGEProtocol::HandleDiceRoll() {
	incomingData.ReadByte();
	m_Game->GetForms()->FConnect_Visible(false);
	m_Game->GetForms()->FMain_Visible(false);
	m_Game->GetForms()->FCreateCharacter_Visible(true);
	m_Game->GetForms()->FCreateCharacter_setAttributes(incomingData.ReadByte(), incomingData.ReadByte(),
													   incomingData.ReadByte(), incomingData.ReadByte(), incomingData.ReadByte());

}

void OGEProtocol::HandleSendSkills() {
	incomingData.ReadByte();
	int NumSkills = m_Game->GetDeclares()->GetNumSkills();

	for (int i = 1; i <= NumSkills; ++i) {
		incomingData.ReadByte(); //Falta aplicar
		incomingData.ReadByte(); //Falta aplicar
	}

	m_Game->GetDeclares()->SetGettedSkills(true);
}

void OGEProtocol::HandleUpdateStrenghtAndDexterity() {
	incomingData.ReadByte();

	incomingData.ReadByte();
	incomingData.ReadByte();
}

void OGEProtocol::HandleMultiMessage() {
	incomingData.ReadByte();
	incomingData.ReadByte();
}

void OGEProtocol::WriteLoginExistingChar(const char* m_Name, const char* m_Password){
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_LoginExistingChar);
	outgoingData.WriteUnicodeString(m_Name);
	outgoingData.WriteUnicodeString(m_Password);
	outgoingData.WriteByte(0);
	outgoingData.WriteByte(13);
	outgoingData.WriteByte(0);
}

void OGEProtocol::WriteThrowDices() {
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_ThrowDices);
}

void OGEProtocol::WriteLoginNewChar(const char* m_Name, const char* m_Password, char m_Raza,
	char m_Genero, char m_Class, short m_Head, const char* m_EMail, char m_City){
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_LoginNewChar);
	outgoingData.WriteUnicodeString(m_Name);
	outgoingData.WriteUnicodeString(m_Password);
	outgoingData.WriteByte(0);
	outgoingData.WriteByte(13);
	outgoingData.WriteByte(0);
	outgoingData.WriteByte(m_Raza);
	outgoingData.WriteByte(m_Genero);
	outgoingData.WriteByte(m_Class);
	outgoingData.WriteInteger(m_Head);
	outgoingData.WriteUnicodeString(m_EMail);
	outgoingData.WriteByte(m_City);
}

void OGEProtocol::WriteWalk(char m_Heading) {
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_Walk);
	outgoingData.WriteByte(m_Heading);
}

void OGEProtocol::WriteAttack(){
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_Attack);
}

void OGEProtocol::WriteLeftClick(unsigned char m_X, unsigned char m_Y) {
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_LeftClick);
	outgoingData.WriteByte(m_X);
	outgoingData.WriteByte(m_Y);
}

void OGEProtocol::WriteRightClick(unsigned char m_X, unsigned char m_Y) {
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_RightClick);
	outgoingData.WriteByte(m_X);
	outgoingData.WriteByte(m_Y);
}

void OGEProtocol::WriteChangeHeading(char m_Heading) {
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_ChangeHeading);
	outgoingData.WriteByte(m_Heading);
}

void OGEProtocol::WriteTalk(std::string m_Message) {
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_Talk);
	outgoingData.WriteUnicodeString(m_Message);
}

void OGEProtocol::WriteQuit(){
	outgoingData.WriteByte(ClientPacketID::ClientPacketID_Quit);
}

void OGEProtocol::ParseUserCommand(std::string m_RawCommand) {
	WriteTalk(m_RawCommand);
}

void OGEProtocol::FlushBuffer(){
	int sizebuff = outgoingData.length();
	if (sizebuff <= 0)
		return;

	std::string sndData = outgoingData.ReadBinaryFixed(sizebuff);
	char* sndmsg = new char[sizebuff];
	memcpy(sndmsg, sndData.c_str(), sizebuff);
	sendMessage(Socket, sndmsg, sizebuff);
	delete sndmsg;
}