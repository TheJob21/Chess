#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include "Piece.h"
using namespace std;

Piece* findPiece(int, int, string (*)[8], Piece**, char);
#endif