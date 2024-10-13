/*
Tetris Game
*/

// force unicode
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h> 

// some internal global variables
static LPCWSTR appName = L"Tetris";
static constexpr int width = 500;
static constexpr int height = 500;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	// define main window
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = appName;
	wc.hInstance = hInstance;
	// TODO: Is CS_OWNDC neccesary for efficienty?
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// NOTE: Maybe Background is not neccesary...
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// no menu, no extra memory 

	// register window
	if (!RegisterClass(&wc)) {
		// fail
		OutputDebugString(L"WinMain: wndclass register fail");
		return 0; 
	}

	// window create 
	HWND hwnd = CreateWindow(
		appName,
		L"My Tetris App",
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,	// window style
		CW_USEDEFAULT, CW_USEDEFAULT,	// initial position
		width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd) {
		OutputDebugString(L"WinMain: CreateWindow failed");
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// default message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	// process exit
	return 0;
} 

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	return DefWindowProc(hwnd, msg, wparam, lparam);
}
