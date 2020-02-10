// Monte Carlo Tree Search.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

#include "Game.h"
#include "MCTS.h"

using namespace std;

int main()
{
	Game state;

	char winner = state.winner();
	cout << state << endl;
	while (!state.isTerminal()) {
		MCTS mcts(state);

		auto timeStart = chrono::steady_clock::now();
		SearchResult searchRes = mcts.runSearch();
		auto timeEnd = chrono::steady_clock::now();
		auto diff = timeEnd - timeStart;

		try {
			auto play = mcts.bestMove();
			state.applyMove(play);
		}
		catch (exception & e) {
			cerr << e.what() << endl;
		}
		cout << "This move took " << chrono::duration<double, milli>(diff).count() << "ms. Simulated " << searchRes.iterations << " game(s)." << endl; // print benchmark
		cout << state << endl;
		winner = state.winner();
	}

	cout << winner;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
