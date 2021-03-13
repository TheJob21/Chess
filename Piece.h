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
        int posx, posy, value;
        bool inCheck = false;
        vector<Piece*> attackers, defenders, attacking, defending;
        vector<Int2> coveredTiles;
        char pieceType, color;
        Piece();
        ~Piece();
        Piece(int, int, char);
        virtual bool moveIsValid(int x, int y, string (*board)[8]) = 0;
        virtual bool captureIsValid(int x, int y, string (*board)[8]) = 0;
        virtual void move(int x, int y, string (*board)[8], Piece**) = 0;
        virtual void update(string (*board)[8], Piece** pieces) = 0;
        bool addCoveredTile(int x, int y, Piece* temp, Int2 tile, string(*board)[8], Piece** pieces);
        void print();
    };

#endif