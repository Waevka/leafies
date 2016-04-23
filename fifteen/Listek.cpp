#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <queue>
#include "Listek.h"
#include "Functions.h"

Listek::Listek()
{
	tab = new int[N*N];
	initialize(this);
}

Listek::Listek(const Listek &toCopy) {
	tab = new int[N*N];
	tabCopy(tab, toCopy.tab);
	depth = toCopy.depth;
	solution = toCopy.solution;
	zeroPos = toCopy.zeroPos;
}

Listek::~Listek()
{
	delete[] this->tab;
}
