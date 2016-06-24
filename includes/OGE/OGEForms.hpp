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
#include "stdafx.hpp"
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Direct3D9/Renderer.h>
#include "OGEGame.hpp"

using namespace CEGUI;

class OGEGame;
class OGEForms {
	public:
		OGEForms::OGEForms(OGEGame *m_Game, System *m_Singleton, Window *m_WinRoot) {
			this->m_Game = m_Game; this->m_Singleton = m_Singleton; this->m_WinRoot = m_WinRoot; LoadForms();
		}

	public:
		void OGEForms::LoadForms();

	private:
		inline OGEGame *OGEForms::GetGame() { return this->m_Game; }
		inline System  *OGEForms::GetSingleton() { return this->m_Singleton; }
		inline Window  *OGEForms::GetWinRoot() { return this->m_WinRoot; }

	protected:
		OGEGame *m_Game;
		System *m_Singleton;
		Window *m_WinRoot;

//Form Connect:
	public:
		void OGEForms::FConnect_Load();
		void OGEForms::FConnect_Visible(bool m_Visible);
		void OGEForms::FConnect_Login();

	private:
		bool OGEForms::FConnect_MouseButtonUp(const EventArgs &e);
		bool OGEForms::FConnect_MouseButtonUp_CP(const EventArgs &e);
		bool OGEForms::FConnect_MouseButtonUp_Exit(const EventArgs &e);

//Form Create PJ:
	public:
		void OGEForms::FCreateCharacter_Load();
		void OGEForms::FCreateCharacter_Visible(bool m_Visible);
		void OGEForms::FCreateCharacter_setAttributes(unsigned char m_Strength, unsigned char m_Agility,
													  unsigned char m_Intelligence, unsigned char m_Charisma,
													  unsigned char m_Constitution);
	private:
		bool OGEForms::FCreateCharacter_MouseButtonUp_Back(const EventArgs &e);
		bool OGEForms::FCreateCharacter_MouseButtonUp_ThrowDices(const EventArgs &e);
		bool OGEForms::FCreateCharacter_MouseButtonUp_CreateCharacter(const EventArgs &e);

//Form Main:
	public:
		void OGEForms::FMain_Load();
		void OGEForms::FMain_UnLoad();
		void OGEForms::FMain_Visible(bool m_Visible);
		void OGEForms::FMain_Menu_Visible(bool m_Visible);
		void OGEForms::FMain_GuildList_Visible(bool m_Visible);
		void OGEForms::FMain_GuildLeader_Visible(bool m_Visible, bool m_isLeader);
		void OGEForms::FMain_GuildNews_setText(std::string newstext);
		void OGEForms::FMain_Reload_GuildList();
		void OGEForms::FMain_Reload_GuildAspirantes();
		void OGEForms::FMain_Reload_GuildMember();
		void OGEForms::FMain_AddItem_Console(std::string text, int color, bool bold, bool italic);
		void OGEForms::FMain_SendText();
		void OGEForms::FMain_SetExpBar(float m_Value);

	private:
		bool OGEForms::FMain_onCloseClicked(const EventArgs &e);
		bool OGEForms::FMain_onCloseClicked_ClanesWindow(const EventArgs &e);
		bool OGEForms::FMain_onCloseClicked_MiClanWindow(const EventArgs &e);
		bool OGEForms::FMain_Exit_MouseButtonUp(const EventArgs&);
		bool OGEForms::FMain_Deslogin_MouseButtonUp(const EventArgs&);
		bool OGEForms::FMain_ClanesButton(const EventArgs &e);
		bool OGEForms::FMain_ClanesList(const EventArgs &e);
		bool OGEForms::FMain_SolicitudWindow_EnviarButton(const EventArgs &e);
		bool OGEForms::FMain_SolicitarButton(const EventArgs &e);
		bool OGEForms::FMain_Aspirantes_RejectButton(const EventArgs &e);
		bool OGEForms::FMain_Aspirantes_AcceptButton(const EventArgs &e);
		bool OGEForms::FMain_SendText_MouseUp(const EventArgs &e);
		bool OGEForms::FMain_GetActive_SendText();
		bool OGEForms::FMain_MyClanes_MembersButton(const EventArgs &e);
		bool OGEForms::FMain_MyClanes_AspirantesButton(const EventArgs &e);
		bool OGEForms::FMain_MyClanes_ClanesButton(const EventArgs &e);

//Form ErrorMSG:
	public:
		void OGEForms::FErrorWindow_Load();
		void OGEForms::FErrorWindow_UnLoad();
};