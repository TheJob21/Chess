#include "Queen.h"

Queen::Queen(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'Q';
    value = 9;
}

bool Queen::moveIsValid(int x, int y, string (*board)[8]) {
    for (int i = 0; i < coveredTiles.size(); i++) {
        if (coveredTiles[i].a[0] == x && coveredTiles[i].a[1] == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    }
    return false;
}

bool Queen::captureIsValid(int x, int y, string (*board)[8]) {
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

void Queen::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WQ";
    } else { // Move Black
        board[x][y] = "BQ";
    }
}

void Queen::update(string (*board)[8], Piece** pieces) {
    vector<Piece> atck;
    Piece* temp;
    Int2 tile;
    int x = posx-1, y = posy;
    while (x >= 0) { // 1 direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        x--;
    }
    x = posx+1;
    while (x <= 7) { // 8 direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        x++;
    }
    x = posx, y = posy-1;
    while (y >= 0) { // a direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        y--;
    }
    y = posy+1;
    while (y <= 7) {
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        y++;
    }
    x = posx-1, y = posy-1;
    while (x >= 0 && y >= 0) { // a1 direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        x--;
        y--;
    }
    x = posx+1, y = posy-1;
    while (x <= 7 && y >= 0) { // a8 direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        x++;
        y--;
    }
    x = posx-1, y = posy+1;
    while (x >= 0 && y <= 7) { // h1 direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        x--;
        y++;
    }
    x = posx+1, y = posy+1;
    while (x <= 7 && y <= 7) { // h8 direction
        if (addCoveredTile(x, y, temp, tile, board, pieces)) {
            break;
        }
        x++;
        y++;
    }
}

