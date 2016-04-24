#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int* readInput(int &height, int &width, bool &read, int &zeropos);
bool readOutput(string &str, int &count);
void drawBoard(int height, int width, int tab[]);
void drawBoard(int height, int width, int tab[], int value, int zeropos);
int returnLastDir(string s, int height, int width, int i);
void simulate(int height, int width, int tab[], string solution, int zeropos, int solutionCount);
void swapKappa(int tab[], int &pos, int val);


int main()
{	
	int height = 0;
	int width = 0;
	int zeropos = 0;
	int *tab = nullptr;
	string solution = "";
	int solutionCount;
	bool inputRead = true;
	bool outputRead = true;

	cout << "#### Wizualizacja lamiglowki ####";
	cout << "Wczytuje dane z pliku input.txt i output.txt...";

	tab = readInput(height, width, inputRead, zeropos);
	outputRead = readOutput(solution, solutionCount);
	if (inputRead == false || outputRead == false) {
		cout << "\nWczytywanie nie powiodlo sie, sprawdz pliki! :(";
	}
	else {
		drawBoard(height, width, tab);
		cout << "\nWczytana plansza";
		simulate(height, width, tab, solution, zeropos, solutionCount);
	}


	cin.get();

	return 0;
}

int* readInput(int &height, int &width, bool &read, int &zeropos) {
	ifstream s;
	int *tab = nullptr;
	s.open("input.txt");
	if (s.is_open()) {
		s >> height;
		s >> width;
		tab = new int[height*width];
		int counter = 0;
		while (!s.eof()) {
			s >> tab[counter];
			if (tab[counter] == 0) {
				zeropos = counter;
			}
			counter++;
		}
	}
	else {
		read = false;
	}
	s.close();

	return tab;
}

bool readOutput(string &str, int &count) {
	ifstream s;
	bool success = true;
	s.open("output.txt");
	if (s.is_open()) {
		s >> count;
		s >> str;
	}
	else {
		success = false;
	}
	s.close();

	return success;
}

void drawBoard(int height, int width, int tab[]) {
	for (int i = 0; i < height*width; i++) {
		cout << setw(5) << tab[i] << " ";
		if (i%height == width - 1) { cout << endl; }
	}
}

void drawBoard(int height, int width, int tab[], int value, int zeropos) {
	bool mark = false;
	int w = 5;
	for (int i = 0; i < height*width; i++) {
		mark = false;
		w = 5;
		if (i == (zeropos - value) || i == zeropos) {
			mark = true;
			w = 5;
		}
		cout << setw(w) << (mark? "[":"") << tab[i] << (mark ? "]" : "") << " ";
		if (i%height == width - 1) { cout << endl; }
	}
}

int returnLastDir(string s, int height, int width, int i) {
	string c = s.substr(i, 1);
	int ret;
	if (c.compare("G") == 0) {
		ret = -width;
	}
	if (c.compare("D") == 0) {
		ret = width;
	}
	if (c.compare("L") == 0) {
		ret = -1;
	}
	if (c.compare("P") == 0) {
		ret = 1;
	}
	return ret;
}
void simulate(int height, int width, int tab[], string solution, int zeropos, int solutionCount) {
	int currMove;
	for (int i = 0; i < solutionCount; i++) {
		cout << "\n\n\n\n\n\n";
		cout << endl;
		currMove = returnLastDir(solution, height, width, i);
		swapKappa(tab, zeropos, currMove);
		drawBoard(height, width, tab, currMove, zeropos);
		cout << "\n#### " << i << " Wykonany ruch: " << solution.substr(i, 1);
	}
	cin.get();
}

void swapKappa(int tab[], int &pos, int val) {
	int a = tab[pos + val];
	tab[pos + val] = tab[pos];
	tab[pos] = a;
	pos = pos + val;
}