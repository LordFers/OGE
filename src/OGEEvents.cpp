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

#include "OGEEvents.hpp"

OGEEvents::OGEEvents(OGEGame *m_Game){
	for (auto &m_Keys : m_Keys) { m_Keys = false; }
	this->m_Game = m_Game;
}

CEGUI::utf32 keycodeToUTF32(unsigned int scanCode)
{
	CEGUI::utf32 utf = 0;

	BYTE keyboardState[256];
	unsigned char ucBuffer[3];
	static WCHAR deadKey = '\0';

	// Retrieve the keyboard layout in order to perform the necessary convertions
	HKL hklKeyboardLayout = GetKeyboardLayout(0); // 0 means current thread 
												  // This seemingly cannot fail 
												  // If this value is cached then the application must respond to WM_INPUTLANGCHANGE 

												  // Retrieve the keyboard state
												  // Handles CAPS-lock and SHIFT states
	if (GetKeyboardState(keyboardState) == FALSE)
		return utf;

	UINT virtualKey = MapVirtualKeyEx(scanCode, 3, hklKeyboardLayout);
	if (virtualKey == 0) // No translation possible
		return utf;

	int ascii = ToAsciiEx(virtualKey, scanCode, keyboardState, (LPWORD)ucBuffer, 0, hklKeyboardLayout);
	if (deadKey != '\0' && ascii == 1)
	{
		// A dead key is stored and we have just converted a character key
		// Combine the two into a single character
		WCHAR wcBuffer[3];
		WCHAR out[3];
		wcBuffer[0] = ucBuffer[0];
		wcBuffer[1] = deadKey;
		wcBuffer[2] = '\0';
		if (FoldStringW(MAP_PRECOMPOSED, (LPWSTR)wcBuffer, 3, (LPWSTR)out, 3))
			utf = out[0];
		else
		{
			// FoldStringW failed
			DWORD dw = GetLastError();
			switch (dw)
			{
			case ERROR_INSUFFICIENT_BUFFER:
			case ERROR_INVALID_FLAGS:
			case ERROR_INVALID_PARAMETER:
				break;
			}
		}
		deadKey = '\0';
	}
	else if (ascii == 1)
	{
		// We have a single character
		utf = ucBuffer[0];
		deadKey = '\0';
	}
	else
	{
		// Convert a non-combining diacritical mark into a combining diacritical mark
		switch (ucBuffer[0])
		{
		case 0x5E: // Circumflex accent: â
			deadKey = 0x302;
			break;
		case 0x60: // Grave accent: à
			deadKey = 0x300;
			break;
		case 0xA8: // Diaeresis: ü
			deadKey = 0x308;
			break;
		case 0xB4: // Acute accent: é
			deadKey = 0x301;
			break;
		case 0xB8: // Cedilla: ç
			deadKey = 0x327;
			break;
		default:
			deadKey = ucBuffer[0];
		}
	}

	return utf;
}

UINT virtualkey2scancode(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(lParam) & 0x0F00)
	{
		UINT scancode = MapVirtualKey(wParam, 0);
		return scancode | 0x80;
	}
	else
	{
		return HIWORD(lParam) & 0x00FF;
	}
}

void OGEEvents::WindowEvents(UINT message, WPARAM wParam, LPARAM lParam){
	int m_X, m_Y;
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		case WM_CHAR:
			m_GUI->injectChar(keycodeToUTF32(virtualkey2scancode(wParam, lParam)));
		break;

		case WM_LBUTTONDOWN:
			m_GUI->injectMouseButtonDown();
			if (m_Game->GetConnected()) {
				m_X = LOWORD(lParam), m_Y = HIWORD(lParam);
				m_Game->ConvertCPtoTP(m_X, m_Y);
				m_Game->GetProtocol()->WriteLeftClick(m_X, m_Y);
			}
			//if (Main.keys[VK_SHIFT]) WriteWarpChar("yo", GameData->UserMap, (unsigned char)lx, (unsigned char)ly);
		break;

		case WM_LBUTTONUP:
			m_GUI->injectMouseButtonUp();
		break;

		case WM_RBUTTONDOWN:
			if (m_Game->GetConnected()) {
				m_X = LOWORD(lParam), m_Y = HIWORD(lParam);
				m_Game->ConvertCPtoTP(m_X, m_Y);
				m_Game->GetProtocol()->WriteRightClick(m_X, m_Y);
			}
		break;
		
		case WM_MOUSEMOVE:
			m_GUI->injectMouseMove((float)LOWORD(lParam), (float)HIWORD(lParam));
		break;

		case WM_KEYDOWN:
			setKeyDown(wParam);
			KeyEvents(wParam);
			m_GUI->injectKeyDown(static_cast<CEGUI::Key::Scan>(virtualkey2scancode(wParam, lParam)));
		break;

		case WM_KEYUP:
			setKeyUp(wParam);
			m_GUI->injectKeyUp(static_cast<CEGUI::Key::Scan>(virtualkey2scancode(wParam, lParam)));

			if (wParam == VK_CONTROL)
				m_Game->GetProtocol()->WriteAttack();
		break;
	}
}

void OGEEvents::KeyEvents(WPARAM wParam){
	switch (wParam){
		case VK_ESCAPE:
			if (m_Game->GetConnected()) {
				m_Game->GetEngine()->GetGUI()->GetForms()->FMain_Menu_Visible(true);
			}
			else {
				m_Game->GetEngine()->setRun(false);
			}
		break;

		case VK_RETURN:
			if (m_Game->GetConnected())
				m_Game->GetEngine()->GetGUI()->GetForms()->FMain_SendText();
		break;
	}
}

void OGEEvents::CheckKeys() {
	if (!m_Game->GetUserMoving()){
		if (m_Keys[VK_UP]){
			m_Game->MoveTo(NORTH);
			return;
		}

		if (m_Keys[VK_DOWN]){
			m_Game->MoveTo(SOUTH);
			return;
		}

		if (m_Keys[VK_LEFT]){
			m_Game->MoveTo(WEST);
			return;
		}

		if (m_Keys[VK_RIGHT]){
			m_Game->MoveTo(EAST);
			return;
		}
	}
}