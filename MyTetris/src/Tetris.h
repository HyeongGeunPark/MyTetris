 // Model
// defines Tetris game logic
#pragma once

#include <array>

class DrawInterface;
 
class Tetris {
public:
	// constructor
	explicit Tetris(DrawInterface* di = nullptr)
		: di{ di }, board{ 0 }, x{ 2 }, y{ 2 }
	{ }

	// destructor
	~Tetris() {}

	// do not allow move/copy construct/assign
	Tetris(const Tetris&) = delete;
	Tetris& operator=(const Tetris&) = delete;
	Tetris(Tetris&&) = delete;
	Tetris& operator=(Tetris&&) = delete;

	// enums
	enum State {
		START = 0, RUNNING, END
	};

	// types
	static constexpr int board_x = 5;
	static constexpr int board_y = 5;
	using Board = std::array<std::array<int, board_x>, board_y>;

	enum Keycode {
		KEYDOWN = 0, KEYUP, KEYRIGHT, KEYLEFT, KEYSPACE, KEYESC, NONE
	};
 
	// interfaces for event handling
	/*
	TODO:
	1. timer handler
	2. keyboard handler
	*/
	void OnTimerEvent();
	void OnKeyEvent(Keycode keycode);

	void Init(); 


	// interfaces for drawing
	void ReDraw();

private:
	// pointer to draw interface
	DrawInterface* di;
	// internal game state
	State state = START;

	// test states
	int x;
	int y;

	// board
	Board board;

	// internal methods
	void BoardInit();
};

class DrawInterface {
public:
	virtual void drawBoard(Tetris::Board& board) = 0;
	//virtual void drawBackground() = 0;
	//virtual void drawStartPage() = 0;
	//virtual void drawEndPage() = 0;
protected:
	// Game Specific constants
};
