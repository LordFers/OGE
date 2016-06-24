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
#include "OGEData.hpp"

using namespace std;

OGEData::OGEData(OGEDeclares *m_Declares) {
	this->m_Declares = m_Declares;
	LoadGrh();
	LoadBodys();
	LoadHeads();
	LoadHelmets();
	LoadShields();
	LoadWeapons();
	LoadFXs();
	LoadFonts();
	LoadFontsConsole();
}

void OGEData::LoadGrh(){
	ifstream file("resources/inits/graphics.ind", ios::in | ios::binary | ios::ate);
	if (!file.is_open()){
		MessageBox(NULL, L"Don't exist the file 'graphics.ind'.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	int grhCount = 0, Grh = 0, tempint = 0;
	float tempfloat; short tempshort;

	file.seekg(0, ios::beg);
	file.read((char *)&tempint, 4);
	file.read((char *)&grhCount, 4);

	m_GrhData = new GRHDATA[grhCount];
	m_Declares->SetNumGrhs(grhCount);

	while (Grh < grhCount){
		file.read((char *)&tempint, 4);
		Grh = tempint;

		file.read((char *)&tempint, 2);
		m_GrhData[Grh].numFrames = tempint;

		if (m_GrhData[Grh].numFrames <= 0){
			MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR);
			return;
		}

		m_GrhData[Grh].frames = new int[m_GrhData[Grh].numFrames + 1];
		if (m_GrhData[Grh].numFrames > 1){
			for (int frame = 1; frame <= m_GrhData[Grh].numFrames; frame++){
				file.read((char *)&tempint, 4);
				m_GrhData[Grh].frames[frame] = tempint;
				if (m_GrhData[Grh].frames[frame] <= 0){
					MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR);
					return;
				}
			}

			file.read((char *)&tempfloat, 4);
			if (tempfloat <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }
			m_GrhData[Grh].speed = tempfloat;

			m_GrhData[Grh].pixelHeight = m_GrhData[m_GrhData[Grh].frames[1]].pixelHeight;
			if (m_GrhData[Grh].pixelHeight <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }
			m_GrhData[Grh].pixelWidth = m_GrhData[m_GrhData[Grh].frames[1]].pixelWidth;
			if (m_GrhData[Grh].pixelWidth <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }
			m_GrhData[Grh].tileWidth = m_GrhData[m_GrhData[Grh].frames[1]].tileWidth;
			if (m_GrhData[Grh].tileWidth <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }
			m_GrhData[Grh].tileHeight = m_GrhData[m_GrhData[Grh].frames[1]].tileHeight;
			if (m_GrhData[Grh].tileHeight <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }
		}
		else{
			file.read((char *)&tempint, 4);
			m_GrhData[Grh].filenum = tempint;
			if (m_GrhData[Grh].filenum <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }

			file.read((char *)&tempshort, 2);
			m_GrhData[Grh].sX = tempshort;
			if (m_GrhData[Grh].sX < 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }

			file.read((char *)&tempshort, 2);
			m_GrhData[Grh].sY = tempshort;
			if (m_GrhData[Grh].sY < 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }

			file.read((char *)&tempshort, 2);
			m_GrhData[Grh].pixelWidth = tempshort;
			if (m_GrhData[Grh].pixelWidth <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }

			file.read((char *)&tempshort, 2);
			m_GrhData[Grh].pixelHeight = tempshort;
			if (m_GrhData[Grh].pixelHeight <= 0) { MessageBox(NULL, L"Error loading a Grh in LoadGrhData.", L"Argentum Online", MB_OK | MB_ICONERROR); return; }

			m_GrhData[Grh].tileWidth = (float)m_GrhData[Grh].pixelWidth / 32;
			m_GrhData[Grh].tileHeight = (float)m_GrhData[Grh].pixelHeight / 32;

			m_GrhData[Grh].frames[1] = Grh;
		}
	}

	file.close();
}

void OGEData::LoadBodys(){
	char cabecera[263];
	ifstream file("resources/inits/bodys.ind", ios::in | ios::binary | ios::ate);

	if (!file.is_open()){
		MessageBox(NULL, L"Error loading a Body in LoadBodys.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short numBodys;

	file.seekg(0, ios::beg);
	file.read((char *)&cabecera, sizeof(cabecera));
	file.read((char *)&numBodys, 2);

	m_BodyData = new BODYDATA[numBodys + 1];
	INDEXBODYS *myBodys = new INDEXBODYS[numBodys + 1];
	m_Declares->SetNumBodys(numBodys);

	for (int i = 1; i <= numBodys; i++){

		for (int j = 1; j <= 4; ++j)
			file.read((char *)&myBodys[i].Body[j], 2);

		file.read((char *)&myBodys[i].HeadOffsetX, 2);
		file.read((char *)&myBodys[i].HeadOffsetY, 2);

		if (myBodys[i].Body[1] != 0){
			for (int j = 1; j <= 4; ++j)
				InitGrh(m_BodyData[i].Walk[j], myBodys[i].Body[j], false);

			m_BodyData[i].HeadOffset.x = myBodys[i].HeadOffsetX;
			m_BodyData[i].HeadOffset.y = myBodys[i].HeadOffsetY;
		}
	}

	for (int j = 1; j <= 4; ++j)
		InitGrh(m_BodyData[0].Walk[j], 0, false);

	m_BodyData[0].HeadOffset.x = 0;
	m_BodyData[0].HeadOffset.y = 0;

	delete [] myBodys;
	file.close();
}

void OGEData::LoadHeads(){
	char cabecera[263];
	ifstream file("resources/inits/heads.ind", ios::in | ios::binary | ios::ate);

	if (!file.is_open()){
		MessageBox(NULL, L"Error loading a Head in LoadHeads.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short numHeads;

	file.seekg(0, ios::beg);
	file.read((char *)&cabecera, sizeof(cabecera));
	file.read((char *)&numHeads, 2);

	m_HeadData = new HEADDATA[numHeads + 1];
	INDEXHEADS *myHeads = new INDEXHEADS[numHeads + 1];
	m_Declares->SetNumHeads(numHeads);

	for (int i = 1; i <= numHeads; i++){
		for (int j = 1; j <= 4; ++j)
			file.read((char *)&myHeads[i].Head[j], 2);

		if (myHeads[i].Head[1] != 0){
			for (int j = 1; j <= 4; ++j)
				InitGrh(m_HeadData[i].Head[j], myHeads[i].Head[j], false);
		}
	}
	for (int j = 1; j <= 4; ++j)
		InitGrh(m_HeadData[0].Head[j], 0, false);

	delete [] myHeads;
	file.close();
}

void OGEData::LoadHelmets(){
	char cabecera[263];
	ifstream file("resources/inits/helmets.ind", ios::in | ios::binary | ios::ate);

	if (!file.is_open()){
		MessageBox(NULL, L"Error loading a Helmet in LoadHelmets.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short numHelmets;

	file.seekg(0, ios::beg);
	file.read((char *)&cabecera, sizeof(cabecera));
	file.read((char *)&numHelmets, 2);

	m_HelmetData = new HEADDATA[numHelmets + 1];
	INDEXHEADS *myHeads = new INDEXHEADS[numHelmets + 1];
	m_Declares->SetNumHelmets(numHelmets);

	for (int i = 1; i <= numHelmets; i++){
		for (int j = 1; j <= 4; ++j)
			file.read((char *)&myHeads[i].Head[j], 2);

		if (myHeads[i].Head[1] != 0){
			for (int j = 1; j <= 4; ++j)
				InitGrh(m_HelmetData[i].Head[j], myHeads[i].Head[j], false);
		}
	}

	for (int j = 1; j <= 4; ++j)
		InitGrh(m_HelmetData[0].Head[j], 0, false);

	delete [] myHeads;
	file.close();
}

void OGEData::LoadShields(){
	ifstream file("resources/inits/shields.ind", ios::in | ios::binary | ios::ate);

	if (!file.is_open())
	{
		MessageBox(NULL, L"Error loading a Shield in LoadShields.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short numShields;

	file.seekg(0, ios::beg);
	file.read((char *)&numShields, 2);

	m_ShieldData = new SHIELDDATA[numShields + 1];
	m_Declares->SetNumShields(numShields);

	for (int i = 1; i <= numShields; i++){
		for (int j = 1; j <= 4; ++j) {
			file.read((char *)&m_ShieldData[i].ShieldWalk[j].grhIndex, 2);
			InitGrh(m_ShieldData[i].ShieldWalk[j], m_ShieldData[i].ShieldWalk[j].grhIndex, false);
		}
	}

	for (int j = 1; j <= 4; ++j)
		InitGrh(m_ShieldData[0].ShieldWalk[j], 0, false);

	file.close();
}

void OGEData::LoadWeapons(){
	ifstream file("resources/inits/weapons.ind", ios::in | ios::binary | ios::ate);

	if (!file.is_open()){
		MessageBox(NULL, L"Error loading a Weapon in LoadWeapons.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short numWeapons;

	file.seekg(0, ios::beg);
	file.read((char *)&numWeapons, 2);

	m_WeaponData = new WEAPONDATA[numWeapons + 1];
	m_Declares->SetNumWeapons(numWeapons);

	for (int i = 1; i <= numWeapons; i++){
		for (int j = 1; j <= 4; ++j) {
			file.read((char *)&m_WeaponData[i].WeaponWalk[j].grhIndex, 2);
			InitGrh(m_WeaponData[i].WeaponWalk[j], m_WeaponData[i].WeaponWalk[j].grhIndex, false);
		}
	}

	for (int j = 1; j <= 4; ++j)
		InitGrh(m_WeaponData[0].WeaponWalk[j], 0, false);

	file.close();
}

void OGEData::LoadFXs(){
	char cabecera[263];
	ifstream file("resources/inits/fxs.ind", ios::in | ios::binary | ios::ate);

	if (!file.is_open()){
		MessageBox(NULL, L"Error loading a FXs in LoadFXs.", L"Argentum Online", MB_OK | MB_ICONERROR);
		return;
	}

	short NumFXs;

	file.seekg(0, ios::beg);
	file.read((char *)&cabecera, sizeof(cabecera));
	file.read((char *)&NumFXs, 2);

	m_FXData = new FXDATA[NumFXs + 1];
	m_Declares->SetNumFXs(NumFXs);

	for (int i = 1; i <= NumFXs; i++){
		file.read((char *)&m_FXData[i].Animation, 2);
		file.read((char *)&m_FXData[i].OffsetX, 2);
		file.read((char *)&m_FXData[i].OffsetY, 2);
	}

	m_FXData[0].Animation = 0;
	m_FXData[0].OffsetX = 0;
	m_FXData[0].OffsetY = 0;

	file.close();
}

void OGEData::LoadFonts(){
	m_Fonts = new FONT[3];
	m_Fonts[0].ascii_code = new short[256];
	m_Fonts[1].ascii_code = new short[256];
	m_Fonts[2].ascii_code = new short[256];

	m_Fonts[0].font_size = 0;
	m_Fonts[1].font_size = 0;
	m_Fonts[2].font_size = 0;

	for (short i = 0; i < 256; ++i) for (char j = 0; j < 3; ++j)
		m_Fonts[j].ascii_code[i] = 0;

	int a;
	m_Fonts[1].font_size = 9;
	m_Fonts[1].ascii_code[48] = 23703;
	m_Fonts[1].ascii_code[49] = 23704;
	m_Fonts[1].ascii_code[50] = 23705;
	m_Fonts[1].ascii_code[51] = 23706;
	m_Fonts[1].ascii_code[52] = 23707;
	m_Fonts[1].ascii_code[53] = 23708;
	m_Fonts[1].ascii_code[54] = 23709;
	m_Fonts[1].ascii_code[55] = 23710;
	m_Fonts[1].ascii_code[56] = 23711;
	m_Fonts[1].ascii_code[57] = 23712;

	for (a = 0; a <= 25; a++)
		m_Fonts[1].ascii_code[a + 97] = 23651 + a;

	for (a = 0; a <= 25; a++)
		m_Fonts[1].ascii_code[a + 65] = 23677 + a;

	m_Fonts[1].ascii_code[33] = 23713;
	m_Fonts[1].ascii_code[161] = 23714;
	m_Fonts[1].ascii_code[34] = 23715;
	m_Fonts[1].ascii_code[36] = 23716;
	m_Fonts[1].ascii_code[191] = 23717;
	m_Fonts[1].ascii_code[35] = 23718;
	m_Fonts[1].ascii_code[36] = 23719;
	m_Fonts[1].ascii_code[37] = 23720;
	m_Fonts[1].ascii_code[38] = 23721;
	m_Fonts[1].ascii_code[47] = 23722;
	m_Fonts[1].ascii_code[92] = 23723;
	m_Fonts[1].ascii_code[40] = 23724;
	m_Fonts[1].ascii_code[41] = 23725;
	m_Fonts[1].ascii_code[61] = 23726;
	m_Fonts[1].ascii_code[39] = 23727;
	m_Fonts[1].ascii_code[123] = 23728;
	m_Fonts[1].ascii_code[125] = 23729;
	m_Fonts[1].ascii_code[95] = 23730;
	m_Fonts[1].ascii_code[45] = 23731;
	m_Fonts[1].ascii_code[63] = 23716;
	m_Fonts[1].ascii_code[64] = 23732;
	m_Fonts[1].ascii_code[94] = 23733;
	m_Fonts[1].ascii_code[91] = 23734;
	m_Fonts[1].ascii_code[93] = 23735;
	m_Fonts[1].ascii_code[60] = 23736;
	m_Fonts[1].ascii_code[62] = 23737;
	m_Fonts[1].ascii_code[42] = 23738;
	m_Fonts[1].ascii_code[43] = 23739;
	m_Fonts[1].ascii_code[46] = 23740;
	m_Fonts[1].ascii_code[44] = 23741;
	m_Fonts[1].ascii_code[58] = 23742;
	m_Fonts[1].ascii_code[59] = 23743;
	m_Fonts[1].ascii_code[124] = 23744;
	/////////////////
	m_Fonts[1].ascii_code[252] = 23845;
	m_Fonts[1].ascii_code[220] = 23846;
	m_Fonts[1].ascii_code[225] = 23847;
	m_Fonts[1].ascii_code[233] = 23848;
	m_Fonts[1].ascii_code[237] = 23849;
	m_Fonts[1].ascii_code[243] = 23850;
	m_Fonts[1].ascii_code[250] = 23851;
	m_Fonts[1].ascii_code[253] = 23852;
	m_Fonts[1].ascii_code[193] = 23853;
	m_Fonts[1].ascii_code[201] = 23854;
	m_Fonts[1].ascii_code[205] = 23855;
	m_Fonts[1].ascii_code[211] = 23856;
	m_Fonts[1].ascii_code[218] = 23857;
	m_Fonts[1].ascii_code[221] = 23858;
	m_Fonts[1].ascii_code[224] = 23859;
	m_Fonts[1].ascii_code[232] = 23860;
	m_Fonts[1].ascii_code[236] = 23861;
	m_Fonts[1].ascii_code[242] = 23862;
	m_Fonts[1].ascii_code[249] = 23863;
	m_Fonts[1].ascii_code[192] = 23864;
	m_Fonts[1].ascii_code[200] = 23865;
	m_Fonts[1].ascii_code[204] = 23866;
	m_Fonts[1].ascii_code[210] = 23867;
	m_Fonts[1].ascii_code[217] = 23868;
	m_Fonts[1].ascii_code[195] = 23869;
	m_Fonts[1].ascii_code[241] = 23869;
	m_Fonts[1].ascii_code[209] = 23870;

	m_Fonts[1].ascii_code[196] = 23970;
	m_Fonts[1].ascii_code[194] = 23971;
	m_Fonts[1].ascii_code[203] = 23972;
	m_Fonts[1].ascii_code[207] = 23973;
	m_Fonts[1].ascii_code[214] = 23974;
	m_Fonts[1].ascii_code[212] = 23975;

	m_Fonts[1].ascii_code[172] = 23975;
	//
	m_Fonts[2].font_size = 9;
	m_Fonts[2].ascii_code[97] = 24076;
	m_Fonts[2].ascii_code[108] = 24077;
	m_Fonts[2].ascii_code[115] = 24078;
	m_Fonts[2].ascii_code[70] = 24079;
	m_Fonts[2].ascii_code[48] = 24080;
	m_Fonts[2].ascii_code[49] = 24081;
	m_Fonts[2].ascii_code[50] = 24082;
	m_Fonts[2].ascii_code[51] = 24083;
	m_Fonts[2].ascii_code[52] = 24084;
	m_Fonts[2].ascii_code[53] = 24085;
	m_Fonts[2].ascii_code[54] = 24086;
	m_Fonts[2].ascii_code[55] = 24087;
	m_Fonts[2].ascii_code[56] = 24088;
	m_Fonts[2].ascii_code[57] = 24089;
	m_Fonts[2].ascii_code[33] = 24090;
	m_Fonts[2].ascii_code[161] = 24091;
	m_Fonts[2].ascii_code[42] = 24092;
}

void OGEData::LoadFontsConsole() {
	m_FontTypes = new CFONT[20];
	//FONTTYPE_TALK
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_TALK].m_Color = -1;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_TALK].m_Bold = false;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_TALK].m_Italic = false;

	//FONTTYPE_FIGHT
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_FIGHT].m_Color = 0xffff;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_FIGHT].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_FIGHT].m_Italic = false;

	//FONTTYPE_WARNING
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_WARNING].m_Color = 0xff2033df;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_WARNING].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_WARNING].m_Italic = true;

	//FONTTYPE_INFO
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFO].m_Color = 0xff41be9c;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFO].m_Bold = false;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFO].m_Italic = false;

	//FONTTYPE_INFOBOLD
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFOBOLD].m_Color = 0xff41be9c;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFOBOLD].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_INFOBOLD].m_Italic = false;

	//FONTTYPE_EJECUCION
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_EJECUCION].m_Color = 0xff828282;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_EJECUCION].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_EJECUCION].m_Italic = false;

	//FONTTYPE_PARTY
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_PARTY].m_Color = 0xffffb4fa;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_PARTY].m_Bold = false;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_PARTY].m_Italic = false;

	//FONTTYPE_VENENO
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_VENENO].m_Color = 0xff00ff;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_VENENO].m_Bold = false;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_VENENO].m_Italic = false;

	//FONTTYPE_GUILD
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILD].m_Color = -1;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILD].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILD].m_Italic = false;

	//FONTTYPE_SERVER
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_SERVER].m_Color = 0xff00b9;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_SERVER].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_SERVER].m_Italic = false;

	//FONTTYPE_GUILDMSG
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILDMSG].m_Color = 0xffe4c71b;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILDMSG].m_Bold = false;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GUILDMSG].m_Italic = false;

	//FONTTYPE_CONSEJO
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJO].m_Color = 0xff8282ff;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJO].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJO].m_Italic = false;

	//FONTTYPE_CONSEJOCAOS
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOS].m_Color = 0xffff3c;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOS].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOS].m_Italic = false;

	//FONTTYPE_CONSEJOVesA
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOVesA].m_Color = 0xffc8ff;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOVesA].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOVesA].m_Italic = false;

	//FONTTYPE_CONSEJOCAOSVesA
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOSVesA].m_Color = 0xffff32;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOSVesA].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSEJOCAOSVesA].m_Italic = false;

	//FONTTYPE_CENTINELA
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CENTINELA].m_Color = 0xff00ff;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CENTINELA].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CENTINELA].m_Italic = false;

	//FONTTYPE_GMMSG
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GMMSG].m_Color = -1;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GMMSG].m_Bold = false;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GMMSG].m_Italic = true;

	//FONTTYPE_GM
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GM].m_Color = 0xff1eff1e;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GM].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_GM].m_Italic = false;

	//FONTTYPE_CITIZEN
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CITIZEN].m_Color = 0xff0000c8;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CITIZEN].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CITIZEN].m_Italic = false;

	//FONTTYPE_CONSE
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSE].m_Color = 0xff1e961e;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSE].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_CONSE].m_Italic = false;

	//FONTTYPE_DIOS
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_DIOS].m_Color = 0xfffafa96;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_DIOS].m_Bold = true;
	m_FontTypes[FontTypeNames::FontTypeNames_FONTTYPE_DIOS].m_Italic = false;
}

void OGEData::InitGrh(GRH &Grh, short m_GrhIndex, bool m_Started){
	Grh.grhIndex = m_GrhIndex;
	Grh.frameCounter = 1;

	if (m_Started){
		if (m_GrhData[Grh.grhIndex].numFrames > 1){
			Grh.started = true;
		}
		else{
			Grh.started = false;
		}
	}
	else{
		m_Started = true; //REVISAR ESTO
		if (m_GrhData[Grh.grhIndex].numFrames == 1) m_Started = false;
		Grh.started = m_Started;
	}

	if (Grh.started){
		Grh.loops = -1;
	}
	else{
		Grh.loops = 0;
	}

	Grh.frameCounter = 1;
	Grh.speed = m_GrhData[Grh.grhIndex].speed;
}