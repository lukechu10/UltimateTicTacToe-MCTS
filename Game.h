#pragma once
#include <array>
#include <iostream>
#include <vector>

#include "IGameState.h"

enum class Player : char {
	None = 0,
	X,
	O,
	Full  // for winCache if quadrant has no more availible moves
};

// std::ostream& operator<<(std::ostream& os, const Player& p) {
// 	switch (p) {
// 		case Player::X:
// 			os << "X";
// 			break;
// 		case Player::O:
// 			os << "O";
// 			break;
// 		case Player::None:
// 			os << " ";
// 			break;
// 		default:
// 			os << " ";
// 	}
// 	return os;
// }

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

class Game : IGameState<Play, Player> {
   public:
	Game();
	Player playerToMove() const { return playerToMove_; }
	std::vector<Play> moves() const;
	void applyMove(Play& p);
	Player winner() const;
	bool isTerminal() const;
	Play lastPlay() const { return lastPlay_; }

	friend std::ostream& operator<<(std::ostream& os, Game& g) {
		os << "TODO" << std::endl;
		return os;
	}

   private:
	Player checkGlobalWin() const;
	void updateWinCache(unsigned row, unsigned col);

	using GameBoard =
		std::array<std::array<std::array<std::array<Player, 3>, 3>, 3>, 3>;

	Player playerToMove_ = Player::X;  // x starts
	int nextSubRow = -1;
	int nextSubCol = -1;
	Play lastPlay_;
	GameBoard board;
	std::array<std::array<Player, 3>, 3> winCache;
};