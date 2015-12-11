/*****************************************************************************
*   Open-source Game Engine (OGE) 0.1.0 programmed in C++
******************************************************************************
*   Copyright (C) 2016 - Fernando Alan Quinteros, 10th Dec 2015.
*   http://email:lordfers@gmail.com
******************************************************************************
*   This program is open-source and free software.
*   OGE used the standard libraries OpenGL and DirectX 9.
*   https://github.com/LordFers/OGE.git
*****************************************************************************/

#ifndef _H_OGEEVENTS_
#define _H_OGEEVENTS_
#include "stdafx.hpp"
#include "OGEEngine.hpp"

class OGEEvents {
	public:
		OGEEvents(IEngine *m_Engine);

	public:
		void OGEEvents::KeyEvents(WPARAM wParam);
	
	public:
		inline void OGEEvents::setKeyDown(WPARAM wParam){ this->m_Keys[wParam] = true; }
		inline void OGEEvents::setKeyUp(WPARAM wParam){ this->m_Keys[wParam] = false; }

	private:
		IEngine *m_Engine;
		bool m_Keys[256];
};
#endif