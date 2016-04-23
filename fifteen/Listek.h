#pragma once
#include <iostream>
#include <string>

class Listek
{
public:
	int* tab;
	int zeroPos;
	int depth;
	std::string solution;
	Listek();
	Listek(const Listek &toCopy);
	~Listek();
};

