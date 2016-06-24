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
//#ifndef _H_OGETEXTURES_
//#define _H_OGETEXTURES_

#include <d3dx9.h>
#include <map>

typedef struct {
	LPDIRECT3DTEXTURE9 pTexture; //pointer to Texture (DX9)
	int texture_width;
	int texture_height;
} TEXTURE;

class OGETextures {

	public:
		OGETextures::OGETextures(LPDIRECT3DDEVICE9 m_pDirect3DDevice) {
			this->m_pDirect3DDevice = m_pDirect3DDevice;
		}

		void OGETextures::LoadTexture(int m_File, int &m_Width, int &m_Height);
		inline LPDIRECT3DTEXTURE9 OGETextures::GetTexture() { return this->m_pTexture; }

	private:
		LPDIRECT3DDEVICE9 m_pDirect3DDevice;
		LPDIRECT3DTEXTURE9 m_pTexture;

	private:
		std::map <int, TEXTURE> TextureMap;
};

//#endif