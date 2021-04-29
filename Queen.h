#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen:public Piece {
    public:
        Queen(int, int, char);
        Queen(int, int, char, int);
        bool moveIsValid(int, int, string (*)[8]);
        bool captureIsValid(int, int, string (*)[8]);
        bool captureIsValid2(int, int, string, string (*)[8], Piece**, bool &);
        void move(int, int, string (*)[8], Piece**);
        bool bishopStack(string (*)[8], Piece**, int, int, int);
        bool rookStack(string (*)[8], Piece**, int, int, int);
        void update(string, string (*)[8], Piece**);
};
#endif