#pragma once

#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#include <string>
#include "Tetris.h"

// simple wrapper for DC
class myDC {
public:
	myDC(HWND hwnd) : hwnd{ hwnd }, dc { GetDC(hwnd) } {}
	~myDC() { ReleaseDC(hwnd, dc); }
	HDC dc;

private:
	HWND hwnd;
};

// this class knows everything about graphics
class WinGDIDraw : public DrawInterface {
public:
	WinGDIDraw(HWND hwnd) : hwnd{ hwnd } {}
 
	void drawBoard(Tetris::Board& board) override;
	void windowInit();

private:
	HWND hwnd;	// handle to the main window
	std::wstring wstr;

	// dimensions
	const int width = 500;
	const int height = 500;
	const int center = 250;
	const int block_size = 100; 

	void StringtoLCPWSTR(const std::string& str) {
		wstr = std::wstring{ str.begin(), str.end() };
	}

	// write text
	void writeText(int x, int y, int width, int height, std::string str);
	// draw rectangle
	void Rect(int x, int y, int width, int height, int color); 
};
