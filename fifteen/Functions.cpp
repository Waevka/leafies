#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <queue>
#include <fstream>
#include "Functions.h"
#include "Listek.h"

using namespace std;
solver setStrategy(char arg[]) {
	string argument = arg;
	solver s;
	if (argument == "b" || argument == "bfs")
		s = BFS;
	if (argument == "d" || argument == "dfs")
		s = DFS;
	if (argument == "i" || argument == "idfs")
		s = DFS_ITERATIVE;
	if (argument == "a")
		s = HEURISTIC;
	return s;
}
void setOrder(char arg[], dir dirlist[]) {
	if (arg[0] == 'R') {
		dirlist[0] = RANDOM;
	}
	else if (arg[0] != 'L' || arg[0] != 'P' || arg[0] != 'G' || arg[0] != 'D') {
		dirlist[0] = RANDOM;
	}
	else {
		string letters = arg;
		for (int i = 0; i < 4; i++) {
			dirlist[i] = returnLastDir(letters.substr(i,1));
		}
	}
}
//Fills the table with numbahs
void initialize(Listek *l) {
	l->depth = 0;
	l->solution = "";

	int count = 1;
	for (int i = 0; i < boardHeight*boardWidth; i++) {
		if (count != boardHeight*boardWidth) {
			l->tab[i] = count;
			count++;
		}
		else {
			l->tab[i] = 0;
			l->zeroPos = boardHeight*boardWidth - 1;
		}
	}
}

void tabCopy(int a[], int b[]) {
	//copies from b to a
	for (int i = 0; i < boardHeight*boardWidth; i++) {
		a[i] = b[i];
	}
}

//Draws the table
void draw(Listek *l) {
	for (int i = 0; i < boardHeight*boardWidth; i++) {
		cout << setw(5) << l->tab[i] << " ";
		if (i%boardHeight == boardWidth - 1) { cout << endl; }
	}
}

//Randomly swaps tiles. Remembers last move to check and not repeat it in reverse.
void randomujTo(int ile, Listek *l) {
	int count = 0;
	dir d = DOWN;
	dir lastd = RIGHT;

	while (count != ile) {
		d = getRandomDirection();
		
		if (check(l->zeroPos, d) && d != lastd) {
			swapKappa(l->tab, l->zeroPos, d);
			lastd = reverseDir(d);
			l->zeroPos += dirVal(d);
			count++;
		}
	}
}

// Checks if a move is possible
// Can't move tiles in first row - > up, last column -> right, etc.
bool check(int pos, dir d) {
	bool youSmart = true;
	switch (d) {
	case UP:
		if ((pos - boardWidth) < 0) {
			youSmart = false;
		}
		break;
	case DOWN:
		if ((pos + boardWidth) > (boardHeight*boardWidth - 1)) {
			youSmart = false;
		}
		break;
	case LEFT:
		if ((pos%boardWidth - 1) <= 0) {
			youSmart = false;
		}
		break;
	case RIGHT:
		if ((pos%boardHeight + 1 >= boardHeight)) {
			youSmart = false;
		}
		break;
	}
	return youSmart;
}

//Swaps two tiles
void swapKappa(int tab[], int pos, dir d) {
	int dv = dirVal(d);
	int a = tab[pos + dv];
	tab[pos + dv] = tab[pos];
	tab[pos] = a;
}

//Reverses the position of d, since the enum holds values that cannot be changed in a simpler way
dir reverseDir(dir d) {
	dir lastd = NONE;
	switch (d)
	{
	case UP:
		lastd = DOWN;
		break;
	case DOWN:
		lastd = UP;
		break;
	case LEFT:
		lastd = RIGHT;
		break;
	case RIGHT:
		lastd = LEFT;
		break;
	default:
		break;
	}
	return lastd;
}

dir returnLastDir(string s) {
	dir returnik = NONE;
	if (s.length() == 0) {
		return NONE;
	}
	string c = s.substr(s.length() - 1);
	if (c.compare("G") == 0) {
		returnik = UP;
	}
	if (c.compare("D") == 0) {
		returnik = DOWN;
	}
	if (c.compare("L") == 0) {
		returnik = LEFT;
	}
	if (c.compare("P") == 0) {
		returnik = RIGHT;
	}
	return returnik;
}

void writeLetter(string *s, dir d) {
	switch (d) {
	case UP:
		*s += "G";
		break;
	case DOWN:
		*s += "D";
		break;
	case LEFT:
		*s += "L";
		break;
	case RIGHT:
		*s += "P";
		break;
	default:
		break;
	}
}

bool dawajBFS(Listek *begin, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur) {
	std::queue <Listek> bingo;
	bingo.push(*begin);
	bool finished = false;
	bool solvable = false;

	while (!bingo.empty() && finished == false) {
		if (checkIfFinished(bingo.front().tab)) {
			finished = true;
			solvable = true;
			copyLeaf(winner, &bingo.front());
			clearMe(&bingo);
		}
		else if (bingo.front().depth + 1 > depth) {
			finished = true;
		}
		else {
			if (randomize) {
				createRandomMoveset(movelist);
			}
			generateMoves(&bingo, movelist, heur);
			bingo.pop();
			totalMoves++;
		}
	}
	return solvable;
}

bool dawajDFS(Listek *begin, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur) {
	bool solvable = false;
	solvable = DFSHelper(*begin, depth, winner, totalMoves, randomize, movelist, heur);
	return solvable;
}

bool dawajIteracyjnyDFS(Listek *begin, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur) {
	int iteracja = 1;
	bool solvable = false;
	while (iteracja <= depth && !solvable) {
		cout << "\nIteracja nr " << iteracja << ", znaleziono rozwiazanie?... ";
		solvable = DFSHelper(*begin, iteracja, winner, totalMoves, randomize, movelist, heur);
		cout << (solvable ? "Tak!" : "Nie, wykonuje kolejna iteracje");
		iteracja++;
	}
	return solvable;
}

bool DFSHelper(Listek oldL, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur) {
	if (checkIfFinished(oldL.tab)) {
		copyLeaf(winner, &oldL);
		return true;			// finished with success
	}
	else if (depth == 0) {	// finished with failure
		return false;
	}
	else {					// else keep diggin'
		dir lastdir = returnLastDir(oldL.solution);
		lastdir = reverseDir(lastdir);
		Listek *newL;
		dir *thisNodeMovelist;
		bool solvable = false;
		totalMoves++;

		// For randomized movelists - create one for each node
		if (randomize) {
			thisNodeMovelist = new dir[4];
			createRandomMoveset(thisNodeMovelist);
		}
		else {
			thisNodeMovelist = movelist;
		}

		if (!heur) {
			for (int i = 0; i < 4; i++) {
				dir d = thisNodeMovelist[i];
				if (check(oldL.zeroPos, d) && lastdir != d && solvable == false) {
					newL = makeANode(&oldL, d);
					solvable = DFSHelper(*newL, depth - 1, winner, totalMoves, randomize, movelist, heur);
					delete newL;
				}
			}
		}
		else {
			Listek *ptr[4];
			int proper = 0;
			for (int i = 0; i < 4; i++) {
				dir d = thisNodeMovelist[i];
				if (check(oldL.zeroPos, d) && lastdir != d && solvable == false) {
					ptr[proper] = makeANode(&oldL, movelist[i]);
					proper++;
				}
			}
			sortHeuristicMoves(proper, ptr);
			for (int i = 0; i < proper; i++) {
				if (!solvable) {
					solvable = DFSHelper(*ptr[i], depth - 1, winner, totalMoves, randomize, movelist, heur);
				}
			}
		}

		if (randomize) {
			delete[] thisNodeMovelist;
		}
		return solvable;
	}
}

bool checkIfFinished(int tab[]) {
	int count = 1;
	bool valid = true;
	for (int i = 0; i < boardHeight*boardWidth; i++) {
		if (count != boardHeight*boardWidth) {
			if (tab[i] != count) {
				valid = false;
			}
			count++;
		}
		else {
			if (tab[i] != 0) {
				valid = false;
			}
		}
	}
	return valid;
}

void generateMoves(std::queue <Listek> *q, dir movelist[], bool heur) {
	Listek *last = &(q->front());
	dir lastdir = returnLastDir(last->solution);
	lastdir = reverseDir(lastdir);
	Listek *newL;

	if (!heur) {
		for (int i = 0; i < 4; i++) {
			if (check(last->zeroPos, movelist[i]) && lastdir != movelist[i]) {
				newL = makeANode(last, movelist[i]);
				q->push(*newL);
				delete newL;
			}
		}
	} // Use heuristics
	else {
		Listek *ptr[4];
		int proper = 0;
		for (int i = 0; i < 4; i++) {
			if (check(last->zeroPos, movelist[i]) && lastdir != movelist[i]) {
				ptr[proper] = makeANode(last, movelist[i]);
				proper++;
			}
		}
		sortHeuristicMoves(proper, ptr);
		for (int i = 0; i < proper; i++) {
			q->push(*ptr[i]);
		}
	}
	
}

void sortHeuristicMoves(int count, Listek* ptr[]) {
	int values[4];
	for (int i = 0; i < count; i++) {
		values[count] = calculateNodeValue(*ptr[i]);
	}
	 // sort them
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - (i + 1); j++) {
			if (values[j] > values[j + 1]) {
				int temp = values[j];
				Listek *tempL = new Listek(*ptr[j]);
				values[j] = values[j + 1];
				values[j + 1] = temp;
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = tempL;
			}
		}
	}
}

int calculateNodeValue(Listek &node) {
	int score = 0;
	for (int i = 0; i < boardHeight*boardWidth; i++) {
		if (node.tab[i] == i+1) {
			score++;
		}
	}
	if (node.tab[boardHeight*boardWidth] == 0) score++;
	return score;
}

Listek* makeANode(const Listek *last, dir d) {
	Listek *l = new Listek();
	initialize(l);
	tabCopy(l->tab, last->tab);
	l->depth = last->depth + 1;
	l->solution = last->solution;
	l->zeroPos = last->zeroPos;
	writeLetter(&(l->solution), d);
	swapKappa(l->tab, l->zeroPos, d);
	l->zeroPos += dirVal(d);
	return l;
}

void copyLeaf(Listek *a, const Listek *b) {
	tabCopy(a->tab, b->tab);
	a->depth = b->depth;
	a->solution = b->solution;
	a->zeroPos = b->zeroPos;
}

void drawNodeInfo(Listek l) {
	cout << "\n===========";
	cout << "\n|Depth: " << l.depth << " |";
	cout << "\n|Zeropos: " << l.zeroPos << " |";
	cout << "\n|Solution: " << l.solution << " |" << endl;
	draw(&l);
	cout << "\n===========";
}

void createRandomMoveset(dir dirs[]) {
	dirs[0] = getRandomDirection();
	for (int i = 1; i < 4; i++) {
		bool unique;
		dir d;
		do {
			unique = true;
			d = getRandomDirection();
			for (int j = 0; j < i; j++) {
				if (dirs[j] == d) unique = false;
			}
		} while (!unique);
		dirs[i] = d;
	}
}

dir getRandomDirection() {
	int randomek;
	dir d;
	randomek = rand() % 4;
	if (randomek == 0) { d = RIGHT; }
	else if (randomek == 1) { d = LEFT; }
	else if (randomek == 2) { d = DOWN; }
	else { d = UP; }
	return d;
}

void clearMe(std::queue <Listek> *q) {
	while (!q->empty()) {
		q->pop();
	}
}

int dirVal(dir d) {
	int h = boardWidth;
	int val;
	switch (d)
	{
	case UP:
		val = -boardWidth;
		break;
	case DOWN:
		val = boardWidth;
		break;
	case LEFT:
		val = -1;
		break;
	case RIGHT:
		val = 1;
		break;
	default:
		break;
	}
	return val;
}

Listek *loadBoard() {
	ifstream s;
	Listek *l;
	s.open("input.txt");
	if (s.is_open()) {
		s >> boardHeight;
		s >> boardWidth;
		l = new Listek();
		l->tab = new int[boardHeight*boardWidth];
		int counter = 0;
		while (!s.eof()) {
			s >> l->tab[counter];
			if (l->tab[counter] == 0) {
				l->zeroPos = counter;
			}
			counter++;
		}
	}
	else {
		l = new Listek(N, N);
	}
	s.close();
	
	return l;
}

void writeInfoToFile(string s) {
	int count = s.length();
	ofstream o;
	o.open("output.txt");
	if (o.is_open()) {
		if (count == 0) {
			o << -1;
		}
		else {
			o << count << endl;
			o << s;
		}
	}
	else {
		cout << "/n  Error writing to file, omitting...";
	}
	o.close();
}