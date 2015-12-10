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

#include "OGEEvents.hpp"

OGEEvents::OGEEvents(IEngine *newEngine){
	for (auto &m_Keys : m_Keys) { m_Keys = false; }
	Engine = newEngine;
}

void OGEEvents::KeyEvents(WPARAM wParam){
	switch (wParam)
	{
		case VK_ESCAPE:
			Engine->setRun(false);
				break;
	}
}
