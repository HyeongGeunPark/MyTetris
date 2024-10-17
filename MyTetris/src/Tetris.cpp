// Model
// defines Tetris game logic

#include "Tetris.h" 

// interfaces for event handling
/*
TODO:
1. timer handler
2. keyboard handler
*/
void Tetris::OnTimerEvent() {}
void Tetris::OnKeyEvent(Keycode keycode) {
	if (state == START) {
		state = RUNNING;
		Init();
		di->drawBoard(board);
	}
	else if (state == RUNNING) {
		board[x][y] = 0;
		switch (keycode) {
		case KEYDOWN:
			if (y != board_y - 1) ++y;
			break;
		case KEYUP:
			if (y != 0)--y;
			break;
		case KEYRIGHT:
			if (x != board_x - 1) ++x;
			break;
		case KEYLEFT:
			if (x != 0) --x;
			break;
		case KEYESC:
			state = END;
			//di->drawEndPage();
			return;
		default:
			return;
		} 
		board[x][y] = 1;
		di->drawBoard(board);
	}
	else if (state == END) {
		state = START;
		//di->drawStartPage();
	}
} 

void Tetris::Init() {
	x = 2;
	y = 2;
}

void Tetris::BoardInit() {
	board = Board{ 0 };
	board[x][y] = 1; 
}

void Tetris::ReDraw() {
	di->drawBoard(board);
}
