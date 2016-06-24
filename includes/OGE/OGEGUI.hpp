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
#include "OGEForms.hpp"

using namespace CEGUI;

class OGEForms;
class OGEGUI {
	public:
		OGEGUI::OGEGUI(LPDIRECT3DDEVICE9 m_Direct3DDevice);

	public:
		inline void OGEGUI::SetGame(OGEGame *m_Game) { this->m_Game = m_Game; }
		inline void OGEGUI::SetForms(OGEForms *m_Forms) { this->m_Forms = m_Forms; }
	
	private:
		inline OGEGame *OGEGUI::GetGame() { return this->m_Game; }

	private:
		inline void OGEGUI::SetSingleton(System *m_Singleton) { this->m_Singleton = m_Singleton; }

	public:
		inline OGEForms *OGEGUI::GetForms() { return this->m_Forms; }
		inline System *OGEGUI::GetSingleton() { return this->m_Singleton; }
		inline Window *OGEGUI::GetWinRoot() { return this->m_WinRoot; }

	private:
		inline void OGEGUI::SetWinRoot(Window* m_WinRoot) { this ->m_WinRoot = m_WinRoot; }

	public:
		inline void OGEGUI::injectKeyUp(Key::Scan scan_code) { GetSingleton()->getDefaultGUIContext().injectKeyUp(scan_code); }
		inline void OGEGUI::injectKeyDown(Key::Scan scan_code) { GetSingleton()->getDefaultGUIContext().injectKeyDown(scan_code); }
		inline void OGEGUI::injectChar(utf32 code_point) { GetSingleton()->getDefaultGUIContext().injectChar(code_point); }
		inline void OGEGUI::injectMouseMove(float posX, float posY) { GetSingleton()->getDefaultGUIContext().injectMousePosition(posX, posY); }
		inline void OGEGUI::injectMouseButtonDown() { GetSingleton()->getDefaultGUIContext().injectMouseButtonDown(MouseButton::LeftButton); }
		inline void OGEGUI::injectMouseButtonUp() { GetSingleton()->getDefaultGUIContext().injectMouseButtonUp(MouseButton::LeftButton); }
		inline void OGEGUI::injectTimePulse(float timeElapsed) { GetSingleton()->injectTimePulse(timeElapsed); }

	protected:
		OGEGame *m_Game;
		OGEForms *m_Forms;
		System *m_Singleton;
		Window *m_WinRoot;
};