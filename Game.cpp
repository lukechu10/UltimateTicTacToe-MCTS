#include "Game.h"

Game::Game() {
	std::array<std::array<char, 3>, 3> temp;
	for (auto &row : temp) {  // initialize game board
		row.fill('-');
	}
	board = temp;
}

std::vector<Game::Play> Game::moves() const {
	std::vector<Play> out;
	for (unsigned i = 0; i < board.size(); i++) {
		for (unsigned j = 0; j < board[i].size(); j++) {
			if (board[i][j] == '-') out.push_back(Play(i, j));
		}
	}
	return out;
}

char Game::winner() const {
	// Checking for Rows for X or O victory.
	for (int row = 0; row < 3; row++) {
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
			if (board[row][0] == 'x')
				return 'x';
			else if (board[row][0] == 'o')
				return 'o';
		}
	}
	// Checking for Columns for X or O victory.
	for (int col = 0; col < 3; col++) {
		if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
			if (board[0][col] == 'x')
				return 'x';
			else if (board[0][col] == 'o')
				return 'o';
		}
	}
	// Checking for Diagonals for X or O victory.
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
		if (board[0][0] == 'x')
			return 'x';
		else if (board[0][0] == 'o')
			return 'o';
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
		if (board[0][2] == 'x')
			return 'x';
		else if (board[0][2] == 'o')
			return 'o';
	}
	// Else if none of them have won then return none
	return '-';
}
