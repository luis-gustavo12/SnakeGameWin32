#pragma once


// Defines

#ifndef _UNICODE
#define _UNICODE
#endif

#define NAME_OF_GAME L"SnakeGame - Win32"
#define EXECUTABLE_NAME L"SnakeGameWin32"


/**
 *   These pre-defined funcitons/variables are for setting values useful for Windows API handling, like screen size, bits per pixel, etc.
 *   Note that, game resolution is of 1024 x 576, but it will be going full screen. That is because, we´re getting this resolution, and will be
 *   streching it to the user´s monitor values. Of course, later will be possible for configuring windows perspective, making it windowed, etc
 */


#define   GAME_WINDOW_HEIGHT    1024
#define   GAME_WINDOW_WIDTH      576
#define   GAME_BPP                32  // Bits per Pixel. Means every single bit, will handle 32 bits, 8 for Red, 8 for Green, and 8 for Blue
#define   GAME_CANVA_SIZE       (GAME_WINDOW_WIDTH* GAME_WINDOW_WIDTH) // It s here, so we can be compatible with WindowsAPI. At some point, we'll need this info



// Includes

#include <iostream>
#include <windows.h>
#include <string.h>


#include "ERRORS.h"

// Globals



bool          bGameRunning = 1;
HWND          GameWindow;



// Functions


/**
 * 
 * @brief Main game window procedure, original from Windos API. See more on: https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure.
 * 
 * 
 * 
 */


LRESULT CALLBACK GameWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


/**
 * @brief Checks weather there´s already a game´s executable running. Just a way to prevent users from running the game twice.
 *
 * @return If there´s already an instance, Mutex Object could not be created, so it returns false. Otherwise, true.
 * 
 */


bool bInstanceRunning();



void vProcessUserInput();


void vPorcessGraphics();


void vLoadGameCanva();


void vGameOver();

void vQuitApplication();


// Structs

typedef struct {

	BITMAPINFO stBitMapInfo;
	void*      xMemory;


} GAME_CANVA, PST_GAME_CANVA;






GAME_CANVA    gstGameCanva; // Surface where game will be written into