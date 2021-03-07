#include <iostream>
#include <string>
using namespace std;


#include "Piece.cpp"
#include "Rook.cpp"
#include "Knight.cpp"
#include "Bishop.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Pawn.cpp"
#include "utility.cpp"

void setBoard(string (*)[8], Piece**);
char blackOrWhite(char);
char computerOrHuman(char);
bool validateRookMoveW(string, string (*)[8], Piece**);
bool validateRookMoveB(string, string (*)[8], Piece**);
string validateKnightMove(string);
string validateBishopMove(string);
string validateQueenMove(string);
string validateKingMove(string);
string validatePawnMove(string);
int letterToNum(char);
int charToNum(char);
void updateAtkDef(string (*)[8], Piece**);

int main()
{
    bool gameOver = false, isValid;
    char col, coh;
    string move;
    string moves[100][2];
    int moveCount = 1;
    string (*board)[8] = new string[8][8];
    Piece **pieces = new Piece*[32];
    setBoard(board, pieces);
    
    coh = computerOrHuman(coh);
    col = blackOrWhite(col);

    // Game Loop
    if (coh == 'c') {
        if (col == 'w') {
            while (!gameOver) {

            }
        } else {
            while (!gameOver) {

            }
        }
    } else { // human vs human
        while (!gameOver) {
            cout << endl;
            for (int i = 0; i < moveCount-1; i++) {
                cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
            }
            cout << moveCount << ". ";
            cin >> move;
            isValid = false;
            while (!isValid) {
                if (move.size() < 2 || move.size() > 7) {
                    cout << "Please enter a correct move ";
                    cin >> move;        
                } else if (move[0] == 'R') { // Rook move
                    if (!validateRookMoveW(move, board, pieces)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                } else if (move[0] == 'N') { // Knight move

                } else if (move[0] == 'B') { // Bishop move

                } else if (move[0] == 'Q') { // Queen move

                } else if (move[0] == 'K') { // King move

                } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') { // Pawn move

                } else if (move[0] == '0') { // Castling

                } else {
                    cout << "Please select a valid piece ";
                    cin >> move;        
                }
            }
            moves[moveCount-1][0] = move;
            cout << moveCount << ". " << move << ", ";
            cin >> move;
            bool isValid = false;
            while (!isValid) {
                if (move.size() < 2 || move.size() > 7) {
                    cout << "Please enter a correct move ";
                    cin >> move;        
                } else if (move[0] == 'R') {
                    if (!validateRookMoveB(move, board, pieces)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                } else if (move[0] == 'N') {

                } else if (move[0] == 'B') {

                } else if (move[0] == 'Q') {

                } else if (move[0] == 'K') {

                } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') {

                } else {
                    cout << "Please select a valid piece ";
                    cin >> move;        
                }
            }
            moves[moveCount-1][1] = move;
            moveCount++;
        }
    }
    

    

    return 0;
}

char blackOrWhite(char col){
    cout << "Play as white or black? (w or b) ";
    while (col != 'w' && col != 'b') {
        cin >> col;
        if (col == 'w' || col == 'b') {
            return col;
        } else {
            cout << "please type 'w' or 'b' "; 
        }
    }
    return 'w';
}

char computerOrHuman(char coh){
    cout << "Play a computer or human? (c or h) ";
    while (coh != 'c' && coh != 'h') {
        cin >> coh;
        if (coh == 'c' || coh == 'h') {
            return coh;
        } else {
            cout << "please type 'c' or 'h' "; 
        }
    }
    return 'h';
}

bool validateRookMoveW(string move, string (*board)[8], Piece** pieces) {
    int x, y;
    if (move.size() == 3) { // Normal move
        y = letterToNum(move[1]);
        x = charToNum(move[2]);
        if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
            cout << "Please make a valid move with your rook ";
            return false;
        } else {
            if (pieces[0]->posx != 8) { // Check if piece is captured
                if (pieces[0]->moveIsValid(x, y, board)) { // Check if move is valid
                    if (pieces[1]->posx != 8) { // Check if piece is captured
                        if (!pieces[1]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                            pieces[0]->move(x,y, board, pieces);
                            return true;
                        } else {
                            cout << "Error (169): Both rooks can move to the same position\n";
                            cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                            return false;
                        }
                    }
                    pieces[0]->move(x,y, board, pieces);
                    return true;
                }
            } if (pieces[1]->posx != 8) { // Check if piece is captured
                if (pieces[1]->moveIsValid(x, y, board)) { // Check if move is valid
                    pieces[1]->move(x,y, board, pieces);
                    return true;
                } else {
                    cout << "Move was invalid.\n";
                    return false;
                }
            } else {
                cout << "You do not have any uncaptured rooks.\n";
                return false;
            }
        }
    } else if (move.size() == 4) {
        if (move[3] == '+' || move[3] == '#') { // Move is Check or Mate
            // Fill in
        } else if (move[1] == 'x') { // Move is a capture
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Please make a valid move with your rook ";
                return false;
            } else {
                if (pieces[0]->posx != 8) { // Check if piece is captured
                    if (pieces[0]->captureIsValid(x, y, board)) { // Check if move is valid
                        if (pieces[1]->posx != 8) { // Check if piece is captured
                            if (!pieces[1]->captureIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                pieces[0]->move(x,y, board, pieces);
                                return true;
                            } else {
                                cout << "Error (207): Both rooks can move to the same position\n";
                                cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                                return false;
                            }
                        }
                        pieces[0]->move(x,y, board, pieces);
                        return true;
                    }
                } if (pieces[1]->posx != 8) { // Check if piece is captured
                    if (pieces[1]->captureIsValid(x, y, board)) { // Check if move is valid
                        pieces[1]->move(x,y, board, pieces);
                        return true;
                    } else {
                        cout << "Move was invalid.\n";
                        return false;
                    }
                } else {
                    cout << "You do not have any uncaptured rooks.\n";
                    return false;
                }
            }
        } else if (letterToNum(move[1]) != 8) { // Specify rook by file
            // Fill in
        } else if (charToNum(move[1]) != 8) { // Specify rook by rank
            // Fill in        
        } else {
            cout << "Make a valid move.\n";
            return false;
        }
    } else if (move.size() == 5) {
        // Fill in
    } else if (move.size() == 6) {
        // Fill in
    } else {
        cout << "Please make a valid move with your rook ";
        return false;
    }
    return false;
}

bool validateRookMoveB(string move, string (*board)[8], Piece** pieces) {
    int x, y;
    if (move.size() == 3) {
        y = letterToNum(move[1]);
        x = charToNum(move[2]);
        if (x == 8 || y < 0 || y > 7) {
            cout << "Error (253): Please make a valid move with your rook ";
            return false;
        } else {
            if (pieces[2]->posx != 8) { // Check if piece is captured
                if (pieces[2]->moveIsValid(x, y, board)) {
                    if (pieces[4]->posx != 8) { // Check if piece is captured
                        if (!pieces[3]->moveIsValid(x, y, board)){
                            pieces[2]->move(x,y, board, pieces);
                            return true;
                        } else {
                            cout << "Error (263): Both rooks can move to the same position\n";
                            cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                            return false;
                        }
                    }
                    pieces[2]->move(x,y, board, pieces);
                    return true;
                }
            } if (pieces[3]->posx != 8) { // Check if piece is captured
                if (pieces[3]->moveIsValid(x, y, board)) {
                    pieces[3]->move(x,y, board, pieces);
                    return true;
                } else {
                    cout << "Move was invalid.\n";
                    return false;
                }
            } else {
                cout << "You do not have any uncaptured rooks.\n";
                return false;
            }
        }
    } else if (move.size() == 4) {
        if (move[3] == '+' || move[3] == '#') { // Move is Check or Mate
            // Fill in
        } else if (move[1] == 'x') { // Move is a capture
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (291): Please make a valid move with your rook ";
                return false;
            } else {
                if (pieces[2]->posx != 8) { // Check if piece is captured
                    if (pieces[2]->captureIsValid(x, y, board)) { // Check if move is valid
                        if (pieces[3]->posx != 8) { // Check if piece is captured
                            if (!pieces[3]->captureIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                pieces[2]->move(x,y, board, pieces);
                                return true;
                            } else {
                                cout << "Error (301): Both rooks can move to the same position\n";
                                cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                                return false;
                            }
                        }
                        pieces[2]->move(x,y, board, pieces);
                        return true;
                    }
                } if (pieces[3]->posx != 8) { // Check if piece is captured
                    if (pieces[3]->captureIsValid(x, y, board)) { // Check if move is valid
                        pieces[3]->move(x,y, board, pieces);
                        return true;
                    } else {
                        cout << "Move was invalid.\n";
                        return false;
                    }
                } else {
                    cout << "You do not have any uncaptured rooks.\n";
                    return false;
                }
            }
        } else if (letterToNum(move[1]) != 8) { // Specify rook by file
            // Fill in
        } else if (charToNum(move[1]) != 8) { // Specify rook by rank
            // Fill in
        } else {
            cout << "Make a valid move.\n";
            return false;
        }
    } else if (move.size() == 5) {
        // Fill in
    } else if (move.size() == 6) {
        // Fill in
    } else {
        cout << "Error (335): Please make a valid move with your rook ";
        return false;
    }
    return false;
}

string validateKnightMove(string) {
    return "";
}

string validateBishopMove(string) {
    return "";
}

string validateQueenMove(string) {
    return "";
}

string validateKingMove(string) {
    return "";
}

string validatePawnMove(string) {
    return "";
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

void setBoard(string (*board)[8], Piece** pieces) {
    board[0][0] = "WR";
    board[0][1] = "WN";
    board[0][2] = "WB";
    board[0][3] = "WQ";
    board[0][4] = "WK";
    board[0][5] = "WB";
    board[0][6] = "WN";
    board[0][7] = "WR";
    // board[1][0] = "WP";
    board[1][1] = "WP";
    board[1][2] = "WP";
    board[1][3] = "WP";
    board[1][4] = "WP";
    board[1][5] = "WP";
    board[1][6] = "WP";
    // board[1][7] = "WP";
    board[7][0] = "BR";
    board[7][1] = "BN";
    board[7][2] = "BB";
    board[7][3] = "BQ";
    board[7][4] = "BK";
    board[7][5] = "BB";
    board[7][6] = "BN";
    board[7][7] = "BR";
    // board[6][0] = "BP";
    board[6][1] = "BP";
    board[6][2] = "BP";
    board[6][3] = "BP";
    board[6][4] = "BP";
    board[6][5] = "BP";
    board[6][6] = "BP";
    // board[6][7] = "BP";
    pieces[0] = new Rook(0,0,'W'), pieces[1] = new Rook(0,7,'W'), pieces[2] = new Rook(7,0,'B'), pieces[3] = new Rook(7,7,'B');
    pieces[4] = new Knight(0,1,'W'), pieces[5] = new Knight(0,6,'W'), pieces[6] = new Knight(7,1,'B'), pieces[7] = new Knight(7,6,'B');
    pieces[8] = new Bishop(0,2,'W'), pieces[9] = new Bishop(0,5,'W'), pieces[10] = new Bishop(7,2,'B'), pieces[11] = new Bishop(7,5,'B');
    pieces[12] = new Queen(0,3,'W'), pieces[13] = new Queen(7,3,'B');
    pieces[14] = new King(0,4,'W'), pieces[15] = new King(7,4,'B');
    for (int i=0; i<8; i++) {
        pieces[i+16] = new Pawn(1,i,'W');
        pieces[i+24] = new Pawn(6,i,'B');
    }
}

void updateAtkDef(string (*board)[8], Piece** pieces) {
    for (int i = 0; i < 32; i++) {
        pieces[i]->update(board, pieces);
    }
}