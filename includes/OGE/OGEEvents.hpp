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
//#ifndef _H_OGEEVENTS_
//#define _H_OGEEVENTS_

#include "stdafx.hpp"
#include "OGEGame.hpp"

class OGEEvents {
	public:
		OGEEvents::OGEEvents(OGEGame *m_Game);
		inline void OGEEvents::SetGUI(OGEGUI *m_GUI) { this->m_GUI = m_GUI; }

	public:
		void OGEEvents::WindowEvents(UINT message, WPARAM wParam, LPARAM lParam);
		void OGEEvents::KeyEvents(WPARAM wParam);
		void OGEEvents::CheckKeys();

	public:
		inline void OGEEvents::setKeyDown(WPARAM wParam){ this->m_Keys[wParam] = true; }
		inline void OGEEvents::setKeyUp(WPARAM wParam){ this->m_Keys[wParam] = false; }

	private:
		OGEGame *m_Game;
		OGEGUI  *m_GUI;
		bool m_Keys[256];
};
//#endif