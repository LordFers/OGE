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

#ifndef NOMINMAX
	#define NOMINMAX
#endif

#pragma warning(push)
#pragma warning(disable: 4275)

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#define MAIN_VIEW_PORT_X 1280
#define MAIN_VIEW_PORT_Y 720

#define TILE_PIXEL_WIDTH 32
#define TILE_PIXEL_HEIGHT 32

#define SCROLL_PIXELS_PER_FRAME_X 8
#define SCROLL_PIXELS_PER_FRAME_Y 8

#define HALF_WINDOW_TILE_WIDTH (MAIN_VIEW_PORT_X / TILE_PIXEL_WIDTH) / 2
#define HALF_WINDOW_TILE_HEIGHT (MAIN_VIEW_PORT_Y / TILE_PIXEL_HEIGHT) / 2

#define WINDOW_TILE_WIDTH (HALF_WINDOW_TILE_WIDTH * 2) + 1
#define WINDOW_TILE_HEIGHT (HALF_WINDOW_TILE_HEIGHT * 2) + 1

#define TILE_BUFFER_SIZE (HALF_WINDOW_TILE_WIDTH + 1)

#define X_MAX_MAP_SIZE 100
#define X_MIN_MAP_SIZE 1

#define Y_MAX_MAP_SIZE 100
#define Y_MIN_MAP_SIZE 1

#define UBound(n)	sizeof(n) / sizeof(n[0])

#define NORTH 1
#define EAST 2
#define SOUTH 3
#define WEST 4

#define ENGINESPEED 0.018f
#define DIRECTINPUT_VERSION 0x0800

// Windows Header Files:
#include <Windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// DirectX Header Files
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

// OpenGL Header Files
#include <gl/GL.h>
#include <gl/GLU.h>

// Others
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>

//#endif