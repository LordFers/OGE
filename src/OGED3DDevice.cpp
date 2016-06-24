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

#include "OGED3DDevice.hpp"
#include <d3dx9.h>

OGED3DDevice::OGED3DDevice(LPDIRECT3DDEVICE9 m_pDirect3DDevice, IDirect3DStateBlock9 *&m_D3DStateBlock){
	this->m_pDirect3DDevice = m_pDirect3DDevice;

	m_pDirect3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDirect3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pDirect3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_pDirect3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	m_pDirect3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDirect3DDevice->SetFVF(FVF_CUSTOM); //FVF CUSTOM
	m_pDirect3DDevice->CreateStateBlock(D3DSBT_ALL, &m_D3DStateBlock);

	Init_Light();
}

void OGED3DDevice::BeginScene(){
	m_pDirect3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0);
	m_pDirect3DDevice->BeginScene();
}

void OGED3DDevice::EndScene(){
	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present(NULL, NULL, NULL, NULL);
}

void OGED3DDevice::Blend(bool m_Bool) {
	if (m_Bool) {
		m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else {
		m_pDirect3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_pDirect3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void OGED3DDevice::Init_Light() {
	D3DLIGHT9 light;
	D3DMATERIAL9 material;

	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_POINT;    // make the light type 'point light'
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	light.Range = 100.0f;    // a range of 100
	light.Attenuation0 = 0.0f;    // no constant inverse attenuation
	light.Attenuation1 = 0.125f;    // only .125 inverse attenuation
	light.Attenuation2 = 0.0f;    // no square inverse attenuation

	m_pDirect3DDevice->SetLight(0, &light);
	m_pDirect3DDevice->LightEnable(0, TRUE);

	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_pDirect3DDevice->SetMaterial(&material);
}