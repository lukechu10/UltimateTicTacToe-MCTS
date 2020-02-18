#pragma once

#include <array>
#include <iostream>
#include <vector>

class Game {
   public:
	struct Play {
		int row = 0;
		int col = 0;
		Play() {}
		Play(int row, int col) {
			this->row = row;
			this->col = col;
		}
	};

	Game();

	const std::array<std::array<char, 3>, 3>& getBoard() { return board; }

	/**
	 * @brief Next player to move
	 *
	 * @return '-' on start, 'x' or 'o'
	 */
	char playerToMove() const { return playerToMove_; }

	std::vector<Play> moves() const;

	void applyMove(Play& m) {
		board[m.row][m.col] = playerToMove_;
		playerToMove_ = (playerToMove_ == 'x' ? 'o' : 'x'); // flip next player
		lastPlay_ = m;
	}

	char winner() const;

	bool isTerminal() const { return winner() != '-' || moves().size() == 0; }

	Play lastPlay() const { return lastPlay_; }

	friend std::ostream& operator<<(std::ostream& os, Game& g) {
		for (auto& row : g.getBoard()) {
			for (auto& col : row) {
				os << col << " ";
			}
			os << std::endl;
		}
		return os;
	}

   private:
	std::array<std::array<char, 3>, 3> board;
	char playerToMove_ = 'x';
	Play lastPlay_;
};
