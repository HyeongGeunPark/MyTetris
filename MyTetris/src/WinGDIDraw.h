#pragma once

#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#include <string>
#include <windowsx.h>
#include "Game.h"

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
	~WinGDIDraw() {
		for (HBRUSH brush : colorBrushes)
			DeleteObject(brush);
	}
 
	void drawBoard(Game::Board& board) override;
	void drawBlock(vec2 pos, Game::Board& board) override;
	void drawStartPage() override;
	void drawEndPage() override;
	void drawBackground() override;
	void windowInit() { ResizeClientArea(width, height); }

private:
	HWND hwnd;	// handle to the main window
	std::wstring wstr;

	// dimensions & string constants
	const int block_size = 30;
	const int width = block_size * Game::board_x;
	const int height = block_size * Game::board_y;
	const int center_x = width/2;
	const int center_y = height/2;
	const std::string startString = "Press Any Key to Start The Game";
	const std::string endString = "Game Over";

	// helper objects and functions
	std::vector<HBRUSH> colorBrushes{
		CreateSolidBrush(RGB(0,0,0)),
		CreateSolidBrush(RGB(100,100,100)),
		CreateSolidBrush(RGB(200,200,200))
	};

	void StringtoLCPWSTR(const std::string& str) {
		wstr = std::wstring{ str.begin(), str.end() };
	}


	// write text
	void writeText(int x, int y, int width, int height, std::string str);
	// draw rectangle
	void Rect(int x, int y, int width, int height, int color); 

	void ResizeClientArea(int newClientWidth, int newClientHeight);

	RECT Pos2Rect(vec2 pos);
};
