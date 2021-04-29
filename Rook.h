#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook:public Piece {
    public:
        Rook();
        Rook(int, int, char);
        Rook(int, int, char, int);
        bool moveIsValid(int, int, string (*)[8]);
        bool captureIsValid(int, int, string (*)[8]);
        bool captureIsValid2(int, int, string, string (*)[8], Piece**, bool &);
        void move(int, int, string (*)[8], Piece**);
        bool rookStack(string (*)[8], Piece**, int, int, int);
        void update(string, string (*)[8], Piece** );
};
#endif