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

#include "OGEDirectXDevice.hpp"

OGEDirectXDevice::OGEDirectXDevice(LPDIRECT3DDEVICE9 m_pDirect3DDevice){
	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDirect3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDirect3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pDirect3DDevice->SetFVF(FVF_CUSTOM);

	this->m_pDirect3DDevice = m_pDirect3DDevice;
}

void OGEDirectXDevice::BeginScene(){
	m_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();
}

void OGEDirectXDevice::EndScene(){
	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}
