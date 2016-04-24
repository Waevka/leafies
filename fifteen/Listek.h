#pragma once
#include <iostream>
#include <string>

extern int boardHeight;
extern int boardWidth;

class Listek
{
public:
	int* tab;
	int zeroPos;
	int depth;
	std::string solution;
	Listek();
	Listek::Listek(int x, int y);
	Listek(const Listek &toCopy);
	~Listek();
};

