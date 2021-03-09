#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop:public Piece {
    public:
        Bishop(int x, int y, char col);
        bool moveIsValid(int x, int y, string (*board)[8]);
        bool captureIsValid(int x, int y, string (*board)[8]);
        void move(int x, int y, string (*board)[8], Piece**);
        void update(string (*board)[8], Piece** pieces);
};
#endif
