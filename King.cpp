#include "King.h"
#include "utility.h"

King::King(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'K';
    value = 100;
}

bool King::moveIsValid(int x, int y, string (*board)[8]) {
    return true;
}

bool King::captureIsValid(int x, int y, string (*board)[8]) {
    return true;
}

void King::move(int x, int y, string (*board)[8], Piece**) {
    return;
}

void King::update(string (*board)[8], Piece** pieces) {
    // Piece* temp;
    // int x = posx-1, y = posy;
    // temp = findPiece(x, y, board, pieces, board[x][y][0]);
    // if (temp->color == color) {
    //     temp->defenders.push_back(this);
    //     defending.push_back(temp);
    // } else {
    //     temp->attackers.push_back(this);
    //     attacking.push_back(temp); 
    // }
}

