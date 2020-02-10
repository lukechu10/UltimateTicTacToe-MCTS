#pragma once

#include "Node.h"

class MCTS {
public:
	Node* traverse();

	void runSearch();

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

