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
        cout << "Black Pawn not found on square " << numToLetter(y) << numToChar(x) << endl;
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
    cout << "Error (utility.cpp 135): Piece was neither black nor white.\n";
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
                    if (pieces[i+16]->posx == x && pieces[i+16]->posy == y) {
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
                        if (pieces[i+16]->posx == x && pieces[i+16]->posy == y) {
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
                        if (pieces[i+16]->posx == x && pieces[i+16]->posy == y) {
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
                        if (pieces[i+16]->posx == x && pieces[i+16]->posy == y) {
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
                        if (pieces[i+16]->posx == x && pieces[i+16]->posy == y) {
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
        pieces[i]->moveableTiles.clear();
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

void copyBoard(string (*b1)[8], string (*b2)[8], Piece** p1, Piece** p2) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            b2[i][j] = b1[i][j];
        }
    }
    for (int i = 0; i < 32; i++) {
        *p2[i] = *p1[i];
    }
}

void setBoard(string (*board)[8], Piece** pieces) {
    board[0][0] = "WR";
    board[0][1] = "WN";
    board[0][2] = "WB";
    board[0][3] = "WQ";
    board[0][4] = "WK";
    board[0][5] = "WB";
    board[0][6] = "WN";
    board[0][7] = "WR";
    board[1][0] = "WP";
    board[1][1] = "WP";
    board[1][2] = "WP";
    board[1][3] = "WP";
    board[1][4] = "WP";
    board[1][5] = "WP";
    board[1][6] = "WP";
    board[1][7] = "WP";
    board[7][0] = "BR";
    board[7][1] = "BN";
    board[7][2] = "BB";
    board[7][3] = "BQ";
    board[7][4] = "BK";
    board[7][5] = "BB";
    board[7][6] = "BN";
    board[7][7] = "BR";
    board[6][0] = "BP";
    board[6][1] = "BP";
    board[6][2] = "BP";
    board[6][3] = "BP";
    board[6][4] = "BP";
    board[6][5] = "BP";
    board[6][6] = "BP";
    board[6][7] = "BP";
    pieces[0] = new Rook(0,0,'W'), pieces[1] = new Rook(0,7,'W'), pieces[2] = new Rook(7,0,'B'), pieces[3] = new Rook(7,7,'B');
    pieces[4] = new Knight(0,1,'W'), pieces[5] = new Knight(0,6,'W'), pieces[6] = new Knight(7,1,'B'), pieces[7] = new Knight(7,6,'B');
    pieces[8] = new Bishop(0,2,'W'), pieces[9] = new Bishop(0,5,'W'), pieces[10] = new Bishop(7,2,'B'), pieces[11] = new Bishop(7,5,'B');
    pieces[12] = new Queen(0,3,'W'), pieces[13] = new Queen(7,3,'B');
    pieces[14] = new King(0,4,'W'), pieces[15] = new King(7,4,'B');
    for (int i=0; i<8; i++) {
        pieces[i+16] = new Pawn(1,i,'W');
        pieces[i+24] = new Pawn(6,i,'B');
    }
    // pieces[0] = new Rook(0,0,'W'), pieces[1] = new Rook(0,7,'W'), pieces[2] = new Rook(7,0,'B'), pieces[3] = new Rook(7,7,'B');
    // pieces[4] = new Knight(0,1,'W'), pieces[5] = new Knight(0,6,'W'), pieces[6] = new Knight(7,1,'B'), pieces[7] = new Knight(8,8,'B');
    // pieces[8] = new Bishop(0,2,'W'), pieces[9] = new Bishop(0,5,'W'), pieces[10] = new Bishop(7,2,'B'), pieces[11] = new Bishop(7,5,'B');
    // pieces[12] = new Queen(0,3,'W'), pieces[13] = new Queen(7,3,'B');
    // pieces[14] = new King(0,4,'W'), pieces[15] = new King(7,4,'B');
    // for (int i=0; i<4; i++) {
    //    pieces[i+16] = new Pawn(8,8,'W');
    //     pieces[i+24] = new Pawn(8,8,'B');
    // }
    // pieces[20] = new Pawn(6,6,'W');
    // pieces[28] = new Pawn(8,8,'B');
    // for (int i=5; i<8; i++) {
    //     pieces[i+16] = new Pawn(8,8,'W');
    //     pieces[i+24] = new Pawn(8,8,'B');
    // }

}

void printBoard(string (*board)[8], ostream & output) {
    output << "  ________________________\n";
    for (int i = 7; i >= 0; i--) {
        output << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != "") {
                output << "|" << board[i][j] << "";
            } else {
                output << "|__";
            }
        }
        output << "|\n";
    }
    output << "   a  b  c  d  e  f  g  h\n";
}

void addMoves(string possMove, int i, Piece** piecesPoss, vector<int> &pieceIndex, vector<string> &possMoves) {
    possMove = piecesPoss[i]->pieceType;
    for (int j = piecesPoss[i]->moveableTiles.size()-1; j >= 0; j--) {
        string tempMove = possMove;
        tempMove += numToLetter(piecesPoss[i]->moveableTiles[j].a[1]);
        tempMove += numToChar(piecesPoss[i]->moveableTiles[j].a[0]);
        pieceIndex.push_back(i);
        possMoves.push_back(tempMove);
    }
}

void check3Reps(vector<vector<Int2>> everyPos, bool &gameOver, ostream &filestream) {
    for (int i = 0; i < everyPos.size(); i++) {
        int _3Limit = 1;
        for (int j = i+1; j < everyPos.size(); j++) {
            for (int k = 0; k < 32; k++) {
                if (everyPos[i][k].a[0] == everyPos[j][k].a[0] && everyPos[i][k].a[1] == everyPos[j][k].a[1]) {
                    continue;
                } else {
                    _3Limit--;
                    break;
                }
            }
            _3Limit++;
            if (_3Limit >= 3) {
                gameOver = true;
                filestream << "Threefold Repetition rule reached. Stalemate!\n";
                cout << "Threefold Repetition rule reached. Stalemate!\n";
                break;
            }
        }
        if (gameOver) {
            break;
        }
    }
}

void copyPos(vector<vector<Int2>> &everyPos, Piece** pieces) {
    vector<Int2> pos;
    for (int i = 0; i < 32; i++) {
        Int2 p;
        p.a[0] = pieces[i]->posx;
        p.a[1] = pieces[i]->posy;
        pos.push_back(p);
    }
    everyPos.push_back(pos);
}