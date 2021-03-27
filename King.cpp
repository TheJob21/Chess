#include "King.h"

King::King(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'K';
    value = 4;
    timesMoved = 0;
}

King::King(int x, int y, char col, int moved) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'K';
    value = 100;
    timesMoved = moved;
}

bool King::moveIsValid(int x, int y, string (*board)[8]) {
    for (int i = 0; i < coveredTiles.size(); i++) {
        if (coveredTiles[i].a[0] == x && coveredTiles[i].a[1] == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    }
    return false;
}

bool King::captureIsValid(int x, int y, string (*board)[8]) {
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

bool King::captureIsValid2(int x, int y, string lastMove, string (*board)[8], Piece** pieces, bool &enPassant) {
    return false;
}

void King::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WK";
    } else { // Move Black
        board[x][y] = "BK";
    }
    timesMoved++;
}

void King::update(string lastMove, string (*board)[8], Piece** pieces) {
    // cout << "King Update";
    int x = posx-1, y = posy;
    if (x >= 0) {
        addCoveredTile(x, y, board, pieces);
        y = posy-1;
        if (y >= 0) {
            addCoveredTile(x, y, board, pieces);
        }
        y = posy+1;
        if (y <= 7) {
            addCoveredTile(x, y, board, pieces);
        }
    }
    x = posx, y = posy+1;
    if (y <= 7) {
        addCoveredTile(x, y, board, pieces);
    }
    y = posy-1;
    if (y >= 0) {
        addCoveredTile(x, y, board, pieces);
    }
    x = posx+1, y = posy;
    if (x <= 7) {
        addCoveredTile(x, y, board, pieces);
        y = posy-1;
        if (y >= 0) {
            addCoveredTile(x, y, board, pieces);
        }
        y = posy+1;
        if (y <= 7) {
            addCoveredTile(x, y, board, pieces);
        }
    }
}