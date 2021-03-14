#include "Bishop.h"

Bishop::Bishop(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'B';
    value = 3;
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

