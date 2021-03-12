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

void Pawn::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WP";
    } else { // Move Black
        board[x][y] = "BP";
    }
}

void Pawn::update(string (*board)[8], Piece** pieces) {
    
}

