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
#include "OGEGame.hpp"

using namespace std;

OGEGame::OGEGame(OGEEngine *m_Engine){
	this->m_World = new OGEWorld**[101]();

	for (int i = 0; i <= 100; ++i) {
		this->m_World[i] = new OGEWorld*[101]();
		for (int j = 0; j <= 100; ++j) {
			this->m_World[i][j] = new OGEWorld();
		}
	}

	this->m_Declares = new OGEDeclares();
	this->m_Data = new OGEData(m_Declares);
	this->m_Audio = new OGEAudio();
	this->m_Engine = m_Engine;

	m_User = new OGEUser*[10001];
	for (int i = 0; i <= 10000; ++i)
		m_User[i] = new OGEUser(0, "", 0, 0, m_Data->m_BodyData[0], m_Data->m_HeadData[0], m_Data->m_HelmetData[0], m_Data->m_WeaponData[0], m_Data->m_ShieldData[0]);

	SetLastChar(0);
	SetNumChars(0);

	//Protecteds:
	m_Connected = false;
	m_UserParalizado = false;
	m_UserDescansar = false;
	m_UserMeditar = false;
	m_UserNavegando = false;
}

void OGEGame::LoadMap(int m_Map) {
	char cabecera[263];

	stringstream filename;
	filename << "resources/maps/mapa" << m_Map << ".map";

	string strfile = filename.str();
	const char* _file = strfile.c_str();

	ifstream file(_file, ios::in | ios::binary | ios::ate);
	if (!file.is_open()) {
		MessageBox(NULL, L"Error loading a Map in LoadMap.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short mapversion = 0;
	short tempint = 0;

	unsigned char byflags = 0;

	file.seekg(0, ios::beg);
	file.read((char *)&mapversion, sizeof(mapversion));
	file.read((char *)&cabecera, sizeof(cabecera));

	file.read((char *)&tempint, sizeof(tempint));
	file.read((char *)&tempint, sizeof(tempint));
	file.read((char *)&tempint, sizeof(tempint));
	file.read((char *)&tempint, sizeof(tempint));

	GRH temp;

	for (short y = 1; y <= 100; y++) {
		for (short x = 1; x <= 100; x++) {
			file.read((char *)&byflags, sizeof(byflags));
			m_World[x][y]->setBlocked(byflags & 1);

			file.read((char *)&tempint, sizeof(tempint));
			temp.grhIndex = tempint;
			InitGrh(temp, tempint, true);
			m_World[x][y]->setLayer(temp, 1);

			if (byflags & 2) {
				file.read((char *)&tempint, sizeof(tempint));
				temp.grhIndex = tempint;
				InitGrh(temp, tempint, true);
				m_World[x][y]->setLayer(temp, 2);
			}
			else {
				temp.grhIndex = 0;
				InitGrh(temp, 0, true);
				m_World[x][y]->setLayer(temp, 2);
			}

			if (byflags & 4) {
				file.read((char *)&tempint, sizeof(tempint));
				temp.grhIndex = tempint;
				InitGrh(temp, tempint, true);
				m_World[x][y]->setLayer(temp, 3);
			}
			else {
				temp.grhIndex = 0;
				InitGrh(temp, 0, true);
				m_World[x][y]->setLayer(temp, 3);
			}

			if (byflags & 8) {
				file.read((char *)&tempint, sizeof(tempint));
				temp.grhIndex = tempint;
				InitGrh(temp, tempint, true);
				m_World[x][y]->setLayer(temp, 4);
			}
			else {
				temp.grhIndex = 0;
				InitGrh(temp, 0, true);
				m_World[x][y]->setLayer(temp, 4);
			}

			m_World[x][y]->setTrigger(0);

			if (byflags & 16) {
				file.read((char *)&tempint, sizeof(tempint));
				m_World[x][y]->setTrigger(tempint);
			}

			if (m_World[x][y]->isCharIndex()) {
				m_World[x][y]->setCharIndex(0);
			}

			m_World[x][y]->setCharIndex(0);
			OBJ objinfo; objinfo.objindex = 0; objinfo.amount = 0;
			m_World[x][y]->setObjGrh(0);
			m_World[x][y]->setObjInfo(objinfo);
		}
	}

	file.close();
}

void OGEGame::CreateUser(short m_CharIndex, std::string m_Name, char m_Heading, short m_PosX, short m_PosY, short m_Body, short m_Head, short m_Helmet, short m_Weapon, short m_Shield) {
	if (m_CharIndex > GetLastChar())
		SetLastChar(m_CharIndex);

	if (GetUser(m_CharIndex)->isActive())
		++m_NumChars;

	if (m_Weapon == 2) m_Weapon = 0;
	if (m_Shield == 2) m_Shield = 0;
	if (m_Helmet == 2) m_Helmet = 0;

	m_World[m_PosX][m_PosY]->setCharIndex(m_CharIndex);
	
	delete m_User[m_CharIndex];
	m_User[m_CharIndex] = new OGEUser(m_Heading, m_Name, m_PosX, m_PosY, m_Data->m_BodyData[m_Body], m_Data->m_HeadData[m_Head], m_Data->m_HelmetData[m_Helmet], m_Data->m_WeaponData[m_Weapon], m_Data->m_ShieldData[m_Shield]);
}

void OGEGame::MoveTo(char m_Direction) {
	bool LegalOk = false;

	OGEUser *m_User = GetUser(GetUserCharIndex());
	short m_UserPosX = m_User->GetPosX();
	short m_UserPosY = m_User->GetPosY();

	switch (m_Direction) {
		case NORTH:
			LegalOk = MoveToLegalPos(m_UserPosX, m_UserPosY - 1);
				break;

		case EAST:
			LegalOk = MoveToLegalPos(m_UserPosX + 1, m_UserPosY);
				break;

		case SOUTH:
			LegalOk = MoveToLegalPos(m_UserPosX, m_UserPosY + 1);
				break;

		case WEST:
			LegalOk = MoveToLegalPos(m_UserPosX - 1, m_UserPosY);
				break;
	}

	if ((LegalOk) && (!GetUserParalizado())){
		m_Protocol->WriteWalk(m_Direction);
		if (!GetUserDescansando() & !GetUserMeditando()){
			MoveCharByHead(GetUserCharIndex(), m_Direction);
			MoveScreen(m_Direction);
		}
	}
	else{
		if (m_User->GetHeading() != m_Direction)
			m_Protocol->WriteChangeHeading(m_Direction);
	}
}

void OGEGame::MoveScreen(char m_Direction) {
	short m_X = 0, m_Y = 0;
	short m_UserPosX = GetUserPosX(), m_UserPosY = GetUserPosY();

	switch (m_Direction){
		case NORTH:
			m_Y = -1;
				break;

		case EAST:
			m_X = 1;
				break;

		case SOUTH:
			m_Y = 1;
				break;

		case WEST:
			m_X = -1;
				break;
	}

	short m_tX = m_UserPosX + m_X;
	short m_tY = m_UserPosY + m_Y;

	SetAddToUserPosition(m_X, m_Y);
	SetUserPosition(m_tX, m_tY);
	SetUserMoving(1);

	//Update_bTecho(tX, tY); //si agregamos la condicion, ésto lo quitamos.
}

bool OGEGame::MoveToLegalPos(short m_PosX, short m_PosY) {
	if (m_PosX < 1 || m_PosX > 100 || m_PosY < 1 || m_PosY > 100) return false;
	if (GetWorld()[m_PosX][m_PosY]->isBlocked())
		return false;

	short m_CharIndex = GetWorld()[m_PosX][m_PosY]->isCharIndex();
	short m_UserPosX = GetUserPosX(), m_UserPosY = GetUserPosY();

	if (m_CharIndex > 0){
		if (GetWorld()[m_UserPosX][m_UserPosY]->isBlocked())
			return false;

		if ((GetUser(m_CharIndex)->GetHeadIndex() != 500) && (GetUser(m_CharIndex)->GetBodyIndex() != 87)) {
			return false;
		}
		else {
			if (GetWorld()[m_UserPosX][m_UserPosY]->isWater()) {
				if (!GetWorld()[m_PosX][m_PosY]->isWater()) return false;
			}
			else {
				if (GetWorld()[m_PosX][m_PosY]->isWater()) return false;
			}

			if (GetUser(GetUserCharIndex())->GetPrivilegios() > 0 && GetUser(GetUserCharIndex())->GetPrivilegios() < 6)
				if (GetUser(GetUserCharIndex())->isInvisible()) return false;
		}
	}

	if (GetUserNavegando() != GetWorld()[m_PosX][m_PosY]->isWater()) return false;
	return true;
}

void OGEGame::MoveCharByHead(short m_CharIndex, char m_Direction) {
	short m_AddX = 0, m_AddY = 0;
	short m_OffsetX = 0, m_OffsetY = 0;

	OGEUser *m_User = GetUser(m_CharIndex);
	short m_X = m_User->GetPosX();
	short m_Y = m_User->GetPosY();

	switch (m_Direction){
		case NORTH:
			m_AddY = -1;
				break;

		case EAST:
			m_AddX = 1;
				break;

		case SOUTH:
			m_AddY = 1;
				break;

		case WEST:
			m_AddX = -1;
				break;
	}

	//HAY QUE CORREGIR ESTO, NO DEBERÍA SUCEDER:
	if (m_AddX == -1) {
		m_OffsetX = 1;
	}
	else if (m_AddY == -1) {
		m_OffsetY = 1;
	}

	short m_nX = m_X + m_AddX;
	short m_nY = m_Y + m_AddY;

	GetWorld()[m_nX][m_nY]->setCharIndex(m_CharIndex);
	m_User->SetPosition(m_nX, m_nY);
	GetWorld()[m_X][m_Y]->setCharIndex(0);

	m_User->SetMoveOffsetX(-1 * (float)(TILE_PIXEL_WIDTH  * m_AddX) + m_OffsetX);
	m_User->SetMoveOffsetY(-1 * (float)(TILE_PIXEL_HEIGHT * m_AddY) + m_OffsetY);

	m_User->SetMoving(1);
	m_User->SetHeading(m_Direction);

	m_User->SetScrollDirectionX(m_AddX);
	m_User->SetScrollDirectionY(m_AddY);

	DoPasosFX(m_CharIndex);

	if ((m_nY < 1) || (m_nY > 100) || (m_nX < 1) || (m_nX > 100)){
		if (m_CharIndex != GetUserCharIndex())
			EraseChar(m_CharIndex);
	}
}

void OGEGame::MoveCharByPos(short m_CharIndex, char m_nX, char m_nY){
	short m_X = GetUser(m_CharIndex)->GetPosX();
	short m_Y = GetUser(m_CharIndex)->GetPosY();

	m_World[m_X][m_Y]->setCharIndex(0);

	short m_AddX = m_nX - m_X;
	short m_AddY = m_nY - m_Y;

	char m_Heading;

	if (Sgn(m_AddX) == 1)
		m_Heading = EAST;

	if (Sgn(m_AddX) == -1)
		m_Heading = WEST;

	if (Sgn(m_AddY) == 1)
		m_Heading = SOUTH;

	if (Sgn(m_AddY) == -1)
		m_Heading = NORTH;

	m_World[m_nX][m_nY]->setCharIndex(m_CharIndex);
	GetUser(m_CharIndex)->SetPosition(m_nX, m_nY);
	GetUser(m_CharIndex)->SetMoveOffsetX(-1.0f * (float)(TILE_PIXEL_WIDTH  * m_AddX));
	GetUser(m_CharIndex)->SetMoveOffsetY(-1.0f * (float)(TILE_PIXEL_HEIGHT * m_AddY));

	GetUser(m_CharIndex)->SetMoving(1);
	GetUser(m_CharIndex)->SetHeading(m_Heading);

	GetUser(m_CharIndex)->SetScrollDirectionX(Sgn(m_AddX));
	GetUser(m_CharIndex)->SetScrollDirectionY(Sgn(m_AddY));

	//FALTA: parche para que no medite cuando camina
	//If .FxIndex = FxMeditar.CHICO Or .FxIndex = FxMeditar.GRANDE Or .FxIndex = FxMeditar.MEDIANO Or .FxIndex = FxMeditar.XGRANDE Or .FxIndex = FxMeditar.XXGRANDE Then

	//If Not EstaPCarea(CharIndex) Then Call Dialogos.RemoveDialog(CharIndex)

	if ((m_nY < 0) || (m_nY > 100) || (m_nX < 0) || (m_nX > 100))
		EraseChar(m_CharIndex);
}

void OGEGame::ConvertCPtoTP(int &m_X, int &m_Y){
	m_X = GetUserPosX() + (m_X / TILE_PIXEL_WIDTH) - ((MAIN_VIEW_PORT_X / TILE_PIXEL_WIDTH) / 2);
	m_Y = GetUserPosY() + (m_Y / TILE_PIXEL_HEIGHT) - ((MAIN_VIEW_PORT_Y / TILE_PIXEL_HEIGHT) / 2);
}

void OGEGame::DoPasosFX(short m_CharIndex) {
	OGEUser *m_User = GetUser(m_CharIndex);

	if (m_User->isDead() || m_User->GetPrivilegios() > 1)
		return;

	char m_PosX = m_User->GetPosX(), m_PosY = m_User->GetPosY();

	if (!GetWorld()[m_PosX][m_PosY]->isWater()) {
		bool m_Pie = !m_User->GetPie();
		m_User->SetPie(m_Pie);

		if (m_Pie) {
			GetAudio()->PlayWAV("23.wav");
		}
		else {
			GetAudio()->PlayWAV("24.wav");
		}
	}
	else {
		GetAudio()->PlayWAV("50.wav");
	}
}

void OGEGame::InitGrh(GRH &Grh, short m_GrhIndex, bool m_Started) {
	GRHDATA *m_GrhData = m_Data->m_GrhData;

	Grh.grhIndex = m_GrhIndex;
	Grh.frameCounter = 1;

	if (m_Started) {
		if (m_GrhData[Grh.grhIndex].numFrames > 1) {
			Grh.started = true;
		}
		else {
			Grh.started = false;
		}
	}
	else {
		m_Started = true;
		if (m_GrhData[Grh.grhIndex].numFrames == 1) m_Started = false;
		Grh.started = m_Started;
	}

	if (Grh.started) {
		Grh.loops = -1;
	}
	else {
		Grh.loops = 0;
	}

	Grh.frameCounter = 1;
	Grh.speed = m_GrhData[Grh.grhIndex].speed;
}

void OGEGame::EraseChar(short m_CharIndex) {
	GetUser(m_CharIndex)->SetActive(0);

	if (m_CharIndex == GetLastChar()) {
		while (GetUser(GetLastChar())->isActive() != 1){
			--m_LastChar;
			if (GetLastChar() == 0)
				break;
		}
	}

	m_World[GetUser(m_CharIndex)->GetPosX()][GetUser(m_CharIndex)->GetPosY()]->setCharIndex(0);
	GetUser(m_CharIndex)->ResetChar();
	--m_NumChars;
}

void OGEGame::RefreshAllDialogsCount() {
	for (int i = 1; i <= GetLastChar(); ++i){
		if (GetUser(i)->GetDialog() != "") {
			GetUser(i)->SetDialogLife(GetUser(i)->GetDialogLife() - 1);
			if (GetUser(i)->GetDialogLife() <= 0)
				GetUser(i)->SetDialog("", -1, 1, 0, 0.0f);
		}
	}
}

void OGEGame::RefreshAllChars() {
	for (int Loopc = 1; Loopc <= GetLastChar(); ++Loopc) {
		if (GetUser(Loopc)->isActive())
			m_World[GetUser(Loopc)->GetPosX()][GetUser(Loopc)->GetPosY()]->setCharIndex(Loopc);
	}
}

void OGEGame::ResetAllInfo() {
	GetForms()->FMain_Visible(false);
	GetForms()->FConnect_Visible(true);
	m_Connected = false;
	m_UserMeditar = false;
	m_UserNavegando = false;
	m_UserDescansar = false;
	m_UserParalizado = false;
	m_UserMoving = 0;
	m_UserCharIndex = 0;

	for (int i = 1; i <= m_LastChar; ++i)
		GetUser(i)->SetInvisible(false);

	//m_UserClass, Raza, Genero, Mail, etc.
	/*' Reset skills
		For i = 1 To NUMSKILLS
		UserSkills(i) = 0
		Next i

		' Reset attributes
		For i = 1 To NUMATRIBUTOS
		UserAtributos(i) = 0
		Next i

		' Clear inventory slots
		Inventario.ClearAllSlots*/
}

void OGEGame::ChangeArea(char m_X, char m_Y) {
	SetMinLimiteX((m_X / 9 - 1) * 9);
	SetMaxLimiteX(GetMinLimiteX() + 26);

	SetMinLimiteY((m_Y / 9 - 1) * 9);
	SetMaxLimiteY(GetMinLimiteY() + 26);

	for (char m_LoopX = 1; m_LoopX <= 100; ++m_LoopX){
		for (char m_LoopY = 1; m_LoopY <= 100; ++m_LoopY){
			if ((m_LoopY < GetMinLimiteY()) || (m_LoopY > GetMaxLimiteY()) || (m_LoopX < GetMinLimiteX()) || (m_LoopX > GetMaxLimiteX())){
				if (GetWorld()[m_LoopX][m_LoopY]->isCharIndex() != GetUserCharIndex()){
					EraseChar(GetWorld()[m_LoopX][m_LoopY]->isCharIndex());
				}
				GetWorld()[m_LoopX][m_LoopY]->setObjGrh(0);
			}
		}
	}

	RefreshAllChars();
}

short OGEGame::Sgn(short m_Number) {
	if (m_Number == 0) return 0;
	return m_Number > 0 ? 1 : -1;
}