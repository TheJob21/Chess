#ifndef UTILITY_H
#define UTILITY_H

#include <fstream>
#include <iostream>
#include <string>
#include "Piece.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Bishop.h"
using namespace std;

Piece* findPiece(int, int, string (*)[8], Piece**, char);
void update(string (*)[8], Piece**);
int letterToNum(char);
int charToNum(char);
char numToLetter(int);
char numToChar(int);
void capture(int, int, char, string (*)[8], Piece**);
void promote(char, char, int, string (*)[8], Piece**);
void copyBoard(string (*)[8], string (*)[8], Piece**, Piece**);
void setBoard(string (*)[8], Piece**);
void printBoard(string (*)[8]);
void addMoves(string, int, Piece**, vector<int> &, vector<string> &);
void print(const string, ostream &);
void check3Reps(vector<vector<Int2>>, bool &, ostream &);
void copyPos(vector<vector<Int2>> &, Piece**);
bool badCheck(string (*)[8], Piece**, char);
void sort(vector<string> &, vector<int> &, Piece**, int);
void prioritizeByValue(int, int, string, ostream &, vector<string>, vector<int>, vector<string> &, vector<string> &, vector<string> &, vector<string> &, vector<int> &, vector<int> &, vector<int> &, vector<int> &);
#endif