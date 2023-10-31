/**
 * @file   main.cpp
 * @brief  Main file for launching the game. It will be used Wide Character Set (Unicode). Basically, the main file handles on its majority
 *  Windows API procedures, like painting and many other OS operations.
 * 
 * @author Luís Silva
 * @date   09/10/2023
 */






#include "main.h"














// main



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, INT iCmdShow) {




	// Check for mutex

	if (bInstanceRunning() == false) {


		switch (GetLastError()) {

		
		// Those two are basically the same, but letting them here, just in case
		case ERROR_ALREADY_EXISTS:
		case ERROR_ACCESS_DENIED:


			MessageBoxExW(NULL, L"Instance already running!!", WINDOW_ERROR, MB_ICONEXCLAMATION | MB_OK, 0);
			return -1;


		default:

			DWORD ulMutexLastError = GetLastError();
			SetLastError(ulMutexLastError);

			wchar_t szErrorMsg[512];
			wsprintf(szErrorMsg, L"Error code: %u", GetLastError());


			MessageBoxExW(NULL, szErrorMsg, WINDOW_ERROR, MB_ICONEXCLAMATION | MB_OK, 0);

			return -1;


			return -1;

		}

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			
			MessageBoxExW(NULL, L"Instance already running!", L"Error", MB_ICONEXCLAMATION | MB_OK, 0);
			return -1;

		}



		else {

			DWORD ulMutexLastError = GetLastError();
			SetLastError(ulMutexLastError);

			wchar_t szErrorMsg [512];
			wsprintf(szErrorMsg, L"Error code: %u", GetLastError() );


			MessageBoxExW(NULL, szErrorMsg, L"Error", MB_ICONEXCLAMATION | MB_OK, 0);

			return -1;

		}


	}


	


	// Windows Class definition
	wndGameWindowClass.lpfnWndProc       = GameWindowProcedure;
	wndGameWindowClass.lpszClassName	 = szClassName;
	wndGameWindowClass.hInstance		 = hInstance;
	wndGameWindowClass.style			 = 0;
	wndGameWindowClass.cbClsExtra		 = 0;
	wndGameWindowClass.cbSize			 = sizeof(WNDCLASSEXW);
	wndGameWindowClass.lpszMenuName      = NULL;
	wndGameWindowClass.cbWndExtra        = 0;
	wndGameWindowClass.hIcon			 = LoadIconW(NULL, IDI_APPLICATION);
	wndGameWindowClass.hIconSm           = LoadIconW(NULL, IDI_APPLICATION);
	wndGameWindowClass.hCursor           = LoadCursorW(NULL, IDC_ARROW);
	wndGameWindowClass.hbrBackground     = CreateSolidBrush( RGB(189,125,35) );


	if (RegisterClassExW(&wndGameWindowClass) == 0) {


		MessageBoxW(NULL, L"Error!! Could not register class!!", L"Error code: ", NULL);
		return GetLastError();

	}



	GameWindow = CreateWindowExW(
		0,
		szClassName,
		NAME_OF_GAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL		// Additional application data


	);

	if (GameWindow == NULL) {

		MessageBoxW(NULL, L"Error!! Could not Handle!!", L"Error code: ", NULL);
		return 0;

	}


	ShowWindow(GameWindow, iCmdShow);


	vLoadGameCanva();

	
	MSG uMessage = { 0 };

	/****************************************************************************
	*																			*
	*																			* 
	*																			* 
	*						         GAME LOOP 									* 
	*																			* 
	*																			* 
	*																			* 
	*****************************************************************************/


	while (bGameRunning) {


		// Windows messages loop
		while ( PeekMessageW(&uMessage, GameWindow, 0, 0, PM_REMOVE | PM_NOREMOVE)   ){


			
			DispatchMessageW(&uMessage);
			

			

		}


		vProcessUserInput();

		vPorcessGraphics();




		/*
		*  After messages are properly processed, we now go to the main game logic. 
		*  First -> user input
		*  Second -> video rendering
		* 
		*  Every thing happening inside this loop, is inside the frame, so every time this loop
		*  is executed, it runs one frame
		* 
		*/



		Sleep(1); // Sleep for not consuming too much CPU usage


	}

	



	return 1;

}






// END - main





LRESULT GameWindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {


	switch (uMsg) {

	case WM_DESTROY:
		OutputDebugStringW(L"WM_DESTROY");
		bGameRunning = false;
		PostQuitMessage(WM_QUIT);
		return 0;





	case WM_QUIT:


		OutputDebugStringW(L"WM_QUIT");
		vQuitApplication();
		return 0;

	case WM_PAINT:
	
		OutputDebugStringW(L"WM_PAINT");
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);

		return 0;


	

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);

}










bool bInstanceRunning() {
	
	HANDLE hMutex = CreateMutexExW(NULL, EXECUTABLE_NAME, 0, SEMAPHORE_ALL_ACCESS);

	if (hMutex == NULL) {
		
		return false;
	}
	else {
		
		return true;
	}

}




void vProcessUserInput() {

	
	// Setting struct values

	stUserInput.shCtrlW = (   GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState('W')   );
	stUserInput.shEsc   = GetAsyncKeyState(VK_ESCAPE);

	
	





	// Run logic for all of the keys, and also relying on game state, which will be includede after

	if (stUserInput.shCtrlW) {
		SendMessage(GameWindow, WM_DESTROY, 0, 0);
		return;
	}

	else if (stUserInput.shEsc) {
		SendMessage(GameWindow, WM_DESTROY, 0, 0);
		return;
	}





}

void vPorcessGraphics() {











}

void vLoadGameCanva() {

	gstGameCanva.stBitMapInfo = { 0 };

	// Bitmap Data handling.

	#ifndef G_BITMAP_HEADER // Stands for game bitmap header
	#define G_BITMAP_HEADER gstGameCanva.stBitMapInfo.bmiHeader // Something i did for not writing everything everytime. 
	#endif 


	G_BITMAP_HEADER.biSize          =     sizeof(gstGameCanva.stBitMapInfo.bmiHeader);
	G_BITMAP_HEADER.biWidth         =     GAME_WINDOW_WIDTH;
	G_BITMAP_HEADER.biHeight        =     GAME_WINDOW_HEIGHT;
	G_BITMAP_HEADER.biBitCount      =     GAME_CANVA_SIZE;
	G_BITMAP_HEADER.biCompression   =     BI_RGB;
	G_BITMAP_HEADER.biPlanes        =     1;
	gstGameCanva.xMemory            =     VirtualAlloc(NULL, GAME_CANVA_SIZE, \
														   MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);



	if (gstGameCanva.xMemory == NULL) {

		vQuitApplication();

	}


}


void vGameOver() {
	;
}



void vQuitApplication(eQuitApplicationOption eOption, const char* szMessage) {


	wchar_t* wszWideStrMessage = (wchar_t* )malloc ( (2048 + 1) * sizeof(wchar_t)    )  ; // Wide string to be displayed in MessageBoxW


	if (wszWideStrMessage == NULL) {
		exit(-1);
	}

	

	wsprintf(wszWideStrMessage, L"%s", szMessage);


	switch (eOption) {

		
		case NO_MESSAGE:
			free(wszWideStrMessage);
			exit(-1);
			break;


		case MESSAGE_BOX:

			MessageBoxW(NULL, wszWideStrMessage, L"Fail", MB_OK);
			free(wszWideStrMessage);
			exit(-1);
			break;

	}


	free(wszWideStrMessage);
	exit(-1);



}


// TESTEE