#include "Piece.h"

Piece::Piece() {
    posx = 8;
    posy = 8;
    color = 'E';
    pieceType = 'E';
    value = 0;
}

Piece::~Piece() {
    posx = 0;
    posy = 0;
    color = 0;
    pieceType = 0;
    value = 0;
}

Piece::Piece(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'E';
    value = 0;
}