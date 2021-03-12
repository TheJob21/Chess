#include "King.h"

King::King(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'K';
    value = 100;
}

bool King::moveIsValid(int x, int y, string (*board)[8]) {
    return true;
}

bool King::captureIsValid(int x, int y, string (*board)[8]) {
    return true;
}

void King::move(int x, int y, string (*board)[8], Piece** pieces) {
    board[posx][posy] = "";
    posx = x;
    posy = y;
    capture(x, y, color, board, pieces);
    if (color == 'W') { // Move White
        board[x][y] = "WK";
    } else { // Move Black
        board[x][y] = "BK";
    }
}

void King::update(string (*board)[8], Piece** pieces) {
    Piece* temp;
    Int2 tile;
    int x = posx-1, y = posy;
    if (!(x < 0)) {
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") { // back a rank
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) { // friendly piece found
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else { // enemy piece found
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
        }
        y = posy-1;
        if (!(y < 0)) {
            tile.a[0] = x;
            tile.a[1] = y;
            coveredTiles.push_back(tile);
            if (board[x][y] != "") { // back a rank and file
                temp = findPiece(x, y, board, pieces, board[x][y][0]);
                if (temp->color == color) { // friendly piece found
                    temp->defenders.push_back(this);
                    defending.push_back(temp);
                } else { // enemy piece found
                    temp->attackers.push_back(this);
                    attacking.push_back(temp); 
                }
            }
        }
        y = posy+1;
        if (!(y > 7)) {
            tile.a[0] = x;
            tile.a[1] = y;
            coveredTiles.push_back(tile);
            if (board[x][y] != "") { // back a rank, forward a file
                temp = findPiece(x, y, board, pieces, board[x][y][0]);
                if (temp->color == color) { // friendly piece found
                    temp->defenders.push_back(this);
                    defending.push_back(temp);
                } else { // enemy piece found
                    temp->attackers.push_back(this);
                    attacking.push_back(temp); 
                }
            }
        }
    }
    x = posx, y = posy+1;
    if (!(y > 7)) {
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") { // forward a file
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) { // friendly piece found
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else { // enemy piece found
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
        }
    }
    y = posy-1;
    if (!(y < 0)) {
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") { // back a file
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) { // friendly piece found
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else { // enemy piece found
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
        }
    }
    x = posx+1, y = posy;
    if (!(x > 7)) {
        tile.a[0] = x;
        tile.a[1] = y;
        coveredTiles.push_back(tile);
        if (board[x][y] != "") { // forward a rank
            temp = findPiece(x, y, board, pieces, board[x][y][0]);
            if (temp->color == color) { // friendly piece found
                temp->defenders.push_back(this);
                defending.push_back(temp);
            } else { // enemy piece found
                temp->attackers.push_back(this);
                attacking.push_back(temp); 
            }
        }
        y = posy-1;
        if (!(y < 0)) {
            tile.a[0] = x;
            tile.a[1] = y;
            coveredTiles.push_back(tile);
            if (board[x][y] != "") { // forward a rank, back a file
                temp = findPiece(x, y, board, pieces, board[x][y][0]);
                if (temp->color == color) { // friendly piece found
                    temp->defenders.push_back(this);
                    defending.push_back(temp);
                } else { // enemy piece found
                    temp->attackers.push_back(this);
                    attacking.push_back(temp); 
                }
            }
        }
        y = posy+1;
        if (!(y > 7)) {
            tile.a[0] = x;
            tile.a[1] = y;
            coveredTiles.push_back(tile);
            if (board[x][y] != "") { // forward a rank and a file
                temp = findPiece(x, y, board, pieces, board[x][y][0]);
                if (temp->color == color) { // friendly piece found
                    temp->defenders.push_back(this);
                    defending.push_back(temp);
                } else { // enemy piece found
                    temp->attackers.push_back(this);
                    attacking.push_back(temp); 
                }
            }
        }
    }
}

