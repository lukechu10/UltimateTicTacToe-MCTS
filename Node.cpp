#include "Node.h"

using namespace std;

Node *Node::selectBestChildUCT() {
	Node *best = nullptr;
	double bestScore = -INFINITY;
	for (auto &child : children) {
		double score = (child->winCount() / child->visitCount()) +
					   C_PARAM * sqrt(log(winCount()) /
									  child->visitCount());	 // UCB1 formula
		if (score > bestScore) {
			bestScore = score;
			best = child;
		}
	}
	return best;
}

Node *Node::expand() {
	// select random unexpanded node
	uniform_int_distribution<int> distribution(0, unexpandedNodes.size() - 1);
	int i = distribution(generator);
	Game::Play play = unexpandedNodes[i];
	unexpandedNodes.erase(unexpandedNodes.begin() + i);
	// expand node
	Game state(this->state);
	state.applyMove(play);
	Node *node = new Node(this, state);
	// add to children vector
	children.push_back(node);
	return node;
}

char Node::simulate() {
	// choose random moves until terminal
	Game tempState(this->state);

	while (!tempState.isTerminal()) {
		vector<Game::Play> moves = tempState.moves();
		// pick random move
		uniform_int_distribution<int> distribution(0, moves.size() - 1);
		Game::Play move = moves[distribution(generator)];
		tempState.applyMove(move);	// advance state
	}
	return tempState.winner();
}

void Node::backpropagate(char winner) {
	visits++;
	if ((state.playerToMove() == 'x' ? 'o' : 'x') == winner) {
		wins++;
	} else if (winner == '-') {
		wins += 0.5;
	}
	// backpropagate parent
	if (parent != nullptr) parent->backpropagate(winner);
}

bool Node::fullyExpanded() { return unexpandedNodes.size() == 0; }

bool Node::isLeaf() { return state.isTerminal(); }

Node::Node(Node *parent, Game state) {
	this->parent = parent;
	this->state = state;

	// compute unexpanded nodes
	unexpandedNodes = state.moves();
}

Node::~Node() {
	// delete children
	for (size_t i = 0; i < children.size(); i++) {
		delete children[i];
	}
}
