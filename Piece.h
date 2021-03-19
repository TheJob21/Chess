#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Int2 {
  int a[2];
};

class Piece {
    public:
        int posx, posy, value, timesMoved;
        bool inCheck = false;
        vector<Piece*> attackers, defenders, attacking, defending;
        vector<Int2> coveredTiles, moveableTiles;
        char pieceType, color;
        Piece();
        ~Piece();
        Piece(int, int, char);
        virtual bool moveIsValid(int, int, string (*)[8]) = 0;
        virtual bool captureIsValid(int, int, string (*)[8]) = 0;
        virtual bool captureIsValid2(int, int, string, string (*)[8], Piece**, bool &) = 0;
        virtual void move(int, int, string (*)[8], Piece**) = 0;
        virtual void update(string, string (*)[8], Piece**) = 0;
        bool addCoveredTile(int, int, string(*)[8], Piece**);
        void print();
    };

#endif