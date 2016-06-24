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

#ifndef _H_OGEDATA_
#define _H_OGEDATA_

#include "stdafx.hpp"
#include "OGEDeclares.hpp"

typedef struct {
	short sX, sY, pixelWidth, pixelHeight, numFrames; int filenum, *frames;
	float tileWidth, tileHeight, speed;
} GRHDATA;

typedef struct {
	short grhIndex; float frameCounter, speed, angle;
	bool started; int loops;
} GRH;

typedef struct {
	short x;
	short y;
} POSITION;

typedef struct {
	GRH Walk[4 + 1];
	POSITION HeadOffset;
} BODYDATA;

typedef struct {
	short Body[4 + 1];
	short HeadOffsetX;
	short HeadOffsetY;
} INDEXBODYS;

typedef struct {
	short Head[4 + 1];
} INDEXHEADS;

typedef struct {
	GRH Head[4 + 1];
} HEADDATA;

typedef struct {
	GRH WeaponWalk[4 + 1];
} WEAPONDATA;

typedef struct {
	GRH ShieldWalk[4 + 1];
} SHIELDDATA;

typedef struct {
	short Animation, OffsetX, OffsetY;
} FXDATA;

typedef struct {
	short objindex, amount;
} OBJ;

typedef struct{
	short font_size, *ascii_code;
} FONT;

typedef struct {
	int m_Color;
	bool m_Bold, m_Italic;
} CFONT;

enum FontTypeNames {
	FontTypeNames_FONTTYPE_TALK,
	FontTypeNames_FONTTYPE_FIGHT,
	FontTypeNames_FONTTYPE_WARNING,
	FontTypeNames_FONTTYPE_INFO,
	FontTypeNames_FONTTYPE_INFOBOLD,
	FontTypeNames_FONTTYPE_EJECUCION,
	FontTypeNames_FONTTYPE_PARTY,
	FontTypeNames_FONTTYPE_VENENO,
	FontTypeNames_FONTTYPE_GUILD,
	FontTypeNames_FONTTYPE_SERVER,
	FontTypeNames_FONTTYPE_GUILDMSG,
	FontTypeNames_FONTTYPE_CONSEJO,
	FontTypeNames_FONTTYPE_CONSEJOCAOS,
	FontTypeNames_FONTTYPE_CONSEJOVesA,
	FontTypeNames_FONTTYPE_CONSEJOCAOSVesA,
	FontTypeNames_FONTTYPE_CENTINELA,
	FontTypeNames_FONTTYPE_GMMSG,
	FontTypeNames_FONTTYPE_GM,
	FontTypeNames_FONTTYPE_CITIZEN,
	FontTypeNames_FONTTYPE_CONSE,
	FontTypeNames_FONTTYPE_DIOS
};

class OGEData {
	public:
		OGEData::OGEData(OGEDeclares *m_Declares);

	public:
		GRHDATA		*m_GrhData;
		BODYDATA	*m_BodyData;
		HEADDATA	*m_HeadData;
		HEADDATA	*m_HelmetData;
		SHIELDDATA	*m_ShieldData;
		WEAPONDATA  *m_WeaponData;
		FXDATA		*m_FXData;
		FONT		*m_Fonts;
		CFONT		*m_FontTypes;

	public:
		void OGEData::LoadGrh();
		void OGEData::LoadBodys();
		void OGEData::LoadHeads();
		void OGEData::LoadHelmets();
		void OGEData::LoadShields();
		void OGEData::LoadWeapons();
		void OGEData::LoadFXs();
		void OGEData::LoadFonts();
		void OGEData::LoadFontsConsole();

	private:
		void OGEData::InitGrh(GRH &Grh, short m_GrhIndex, bool m_Started);

	private:
		OGEDeclares *m_Declares;

};
#endif