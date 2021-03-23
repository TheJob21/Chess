#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "utility.h"
#include "bstree.h"
#include "Piece.h"
#include "utility.cpp"
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

void setBoard(string (*)[8], Piece**);
void copyBoard(string (*)[8], string (*)[8], Piece**, Piece**);
char blackOrWhite(char);
char computerOrHuman(char);
bool validatePawnMove(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
int letterToNum(char);
int charToNum(char);
void updateAtkDef(string (*)[8], Piece**);
bool check(string (*)[8], Piece**, char);
bool badCheck(string (*)[8], Piece**, char);
bool stalemate(string, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkmate(string, string (*)[8], string (*)[8], Piece**, Piece**, char);
void printBoard(string (*)[8]);
bool checkForBlock(string, int, int, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkValidKingMove(string, int, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool validateMove(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
bool castle(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
string generateMove(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);

int main()
{
    ofstream filestream("GameRecord.out");
    bool gameOver = false, isValid;
    char col, coh;
    string move, lastMove = "";
    string moves[200][2];
    int moveCount = 1;
    string (*board)[8] = new string[8][8]; 
    string (*boardPoss)[8] = new string[8][8]; 
    string (*boardPoss2)[8] = new string[8][8]; 
    string (*prevBoard)[8] = new string[8][8]; 
    Piece **pieces = new Piece*[32];
    Piece **piecesPoss = new Piece*[32];
    Piece **piecesPoss2 = new Piece*[32];
    Piece **prevPieces = new Piece*[32];
    setBoard(board, pieces);
    update(lastMove, board, pieces);
    setBoard(boardPoss, piecesPoss);
    update(lastMove, boardPoss, piecesPoss);
    setBoard(boardPoss2, piecesPoss2);
    update(lastMove, boardPoss2, piecesPoss2);
    setBoard(prevBoard, prevPieces);
    coh = computerOrHuman(coh);
    if (coh == 'c') {
        col = blackOrWhite(col);
    }

    // Game Loop
    if (coh == 'c') {
        if (col == 'w') {
            while (!gameOver) {
                // Human Turn
                cout << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board);
                cout << moveCount << ". ";
                cin >> move;
                isValid = false;
                while (!isValid) {
                    if (move.size() < 2 || move.size() > 7) {
                        cout << "Please enter a correct move ";
                        cin >> move;        
                    } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') { // Pawn move
                        if (!validatePawnMove(move, lastMove, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                            cin >> move;
                        } else {
                            isValid = true;
                        }
                    } else if (move[0] == '0') { // Castling
                        if (!castle(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                            cin >> move;
                        } else {
                            isValid = true;
                        }
                    } else {
                        if (!validateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                            cin >> move;
                        } else {
                            isValid = true;
                        }
                    }
                }
                printBoard(board);
                moves[moveCount-1][0] = lastMove = move;
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    filestream << moveCount << ". " << move;
                    break;
                }
                bool isValid = false;
                // Computer Turn
                moves[moveCount-1][1] = lastMove = generateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver);
                moveCount++;
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    printBoard(board);
                }
            }
        } else if (col == 'w') {
            while (!gameOver) {
                // Computer Turn
                moves[moveCount-1][0] = lastMove = generateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    filestream << moveCount << ". " << move;
                    break;
                }
                printBoard(board);
                // Human Turn
                cout << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board);
                cout << moveCount << ". " << lastMove << ", ";
                cin >> move;
                isValid = false;
                while (!isValid) {
                    if (move.size() < 2 || move.size() > 7) {
                        cout << "Please enter a correct move ";
                        cin >> move;        
                    } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') { // Pawn move
                        if (!validatePawnMove(move, lastMove, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                            cin >> move;
                        } else {
                            isValid = true;
                        }
                    } else if (move[0] == '0') { // Castling
                        if (!castle(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                            cin >> move;
                        } else {
                            isValid = true;
                        }
                    } else {
                        if (!validateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                            cin >> move;
                        } else {
                            isValid = true;
                        }
                    }
                }
                moves[moveCount-1][1] = lastMove = move;
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    printBoard(board);
                }
                bool isValid = false;
                moveCount++;
            }
        } else { // computer vs computer
            while (!gameOver) {
                cout << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board);
                // cout << "Press enter to continue.";
                // getline(cin, move);
                moves[moveCount-1][0] = lastMove = generateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    filestream << moveCount << ". " << lastMove;
                    for (int i = 0; i < moveCount-1; i++) {
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    cout << moveCount << ". " << lastMove << endl;
                    printBoard(board);
                    break;
                }
                for (int i = 0; i < moveCount-1; i++) {
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                cout << moveCount << ". " << lastMove << endl;
                printBoard(board);
                // cout << "Press enter to continue.";
                // getline(cin, move);
                moves[moveCount-1][1] = lastMove = generateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver);
                moveCount++;
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    for (int i = 0; i < moveCount-1; i++) {
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    printBoard(board);
                }
            }
        }
    } else { // human vs human
        while (!gameOver) {
            cout << endl;
            for (int i = 0; i < moveCount-1; i++) {
                cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
            }
            printBoard(board);
            cout << moveCount << ". ";
            cin >> move;
            isValid = false;
            while (!isValid) {
                if (move.size() < 2 || move.size() > 7) {
                    cout << "Please enter a correct move ";
                    cin >> move;        
                } else if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h') { // Pawn move
                    if (!validatePawnMove(move, lastMove, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                } else if (move[0] == '0') { // Castling
                    if (!castle(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                } else {
                    if (!validateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                }
            }
            printBoard(board);
            moves[moveCount-1][0] = lastMove = move;
            if (gameOver) {
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                filestream << moveCount << ". " << move;
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
                    if (!validatePawnMove(move, lastMove, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                } else if (move[0] == '0') { // Castling
                    if (!castle(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                } else {
                    if (!validateMove(lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver)) {
                        cin >> move;
                    } else {
                        isValid = true;
                    }
                }
            }
            moves[moveCount-1][1] = lastMove = move;
            moveCount++;
            if (gameOver) {
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board);
            }
        }
    }
    

    return 0;
}

char blackOrWhite(char col){
    cout << "Play as white or black? (w or b) (Or c to watch a computer vs computer match) ";
    while (col != 'w' && col != 'b' && col != 'c') {
        cin >> col;
        if (col == 'w' || col == 'b' || col == 'c') {
            return col;
        } else {
            cout << "please type 'w' or 'b' or 'c'"; 
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

bool validateMove(string lastMove, string move, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
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
                    update(lastMove, boardPoss, piecesPoss);
                    if (badCheck(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 228): That move puts or leaves you in check.\n";
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        return false;
                    }
                    if (check(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 229): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        return false;
                    }
                    if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        update(lastMove, board, pieces);
                        cout << "Stalemate!\n";
                        gameOver = true;
                        return true;
                    }
                    copyBoard(boardPoss, board, piecesPoss, pieces);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, board, pieces);
                    update(lastMove, boardPoss2, piecesPoss2);
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
                        update(lastMove, boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 271): That move puts or leaves you in check.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        if (!check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 278): That move is not check, remove the  '+' or '#'\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                            if (move[3] == '#') {
                                cout << "Checkmate!\n";
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(lastMove, board, pieces);
                                gameOver = true;
                                return true;
                            } else {
                                cout << "Error (main.cpp 294): That move is checkmate, please use '#' at the end.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                return false;
                            }
                        } else {
                            if (move[3] == '#') {
                                cout << "Error (main.cpp 294): That move is not checkmate, replace the '#' with a '+'\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                return false;
                            }
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, board, pieces);
                        update(lastMove, boardPoss2, piecesPoss2);
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
                        update(lastMove, boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 334): That move puts or leaves you in check.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        if (check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 340): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            update(lastMove, board, pieces);
                            cout << "Stalemate!\n";
                            gameOver = true;
                            return true;
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, board, pieces);
                        update(lastMove, boardPoss2, piecesPoss2);
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
                            update(lastMove, boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 380): That move puts or leaves you in check.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            if (check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 366): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(lastMove, board, pieces);
                                cout << "Stalemate!\n";
                                gameOver = true;
                                return true;
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, board, pieces);
                            update(lastMove, boardPoss2, piecesPoss2);
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
                            update(lastMove, boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 428): That move puts or leaves you in check.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            if (check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 435): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(lastMove, board, pieces);
                                cout << "Stalemate!\n";
                                gameOver = true;
                                return true;
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, board, pieces);
                            update(lastMove, boardPoss2, piecesPoss2);
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
                            update(lastMove, boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 478): That move puts or leaves you in check.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            if (!check(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 460): That move is not check, remove the '+' or '#'\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                if (move[4] == '#') {
                                    cout << "Checkmate!\n";
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(lastMove, board, pieces);
                                    gameOver = true;
                                    return true;
                                } else {
                                    cout << "Error (main.cpp 471): That move is checkmate, please use '#' at the end.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    return false;
                                }
                            } else {
                                if (move[4] == '#') {
                                    cout << "Error (main.cpp 294): That move is not checkmate, replace the '#' with a '+'\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    return false;
                                }
                            }
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, board, pieces);
                            update(lastMove, boardPoss2, piecesPoss2);
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
                                update(lastMove, boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 837): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                if (!check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 516): That move is not check, remove the '+' or '#'\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    if (move[4] == '#') {
                                        cout << "Checkmate!\n";
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        update(lastMove, board, pieces);gameOver = true;
                                        gameOver = true;
                                        return true;
                                    } else {
                                        cout << "Error (main.cpp 527): That move is checkmate, please use '#' at the end.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(lastMove, boardPoss2, piecesPoss2);
                                        return false;
                                    }
                                } else {
                                    if (move[4] == '#') {
                                        cout << "Error (main.cpp 294): That move is not checkmate, replace the '#' with a '+'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(lastMove, boardPoss2, piecesPoss2);
                                        return false;
                                    }
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, board, pieces);
                                update(lastMove, boardPoss2, piecesPoss2);
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
                                update(lastMove, boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 837): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                if (!check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 516): That move is not check, remove the '+' or '#'\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    if (move[4] == '#') {
                                        cout << "Checkmate!\n";
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        update(lastMove, board, pieces);gameOver = true;
                                        gameOver = true;
                                        return true;
                                    } else {
                                        cout << "Error (main.cpp 527): That move is checkmate, please use '#' at the end.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(lastMove, boardPoss2, piecesPoss2);
                                        return false;
                                    }
                                } else {
                                    if (move[4] == '#') {
                                        cout << "Error (main.cpp 294): That move is not checkmate, replace the '#' with a '+'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(lastMove, boardPoss2, piecesPoss2);
                                        return false;
                                    }
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, board, pieces);
                                update(lastMove, boardPoss2, piecesPoss2);
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
                                update(lastMove, boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 672): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                if (check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 678): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(lastMove, board, pieces);
                                    cout << "Stalemate!\n";
                                    gameOver = true;
                                    return true;
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, board, pieces);
                                update(lastMove, boardPoss2, piecesPoss2);
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
                                update(lastMove, boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 720): You cannot put yourself in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                if (check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 726): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(lastMove, board, pieces);
                                    cout << "Stalemate!\n";
                                    gameOver = true;
                                    return true;
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, board, pieces);
                                update(lastMove, boardPoss2, piecesPoss2);
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
        if (move[5] == '+' || move[5] == '#') { // Specify, Capture, and Check/mate
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
                                    update(lastMove, boardPoss, piecesPoss);
                                    if (badCheck(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 773): That move puts or leaves you in check.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (!check(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 733): That move is not check, remove the '+' or '#'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                        if (move[5] == '#') {
                                            cout << "Checkmate!\n";
                                            copyBoard(boardPoss, board, piecesPoss, pieces);
                                            update(lastMove, board, pieces);gameOver = true;
                                            gameOver = true;
                                            return true;
                                        } else {
                                            cout << "Error (main.cpp 744): That move is checkmate, please use '#' at the end.\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            copyBoard(board, boardPoss2, pieces, piecesPoss2);
                                            update(lastMove, boardPoss2, piecesPoss2);
                                            return false;
                                        }
                                    } else {
                                        if (move[5] == '#') {
                                            cout << "Error (main.cpp 294): That move is not checkmate, replace the '#' with a '+'\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                            update(lastMove, boardPoss2, piecesPoss2);
                                            return false;
                                        }
                                    }
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, board, pieces);
                                    update(lastMove, boardPoss2, piecesPoss2);
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
                                    update(lastMove, boardPoss, piecesPoss);
                                    if (badCheck(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 837): That move puts or leaves you in check.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (!check(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 791): That move is not check, remove the '+' or '#'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                        if (move[5] == '#') {
                                            cout << "Checkmate!\n";
                                            copyBoard(boardPoss, board, piecesPoss, pieces);
                                            update(lastMove, board, pieces);gameOver = true;
                                            gameOver = true;
                                            return true;
                                        } else {
                                            cout << "Error (main.cpp 802): That move is checkmate, please use '#' at the end.\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            return false;
                                        }
                                    } else {
                                        if (move[5] == '#') {
                                            cout << "Error (main.cpp 294): That move is not checkmate, replace the '#' with a '+'\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                            update(lastMove, boardPoss2, piecesPoss2);
                                            return false;
                                        }
                                    }
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, board, pieces);
                                    update(lastMove, boardPoss2, piecesPoss2);
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

bool validatePawnMove(string move, string lastMove, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
    vector<int> p;
    bool enPassant = false;
    int i, pawns;
    if (col == 'W') {
        i = 16;
    } else {
        i = 24;
    }
    pawns = i + 8;
    while (i < pawns) {
        if (piecesPoss[i]->pieceType == 'P') { // Check for pawns promoted to pieces
            if (piecesPoss[i]->posx != 8) { // Check if piece is captured
                p.push_back(i);
            }
        }
        i++;
    }
    if (p.size() <= 0) {
        cout << "Error (main.cpp 1434): You do not have any uncaptured pieces of type " << move[0] << ".\n";
        return false;
    }
    int x, y;
    if (move.size() == 2) { // Normal move
        y = letterToNum(move[0]);
        x = charToNum(move[1]);
        if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
            cout << "Error (main.cpp 1442): Please choose a square on the board.\n";
            return false;
        } else {
            for (int j = 0; j < p.size(); j++) {
                if (piecesPoss[p[j]]->moveIsValid(x, y, board)) { // Check if move is valid
                    piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                    update(lastMove, boardPoss, piecesPoss);
                    if (badCheck(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 1450): That move puts or leaves you in check.\n";
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        return false;
                    }
                    if (check(boardPoss, piecesPoss, col)) {
                        cout << "Error (main.cpp 1456): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        return false;
                    }
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        update(lastMove, board, pieces);
                        cout << "Stalemate!\n";
                        gameOver = true;
                        return true;
                    }
                    copyBoard(boardPoss, board, piecesPoss, pieces);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, board, pieces);
                    update(lastMove, boardPoss2, piecesPoss2);
                    return true;
                }
            }
            cout << "Error (main.cpp 1475): Move was invalid.\n";
            return false;
        }
    } else if (move.size() == 3) {
        if (move[2] == '+' || move[2] == '#') { // Move is Check or Mate
            y = letterToNum(move[0]);
            x = charToNum(move[1]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (main.cpp 1483): Please choose a square on the board.\n";
                return false;
            } else {
                for (int j = 0; j < p.size(); j++) {
                    if (piecesPoss[p[j]]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                        piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 1491): That move puts or leaves you in check.\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        if (!check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 1497): That move is not check, remove the  '+' or '#'\n";
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                            if (move[2] == '#') {
                                cout << "Checkmate!\n";
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                update(lastMove, board, pieces);
                                gameOver = true;
                                return true;
                            } else {
                                cout << "Error (main.cpp 1512): That move is checkmate, please use '#' at the end.\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                return false;
                            }
                        } else {
                            if (move[2] == '#') {
                                cout << "Error (main.cpp 1521): That move is not checkmate, replace the '#' with a '+'\n";
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                return false;
                            }
                        }
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, board, pieces);
                        update(lastMove, boardPoss2, piecesPoss2);
                        return true;
                    }
                }
                cout << "Error (main.cpp 1536): Move is invalid.\n";
                return false;
            }
        } else if (move[2] == 'Q' || move[2] == 'N' || move[2] == 'R' || move[2] == 'B') { // Pawn Promotion
            y = letterToNum(move[0]);
            x = charToNum(move[1]);
            if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                cout << "Error (main.cpp 1543): Please choose a square on the board.\n";
                return false;
            } else if (col == 'W' && x != 7) {
                cout << "Error (main.cpp 1546): You cannot promote until you reach the other end of the board.\n";
                return false;
            } else if ((col == 'B' && x != 0)) {
                cout << "Error (main.cpp 1549): You cannot promote until you reach the other end of the board.\n";
                return false;
            } else {
                for (int j = 0; j < p.size(); j++) {
                    if (piecesPoss[p[j]]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                        piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                        promote(col, move[2], p[j], boardPoss, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        if (badCheck(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 1558): That move puts or leaves you in check.\n";
                            promote(col, 'P', p[j], boardPoss, piecesPoss);
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        if (check(boardPoss, piecesPoss, col)) {
                            cout << "Error (main.cpp 1565): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                            promote(col, 'P', p[j], boardPoss, piecesPoss);
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                        promote(col, move[2], p[j], boardPoss2, piecesPoss2);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                            promote(col, piecesPoss[p[j]]->pieceType, p[j], board, pieces);
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            update(lastMove, board, pieces);
                            cout << "Stalemate!\n";
                            gameOver = true;
                            return true;
                        }
                        promote(col, piecesPoss[p[j]]->pieceType, p[j], board, pieces);
                        copyBoard(boardPoss, board, piecesPoss, pieces);
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, board, pieces);
                        update(lastMove, boardPoss2, piecesPoss2);
                        return true;
                    }
                }
                cout << "Error (main.cpp 1591): Move is invalid.\n";
                return false;
            }
        } else {
            cout << "Error (main.cpp 1595): Make a valid move.\n";
            return false;
        }
    } else if (move.size() == 4) {
        if (move[3] == '+' || move[3] == '#') { // Check/mate
            if (move[2] == 'Q' || move[2] == 'N' || move[2] == 'R' || move[2] == 'B') { // Pawn Promotion
                y = letterToNum(move[0]);
                x = charToNum(move[1]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 1604): Please choose a square on the board.\n";
                    return false;
                } else if (col == 'W' && x != 7) {
                    cout << "Error (main.cpp 1607): You cannot promote until you reach the other end of the board.\n";
                    return false;
                } else if ((col == 'B' && x != 0)) {
                    cout << "Error (main.cpp 1610): You cannot promote until you reach the other end of the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < p.size(); j++) {
                        if (piecesPoss[p[j]]->moveIsValid(x, y, boardPoss)) { // Check if move is valid
                            piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                            promote(col, move[2], p[j], boardPoss, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            if (badCheck(boardPoss, piecesPoss, col)) {
                                cout << "Error (main.cpp 1619): That move puts or leaves you in check.\n";
                                promote(col, 'P', p[j], boardPoss, piecesPoss);
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            if (!check(boardPoss, piecesPoss, col)) { // Ensure Check
                                cout << "Error (main.cpp 1626): That move is not check, remove the  '+' or '#'\n";
                                promote(col, 'P', p[j], boardPoss, piecesPoss);
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                            promote(col, move[2], p[j], boardPoss2, piecesPoss2);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                if (move[3] == '#') {
                                    cout << "Checkmate!\n";
                                    promote(col, piecesPoss[p[j]]->pieceType, p[j], board, pieces);
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(lastMove, board, pieces);
                                    gameOver = true;
                                    return true;
                                } else {
                                    cout << "Error (main.cpp 1644): That move is checkmate, please use '#' at the end.\n";
                                    promote(col, 'P', p[j], boardPoss, piecesPoss);
                                    promote(col, 'P', p[j], boardPoss2, piecesPoss2);
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    return false;
                                }
                            } else {
                                if (move[3] == '#') {
                                    cout << "Error (main.cpp 1655): That move is not checkmate, replace the '#' with a '+'\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    return false;
                                }
                            }
                            promote(col, piecesPoss[p[j]]->pieceType, p[j], board, pieces);
                            promote(col, piecesPoss[p[j]]->pieceType, p[j], boardPoss2, piecesPoss2);
                            copyBoard(boardPoss, board, piecesPoss, pieces);
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, board, pieces);
                            update(lastMove, boardPoss2, piecesPoss2);
                            return true;
                        }
                    }
                    cout << "Error (main.cpp 1673): Move is invalid.\n";
                    return false;
                }
            } else {
                cout << "Error (main.cpp 1677): Select a legitimate piece for promotion (i.e. 'e8Q+' or 'd1N#').\n";
                return false;
            }
        } else if (letterToNum(move[0]) != 8) { // Specified by file
            if (move[1] == 'x') { // Specify and capture
                int file = letterToNum(move[0]);
                y = letterToNum(move[2]);
                x = charToNum(move[3]);
                if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                    cout << "Error (main.cpp 1686): Please choose a square on the board.\n";
                    return false;
                } else {
                    for (int j = 0; j < p.size(); j++) {
                        if (piecesPoss[p[j]]->posy == file) { // Check if specified file checks out
                            if (piecesPoss[p[j]]->captureIsValid2(x, y, lastMove, boardPoss, piecesPoss, enPassant)) { // Check if move is valid
                                if (enPassant) {
                                    findPiece(piecesPoss[p[j]]->posx, y, boardPoss, pieces, boardPoss[piecesPoss[p[j]]->posx][y][0])->posx = 8;
                                    boardPoss[piecesPoss[p[j]]->posx][y] = "";
                                }
                                piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                if (badCheck(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 1695): That move puts or leaves you in check.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                if (check(boardPoss, piecesPoss, col)) {
                                    cout << "Error (main.cpp 1701): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, boardPoss2, piecesPoss2);
                                if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(lastMove, board, pieces);
                                    cout << "Stalemate!\n";
                                    gameOver = true;
                                    return true;
                                }
                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                update(lastMove, board, pieces);
                                update(lastMove, boardPoss2, piecesPoss2);
                                return true;
                            }
                        }
                    }
                    cout << "Error (main.cpp 1724): You do not have any pawn on the specified file that can move there.\n";
                    return false;
                }
            }
        }
    } else if (move.size() == 5) {
        if (move[4] == '+' || move[4] == '#') { // Specify, Capture, and Check/mate
            if (move[1] == 'x') {
                if (letterToNum(move[0]) != 8) { // Capture, check, and specify by file
                    int file = letterToNum(move[0]);
                    y = letterToNum(move[2]);
                    x = charToNum(move[3]);
                    if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                        cout << "Error (main.cpp 1737): Please choose a square on the board.\n";
                        return false;
                    } else {
                        for (int j = 0; j < p.size(); j++) {
                            if (piecesPoss[p[j]]->posy == file) { // Check if specified file checks out
                                if (piecesPoss[p[j]]->captureIsValid2(x, y, lastMove, boardPoss, piecesPoss, enPassant)) { // Check if move is valid
                                    if (enPassant) {
                                        findPiece(piecesPoss[p[j]]->posx, y, boardPoss, pieces, boardPoss[piecesPoss[p[j]]->posx][y][0])->posx = 8;
                                        boardPoss[piecesPoss[p[j]]->posx][y] = "";
                                    }
                                    piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    if (badCheck(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 1746): That move puts or leaves you in check.\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (!check(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 1752): That move is not check, remove the '+' or '#'\n";
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                        if (move[4] == '#') {
                                            cout << "Checkmate!\n";
                                            copyBoard(boardPoss, board, piecesPoss, pieces);
                                            update(lastMove, board, pieces);gameOver = true;
                                            gameOver = true;
                                            return true;
                                        } else {
                                            cout << "Error (main.cpp 1767): That move is checkmate, please use '#' at the end.\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            copyBoard(board, boardPoss2, pieces, piecesPoss2);
                                            update(lastMove, boardPoss2, piecesPoss2);
                                            return false;
                                        }
                                    } else {
                                        if (move[4] == '#') {
                                            cout << "Error (main.cpp 1776): That move is not checkmate, replace the '#' with a '+'\n";
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                            update(lastMove, boardPoss2, piecesPoss2);
                                            return false;
                                        }
                                    }
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, board, pieces);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    return true;
                                }
                            }
                        }
                        cout << "Error (main.cpp 1793): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                        return false;
                    }
                } 
            }
            cout << "Error (main.cpp 1798): Please make a valid move";
            return false;
        } else if (move[4] == 'Q' || move[4] == 'N' || move[4] == 'R' || move[4] == 'B') { // Specify, Capture, and Promotion
            if (move[1] == 'x') {
                if (letterToNum(move[0]) != 8) { // Capture, promote, and specify by file
                    int file = letterToNum(move[0]);
                    y = letterToNum(move[2]);
                    x = charToNum(move[3]);
                    if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                        cout << "Error (main.cpp 1807): Please choose a square on the board.\n";
                        return false;
                    } else if (col == 'W' && x != 7) {
                        cout << "Error (main.cpp 1810): You cannot promote until you reach the other end of the board.\n";
                        return false;
                    } else if ((col == 'B' && x != 0)) {
                        cout << "Error (main.cpp 1813): You cannot promote until you reach the other end of the board.\n";
                        return false;
                    } else {
                        for (int j = 0; j < p.size(); j++) {
                            if (piecesPoss[p[j]]->posy == file) { // Check if specified file checks out
                                if (piecesPoss[p[j]]->captureIsValid(x, y, board)) { // Check if move is valid
                                    piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                                    promote(col, move[4], p[j], boardPoss, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    if (badCheck(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 1823): That move puts or leaves you in check.\n";
                                        promote(col, 'P', p[j], boardPoss, piecesPoss);
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    if (check(boardPoss, piecesPoss, col)) {
                                        cout << "Error (main.cpp 1830): That move is check, please add a '+' to the move, or '#' for checkmate.\n";
                                        promote(col, 'P', p[j], boardPoss, piecesPoss);
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                        promote(col, 'P', piecesPoss[p[j]]->pieceType, boardPoss, piecesPoss);
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        update(lastMove, board, pieces);
                                        cout << "Stalemate!\n";
                                        gameOver = true;
                                        return true;
                                    }
                                    promote(col, piecesPoss[p[j]]->pieceType, p[j], board, pieces);
                                    promote(col, piecesPoss[p[j]]->pieceType, p[j], boardPoss2, piecesPoss2);
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                    update(lastMove, board, pieces);
                                    update(lastMove, boardPoss2, piecesPoss2);
                                    return true;
                                }
                            }
                        }
                        cout << "Error (main.cpp 1857): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                        return false;
                    }
                } 
            }
            cout << "Error (main.cpp 1862): Please make a valid move";
            return false;
        }
    } else if (move.size() == 6) {
        if (move[5] == '+' || move[5] == '#') { // Specify, Capture, Promote, and Check/mate
            if (move[1] == 'x') { // Capture
                if (letterToNum(move[0]) != 8) { // Specify by file
                    if (move[4] == 'Q' || move[4] == 'N' || move[4] == 'R' || move[4] == 'B') { // Promotion
                        int file = letterToNum(move[0]);
                        y = letterToNum(move[2]);
                        x = charToNum(move[3]);
                        if (x == 8 || y < 0 || y > 7) { // Validate a-h, 1-8
                            cout << "Error (main.cpp 1874): Please choose a square on the board.\n";
                            return false;
                        } else if (col == 'W' && x != 7) {
                            cout << "Error (main.cpp 1877): You cannot promote until you reach the other end of the board.\n";
                            return false;
                        } else if ((col == 'B' && x != 0)) {
                            cout << "Error (main.cpp 1880): You cannot promote until you reach the other end of the board.\n";
                            return false;
                        } else {
                            for (int j = 0; j < p.size(); j++) {
                                if (piecesPoss[p[j]]->posy == file) { // Check if specified file checks out
                                    if (piecesPoss[p[j]]->captureIsValid(x, y, board)) { // Check if move is valid
                                        piecesPoss[p[j]]->move(x,y, boardPoss, piecesPoss);
                                        promote(col, move[4], p[j], boardPoss, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        if (badCheck(boardPoss, piecesPoss, col)) {
                                            cout << "Error (main.cpp 1890): That move puts or leaves you in check.\n";
                                            promote(col, 'P', p[j], boardPoss, piecesPoss);
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            return false;
                                        }
                                        if (!check(boardPoss, piecesPoss, col)) {
                                            cout << "Error (main.cpp 1897): That move is not check, remove the '+' or '#'\n";
                                            promote(col, 'P', p[j], boardPoss, piecesPoss);
                                            copyBoard(board, boardPoss, pieces, piecesPoss);
                                            update(lastMove, boardPoss, piecesPoss);
                                            return false;
                                        }
                                        promote(col, move[4], p[j], boardPoss2, piecesPoss2);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(lastMove, boardPoss2, piecesPoss2);
                                        if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                                            if (move[5] == '#') {
                                                cout << "Checkmate!\n";
                                                promote(col, move[4], p[j], board, pieces);
                                                copyBoard(boardPoss, board, piecesPoss, pieces);
                                                update(lastMove, board, pieces);gameOver = true;
                                                gameOver = true;
                                                return true;
                                            } else {
                                                cout << "Error (main.cpp 1915): That move is checkmate, please use '#' at the end.\n";
                                                promote(col, 'P', p[j], boardPoss, piecesPoss);
                                                promote(col, 'P', p[j], boardPoss2, piecesPoss2);
                                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                                update(lastMove, boardPoss, piecesPoss);
                                                copyBoard(board, boardPoss2, pieces, piecesPoss2);
                                                update(lastMove, boardPoss2, piecesPoss2);
                                                return false;
                                            }
                                        } else {
                                            if (move[5] == '#') {
                                                cout << "Error (main.cpp 1926): That move is not checkmate, replace the '#' with a '+'\n";
                                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                                update(lastMove, boardPoss, piecesPoss);
                                                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                                update(lastMove, boardPoss2, piecesPoss2);
                                                return false;
                                            }
                                        }
                                        promote(col, piecesPoss[p[j]]->pieceType, p[j], board, pieces);
                                        promote(col, piecesPoss[p[j]]->pieceType, p[j], boardPoss2, piecesPoss2);
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                                        update(lastMove, board, pieces);
                                        update(lastMove, boardPoss2, piecesPoss2);
                                        return true;
                                    }
                                }
                            }
                            cout << "Error (main.cpp 1788): You do not have any piece of type '" << move[0] << "' on the specified file that can move there.\n";
                            return false;
                        }
                    }
                } 
            }
            cout << "Error (main.cpp 1794): Please make a valid move";
            return false;
        } 
    } else {
        cout << "Error (main.cpp 1785): Please make a valid move";
        return false;
    }
    return false;
}

bool castle(string lastMove, string move, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
    int king, kr, qr, rkSq;
    if (col == 'W') {
        king = 14;
        kr = 1;
        qr = 0;
        rkSq = 0; 
    } else {
        king = 15;
        kr = 3;
        qr = 2;
        rkSq = 7;
    }
    if (!pieces[king]->inCheck) { // Make sure king isn't in check
        if (move == "0-0") { // King side Castle
            if (pieces[kr]->posx != 8) { // Check rook isn't captured
                if (pieces[kr]->timesMoved < 1 && pieces[king]->timesMoved < 1) { // Make sure king and rook haven't move before
                    if (piecesPoss[king]->moveIsValid(rkSq, 5, boardPoss)) {
                        piecesPoss[king]->move(rkSq, 5, boardPoss, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        if (!piecesPoss[king]->inCheck) {
                            if (piecesPoss[king]->moveIsValid(rkSq, 6, boardPoss)) {
                                piecesPoss[king]->move(rkSq, 6, boardPoss, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                if (!piecesPoss[king]->inCheck) { // Success
                                    piecesPoss[kr]->move(rkSq, 5, boardPoss, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    copyBoard(boardPoss, board, piecesPoss, pieces);
                                    update(lastMove, board, pieces);
                                    return true;
                                } else {
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    cout << "Error (main.cpp 1832): You cannot castle into an attacked square.\n";
                                    return false;
                                }
                            } else {
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                cout << "Error (main.cpp 1838): You cannot castle into occupied space.\n";
                                return false;
                            }
                        } else {
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            cout << "Error (main.cpp 1844): You cannot castle through an attacked square.\n";
                            return false;
                        }
                    } else {
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        cout << "Error (main.cpp 1850): You cannot castle into occupied space.\n";
                        return false;
                    }
                } else {
                    cout << "Error (main.cpp 1854): You cannot castle after moving one of the castling pieces.\n";
                    return false;
                }
            } else {
                cout << "Error (main.cpp 1858): You cannot castle using a captured rook!\n";
                return false;
            }
        } else if (move == "0-0-0") { // Queen side castle
            if (pieces[qr]->posx != 8) { // Check rook isn't captured
                if (pieces[qr]->timesMoved < 1 && pieces[king]->timesMoved < 1) { // Make sure king and rook haven't move before
                    if (piecesPoss[king]->moveIsValid(rkSq, 3, boardPoss)) {
                        piecesPoss[king]->move(rkSq, 3, boardPoss, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        if (!piecesPoss[king]->inCheck) {
                            if (piecesPoss[king]->moveIsValid(rkSq, 2, boardPoss)) {
                                piecesPoss[king]->move(rkSq, 2, boardPoss, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                if (!piecesPoss[king]->inCheck) {
                                    if (piecesPoss[qr]->moveIsValid(rkSq, 1, boardPoss)) { // Success
                                        piecesPoss[qr]->move(rkSq, 3, boardPoss, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        copyBoard(boardPoss, board, piecesPoss, pieces);
                                        update(lastMove, board, pieces);
                                        return true;
                                        
                                    } else {
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        cout << "Error (main.cpp 1882): You cannot castle through an occupied square.\n";
                                        return false;
                                    }
                                } else {
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    cout << "Error (main.cpp 1888): You cannot castle into an attacked square.\n";
                                    return false;
                                }
                            } else {
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                cout << "Error (main.cpp 1894): You cannot castle into occupied space.\n";
                                return false;
                            }
                        } else {
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            cout << "Error (main.cpp 1900): You cannot castle through an attacked square.\n";
                            return false;
                        }
                    } else {
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        cout << "Error (main.cpp 1906): You cannot castle into occupied space.\n";
                        return false;
                    }
                } else {
                    cout << "Error (main.cpp 1910): You cannot castle after moving one of the castling pieces.\n";
                    return false;
                }
            } else {
                cout << "Error (main.cpp 1914): You cannot castle using a captured rook!\n";
                return false;
            }
        } else {
            cout << "Error (main.cpp 1918): Please make a valid move.\n";
            return false;
        }
    } else {
        cout << "Error (main.cpp 1922): You cannot castle from check.\n";
        return false;
    }
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

bool stalemate(string lastMove, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    copyBoard(board, board1, pieces, pieces1);
    update(lastMove, board1, pieces1);
    char color;
    if (col == 'W') {
        color = 'B';
    } else {
        color = 'W';
    }
    for (int i = 0; i < 32; i++) {
        if (pieces1[i]->color == color) {
            for (int j = 0; j < pieces1[i]->moveableTiles.size(); j++) {
                if (board1[pieces1[i]->moveableTiles[j].a[0]][pieces1[i]->moveableTiles[j].a[1]] != "") {
                    pieces1[i]->move(pieces1[i]->moveableTiles[j].a[0], pieces1[i]->moveableTiles[j].a[1], board1, pieces1);
                    update(lastMove, board1, pieces1);
                    if (!badCheck(board1, pieces1, color)) {
                        copyBoard(board, board1, pieces, pieces1);
                        update(lastMove, board1, pieces1);
                        return false;
                    }
                    copyBoard(board, board1, pieces, pieces1);
                    update(lastMove, board1, pieces1);
                } else {
                    pieces1[i]->move(pieces1[i]->moveableTiles[j].a[0], pieces1[i]->moveableTiles[j].a[1], board1, pieces1);
                    update(lastMove, board1, pieces1);
                    if (!badCheck(board1, pieces1, color)) {
                        copyBoard(board, board1, pieces, pieces1);
                        update(lastMove, board1, pieces1);
                        return false;
                    }
                    copyBoard(board, board1, pieces, pieces1);
                    update(lastMove, board1, pieces1);
                }
            }

        }
    }
    return true;
}

bool checkmate(string lastMove, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    int king, x, y;
    if (col == 'W') {
        king = 15;
    } else {
        king = 14;
    }
    if (pieces[king]->attackers.size() == 2) { // double check
        if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) { // Check for valid king moves or captures
            return false;
        } else { // Checkmate
            return true;
        } 
    } else { // regular check
        if (pieces[king]->attackers[0]->pieceType == 'P') { // Pawn attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                return false;
            }
            if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                return false;
            }
            return true;
        } else if (pieces[king]->attackers[0]->pieceType == 'R') { // Rook attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (x == pieces[king]->posx) { // Rook is on same rank
                if (y < pieces[king]->posy) { // Rook is in 'a' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Rook is in 'h' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else { // Rook is on same file
                if (x < pieces[king]->posx) { // Rook is in '1' direction of king
                    while (x < pieces[king]->posx) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Rook is in '8' direction of king
                    while (x > pieces[king]->posx) { 
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            }
        } else if (pieces[king]->attackers[0]->pieceType == 'N') { // Knight attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                return false;
            }
            if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                return false;
            }
            return true;
        } else if (pieces[king]->attackers[0]->pieceType == 'B') { // Bishop attacker
            x = pieces[king]->attackers[0]->posx;
            y = pieces[king]->attackers[0]->posy;
            if (x > pieces[king]->posx) {
                if (y > pieces[king]->posy) { // Bishop is in 'h8' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Bishop is in 'a8' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else { 
                if (y < pieces[king]->posy) { // Bishop is in 'a1' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Bishop is in 'h1' direction of king
                    while (y > pieces[king]->posx) { 
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
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
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in 'h' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        y--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else if (y == pieces[king]->posy) { // Queen is on same file
                if (x < pieces[king]->posx) { // Queen is in '1' direction of king
                    while (x < pieces[king]->posx) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in '8' direction of king
                    while (x > pieces[king]->posx) { 
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else if (x > pieces[king]->posx) {
                if (y > pieces[king]->posy) { // Queen is in 'h8' direction of king
                    while (y > pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in 'a8' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x--;
                        y++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            } else { 
                if (y < pieces[king]->posy) { // Queen is in 'a1' direction of king
                    while (y < pieces[king]->posy) {
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y++;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                } else { // Queen is in 'h1' direction of king
                    while (y > pieces[king]->posx) { 
                        if (checkForBlock(lastMove, x, y, board, board1, pieces, pieces1, col)) { // Piece can block, not checkmate
                            return false;
                        }
                        x++;
                        y--;
                    }
                    if (checkValidKingMove(lastMove, king, board, board1, pieces, pieces1, col)) {
                        return false;
                    }
                    return true;
                }
            }
        }
    }
}

bool checkForBlock(string lastMove, int x, int y, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    vector<Piece*> temp;
    for (int i = 0; i < 32; i++) {
        if (pieces1[i]->color != col) {
            if (i == 14 || i == 15) {
                continue;
            } else if (pieces1[i]->pieceType == 'P') {
                temp.push_back(pieces1[i]);
            } else {
                for (int j = 0; j < pieces1[i]->coveredTiles.size(); j++) {
                    if (pieces1[i]->coveredTiles[j].a[0] == x && pieces1[i]->coveredTiles[j].a[1] == y) {
                        pieces1[i]->move(x,y, board1, pieces1);
                        update(lastMove, board1, pieces1);
                        if (!badCheck(board1, pieces1, pieces[i]->color)) {
                            copyBoard(board, board1, pieces, pieces1);
                            return true;
                        }
                        copyBoard(board, board1, pieces, pieces1);
                    }
                }
            }
        } 
    }
    for (int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp[i]->moveableTiles.size(); j++) {
            if (temp[i]->moveableTiles[j].a[0] == x && temp[i]->moveableTiles[j].a[1] == y) {
                temp[i]->move(x,y, board1, pieces1);
                update(lastMove, board1, pieces1);
                if (!badCheck(board1, pieces1, pieces[i]->color)) {
                    copyBoard(board, board1, pieces, pieces1);
                    return true;
                }
                copyBoard(board, board1, pieces, pieces1);
            }
        }
    }
    return false;
}

bool checkValidKingMove(string lastMove, int king, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    for (int i = pieces1[king]->posx-1; i <= pieces1[king]->posx+1; i++) {
        for (int j = pieces1[king]->posy-1; j <= pieces1[king]->posy+1; j++) {
            if (i == pieces1[king]->posx && j == pieces1[king]->posy) {
                continue;
            } else {
                if (i >=0 && i <= 7 && j >=0 && j <= 7) {
                    if (board1[i][j] != "") {
                        if (board1[i][j][0] != pieces1[king]->color) {
                            pieces1[king]->move(i, j, board1, pieces1);
                            update(lastMove, board1, pieces1);
                            if (!badCheck(board1, pieces1, pieces1[king]->color)) {
                                copyBoard(board, board1, pieces, pieces1);
                                return true;
                            }
                            copyBoard(board, board1, pieces, pieces1);
                        }
                    } else {
                        pieces1[king]->move(i, j, board1, pieces1);
                        update(lastMove, board1, pieces1);
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

string generateMove(string lastMove, string move, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
    vector<string> possMoves, shuffle0, shuffle1, shuffle2, shuffle3;
    vector<int> pieceIndex, iShuffle0, iShuffle1, iShuffle2, iShuffle3;
    string possMove;
    if (col == 'W') {
        if (piecesPoss[19]->posx != 8) {
            addMoves(possMove, 19, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[20]->posx != 8) {
            addMoves(possMove, 20, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[4]->posx != 8) {
            addMoves(possMove, 4, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[5]->posx != 8) {
            addMoves(possMove, 5, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[8]->posx != 8) {
            addMoves(possMove, 8, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[9]->posx != 8) {
            addMoves(possMove, 9, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[12]->posx != 8) {
            addMoves(possMove, 12, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[16]->posx != 8) {
            addMoves(possMove, 16, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[17]->posx != 8) {
            addMoves(possMove, 17, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[18]->posx != 8) {
            addMoves(possMove, 18, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[21]->posx != 8) {
            addMoves(possMove, 21, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[22]->posx != 8) {
            addMoves(possMove, 22, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[23]->posx != 8) {
            addMoves(possMove, 23, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[0]->posx != 8) {
            addMoves(possMove, 0, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[1]->posx != 8) {
            addMoves(possMove, 1, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[14]->posx != 8) {
            addMoves(possMove, 14, piecesPoss, pieceIndex, possMoves);
        }
    } else {
        if (piecesPoss[27]->posx != 8) {
            addMoves(possMove, 27, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[28]->posx != 8) {
            addMoves(possMove, 28, piecesPoss, pieceIndex, possMoves);
        }  
        if (piecesPoss[6]->posx != 8) {
            addMoves(possMove, 6, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[7]->posx != 8) {
            addMoves(possMove, 7, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[10]->posx != 8) {
            addMoves(possMove, 10, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[11]->posx != 8) {
            addMoves(possMove, 11, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[13]->posx != 8) {
            addMoves(possMove, 13, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[24]->posx != 8) {
            addMoves(possMove, 24, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[25]->posx != 8) {
            addMoves(possMove, 25, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[26]->posx != 8) {
            addMoves(possMove, 26, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[29]->posx != 8) {
            addMoves(possMove, 29, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[30]->posx != 8) {
            addMoves(possMove, 30, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[31]->posx != 8) {
            addMoves(possMove, 31, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[2]->posx != 8) {
            addMoves(possMove, 2, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[3]->posx != 8) {
            addMoves(possMove, 3, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[15]->posx != 8) {
            addMoves(possMove, 15, piecesPoss, pieceIndex, possMoves);
        }
    }

    for (int i = 0; i < possMoves.size(); i++) {
        int x, y;
        Piece* temp;
        if (possMoves[i].size() == 3) {
            x = charToNum(possMoves[i][2]), y = letterToNum(possMoves[i][1]);
        } else {
            x = charToNum(possMoves[i][1]), y = letterToNum(possMoves[i][0]);
        }
        if (boardPoss[x][y] != "") {
            temp = findPiece(x, y, boardPoss, piecesPoss, boardPoss[x][y][0]);
            if (temp->defenders.size() == 0) {
                shuffle0.push_back(possMoves[i]);
                iShuffle0.push_back(pieceIndex[i]);
                continue;
            } else if (temp->attackers.size() > temp->defenders.size()) {
                int dValue = temp->value, aValue = 0;
                if (dValue <= piecesPoss[pieceIndex[i]]->value) {
                    shuffle3.push_back(possMoves[i]);
                    iShuffle3.push_back(pieceIndex[i]);
                    continue;
                }
                for (int j = 0; j < temp->attackers.size(); j++) {
                    aValue += temp->attackers[j]->value;
                }
                for (int j = 0; j < temp->defenders.size(); j++) {
                    dValue += temp->defenders[j]->value;
                }
                if (dValue > aValue) {
                    shuffle0.push_back(possMoves[i]);
                    iShuffle0.push_back(pieceIndex[i]);
                    continue;
                }
            }
        } else {
            piecesPoss2[pieceIndex[i]]->move(x, y, boardPoss2, piecesPoss2);
            // cout << piecesPoss2[pieceIndex[i]]->pieceType << numToLetter(y) << numToChar(x) << "\n";
            update(lastMove, boardPoss2, piecesPoss2);
            if (piecesPoss2[pieceIndex[i]]->attackers.size() > piecesPoss2[pieceIndex[i]]->defenders.size()) {
                int dValue = piecesPoss2[pieceIndex[i]]->value, aValue = 0;
                for (int j = 0; j < piecesPoss2[pieceIndex[i]]->attackers.size(); j++) {
                    aValue = piecesPoss2[pieceIndex[i]]->attackers[j]->value;
                }
                for (int j = 0; j < piecesPoss2[pieceIndex[i]]->defenders.size(); j++) {
                    dValue = piecesPoss2[pieceIndex[i]]->attackers[j]->value;
                }
                if (aValue <= dValue) {
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    shuffle2.push_back(possMoves[i]);
                    iShuffle2.push_back(pieceIndex[i]);
                    continue;
                }
            } else if (piecesPoss2[pieceIndex[i]]->coveredTiles.size() > piecesPoss[pieceIndex[i]]->coveredTiles.size()) {
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                shuffle1.push_back(possMoves[i]);
                iShuffle1.push_back(pieceIndex[i]);
                continue;
            }
            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
            update(lastMove, boardPoss2, piecesPoss2);
        } 
        if (piecesPoss[pieceIndex[i]]->timesMoved == 0) {
            if (i == possMoves.size()-1) {
                shuffle3.push_back(possMoves[i]);
                iShuffle3.push_back(pieceIndex[i]);
            }
            shuffle1.push_back(possMoves[i]);
            iShuffle1.push_back(pieceIndex[i]);
        } else if (piecesPoss[pieceIndex[i]]->timesMoved == 1) {
            if (i == possMoves.size()-1) {
                shuffle3.push_back(possMoves[i]);
                iShuffle3.push_back(pieceIndex[i]);
            }
            shuffle2.push_back(possMoves[i]);
            iShuffle2.push_back(pieceIndex[i]);
        } else {
            shuffle3.push_back(possMoves[i]);
            iShuffle3.push_back(pieceIndex[i]);
        }
    }
    possMoves.clear();
    pieceIndex.clear();
    for (int i = 0; i < shuffle0.size(); i++) {
        possMoves.push_back(shuffle0[i]);
        pieceIndex.push_back(iShuffle0[i]);
    }
    for (int i = 0; i < shuffle1.size(); i++) {
        possMoves.push_back(shuffle1[i]);
        pieceIndex.push_back(iShuffle1[i]);
    }
    for (int i = 0; i < shuffle2.size(); i++) {
        possMoves.push_back(shuffle2[i]);
        pieceIndex.push_back(iShuffle2[i]);
    }
    for (int i = 0; i < shuffle3.size(); i++) {
        possMoves.push_back(shuffle3[i]);
        pieceIndex.push_back(iShuffle3[i]);
    }
    cout << "Move ranking:\n";
    for (int i = 0; i < possMoves.size(); i++) {
        cout << "\t" << i << ". " << possMoves[i] << endl;
    }

    for (int i = 0; i < possMoves.size(); i++) {
        // cout << "Trying move " << possMoves[i] << " #" << i+1 << " of " << possMoves.size() << endl;
        if (possMoves[i][0] != 'P') { // Check if not pawn piece
            possMove = possMoves[i][0];
        } else {
            possMove = "";
        }
        for (int j = i+1; j < possMoves.size(); j++) { // Check for ambiguity
            if (possMoves[i][0] == possMoves[j][0] && possMoves[i][1] == possMoves[j][1] && possMoves[i][2] == possMoves[j][2]) {
                if (piecesPoss[pieceIndex[i]]->posy != piecesPoss[pieceIndex[j]]->posy) { // Add Specification
                    possMove += numToLetter(piecesPoss[pieceIndex[i]]->posy);
                    for (int k = j+1; k < possMoves.size(); k++) { // Check for more ambiguity
                        if (possMoves[i][0] == possMoves[k][0] && possMoves[i][1] == possMoves[k][1] && possMoves[i][2] == possMoves[k][2]) {
                            if (piecesPoss[pieceIndex[i]]->posy != piecesPoss[pieceIndex[j]]->posy) { // Add Specification
                                continue;
                            } else if (piecesPoss[pieceIndex[i]]->posx != piecesPoss[pieceIndex[j]]->posx) {
                                possMove += numToChar(piecesPoss[pieceIndex[i]]->posx);
                                break;
                            }
                        }
                    }
                } else if (piecesPoss[pieceIndex[i]]->posx != piecesPoss[pieceIndex[j]]->posx) {
                    possMove += numToChar(piecesPoss[pieceIndex[i]]->posx);
                    for (int k = j+1; k < possMoves.size(); k++) { // Check for more ambiguity
                        if (possMoves[i][0] == possMoves[k][0] && possMoves[i][1] == possMoves[k][1] && possMoves[i][2] == possMoves[k][2]) {
                            if (piecesPoss[pieceIndex[i]]->posy != piecesPoss[pieceIndex[j]]->posy) { // Add Specification
                                possMove = possMove.substr(0, possMove.size()-1);
                                possMove += numToLetter(piecesPoss[pieceIndex[i]]->posy);
                                possMove += numToChar(piecesPoss[pieceIndex[i]]->posx);
                                break;
                            } else if (piecesPoss[pieceIndex[i]]->posx != piecesPoss[pieceIndex[j]]->posx) {
                                continue;
                            }
                        }
                    }
                }
            }
        }
        if (boardPoss[charToNum(possMoves[i][2])][letterToNum(possMoves[i][1])] != "") { // Check if Capture
            if (possMove == "") {
                possMove += numToLetter(piecesPoss[pieceIndex[i]]->posy);
            }
            possMove += 'x'; // Add capture notation
        }
        possMove += possMoves[i][1]; // Add y position
        possMove += possMoves[i][2]; // Add x position
        bool prom = false;
        if (col == 'W' && piecesPoss[pieceIndex[i]]->pieceType == 'P' && possMoves[i][2] == '8') {
            promote(col, 'Q', pieceIndex[i], boardPoss, piecesPoss);
            update(lastMove, boardPoss, piecesPoss);
            possMove += 'Q';
            prom = true;
        } else if (col == 'B' && piecesPoss[pieceIndex[i]]->pieceType == 'P' && possMoves[i][2] == '1') {
            promote(col, 'Q', pieceIndex[i], boardPoss, piecesPoss);
            update(lastMove, boardPoss, piecesPoss);
            possMove += 'Q';
            prom = true;
        }
        piecesPoss[pieceIndex[i]]->move(charToNum(possMoves[i][2]), letterToNum(possMoves[i][1]), boardPoss, piecesPoss);
        update(lastMove, boardPoss, piecesPoss);
        if (badCheck(boardPoss, piecesPoss, col)) { // Validate move doesn't put yourself in check
            if (prom) {
                promote(col, 'P', pieceIndex[i], boardPoss, piecesPoss);   
            }
            copyBoard(board, boardPoss, pieces, piecesPoss);
            update(lastMove, boardPoss, piecesPoss);
            continue; // Try next move possibility
        } else if (check(boardPoss, piecesPoss, col)) { // Check if Check
            if (prom) {
                promote(col, 'Q', pieceIndex[i], boardPoss2, piecesPoss2);   
            }
            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
            update(lastMove, boardPoss2, piecesPoss2);
            if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) { // Check if Checkmate
                gameOver = true;
                possMove += '#';
            } else {
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                possMove += '+';
            }
        } else if (stalemate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) { // Check if stalemate
            if (prom) {
                promote(col, 'P', pieceIndex[i], boardPoss, piecesPoss);   
            }
            copyBoard(board, boardPoss, pieces, piecesPoss);
            update(lastMove, boardPoss, piecesPoss);
            continue; // Try next move possibility
        }
        if (prom) {
            promote(col, 'Q', pieceIndex[i], board, pieces);
            if (piecesPoss2[pieceIndex[i]]->pieceType != 'Q') {
                promote(col, 'Q', pieceIndex[i], boardPoss2, piecesPoss2);
            }
        }
        copyBoard(boardPoss, board, piecesPoss, pieces);
        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
        update(lastMove, board, pieces);
        update(lastMove, boardPoss2, piecesPoss2);
        return possMove;
    }
    gameOver = true;
    return "Stalemate";
}

