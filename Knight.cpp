#include "Knight.h"

Knight::Knight(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'N';
    value = 3;
    timesMoved = 0;
}

bool Knight::moveIsValid(int x, int y, string (*board)[8]) {
    for (int i = 0; i < coveredTiles.size(); i++) {
        if (coveredTiles[i].a[0] == x && coveredTiles[i].a[1] == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    }
    return false;
}

bool Knight::captureIsValid(int x, int y, string (*board)[8]) {
    for (int i = 0; i < coveredTiles.size(); i++) {
        if (coveredTiles[i].a[0] == x && coveredTiles[i].a[1] == y) {
            if (board[x][y] != "") {
                if (color != board[x][y][0]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Knight::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WN";
    } else { // Move Black
        board[x][y] = "BN";
    }
    timesMoved++;
}

void Knight::update(string (*board)[8], Piece** pieces) {
    int x = posx-1, y = posy-2;
    if (x >= 0 && y >= 0) { // a-a1 direction
        addCoveredTile(x, y, board, pieces);
    }
    x = posx+1;
    if (x <= 7 && y >= 0) { // a-a8 direction
        addCoveredTile(x, y, board, pieces);
    }
    x = posx+2, y = posy-1;
    if (x <= 7 && y >= 0) { // a8-8 direction
        addCoveredTile(x, y, board, pieces);
    }
    y = posy+1;
    if (x <= 7 && y <= 7) { // 8-h8 direction
        addCoveredTile(x, y, board, pieces);
    }
    x = posx+1, y = posy+2;
    if (x <= 7 && y <= 7) { // h-h8 direction
        addCoveredTile(x, y, board, pieces);
    }
    x = posx-1;
    if (x >= 0 && y <= 7) { // h-h1 direction
        addCoveredTile(x, y, board, pieces);
    }
    x = posx-2, y = posy+1;
    if (x >= 0 && y <= 7) { // h1-1 direction
        addCoveredTile(x, y, board, pieces);
    }
    y = posy-1;
    if (x >= 0 && y <= 7) { // 1-a1 direction
        addCoveredTile(x, y, board, pieces);
    }
}

