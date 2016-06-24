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
#include <chrono>
class OGEWatch{
	public:
		void OGEWatch::Start();
		float OGEWatch::Lap();
		void OGEWatch::Stop();
		float OGEWatch::Elapsed();

	protected:
		std::chrono::time_point<std::chrono::system_clock> start, end;
};