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
//#ifndef _H_OGEWORLD_
//#define _H_OGEWORLD_

#include "OGEData.hpp"

class OGEWorld {
	public:
		OGEWorld::OGEWorld() {
			this->m_CharIndex = 0;
			this->m_Blocked = 0;
			this->m_Trigger = 0;
			this->m_ObjGrh.grhIndex = 0;
			this->m_ObjInfo.objindex = 0;
			this->m_ObjInfo.amount = 0;
			for (int i = 0; i <= 4; ++i) {
				this->m_Layer[i].angle = 0.0f;
				this->m_Layer[i].grhIndex = 0;
				this->m_Layer[i].speed = 0.0f;
				this->m_Layer[i].frameCounter = 0.0f;
				this->m_Layer[i].started = 0.0f;
				this->m_Layer[i].loops = 0;
			}
		}

		inline void OGEWorld::setBlocked(char m_Blocked) { this->m_Blocked = m_Blocked; }
		inline char &OGEWorld::isBlocked() { return this->m_Blocked; }
		
		inline void OGEWorld::setCharIndex(short m_CharIndex) { this->m_CharIndex = m_CharIndex; }
		inline short &OGEWorld::isCharIndex() { return this->m_CharIndex; }

		inline void OGEWorld::setTrigger(short m_Trigger) { this->m_Trigger = m_Trigger; }
		inline short &OGEWorld::isTrigger() { return this->m_Trigger; }

		inline void OGEWorld::setLayer(GRH m_GRH, int m_Layer) { this->m_Layer[m_Layer] = m_GRH; }
		inline GRH &OGEWorld::isLayer(int m_Layer) { return this->m_Layer[m_Layer]; }

		inline void OGEWorld::setObjGrh(short m_GrhIndex) { this->m_ObjGrh.grhIndex = m_GrhIndex; }
		inline GRH &OGEWorld::isObjGrh() { return this->m_ObjGrh; }

		inline void OGEWorld::setObjInfo(OBJ m_Obj) { this->m_ObjInfo = m_Obj; }
		inline OBJ &OGEWorld::isObjInfo() { return this->m_ObjInfo; }

	public:
		inline bool OGEWorld::isWater() { return ( (isLayer(1).grhIndex >= 1505 && isLayer(1).grhIndex <= 1520)
												|| (isLayer(1).grhIndex >= 5665 && isLayer(1).grhIndex <= 5680)
												|| (isLayer(1).grhIndex >= 13547 && isLayer(1).grhIndex <= 13562))
												& (isLayer(2).grhIndex == 0) ;}

	private:
		short m_CharIndex, m_Trigger;
		GRH m_Layer[5], m_ObjGrh;
		OBJ m_ObjInfo;
		char m_Blocked;
};
//#endif