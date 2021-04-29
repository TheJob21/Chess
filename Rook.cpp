#include "Rook.h"
#include <vector>
using namespace std;

bool Rook::moveIsValid(int x, int y, string (*board)[8]) {
    if (x == posx) {
        if (y == posy) {
            return false;
        } else if (y < posy) {
            for (int i = posy-1; i >= y; i--) {
                if (board[x][i] != "") {
                    return false;
                }
            }
            return true;
        } else {
            for (int i = posy+1; i <= y; i++) {
                if (board[x][i] != "") {
                    return false;
                }
            }
            return true;
        }
    } else if (y == posy) {
        if (x < posx) {
            for (int i = posx-1; i >= x; i--) {
                if (board[i][y] != "") {
                    return false;
                }
            }
            return true;
        } else {
            for (int i = posx+1; i <= x; i++) {
                if (board[i][y] != "") {
                    return false;
                }
            }
            return true;
        }
    } else {
        return false;
    }
}

bool Rook::captureIsValid(int x, int y, string (*board)[8]) {
    if (x == posx) {
        if (y == posy) {
            return false;
        } else if (y < posy) {
            for (int i = posy-1; i > y; i--) {
                if (board[x][i] != "") {
                    return false;
                }
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 56): No capturable piece found\n";
                return false;
            }
            return true;
        } else {
            for (int i = posy+1; i < y; i++) {
                if (board[x][i] != "") {
                    return false;
                }
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 67): No capturable piece found\n";
                return false;
            }
            return true;
        }
    } else if (y == posy) {
        if (x < posx) {
            for (int i = posx-1; i > x; i--) {
                if (board[i][y] != "") {
                    return false;
                }
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 79): No capturable piece found\n";
                return false;
            }
            return true;
        } else {
            for (int i = posx+1; i < x; i++) {
                if (board[i][y] != "") {
                    return false;
                }
            }
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 90): No capturable piece found\n";
                return false;
            }
            return true;
        }
    } else {
        return false;
    }
}

bool Rook::captureIsValid2(int x, int y, string lastMove, string (*board)[8], Piece** pieces, bool &enPassant) {
    return false;
}

Rook::Rook(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'R';
    value = 5;
    timesMoved = 0;
}

Rook::Rook(int x, int y, char col, int moved) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'R';
    value = 5;
    timesMoved = moved;
}

void Rook::move(int x, int y, string (*board)[8], Piece **pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WR";
    } else { // Move Black
        board[x][y] = "BR";
    }
    timesMoved++;
}

void Rook::rookStack(string (*board)[8], Piece** pieces, int x, int y, int i) {
    Piece* temp;
    if (board[x][y] != "") {        
        temp = findPiece(x, y, board, pieces, board[x][y][0]);
        if (temp->color == color) {
            temp->defenders.push_back(this);
            defending.push_back(temp);
            if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                if (i == 0) {
                    while (x >= 0) {
                        rookStack(board, pieces, x, y, i);
                        x--;
                    }
                } else if (i == 1) {
                    while (x <= 7) {
                        rookStack(board, pieces, x, y, i);
                        x++;
                    }
                } else if (i == 2) {
                    while (y >= 0) {
                        rookStack(board, pieces, x, y, i);
                        y--;
                    }
                } else {
                    while (y <= 7) {
                        rookStack(board, pieces, x, y, i);
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

void Rook::update(string lastMove, string (*board)[8], Piece** pieces) {
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
                    while (x >= 0) {
                        rookStack(board, pieces, x, y, 0);
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
                    while (x <= 7) {
                        rookStack(board, pieces, x, y, 1);
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
                    while (y >= 0) {
                        rookStack(board, pieces, x, y, 2);
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
    while (y <= 7) { // h direction
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") {        
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
                if (temp->pieceType == 'R' || temp->pieceType == 'Q') {
                    while (y <= 7) {
                        rookStack(board, pieces, x, y, 3);
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
}