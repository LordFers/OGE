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

#include "OGEEngine.hpp"

bool OGEEngine::Initialize(HWND m_hWnd, int m_Width, int m_Height, bool m_FScreen) {
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS m_D3DWindow;
	ZeroMemory(&m_D3DWindow, sizeof(m_D3DWindow));

	m_D3DWindow.Windowed = (!m_FScreen);
	m_D3DWindow.SwapEffect = D3DSWAPEFFECT_COPY;
	m_D3DWindow.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//D3DPRESENT_INTERVAL_ONE;
	m_D3DWindow.hDeviceWindow = m_hWnd;
	m_D3DWindow.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_D3DWindow.BackBufferWidth = m_Width;
	m_D3DWindow.BackBufferHeight = m_Height;
	m_D3DWindow.EnableAutoDepthStencil = TRUE;
	m_D3DWindow.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		(D3DCREATE_HARDWARE_VERTEXPROCESSING), &m_D3DWindow, &m_pDirect3DDevice))) {
		MessageBox(NULL, L"Can't initialize Direct3DDevice in a rendering context.", L"Direct3DDevice9", MB_OK | MB_ICONERROR);
		return false;
	}

	m_GUI = new OGEGUI(m_pDirect3DDevice);
	m_Device = new OGED3DDevice(m_pDirect3DDevice, m_D3DStateBlock);
	m_Textures = new OGETextures(m_pDirect3DDevice);
	return true;
}

void OGEEngine::Render(){
	m_Device->BeginScene();
		GetRender()->Scene();
		GetGUI()->GetSingleton()->renderAllGUIContexts();
		m_D3DStateBlock->Apply();
	m_Device->EndScene();
}

void OGEEngine::VertexTexture(int m_FileNum, short m_X, short m_Y, short m_Width, short m_Height, short m_sX, short m_sY, bool m_Blend, int m_Color){
	int m_TextWidth, m_TextHeight;
	m_Textures->LoadTexture(m_FileNum, m_TextWidth, m_TextHeight);

	auto src_right = m_sX + m_Width;
	auto src_bottom = m_sY + (m_Height);
	auto dest_right = m_X + (src_right - m_sX);
	auto dest_bottom = m_Y + (src_bottom - m_sY);
	
	SetD3DXV3VERTEX(m_Vertices[0], (FLOAT)m_X, (FLOAT)dest_bottom, m_Color, (FLOAT)m_sX / m_TextWidth, ((FLOAT)src_bottom + 1.0f) / m_TextHeight);
	SetD3DXV3VERTEX(m_Vertices[1], (FLOAT)m_X, (FLOAT)m_Y, m_Color, (FLOAT)m_sX / m_TextWidth, (FLOAT)m_sY / m_TextHeight);
	SetD3DXV3VERTEX(m_Vertices[2], (FLOAT)dest_right, (FLOAT)dest_bottom, m_Color, ((FLOAT)src_right + 1.0f) / m_TextWidth, ((FLOAT)src_bottom + 1.0f) / m_TextHeight);
	SetD3DXV3VERTEX(m_Vertices[3], (FLOAT)dest_right, (FLOAT)m_Y, m_Color, ((FLOAT)src_right + 1.0f) / m_TextWidth, (FLOAT)m_sY / m_TextHeight);

	if (m_Blend)
		m_Device->Blend(true);

	m_pDirect3DDevice->SetTexture(NULL, m_Textures->GetTexture());
	m_pDirect3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &m_Vertices, sizeof(VERTEX));

	if (m_Blend)
		m_Device->Blend(false);
}

void OGEEngine::SetD3DXV3VERTEX(VERTEX &m_Vertex, FLOAT x, FLOAT y, UINT color, FLOAT tu, FLOAT tv) {
	m_Vertex.m_Position.x = x;
	m_Vertex.m_Position.y = y;
	m_Vertex.m_Position.z = 0.0f;
	m_Vertex.m_Position.w = 1.0f;
	m_Vertex.m_Color = color;
	m_Vertex.m_TexCoords.x = tu;
	m_Vertex.m_TexCoords.y = tv;
}
