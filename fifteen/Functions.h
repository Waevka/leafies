#pragma once
#include <iostream>
#include <string>
#define N 4

/////////////////////////////////////////////////////////////////
enum dir { LEFT = -1, NONE = 0, RIGHT = 1, UP = -N, DOWN = N, RANDOM };
enum solver { BFS, DFS, DFS_ITERATIVE, HEURISTIC };
class Listek;
/////////////////////////////////////////////////////////////////
solver setStrategy(char arg[]);
void setOrder(char arg[], dir dirlist[]);
void initialize(Listek *l);
void tabCopy(int a[], int b[]);
void draw(Listek *l);
void randomujTo(int ile, Listek *l);
bool check(int pos, dir d);
void swapKappa(int tab[], int pos, dir d);
dir reverseDir(dir d);
dir returnLastDir(std::string s);
void writeLetter(std::string *s, dir d);
bool dawajBFS(Listek *begin, int depth, Listek *winner, int &totalMoves);
bool dawajDFS(Listek *begin, int depth, Listek *winner, int &totalMoves);
bool dawajIteracyjnyDFS(Listek *begin, int depth, Listek *winner, int &totalMoves);
bool DFSHelper(Listek oldL, int depth, Listek *winner, int &totalMoves);
bool checkIfFinished(int tab[]);
void generateMoves(std::queue <Listek> *q);
Listek* makeANode(const Listek *last, dir d);
void copyLeaf(Listek *a, const Listek *b);
void drawNodeInfo(Listek l);
void clearMe(std::queue <Listek> *q);
