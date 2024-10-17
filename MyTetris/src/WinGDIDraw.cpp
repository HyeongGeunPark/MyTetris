#include "WinGDIDraw.h"
#include "windowsx.h"
 
// this class knows everything about graphics
 
void WinGDIDraw::drawBoard(Tetris::Board& board) {
	myDC dc{ hwnd };
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			RECT rect = {
				0 + i * block_size,
				0 + j * block_size,
				0 + i * block_size + block_size,
				0 + j * block_size + block_size,
			};
			if (board[i][j])
				FillRect(dc.dc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
			else
				FillRect(dc.dc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
	} 
}

void WinGDIDraw::windowInit() {
	//SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}
 
// write text
void WinGDIDraw::writeText(int x, int y, int width, int height, std::string str) {
	myDC dc{ hwnd };
	RECT rect = { x, y, x + width, y + height }; 
	StringtoLCPWSTR(str);
	DrawText(dc.dc, wstr.c_str(), -1, &rect, DT_CENTER); 
}
// draw rectangle
void WinGDIDraw::Rect(int x, int y, int width, int height, int color) {
	myDC dc{ hwnd };
	RECT rect = { x,y,x + width,y + height };
}

