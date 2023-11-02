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

	
			MessageBoxExA(NULL, "Instance already running!!", WINDOW_ERROR, MB_ICONEXCLAMATION | MB_OK, 0);
			return -1;


		default:

			DWORD ulMutexLastError = GetLastError();
			SetLastError(ulMutexLastError);

			char szErrorMsg[512];
			sprintf_s(szErrorMsg, "Error code: %u", GetLastError());


			MessageBoxExA(NULL, szErrorMsg, WINDOW_ERROR, MB_ICONEXCLAMATION | MB_OK, 0);

			return -1;


			return -1;

		}

		if (GetLastError() == ERROR_ALREADY_EXISTS) {
			
			MessageBoxExA(NULL, "Instance already running!", "Error", MB_ICONEXCLAMATION | MB_OK, 0);
			return -1;

		}



		else {

			DWORD ulMutexLastError = GetLastError();
			SetLastError(ulMutexLastError);

			char szErrorMsg [512];
			sprintf_s(szErrorMsg,"Error code: %u", GetLastError() );


			MessageBoxExA(NULL, szErrorMsg, "Error", MB_ICONEXCLAMATION | MB_OK, 0);

			return -1;

		}


	}


	


	// Windows Class definition
	wndGameWindowClass.lpfnWndProc       = GameWindowProcedure;
	wndGameWindowClass.lpszClassName	 = szClassName;
	wndGameWindowClass.hInstance		 = hInstance;
	wndGameWindowClass.cbClsExtra		 = 0;
	wndGameWindowClass.cbSize			 = sizeof(WNDCLASSEXA);
	wndGameWindowClass.lpszMenuName      = NULL;
	wndGameWindowClass.cbWndExtra        = 0;
	wndGameWindowClass.lpszClassName	 = NULL;
	wndGameWindowClass.style = CS_SAVEBITS;
	wndGameWindowClass.hIcon             = LoadIconA(NULL, IDI_APPLICATION);
	wndGameWindowClass.hIconSm			 = LoadIconA(NULL, IDI_APPLICATION);
	wndGameWindowClass.hCursor			 = LoadCursorA(NULL, IDC_ARROW);

	if ((\
	wndGameWindowClass.hbrBackground = CreateSolidBrush(RGB(255, 0, 255)) \
	) == NULL) {
		OutputDebugStringA("ERROR TO CREATE SOLID BRUSH!!");
	}


	if (RegisterClassExA(&wndGameWindowClass) == 0) {


		MessageBoxA(NULL, "Error!! Could not register class!!", "Error code: ", NULL);
		return GetLastError();

	}



	hGameWindow = CreateWindowExA(
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

	if (hGameWindow == NULL) {

		MessageBoxA(NULL, "Error!! Could not Handle!!", "Error code: ", NULL);
		return 0;

	}


	ShowWindow(hGameWindow, iCmdShow);


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
		while ( PeekMessageA(&uMessage, hGameWindow, 0, 0, PM_REMOVE | PM_NOREMOVE)   ){


			
			DispatchMessageA(&uMessage);
			

			

		}


		vProcessUserInput();

		vProcessGraphics();




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
		OutputDebugStringA("WM_DESTROY");
		bGameRunning = false;
		PostQuitMessage(WM_QUIT);
		return 0;





	case WM_QUIT:


		OutputDebugStringA("WM_QUIT");
		vQuitApplication();
		return 0;

	case WM_PAINT:
	
		OutputDebugStringA("WM_PAINT");
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
	
	HANDLE hMutex = CreateMutexExA(NULL, EXECUTABLE_NAME, 0, SEMAPHORE_ALL_ACCESS);

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
		SendMessage(hGameWindow, WM_DESTROY, 0, 0);
		return;
	}

	else if (stUserInput.shEsc) {
		SendMessage(hGameWindow, WM_DESTROY, 0, 0);
		return;
	}





}

void vProcessGraphics() {



	HDC hDeviceContext = GetDC(hGameWindow);

	StretchDIBits(hDeviceContext, 0, 0, 100, 100, 0, 0, 100, 100, gstGameCanva.xMemory, &gstGameCanva.stBitMapInfo, DIB_RGB_COLORS, SRCCOPY);

	//OutputDebugStringW()



	ReleaseDC(hGameWindow, hDeviceContext);


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



void vQuitApplication(eQuitApplicationOption eOption, const char* szMessageParam) {


	char* szMessageDisplay = (char* )malloc ( (2048 + 1) * sizeof(char*)    )  ; // Wide string to be displayed in MessageBoxW


	if (szMessageDisplay == NULL) {
		exit(-1);
	}

	

	snprintf(szMessageDisplay,sizeof(szMessageDisplay), "%s", szMessageParam);


	switch (eOption) {

		
		case NO_MESSAGE:
			free(szMessageDisplay);
			exit(-1);
			break;


		case MESSAGE_BOX:

			MessageBoxA(NULL, szMessageDisplay, "Fail", MB_OK);
			free(szMessageDisplay);
			exit(-1);
			break;

	}


	free(szMessageDisplay);
	exit(-1);



}


// TESTEE