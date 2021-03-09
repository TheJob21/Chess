#include "Knight.h"

Knight::Knight(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'N';
    value = 3;
}

bool Knight::moveIsValid(int x, int y, string (*board)[8]) {
    return true;
}

bool Knight::captureIsValid(int x, int y, string (*board)[8]) {
    return true;
}

void Knight::move(int x, int y, string (*board)[8], Piece**) {
    return;
}

void Knight::update(string (*board)[8], Piece** pieces) {
    
}

