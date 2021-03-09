#include "Pawn.h"

Pawn::Pawn(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'P';
    value = 1;
}

bool Pawn::moveIsValid(int x, int y, string (*board)[8]) {
    return true;
}

bool Pawn::captureIsValid(int x, int y, string (*board)[8]) {
    return true;
}

void Pawn::move(int x, int y, string (*board)[8], Piece**) {
    return;
}

void Pawn::update(string (*board)[8], Piece** pieces) {
    
}

