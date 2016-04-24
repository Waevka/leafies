#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <queue>
#include "Listek.h"
#include "Functions.h"

using namespace std;
/////////////////////////////////////
class Listek;
/////////////////////////////////////
int main(int argc, char *argv[])
{	
	srand((unsigned int)time(NULL));
	Listek *first = new Listek();
	Listek *winner = new Listek();
	initialize(first);
	draw(first);
	initialize(winner);
	int randomSteps = 15;
	int maxDepth = 30;
	bool melon = false;
	bool randomizeMoves = false;
	int totalMoves = 0;
	solver s;
	dir order[4];
	
	if (argc > 1) {
		s = setStrategy(argv[1]);
	}
	if (argc > 2) {
		//setOrder(argv[2], order);
		createRandomMoveset(order);
		if (order[1] == RANDOM) {
			randomizeMoves = true;
		}
	}
	
	cout << "#### Losowo wygenerowana plansza (Liczba krokow: " << randomSteps << "): ####\n";
	randomujTo(randomSteps, first);
	draw(first);
	cout << "\n#### Rozpoczynam rozwiazywanie planszy (Maksymalny poziom listka: " << maxDepth << ") ####";
	cout << "\n#### Wybrana strategia: ";

	switch (s) {
	case(BFS):
		cout << "BFS";
		melon = dawajBFS(first, maxDepth, winner, totalMoves, randomizeMoves, order);
		break;
	case(DFS):
		cout << "DFS";
		melon = dawajDFS(first, maxDepth, winner, totalMoves, randomizeMoves, order);
		break;
	case(DFS_ITERATIVE):
		cout << "DFS iteracyjny";
		melon = dawajIteracyjnyDFS(first, maxDepth, winner, totalMoves, randomizeMoves, order);		
		break;
	case(HEURISTIC):
		cout << "Heurystyka";
		break;
	default:
		cout << "\n!! Brak wybranej strategii! U¿ywam domyœlnie BFS";
		melon = dawajBFS(first, maxDepth, winner, totalMoves, randomizeMoves, order);
		break;
	}

	cout << "\n\nCzy zagadka jest rozwiazywalna? : " << (melon? "tak!" : "nie :(" );
	if (melon) {
		cout << "\n\n Zwycieski listek: \n";
		drawNodeInfo(*winner);
	}
	cout << "\n\nOdwiedzone listki: " << totalMoves;
	cin.get();
	return 0;
}