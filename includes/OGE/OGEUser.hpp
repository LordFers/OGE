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
#ifndef _H_OGEUSER_
#define _H_OGEUSER_
#include "stdafx.hpp"
#include "OGEGame.hpp"

class OGEUser {
	public:
		OGEUser::OGEUser(char m_Heading, std::string m_Name, short m_posX, short m_posY, BODYDATA m_Body, HEADDATA m_Head, HEADDATA m_Helmet, WEAPONDATA m_Weapon, SHIELDDATA m_Shield);

	public:
		inline bool OGEUser::isInvisible() { return this->m_Invisible; }
		inline char OGEUser::isMoving() { return this->m_Moving; }
		inline char OGEUser::isActive() { return this->m_Active; }
		inline bool OGEUser::isDead() { return this->m_Dead; }

	public:
		inline int OGEUser::GetPosX() { return this->m_Position.x; }
		inline int OGEUser::GetPosY() { return this->m_Position.y; }
		inline short OGEUser::GetScrollDirectionX() { return this->m_scrollDirectionX; }
		inline short OGEUser::GetScrollDirectionY() { return this->m_scrollDirectionY; }
		inline float OGEUser::GetMoveOffsetX() { return this->m_MoveOffsetX; }
		inline float OGEUser::GetMoveOffsetY() { return this->m_MoveOffsetY; }
		inline char OGEUser::GetPrivilegios() { return this->m_Priv; }

	public:
		inline BODYDATA &OGEUser::GetBody() { return this->m_Body; }
		inline HEADDATA &OGEUser::GetHead() { return this->m_Head; }
		inline HEADDATA &OGEUser::GetHelmet() { return this->m_Helmet; }
		inline SHIELDDATA &OGEUser::GetShield() { return this->m_Shield; }
		inline WEAPONDATA &OGEUser::GetWeapon() { return this->m_Weapon; }
		inline GRH &OGEUser::GetFX() { return this->m_FX; }
		inline std::string OGEUser::GetName() { return this->m_Name; }
		inline short OGEUser::GetFXIndex() { return this->m_FXIndex; }
		inline short OGEUser::GetBodyIndex() { return this->m_BodyIndex; }
		inline short OGEUser::GetHeadIndex() { return this->m_HeadIndex; }
		inline char OGEUser::GetHeading() { return this->m_Heading; }
		inline bool OGEUser::GetPie() { return this->m_Pie; }
		inline std::string OGEUser::GetDialog() { return this->m_Dialog; }
		inline short OGEUser::GetDialogLife() { return this->m_DialogLife; }
		inline float OGEUser::GetDialogOffsetY() { return this->m_OffsetCounterY; }
		inline short OGEUser::GetDialogFontIndex() { return this->m_Dialog_iFont; }
		inline int OGEUser::GetDialogColor() { return this->m_DialogColor; }
		//inline void OGEUser::GetDialog(std::string &m_Dialog, int &m_Color) { m_Dialog = this->m_Dialog; m_Color = this->m_DialogColor; }

	public:
		void OGEUser::SetChar(std::string m_Name, BODYDATA m_Body, HEADDATA m_Head, HEADDATA m_Helmet, WEAPONDATA m_Weapon, SHIELDDATA m_Shield);
		void OGEUser::SetDialog(std::string m_Dialog, int m_Color, short m_iFont, short m_Life, float m_OffsetCounterY);
		void OGEUser::ResetChar();

	public:
		inline void OGEUser::SetBody(BODYDATA m_Body) { this->m_Body = m_Body; }
		inline void OGEUser::SetHead(HEADDATA m_Head) { this->m_Head = m_Head; }
		inline void OGEUser::SetHelmet(HEADDATA m_Helmet) { this->m_Helmet = m_Helmet; }
		inline void OGEUser::SetShield(SHIELDDATA m_Shield) { this->m_Shield = m_Shield; }
		inline void OGEUser::SetWeapon(WEAPONDATA m_Weapon) { this->m_Weapon = m_Weapon; }
		inline void OGEUser::SetFX(GRH m_FX) { this->m_FX = m_FX; }
		inline void OGEUser::SetFXIndex(short m_FXIndex) { this->m_FXIndex = m_FXIndex; }
		inline void OGEUser::SetBodyIndex(short m_BodyIndex) { this->m_BodyIndex = m_BodyIndex; }
		inline void OGEUser::SetHeadIndex(short m_HeadIndex) { this->m_HeadIndex = m_HeadIndex; }

	public:
		inline void OGEUser::SetDialogLife(short m_Life) { this->m_DialogLife = m_Life; }
		inline void OGEUser::SetDialogOffsetY(float m_OffsetCounterY) { this->m_OffsetCounterY = m_OffsetCounterY; }
		inline void OGEUser::SetPosition(int m_X, int m_Y) { this->m_Position.x = m_X; this->m_Position.y = m_Y; }
		inline void OGEUser::SetInvisible(bool m_Invisible) { this->m_Invisible = m_Invisible; }
		inline void OGEUser::SetMoveOffsetX(float m_MoveOffsetX) { this->m_MoveOffsetX = m_MoveOffsetX; }
		inline void OGEUser::SetMoveOffsetY(float m_MoveOffsetY) { this->m_MoveOffsetY = m_MoveOffsetY; }
		inline void OGEUser::SetScrollDirectionX(short m_DirectionX) { this->m_scrollDirectionX = m_DirectionX; }
		inline void OGEUser::SetScrollDirectionY(short m_DirectionY) { this->m_scrollDirectionY = m_DirectionY; }
		inline void OGEUser::SetHeading(char m_Heading) { this->m_Heading = m_Heading; }
		inline void OGEUser::SetMoving(char m_Moving) { this->m_Moving = m_Moving; }
		inline void OGEUser::SetPrivilegios(char m_Priv) { this->m_Priv = m_Priv; }
		inline void OGEUser::SetActive(char m_Active) { this->m_Active = m_Active; }
		inline void OGEUser::SetDead(bool m_Dead) { this->m_Dead = m_Dead; }
		inline void OGEUser::SetPie(bool m_Pie) { this->m_Pie = m_Pie; }

	private:
		char m_Active;
		char m_Heading;
		char m_Criminal;
		char m_Moving;
		char m_Priv;

	private:
		POSITION m_Position;
		BODYDATA m_Body;
		HEADDATA m_Head;
		HEADDATA m_Helmet;
		WEAPONDATA m_Weapon;
		SHIELDDATA m_Shield;
		GRH m_FX;

	private:
		bool m_UsingArm;
		bool m_Attackable;
		bool m_Pie;
		bool m_Dead;
		bool m_Invisible;

	private:
		std::string m_Name;

	private:
		short m_BodyIndex;
		short m_HeadIndex;
		short m_FXIndex;
		short m_scrollDirectionX;
		short m_scrollDirectionY;

	private:
		float m_MoveOffsetX;
		float m_MoveOffsetY;

	private:
		std::string m_Dialog;
		int m_DialogColor;
		short m_DialogLife;
		short m_Dialog_iFont;
		float m_OffsetCounterY;
};
#endif