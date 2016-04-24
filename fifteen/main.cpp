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
	enum solver { BFS, DFS, DFS_ITERATIVE, HEURISTIC };
	srand((unsigned int)time(NULL));
	Listek *first = new Listek();
	Listek *winner = new Listek();
	initialize(first);
	draw(first);
	initialize(winner);
	int randomSteps = 15;
	int maxDepth = 30;
	bool melon = false;
	int totalMoves = 0;
	solver s;
	
	if (argc > 1) {
		string argument = argv[1];
		if (argument == "b" || argument == "bfs")
			s = BFS;
		if (argument == "d" || argument == "dfs")
			s = DFS;
		if (argument == "i" || argument == "idfs")
			s = DFS_ITERATIVE;
		//if(argv[1] == "a")
	}

	cout << "#### Losowo wygenerowana plansza (Liczba krokow: " << randomSteps << "): ####\n";
	randomujTo(randomSteps, first);
	draw(first);
	cout << "\n#### Rozpoczynam rozwiazywanie planszy (Maksymalny poziom listka: " << maxDepth << ") ####";
	cout << "\n#### Wybrana strategia: ";

	switch (s) {
	case(BFS):
		cout << "BFS";
		melon = dawajBFS(first, maxDepth, winner, totalMoves);
		break;
	case(DFS):
		cout << "DFS";
		melon = dawajDFS(first, maxDepth, winner, totalMoves);
		break;
	case(DFS_ITERATIVE):
		cout << "DFS iteracyjny";
		melon = dawajIteracyjnyDFS(first, maxDepth, winner, totalMoves);		
		break;
	case(HEURISTIC):
		cout << "Heurystyka";
		break;
	default:
		cout << "\n!! Brak wybranej strategii! U¿ywam domyœlnie BFS";
		melon = dawajBFS(first, maxDepth, winner, totalMoves);
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