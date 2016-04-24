#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <queue>
#include "Listek.h"
#include "Functions.h"

Listek::Listek()
{
	tab = new int[boardHeight*boardWidth];
	initialize(this);
}

Listek::Listek(int x, int y)
{
	tab = new int[x*y];
	initialize(this);
}

Listek::Listek(const Listek &toCopy) {
	tab = new int[boardHeight*boardWidth];
	tabCopy(tab, toCopy.tab);
	depth = toCopy.depth;
	solution = toCopy.solution;
	zeroPos = toCopy.zeroPos;
}

Listek::~Listek()
{
	delete[] this->tab;
}
