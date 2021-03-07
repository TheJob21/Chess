#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>
#include <iostream>
using namespace std;

class Rook:public Piece {
    public:
        Rook();
        Rook(int x, int y, char col);
        bool moveIsValid(int x, int y, string (*board)[8]);
        bool captureIsValid(int x, int y, string (*board)[8]);
        void move(int x, int y, string (*board)[8], Piece**);
        void update(string (*board)[8], Piece** pieces);
};
#endif