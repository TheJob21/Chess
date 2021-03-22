#include "Piece.h"

Piece::Piece() {
    posx = 8;
    posy = 8;
    color = 'E';
    pieceType = 'E';
    value = 0;
}

Piece::~Piece() {
    posx = 0;
    posy = 0;
    color = 0;
    pieceType = 0;
    value = 0;
}

Piece::Piece(int x, int y, char col) {
    posx = x;
    posy = y;
    color = col;
    pieceType = 'E';
    value = 0;
}

void Piece::print() {
    cout << "Piece: " << color << pieceType << endl;
    if (posx != 8) {
        cout << "Tile: " << numToLetter(posy) << numToChar(posx) << endl;
    } else {
        cout << "Piece is captured.\n";
    }
    cout << "Attacking: \n";
    for (int i = 0; i < attacking.size(); i++) {
        cout << "\tPiece: " << attacking[i]->color << attacking[i]->pieceType << " on ";
        cout << numToLetter(attacking[i]->posy) << numToChar(attacking[i]->posx) << endl;
    }
    cout << "Attacked by: \n";
    for (int i = 0; i < attackers.size(); i++) {
        cout << "\tPiece: " << attackers[i]->color << attackers[i]->pieceType << " on ";
        cout << numToLetter(attackers[i]->posy) << numToChar(attackers[i]->posx) << endl;
    }
    cout << "Defending: \n";
    for (int i = 0; i < defending.size(); i++) {
        cout << "\tPiece: " << defending[i]->color << defending[i]->pieceType << " on ";
        cout << numToLetter(defending[i]->posy) << numToChar(defending[i]->posx) << endl;
    }
    cout << "Defended by: \n";
    for (int i = 0; i < defenders.size(); i++) {
        cout << "\tPiece: " << defenders[i]->color << defenders[i]->pieceType << " on ";
        cout << numToLetter(defenders[i]->posy) << numToChar(defenders[i]->posx) << endl;
    }
}

bool Piece::addCoveredTile(int x, int y, string(*board)[8], Piece** pieces) {
    Piece* temp;
    Int2 tile;
    tile.a[0] = x;
    tile.a[1] = y;
    coveredTiles.push_back(tile);
    if (board[x][y] != "") {        
        // cout << x << ", " << y << " " << board[x][y][0] << endl;
        temp = findPiece(x, y, board, pieces, board[x][y][0]);
        if (temp->color == color) {
            temp->defenders.push_back(this);
            defending.push_back(temp);
        } else {
            if (temp->pieceType == 'K') {
                temp->inCheck = true;
            }
            moveableTiles.push_back(tile);
            temp->attackers.push_back(this);
            attacking.push_back(temp); 
        }
        return true;
    } else if (pieceType == 'P') {
        return false;
    }
    moveableTiles.push_back(tile);
    return false;
}