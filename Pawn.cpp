#include "Pawn.h"

Pawn::Pawn(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'P';
    value = 1;
    timesMoved = 0;
}

Pawn::Pawn(int x, int y, char col, int moved) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'P';
    value = 1;
    timesMoved = moved;
}

bool Pawn::moveIsValid(int x, int y, string (*board)[8]) {
    if (timesMoved == 0) {
        if (color == 'W') {
            if (posx+2 == x && posy == y) {
                if (board[x-1][y] == "") {
                    if (board[x][y] == "") {
                        return true;
                    }
                }
            } else if (posx+1 == x && posy == y) {
                if (board[x][y] == "") {
                    return true;
                }
            }
        } else {
            if (posx-2 == x && posy == y) {
                if (board[x+1][y] == "") {
                    if (board[x][y] == "") {
                        return true;
                    }
                }
            } else if (posx-1 == x && posy == y) {
                if (board[x][y] == "") {
                    return true;
                }
            }
        }
    } else if (color == 'W') {
        if (posx+1 == x && posy == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    } else {
        if (posx-1 == x && posy == y) {
            if (board[x][y] == "") {
                return true;
            }
        }
    }
    return false;
}

bool Pawn::captureIsValid(int x, int y, string (*board)[8]) {
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

bool Pawn::captureIsValid2(int x, int y, string lastMove, string (*board)[8], Piece** pieces, bool &enPassant) {
    Piece* temp;
    for (int i = 0; i < coveredTiles.size(); i++) {
        if (coveredTiles[i].a[0] == x && coveredTiles[i].a[1] == y) {
            if (board[x][y] != "") {
                if (color != board[x][y][0]) {
                    return true;
                }
            } else if (color == 'W' && posx == 4) {
                if (board[posx][y] != "" && board[posx][y][0] != color && board[posx][y][1] == 'P') {
                    temp = findPiece(posx, y, board, pieces, 'B');
                    if (lastMove.size() == 2 && letterToNum(lastMove[0]) == y && charToNum(lastMove[1]) == posx && temp->timesMoved == 1) {
                        enPassant = true;
                        return true;
                    }
                }
            } else if (color == 'B' && posx == 3) {
                if (board[posx][y] != "" && board[posx][y][0] != color && board[posx][y][1] == 'P') {
                    temp = findPiece(posx, y, board, pieces, 'W');
                    if (lastMove.size() == 2 && letterToNum(lastMove[0]) == y && charToNum(lastMove[1]) == posx && temp->timesMoved == 1) {
                        enPassant = true;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void Pawn::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WP";
    } else { // Move Black
        board[x][y] = "BP";
    }
    timesMoved++;
}

void Pawn::update(string lastMove, string (*board)[8], Piece** pieces) {
    Piece* temp;
    Int2 tile;
    if (color == 'W') {
        int x = posx+1, y = posy-1;
        tile.a[0] = x;
        tile.a[1] = y;
        if (x <= 7 && y >= 0) { // a-a1 direction
            addCoveredTile(x, y, board, pieces);
            if (board[x][y] != "" && board[x][y][0] == 'B') {
                moveableTiles.push_back(tile);
            } else if (posx == 4) {
                if (board[posx][y] != "" && board[posx][y][0] != color && board[posx][y][1] == 'P') {
                    temp = findPiece(posx, y, board, pieces, 'B');
                    if (lastMove.size() == 2 && letterToNum(lastMove[0]) == y && charToNum(lastMove[1]) == posx && temp->timesMoved == 1) {
                        moveableTiles.push_back(tile);
                    }
                }
            }
        }
        y = posy+1;
        tile.a[1] = y;
        if (x <= 7 && y <= 7) { // a-a8 direction
            addCoveredTile(x, y, board, pieces);
            if (board[x][y] != "" && board[x][y][0] == 'B') {
                moveableTiles.push_back(tile);
            } else if (posx == 4) {
                if (board[posx][y] != "" && board[posx][y][0] != color && board[posx][y][1] == 'P') {
                    temp = findPiece(posx, y, board, pieces, 'B');
                    if (lastMove.size() == 2 && letterToNum(lastMove[0]) == y && charToNum(lastMove[1]) == posx && temp->timesMoved == 1) {
                        moveableTiles.push_back(tile);
                    }
                }
            }
        }
        if (timesMoved == 0) {
            x = posx+2;
            y = posy;
            tile.a[0] = x;
            tile.a[1] = y;
            if (board[x][y] == "") {
                moveableTiles.push_back(tile);
            }
            x--;
            tile.a[0] = x;
            tile.a[1] = y;
            if (board[x][y] == "") {
                moveableTiles.push_back(tile);
            }
        } else {
            x = posx+1;
            tile.a[0] = x;
            tile.a[1] = y;
            if (board[x][y] == "") {
                moveableTiles.push_back(tile);
            }
        }
    } else {
        int x = posx-1, y = posy-1;
        tile.a[0] = x;
        tile.a[1] = y;
        if (x >= 0 && y >= 0) { // a-a1 direction
            addCoveredTile(x, y, board, pieces);
            if (board[x][y] != "" && board[x][y][0] == 'W') {
                moveableTiles.push_back(tile);
            } else if (posx == 3) {
                if (board[posx][y] != "" && board[posx][y][0] != color && board[posx][y][1] == 'P') {
                    temp = findPiece(posx, y, board, pieces, 'W');
                    if (lastMove.size() == 2 && letterToNum(lastMove[0]) == y && charToNum(lastMove[1]) == posx && temp->timesMoved == 1) {
                        moveableTiles.push_back(tile);
                    }
                }
            }
        }
        y = posy+1;
        tile.a[1] = y;
        if (x >= 0 && y <= 7) { // a-a8 direction
            addCoveredTile(x, y, board, pieces);
            if (board[x][y] != "" && board[x][y][0] == 'W') {
                moveableTiles.push_back(tile);
            } else if (posx == 3) {
                if (board[posx][y] != "" && board[posx][y][0] != color && board[posx][y][1] == 'P') {
                    temp = findPiece(posx, y, board, pieces, 'W');
                    if (lastMove.size() == 2 && letterToNum(lastMove[0]) == y && charToNum(lastMove[1]) == posx && temp->timesMoved == 1) {
                        moveableTiles.push_back(tile);
                    }
                }
            }
        }
        if (timesMoved == 0) {
            x = posx-2;
            y = posy;
            tile.a[0] = x;
            tile.a[1] = y;
            if (board[x][y] == "") {
                moveableTiles.push_back(tile);
            }
            x++;
            tile.a[0] = x;
            tile.a[1] = y;
            if (board[x][y] == "") {
                moveableTiles.push_back(tile);
            }
        } else {
            x = posx-1;
            tile.a[0] = x;
            tile.a[1] = y;
            if (board[x][y] == "") {
                moveableTiles.push_back(tile);
            }
        }
    }
}