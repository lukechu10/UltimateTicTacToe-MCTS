#include <exception>

#include "MCTS.h"

using namespace std;

Node* MCTS::traverse() {
	// start at tree root
	Node* node = root;
	while (node->fullyExpanded() && !node->isLeaf()) {
		Node* temp = node->selectBestChildUCT();
		if (temp == nullptr) break;
		else node = temp;
	}
	return node;
}

void MCTS::runSearch() {
	// run 4 phases until no more time left
	int i = 0;
	while (++i < 1000000) {
		// run 100 simulations
		Node* node = traverse(); // phase 1 - selection
		if (node->fullyExpanded()) break; // entire tree is searched
		Node* expandedNode = node->expand(); // phase 2 - expansion
		char winner = expandedNode->simulate(); // phase 3 - simulation
		expandedNode->backpropagate(winner);
	}
}

Game::Play MCTS::bestMove() {
	// check if root is fully expanded
	if (!root->fullyExpanded()) {
		throw exception("Root is not fully expanded. There is not enough information");
	}
	// find child with most visits
	int visitsBest = 0;
	Game::Play bestPlay;
	for (auto& child : root->getChildren()) {
		if (child->visitCount() > visitsBest) {
			visitsBest = child->visitCount();
			bestPlay = child->getState().lastPlay();
		}
	}

	return bestPlay;
}
