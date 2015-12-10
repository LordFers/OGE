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

#include "OGEEngine.hpp"

bool CEngineDX::Initialize(HWND hWnd, int width, int height, bool fullscreen) {
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS m_D3DWindow;
	ZeroMemory(&m_D3DWindow, sizeof(m_D3DWindow));

	m_D3DWindow.Windowed = (!fullscreen);
	m_D3DWindow.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DWindow.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	m_D3DWindow.hDeviceWindow = hWnd;
	m_D3DWindow.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_D3DWindow.BackBufferWidth = width;
	m_D3DWindow.BackBufferHeight = height;
	m_D3DWindow.EnableAutoDepthStencil = TRUE;
	m_D3DWindow.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		(D3DCREATE_HARDWARE_VERTEXPROCESSING), &m_D3DWindow, &m_pDirect3DDevice))) {
		MessageBox(NULL, L"Can't initialize Direct3DDevice in a rendering context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDirect3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pDirect3DDevice->SetFVF(FVF_CUSTOM);

	return true;
}

void CEngineDX::Render(){
	m_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();
		//RenderScene();
	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CEngineDX::RenderScene(){

}

bool CEngineOGL::Initialize(HWND hWnd, int width, int height, bool fullscreen){
	hDC = GetDC(hWnd);
	auto PixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, PixelFormat, &pfd);
	auto hRC = wglCreateContext(hDC);
	auto aspect = static_cast<GLdouble>(width) / static_cast<GLdouble>(height);

	SetPixelFormat(hDC, PixelFormat, &pfd);

	if (!wglMakeCurrent(hDC, hRC)) {
		MessageBox(NULL, L"Can't initialize the OpenGL rendering context.", L"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	glOrtho(0, static_cast<GLdouble>(width), static_cast<GLdouble>(height), 0, 1, -1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

void CEngineOGL::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//RenderScene();
	SwapBuffers(hDC);
}

void CEngineOGL::RenderScene(){

}
