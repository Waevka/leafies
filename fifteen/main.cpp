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
int boardHeight = N;
int boardWidth = N;
/////////////////////////////////////
int main(int argc, char *argv[])
{	
	srand((unsigned int)time(NULL));
	Listek *first = new Listek();
	Listek *winner = new Listek();
	initialize(first);
	int randomSteps = 12;
	int maxDepth = 20;
	bool melon = false;
	bool randomizeMoves = false;
	bool useHeuristics = false;
	int totalMoves = 0;
	solver s;
	dir order[4];
	
	// Setting search parameters:
	// If there are no arguments, use bfs and a default movelist.
	if (argc >= 0) {
		s = setStrategy("bfs");
		order[0] = LEFT; // default move strategy
		order[1] = DOWN;
		order[2] = RIGHT;
		order[3] = UP;
	}
	// If only the method is passed, set it and use a default movelist (set above)
	if (argc > 1) {
		s = setStrategy(argv[1]);
	}
	// Finally, if both arguments are passed, set them.
	if (argc > 2) {
		if (s == HEURISTIC) {
			useHeuristics = true;
			s = setStrategy(argv[2]);
		}
		else {
			setOrder(argv[2], order);
			if (order[0] == RANDOM) {
				randomizeMoves = true;
			}
		}
	}

	int solution;
	cout << "#### Wybierz opcje:";
	cout << "\n 1. Losowa generacja";
	cout << "\n 2. Wczytywanie z pliku input.txt";
	cout << "\n Wybor:  ";
	cin >> solution;
	cin.ignore();
	cout << "\n Podaj maksymalna glebokosc poszukiwan (maxDepth):  ";
	cin >> maxDepth;

	switch (solution)
	{ 
	case 1:
		cout << "\n Podaj ile losowych ruchow wykonac (randomSteps):  ";
		cin.ignore();
		cin >> randomSteps;
		cout << "\n#### Losowo wygenerowana plansza (Liczba krokow: " << randomSteps << "): ####\n";
		randomujTo(randomSteps, first);
		draw(first);
		break;
	case 2:
		cout << "\n#### Wczytuje z pliku:";
		first = loadBoard();
		initialize(winner);
		break;
	default:
		break;
	}
	
	
	cout << "\n#### Rozpoczynam rozwiazywanie planszy (Maksymalny poziom listka: " << maxDepth << ") ####";
	cout << "\n#### Porzadek przeszukiwania: " << (randomizeMoves ? "losowy" : "wczytany");
	cout << (useHeuristics? "\n#### Wybrano opcje heurystyki" : "");
	cout << "\n#### Wybrana strategia: ";

	switch (s) {
	case(BFS):
		cout << "BFS";
		melon = dawajBFS(first, maxDepth, winner, totalMoves, randomizeMoves, order, useHeuristics);
		break;
	case(DFS):
		cout << "DFS";
		melon = dawajDFS(first, maxDepth, winner, totalMoves, randomizeMoves, order, useHeuristics);
		break;
	case(DFS_ITERATIVE):
		cout << "DFS iteracyjny";
		melon = dawajIteracyjnyDFS(first, maxDepth, winner, totalMoves, randomizeMoves, order, useHeuristics);		
		break;
	default:
		cout << "\n!! Brak wybranej strategii! U¿ywam domyœlnie BFS";
		melon = dawajBFS(first, maxDepth, winner, totalMoves, randomizeMoves, order, useHeuristics);
		break;
	}

	cout << "\n\nCzy zagadka jest rozwiazywalna? : " << (melon? "tak!" : "nie :(" );
	if (melon) {
		cout << "\n\n Zwycieski listek: \n";
		drawNodeInfo(*winner);
	}
	cout << "\n\nOdwiedzone listki: " << totalMoves;
	cout << "\n\nRozwiazanie zostaje zapisane do pliku output.txt!";
	writeInfoToFile(winner->solution);

	cin.ignore();
	cin.get();
	return 0;
}