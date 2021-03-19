#ifndef KING_H
#define KING_H
#include "Piece.h"

class King:public Piece {
    public:
        King(int, int, char);
        King(int, int, char, int);
        bool moveIsValid(int, int, string (*)[8]);
        bool captureIsValid(int, int, string (*)[8]);
        bool captureIsValid2(int, int, string, string (*)[8], Piece**, bool &);
        void move(int, int, string (*)[8], Piece**);
        void update(string, string (*)[8], Piece**);
};
#endif