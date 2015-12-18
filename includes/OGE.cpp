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

#include "OGE.hpp"

OGE::OGE(){

	#ifdef _WIN32
		m_Engine = new CEngineDX();
	#elif __linux__
		m_Engine = new CEngineOGL();
	#endif
	
	m_Events = new OGEEvents(m_Engine);
	new OGEDisplay(m_Engine, m_Events, 1280, 720, false);
	
	while (m_Engine->IsRun()){
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		m_Engine->Render();
	}
}
