#include "utility.h"

Piece* findPiece(int x, int y, string (*board)[8], Piece** pieces, char col) {
    if (col == 'B') { // Black
        if (board[x][y][1] == 'P') { // Pawn
            for (int i = 24; i < 32; i++) {
                if (pieces[i]->posx == x && pieces[i]->posy == y) {
                    return pieces[i];
                }
            }
        } else if (board[x][y][1] == 'R') { // Rook
            if (pieces[2]->posx == x && pieces[2]->posy == y) {
                return pieces[2];
            }
            else if (pieces[3]->posx == x && pieces[3]->posy == y) {
                return pieces[3];
            }
            else {
                for (int i = 24; i < 32; i++) {
                    if (pieces[i]->posx == x && pieces[i]->posy == y) {
                        return pieces[i];
                    }
                }
            } 
        } else if (board[x][y][1] == 'N') { // Knight
            if (pieces[6]->posx == x && pieces[6]->posy == y) {
                return pieces[6];
            }
            else if (pieces[7]->posx == x && pieces[7]->posy == y) {
                return pieces[7];
            }
            else {
                for (int i = 24; i < 32; i++) {
                    if (pieces[i]->posx == x && pieces[i]->posy == y) {
                        return pieces[i];
                    }
                }
            } 
        } else if (board[x][y][1] == 'B') { // Bishop
            if (pieces[10]->posx == x && pieces[10]->posy == y) {
                return pieces[10];
            }
            else if (pieces[11]->posx == x && pieces[11]->posy == y) {
                return pieces[11];
            }
            else {
                for (int i = 24; i < 32; i++) {
                    if (pieces[i]->posx == x && pieces[i]->posy == y) {
                        return pieces[i];
                    }
                }
            } 
        } else if (board[x][y][1] == 'Q') { // Queen
            if (pieces[13]->posx == x && pieces[13]->posy == y) {
                return pieces[13];
            }
            else {
                for (int i = 24; i < 32; i++) {
                    if (pieces[i]->posx == x && pieces[i]->posy == y) {
                        return pieces[i];
                    }
                }
            } 
        } else { // King
            return pieces[15];
        }
    } else { // White
        if (board[x][y] != "") {
            if (board[x][y][1] == 'P') { // Pawn
                for (int i = 16; i < 24; i++) {
                    if (pieces[i]->posx == x && pieces[i]->posy == y) {
                        return pieces[i];
                    }
                }
            } else if (board[x][y][1] == 'R') { // Rook
                if (pieces[0]->posx == x && pieces[0]->posy == y) {
                    return pieces[0];
                }
                else if (pieces[1]->posx == x && pieces[1]->posy == y) {
                    return pieces[1];
                }
                else {
                    for (int i = 16; i < 24; i++) {
                        if (pieces[i]->posx == x && pieces[i]->posy == y) {
                            return pieces[i];
                        }
                    }
                } 
            } else if (board[x][y][1] == 'N') { // Knight
                if (pieces[4]->posx == x && pieces[4]->posy == y) {
                    return pieces[4];
                }
                else if (pieces[5]->posx == x && pieces[5]->posy == y) {
                    return pieces[5];
                }
                else {
                    for (int i = 16; i < 24; i++) {
                        if (pieces[i]->posx == x && pieces[i]->posy == y) {
                            return pieces[i];
                        }
                    }
                } 
            } else if (board[x][y][1] == 'B') { // Bishop
                if (pieces[8]->posx == x && pieces[8]->posy == y) {
                    return pieces[8];
                }
                else if (pieces[9]->posx == x && pieces[9]->posy == y) {
                    return pieces[9];
                }
                else {
                    for (int i = 16; i < 24; i++) {
                        if (pieces[i]->posx == x && pieces[i]->posy == y) {
                            return pieces[i];
                        }
                    }
                } 
            } else if (board[x][y][1] == 'Q') { // Queen
                if (pieces[12]->posx == x && pieces[12]->posy == y) {
                    return pieces[12];
                }
                else {
                    for (int i = 16; i < 24; i++) {
                        if (pieces[i]->posx == x && pieces[i]->posy == y) {
                            return pieces[i];
                        }
                    }
                } 
            } else { // King
                return pieces[14];
            }
        }
    }
    cout << "Error(utility.cpp 129): No piece found on that tile.\n";
    return pieces[0]; // Never meant to run
}

void update(string (*board)[8], Piece** pieces) {
    for (int i = 0; i < 32; i++) {
        pieces[i]->attackers.clear();
        pieces[i]->attacking.clear();
        pieces[i]->defenders.clear();
        pieces[i]->defending.clear();
    }
    pieces[14]->inCheck = false;
    pieces[15]->inCheck = false;
    for (int i = 0; i < 32; i++) {
        if (pieces[i]->posx != 8) { 
            pieces[i]->update(board, pieces);
        }
    }
}

int letterToNum(char c) {
    if (c == 'a') return 0;
    if (c == 'b') return 1;
    if (c == 'c') return 2;
    if (c == 'd') return 3;
    if (c == 'e') return 4;
    if (c == 'f') return 5;
    if (c == 'g') return 6;
    if (c == 'h') return 7;
    return 8;
}

char numToLetter(int i) {
    if (i == 0) return 'a';
    if (i == 1) return 'b';
    if (i == 2) return 'c';
    if (i == 3) return 'd';
    if (i == 4) return 'e';
    if (i == 5) return 'f';
    if (i == 6) return 'g';
    if (i == 7) return 'h';
    return 'i';
}

int charToNum(char c) {
    if (c == '1') return 0;
    if (c == '2') return 1;
    if (c == '3') return 2;
    if (c == '4') return 3;
    if (c == '5') return 4;
    if (c == '6') return 5;
    if (c == '7') return 6;
    if (c == '8') return 7;
    return 8;
}

char numToChar(int i) {
    return '0' + (i+1);
}