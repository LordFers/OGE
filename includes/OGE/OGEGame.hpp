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
#ifndef _H_OGEGAME_
#define _H_OGEGAME_

#include "stdafx.hpp"
#include "OGEDeclares.hpp"
#include "OGEWorld.hpp"
#include "OGEEngine.hpp"
#include "OGEUser.hpp"
#include "OGEProtocol.hpp"
#include "OGEAudio.hpp"

class OGEEngine;
class OGEUser;
class OGEProtocol;
class OGEForms;

class OGEGame {
	public:
		OGEGame::OGEGame(OGEEngine *m_Engine);

	public:
		inline void OGEGame::SetProtocol(OGEProtocol *m_Protocol) { this->m_Protocol = m_Protocol; }
		inline void OGEGame::SetForms(OGEForms *m_Forms) { this->m_Forms = m_Forms; }

	public:
		void OGEGame::LoadMap(int m_Map);
		void OGEGame::CreateUser(short m_CharIndex, std::string m_Name, char m_Heading, short m_PosX, short m_PosY, short m_Body, short m_Head, short m_Helmet, short m_Weapon, short m_Shield);
		void OGEGame::MoveTo(char m_Direction);
		bool OGEGame::MoveToLegalPos(short m_PosX, short m_PosY);
		void OGEGame::MoveScreen(char m_Direction);
		void OGEGame::MoveCharByHead(short m_CharIndex, char m_Direction);
		void OGEGame::MoveCharByPos(short m_CharIndex, char m_nX, char m_nY);
		void OGEGame::ConvertCPtoTP(int &m_X, int &m_Y);
		void OGEGame::DoPasosFX(short m_CharIndex);
		void OGEGame::EraseChar(short m_CharIndex);
		void OGEGame::RefreshAllDialogsCount();
		void OGEGame::RefreshAllChars();
		void OGEGame::ResetAllInfo();
		void OGEGame::ChangeArea(char m_X, char m_Y);
		void OGEGame::InitGrh(GRH &Grh, short m_GrhIndex, bool m_Started);
		short OGEGame::Sgn(short m_Number);

	public:
		inline void OGEGame::SetConnected(bool m_Connected) { this->m_Connected = m_Connected; }
		inline void OGEGame::SetNumChars(short m_NumChars) { this->m_NumChars = m_NumChars; }
		inline void OGEGame::SetLastChar(short m_LastChar) { this->m_LastChar = m_LastChar; }
		inline void OGEGame::SetUserCharIndex(short m_UserIndex) { this->m_UserCharIndex = m_UserIndex; }
		inline void OGEGame::SetUserMoving(bool m_Moving) { this->m_UserMoving = m_Moving; }
		inline void OGEGame::SetUserParalizado(bool m_UserParalizado) { this->m_UserParalizado = m_UserParalizado; }
		inline void OGEGame::SetUserDescansando(bool m_UserDescansar) { this->m_UserDescansar = m_UserDescansar; }
		inline void OGEGame::SetUserMeditando(bool m_UserMeditar) { this->m_UserMeditar = m_UserMeditar; }
		inline void OGEGame::SetUserNavegando(bool m_UserNavegando) { this->m_UserNavegando = m_UserNavegando; }
		inline void OGEGame::SetUserClass(char m_UserClass) { this->m_UserClass = m_UserClass; }
		inline void OGEGame::SetAddToUserPosition(short m_PosX, short m_PosY) { this->m_AddToUserPos.x = m_PosX; this->m_AddToUserPos.y = m_PosY; }
		inline void OGEGame::SetUserPosition(short m_PosX, short m_PosY) { this->m_UserPos.x = m_PosX; this->m_UserPos.y = m_PosY; }

	public:
		inline void OGEGame::SetMinLimiteX(short m_MinLimiteX) { this->m_MinLimiteX = m_MinLimiteX; }
		inline void OGEGame::SetMinLimiteY(short m_MinLimiteY) { this->m_MinLimiteY = m_MinLimiteY; }
		inline void OGEGame::SetMaxLimiteX(short m_MaxLimiteX) { this->m_MaxLimiteX = m_MaxLimiteX; }
		inline void OGEGame::SetMaxLimiteY(short m_MaxLimiteY) { this->m_MaxLimiteY = m_MaxLimiteY; }

	public:
		inline OGEEngine  *OGEGame::GetEngine() { return this->m_Engine; }
		inline OGEAudio	  *OGEGame::GetAudio() { return this->m_Audio; }
		inline OGEForms	  *OGEGame::GetForms() { return this->m_Forms; }
		inline OGEData    *OGEGame::GetData() { return this->m_Data; }
		inline OGEDeclares*OGEGame::GetDeclares() { return this->m_Declares; }
		inline OGEUser	  *OGEGame::GetUser(short m_Index) { return this->m_User[m_Index]; }
		inline OGEWorld ***OGEGame::GetWorld() { return this->m_World; }
		inline OGEProtocol*OGEGame::GetProtocol() { return this->m_Protocol; }
		inline GRHDATA     OGEGame::GetGrh(int m_GrhIndex) { return this->m_Data->m_GrhData[m_GrhIndex]; }

	public:
		inline bool		   OGEGame::GetConnected() { return this->m_Connected; }
		inline short	   OGEGame::GetNumChars() { return this->m_NumChars; }
		inline short	   OGEGame::GetLastChar() { return this->m_LastChar; }
		inline short	   OGEGame::GetUserCharIndex() { return this->m_UserCharIndex; }
		inline bool		   OGEGame::GetUserMoving() { return this->m_UserMoving; }
		inline bool		   OGEGame::GetUserParalizado() { return this->m_UserParalizado; }
		inline bool		   OGEGame::GetUserDescansando() { return this->m_UserDescansar; }
		inline bool		   OGEGame::GetUserMeditando() { return this->m_UserMeditar; }
		inline bool		   OGEGame::GetUserNavegando() { return this->m_UserNavegando; }
		inline char		   OGEGame::GetUserClass() { return this->m_UserClass; }
		inline short	   OGEGame::GetAddPositionX() { return this->m_AddToUserPos.x; }
		inline short	   OGEGame::GetAddPositionY() { return this->m_AddToUserPos.y; }
		inline short	   OGEGame::GetUserPosX() { return this->m_UserPos.x; }
		inline short	   OGEGame::GetUserPosY() { return this->m_UserPos.y; }

	public:
		inline short	   OGEGame::GetMinLimiteX() { return m_MinLimiteX; }
		inline short	   OGEGame::GetMinLimiteY() { return m_MinLimiteY; }
		inline short	   OGEGame::GetMaxLimiteX() { return m_MaxLimiteX; }
		inline short	   OGEGame::GetMaxLimiteY() { return m_MaxLimiteY; }

	private:
		OGEEngine   *m_Engine;
		OGEAudio	*m_Audio;
		OGEForms	*m_Forms;
		OGEData		*m_Data;
		OGEDeclares *m_Declares;
		OGEWorld	***m_World;
		OGEUser		**m_User;
		OGEProtocol *m_Protocol;

	protected:
		short m_NumChars;
		short m_LastChar;
		short m_UserCharIndex;

		bool m_Connected;
		bool m_UserMoving;
		bool m_UserParalizado;
		bool m_UserMeditar;
		bool m_UserDescansar;
		bool m_UserNavegando;

		char m_UserClass;

		short m_MinLimiteX;
		short m_MaxLimiteX;

		short m_MinLimiteY;
		short m_MaxLimiteY;

		POSITION m_AddToUserPos;
		POSITION m_UserPos;
};
#endif