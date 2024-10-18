// Model
// defines Game game logic

#include "Game.h" 

// interfaces for event handling
/*
TODO:
1. timer handler
*/
void Game::OnTimerEvent() {}
void Game::OnKeyEvent(Keycode keycode) {
	if (state == START) {
		state = RUNNING;
		target = CreateTarget();
		board[target.x][target.y] = TARGET;
		di->drawBoard(board);
	}
	else if (state == RUNNING) {
		switch (keycode) {
		case KEYDOWN:
		case KEYUP:
		case KEYRIGHT:
		case KEYLEFT:
			SnakeMove(keycode);
			break;
		case KEYESC:
			SnakeDead();
			return;
		default:
			return;
		} 
	}
	else if (state == END) {
		state = START;
		Init();
	}
} 

void Game::Init() {
	StateInit();
	BoardInit();
	di->drawStartPage();
}

void Game::StateInit() {
	head = center;
	snake.clear();
	snake.push_back(head);
}

void Game::BoardInit() {
	board = Board{ EMPTY };
	board[head.x][head.y] = SNAKE;
}

void Game::ReDraw() {
	switch (state) {
	case START:
		di->drawStartPage();
		break;
	case RUNNING:
		di->drawBoard(board);
		break;
	case END:
		di->drawEndPage();
		break;
	}
}

// game logics
vec2 Game::CreateTarget() {
	static std::random_device rnd;
	static std::default_random_engine rng{ rnd()};
	static std::uniform_int_distribution x_dist{ 0, board_x-1 };
	static std::uniform_int_distribution y_dist{ 0, board_y-1 };
	vec2 newTarget;
	do {
		newTarget.x = x_dist(rng);
		newTarget.y = y_dist(rng);
	} while (board[newTarget.x][newTarget.y] != EMPTY);
	return newTarget;
}

void Game::SnakeGrow() {
	snake.push_front(target);
	board[target.x][target.y] = SNAKE;
	di->drawBlock(target, board);
}
void Game::SnakeMove(Keycode direction) {
	if (InBoardMove(head, direction)) {
		// actually moved
		if (head == target) {
			SnakeGrow();
			target = CreateTarget();
			board[target.x][target.y] = TARGET;
			di->drawBlock(target, board);
		}
		else if(board[head.x][head.y]==SNAKE) {
			SnakeDead();
		}
		else {
			board[snake.back().x][snake.back().y] = EMPTY;
			di->drawBlock(snake.back(), board);
			snake.pop_back();
			board[head.x][head.y] = SNAKE;
			snake.push_front(head); 
			di->drawBlock(head, board);
		} 
	}

}
void Game::SnakeDead() {
	state = END; 
	di->drawEndPage();
}
bool Game::InBoardMove(vec2& pos, Keycode dir) {
	switch (dir) {
	case KEYUP:
		if (pos.y != 0) {
			--pos.y;
			return true;
		}
		break;
	case KEYDOWN:
		if (pos.y != board_y - 1) {
			++pos.y;
			return true; 
		}
		break;
	case KEYLEFT:
		if (pos.x != 0) {
			--pos.x;
			return true;
		}
		break;
	case KEYRIGHT:
		if (pos.x != board_x - 1) {
			++pos.x;
			return true; 
		}
		break;
	}
	return false;
}

