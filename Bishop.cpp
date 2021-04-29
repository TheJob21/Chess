#include "Bishop.h"

Bishop::Bishop(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'B';
    value = 3;
    timesMoved = 0;
}

Bishop::Bishop(int x, int y, char col, int moved) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'B';
    value = 3;
    timesMoved = moved;
}

bool Bishop::moveIsValid(int x, int y, string (*board)[8]) {
    if (x > posx) {
        int j = posx+1;
        if (y < posy) {
            if (x-posx != fabs(y-posy)) {
                return false;
            }
            for (int i = posy-1; i >= y; i--) {
                if (board[j][i] != "") {
                    return false;
                }
                j++;
            }
            return true;
        } else {
            if (x-posx != y-posy) {
                return false;
            }
            for (int i = posy+1; i <= y; i++) {
                if (board[j][i] != "") {
                    return false;
                }
                j++;
            }
            return true;
        }
    } else if (x < posx) {
        int j = posx-1;
        if (y < posy) {
            if (x-posx != y-posy) {
                return false;
            }
            for (int i = posy-1; i >= y; i--) {
                if (board[j][i] != "") {
                    return false;
                }
                j--;
            }
            return true;
        } else {
            if (fabs(x-posx) != y-posy) {
                return false;
            }
            for (int i = posy+1; i <= y; i++) {
                if (board[j][i] != "") {
                    return false;
                }
                j--;
            }
            return true;
        }
    } else {
        return false;
    }
}

bool Bishop::captureIsValid(int x, int y, string (*board)[8]) {
    if (x > posx) {
        int j = posx+1;
        if (y < posy) {
            if (x-posx != fabs(y-posy)) {
                return false;
            }
            for (int i = posy-1; i > y; i--) {
                //cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[j][i] != "") {
                    return false;
                }
                j++;
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Bishop.cpp 86): No capturable piece found\n";
                return false;
            }
            return true;
        } else {
            if (x-posx != y-posy) {
                return false;
            }
            for (int i = posy+1; i < y; i++) {
                //cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[j][i] != "") {
                    return false;
                }
                j++;
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Bishop.cpp 102): No capturable piece found\n";
                return false;
            }
            return true;
        }
    } else if (x < posx) {
        int j = posx-1;
        if (y < posy) {
            if (x-posx != y-posy) {
                return false;
            }
            for (int i = posy-1; i > y; i--) {
                //cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[j][i] != "") {
                    return false;
                }
                j--;
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Bishop.cpp 121): No capturable piece found\n";
                return false;
            }
            return true;
        } else {
            if (fabs(x-posx) != y-posy) {
                return false;
            }
            for (int i = posy+1; i < y; i++) {
                //cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[j][i] != "") {
                    return false;
                }
                j--;
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Bishop.cpp 137): No capturable piece found\n";
                return false;
            }
            return true;
        }
    } else {
        return false;
    }
}

bool Bishop::captureIsValid2(int x, int y, string lastMove, string (*board)[8], Piece** pieces, bool &enPassant) {
    return false;
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
    timesMoved++;
}

void Bishop::bishopStack(string (*board)[8], Piece** pieces, int x, int y, int i) {
    Piece* temp;
    if (board[x][y] != "") {        
        temp = findPiece(x, y, board, pieces, board[x][y][0]);
        if (temp->color == color) {
            temp->defenders.push_back(this);
            defending.push_back(temp);
            if (temp->pieceType == 'B' || temp->pieceType == 'Q') {
                if (i == 0) {
                    while (x >= 0 && y >= 0) { // a1 direction
                        bishopStack(board, pieces, x, y, i);
                        x--;
                        y--;
                    }
                } else if (i == 1) {
                    while (x <= 7 && y >= 0) { // a1 direction
                        bishopStack(board, pieces, x, y, i);
                        x++;
                        y--;
                    }
                } else if (i == 2) {
                    while (x >= 0 && y <= 7) { // a1 direction
                        bishopStack(board, pieces, x, y, i);
                        x--;
                        y++;
                    }
                } else {
                    while (x <= 7 && y <= 7) { // a1 direction
                        bishopStack(board, pieces, x, y, i);
                        x++;
                        y++;
                    }
                }
            }
        } else {
            temp->attackers.push_back(this);
            attacking.push_back(temp); 
        }
    }
}

void Bishop::update(string lastMove, string (*board)[8], Piece** pieces) {
    Piece* temp;
    Int2 tile;
    int x = posx-1, y = posy-1;
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
                    while (x >= 0 && y >= 0) {
                        bishopStack(board, pieces, x, y, 0);
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
                    while (x <= 7 && y >= 0) {
                        bishopStack(board, pieces, x, y, 1);
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
                    while (x >= 0 && y <= 7) {
                        bishopStack(board, pieces, x, y, 2);
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
                    while (x <= 7 && y <= 7) {
                        bishopStack(board, pieces, x, y, 3);
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