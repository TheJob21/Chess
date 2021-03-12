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

void Knight::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WB";
    } else { // Move Black
        board[x][y] = "BB";
    }
}

void Knight::update(string (*board)[8], Piece** pieces) {
    
}

