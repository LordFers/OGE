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

#include "stdafx.hpp"
#include "OGEGame.hpp"

class OGEGame;
class OGERender {
	public:
		OGERender::OGERender(OGEGame *m_Game) { this->m_Game = m_Game; }

	public:
		void OGERender::Scene();
		void OGERender::Screen(short m_tileX, short m_tileY, short m_PixelOffsetX, short m_PixelOffsetY);
		void OGERender::DrawGrh(GRH &m_Grh, short m_X, short m_Y, bool m_Center, bool m_Animate, bool m_Blend);
		void OGERender::Draw_GrhIndex(short grhIndex, short x, short y, int color);
		void OGERender::Char(short m_CharIndex, short m_PixelOffsetX, short m_PixelOffsetY);
		void OGERender::Draw_Text(std::string text, short x, short y, int font_index, bool multi_line, int colortexto);

	public:
		int OGERender::Engine_Text_Width(std::string text, bool multi_line);
		int OGERender::Engine_Text_Height(std::string text, bool multi_line);

	private:
		OGEGame	*m_Game;
};