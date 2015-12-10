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

#ifndef _H_OGE_
#define _H_OGE_

#include "OGEEngine.hpp"
#include "OGEDisplay.hpp"
#include "OGEEvents.hpp"

class OGE {
	public:
		OGE();

	public:
		IEngine* Engine;
		OGEEvents* Events;

	private:
		MSG msg;
};
#endif