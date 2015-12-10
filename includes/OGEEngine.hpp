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

#ifndef _H_OGEENGINE_
#define _H_OGEENGINE_
#include "stdafx.hpp"

#define FVF_CUSTOM (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

class IEngine {
	public:
		virtual bool IEngine::Initialize(HWND hWnd, int width, int height, bool fullscreen) = 0;
		virtual void IEngine::Render() = 0;
		virtual void IEngine::RenderScene() = 0;
		virtual void IEngine::setRun(bool run) = 0;
		virtual bool IEngine::IsRun() = 0;
	protected:
		bool m_Run;
	};

class CEngineDX : public IEngine {
	public:
		bool CEngineDX::Initialize(HWND hWnd, int width, int height, bool fullscreen);
		void CEngineDX::Render();
		void CEngineDX::RenderScene();

	public:
		void CEngineDX::setRun(bool run) { this->m_Run = run; }
		bool CEngineDX::IsRun() { return this->m_Run; }

	private:
		LPDIRECT3D9				m_pDirect3D;
		LPDIRECT3DDEVICE9		m_pDirect3DDevice;
		LPDIRECT3DTEXTURE9		m_pDirect3DTexture;

	private:
		typedef struct {
			float x, y, z; int color; float tu, tv;
		} VERTEX;
		  VERTEX				m_Vertex[6];
};

class CEngineOGL : public IEngine {
	public:
		bool CEngineOGL::Initialize(HWND hWnd, int width, int height, bool fullscreen);
		void CEngineOGL::Render();
		void CEngineOGL::RenderScene();

	public:
		void CEngineOGL::setRun(bool run) { this->m_Run = run; }
		bool CEngineOGL::IsRun() { return this->m_Run; }

	private:
		HDC hDC;

	private:
		PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1,
			(PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER), PFD_TYPE_RGBA, 32,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
};
#endif