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

#include <d3d9.h>
#define FVF_CUSTOM ( D3DFVF_XYZRHW | D3DFVF_TEX1 | D3DFVF_DIFFUSE )
class OGED3DDevice {
	public:
		OGED3DDevice::OGED3DDevice(LPDIRECT3DDEVICE9 m_pDirect3DDevice, IDirect3DStateBlock9 *&m_D3DStateBlock);

	public:
		void OGED3DDevice::BeginScene();
		void OGED3DDevice::EndScene();
	
	public:
		void OGED3DDevice::Blend(bool m_Bool);
		void OGED3DDevice::Init_Light();

	private:
		LPDIRECT3DDEVICE9 m_pDirect3DDevice;
		IDirect3DStateBlock9* m_D3DStateBlock;
};