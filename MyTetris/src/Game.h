// Model + ViewController
// defines Game game logic
// currently this game is the snake game
#pragma once

#include <array>
#include <list>
#include <random>

class DrawInterface;

struct vec2 {
	int x, y;
	friend bool operator==(const vec2& a, const vec2& b) {
		return a.x == b.x && a.y == b.y;
	}
};
 
class Game {
public:
	// constructor
	explicit Game(DrawInterface* di = nullptr)
		: di{ di }, board{ EMPTY }
	{ 
		Init();
	}

	// destructor
	~Game() {}

	// do not allow move/copy construct/assign
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

	// enums
	enum State {
		START = 0, RUNNING, END
	};
	enum Keycode {
		KEYDOWN = 0, KEYUP, KEYRIGHT, KEYLEFT, KEYSPACE, KEYESC, NONE
	};
	enum BoardState {
		EMPTY = 0, SNAKE, TARGET
	};

	// types
	static constexpr int board_x = 21;
	static constexpr int board_y = 21; 
	using Board = std::array<std::array<BoardState, board_x>, board_y>;


 
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
	std::list<vec2> snake;
	vec2 head;
	vec2 target;
	static constexpr vec2 center = { board_x / 2, board_y / 2 };

	// board
	Board board;

	// internal methods
	void BoardInit();
	void StateInit();

	// game logics
	vec2 CreateTarget(); 
	void SnakeGrow();
	void SnakeMove(Keycode direction);
	void SnakeDead(); 
	bool InBoardMove(vec2& pos, Keycode direction);
	
};

class DrawInterface {
public:
	// draw all client area
	virtual void drawBoard(Game::Board& board) = 0;
	// draw one block
	virtual void drawBlock(vec2 pos, Game::Board& board) = 0;
	virtual void drawBackground() = 0;
	virtual void drawStartPage() = 0;
	virtual void drawEndPage() = 0;
protected:
	// Game Specific constants
};
