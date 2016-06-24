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
#ifndef _H_OGE_
#define _H_OGE_

#include "stdafx.hpp"
#include "OGEEngine.hpp"
#include "OGEDisplay.hpp"
#include "OGEEvents.hpp"
#include "OGEGame.hpp"
#include "OGEWatch.hpp"
#include "OGERender.hpp"
#include "OGEProtocol.hpp"

class OGE {
	public:
		OGE::OGE();

	public:
		OGEEngine *m_Engine;
		OGEGame *m_Game;
		OGEEvents *m_Events;
		OGERender *m_Render; //DEBE SER IRENDER como interface.
		OGEProtocol *m_Protocol;

	public:
		OGEWatch m_Watch;

	private:
		MSG msg;
};
#endif