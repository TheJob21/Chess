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

void Rook::update(string lastMove, string (*board)[8], Piece** pieces) {
    cout << "Rook Update\n";
    int x = posx-1, y = posy;
    while (x >= 0) { // 1 direction
        if (addCoveredTile(x, y, board, pieces)) {
            break;
        }
        x--;
    }
    x = posx+1, y = posy;
    while (x <= 7) { // 8 direction
        if (addCoveredTile(x, y, board, pieces)) {
            break;
        }
        x++;
    }
    x = posx, y = posy-1;
    while (y >= 0) { // a direction
        if (addCoveredTile(x, y, board, pieces)) {
            break;
        }
        y--;
    }
    x = posx, y = posy+1;
    while (y <= 7) { // h direction
        if (addCoveredTile(x, y, board, pieces)) {
            break;
        }
        y++;
    }
}