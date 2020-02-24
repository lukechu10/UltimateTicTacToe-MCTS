#pragma once
#include <array>
#include <vector>

#include "IGameState.h"

struct Play {
	unsigned int row = 0;
	unsigned int col = 0;
	unsigned int subRow = 0;
	unsigned int subCol = 0;
	Play() {}
	Play(unsigned int row, unsigned int col, unsigned int subRow,
		 unsigned int subCol) {
		this->row = row;
		this->col = col;
		this->subRow = subRow;
		this->subCol = subCol;
	}
};

class Game : IGameState<Play> {
   public:
	Game();
	char playerToMove() const { return playerToMove_; }
	std::vector<Play> moves() const;
	void applyMove(Play& p);
	char winner() const;
	bool isTerminal() const;
	Play lastPlay() const { return lastPlay_; }

   private:
	using GameBoard =
		std::array<std::array<std::array<std::array<char, 3>, 3>, 3>, 3>;

	char playerToMove_ = '-';
	Play lastPlay_;
	GameBoard board;
};