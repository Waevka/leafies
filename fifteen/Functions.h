#pragma once
#include <iostream>
#include <string>
#define N 4

/////////////////////////////////////////////////////////////////
enum dir { LEFT = -1, NONE = 0, RIGHT = 1, UP = -N, DOWN = N, RANDOM };
enum solver { BFS, DFS, DFS_ITERATIVE, HEURISTIC };
class Listek;
extern int boardHeight;
extern int boardWidth;
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
bool dawajBFS(Listek *begin, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur);
bool dawajDFS(Listek *begin, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur);
bool dawajIteracyjnyDFS(Listek *begin, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur);
bool DFSHelper(Listek oldL, int depth, Listek *winner, int &totalMoves, bool randomize, dir movelist[], bool heur);
bool checkIfFinished(int tab[]);
void generateMoves(std::queue <Listek> *q, dir movelist[], bool heur);
void sortHeuristicMoves(int proper, Listek* ptr[]);
int calculateNodeValue(Listek &node);
Listek* makeANode(const Listek *last, dir d);
void copyLeaf(Listek *a, const Listek *b);
void drawNodeInfo(Listek l);
void createRandomMoveset(dir dirs[]);
dir getRandomDirection();
void clearMe(std::queue <Listek> *q);
int dirVal(dir d);
Listek *loadBoard();
void writeInfoToFile(std::string s);
