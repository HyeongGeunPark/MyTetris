 // View
// highly-windows-dependent codes
// defines the View
// provides interfaces to control the View

// force Unicode
#pragma once

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN 
#include <windows.h> 

class MainWindow {
public:
	// constructor
	MainWindow(HINSTANCE hInstance, int nCmdShow)
		: hInstance(hInstance), nCmdShow(nCmdShow), wc{ 0 }
	{ }
	// destructor
	~MainWindow() {}
	// do not allow copy/move construct/assignment
	MainWindow(const MainWindow&) = delete;
	MainWindow(MainWindow&&) = delete;
	MainWindow& operator=(const MainWindow&) = delete;
	MainWindow& operator=(MainWindow&&) = delete;

	// post-construct init
	bool Init(WNDPROC WndProc); 
 
	// pre-destruct deinit
	bool DeInit(); 

	// getter
	HWND gethWnd() const { return hwnd; }


private:
	// win32 api related handles
	HINSTANCE hInstance = NULL;
	int nCmdShow;
	WNDCLASS wc;
	LPCWSTR appName = L"Tetris";
	LPCWSTR windowName = L"My Tetris App";
	WNDPROC WndProc = NULL;
	HWND hwnd = NULL; 
};
