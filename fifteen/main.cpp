#include <iostream>
#include <iomanip>
#include <time.h>
#include <string>
#define N 4

using namespace std;
/////////////////////////////////////
enum dir { LEFT = -1, RIGHT = 1, UP = -N, DOWN = N };
void fill(int tab[]);
void draw(int tab[]);
void randomujTo(int ile, int tab[], string *s);
bool check(int pos, dir d);
void swapKappa(int tab[], int pos, dir d);
void reverseDir(dir d, dir *lastd);
void writeLetter(string *s, dir d);

int zeroPos;
/////////////////////////////////////


int main()
{   
	srand(time(NULL));
	int* matrix = new int[N*N];
	string solution = "";

	fill(matrix);
	draw(matrix);
	randomujTo(4, matrix, &solution);
	cout << endl;
	draw(matrix);
	cout << solution;

	cin.get();
	return 0;
}

//Fills the table with numbahs
void fill(int tab[]) {
	int count = 1;
	for (int i = 0; i < N*N; i++) {
			if (count != N*N) {
				tab[i] = count;
				count++;
			}
			else {
				tab[i] = 0;
				zeroPos = N*N-1;
			}
	}
}

//Draws the table
void draw(int tab[]) {
	for (int i = 0; i < N*N; i++) {
			cout << setw(5) << tab[i] << " ";
			if (i%N == N-1) { cout << endl; }
	}
}

//Randomly swaps tiles. Remembers last move to check and not repeat it in reverse.
void randomujTo(int ile, int tab[], string *s) {
	int count = 0;
	int randomek;
	dir d = DOWN;
	dir lastd = UP;

	while (count != ile) {
		randomek = rand() % 4;

		if (randomek == 0) { d = RIGHT; }
		else if (randomek == 1) { d = LEFT; }
		else if (randomek == 2) { d = DOWN; }
		else { d = UP; }

		if (check(zeroPos, d) && d != lastd) {
			swapKappa(tab, zeroPos, d);
			writeLetter(s, d);
			reverseDir(d, &lastd);
			zeroPos += d;
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
	int a = tab[pos+d];
	tab[pos + d] = tab[pos];
	tab[pos] = a;
}

//Reverses the position of d, since the enum holds values that cannot be changed in a simpler way
void reverseDir(dir d, dir *lastd) {
	switch (d)
	{
	case UP:
		*lastd = DOWN;
		break;
	case DOWN:
		*lastd = UP;
		break;
	case LEFT:
		*lastd = RIGHT;
		break;
	case RIGHT:
		*lastd = LEFT;
		break;
	default:
		break;
	}
}

void writeLetter(string *s, dir d) {
	switch (d) {
	case UP:
		*s += "D";
		break;
	case DOWN:
		*s += "U";
		break;
	case LEFT:
		*s += "R";
		break;
	case RIGHT:
		*s += "L";
		break;
	default:
		break;
	}
}
