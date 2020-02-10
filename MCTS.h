#pragma once

#include "Node.h"

struct SearchResult {
	int iterations = 0;
	SearchResult(int iterations) { this->iterations = iterations; }
};

class MCTS {
public:
	Node* traverse();

	SearchResult runSearch(double timeout = 1000);

	Game::Play bestMove();

	MCTS(Game g) {
		root = new Node(nullptr, g);
	}
	~MCTS() {
		delete root;
	}

private:
	Node* root;
};

