#include "Queen.h"

Queen::Queen(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'Q';
    value = 9;
    timesMoved = 0;
}

Queen::Queen(int x, int y, char col, int moved) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'Q';
    value = 9;
    timesMoved = moved;
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

bool Queen::captureIsValid2(int x, int y, string lastMove, string (*board)[8], Piece** pieces, bool &enPassant) {
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
    timesMoved++;
}

bool Queen::bishopStack(string (*board)[8], Piece** pieces, int x, int y, int i) {
    Piece* temp;
    if (board[x][y] != "") {        
        temp = findPiece(x, y, board, pieces, board[x][y][0]);
        if (temp->color == color) {
            temp->defenders.push_back(this);
            defending.push_back(temp);
            if (temp->pieceType == 'B' || temp->pieceType == 'Q') {
                if (i == 0) {
                    x--;
                    y--;
                    while (x >= 0 && y >= 0) { // a1 direction
                        if (bishopStack(board, pieces, x, y, i)) {
                            break;
                        }
                        x--;
                        y--;
                    }
                } else if (i == 1) {
                    x++;
                    y--;
                    while (x <= 7 && y >= 0) { // a1 direction
                        if (bishopStack(board, pieces, x, y, i)) {
                            break;
                        }
                        x++;
                        y--;
                    }
                } else if (i == 2) {
                    x--;
                    y++;
                    while (x >= 0 && y <= 7) { // a1 direction
                        if (bishopStack(board, pieces, x, y, i)) {
                            break;
                        }
                        x--;
                        y++;
                    }
                } else {
                    x++;
                    y++;
                    while (x <= 7 && y <= 7) { // a1 direction
                        if (bishopStack(board, pieces, x, y, i)) {
                            break;
                        }
                        x++;
                        y++;
                    }
                }
            }
            return true;
        } else {
            temp->attackers.push_back(this);
            attacking.push_back(temp);
            return true;
        }
    }
    return false;
}

bool Queen::rookStack(string (*board)[8], Piece** pieces, int x, int y, int i) {
    Piece* temp;
    if (board[x][y] != "") {        
        temp = findPiece(x, y, board, pieces, board[x][y][0]);
        if (temp->color == color) {
            temp->defenders.push_back(this);
            defending.push_back(temp);
            if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                if (i == 0) {
                    x--;
                    while (x >= 0) {
                        if (rookStack(board, pieces, x, y, i)) {
                            break;
                        }
                        x--;
                    }
                } else if (i == 1) {
                    x++;
                    while (x <= 7) {
                        if (rookStack(board, pieces, x, y, i)) {
                            break;
                        }
                        x++;
                    }
                } else if (i == 2) {
                    y--;
                    while (y >= 0) {
                        if (rookStack(board, pieces, x, y, i)) {
                            break;
                        }
                        y--;
                    }
                } else {
                    y++;
                    while (y <= 7) {
                        if (rookStack(board, pieces, x, y, i)) {
                            break;
                        }
                        y++;
                    }
                }
            }
            return true;
        } else {
            temp->attackers.push_back(this);
            attacking.push_back(temp); 
            return true;
        }
    }
    return false;
}

void Queen::update(string lastMove, string (*board)[8], Piece** pieces) {
    Piece* temp;
    Int2 tile;
    int x = posx-1, y = posy;
    tile.a[1] = y;
    while (x >= 0) { // 1 direction
        tile.a[0] = x;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {        
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
                if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                    x--;
                    while (x >= 0) {
                        if (rookStack(board, pieces, x, y, 0)) {
                            break;
                        }
                        x--;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
        }
        x--;
    }
    x = posx+1;
    while (x <= 7) { // 8 direction
        tile.a[0] = x;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {        
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
                if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                    x++;
                    while (x <= 7) {
                        if (rookStack(board, pieces, x, y, 1)) {
                            break;
                        }
                        x++;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
        }
        x++;
    }
    x = posx, y = posy-1;
    tile.a[0] = x;
    while (y >= 0) { // a direction
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {        
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
                if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                    y--;
                    while (y >= 0) {
                        if (rookStack(board, pieces, x, y, 2)) {
                            break;
                        }
                        y--;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
        }
        y--;
    }
    y = posy+1;
    while (y <= 7) {
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {        
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
                if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                    y++;
                    while (y <= 7) {
                        if (rookStack(board, pieces, x, y, 3)) {
                            break;
                        }
                        y++;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
        }
        y++;
    }
    x = posx-1, y = posy-1;
    while (x >= 0 && y >= 0) { // a1 direction
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {        
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
                if (temp->pieceType == 'B' || temp->pieceType == 'Q') {
                    x--; 
                    y--;
                    while (x >= 0 && y >= 0) {
                        if (bishopStack(board, pieces, x, y, 0)) {
                            break;
                        }
                        x--;
                        y--;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
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
                if (temp->pieceType == 'B' || temp->pieceType == 'Q') {
                    x++;
                    y--;
                    while (x <= 7 && y >= 0) {
                        if (bishopStack(board, pieces, x, y, 1)) {
                            break;
                        }
                        x++;
                        y--;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
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
                if (temp->pieceType == 'B' || temp->pieceType == 'Q') {
                    x--;
                    y++;
                    while (x >= 0 && y <= 7) {
                        if (bishopStack(board, pieces, x, y, 2)) {
                            break;
                        }
                        x--;
                        y++;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
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
                if (temp->pieceType == 'B' || temp->pieceType == 'Q') {
                    x++;
                    y++;
                    while (x <= 7 && y <= 7) {
                        if (bishopStack(board, pieces, x, y, 3)) {
                            break;
                        }
                        x++;
                        y++;
                    }
                }
                break;
            } else {
                if (temp->pieceType == 'K') {
                    temp->inCheck = true;
                }
                moveableTiles.push_back(tile);
                temp->attackers.push_back(this);
                attacking.push_back(temp);
                break;
            }
        } else {
            moveableTiles.push_back(tile);
        }
        x++;
        y++;
    }
}