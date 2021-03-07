#include "Rook.h"
#include "utility.h"

bool Rook::moveIsValid(int x, int y, string (*board)[8]) {
    if (x == posx) {
        if (y == posy) {
            return false;
        } else if (y < posy) {
            for (int i = posy-1; i >= y; i--) {
                cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[x][i] != "") {
                    return false;
                }
            }
            return true;
        } else {
            for (int i = posy+1; i <= y; i++) {
                cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[x][i] != "") {
                    return false;
                }
            }
            return true;
        }
    } else if (y == posy) {
        if (x < posx) {
            for (int i = posx-1; i >= x; i--) {
                cout << "tile[" << i << "][" << y << "]=" << board[i][y] << endl;
                if (board[i][y] != "") {
                    return false;
                }
            }
            return true;
        } else {
            for (int i = posx+1; i <= x; i++) {
                cout << "tile[" << i << "][" << y << "]=" << board[i][y] << endl;
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
                cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[x][i] != "") {
                    return false;
                }
            }
            cout << "tile[" << x << "][" << y << "]=" << board[x][y] << endl;
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 62): No capturable piece found\n";
                return false;
            }
            return true;
        } else {
            for (int i = posy+1; i < y; i++) {
                cout << "tile[" << x << "][" << i << "]=" << board[x][i] << endl;
                if (board[x][i] != "") {
                    return false;
                }
            }
            cout << "tile[" << x << "][" << y << "]=" << board[x][y] << endl;
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 75): No capturable piece found\n";
                return false;
            }
            return true;
        }
    } else if (y == posy) {
        if (x < posx) {
            for (int i = posx-1; i > x; i--) {
                cout << "tile[" << i << "][" << y << "]=" << board[i][y] << endl;
                if (board[i][y] != "") {
                    return false;
                }
            }
            cout << "tile[" << x << "][" << y << "]=" << board[x][y] << endl;
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 90): No capturable piece found\n";
                return false;
            }
            return true;
        } else {
            for (int i = posx+1; i < x; i++) {
                cout << "tile[" << i << "][" << y << "]=" << board[i][y] << endl;
                if (board[i][y] != "") {
                    return false;
                }
            }
            cout << "tile[" << x << "][" << y << "]=" << board[x][y] << endl;
            if (board[x][y] == "" || board[x][y][0] == color) {
                cout << "Error(Rook.cpp 103): No capturable piece found\n";
                return false;
            }
            return true;
        }
    } else {
        return false;
    }
}

Rook::Rook(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'R';
    value = 5;
}

void Rook::move(int x, int y, string (*board)[8], Piece **pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    if (color == 'W') { // Move White
        if (board[x][y] != "") { // Capture
            if (board[x][y][1] == 'P') { // Capture Pawn
                for (int i = 0; i < 8; i++) {
                    if (pieces[i+24]->posx == x && pieces[i+24]->posy == y) {
                        pieces[i+24]->posx = 8;
                        pieces[i+24]->posy = 8;
                        break;
                    }
                }
            } else if (board[x][y][1] == 'R') { // Capture Rook
                if (pieces[2]->posx == x && pieces[2]->posy == y) {
                    pieces[2]->posx = 8;
                    pieces[2]->posy = 8;
                }
                else if (pieces[3]->posx == x && pieces[3]->posy == y) {
                    pieces[3]->posx = 8;
                    pieces[3]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+24]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+24]->posx = 8;
                            pieces[i+24]->posy = 8;
                            break;
                        }
                    }
                } 
            } else if (board[x][y][1] == 'N') { // Capture Knight
                if (pieces[6]->posx == x && pieces[6]->posy == y) {
                    pieces[6]->posx = 8;
                    pieces[6]->posy = 8;
                }
                else if (pieces[7]->posx == x && pieces[7]->posy == y) {
                    pieces[7]->posx = 8;
                    pieces[7]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+24]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+24]->posx = 8;
                            pieces[i+24]->posy = 8;
                            break;
                        }
                    }
                } 
            } else if (board[x][y][1] == 'B') { // Capture Bishop
                if (pieces[10]->posx == x && pieces[10]->posy == y) {
                    pieces[10]->posx = 8;
                    pieces[10]->posy = 8;
                }
                else if (pieces[11]->posx == x && pieces[11]->posy == y) {
                    pieces[11]->posx = 8;
                    pieces[11]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+24]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+24]->posx = 8;
                            pieces[i+24]->posy = 8;
                            break;
                        }
                    }
                } 
            } else { // Capture Queen
                if (pieces[13]->posx == x && pieces[13]->posy == y) {
                    pieces[13]->posx = 8;
                    pieces[13]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+24]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+24]->posx = 8;
                            pieces[i+24]->posy = 8;
                            break;
                        }
                    }
                } 
            }
        }
        board[x][y] = "WR";
    } else { // Move Black
        if (board[x][y] != "") { // Capture
            if (board[x][y][1] == 'P') { // Capture Pawn
                for (int i = 0; i < 8; i++) {
                    if (pieces[i+16]->posx == x && pieces[i+24]->posy == y) {
                        pieces[i+16]->posx = 8;
                        pieces[i+16]->posy = 8;
                        break;
                    }
                }
            } else if (board[x][y][1] == 'R') { // Capture Rook
                if (pieces[0]->posx == x && pieces[0]->posy == y) {
                    pieces[0]->posx = 8;
                    pieces[0]->posy = 8;
                }
                else if (pieces[1]->posx == x && pieces[1]->posy == y) {
                    pieces[1]->posx = 8;
                    pieces[1]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+16]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+16]->posx = 8;
                            pieces[i+16]->posy = 8;
                            break;
                        }
                    }
                } 
            } else if (board[x][y][1] == 'N') { // Capture Knight
                if (pieces[4]->posx == x && pieces[4]->posy == y) {
                    pieces[4]->posx = 8;
                    pieces[4]->posy = 8;
                }
                else if (pieces[5]->posx == x && pieces[5]->posy == y) {
                    pieces[5]->posx = 8;
                    pieces[5]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+16]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+16]->posx = 8;
                            pieces[i+16]->posy = 8;
                            break;
                        }
                    }
                } 
            } else if (board[x][y][1] == 'B') { // Capture Bishop
                if (pieces[8]->posx == x && pieces[8]->posy == y) {
                    pieces[8]->posx = 8;
                    pieces[8]->posy = 8;
                }
                else if (pieces[9]->posx == x && pieces[9]->posy == y) {
                    pieces[9]->posx = 8;
                    pieces[9]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+16]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+16]->posx = 8;
                            pieces[i+16]->posy = 8;
                            break;
                        }
                    }
                } 
            } else { // Capture Queen
                if (pieces[12]->posx == x && pieces[13]->posy == y) {
                    pieces[12]->posx = 8;
                    pieces[12]->posy = 8;
                }
                else {
                    for (int i = 0; i < 8; i++) {
                        if (pieces[i+16]->posx == x && pieces[i+24]->posy == y) {
                            pieces[i+16]->posx = 8;
                            pieces[i+16]->posy = 8;
                            break;
                        }
                    }
                } 
            }
        }
        board[x][y] = "BR";
    }
}

void Rook::update(string (*board)[8], Piece** pieces) {
    Piece* temp;
    int x = posx-1, y = posy;
    while (x >= 0) { // 1 direction
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
    }
    x = posx+1, y = posy;
    while (x <= 7) { // 8 direction
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
    }
    x = posx, y = posy-1;
    while (y >= 0) { // a direction
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
        y--;
    }
    x = posx, y = posy+1;
    while (y <= 7) { // h direction
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
        y++;
    }
}