#include "Bishop.h"

Bishop::Bishop(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'B';
    value = 3;
}

bool Bishop::moveIsValid(int x, int y, string (*board)[8]) {
    return true;
}

bool Bishop::captureIsValid(int x, int y, string (*board)[8]) {
    return true;
}

void Bishop::move(int x, int y, string (*board)[8], Piece** pieces) {
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

void Bishop::update(string (*board)[8], Piece** pieces) {
    Piece* temp;
    int x = posx-1, y = posy-1;
    Int2 tile;
    while (x >= 0 && y >= 0) { // a1 direction
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
            break;
        }
        x--;
        y--;
    }
    x = posx+1, y = posy-1;
    while (x <= 7 && y >= 0) { // a8 direction
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
            break;
        }
        x++;
        y--;
    }
    x = posx-1, y = posy+1;
    while (x >= 0 && y <= 7) { // h1 direction
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
            break;
        }
        x--;
        y++;
    }
    x = posx+1, y = posy+1;
    while (x <= 7 && y <= 7) { // h8 direction
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
            break;
        }
        x++;
        y++;
    }
}

