#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <queue>
#define N 4

using namespace std;
/////////////////////////////////////
enum dir { LEFT = -1, NONE = 0, RIGHT = 1, UP = -N, DOWN = N };
struct Listek {
	int* tab = new int[N*N];
	int zeroPos;
	int depth;
	string solution;
};
void initialize(Listek *l);
void tabCopy(int a[], int b[]);
void draw(Listek *l);
void randomujTo(int ile, Listek *l);
bool check(int pos, dir d);
void swapKappa(int tab[], int pos, dir d);
dir reverseDir(dir d);
dir returnLastDir(string s);
void writeLetter(string *s, dir d);
bool dawajBFS(Listek *begin, int depth, Listek *winner);
bool checkIfFinished(int tab[]);
void generateMoves(std::queue <Listek> *q);
Listek *makeANode(Listek last, dir d);
Listek *copyLeaf(Listek c);
void drawNodeInfo(Listek l);

/////////////////////////////////////
int main()
{
	srand(time(NULL));
	Listek *first = new Listek();
	Listek *winner = new Listek();

	initialize(first);
	cout << "\n\n CASE 1: ------------------------------------\n";
	draw(first);
	cout << endl << "\nValid tabliczka: " << checkIfFinished(first->tab);
	cout << "\nzagadka jest rozwiazywalna? : " << dawajBFS(first, 1, winner);
	cout << "\n\n The winner leaf: \n";
	draw(winner);
	cout << "\n\n CASE 2: ------------------------------------\n";
	randomujTo(1, first);
	cout << endl;
	draw(first);
	cout << endl << "\nValid tabliczka: " << checkIfFinished(first->tab);
	cout << "\nzagadka jest rozwiazywalna? : " << dawajBFS(first, 2, winner);
	cout << "\n\n The winner leaf: \n";
	draw(winner);
	cin.get();
	return 0;
}

//Fills the table with numbahs
void initialize(Listek *l) {
	l->depth = 0;
	l->solution = "";

	int count = 1;
	for (int i = 0; i < N*N; i++) {
		if (count != N*N) {
			l->tab[i] = count;
			count++;
		}
		else {
			l->tab[i] = 0;
			l->zeroPos = N*N - 1;
		}
	}
}

void tabCopy(int a[], int b[]) {
	//copies from b to a
	for (int i = 0; i < N*N; i++) {
		a[i] = b[i];
	}
}

//Draws the table
void draw(Listek *l) {
	for (int i = 0; i < N*N; i++) {
		cout << setw(5) << l->tab[i] << " ";
		if (i%N == N - 1) { cout << endl; }
	}
}

//Randomly swaps tiles. Remembers last move to check and not repeat it in reverse.
void randomujTo(int ile, Listek *l) {
	int count = 0;
	int randomek;
	dir d = DOWN;
	dir lastd = RIGHT;

	while (count != ile) {
		randomek = rand() % 4;

		if (randomek == 0) { d = RIGHT; }
		else if (randomek == 1) { d = LEFT; }
		else if (randomek == 2) { d = DOWN; }
		else { d = UP; }

		if (check(l->zeroPos, d) && d != lastd) {
			swapKappa(l->tab, l->zeroPos, d);
			lastd = reverseDir(d);
			l->zeroPos += d;
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
		if ((pos - N) < 0) {
			youSmart = false;
		}
		break;
	case DOWN:
		if ((pos + N) > (N*N - 1)) {
			youSmart = false;
		}
		break;
	case LEFT:
		if ((pos%N - 1) <= 0) {
			youSmart = false;
		}
		break;
	case RIGHT:
		if ((pos%N + 1 >= N)) {
			youSmart = false;
		}
		break;
	}
	return youSmart;
}

//Swaps two tiles
void swapKappa(int tab[], int pos, dir d) {
	int a = tab[pos + d];
	tab[pos + d] = tab[pos];
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
	if (c.compare("U") == 0) {
		returnik = UP;
	}
	if (c.compare("D") == 0) {
		returnik = DOWN;
	}
	if (c.compare("L") == 0) {
		returnik = LEFT;
	}
	if (c.compare("R") == 0) {
		returnik = RIGHT;
	}
	return returnik;
}

void writeLetter(string *s, dir d) {
	switch (d) {
	case UP:
		*s += "U";
		break;
	case DOWN:
		*s += "D";
		break;
	case LEFT:
		*s += "L";
		break;
	case RIGHT:
		*s += "R";
		break;
	default:
		break;
	}
}

bool dawajBFS(Listek *begin, int depth, Listek *winner) {
	std::queue <Listek> *bingo = new queue <Listek>();
	bingo->push(*begin);
	drawNodeInfo(*begin);
	bool finished = false;
	bool solvable = false;

	while (!bingo->empty() && finished == false) {
		if (checkIfFinished(bingo->front().tab)) {
			finished = true;
			solvable = true;
			winner = copyLeaf(bingo->front());
			cout << "\nqueue finished with success";
		}	else if (bingo->front().depth + 1 > depth) {
			finished = true;
		}	else {
			// time to add sum leaves
			generateMoves(bingo);
			bingo->pop();
		}
	}
	return solvable;
}

bool checkIfFinished(int tab[]) {
	int count = 1;
	bool valid = true;
	for (int i = 0; i < N*N; i++) {
		if (count != N*N) {
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

void generateMoves(std::queue <Listek> *q) {
	Listek last = q->front();
	dir lastdir = returnLastDir(last.solution);
	lastdir = reverseDir(lastdir);

	if (check(last.zeroPos, UP) && lastdir != UP) {
		Listek *pushMe;
		cout << "\nUP possible";
		pushMe = makeANode(last, UP);
		q->push(*pushMe);
		drawNodeInfo(*pushMe);
	}
	if (check(last.zeroPos, DOWN) && lastdir != DOWN) {
		Listek *pushMe;
		cout << "\nDOWN possible";
		pushMe = makeANode(last, DOWN);
		q->push(*pushMe);
		drawNodeInfo(*pushMe);
	}
	if (check(last.zeroPos, LEFT) && lastdir != LEFT) {
		Listek *pushMe;
		cout << "\nLEFT possible";
		pushMe = makeANode(last, LEFT);
		q->push(*pushMe);
		drawNodeInfo(*pushMe);
	}
	if (check(last.zeroPos, RIGHT) && lastdir != RIGHT){
		Listek *pushMe;
		cout << "\nRIGHT possible";
		pushMe = makeANode(last, RIGHT);
		q->push(*pushMe);
		drawNodeInfo(*pushMe);
	}
}

Listek *makeANode(Listek last, dir d) {
	Listek *l = new Listek();
	tabCopy(l->tab, last.tab);
	l->depth = last.depth + 1;
	l->solution = last.solution;
	l->zeroPos = last.zeroPos;
	writeLetter(&(l->solution), d);
	swapKappa(l->tab, l->zeroPos, d);
	l->zeroPos += d;
	return l;
}

Listek *copyLeaf(Listek c) {
	Listek *l = new Listek();
	tabCopy(l->tab, c.tab);
	l->depth = c.depth;
	l->solution = c.solution;
	l->zeroPos = c.zeroPos;
	return l;
}

void drawNodeInfo(Listek l) {
	cout << "\n===========";
	cout << "\n|Depth:" << l.depth << " |";
	cout << "\n|Zeropos:" << l.zeroPos << " |";
	cout << "\n|Solution: " << l.solution << " |" << endl;
	draw(&l);
	cout << "\n===========";
}
