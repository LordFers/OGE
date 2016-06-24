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
#include "OGEUser.hpp"

OGEUser::OGEUser(char m_Heading, std::string m_Name, short m_posX, short m_posY, BODYDATA m_Body, HEADDATA m_Head, HEADDATA m_Helmet, WEAPONDATA m_Weapon, SHIELDDATA m_Shield){
	ResetChar();
	SetActive(0);
	SetChar(m_Name, m_Body, m_Head, m_Helmet, m_Weapon, m_Shield);
	SetPosition(m_posX, m_posY);
	SetHeading(m_Heading);
}

void OGEUser::ResetChar() {
	this->m_Active = 0;
	this->m_Heading = 3;
	this->m_Criminal = 0;
	this->m_Moving = 0;
	this->m_Priv = 0;
	this->m_UsingArm = false;
	this->m_Attackable = false;
	this->m_Pie = false;
	this->m_Dead = false;
	this->m_Invisible = false;
	this->m_Name = "";
	this->m_FXIndex = 0;
	this->m_scrollDirectionX = 0;
	this->m_scrollDirectionY = 0;
	this->m_MoveOffsetX = 0.0f;
	this->m_MoveOffsetY = 0.0f;
	this->m_Dialog = "";
	this->m_DialogColor = -1;
	this->m_DialogLife = 0;
	this->m_Dialog_iFont = 1;
	this->m_OffsetCounterY = 0.0f;
}

void OGEUser::SetChar(std::string m_Name, BODYDATA m_Body, HEADDATA m_Head, HEADDATA m_Helmet, WEAPONDATA m_Weapon, SHIELDDATA m_Shield) {
	this->m_Name = m_Name;
	this->m_Body = m_Body;
	this->m_Head = m_Head;
	this->m_Helmet = m_Helmet;
	this->m_Weapon = m_Weapon;
	this->m_Shield = m_Shield;
	SetActive(1);
}

void OGEUser::SetDialog(std::string m_Dialog, int m_Color, short m_iFont, short m_Life, float m_OffsetCounterY){
	this->m_Dialog = m_Dialog;
	this->m_DialogColor = m_Color;
	this->m_Dialog_iFont = m_iFont;
	this->m_DialogLife = m_Life;
	this->m_OffsetCounterY = m_OffsetCounterY;
}