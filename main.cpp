// Monte Carlo Tree Search.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <chrono>
#include <iostream>
#include <random>

#include "Game.h"
#include "MCTS.h"

using namespace std;

// Game::Play getMoveFromInput() {
// 	int row, col;
// 	cout << "Enter row (1-3):\n";
// 	cin >> row;
// 	cout << "Enter col (1-3):\n";
// 	cin >> col;

// 	if (row < 1 || row > 3 || col < 1 || col > 3) {
// 		cerr << "Invalid input!\n";
// 		return getMoveFromInput();
// 	}

// 	return Game::Play(row, col);
// }
double sims = 0;
int iterations = 0;
constexpr int timeout = 100;
Player simulateGame() {
	Game state;

	Player winner = state.winner();
	//cout << state << endl;
	while (!state.isTerminal()) {
		try {
			//cout << "Player to move: " << state.playerToMove() << endl;
			// X is MCTS, O is random
			if (state.playerToMove() == Player::X) {
				MCTS mcts(state);

				auto timeStart = chrono::steady_clock::now();
				SearchResult searchRes = mcts.runSearch(timeout);
				auto timeEnd = chrono::steady_clock::now();
				auto diff = timeEnd - timeStart;

				auto play = mcts.bestMove("robust");

				iterations++;
				sims += searchRes.visits;

				state.applyMove(play.bestPlay);

				cout << "This move took "
					 << chrono::duration<double, milli>(diff).count() << "ms"
					 << endl;  // print benchmark
				cout << "Root stats\tvisits: " << searchRes.visits
					 << "\twins: " << searchRes.wins << endl;  // stats
				cout << "Best Play stats\tvisits: " << play.bestVisits
					 << "\twins: " << play.bestWins << endl;
			} else {
				auto moves = state.moves();
				random_device r;
				default_random_engine generator{r()};
				uniform_int_distribution<int> distribution(0, moves.size() - 1);
				state.applyMove(moves[distribution(generator)]);
			}
		} catch (exception& e) {
			cerr << e.what() << endl;
		}

		//cout << state << endl;
		// debug
		/*for (auto& row : state.getWinCache()) {
			for (auto& col : row) cout << col;
			cout << endl;
		}*/
		winner = state.winner();
	}

	//cout << "Winner: " << winner << endl;

	return winner;
}

int main() {
	for (unsigned i = 0; i < 1; i++) {
		cout << simulateGame();
		flush(cout);
	}

	cout << "\nAverage simulations in " << timeout
		 << "ms: " << sims / iterations << endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
