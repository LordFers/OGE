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
#include "OGE.hpp"

OGE::OGE(){
	#ifdef _WIN32
		m_Engine = new OGEEngine();
	#elif __linux__
		m_Engine = new CEngineOGL();
	#endif
	
	m_Game = new OGEGame(m_Engine);
	m_Render = new OGERender(m_Game);
	m_Protocol = new OGEProtocol(m_Game);
	m_Events = new OGEEvents(m_Game);

	m_Engine->SetRender(m_Render);
	m_Game->SetProtocol(m_Protocol);

	new OGEDisplay(m_Engine, m_Events, MAIN_VIEW_PORT_X, MAIN_VIEW_PORT_Y, false);

	m_Events->SetGUI(m_Engine->GetGUI());
	m_Engine->GetGUI()->SetGame(m_Game);
	m_Engine->GetGUI()->SetForms(new OGEForms(m_Game, m_Engine->GetGUI()->GetSingleton(), m_Engine->GetGUI()->GetWinRoot()));
	m_Game->SetForms(m_Engine->GetGUI()->GetForms());

	while (m_Engine->IsRun()){
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		m_Engine->Render();
		m_Events->CheckKeys();

		m_Protocol->SocketReceive();
		m_Protocol->FlushBuffer();

		if (GetTickCount() >= m_Engine->m_lFrameTimer + 1000) {
			m_Engine->m_lFrameTimer = (float)GetTickCount();
			m_Engine->m_FPS = m_Engine->m_FPSCounter;
			m_Engine->m_FPSCounter = 0;
			m_Game->RefreshAllDialogsCount();
		}

		++m_Engine->m_FPSCounter;
		m_Engine->m_timerElapsedTime = m_Watch.Elapsed();
		m_Engine->GetGUI()->injectTimePulse(m_Engine->m_timerElapsedTime * 0.001f);
		m_Engine->m_timerTicksPerFrame = m_Engine->m_timerElapsedTime * ENGINESPEED;
	}
}