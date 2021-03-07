#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen:public Piece {
    public:
        Queen(int x, int y, char col);
        bool moveIsValid(int x, int y, string (*board)[8]);
        bool captureIsValid(int x, int y, string (*board)[8]);
        void move(int x, int y, string (*board)[8], Piece**);
        void update(string (*board)[8], Piece** pieces);
};
#endif