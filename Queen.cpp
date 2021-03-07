#include "Queen.h"
#include "utility.h"

Queen::Queen(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'Q';
    value = 9;
}

bool Queen::moveIsValid(int x, int y, string (*board)[8]) {
    return true;
}

bool Queen::captureIsValid(int x, int y, string (*board)[8]) {
    return true;
}

void Queen::move(int x, int y, string (*board)[8], Piece**) {
    return;
}

void Queen::update(string (*board)[8], Piece** pieces) {
    vector<Piece> atck;
    Piece* temp;
    int x = posx-1, y = posy;
    while (x >= 0) { // 1 direction
        if (board[x][y] != "") {
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else {
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
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
            break;
        }
        y--;
    }
    x = posx, y = posy+1;
    while (y <= 7) {
        if (board[x][y] != "") { // h direction
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) {
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else {
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
            break;
        }
        y++;
    }
    x = posx-1, y = posy-1;
    while (x >= 0 && y >= 0) { // a1 direction
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
        y--;
    }
    x = posx+1, y = posy-1;
    while (x <= 7 && y >= 0) { // a8 direction
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
        y--;
    }
    x = posx-1, y = posy+1;
    while (x >= 0 && y <= 7) { // h1 direction
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
        y++;
    }
    x = posx+1, y = posy+1;
    while (x <= 7 && y <= 7) { // h8 direction
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
        y++;
    }
}

