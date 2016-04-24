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
int main()
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
	int totalMoves = 0;

	cout << "#### Losowo wygenerowana plansza (Liczba krokow: " << randomSteps << "): ####\n";
	randomujTo(randomSteps, first);
	draw(first);
	cout << "\n#### Rozpoczynam rozwiazywanie planszy (Maksymalny poziom listka: " << maxDepth << ") ####";
	//melon = dawajBFS(first, maxDepth, winner, totalMoves);
	//melon = dawajDFS(first, maxDepth, winner, totalMoves); // Let's try some DFS instead!
	melon = dawajIteracyjnyBFS(first, maxDepth, winner, totalMoves); // iterative
	cout << "\n\nCzy zagadka jest rozwiazywalna? : " << (melon? "tak!" : "nie :(" );
	if (melon) {
		cout << "\n\n Zwycieski listek: \n";
		drawNodeInfo(*winner);
	}
	cout << "\n\nOdwiedzone listki: " << totalMoves;
	cin.get();
	return 0;
}