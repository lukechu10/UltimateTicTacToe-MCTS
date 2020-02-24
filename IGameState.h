#pragma once

#include <vector>

template <typename Play>
class IGameState {
   public:
	virtual char playerToMove() const = 0;
	virtual std::vector<Play> moves() const = 0;
	virtual void applyMove(Play& p) = 0;
	virtual char winner() const = 0;
	virtual bool isTerminal() const = 0;
	virtual Play lastPlay() const = 0;
};