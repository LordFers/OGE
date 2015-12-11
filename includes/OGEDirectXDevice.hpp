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

#ifndef _H_OGEDIRECTXDEVICE_
#define _H_OGEDIRECTXDEVICE_
#include <d3dx9.h>

#define FVF_CUSTOM (D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE)

class OGEDirectXDevice {
	public:
		OGEDirectXDevice::OGEDirectXDevice(LPDIRECT3DDEVICE9 m_pDirect3DDevice);
		void OGEDirectXDevice::BeginScene();
		void OGEDirectXDevice::EndScene();

	private:
		LPDIRECT3DDEVICE9 m_pDirect3DDevice;
};

#endif