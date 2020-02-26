#include "Game.h"
using namespace std;

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
			// get moves is subWins[data.subNextRow][data.subNextCol]
			for (unsigned row = 0; row < 3; row++) {
				for (unsigned col = 0; col < 3; col++) {
					if (board[nextSubRow][nextSubCol][row][col] ==
						Player::None) {
						results.push_back(Play(nextSubRow, nextSubCol, row, col));
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