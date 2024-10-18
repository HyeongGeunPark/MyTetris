/*
Game Game
*/

// force unicode
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 

#include "Game.h"
#include "MainWindow.h"
#include "WinGDIDraw.h"
 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// create main window
	MainWindow mainWindow(hInstance, nCmdShow);
	if (!mainWindow.Init(WndProc)) {
		OutputDebugString(L"WinMain: mainWindow::Init() failed");
		return 0;
	} 
	HWND hwnd = mainWindow.gethWnd();
 
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
 
	// default message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// process exit
	mainWindow.DeInit();
	return 0;
} 

// delegates windows message to Game object
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	static WinGDIDraw di{ hwnd };
	static Game tetris{ &di };
	switch (msg) {
	case WM_CREATE: {
		di.windowInit();
	} return 0;


	case WM_KEYDOWN: {
		Game::Keycode keycode;
		switch (wparam) {
		case VK_UP:
			keycode = Game::Keycode::KEYUP;
			break;
		case VK_DOWN:
			keycode = Game::Keycode::KEYDOWN;
			break;
		case VK_RIGHT:
			keycode = Game::Keycode::KEYRIGHT;
			break;
		case VK_LEFT:
			keycode = Game::Keycode::KEYLEFT;
			break;
		case VK_ESCAPE:
			keycode = Game::Keycode::KEYESC;
			break;
		default:
			return 0;
		}
		tetris.OnKeyEvent(keycode);
	} return 0;


	case WM_PAINT: 
		tetris.ReDraw();
		return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}
