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
#include "OGETextures.hpp"
#include <sstream>

using namespace std;

void OGETextures::LoadTexture(int m_File, int &m_Width, int &m_Height){
	map<int, TEXTURE>::iterator iter = TextureMap.find(m_File);
	if (iter != TextureMap.end()){
		m_pTexture = TextureMap[m_File].pTexture;
		m_Width = TextureMap[m_File].texture_width;
		m_Height = TextureMap[m_File].texture_height;
		return;
	}

	stringstream filename;
	filename << "Resources/Graphics/" << m_File << ".bmp";
	string strfile = filename.str();
	const char* file = strfile.c_str();

	D3DXIMAGE_INFO texture_info;
	D3DXCreateTextureFromFileExA(m_pDirect3DDevice, file, D3DX_FROM_FILE, D3DX_FROM_FILE, 1, 0, D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xff000000, &texture_info, NULL, &m_pTexture);

	m_Width = texture_info.Width;
	m_Height = texture_info.Height;
	
	TEXTURE textura_new;
	textura_new.texture_width = m_Width;
	textura_new.texture_height = m_Height;
	textura_new.pTexture = m_pTexture;

	TextureMap.insert(pair<int, TEXTURE>(m_File, textura_new));
}