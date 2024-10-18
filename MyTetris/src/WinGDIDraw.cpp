#include "WinGDIDraw.h"
 
// this class knows everything about graphics
// implementing interface requirements 
void WinGDIDraw::drawBoard(Game::Board& board) {
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			RECT rect = {
				0 + i * block_size,
				0 + j * block_size,
				0 + i * block_size + block_size,
				0 + j * block_size + block_size,
			};
			FillRect(memDC, &rect, colorBrushes[board[i][j]]);
		}
	} 
	InvalidateRect(hwnd, NULL, TRUE);	// post WM_PAINT -> BitBlt
}

void WinGDIDraw::drawBlock(vec2 pos, Game::Board& board) {
	RECT rect = Pos2Rect(pos);
	FillRect(memDC, &rect, colorBrushes[board[pos.x][pos.y]]);
	InvalidateRect(hwnd, &rect, FALSE);
}
void WinGDIDraw::drawStartPage() {
	writeText(center_x, center_y, 300, 100, startString); 
	InvalidateRect(hwnd, NULL, false);
}
void WinGDIDraw::drawEndPage() {
	writeText(center_x, center_y, 300, 100, endString); 
	InvalidateRect(hwnd, NULL, false);
}
void WinGDIDraw::drawBackground() {
	RECT rect;
	GetClientRect(hwnd, &rect);
	FillRect(memDC, &rect, colorBrushes[0]); // black brush
}
 
// write text
void WinGDIDraw::writeText(int x, int y, int width, int height, std::string str) {
	RECT rect = { x - width/2, y -height/2, x + width/2, y + height/2 }; 
	StringtoLCPWSTR(str);
	DrawText(memDC, wstr.c_str(), -1, &rect, DT_CENTER); 
	InvalidateRect(hwnd, NULL, FALSE);
}

void WinGDIDraw::ResizeClientArea(int newClientWidth, int newClientHeight) {
	// NOTE: It seems there is a DPI related problem... 500*500 becomes 630*630
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

// post-construct initialization
void WinGDIDraw::windowInit() {
	// resize client area
	ResizeClientArea(width, height);
	// get window DC
	winDC = GetDC(hwnd);
	// init back buffer
	InitBackBuffer();
}

void WinGDIDraw::InitBackBuffer() {
	memDC = CreateCompatibleDC(winDC);
	backBuffer = CreateCompatibleBitmap(winDC, width, height); 
	SelectObject(memDC, backBuffer); // now all graphic api works with memDC draw on backbuffer
}
void WinGDIDraw::DeInitBackBuffer() {
	DeleteObject(backBuffer);
	DeleteDC(memDC);
}

void WinGDIDraw::reDraw() {
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);
	RECT& rect = ps.rcPaint;
	int rcWidth = rect.right - rect.left;
	int rcHeight = rect.bottom - rect.top;
	// BLIT required(invalidated) parts from back buffer to client dc
	BitBlt(dc,	// destination DC
		rect.left, rect.top, rcWidth, rcHeight,	// destination origin and size
		memDC,	// source DC(DC handle to memory DDB)
		rect.left, rect.top,	// source origin
		SRCCOPY	// blt mode
	);
	EndPaint(hwnd, &ps);
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

