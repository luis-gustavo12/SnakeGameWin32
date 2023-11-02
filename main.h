#pragma once


// Defines


#define   NAME_OF_GAME	    "SnakeGame - Win32"
#define   EXECUTABLE_NAME   "SnakeGameWin32"


/**
 *   These pre-defined funcitons/variables are for setting values useful for Windows API handling, like screen size, bits per pixel, etc.
 *   Note that, game resolution is of 1024 x 576, but it will be going full screen. That is because, we큥e getting this resolution, and will be
 *   streching it to the user큦 monitor values. Of course, later will be possible for configuring windows perspective, making it windowed, etc
 */


#define   GAME_WINDOW_HEIGHT    1024
#define   GAME_WINDOW_WIDTH      576
#define   GAME_BPP                32  // Bits per Pixel. Means every single bit, will handle 32 bits, 8 for Red, 8 for Green, and 8 for Blue
#define   GAME_CANVA_SIZE       (GAME_WINDOW_WIDTH* GAME_WINDOW_WIDTH) // It s here, so we can be compatible with WindowsAPI. At some point, we'll need this info
#define   GAME_CANVA_DRAW_AREA  ( GAME_CANVA_SIZE * (GAME_BPP / 8)  )


// Includes

#include <iostream>
#include <windows.h>
#include <string.h>


#include "ERRORS.h"
#include "STRING.h"
#include "INPUT.h"



// Globals



bool          bGameRunning = 1;
HWND          hGameWindow;

const char szClassName[] = "Snake Game";      //TODO: Futurelly, here will load the string from the configuration file pre-defined by the user.


WNDCLASSEXA wndGameWindowClass = { 0 };              // Window Class to be used on bCreateGameWindow() function.


USERINPUT stUserInput = { 0 }; // Struct that will handle user input.



// Structs

typedef struct {

	BITMAPINFO stBitMapInfo;
	void*      xMemory;


} GAME_CANVA, PST_GAME_CANVA;


enum eQuitApplicationOption {
	NO_MESSAGE,  // No message to be displayed
	MESSAGE_BOX // Display messagebox
};



GAME_CANVA    gstGameCanva; // Surface where game will be written into










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
 * @brief Checks weather there큦 already a game큦 executable running. Just a way to prevent users from running the game twice.
 *
 * @return If there큦 already an instance, Mutex Object could not be created, so it returns false. Otherwise, true.
 *
 */




bool bInstanceRunning();



/**
 * 
 * @brief Process all user큦 input. First, it will set, for every single frame, a value to all USERINPUT struct members (defined at INPUT.h file) 
 * .Then, it will run again over all of them to apply its logics, given the game큦 current state, and based on its value, it will send a Message
 * to the Message Queue, making its logic through it. 
 * .
 */


void vProcessUserInput();



void vProcessGraphics();



void vLoadGameCanva();



void vGameOver();



void vQuitApplication(eQuitApplicationOption eOption = NO_MESSAGE, const char* szMessage = "Fail");


