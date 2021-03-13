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
    Piece* temp;
    Int2 tile;
    int x = posx-1, y = posy-2;
    if (x >= 0 && y >= 0) { // a-a1 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    x = posx+1;
    if (x <= 7 && y >= 0) { // a-a8 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    x = posx+2, y = posy-1;
    if (x <= 7 && y >= 0) { // a8-8 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    y = posy+1;
    if (x <= 7 && y <= 7) { // 8-h8 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    x = posx+1, y = posy+2;
    if (x <= 7 && y <= 7) { // h-h8 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    x = posx-1;
    if (x >= 0 && y <= 7) { // h-h1 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    x = posx-2, y = posy+1;
    if (x >= 0 && y <= 7) { // h1-1 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
    y = posy-1;
    if (x >= 0 && y <= 7) { // 1-a1 direction
        addCoveredTile(x, y, temp, tile, board, pieces);
    }
}

