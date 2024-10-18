#include "WinGDIDraw.h"
 
// this class knows everything about graphics
// implementing interface requirements 
void WinGDIDraw::drawBoard(Game::Board& board) {
	myDC dc{ hwnd };
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			RECT rect = {
				0 + i * block_size,
				0 + j * block_size,
				0 + i * block_size + block_size,
				0 + j * block_size + block_size,
			};
			FillRect(dc.dc, &rect, colorBrushes[board[i][j]]);
		}
	} 
}

void WinGDIDraw::drawBlock(vec2 pos, Game::Board& board) {
	myDC dc{ hwnd };
	RECT rect = Pos2Rect(pos);
	FillRect(dc.dc, &rect, colorBrushes[board[pos.x][pos.y]]);
}
void WinGDIDraw::drawStartPage() {
	writeText(center_x, center_y, 100, 100, startString); 
}
void WinGDIDraw::drawEndPage() {
	writeText(center_x, center_y, 100, 100, endString); 
}
void WinGDIDraw::drawBackground() {
	myDC dc{ hwnd };
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(dc.dc, &rect, colorBrushes[0]); // black brush
}
 
// write text
void WinGDIDraw::writeText(int x, int y, int width, int height, std::string str) {
	myDC dc{ hwnd };
	RECT rect = { x - width/2, y -height/2, x + width/2, y + height/2 }; 
	StringtoLCPWSTR(str);
	DrawText(dc.dc, wstr.c_str(), -1, &rect, DT_CENTER); 
}
// draw rectangle
void WinGDIDraw::Rect(int x, int y, int width, int height, int color) {
	myDC dc{ hwnd };
	RECT rect = { x,y,x + width,y + height };
}

void WinGDIDraw::ResizeClientArea(int newClientWidth, int newClientHeight) {
	RECT windowRect;
	GetWindowRect(hwnd, &windowRect);
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	int widthDiff =
		(windowRect.right - windowRect.left)
		- (clientRect.right - clientRect.left);
	int heightDiff =
		(windowRect.bottom - windowRect.top)
		- (clientRect.bottom - clientRect.top);

	SetWindowPos(hwnd,
		NULL,
		0, 0,	// position, not needed
		newClientWidth + widthDiff,
		newClientHeight + heightDiff,
		SWP_NOMOVE | SWP_NOZORDER); 
}

RECT WinGDIDraw::Pos2Rect(vec2 pos) {
	RECT rect = {
		0 + pos.x * block_size,
		0 + pos.y * block_size,
		0 + pos.x * block_size + block_size,
		0 + pos.y * block_size + block_size,
	};
	return rect;
}
