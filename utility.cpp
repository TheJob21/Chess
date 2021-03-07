#include "utility.h"

Piece* findPiece(int x, int y, string (*board)[8], Piece** pieces, char col) {
    if (col == 'W') {
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
        } else { // Queen
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
        }
    } else { // Black
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
            } else { // Queen
                if (pieces[12]->posx == x && pieces[13]->posy == y) {
                    return pieces[12];
                }
                else {
                    for (int i = 16; i < 24; i++) {
                        if (pieces[i]->posx == x && pieces[i]->posy == y) {
                            return pieces[i];
                        }
                    }
                } 
            }
        }
    }
    cout << "Error(Pawn.cpp 153): No piece found on that tile.\n";
    return pieces[0]; // Never meant to run
}