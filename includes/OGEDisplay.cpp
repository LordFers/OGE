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

#include "OGEDisplay.hpp"

OGEDisplay::OGEDisplay(IEngine *Engine, OGEEvents *Events, int width, int height, bool fullscreen) {
	RegisterWindow(width, height, fullscreen);
	Engine->setRun(Engine->Initialize(m_hWnd, width, height, fullscreen));
	this->Events = Events;
}

void OGEDisplay::RegisterWindow(int width, int height, bool fullscreen){
	WNDCLASSEX wincl;

	wincl.hInstance = GetModuleHandleW(NULL);
	wincl.lpszClassName = _T("OGEWindow");
	wincl.lpfnWndProc = WindProc;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	int center_x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int center_y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	if (!RegisterClassEx(&wincl)) return;

	m_hWnd = CreateWindowEx(0, _T("OGEWindow"), _T("OGE"), WS_POPUP | WS_VISIBLE | WS_SYSMENU,
		center_x, center_y - 20, width, height, HWND_DESKTOP, NULL, GetModuleHandleW(NULL), this);

	m_viewWidth = width;
	m_viewHeight = height;
	m_fullScreen = fullscreen;
}

LRESULT CALLBACK OGEDisplay::WindProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	OGEDisplay *pThis;
	if (message == WM_NCCREATE){
		pThis = static_cast<OGEDisplay*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hwnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(pThis))){
			if (GetLastError() != 0)
				return FALSE;
		}
	}else{
		pThis = reinterpret_cast<OGEDisplay*>(GetWindowLongPtr(hwnd, GWL_USERDATA));
	}

	if (pThis){
		switch (message){
			case WM_DESTROY:
				PostQuitMessage(0);
					break;

			case WM_KEYDOWN:
				pThis->Events->setKeyDown(wParam);
				pThis->Events->KeyEvents(wParam);
					break;

			case WM_KEYUP:
				pThis->Events->setKeyUp(wParam);
					break;

			default:
				return DefWindowProc(hwnd, message, wParam, lParam);
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}