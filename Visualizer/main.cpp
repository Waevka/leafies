#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int* readInput(int &height, int &width, bool &read, int &zeropos);
bool readOutput(string &str, int &count);
void drawBoard(int height, int width, int tab[]);

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
		cout << "\Wczytana plansza";
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