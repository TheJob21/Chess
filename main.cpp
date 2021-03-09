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
void copyBoard(string (*)[8], string (*)[8], Piece**, Piece**);
char blackOrWhite(char);
char computerOrHuman(char);
bool validateRookMove(string, string (*)[8], string (*)[8], Piece**, Piece**, char, bool);
string validateKnightMove(string);
string validateBishopMove(string);
string validateQueenMove(string);
string validateKingMove(string);
string validatePawnMove(string);
int letterToNum(char);
int charToNum(char);
void updateAtkDef(string (*)[8], Piece**);
bool check(string (*)[8], Piece**, char);
bool badCheck(string (*)[8], Piece**, char);
bool checkmate(string (*)[8], Piece**, char);
void printBoard(string (*)[8]);

int main()
{
    bool gameOver = false, isValid;
    char col, coh;
    string move;
    string moves[100][2];
    int moveCount = 1;
    string (*board)[8] = new string[8][8]; 
    string (*boardPoss)[8] = new string[8][8];
    Piece **pieces = new Piece*[32];
    Piece **piecesPoss = new Piece*[32];
    setBoard(board, pieces);
    setBoard(boardPoss, piecesPoss);
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
                    if (!validateRookMove(move, board, boardPoss, pieces, piecesPoss, 'W', gameOver)) {
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
            printBoard(board);
            moves[moveCount-1][0] = move;
            cout << moveCount << ". " << move << ", ";
            cin >> move;
            bool isValid = false;
            while (!isValid) {
                if (move.size() < 2 || move.size() > 7) {
                    cout << "Please enter a correct move ";
                    cin >> move;        
                } else if (move[0] == 'R') {
                    if (!validateRookMove(move, board, boardPoss, pieces, piecesPoss, 'B', gameOver)) {
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
            printBoard(board);
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

bool validateRookMove(string move, string (*board)[8], string (*boardPoss)[8], Piece** pieces, Piece** piecesPoss, char col, bool gameOver) {
    vector<Piece*> rook;
    int i, pawns;
    if (col == 'W') {
        if (piecesPoss[0]->posx != 8) { // Check 'a' file rook is uncaptured
            rook.push_back(piecesPoss[0]);
        }
        if (piecesPoss[1]->posx != 8) { // Check 'h' file rook is uncaptured
            rook.push_back(piecesPoss[1]);
        }
        i = 16;
    } else {
        if (piecesPoss[2]->posx != 8) { // Check 'a' file rook is uncaptured
            rook.push_back(piecesPoss[2]);
        }
        if (piecesPoss[3]->posx != 8) { // Check 'h' file rook is uncaptured
            rook.push_back(piecesPoss[3]);
        }
        i = 24;
    }
    pawns = i + 8;
    while (i < pawns) {
        if (piecesPoss[i]->pieceType == 'R') { // Check for pawns promoted to rooks
            if (piecesPoss[i]->posx != 8) { // Check if piece is captured
                rook.push_back(piecesPoss[i]);
            }
        }
        i++;
    }
    if (rook.size() <= 0) {
        cout << "You do not have any uncaptured rooks.\n";
        return false;
    }
    int x, y;
    if (move.size() == 3) { // Normal move
        y = letterToNum(move[1]);
        x = charToNum(move[2]);
        if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
            cout << "Please choose a square on the board.\n";
            return false;
        } else {
            for (int j = 0; j < rook.size(); j++) {
                if (rook[j]->moveIsValid(x, y, board)) { // Check if move is valid
                    for (int i = j+1; i < rook.size(); i++) {
                        if (rook[i]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                            cout << "Error (main.cpp 208): Multiple rooks can move to the same position\n";
                            cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                            return false;
                        }
                    }
                    rook[j]->move(x,y, boardPoss, piecesPoss);
                    update(boardPoss, piecesPoss);
                    if (badCheck(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 213): You cannot put yourself in check.\n";
                        return false;
                    }
                    if (check(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 218): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                        return false;
                    }
                    copyBoard(boardPoss, board, piecesPoss, pieces);
                    return true;
                }
            }
            cout << "Move was invalid.\n";
            return false;
        }
    } else if (move.size() == 4) {
        if (move[3] == '+' || move[3] == '#') { // Move is Check or Mate
            y = letterToNum(move[1]);
            x = charToNum(move[2]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < rook.size(); j++) {
                    if (rook[j]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                        for (int i = j+1; i < rook.size(); i++) {
                            if (rook[i]->moveIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                cout << "Error (main.cpp 195): Multiple rooks can move to the same position\n";
                                cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                                return false;
                            }
                        }
                        rook[j]->move(x,y, boardPoss, piecesPoss);
                        update(boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 247): You cannot put yourself in check.\n";
                            return false;
                        }
                        if (!check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 251): That move is not check, remove the '+'\n";
                            return false;
                        }
                        if (checkmate(boardPoss, piecesPoss, col)) {
                            if (move[3] == '#') {
                                gameOver = true;
                                return true;
                            } else {
                                cout << "Error (main.cpp 259): That move is checkmate, please use '#' at the end.\n";
                                return false;
                            }
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        return true;
                    }
                }
                cout << "You do not have any rook on the specified file.\n";
                return false;
            }
        } else if (move[1] == 'x') { // Move is a capture
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < rook.size(); j++) {
                    if (rook[j]->captureIsValid(x, y, boardPoss)) { // Check if move is valid
                        for (int i = j+1; i < rook.size(); i++) {
                            if (rook[i]->captureIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                cout << "Error (main.cpp 285): Multiple rooks can move to the same position\n";
                                cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                                return false;
                            }
                        }
                        rook[j]->move(x,y, boardPoss, piecesPoss);
                        update(boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 293): You cannot put yourself in check.\n";
                            return false;
                        }
                        if (check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 293): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                            return false;
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        return true;
                    }
                }
                cout << "Move was invalid.\n";
                return false;
            }
        } else if (letterToNum(move[1]) != 8) { // Specify rook by file
            int file = letterToNum(move[1]);
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < rook.size(); j++) {
                    if (rook[j]->posy == file) { // Check if specified file checks out
                        if (rook[j]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                            for (int i = j+1; i < rook.size(); i++) {
                                if (rook[i]->posy == file) { // Check if specified file checks out
                                    if (rook[i]->moveIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                        cout << "Error (main.cpp 321): Multiple rooks can move to the same position\n";
                                        cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                                        return false;
                                    }
                                }
                            }
                            rook[j]->move(x,y, boardPoss, piecesPoss);
                            update(boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 325): You cannot put yourself in check.\n";
                                return false;
                            }
                            if (check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 329): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                return false;
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            return true;
                        }
                    }
                }
                cout << "You do not have any rook on the specified file.\n";
                return false;
            }
        } else if (charToNum(move[1]) != 8) { // Specify rook by rank
            int rank = charToNum(move[1]);
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < rook.size(); j++) {
                    if (rook[j]->posx == rank) { // Check if specified file checks out
                        if (rook[j]->moveIsValid(x, y, board)) { // Check if move is valid
                            for (int i = j+1; i < rook.size(); i++) {
                                if (rook[i]->posx == rank) { // Check if specified file checks out
                                    if (rook[i]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                        cout << "Error (main.cpp 354): Multiple rooks can move to the same position\n";
                                        cout << "Please specify which rook you'd like to move (i.e. Rae4 or R3e4)\n";
                                        return false;
                                    }
                                }
                            }
                            rook[j]->move(x,y, boardPoss, piecesPoss);
                            update(boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 362): You cannot put yourself in check.\n";
                                return false;
                            }
                            if (check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 366): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                return false;
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            return true;
                        }
                    }
                }
                cout << "You do not have any rook on the specified file.\n";
                return false;
            }       
        } else {
            cout << "Make a valid move.\n";
            return false;
        }
    } else if (move.size() == 5) {
        // Capture and Check/mate
        // Specify and Check/mate
        // Specify and Capture
    } else if (move.size() == 6) {
        // Specify, Capture, and Check/mate
    } else {
        cout << "Please make a valid move with your rook ";
        return false;
    }
    return false;
}

bool badCheck(string (*board)[8], Piece** pieces, char col) {
    if (col == 'W') {
        if (pieces[14]->inCheck) { // You put yourself in check
            cout << "Error (main.cpp 337): That move puts yourself in check.\n";
            return true;
        }
        return false;
    } else {
        if (pieces[15]->inCheck) { // You put yourself in check
            cout << "Error (main.cpp 343): That move puts yourself in check.\n";
            return true;
        }
        return false;
    }
}

bool check(string (*board)[8], Piece** pieces, char col) {
    if (col == 'W') {
        if (pieces[15]->inCheck) { // Black is in check
            return true;
        }
        return false;
    } else {
        if (pieces[14]->inCheck) { // You put yourself in check
            cout << "Error (main.cpp 237): That move puts yourself in check.\n";
            return true;
        }
        return false;
    }
}

bool checkmate(string (*board)[8], Piece** pieces, char col) {
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

void copyBoard(string (*b1)[8], string (*b2)[8], Piece** p1, Piece** p2) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            b2[i][j] = b1[i][j];
        }
    }
    for (int i = 0; i < 32; i++) {
        p2[i] = p1[i];
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

void printBoard(string (*board)[8]) {
    cout << "  _________________________________________\n";
    for (int i = 7; i >= 0; i--) {
        cout << i+1 << " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != "") {
                cout << "|_" << board[i][j] << "_";
            } else {
                cout << "|____";
            }
        }
        cout << "|\n";
    }
    cout << "     a    b    c    d    e    f    g    h\n";
}