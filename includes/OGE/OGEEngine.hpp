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
#ifndef _H_OGEENGINE_
#define _H_OGEENGINE_
#include "stdafx.hpp"
#include "OGED3DDevice.hpp"
#include "OGETextures.hpp"
#include "OGERender.hpp"
#include "OGEGUI.hpp"

class OGERender;
class OGEGUI;

class OGEEngine {
	public:
		bool OGEEngine::Initialize(HWND m_hWnd, int m_Width, int m_Height, bool m_FScreen);
		void OGEEngine::Render();

	public:
		inline OGERender *OGEEngine::GetRender() { return this->m_Render; }
		inline OGEGUI		*OGEEngine::GetGUI() { return this->m_GUI; }
		inline void OGEEngine::SetRender(OGERender *m_Render) { this->m_Render = m_Render; }
		inline void OGEEngine::setRun(bool run) { this->m_Run = run; }
		inline bool OGEEngine::IsRun() { return this->m_Run; }

	public:
		void OGEEngine::VertexTexture(int m_FileNum, short m_X, short m_Y, short m_Width, short m_Height, short m_sX, short m_sY, bool m_Blend, int m_Color);

	private:
		LPDIRECT3D9				m_pDirect3D;
		LPDIRECT3DDEVICE9		m_pDirect3DDevice;
		IDirect3DStateBlock9    *m_D3DStateBlock;

	private: //Classes:
		OGED3DDevice			*m_Device;
		OGETextures				*m_Textures;

	private:
		typedef struct {
			D3DXVECTOR4 m_Position;
			UINT m_Color;
			D3DXVECTOR2 m_TexCoords;
		} VERTEX;

		VERTEX m_Vertices[4];

	private:
		void OGEEngine::SetD3DXV3VERTEX(VERTEX &m_Vertex, FLOAT x, FLOAT y, UINT color, FLOAT tu, FLOAT tv);

	public:
		float m_FPS;
		float m_FPSCounter;
		float m_lFrameTimer;

		float m_timerTicksPerFrame;
		float m_timerElapsedTime;

	protected:
		bool m_Run;
		OGERender *m_Render;
		OGEGUI		 *m_GUI;
};
#endif