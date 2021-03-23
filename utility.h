#ifndef UTILITY_H
#define UTILITY_H

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
#endif