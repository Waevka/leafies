#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#include <queue>
#define N 4

using namespace std;
/////////////////////////////////////
enum dir { LEFT = -1, NONE = 0, RIGHT = 1, UP = -N, DOWN = N };
class Listek;
void initialize(Listek *l);
void tabCopy(int a[], int b[]);
class Listek {
public:
	int* tab;
	int zeroPos;
	int depth;
	string solution;
	Listek() {
		tab = new int[N*N];
		initialize(this);
	}
	Listek(const Listek &toCopy) {
		tab = new int[N*N];
		tabCopy(tab, toCopy.tab);
		depth = toCopy.depth;
		solution = toCopy.solution;
		zeroPos = toCopy.zeroPos;

	}
	~Listek() {
		delete[] this->tab;
	}
};
void draw(Listek *l);
void randomujTo(int ile, Listek *l);
bool check(int pos, dir d);
void swapKappa(int tab[], int pos, dir d);
dir reverseDir(dir d);
dir returnLastDir(string s);
void writeLetter(string *s, dir d);
bool dawajBFS(Listek *begin, int depth, Listek *winner, int &totalMoves);
bool dawajDFS(Listek *begin, int depth, Listek *winner, int &totalMoves);
bool checkIfFinished(int tab[]);
void generateMoves(std::queue <Listek> *q);
Listek* makeANode(const Listek *last, dir d);
void copyLeaf(Listek *a, const Listek *b);
void drawNodeInfo(Listek l);
void clearMe(std::queue <Listek> *q);

/////////////////////////////////////
int main()
{
	srand((unsigned int)time(NULL));
	Listek *first = new Listek();
	Listek *winner = new Listek();
	initialize(first);
	draw(first);
	initialize(winner);
	int randomSteps = 17;
	int maxDepth = 20;
	bool melon = false;
	int totalMoves = 0;

	cout << "#### Losowo wygenerowana plansza (Liczba krokow: " << randomSteps << "): ####\n";
	randomujTo(randomSteps, first);
	draw(first);
	cout << "\n#### Rozpoczynam rozwiazywanie planszy (Maksymalny poziom listka: " << maxDepth << ") ####";
	melon = dawajBFS(first, maxDepth, winner, totalMoves);
	//melon = dawajDFS(first, maxDepth, winner, totalMoves); // Let's try some DFS instead!
	cout << "\n\nCzy zagadka jest rozwiazywalna? : " << (melon? "tak!" : "nie :(" );
	if (melon) {
		cout << "\n\n Zwycieski listek: \n";
		drawNodeInfo(*winner);
	}
	cout << "\n\nOdwiedzone listki: " << totalMoves;
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

bool dawajBFS(Listek *begin, int depth, Listek *winner, int &totalMoves) {
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
		}	else if (bingo.front().depth + 1 > depth) {
			finished = true;
		}	else {
			// time to add sum leaves
			generateMoves(&bingo);
			//delete[] bingo.front().tab;
			bingo.pop();
			totalMoves++;
		}
	}
	return solvable;
}

bool dawajDFS(Listek *begin, int depth, Listek *winner, int &totalMoves) {
	bool finished = false;
	bool solvable = false;

	while (finished == false) {
		/*if (checkIfFinished) {
			finished = true;
			solvable = true;
			copyLeafff
		}*/
	}

	return solvable;
}

bool DFSHelper(Listek oldL, int depth, Listek *winner) {
	if (checkIfFinished(oldL.tab)) {
		copyLeaf(winner, &oldL);
		//delete[] oldL.tab;
		return true;			// finished with success
	} else if ( depth == 0 ){	// finished with failure
		return false;
	} else {					// else keep diggin'
		
	}
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
	Listek *last = &(q->front());
	dir lastdir = returnLastDir(last->solution);
	lastdir = reverseDir(lastdir);
	Listek *newL;

	if (check(last->zeroPos, UP) && lastdir != UP) {
		newL = makeANode(last, UP);
		q->push(*newL);
		delete newL;
	}
	if (check(last->zeroPos, DOWN) && lastdir != DOWN) {
		newL = makeANode(last, DOWN);
		q->push(*newL);
		delete newL;
	}
	if (check(last->zeroPos, LEFT) && lastdir != LEFT) {
		newL = makeANode(last, LEFT);
		q->push(*newL);
		delete newL;
	}
	if (check(last->zeroPos, RIGHT) && lastdir != RIGHT){
		newL = makeANode(last, RIGHT);
		q->push(*newL);
		delete newL;
	}
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
	l->zeroPos += d;
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

void clearMe(std::queue <Listek> *q) {
	while (!q->empty()) {
		q->pop();
	}
	cout << "Finished clearing";
}