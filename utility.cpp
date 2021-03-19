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
        cout << "Error (utility.cpp 132): Tile was somehow empty\n";
        return pieces[0]; // Never meant to run
    }
    cout << "Error (utility.cpp 129): Piece was neither black nor white.\n";
    return pieces[0]; // Never meant to run
}

void capture(int x, int y, char color, string (*board)[8], Piece** pieces) {
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
                } else if (pieces[3]->posx == x && pieces[3]->posy == y) {
                    pieces[3]->posx = 8;
                    pieces[3]->posy = 8;
                } else {
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
                } else if (pieces[7]->posx == x && pieces[7]->posy == y) {
                    pieces[7]->posx = 8;
                    pieces[7]->posy = 8;
                } else {
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
                } else {
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
                if (pieces[12]->posx == x && pieces[12]->posy == y) {
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
    }
}

void update(string lastMove, string (*board)[8], Piece** pieces) {
    for (int i = 0; i < 32; i++) {
        pieces[i]->attackers.clear();
        pieces[i]->attacking.clear();
        pieces[i]->defenders.clear();
        pieces[i]->defending.clear();
        pieces[i]->coveredTiles.clear();
    }
    pieces[14]->inCheck = false;
    pieces[15]->inCheck = false;
    for (int i = 0; i < 32; i++) {
        if (pieces[i]->posx != 8) { 
            pieces[i]->update(lastMove, board, pieces);
        }
    }
}

void promote(char color, char pieceType, int index, string (*board)[8], Piece** pieces) {
    if (color == 'W') {
        if (pieceType == 'Q') {
            pieces[index] = new Queen(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "WQ";
        } else if (pieceType == 'N') {
            pieces[index] = new Knight(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "WN";
        } else if (pieceType == 'R') {
            pieces[index] = new Rook(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "WR";
        } else if (pieceType == 'B') {
            pieces[index] = new Bishop(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "WB";
        } else if (pieceType == 'P') {
            pieces[index] = new Pawn(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "WP";
        }
    } else {
        if (pieceType == 'Q') {
            pieces[index] = new Queen(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "BQ";
        } else if (pieceType == 'N') {
            pieces[index] = new Knight(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "BN";
        } else if (pieceType == 'R') {
            pieces[index] = new Rook(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "BR";
        } else if (pieceType == 'B') {
            pieces[index] = new Bishop(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "BB";
        } else if (pieceType == 'P') {
            pieces[index] = new Pawn(pieces[index]->posx, pieces[index]->posy, color, pieces[index]->timesMoved);
            board[pieces[index]->posx][pieces[index]->posy] = "BP";
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