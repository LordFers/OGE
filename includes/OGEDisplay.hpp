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

#ifndef _H_OGEDISPLAY_
#define _H_OGEDISPLAY_
#include "OGEEngine.hpp"
#include "OGEEvents.hpp"
#include "stdafx.hpp"

class OGEDisplay {
private:
	static LRESULT CALLBACK OGEDisplay::WindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	OGEDisplay(IEngine *m_Engine, OGEEvents *m_Events, int width, int height, bool fullscreen);

public:
	void OGEDisplay::RegisterWindow(int width, int height, bool fullscreen);

private:
	HWND m_hWnd;

private:
	OGEEvents* m_Events;

private:
	int m_viewWidth, m_viewHeight;
	bool m_fullScreen;
};
#endif