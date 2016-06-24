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
//#ifndef _H_OGEDISPLAY_
//#define _H_OGEDISPLAY_

#include "stdafx.hpp"
#include "OGEEngine.hpp"
#include "OGEEvents.hpp"

class OGEDisplay {
private:
	static LRESULT CALLBACK OGEDisplay::WindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	OGEDisplay(OGEEngine *m_Engine, OGEEvents *m_Events, int width, int height, bool fullscreen);

public:
	void OGEDisplay::RegisterWindow(int width, int height, bool fullscreen);

private:
	HWND m_hWnd;

private:
	OGEEvents *m_Events;
	OGEEngine *m_Engine;

private:
	int m_viewWidth, m_viewHeight;
	bool m_fullScreen;
};
//#endif