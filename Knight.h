#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include <iostream>
#include <string>
using namespace std;

class Knight:public Piece {
    public:
        Knight(int x, int y, char col);
        bool moveIsValid(int x, int y, string (*board)[8]);
        bool captureIsValid(int x, int y, string (*board)[8]);
        void move(int x, int y, string (*board)[8], Piece**);
        void update(string (*board)[8], Piece** pieces);
};
#endif