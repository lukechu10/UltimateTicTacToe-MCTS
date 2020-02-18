#pragma once

#include "Node.h"

struct SearchResult {
	int visits = 0;
	int wins = 0;
	SearchResult(int visits, int wins) {
		this->visits = visits;
		this->wins = wins;
		
	}
};

struct BestResult {
	int bestVisits = 0;
	int bestWins = 0;
	Game::Play bestPlay;
	BestResult(int bestVisits, int bestWins, Game::Play bestPlay) {
		this->bestVisits = bestVisits;
		this->bestWins = bestWins;
		this->bestPlay = bestPlay;
	}
};

class MCTS {
   public:
	Node* traverse();

	SearchResult runSearch(double timeout = 1000);

	BestResult bestMove(std::string policy = "robust");

	MCTS(Game g) { root = new Node(nullptr, g); }
	~MCTS() { delete root; }

   private:
	Node* root;
};
