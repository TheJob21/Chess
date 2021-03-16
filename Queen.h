#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen:public Piece {
    public:
        Queen(int, int, char);
        Queen(int, int, char, int);
        bool moveIsValid(int, int, string (*)[8]);
        bool captureIsValid(int, int, string (*)[8]);
        void move(int, int, string (*)[8], Piece**);
        void update(string (*)[8], Piece**);
};
#endif