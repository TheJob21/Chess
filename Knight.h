#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight:public Piece {
    public:
        Knight(int, int, char);
        Knight(int, int, char, int);
        bool moveIsValid(int, int, string (*)[8]);
        bool captureIsValid(int, int, string (*)[8]);
        void move(int, int, string (*)[8], Piece**);
        void update(string (*)[8], Piece** );
};
#endif