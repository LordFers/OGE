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
#include "OGERender.hpp"

void OGERender::Scene() {
	static float m_OffsetCounterX;
	static float m_OffsetCounterY;

	if (m_Game->GetUserMoving()){
		if (m_Game->GetAddPositionX() != 0){
			m_OffsetCounterX += -SCROLL_PIXELS_PER_FRAME_X * m_Game->GetAddPositionX() * m_Game->GetEngine()->m_timerTicksPerFrame;
			if (abs(m_OffsetCounterX) >= TILE_PIXEL_WIDTH){
				m_OffsetCounterX = 0;
				m_Game->SetAddToUserPosition(0, m_Game->GetAddPositionY());
				m_Game->SetUserMoving(0);
			}
		}

		if (m_Game->GetAddPositionY() != 0){
			m_OffsetCounterY += -SCROLL_PIXELS_PER_FRAME_Y * m_Game->GetAddPositionY() * m_Game->GetEngine()->m_timerTicksPerFrame;
			if (abs(m_OffsetCounterY) >= TILE_PIXEL_HEIGHT){
				m_OffsetCounterY = 0;
				m_Game->SetAddToUserPosition(m_Game->GetAddPositionX(), 0);
				m_Game->SetUserMoving(0);
			}
		}
	}

	Screen(m_Game->GetUserPosX() - m_Game->GetAddPositionX(), m_Game->GetUserPosY() - m_Game->GetAddPositionY(), (short)m_OffsetCounterX, (short)m_OffsetCounterY);
}

void OGERender::Draw_GrhIndex(short grhIndex, short x, short y, int color){
	if (grhIndex <= 0) return;
	GRHDATA *m_GrhData = m_Game->GetData()->m_GrhData;

	m_Game->GetEngine()->VertexTexture(m_GrhData[grhIndex].filenum, x, y,
		m_GrhData[grhIndex].pixelWidth,
		m_GrhData[grhIndex].pixelHeight,
		m_GrhData[grhIndex].sX,
		m_GrhData[grhIndex].sY, false, color);
}

void OGERender::DrawGrh(GRH &m_Grh, short m_X, short m_Y, bool m_Center, bool m_Animate, bool m_Blend) {
	if (m_Grh.grhIndex <= 0)
		return;

	if (m_Game->GetData()->m_GrhData[m_Grh.grhIndex].numFrames == 0)
		return;

	GRHDATA *m_GrhData = m_Game->GetData()->m_GrhData;
	float timerElapsed = m_Game->GetEngine()->m_timerElapsedTime;

	if (m_Animate) {
		if (m_Grh.started) {
			m_Grh.frameCounter = m_Grh.frameCounter + (timerElapsed * m_GrhData[m_Grh.grhIndex].numFrames) / m_Grh.speed;
			if (m_Grh.frameCounter > m_GrhData[m_Grh.grhIndex].numFrames) {
				m_Grh.frameCounter = (float)(((int)m_Grh.frameCounter % (int)m_GrhData[m_Grh.grhIndex].numFrames) + 1);
				if (m_Grh.loops != -1) {
					if (m_Grh.loops > 0) {
						m_Grh.loops--;
					}
					else {
						m_Grh.started = false;
					}
				}
			}
		}
	}


	if (m_Grh.frameCounter + 0.5f < 1.0f) m_Grh.frameCounter = 1.0f;
	int currentGrhIndex = m_GrhData[m_Grh.grhIndex].frames[(int)(m_Grh.frameCounter + 0.5f)];

	if (m_Center) {
		if (m_GrhData[currentGrhIndex].tileWidth != 1)
			m_X = m_X - (int)(m_GrhData[currentGrhIndex].tileWidth * TILE_PIXEL_WIDTH / 2) + TILE_PIXEL_WIDTH / 2;

		if (m_GrhData[currentGrhIndex].tileHeight != 1)
			m_Y = m_Y - (int)(m_GrhData[currentGrhIndex].tileHeight * TILE_PIXEL_HEIGHT) + TILE_PIXEL_HEIGHT;
	}

	if (currentGrhIndex == 0)
		return;

	if (m_GrhData[currentGrhIndex].filenum == 0)
		return;

	m_Game->GetEngine()->VertexTexture(m_GrhData[currentGrhIndex].filenum, m_X, m_Y,
		m_GrhData[currentGrhIndex].pixelWidth,
		m_GrhData[currentGrhIndex].pixelHeight,
		m_GrhData[currentGrhIndex].sX,
		m_GrhData[currentGrhIndex].sY, m_Blend, -1);
}

void OGERender::Screen(short m_tileX, short m_tileY, short m_PixelOffsetX, short m_PixelOffsetY) {
	short screenminY = 0, screenmaxY = 0;
	short screenminX = 0, screenmaxX = 0;
	short minY, maxY;
	short minX, maxX;
	short ScreenX = 0, ScreenY = 0;
	short minXOffset = 0, minYOffset = 0;
	short y, x;

	screenminY = m_tileY - HALF_WINDOW_TILE_HEIGHT;
	screenmaxY = m_tileY + HALF_WINDOW_TILE_HEIGHT;
	screenminX = m_tileX - HALF_WINDOW_TILE_WIDTH;
	screenmaxX = m_tileX + HALF_WINDOW_TILE_WIDTH;

	minY = screenminY - TILE_BUFFER_SIZE;
	maxY = screenmaxY + TILE_BUFFER_SIZE;
	minX = screenminX - TILE_BUFFER_SIZE;
	maxX = screenmaxX + TILE_BUFFER_SIZE;

	if (minY < X_MIN_MAP_SIZE)
	{
		minYOffset = Y_MIN_MAP_SIZE - minY;
		minY = Y_MIN_MAP_SIZE;
	}

	if (maxY > Y_MAX_MAP_SIZE) maxY = Y_MAX_MAP_SIZE;

	if (minX < X_MIN_MAP_SIZE)
	{
		minXOffset = X_MIN_MAP_SIZE - minX;
		minX = X_MIN_MAP_SIZE;
	}

	if (maxX > X_MAX_MAP_SIZE) maxX = X_MAX_MAP_SIZE;

	if (screenminY > Y_MIN_MAP_SIZE)
	{
		screenminY = screenminY - 1;
	}
	else
	{
		screenminY = 1;
		ScreenY = 1;
	}

	if (screenmaxY < Y_MAX_MAP_SIZE) screenmaxY = screenmaxY + 1;

	if (screenminX > X_MIN_MAP_SIZE)
	{
		screenminX = screenminX - 1;
	}
	else
	{
		screenminX = 1;
		ScreenX = 1;
	}

	if (screenmaxX < X_MAX_MAP_SIZE) screenmaxX = screenmaxX + 1;

	if (screenmaxX > X_MAX_MAP_SIZE) screenmaxX = X_MAX_MAP_SIZE;
	if (screenmaxY > Y_MAX_MAP_SIZE) screenmaxY = Y_MAX_MAP_SIZE;
	if (screenminX < X_MIN_MAP_SIZE) screenminX = X_MIN_MAP_SIZE;
	if (screenminY < Y_MIN_MAP_SIZE) screenminY = Y_MIN_MAP_SIZE;

	OGEWorld ***World = m_Game->GetWorld();

	for (y = screenminY; y <= screenmaxY; y++){
		for (x = screenminX; x <= screenmaxX; x++){
			DrawGrh(World[x][y]->isLayer(1),
				(ScreenX - 1) * TILE_PIXEL_WIDTH + m_PixelOffsetX,
				(ScreenY - 1) * TILE_PIXEL_HEIGHT + m_PixelOffsetY, true, true, false);

			if (World[x][y]->isLayer(2).grhIndex != 0)
				DrawGrh(World[x][y]->isLayer(2), (ScreenX - 1) * TILE_PIXEL_WIDTH + m_PixelOffsetX,
												 (ScreenY - 1) * TILE_PIXEL_HEIGHT + m_PixelOffsetY, true, true, false);

			ScreenX++;
		}
		ScreenX = ScreenX - x + screenminX;
		ScreenY++;
	}

	ScreenY = minYOffset - TILE_BUFFER_SIZE;
	for (y = minY; y <= maxY; y++){
		ScreenX = minXOffset - TILE_BUFFER_SIZE;
		for (x = minX; x <= maxX; x++){
			if (World[x][y]->isObjGrh().grhIndex != 0)
				DrawGrh(World[x][y]->isObjGrh(), ScreenX * TILE_PIXEL_WIDTH + m_PixelOffsetX,
												 ScreenY * TILE_PIXEL_HEIGHT + m_PixelOffsetY, true, true, false);

			if (m_Game->GetConnected()){
				if (World[x][y]->isCharIndex())
					Char(World[x][y]->isCharIndex(), (ScreenX * TILE_PIXEL_WIDTH + m_PixelOffsetX), (ScreenY * TILE_PIXEL_HEIGHT + m_PixelOffsetY));
			}
			
			if (World[x][y]->isLayer(3).grhIndex != 0)
				DrawGrh(World[x][y]->isLayer(3), ScreenX * TILE_PIXEL_WIDTH + m_PixelOffsetX,
															   ScreenY * TILE_PIXEL_HEIGHT + m_PixelOffsetY, true, true, false);
			ScreenX++;
		}
		ScreenY++;
	}

	ScreenY = minYOffset - TILE_BUFFER_SIZE;
	for (y = minY; y <= maxY; y++){
		ScreenX = minXOffset - TILE_BUFFER_SIZE;
		for (x = minX; x <= maxX; x++){
			if (false == false){ //bTecho
				if (World[x][y]->isLayer(4).grhIndex > 0)
					DrawGrh(World[x][y]->isLayer(4), ScreenX * TILE_PIXEL_WIDTH + m_PixelOffsetX,
												     ScreenY * TILE_PIXEL_HEIGHT + m_PixelOffsetY, true, true, false);
			}

			if (m_Game->GetConnected()) {
				if (World[x][y]->isCharIndex()) {
					if (m_Game->GetUser(World[x][y]->isCharIndex())->GetDialog() != "") {
						float m_OffY = m_Game->GetUser(World[x][y]->isCharIndex())->GetDialogOffsetY();
						if (m_OffY < 10)
							m_Game->GetUser(World[x][y]->isCharIndex())->SetDialogOffsetY(m_OffY + 1);

						short screen_x = (ScreenX * TILE_PIXEL_WIDTH)  + ((short)floor(m_Game->GetUser(World[x][y]->isCharIndex())->GetMoveOffsetX()) + m_PixelOffsetX);
						short screen_y = (ScreenY * TILE_PIXEL_HEIGHT) + ((short)floor(m_Game->GetUser(World[x][y]->isCharIndex())->GetMoveOffsetY()) + m_PixelOffsetY);

						Draw_Text(m_Game->GetUser(World[x][y]->isCharIndex())->GetDialog(),
							screen_x + 14 - Engine_Text_Width(m_Game->GetUser(World[x][y]->isCharIndex())->GetDialog(), true) / 4,
							screen_y + m_Game->GetUser(World[x][y]->isCharIndex())->GetBody().HeadOffset.y - Engine_Text_Height(m_Game->GetUser(World[x][y]->isCharIndex())->GetDialog(), true) - (short)m_Game->GetUser(World[x][y]->isCharIndex())->GetDialogOffsetY() - 25,
							m_Game->GetUser(World[x][y]->isCharIndex())->GetDialogFontIndex(), true, m_Game->GetUser(World[x][y]->isCharIndex())->GetDialogColor());
					}
				}
			}
			ScreenX++;
		}
		ScreenY++;
	}
}

void OGERender::Char(short m_CharIndex, short m_PixelOffsetX, short m_PixelOffsetY) {
	OGEUser *m_User = m_Game->GetUser(m_CharIndex);

	bool m_Moved = false;

	if (m_User->isMoving()){
		if (m_User->GetScrollDirectionX()){
			m_User->SetMoveOffsetX(m_User->GetMoveOffsetX() + SCROLL_PIXELS_PER_FRAME_X * m_Game->Sgn(m_User->GetScrollDirectionX()) * m_Game->GetEngine()->m_timerTicksPerFrame);
			if (m_User->GetBody().Walk[m_User->GetHeading()].speed > 0.0f)
				m_User->GetBody().Walk[m_User->GetHeading()].started = true;

			m_User->GetWeapon().WeaponWalk[m_User->GetHeading()].started = true;
			m_User->GetShield().ShieldWalk[m_User->GetHeading()].started = true;

			m_Moved = true;

			if (((m_Game->Sgn(m_User->GetScrollDirectionX()) == 1) && ((m_User->GetMoveOffsetX()) >= 0.0f))
				|| ((m_Game->Sgn(m_User->GetScrollDirectionX()) == -1) && ((m_User->GetMoveOffsetX()) <= 0.0f))){
				m_User->SetMoveOffsetX(0.0f);
				m_User->SetScrollDirectionX(0);
			}
		}

		if (m_User->GetScrollDirectionY()) {
			m_User->SetMoveOffsetY(m_User->GetMoveOffsetY() + SCROLL_PIXELS_PER_FRAME_Y * m_Game->Sgn(m_User->GetScrollDirectionY()) * m_Game->GetEngine()->m_timerTicksPerFrame);
			if (m_User->GetBody().Walk[m_User->GetHeading()].speed > 0.0f)
				m_User->GetBody().Walk[m_User->GetHeading()].started = true;

			m_User->GetWeapon().WeaponWalk[m_User->GetHeading()].started = true;
			m_User->GetShield().ShieldWalk[m_User->GetHeading()].started = true;

			m_Moved = true;

			if (((m_Game->Sgn(m_User->GetScrollDirectionY()) == 1) && (m_User->GetMoveOffsetY() >= 0.0f))
				|| ((m_Game->Sgn(m_User->GetScrollDirectionY()) == -1) && (m_User->GetMoveOffsetY() <= 0.0f))) {
				m_User->SetMoveOffsetY(0.0f);
				m_User->SetScrollDirectionY(0);
			}
		}
	}

	if (!m_Moved){
		m_User->GetBody().Walk[m_User->GetHeading()].started = false;
		m_User->GetBody().Walk[m_User->GetHeading()].frameCounter = 1;

		m_User->GetWeapon().WeaponWalk[m_User->GetHeading()].started = false;
		m_User->GetWeapon().WeaponWalk[m_User->GetHeading()].frameCounter = 1;

		m_User->GetShield().ShieldWalk[m_User->GetHeading()].started = false;
		m_User->GetShield().ShieldWalk[m_User->GetHeading()].frameCounter = 1;

		m_User->SetMoving(0);
	}

	m_PixelOffsetX += (short)floor(m_User->GetMoveOffsetX());
	m_PixelOffsetY += (short)floor(m_User->GetMoveOffsetY());

	if (!m_User->isInvisible()) {
		if (m_User->GetBody().Walk[m_User->GetHeading()].grhIndex)
			DrawGrh(m_User->GetBody().Walk[m_User->GetHeading()], m_PixelOffsetX, m_PixelOffsetY, true, true, false);

		if (m_User->GetHead().Head[m_User->GetHeading()].grhIndex)
			DrawGrh(m_User->GetHead().Head[m_User->GetHeading()], m_PixelOffsetX, m_PixelOffsetY + m_User->GetBody().HeadOffset.y, true, true, false);

		if (m_User->GetHelmet().Head[m_User->GetHeading()].grhIndex)
			DrawGrh(m_User->GetHelmet().Head[m_User->GetHeading()], m_PixelOffsetX, m_PixelOffsetY + m_User->GetBody().HeadOffset.y - 34, true, true, false);

		if (m_User->GetWeapon().WeaponWalk[m_User->GetHeading()].grhIndex)
			DrawGrh(m_User->GetWeapon().WeaponWalk[m_User->GetHeading()], m_PixelOffsetX, m_PixelOffsetY, true, true, false);

		if (m_User->GetShield().ShieldWalk[m_User->GetHeading()].grhIndex)
			DrawGrh(m_User->GetShield().ShieldWalk[m_User->GetHeading()], m_PixelOffsetX, m_PixelOffsetY, true, true, false);

		if (m_User->GetName() != "") {
			std::string m_Line = m_User->GetName();
			Draw_Text(m_User->GetName(), (m_PixelOffsetX + 16) - Engine_Text_Width(m_Line, false) / 2, m_PixelOffsetY + 30, 1, false, -1);
		}
	}
}

int OGERender::Engine_Text_Width(std::string text, bool multi_line){
	unsigned char a = 0, b, d, e, f;
	int width_text = 0;
	short grhIndex;
	d = 0;
	if (!multi_line){
		for (a = 0; a < strlen(text.c_str()); a++){
			b = text[a];
			if (b > 255) b = 0;
			grhIndex = m_Game->GetData()->m_Fonts[1].ascii_code[b];
			if ((b != 32) && (b != 5) && (b != 129) && (b != 9) && (b != 4) && (b != 255) && (b != 2) && (b != 151) && (b != 152)){
				if (grhIndex <= 0){
					width_text += 5;
				}
				else{
					width_text += m_Game->GetGrh(m_Game->GetGrh(grhIndex).frames[1]).pixelWidth; //+1
				}
			}
			else{
				width_text += 4;
			}
		}
	}
	else{
		e = 0;
		f = 0;
		for (a = 0; a < strlen(text.c_str()); a++){
			b = text[a];
			if (b > 255) b = 0;
			grhIndex = m_Game->GetData()->m_Fonts[1].ascii_code[b];
			if ((b == 32) || (b == 13)){
				if (e >= 20){
					f++;
					e = 0;
					d = 0;
				}
				else{
					if (b == 32) d += 4;
				}
			}
			else{
				if (grhIndex > 12){
					d += m_Game->GetGrh(m_Game->GetGrh(grhIndex).frames[1]).pixelWidth; //+1
					if (d > width_text) width_text = d;
				}
			}
		}
	}
	return width_text;
}

int OGERender::Engine_Text_Height(std::string text, bool multi_line){
	unsigned char a, b = 0, d, e, f;
	int height_text = 0;
	d = 0;
	if (!multi_line){
		height_text = 0;
	}
	else{
		e = 0;
		f = 0;
		for (a = 0; a < strlen(text.c_str()); a++){
			b = (int)text[a];
			if (b > 255) b = 0;
			if ((b == 32) || (b == 13)){
				if (e >= 20){
					f++;
					e = 0;
					d = 0;
				}
				else{
					if (b == 32) d += 4;
				}
			}
			e++;
		}
		height_text = f * 14;
	}

	return height_text;
}

void OGERender::Draw_Text(std::string text, short x, short y, int font_index, bool multi_line, int colortexto){
	unsigned char a, b = 0, d, e, f;
	short grhIndex;
	if (text == "") return;
	d = 0;
	if (!multi_line){
		for (a = 0; a < strlen(text.c_str()); a++){
			b = text[a];
			if (b > 255) b = 0;
			grhIndex = m_Game->GetData()->m_Fonts[font_index].ascii_code[b];
			if (b != 32){
				if (grhIndex != 0){
					//mega sombra O-matica
					grhIndex = (m_Game->GetData()->m_Fonts[font_index].ascii_code[b] + 100);
					Draw_GrhIndex(grhIndex, (x + d) + 1, y + 1, colortexto);
					grhIndex = (m_Game->GetData()->m_Fonts[font_index].ascii_code[b]);
					Draw_GrhIndex(grhIndex, (x + d) + 1, y, colortexto);
					d += m_Game->GetGrh(m_Game->GetGrh(grhIndex).frames[1]).pixelWidth;
				}
			}
			else{
				d += 4;
			}
		}
	}
	else{
		e = 0;
		f = 0;
		for (a = 0; a < strlen(text.c_str()); a++){
			b = (int)text[a];
			grhIndex = m_Game->GetData()->m_Fonts[1].ascii_code[b];
			if (b > 255) b = 0;
			if (b == 32 || b == 13){
				if (e >= 20){
					f++;
					e = 0;
					d = 0;
				}
				else{
					if (b == 32) d = d + 4;
				}
			}
			else{
				if (grhIndex > 12){
					grhIndex = m_Game->GetData()->m_Fonts[font_index].ascii_code[b] + 100;
					Draw_GrhIndex(grhIndex, (x + d) + 1, y + 1 + f * 14, colortexto);

					grhIndex = m_Game->GetData()->m_Fonts[font_index].ascii_code[b];
					Draw_GrhIndex(grhIndex, (x + d), y + f * 14, colortexto);
					d += m_Game->GetGrh(m_Game->GetGrh(grhIndex).frames[1]).pixelWidth;
				}
			}
			e++;
		}
	}
}