#include "Game.h"
using namespace std;

Game::Game() {
	// initialize all Player values to Player::None
	for (auto& row : board)
		for (auto& col : row)
			for (auto& subRow : col) subRow.fill(Player::None);
	for (auto& row : winCache)
		row.fill(Player::None);
}

vector<Play> Game::moves() const {
	vector<Play> results;

	// check if subNext == -1 -1 or subWin set
	if ((nextSubRow == -1 && nextSubCol == -1) ||
		winCache[nextSubRow][nextSubCol] != Player::None) {
		// get all tiles availible
		for (unsigned winRow = 0; winRow < 3; winRow++) {
			for (unsigned winCol = 0; winCol < 3; winCol++) {
				if (winCache[winRow][winCol] == Player::None) {
					// get all empty squares
					for (unsigned subRow = 0; subRow < 3; subRow++) {
						for (unsigned subCol = 0; subCol < 3; subCol++) {
							if (board[winRow][winCol][subRow][subCol] ==
								Player::None) {
								results.push_back(
									Play(winRow, winCol, subRow, subCol));
							}
						}
					}
					//
				}
			}
		}
	}

	else {
		if (winCache[nextSubRow][nextSubCol] == Player::None) {
			// get moves is winCache[nextSubRow][nextSubCol]
			for (unsigned row = 0; row < 3; row++) {
				for (unsigned col = 0; col < 3; col++) {
					if (board[nextSubRow][nextSubCol][row][col] ==
						Player::None) {
						results.push_back(
							Play(nextSubRow, nextSubCol, row, col));
					}
				}
			}
		}
	}

	return results;
}

void Game::applyMove(Play &p) {
	board[p.row][p.col][p.subRow][p.subCol] = playerToMove_;
	// toggle player to move
	playerToMove_ = playerToMove_ == Player::X ? Player::O : Player::X;
	// update next sub row
	nextSubRow = p.subRow;
	nextSubCol = p.subCol;
	updateWinCache(p.row, p.col);  // check for win
}

Player Game::winner() const { return checkGlobalWin(); }

bool Game::isTerminal() const {
	return checkGlobalWin() == Player::None && moves().size() != 0;
}

Player Game::checkGlobalWin() const {
	// Checking for Rows for X or O victory.
	for (int row = 0; row < 3; row++) {
		if (winCache[row][0] == winCache[row][1] &&
			winCache[row][1] == winCache[row][2] &&
			winCache[row][0] != Player::None &&
			winCache[row][0] != Player::Full) {
			return winCache[row][0];
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col < 3; col++) {
		if (winCache[0][col] == winCache[1][col] &&
			winCache[1][col] == winCache[2][col] &&
			winCache[0][col] != Player::None &&
			winCache[0][col] != Player::Full) {
			return winCache[0][col];
		}
	}

	// Checking for Diagonals for X or O victory.
	if (winCache[0][0] == winCache[1][1] && winCache[1][1] == winCache[2][2] &&
		winCache[0][0] != Player::None && winCache[0][0] != Player::Full) {
		return winCache[0][0];
	}

	if (winCache[0][2] == winCache[1][1] && winCache[1][1] == winCache[2][0] &&
		winCache[0][2] != Player::None && winCache[0][2] != Player::Full) {
		return winCache[0][2];
	}

	// Else if none of them have won then return 0
	return Player::None;
	// Win check
}

void Game::updateWinCache(unsigned gRow, unsigned gCol) {
	// check for win in sub gameboard
	auto& subBoard = board[gRow][gCol];
	// Checking for Rows for X or O victory.
	for (int row = 0; row < 3; row++) {
		if (subBoard[row][0] == subBoard[row][1] &&
			subBoard[row][1] == subBoard[row][2] &&
			subBoard[row][0] != Player::None &&
			subBoard[row][0] != Player::Full) {
			winCache[gRow][gCol] = subBoard[row][0];
			return;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col < 3; col++) {
		if (subBoard[0][col] == subBoard[1][col] &&
			subBoard[1][col] == subBoard[2][col] &&
			subBoard[0][col] != Player::None &&
			subBoard[0][col] != Player::Full) {
			winCache[gRow][gCol] = subBoard[0][col];
			return;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (subBoard[0][0] == subBoard[1][1] && subBoard[1][1] == subBoard[2][2] &&
		subBoard[0][0] != Player::None && subBoard[0][0] != Player::Full) {
		winCache[gRow][gCol] = subBoard[0][0];
		return;
	}

	if (subBoard[0][2] == subBoard[1][1] && subBoard[1][1] == subBoard[2][0] &&
		subBoard[0][2] != Player::None && subBoard[0][2] != Player::Full) {
		winCache[gRow][gCol] = subBoard[0][2];
		return;
	}

	// Check for full
	for (auto& row : subBoard) {
		for (auto& col : row) {
			if (col == Player::None) {
				winCache[gRow][gCol] = Player::Full;
				return;
			}
		}
	}
	return;
}