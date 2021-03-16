#include "Pawn.h"

Pawn::Pawn(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'P';
    value = 1;
    timesMoved = 0;
}

Pawn::Pawn(int x, int y, char col, int moved) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'P';
    value = 1;
    timesMoved = moved;
}

bool Pawn::moveIsValid(int x, int y, string (*board)[8]) {
    if (timesMoved == 0) {
        if (color == 'W') {
            if (posx+2 == x && posy == y) {
                if (board[x][y] == "") {
                    return true;
                }
            } else if (posx+1 == x && posy == y) {
                if (board[x][y] == "") {
                    return true;
                }
            }
        } else {
            if (posx-2 == x && posy == y) {
                if (board[x][y] == "") {
                    return true;
                }
            } else if (posx-1 == x && posy == y) {
                if (board[x][y] == "") {
                    return true;
                }
            }
        }
    } else if (color == 'W') {
        if (posx+1 == x && posy == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    } else {
        if (posx-1 == x && posy == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    }
    return false;
}

bool Pawn::captureIsValid(int x, int y, string (*board)[8]) {
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
    timesMoved++;
}

void Pawn::update(string (*board)[8], Piece** pieces) {
    if (color == 'W') {
        int x = posx+1, y = posy-1;
        if (x <= 7 && y >= 0) { // a-a1 direction
            addCoveredTile(x, y, board, pieces);
        }
        y = posy+1;
        if (x <= 7 && y <= 7) { // a-a8 direction
            addCoveredTile(x, y, board, pieces);
        }
    } else {
        int x = posx-1, y = posy-1;
        if (x >= 0 && y >= 0) { // a-a1 direction
            addCoveredTile(x, y, board, pieces);
        }
        y = posy+1;
        if (x >= 0 && y <= 7) { // a-a8 direction
            addCoveredTile(x, y, board, pieces);
        }
    }
}