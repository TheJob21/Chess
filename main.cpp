#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Piece.h"
#include "utility.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
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
string validateKingMove(string);
string validatePawnMove(string);
int letterToNum(char);
int charToNum(char);
void updateAtkDef(string (*)[8], Piece**);
bool check(string (*)[8], Piece**, char);
bool badCheck(string (*)[8], Piece**, char);
bool stalemate(string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkmate(string (*)[8], string (*)[8], Piece**, Piece**, char);
void printBoard(string (*)[8]);
bool checkForBlock(int, int, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkValidKingMove(int, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool validateMove(string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);

int main()
{
    bool gameOver = false, isValid;
    char col, coh;
    string move;
    string moves[100][2];
    int moveCount = 1;
    string (*board)[8] = new string[8][8]; 
    string (*boardPoss)[8] = new string[8][8]; 
    string (*boardPoss2)[8] = new string[8][8]; 
    Piece **pieces = new Piece*[32];
    Piece **piecesPoss = new Piece*[32];
    Piece **piecesPoss2 = new Piece*[32];
    setBoard(board, pieces);
    update(board, pieces);
    setBoard(boardPoss, piecesPoss);
    update(boardPoss, piecesPoss);
    setBoard(boardPoss2, piecesPoss2);
    update(boardPoss2, piecesPoss2);
    coh = computerOrHuman(coh);
    if (coh == 'c') {
        col = blackOrWhite(col);
    }

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
                } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') { // Pawn move

                } else if (move[0] == '0') { // Castling

                } else {
                    if (!validateMove(move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                }
            }
            printBoard(board);
            moves[moveCount-1][0] = move;
            if (gameOver) {
                break;
            }
            cout << moveCount << ". " << move << ", ";
            cin >> move;
            bool isValid = false;
            while (!isValid) {
                if (move.size() < 2 || move.size() > 7) {
                    cout << "Please enter a correct move ";
                    cin >> move;        
                } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') { // Pawn move

                } else if (move[0] == '0') { // Castling

                } else {
                    if (!validateMove(move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
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

bool validateMove(string move, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
    vector<Piece*> piece;
    int i, pawns;
    if (col == 'W') {
		if (move[0] == 'R') {
			if (piecesPoss[0]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[0]);
			}
			if (piecesPoss[1]->posx != 8) { // Check 'h' file piece is uncaptured
				piece.push_back(piecesPoss[1]);
			}
		} else if (move[0] == 'N') {
			if (piecesPoss[4]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[4]);
			}
			if (piecesPoss[5]->posx != 8) { // Check 'h' file piece is uncaptured
				piece.push_back(piecesPoss[5]);
			}
		} else if (move[0] == 'B') {
			if (piecesPoss[8]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[8]);
			}
			if (piecesPoss[9]->posx != 8) { // Check 'h' file piece is uncaptured
				piece.push_back(piecesPoss[9]);
			}
		} else if (move[0] == 'Q') {
			if (piecesPoss[12]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[12]);
			}
		} else if (move[0] == 'K') {
			if (piecesPoss[14]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[14]);
			}
		}
        i = 16;
    } else {
        if (move[0] == 'R') {
			if (piecesPoss[2]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[2]);
			}
			if (piecesPoss[3]->posx != 8) { // Check 'h' file piece is uncaptured
				piece.push_back(piecesPoss[3]);
			}
		} else if (move[0] == 'N') {
			if (piecesPoss[6]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[6]);
			}
			if (piecesPoss[7]->posx != 8) { // Check 'h' file piece is uncaptured
				piece.push_back(piecesPoss[7]);
			}
		} else if (move[0] == 'B') {
			if (piecesPoss[10]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[10]);
			}
			if (piecesPoss[11]->posx != 8) { // Check 'h' file piece is uncaptured
				piece.push_back(piecesPoss[11]);
			}
		} else if (move[0] == 'Q') {
			if (piecesPoss[13]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[13]);
			}
		} else if (move[0] == 'K') {
			if (piecesPoss[15]->posx != 8) { // Check 'a' file piece is uncaptured
				piece.push_back(piecesPoss[15]);
			}
		}
        i = 24;
    }
    pawns = i + 8;
    while (i < pawns) {
        if (piecesPoss[i]->pieceType == move[0]) { // Check for pawns promoted to pieces
            if (piecesPoss[i]->posx != 8) { // Check if piece is captured
                piece.push_back(piecesPoss[i]);
            }
        }
        i++;
    }
    if (piece.size() <= 0) {
        cout << "Error (main.cpp 199): You do not have any uncaptured pieces of type " << move[0] << ".\n";
        return false;
    }
    int x, y;
    if (move.size() == 3) { // Normal move
        y = letterToNum(move[1]);
        x = charToNum(move[2]);
        if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
            cout << "Error (main.cpp 207): Please choose a square on the board.\n";
            return false;
        } else {
            for (int j = 0; j < piece.size(); j++) {
                if (piece[j]->moveIsValid(x, y, board)) { // Check if move is valid
                    for (int i = j+1; i < piece.size(); i++) {
                        if (piece[i]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                            cout << "Error (main.cpp 214): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                            cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                            return false;
                        }
                    }
                    piece[j]->move(x,y, boardPoss, piecesPoss);
                    update(boardPoss, piecesPoss);
                    if (badCheck(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 228): That move puts or leaves you in check.\n";
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(boardPoss, piecesPoss);
                        return false;
                    }
                    if (check(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 229): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(boardPoss, piecesPoss);
                        return false;
                    }
                    if (stalemate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        update(board, pieces);
                        cout << "Stalemate!\n";
                        gameOver = true;
                        return true;
                    }
                    copyBoard(boardPoss, board, piecesPoss, pieces);
                    update(board, pieces);
                    return true;
                }
            }
            cout << "Error (main.cpp 240): Move was invalid.\n";
            return false;
        }
    } else if (move.size() == 4) {
        if (move[3] == '+' || move[3] == '#') { // Move is Check or Mate
            y = letterToNum(move[1]);
            x = charToNum(move[2]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (main.cpp 248): Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < piece.size(); j++) {
                    if (piece[j]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                        for (int i = j+1; i < piece.size(); i++) {
                            if (piece[i]->moveIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                cout << "Error (main.cpp 255): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                return false;
                            }
                        }
                        piece[j]->move(x,y, boardPoss, piecesPoss);
                        update(boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 271): That move puts or leaves you in check.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(boardPoss, piecesPoss);
                            return false;
                        }
                        if (!check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 278): That move is not check, remove the  '+' or '#'\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(boardPoss, piecesPoss);
                            return false;
                        }
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(boardPoss2, piecesPoss2);
                        if (checkmate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                            if (move[3] == '#') {
                                cout << "Checkmate!\n";
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(board, pieces);
                                gameOver = true;
                                return true;
                            } else {
                                cout << "Error (main.cpp 294): That move is checkmate, please use '#' at the end.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(boardPoss2, piecesPoss2);
                                return false;
                            }
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(board, pieces);
                        update(boardPoss2, piecesPoss2);
                        return true;
                    }
                }
                cout << "Error (main.cpp 312): Move is invalid.\n";
                return false;
            }
        } else if (move[1] == 'x') { // Move is a capture
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (main.cpp 319): Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < piece.size(); j++) {
                    if (piece[j]->captureIsValid(x, y, boardPoss)) { // Check if move is valid
                        for (int i = j+1; i < piece.size(); i++) {
                            if (piece[i]->captureIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                cout << "Error (main.cpp 327): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                return false;
                            }
                        }
                        piece[j]->move(x,y, boardPoss, piecesPoss);
                        update(boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 334): That move puts or leaves you in check.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(boardPoss, piecesPoss);
                            return false;
                        }
                        if (check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 340): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(boardPoss, piecesPoss);
                            return false;
                        }
                        if (stalemate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            update(board, pieces);
                            cout << "Stalemate!\n";
                            gameOver = true;
                            return true;
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(board, pieces);
                        update(boardPoss2, piecesPoss2);
                        return true;
                    }
                }
                cout << "Error (main.cpp 354): Move was invalid.\n";
                return false;
            }
        } else if (letterToNum(move[1]) != 8) { // Specify piece by file
            int file = letterToNum(move[1]);
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (main.cpp 362): Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < piece.size(); j++) {
                    if (piece[j]->posy == file) { // Check if specified file checks out
                        if (piece[j]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                            for (int i = j+1; i < piece.size(); i++) {
                                if (piece[i]->posy == file) { // Check if specified file checks out
                                    if (piece[i]->moveIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                        cout << "Error (main.cpp 350): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                        cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                        return false;
                                    }
                                }
                            }
                            piece[j]->move(x,y, boardPoss, piecesPoss);
                            update(boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 380): That move puts or leaves you in check.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                return false;
                            }
                            if (check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 366): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                return false;
                            }
                            if (stalemate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(board, pieces);
                                cout << "Stalemate!\n";
                                gameOver = true;
                                return true;
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(board, pieces);
                            update(boardPoss2, piecesPoss2);
                            return true;
                        }
                    }
                }
                cout << "Error (main.cpp 402): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                return false;
            }
        } else if (charToNum(move[1]) != 8) { // Specify piece by rank
            int rank = charToNum(move[1]);
            y = letterToNum(move[2]);
            x = charToNum(move[3]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (main.cpp 410): Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < piece.size(); j++) {
                    if (piece[j]->posx == rank) { // Check if specified file checks out
                        if (piece[j]->moveIsValid(x, y, board)) { // Check if move is valid
                            for (int i = j+1; i < piece.size(); i++) {
                                if (piece[i]->posx == rank) { // Check if specified file checks out
                                    if (piece[i]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                        cout << "Error (main.cpp 419): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                        cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                        return false;
                                    }
                                }
                            }
                            piece[j]->move(x,y, boardPoss, piecesPoss);
                            update(boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 428): That move puts or leaves you in check.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                return false;
                            }
                            if (check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 435): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                return false;
                            }
                            if (stalemate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(board, pieces);
                                cout << "Stalemate!\n";
                                gameOver = true;
                                return true;
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(board, pieces);
                            update(boardPoss2, piecesPoss2);
                            return true;
                        }
                    }
                }
                cout << "Error (main.cpp 450): You do not have any piece of type '" << move[0] << "' on the specified rank that can move there.\n";
                return false;
            }       
        } else {
            cout << "Error (main.cpp 454): Make a valid move.\n";
            return false;
        }
    } else if (move.size() == 5) {
        if (move[4] == '+' || move[4] == '#') { // Move is Check/mate and Capture
            if (move[1] == 'x') {
                y = letterToNum(move[2]);
                x = charToNum(move[3]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 463): Please choose a square on the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < piece.size(); j++) {
                        if (piece[j]->captureIsValid(x, y, boardPoss)) { // Check if move is valid
                            for (int i = j+1; i < piece.size(); i++) {
                                if (piece[i]->captureIsValid(x, y, boardPoss)){ // Check other piece can't move to the same squre
                                    cout << "Error (main.cpp 445): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                    cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                    return false;
                                }
                            }
                            piece[j]->move(x,y, boardPoss, piecesPoss);
                            update(boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 478): That move puts or leaves you in check.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                return false;
                            }
                            if (!check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 460): That move is not check, remove the '+' or '#'\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(boardPoss, piecesPoss);
                                return false;
                            }
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(boardPoss2, piecesPoss2);
                            if (checkmate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                if (move[4] == '#') {
                                    cout << "Checkmate!\n";
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(board, pieces);
                                    gameOver = true;
                                    return true;
                                } else {
                                    cout << "Error (main.cpp 471): That move is checkmate, please use '#' at the end.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(boardPoss2, piecesPoss2);
                                    return false;
                                }
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(board, pieces);
                            update(boardPoss2, piecesPoss2);
                            return true;
                        }
                    }
                    cout << "Error (main.cpp 483): Move was invalid.\n";
                    return false;
                }
            } else if (charToNum(move[1]) != 8) { // Specified Check/mate by rank
                int rank = charToNum(move[1]);
                y = letterToNum(move[2]);
                x = charToNum(move[3]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 491): Please choose a square on the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < piece.size(); j++) {
                        if (piece[j]->posx == rank) { // Check if specified rank checks out
                            if (piece[j]->moveIsValid(x, y, board)) { // Check if move is valid
                                for (int i = j+1; i < piece.size(); i++) {
                                    if (piece[i]->posx == rank) { // Check if specified rank checks out
                                        if (piece[i]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                            cout << "Error (main.cpp 500): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                            cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                            return false;
                                        }
                                    }
                                }
                                piece[j]->move(x,y, boardPoss, piecesPoss);
                                update(boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 837): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                if (!check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 516): That move is not check, remove the '+' or '#'\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(boardPoss2, piecesPoss2);
                                if (checkmate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    if (move[4] == '#') {
                                        cout << "Checkmate!\n";
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        update(board, pieces);gameOver = true;
                                        gameOver = true;
                                        return true;
                                    } else {
                                        cout << "Error (main.cpp 527): That move is checkmate, please use '#' at the end.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(boardPoss, piecesPoss);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(boardPoss2, piecesPoss2);
                                        return false;
                                    }
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(board, pieces);
                                update(boardPoss2, piecesPoss2);
                                return true;
                            }
                        }
                    }
                    cout << "Error (main.cpp 541): You do not have any piece of type '" << move[0] << "' on the specified rank that can move there.\n";
                    return false;
                } 
            } else if (letterToNum(move[1]) != 8) { // Specified Check/mate by file
                int file = letterToNum(move[1]);
                y = letterToNum(move[2]);
                x = charToNum(move[3]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 549): Please choose a square on the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < piece.size(); j++) {
                        if (piece[j]->posy == file) { // Check if specified file checks out
                            if (piece[j]->moveIsValid(x, y, board)) { // Check if move is valid
                                for (int i = j+1; i < piece.size(); i++) {
                                    if (piece[i]->posy == file) { // Check if specified file checks out
                                        if (piece[i]->moveIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                            cout << "Error (main.cpp 558): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                            cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                            return false;
                                        }
                                    }
                                }
                                piece[j]->move(x,y, boardPoss, piecesPoss);
                                update(boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 837): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                if (!check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 516): That move is not check, remove the '+' or '#'\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(boardPoss2, piecesPoss2);
                                if (checkmate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    if (move[4] == '#') {
                                        cout << "Checkmate!\n";
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        update(board, pieces);gameOver = true;
                                        gameOver = true;
                                        return true;
                                    } else {
                                        cout << "Error (main.cpp 527): That move is checkmate, please use '#' at the end.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(boardPoss, piecesPoss);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(boardPoss2, piecesPoss2);
                                        return false;
                                    }
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(board, pieces);
                                update(boardPoss2, piecesPoss2);
                                return true;
                            }
                        }
                    }
                    cout << "Error (main.cpp 599): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                    return false;
                } 
            }
            cout << "Error (main.cpp 603): Please make a valid move.\n";
            return false;
        } else if (move[2] == 'x') { // Capture and Specify
            if (charToNum(move[1]) != 8) { // Capture and specify by rank
                int rank = charToNum(move[1]);
                y = letterToNum(move[3]);
                x = charToNum(move[4]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 611): Please choose a square on the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < piece.size(); j++) {
                        if (piece[j]->posx == rank) { // Check if specified rank checks out
                            if (piece[j]->captureIsValid(x, y, board)) { // Check if move is valid
                                for (int i = j+1; i < piece.size(); i++) {
                                    if (piece[i]->posx == rank) { // Check if specified rank checks out
                                        if (piece[i]->captureIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                            cout << "Error (main.cpp 620): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                            cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                            return false;
                                        }
                                    }
                                }
                                piece[j]->move(x,y, boardPoss, piecesPoss);
                                update(boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 672): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                if (check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 678): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                if (stalemate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(board, pieces);
                                    cout << "Stalemate!\n";
                                    gameOver = true;
                                    return true;
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(board, pieces);
                                update(boardPoss2, piecesPoss2);
                                return true;
                            }
                        }
                    }
                    cout << "Error (main.cpp 649): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                    return false;
                } 
            } else if (letterToNum(move[1]) != 8) { // Capture and specify by file
                int file = letterToNum(move[1]);
                y = letterToNum(move[3]);
                x = charToNum(move[4]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 702): Please choose a square on the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < piece.size(); j++) {
                        if (piece[j]->posy == file) { // Check if specified file checks out
                            if (piece[j]->captureIsValid(x, y, board)) { // Check if move is valid
                                for (int i = j+1; i < piece.size(); i++) {
                                    if (piece[i]->posy == file) { // Check if specified file checks out
                                        if (piece[i]->captureIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                            cout << "Error (main.cpp 711): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                            cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                            return false;
                                        }
                                    }
                                }
                                piece[j]->move(x,y, boardPoss, piecesPoss);
                                update(boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 720): You cannot put yourself in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                if (check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 726): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    return false;
                                }
                                if (stalemate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(board, pieces);
                                    cout << "Stalemate!\n";
                                    gameOver = true;
                                    return true;
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(board, pieces);
                                update(boardPoss2, piecesPoss2);
                                return true;
                            }
                        }
                    }
                    cout << "Error (main.cpp 695): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                    return false;
                } 
            }
        }
    } else if (move.size() == 6) {
        if (move[5] == '+' || move[4] == '#') { // Specify, Capture, and Check/mate
            if (move[2] == 'x') {
                if (letterToNum(move[1]) != 8) { // Capture, check, and specify by file
                    int file = letterToNum(move[1]);
                    y = letterToNum(move[3]);
                    x = charToNum(move[4]);
                    if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                        cout << "Error (main.cpp 708): Please choose a square on the board.\n";
                        return false;
                    } else {
                        for (int j = 0; j < piece.size(); j++) {
                            if (piece[j]->posy == file) { // Check if specified file checks out
                                if (piece[j]->captureIsValid(x, y, board)) { // Check if move is valid
                                    for (int i = j+1; i < piece.size(); i++) {
                                        if (piece[i]->posy == file) { // Check if specified file checks out
                                            if (piece[i]->captureIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                                cout << "Error (main.cpp 764): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                                cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                                return false;
                                            }
                                        }
                                    }
                                    piece[j]->move(x,y, boardPoss, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    if (badCheck(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 773): That move puts or leaves you in check.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (!check(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 733): That move is not check, remove the '+' or '#'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(boardPoss, piecesPoss);
                                        return false;
                                    }
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(boardPoss2, piecesPoss2);
                                    if (checkmate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                        if (move[4] == '#') {
                                            cout << "Checkmate!\n";
                                            copyBoard(boardPoss, board, piecesPoss, pieces);
                                            update(board, pieces);gameOver = true;
                                            gameOver = true;
                                            return true;
                                        } else {
                                            cout << "Error (main.cpp 744): That move is checkmate, please use '#' at the end.\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(boardPoss, piecesPoss);
                                            copyBoard(board, boardPoss2, pieces, piecesPoss2);
                                            update(boardPoss2, piecesPoss2);
                                            return false;
                                        }
                                    }
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(board, pieces);
                                    update(boardPoss2, piecesPoss2);
                                    return true;
                                }
                            }
                        }
                        cout << "Error (main.cpp 758): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                        return false;
                    }
                } else if (charToNum(move[1]) != 8) { // Capture, check, and specify by rank
                    int rank = charToNum(move[1]);
                    y = letterToNum(move[3]);
                    x = charToNum(move[4]);
                    if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                        cout << "Error (main.cpp 766): Please choose a square on the board.\n";
                        return false;
                    } else {
                        for (int j = 0; j < piece.size(); j++) {
                            if (piece[j]->posx == rank) { // Check if specified rank checks out
                                if (piece[j]->captureIsValid(x, y, board)) { // Check if move is valid
                                    for (int i = j+1; i < piece.size(); i++) {
                                        if (piece[i]->posx == rank) { // Check if specified rank checks out
                                            if (piece[i]->captureIsValid(x, y, board)){ // Check other piece can't move to the same squre
                                                cout << "Error (main.cpp 775): Multiple pieces of type '" << move[0] << "' can move to the same position\n";
                                                cout << "Please specify which piece you'd like to move (i.e. " << move[0] << "ae4 or " << move[0] << "3e4)\n";
                                                return false;
                                            }
                                        }
                                    }
                                    piece[j]->move(x,y, boardPoss, piecesPoss);
                                    update(boardPoss, piecesPoss);
                                    if (badCheck(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 837): That move puts or leaves you in check.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (!check(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 791): That move is not check, remove the '+' or '#'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (checkmate(boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                        if (move[5] == '#') {
                                            cout << "Checkmate!\n";
                                            copyBoard(boardPoss, board, piecesPoss, pieces);
                                            update(board, pieces);gameOver = true;
                                            gameOver = true;
                                            return true;
                                        } else {
                                            cout << "Error (main.cpp 802): That move is checkmate, please use '#' at the end.\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(boardPoss, piecesPoss);
                                            return false;
                                        }
                                    }
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(board, pieces);
                                    update(boardPoss2, piecesPoss2);
                                    return true;
                                }
                            }
                        }
                        cout << "Error (main.cpp 816): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                        return false;
                    }
                }
                cout << "Error (main.cpp 820): Please make a valid move";
                return false;
            }
            cout << "Error (main.cpp 823): Please make a valid move";
            return false;
        }
    } else {
        cout << "Error (main.cpp 827): Please make a valid move";
        return false;
    }
    return false;
}

bool badCheck(string (*board)[8], Piece** pieces, char col) {
    if (col == 'W') {
        if (pieces[14]->inCheck) { // You put yourself in check
            return true;
        }
        return false;
    } else {
        if (pieces[15]->inCheck) { // You put yourself in check
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
            return true;
        }
        return false;
    }
}

bool stalemate(string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    copyBoard(board, board1, pieces, pieces1);
    update(board1, pieces1);
    char color;
    if (col == 'W') {
        color = 'B';
    } else {
        color = 'W';
    }
    for (int i = 0; i < 32; i++) {
        if (pieces1[i]->color == color) {
            for (int j = 0; j < pieces1[i]->coveredTiles.size(); j++) {
                if (board1[pieces1[i]->coveredTiles[j].a[0]][pieces1[i]->coveredTiles[j].a[1]] != "") {
                    if (board1[pieces[i]->coveredTiles[j].a[0]][pieces1[i]->coveredTiles[j].a[1]][0] != color) {
                        pieces[i]->move(pieces1[i]->coveredTiles[j].a[0], pieces1[i]->coveredTiles[j].a[1], board1, pieces1);
                        update(board1, pieces1);
                        if (!badCheck(board1, pieces1, color)) {
                            copyBoard(board1, board, pieces1, pieces);
                            update(board1, pieces1);
                            return false;
                        }
                        copyBoard(board, board1, pieces, pieces1);
                        update(board1, pieces1);
                    }

                } else {
                    pieces1[i]->move(pieces1[i]->coveredTiles[j].a[0], pieces1[i]->coveredTiles[j].a[1], board1, pieces1);
                    update(board1, pieces1);
                    if (!badCheck(board1, pieces1, color)) {
                        copyBoard(board, board1, pieces, pieces1);
                        update(board1, pieces1);
                        return false;
                    }
                    copyBoard(board, board1, pieces, pieces1);
                    update(board1, pieces1);
                }
                
            }
        }
    }
    return true;
}

bool checkmate(string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    int king, x, y;
    if (col == 'W') {
        king = 15;
    } else {
        king = 14;
    }
    if (pieces[king]->attackers.size() == 2) { // double check
        if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) { // Check for valid king moves or captures
            return false;
        } else { // Checkmate
            return true;
        } 
    } else { // regular check
        if (pieces[king]->attackers[0]->pieceType == 'P') { // Pawn attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                return false;
            }
            if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                return false;
            }
            return true;
        } else if (pieces[king]->attackers[0]->pieceType == 'R') { // Rook attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (x == pieces[king]->posx) { // Rook is on same rank
                if (y < pieces[king]->posy) { // Rook is in 'a' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Rook is in 'h' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else { // Rook is on same file
                if (x < pieces[king]->posx) { // Rook is in '1' direction of king
                    while (x < pieces[king]->posx) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Rook is in '8' direction of king
                    while (x > pieces[king]->posx) { 
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            }
        } else if (pieces[king]->attackers[0]->pieceType == 'N') { // Knight attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                return false;
            }
            if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                return false;
            }
            return true;
        } else if (pieces[king]->attackers[0]->pieceType == 'B') { // Bishop attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (x > pieces[king]->posx) {
                if (y > pieces[king]->posy) { // Bishop is in 'h8' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Bishop is in 'a8' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else { 
                if (y < pieces[king]->posy) { // Bishop is in 'a1' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Rook is in 'h1' direction of king
                    while (y > pieces[king]->posx) { 
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            }
        } else { // Queen attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (x == pieces[king]->posx) { // Queen is on same rank
                if (y < pieces[king]->posy) { // Queen is in 'a' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in 'h' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else if (y == pieces[king]->posy) { // Queen is on same file
                if (x < pieces[king]->posx) { // Queen is in '1' direction of king
                    while (x < pieces[king]->posx) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in '8' direction of king
                    while (x > pieces[king]->posx) { 
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else if (x > pieces[king]->posx) {
                if (y > pieces[king]->posy) { // Queen is in 'h8' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in 'a8' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else { 
                if (y < pieces[king]->posy) { // Queen is in 'a1' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y++;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in 'h1' direction of king
                    while (y > pieces[king]->posx) { 
                        if (checkForBlock(x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y--;
                    }
                    if (checkValidKingMove(king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            }
        }
    }
}

bool checkForBlock(int x, int y, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    for (int i = 0; i < 32; i++) {
        if (pieces1[i]->color != col || i == 14 || i == 15) {
            for (int j = 0; j < pieces1[i]->coveredTiles.size(); j++) {
                if (pieces1[i]->coveredTiles[j].a[0] == x && pieces1[i]->coveredTiles[j].a[1] == y) {
                    pieces1[i]->move(x,y, board1, pieces1);
                    update(board1, pieces1);
                    if (!badCheck(board1, pieces1, pieces[i]->color)) {
                        copyBoard(board, board1, pieces, pieces1);
                        return true;
                    }
                    copyBoard(board, board1, pieces, pieces1);
                }
            }
        } 
    }
    return false;
}

bool checkValidKingMove(int king, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    for (int i = pieces1[king]->posx-1; i <= pieces1[king]->posx+1; i++) {
        for (int j = pieces1[king]->posy-1; j <= pieces1[king]->posy+1; j++) {
            if (i == pieces1[king]->posx && j == pieces1[king]->posy) {
                continue;
            } else {
                if (i >=0 && i <= 7 && j >=0 && j <= 7) {
                    if (board1[i][j] != "") {
                        if (board1[i][j][0] != pieces1[king]->color) {
                            pieces1[king]->move(i, j, board1, pieces1);
                            update(board1, pieces1);
                            if (!badCheck(board1, pieces1, pieces1[king]->color)) {
                                copyBoard(board, board1, pieces, pieces1);
                                return true;
                            }
                            copyBoard(board, board1, pieces, pieces1);
                        }
                    } else {
                        pieces1[king]->move(i, j, board1, pieces1);
                        update(board1, pieces1);
                        if (!badCheck(board1, pieces1, pieces1[king]->color)) {
                            copyBoard(board, board1, pieces, pieces1);
                            return true;
                        }
                        copyBoard(board, board1, pieces, pieces1);
                    }
                }
            }
        }
    }
    return false;
}

string validateKingMove(string) {
    return "";
}

string validatePawnMove(string) {
    return "";
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
    // board[0][1] = "WN";
    board[0][2] = "WB";
    // board[0][3] = "WQ";
    board[0][4] = "WK";
    board[0][5] = "WB";
    // board[0][6] = "WN";
    board[0][7] = "WR";
    // board[1][0] = "WP";
    // board[1][1] = "WP";
    // board[1][2] = "WP";
    // board[1][3] = "WP";
    // board[1][4] = "WP";
    // board[1][5] = "WP";
    // board[1][6] = "WP";
    // board[1][7] = "WP";
    // board[7][0] = "BR";
    // board[7][1] = "BN";
    board[7][2] = "BB";
    // board[7][3] = "BQ";
    board[7][4] = "BK";
    board[7][5] = "BB";
    // board[7][6] = "BN";
    board[7][7] = "BR";
    // board[6][0] = "BP";
    // board[6][1] = "BP";
    // board[6][2] = "BP";
    // board[6][3] = "BP";
    board[6][4] = "BP";
    // board[6][5] = "BP";
    // board[6][6] = "BP";
    // board[6][7] = "BP";
    // pieces[0] = new Rook(0,0,'W'), pieces[1] = new Rook(0,7,'W'), pieces[2] = new Rook(7,0,'B'), pieces[3] = new Rook(7,7,'B');
    // pieces[4] = new Knight(0,1,'W'), pieces[5] = new Knight(0,6,'W'), pieces[6] = new Knight(7,1,'B'), pieces[7] = new Knight(7,6,'B');
    // pieces[8] = new Bishop(0,2,'W'), pieces[9] = new Bishop(0,5,'W'), pieces[10] = new Bishop(7,2,'B'), pieces[11] = new Bishop(7,5,'B');
    // pieces[12] = new Queen(0,3,'W'), pieces[13] = new Queen(7,3,'B');
    // pieces[14] = new King(0,4,'W'), pieces[15] = new King(7,4,'B');
    // for (int i=0; i<8; i++) {
    //     pieces[i+16] = new Pawn(1,i,'W');
    //     pieces[i+24] = new Pawn(6,i,'B');
    // }
    pieces[0] = new Rook(0,0,'W'), pieces[1] = new Rook(0,7,'W'), pieces[2] = new Rook(8,8,'B'), pieces[3] = new Rook(7,7,'B');
    pieces[4] = new Knight(8,8,'W'), pieces[5] = new Knight(8,8,'W'), pieces[6] = new Knight(8,8,'B'), pieces[7] = new Knight(8,8,'B');
    pieces[8] = new Bishop(0,2,'W'), pieces[9] = new Bishop(0,5,'W'), pieces[10] = new Bishop(7,2,'B'), pieces[11] = new Bishop(7,5,'B');
    pieces[12] = new Queen(8,8,'W'), pieces[13] = new Queen(8,8,'B');
    pieces[14] = new King(0,4,'W'), pieces[15] = new King(7,4,'B');
    for (int i=0; i<4; i++) {
        pieces[i+16] = new Pawn(1,8,'W');
        pieces[i+24] = new Pawn(6,8,'B');
    }
    pieces[20] = new Pawn(1,4,'W');
    pieces[28] = new Pawn(6,4,'B');
    for (int i=5; i<8; i++) {
        pieces[i+16] = new Pawn(8,8,'W');
        pieces[i+24] = new Pawn(8,8,'B');
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