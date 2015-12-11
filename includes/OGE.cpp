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
	/* In process */
	#ifdef _WIN32
		Engine = new CEngineDX();
	#elif __linux__
		Engine = new CEngineOGL();
	#endif
	
	Events = new OGEEvents(Engine);

	new OGEDisplay(Engine, Events, 1280, 720, false);
	
	while (Engine->IsRun()){
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Engine->Render();
	}
}
