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
#include "OGEWatch.hpp"

using namespace std::chrono;

void OGEWatch::Start(){
    this->start = system_clock::now();
}

float OGEWatch::Lap(){
    time_point<system_clock> lap;
    lap = system_clock::now();
    duration<float> elapsed_seconds = lap - this->start;
    return elapsed_seconds.count();
}

void OGEWatch::Stop(){
    this->end = system_clock::now();
}

float OGEWatch::Elapsed(){
	Stop();
	duration<double> elapsed_seconds = (this->end - this->start) * 1000;
	Start();
	return static_cast<float>(elapsed_seconds.count());
}