#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn:public Piece {
    public: 
        Pawn(int, int, char );
        Pawn(int, int, char, int);
        bool moveIsValid(int, int, string (*)[8]);
        bool captureIsValid(int, int, string (*)[8]);
        bool captureIsValid2(int, int, string, string (*)[8], Piece**, bool &);
        void move(int, int, string (*)[8], Piece**);
        void update(string, string (*)[8], Piece**);
};
#endif