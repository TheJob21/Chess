#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <time.h>
#include <string>
#include <vector>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
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

char blackOrWhite(char);
char computerOrHuman(char);
bool check(string (*)[8], Piece**, char);
bool stalemate(string, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkmate(string, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkForBlock(string, int, int, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool checkValidKingMove(string, int, string (*)[8], string (*)[8], Piece**, Piece**, char);
bool validateMove(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
bool validatePawnMove(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
bool castle(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
string generateMove(ostream &, string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece** , char, bool &);
bool canCastle(string, string, string (*)[8], string (*)[8], string (*)[8], Piece**, Piece**, Piece**, char, bool &);

int main()
{
    srand(time(0));
    ofstream filestream("GameRecord.out");
    bool gameOver = false, isValid;
    char col, coh;
    string move, lastMove = "";
    string moves[5949][2];
    int moveCount = 1;
    double _50MoveLimit = 0;
    string (*board)[8] = new string[8][8]; 
    string (*boardPoss)[8] = new string[8][8]; 
    string (*boardPoss2)[8] = new string[8][8]; 
    string (*prevBoard)[8] = new string[8][8]; 
    Piece **pieces = new Piece*[32];
    Piece **piecesPoss = new Piece*[32];
    Piece **piecesPoss2 = new Piece*[32];
    Piece **prevPieces = new Piece*[32];
    vector<vector<Int2>> everyPos;
    setBoard(board, pieces);
    update(lastMove, board, pieces);
    setBoard(boardPoss, piecesPoss);
    update(lastMove, boardPoss, piecesPoss);
    setBoard(boardPoss2, piecesPoss2);
    update(lastMove, boardPoss2, piecesPoss2);
    setBoard(prevBoard, prevPieces);
    copyPos(everyPos, pieces);
    coh = computerOrHuman(coh);
    if (coh == 'c') {
        col = blackOrWhite(col);
    }

    // Game Loop
    if (coh == 'c') {
        if (col == 'w') {
            while (!gameOver) {
                // Human Turn
                filestream << endl;
                cout << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board, cout);
                printBoard(board, filestream);
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
                filestream << endl;
                cout << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board, cout);
                printBoard(board, filestream);
                moves[moveCount-1][0] = lastMove = move;
                update(lastMove, board, pieces);
                update(lastMove, boardPoss, piecesPoss);
                update(lastMove, boardPoss2, piecesPoss2);
                filestream << moveCount << ". " << lastMove << endl;
                cout << moveCount << ". " << lastMove << endl;
                _50MoveLimit += 0.5;
                if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                    _50MoveLimit += 0.5;
                } else {
                    _50MoveLimit = 0;
                }
                if (_50MoveLimit >= 50) {
                    gameOver = true;
                    filestream << "50 move limit reached. Stalemate!\n";
                    cout << "50 move limit reached. Stalemate!\n";
                }
                copyPos(everyPos, pieces);
                check3Reps(everyPos, gameOver, filestream);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    cout << moveCount << ". " << lastMove << endl;
                    filestream << moveCount << ". " << lastMove << endl;
                    printBoard(board, cout);
                    printBoard(board, filestream);
                    break;
                }
                bool isValid = false;
                // Computer Turn
                moves[moveCount-1][1] = lastMove = move = generateMove(filestream, lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver);
                moveCount++;
                _50MoveLimit += 0.5;
                if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                    _50MoveLimit += 0.5;
                } else {
                    _50MoveLimit = 0;
                }
                if (_50MoveLimit >= 50) {
                    gameOver = true;
                    filestream << "50 move limit reached. Stalemate!\n";
                    cout << "50 move limit reached. Stalemate!\n";
                }
                copyPos(everyPos, pieces);
                check3Reps(everyPos, gameOver, filestream);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    cout << moveCount << ". " << lastMove << endl;
                    filestream << moveCount << ". " << lastMove << endl;
                    printBoard(board, cout);
                    printBoard(board, filestream);
                }
            }
        } else if (col == 'b') {
            while (!gameOver) {
                // Computer Turn
                printBoard(board, cout);
                printBoard(board, filestream);
                cout << endl;
                filestream << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                moves[moveCount-1][0] = lastMove = move = generateMove(filestream, lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver);
                _50MoveLimit += 0.5;
                if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                    _50MoveLimit += 0.5;
                } else {
                    _50MoveLimit = 0;
                }
                if (_50MoveLimit >= 50) {
                    gameOver = true;
                    filestream << "50 move limit reached. Stalemate!\n";
                    cout << "50 move limit reached. Stalemate!\n";
                }
                copyPos(everyPos, pieces);
                check3Reps(everyPos, gameOver, filestream);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    for (int i = 0; i < moveCount-1; i++) {
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    cout << moveCount << ". " << lastMove << endl;
                    filestream << moveCount << ". " << lastMove << endl;
                    printBoard(board, cout);
                    printBoard(board, filestream);
                    break;
                }
                // Human Turn
                cout << endl;
                filestream << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board, cout);
                printBoard(board, filestream);
                cout << moveCount << ". " << lastMove << ", ";
                filestream << moveCount << ". " << lastMove << ", ";
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
                update(lastMove, board, pieces);
                update(lastMove, boardPoss, piecesPoss);
                update(lastMove, boardPoss2, piecesPoss2);
                _50MoveLimit += 0.5;
                if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                    _50MoveLimit += 0.5;
                } else {
                    _50MoveLimit = 0;
                }
                if (_50MoveLimit >= 50) {
                    gameOver = true;
                    filestream << "50 move limit reached. Stalemate!\n";
                    cout << "50 move limit reached. Stalemate!\n";
                }
                copyPos(everyPos, pieces);
                check3Reps(everyPos, gameOver, filestream);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    printBoard(board, cout);
                    printBoard(board, filestream);
                }
                bool isValid = false;
                moveCount++;
            }
        } else { // computer vs computer
            while (!gameOver) {
                filestream << endl;
                for (int i = 0; i < moveCount-1; i++) {
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board, cout);
                printBoard(board, filestream);
                // cout << "Press enter to continue.";
                // getline(cin, move);
                moves[moveCount-1][0] = lastMove = move = generateMove(filestream, lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'W', gameOver);
                update(lastMove, board, pieces);
                update(lastMove, boardPoss, piecesPoss);
                update(lastMove, boardPoss2, piecesPoss2);
                _50MoveLimit += 0.5;
                if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                    _50MoveLimit += 0.5;
                } else {
                    _50MoveLimit = 0;
                }
                if (_50MoveLimit >= 50) {
                    gameOver = true;
                    filestream << "50 move limit reached. Stalemate!\n";
                    cout << "50 move limit reached. Stalemate!\n";
                }
                copyPos(everyPos, pieces);
                check3Reps(everyPos, gameOver, filestream);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    filestream << moveCount << ". " << lastMove << endl;
                    for (int i = 0; i < moveCount-1; i++) {
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    cout << moveCount << ". " << lastMove << endl;
                    printBoard(board, cout);
                    printBoard(board, filestream);
                    break;
                }
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                filestream << moveCount << ". " << lastMove << endl;
                cout << moveCount << ". " << lastMove << endl;
                printBoard(board, cout);
                printBoard(board, filestream);
                // cout << "Press enter to continue.";
                // getline(cin, move);
                moves[moveCount-1][1] = lastMove = move = generateMove(filestream, lastMove, move, board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, 'B', gameOver);
                update(lastMove, board, pieces);
                update(lastMove, boardPoss, piecesPoss);
                update(lastMove, boardPoss2, piecesPoss2);
                moveCount++;
                if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                    _50MoveLimit += 0.5;
                } else {
                    _50MoveLimit = 0;
                }
                if (_50MoveLimit >= 50) {
                    gameOver = true;
                    filestream << "50 move limit reached. Stalemate!\n";
                    cout << "50 move limit reached. Stalemate!\n";
                }
                copyPos(everyPos, pieces);
                check3Reps(everyPos, gameOver, filestream);
                if (gameOver) {
                    for (int i = 0; i < moveCount-1; i++) {
                        filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    for (int i = 0; i < moveCount-1; i++) {
                        cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                    }
                    printBoard(board, cout);
                    printBoard(board, filestream);
                }
            }
        }
    } else { // human vs human
        while (!gameOver) {
            cout << endl;
            for (int i = 0; i < moveCount-1; i++) {
                cout << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
            }
            printBoard(board, cout);
            printBoard(board, filestream);
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
            printBoard(board, cout);
            printBoard(board, filestream);
            moves[moveCount-1][0] = lastMove = move;
            _50MoveLimit += 0.5;
            if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                _50MoveLimit += 0.5;
            } else {
                _50MoveLimit = 0;
            }
            if (_50MoveLimit >= 50) {
                gameOver = true;
                filestream << "50 move limit reached. Stalemate!\n";
                cout << "50 move limit reached. Stalemate!\n";
            }
            copyPos(everyPos, pieces);
            check3Reps(everyPos, gameOver, filestream);
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
            _50MoveLimit += 0.5;
            if ((move[0] == 'R' || move[0] == 'N' || move[0] == 'B' || move[0] == 'Q' || move[0] == 'K' || move[0] == '0') && move.find('x') != string::npos) {
                _50MoveLimit += 0.5;
            } else {
                _50MoveLimit = 0;
            }
            if (_50MoveLimit >= 50) {
                gameOver = true;
                filestream << "50 move limit reached. Stalemate!\n";
                cout << "50 move limit reached. Stalemate!\n";
            }
            copyPos(everyPos, pieces);
            check3Reps(everyPos, gameOver, filestream);
            if (gameOver) {
                for (int i = 0; i < moveCount-1; i++) {
                    filestream << i+1 << ". " << moves[i][0] << ", " << moves[i][1] << endl;
                }
                printBoard(board, cout);
                printBoard(board, filestream);
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
                                    Piece* temp = findPiece(piecesPoss[p[j]]->posx, y, boardPoss, piecesPoss, boardPoss[piecesPoss[p[j]]->posx][y][0]);
                                    temp->posx = 8; temp->posy = 8;
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
                                        Piece* temp = findPiece(piecesPoss[p[j]]->posx, y, boardPoss, piecesPoss, boardPoss[piecesPoss[p[j]]->posx][y][0]);
                                        temp->posx = 8; temp->posy = 8;
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
                while (y > pieces[king]->posy) { 
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
                while (y > pieces[king]->posy) { 
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

bool checkForBlock(string lastMove, int x, int y, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    for (int i = 0; i < 32; i++) {
        if (pieces1[i]->color != col) {
            if (i == 14 || i == 15) {
                continue;
            } else {
                for (int j = 0; j < pieces1[i]->moveableTiles.size(); j++) {
                    if (pieces1[i]->moveableTiles[j].a[0] == x && pieces1[i]->moveableTiles[j].a[1] == y) {
                        pieces1[i]->move(x, y, board1, pieces1);
                        update(lastMove, board1, pieces1);
                        if (!badCheck(board1, pieces1, pieces1[i]->color)) {
                            copyBoard(board, board1, pieces, pieces1);
                            update(lastMove, board1, pieces1);
                            return true;
                        }
                        copyBoard(board, board1, pieces, pieces1);
                        update(lastMove, board1, pieces1);
                    }
                }
            }
        } 
    }
    return false;
}

bool checkValidKingMove(string lastMove, int king, string (*board)[8], string (*board1)[8], Piece** pieces, Piece** pieces1, char col) {
    for (int i = 0 ; i < pieces1[king]->moveableTiles.size(); i++) {
        pieces1[king]->move(pieces1[king]->moveableTiles[i].a[0], pieces1[king]->moveableTiles[i].a[1], board1, pieces1);
        update(lastMove, board1, pieces1);
        if (!badCheck(board1, pieces1, pieces1[king]->color)) {
            copyBoard(board, board1, pieces, pieces1);
            return true;
        }
        copyBoard(board, board1, pieces, pieces1);
    }
    return false;
}

string generateMove(ostream &fstream, string lastMove, string move, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
    vector<string> possMoves, priority0, priority1, priority2, priority3, priority4, priority5, priority6, priority7, priority8, priority9, priority10, priority11, priority12, priority13, priority14, priority15, priority16, priority17;
    vector<int> myPcsI, pieceIndex, ipriority0, ipriority1, ipriority2, ipriority3, ipriority4, ipriority5, ipriority6, ipriority7, ipriority8, ipriority9, ipriority10, ipriority11, ipriority12, ipriority13, ipriority14, ipriority15, ipriority16, ipriority17;
    string possMove;
    if (col == 'W') {
        if (piecesPoss[0]->posx != 8) {
            myPcsI.push_back(0);
            addMoves(possMove, 0, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[1]->posx != 8) {
            myPcsI.push_back(1);
            addMoves(possMove, 1, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[4]->posx != 8) {
            myPcsI.push_back(4);
            addMoves(possMove, 4, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[5]->posx != 8) {
            myPcsI.push_back(5);
            addMoves(possMove, 5, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[8]->posx != 8) {
            myPcsI.push_back(8);
            addMoves(possMove, 8, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[9]->posx != 8) {
            myPcsI.push_back(9);
            addMoves(possMove, 9, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[12]->posx != 8) {
            myPcsI.push_back(12);
            addMoves(possMove, 12, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[14]->posx != 8) {
            myPcsI.push_back(14);
            addMoves(possMove, 14, piecesPoss, pieceIndex, possMoves);
        }
        for (int i = 16; i < 24; i++) {
            if (piecesPoss[i]->posx != 8) {
                myPcsI.push_back(i);
                addMoves(possMove, i, piecesPoss, pieceIndex, possMoves);
            }
        }
    } else {
        if (piecesPoss[2]->posx != 8) {
            myPcsI.push_back(2);
            addMoves(possMove, 2, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[3]->posx != 8) {
            myPcsI.push_back(3);
            addMoves(possMove, 3, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[6]->posx != 8) {
            myPcsI.push_back(6);
            addMoves(possMove, 6, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[7]->posx != 8) {
            myPcsI.push_back(7);
            addMoves(possMove, 7, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[10]->posx != 8) {
            myPcsI.push_back(10);
            addMoves(possMove, 10, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[11]->posx != 8) {
            myPcsI.push_back(11);
            addMoves(possMove, 11, piecesPoss, pieceIndex, possMoves);
        }
        if (piecesPoss[13]->posx != 8) {
            myPcsI.push_back(13);
            addMoves(possMove, 13, piecesPoss, pieceIndex, possMoves);
        } 
        if (piecesPoss[15]->posx != 8) {
            myPcsI.push_back(15);
            addMoves(possMove, 15, piecesPoss, pieceIndex, possMoves);
        }
        for (int i = 24; i < 32; i++) {
            if (piecesPoss[i]->posx != 8) {
                myPcsI.push_back(i);
                addMoves(possMove, i, piecesPoss, pieceIndex, possMoves);
            }
        }
    }
    if (canCastle(lastMove, "0-0-0", board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, col, gameOver)) {
        possMoves.push_back("0-0-0");
        pieceIndex.push_back(33);
    } else if (canCastle(lastMove, "0-0", board, boardPoss, boardPoss2, pieces, piecesPoss, piecesPoss2, col, gameOver)) {
        possMoves.push_back("0-0");
        pieceIndex.push_back(33);
    }

    srand(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
    int r = rand(), king;
    // Prioritize moves
    fstream << "Total Possible Moves: " << possMoves.size() << endl;
    cout << "Total Possible Moves: " << possMoves.size() << endl;
    for (int index = 0; index < possMoves.size(); index++) {
        int x, y, i = (index + r) % possMoves.size();
        bool assigned = false, enPassant = false;
        fstream << "\t" << index+1 << " " << possMoves[i] << ": ";
        cout << "\t" << index+1 << " " << possMoves[i] << ": ";
        Piece* temp;
        if (possMoves[i][0] == '0') {
            fstream << "That's a good trick, priority 13\n";
            cout << "That's a good trick, priority 13\n";
            priority13.push_back(possMoves[i]);
            ipriority13.push_back(pieceIndex[i]);
            continue;
        } else if (possMoves[i].size() == 3) {
            x = charToNum(possMoves[i][2]), y = letterToNum(possMoves[i][1]);
        } else {
            x = charToNum(possMoves[i][1]), y = letterToNum(possMoves[i][0]);
        }
        piecesPoss[pieceIndex[i]]->move(x, y, boardPoss, piecesPoss); // Try out the move
        update(lastMove, boardPoss, piecesPoss);
        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
        update(lastMove, boardPoss2, piecesPoss2);
        if (col == 'W') {
            king = 14;
            if (piecesPoss2[king]->inCheck) {
                copyBoard(board, boardPoss, pieces, piecesPoss);
                update(lastMove, boardPoss, piecesPoss);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                cout << "Places yourself in check, illegal\n";
                fstream << "Places yourself in check, illegal\n";
                continue;
            } else if (piecesPoss2[15]->inCheck) {
                if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                    fstream << "Places opponent in checkmate, priority 0\n";
                    cout << "Places opponent in checkmate, priority 0\n";
                    copyBoard(board, boardPoss, pieces, piecesPoss);
                    update(lastMove, boardPoss, piecesPoss);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority0.push_back(possMoves[i]);
                    ipriority0.push_back(pieceIndex[i]);
                    continue;
                }
            }
        } else if (col == 'B') {
            king = 15;
            if (piecesPoss2[king]->inCheck) {
                copyBoard(board, boardPoss, pieces, piecesPoss);
                update(lastMove, boardPoss, piecesPoss);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                cout << "Places yourself in check, illegal\n";
                fstream << "Places yourself in check, illegal\n";
                continue;
            } else if (piecesPoss2[14]->inCheck) {
                if (checkmate(lastMove, boardPoss, boardPoss2, piecesPoss, piecesPoss2, col)) {
                    fstream << "Places opponent in checkmate, priority 0\n";
                    cout << "Places opponent in checkmate, priority 0\n";
                    copyBoard(board, boardPoss, pieces, piecesPoss);
                    update(lastMove, boardPoss, piecesPoss);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority0.push_back(possMoves[i]);
                    ipriority0.push_back(pieceIndex[i]);
                    continue;
                }
            } 
        }
        copyBoard(board, boardPoss, pieces, piecesPoss);
        update(lastMove, boardPoss, piecesPoss);
        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
        update(lastMove, boardPoss2, piecesPoss2);
        piecesPoss2[pieceIndex[i]]->move(x, y, boardPoss2, piecesPoss2); // Try out the move
        update(lastMove, boardPoss2, piecesPoss2);
        int inDangerBefore = 0, inDangerAfter = 0;
        for (int j = 0; j < myPcsI.size(); j++) {
            if (piecesPoss[myPcsI[j]]->attackers.size() > 0 && piecesPoss[myPcsI[j]]->defenders.size() == 0) {
                inDangerBefore += piecesPoss[myPcsI[j]]->value;
            } else if (piecesPoss[myPcsI[j]]->attackers.size() > piecesPoss[myPcsI[j]]->defenders.size()) {
                int dValue = piecesPoss[myPcsI[j]]->value, aValue = 0, mostVal = 0;
                bool accounted = false;
                for (int k = 0; k < piecesPoss[myPcsI[j]]->attackers.size(); k++) {
                    if (piecesPoss[myPcsI[j]]->attackers[k]->value < dValue) {
                        inDangerBefore += dValue;
                        accounted = true;
                        break;
                    } else {
                        aValue += piecesPoss[myPcsI[j]]->attackers[k]->value;
                        if (piecesPoss[myPcsI[j]]->attackers[k]->value > mostVal) {
                            mostVal = piecesPoss[myPcsI[j]]->attackers[k]->value;
                        }
                    }
                }
                if (accounted) {
                    continue;
                }
                for (int k = 0; k < piecesPoss[myPcsI[j]]->defenders.size(); k++) {
                    dValue += piecesPoss[myPcsI[j]]->defenders[k]->value;
                }
                aValue -= mostVal;
                if (dValue > aValue) {
                    inDangerBefore += piecesPoss[myPcsI[j]]->value;
                }
            } else if (piecesPoss[myPcsI[j]]->attackers.size() > 0 && piecesPoss[myPcsI[j]]->attackers.size() == piecesPoss[myPcsI[j]]->defenders.size()) { // Equal defenders to attackers
                int dValue = piecesPoss[myPcsI[j]]->value, aValue = 0, mostVal = 0;
                bool accounted = false;
                for (int k = 0; k < piecesPoss[myPcsI[j]]->attackers.size(); k++) {
                    if (piecesPoss[myPcsI[j]]->attackers[k]->value < dValue) {
                        inDangerBefore += dValue-piecesPoss[myPcsI[j]]->attackers[k]->value;
                        accounted = true;
                        break;
                    } else {
                        aValue += piecesPoss[myPcsI[j]]->attackers[k]->value;
                    }
                }
                if (accounted) {
                    continue;
                }
                for (int k = 0; k < piecesPoss[myPcsI[j]]->defenders.size(); k++) {
                    dValue += piecesPoss[myPcsI[j]]->defenders[k]->value;
                    if (piecesPoss[myPcsI[j]]->defenders[k]->value > mostVal) {
                        mostVal = piecesPoss[myPcsI[j]]->defenders[k]->value;
                    }
                }
                dValue -= mostVal;
                if (dValue > aValue) {
                    inDangerBefore += dValue-aValue;
                }
            } else if (piecesPoss[myPcsI[j]]->attackers.size() > 0 && piecesPoss[myPcsI[j]]->defenders.size() > 0) { // More defenders than attackers
                int dValue = piecesPoss[myPcsI[j]]->value, aValue = 0, mostVal = 0;
                bool accounted = false;
                for (int k = 0; k < piecesPoss[myPcsI[j]]->attackers.size(); k++) {
                    if (piecesPoss[myPcsI[j]]->attackers[k]->value < dValue) {
                        inDangerBefore += dValue-piecesPoss[myPcsI[j]]->attackers[k]->value;
                        accounted = true;
                        break;
                    }
                }
            }
        }
        for (int j = 0; j < myPcsI.size(); j++) {
            if (piecesPoss2[myPcsI[j]]->attackers.size() > 0 && piecesPoss2[myPcsI[j]]->defenders.size() == 0) {
                inDangerAfter += piecesPoss2[myPcsI[j]]->value;
            } else if (piecesPoss2[myPcsI[j]]->attackers.size() > piecesPoss2[myPcsI[j]]->defenders.size()) {
                int dValue = piecesPoss2[myPcsI[j]]->value, aValue = 0, mostVal = 0;
                bool accounted = false;
                for (int k = 0; k < piecesPoss2[myPcsI[j]]->attackers.size(); k++) {
                    if (piecesPoss2[myPcsI[j]]->attackers[k]->value < dValue) {
                        inDangerAfter += dValue;
                        accounted = true;
                        break;
                    } else {
                        aValue += piecesPoss2[myPcsI[j]]->attackers[k]->value;
                        if (piecesPoss2[myPcsI[j]]->attackers[k]->value > mostVal) {
                            mostVal = piecesPoss2[myPcsI[j]]->attackers[k]->value;
                        }
                    }
                }
                if (accounted) {
                    continue;
                }
                for (int k = 0; k < piecesPoss2[myPcsI[j]]->defenders.size(); k++) {
                    dValue += piecesPoss2[myPcsI[j]]->defenders[k]->value;
                }
                aValue -= mostVal;
                if (dValue > aValue) {
                    inDangerAfter += piecesPoss2[myPcsI[j]]->value;
                }
            } else if (piecesPoss2[myPcsI[j]]->attackers.size() > 0 && piecesPoss2[myPcsI[j]]->attackers.size() == piecesPoss2[myPcsI[j]]->defenders.size()) { // Equal defenders to attackers
                int dValue = piecesPoss2[myPcsI[j]]->value, aValue = 0, mostVal = 0;
                bool accounted = false;
                for (int k = 0; k < piecesPoss2[myPcsI[j]]->attackers.size(); k++) {
                    if (piecesPoss2[myPcsI[j]]->attackers[k]->value < dValue) {
                        inDangerAfter += dValue-piecesPoss2[myPcsI[j]]->attackers[k]->value;
                        accounted = true;
                        break;
                    } else {
                        aValue += piecesPoss2[myPcsI[j]]->attackers[k]->value;
                    }
                }
                if (accounted) {
                    continue;
                }
                for (int k = 0; k < piecesPoss2[myPcsI[j]]->defenders.size(); k++) {
                    dValue += piecesPoss2[myPcsI[j]]->defenders[k]->value;
                    if (piecesPoss2[myPcsI[j]]->defenders[k]->value > mostVal) {
                        mostVal = piecesPoss2[myPcsI[j]]->defenders[k]->value;
                    }
                }
                dValue -= mostVal;
                if (dValue > aValue) {
                    inDangerAfter += dValue-aValue;
                }
            } else if (piecesPoss2[myPcsI[j]]->attackers.size() > 0 && piecesPoss2[myPcsI[j]]->defenders.size() > 0) { // More defenders than attackers
                int dValue = piecesPoss2[myPcsI[j]]->value, aValue = 0, mostVal = 0;
                bool accounted = false;
                for (int k = 0; k < piecesPoss2[myPcsI[j]]->attackers.size(); k++) {
                    if (piecesPoss2[myPcsI[j]]->attackers[k]->value < dValue) {
                        inDangerAfter += dValue-piecesPoss2[myPcsI[j]]->attackers[k]->value;
                        accounted = true;
                        break;
                    }
                }
            }
        }
        if (piecesPoss[pieceIndex[i]]->pieceType == 'P' && boardPoss[x][y] == "" && piecesPoss[pieceIndex[i]]->posy != y) { // If piece is pawn, check en passant
            enPassant = true;
            temp = findPiece(piecesPoss[pieceIndex[i]]->posx, y, boardPoss, piecesPoss, boardPoss[piecesPoss[pieceIndex[i]]->posx][y][0]);
        }
        if (boardPoss[x][y] != "" || enPassant) { // Move is a capture
            if (!enPassant) {
                temp = findPiece(x, y, boardPoss, piecesPoss, boardPoss[x][y][0]);
            } else {
                if (inDangerAfter-1 > inDangerBefore) {
                    fstream << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    cout << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority17.push_back(possMoves[i]);
                    ipriority17.push_back(pieceIndex[i]);
                    continue;
                }
                if (inDangerAfter < inDangerBefore) {
                    prioritizeByValue(temp->value+inDangerBefore-inDangerAfter, i, "Undefended danger-relief attack", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    continue;
                }
                if (inDangerAfter-1 == inDangerBefore) {
                    fstream << "Move is a trade, priority 13\n";
                    cout << "Move is a trade, priority 13\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority13.push_back(possMoves[i]);
                    ipriority13.push_back(pieceIndex[i]);
                    continue;
                }
                prioritizeByValue(temp->value, i, "Undefended attack", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                continue;
            }
            if (temp->defenders.size() == 0) { // If attacked piece is undefended
                if (inDangerAfter-temp->value > inDangerBefore) {
                    fstream << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    cout << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority17.push_back(possMoves[i]);
                    ipriority17.push_back(pieceIndex[i]);
                    continue;
                }
                if (inDangerAfter < inDangerBefore) {
                    prioritizeByValue(temp->value+inDangerBefore-inDangerAfter, i, "Undefended danger-relief attack", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    continue;
                }
                prioritizeByValue(temp->value, i, "Undefended attack", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                continue;
            } else if (piecesPoss[pieceIndex[i]]->value < temp->value) { // If attacked piece is more valuable than attacking piece
                if (inDangerAfter-temp->value > inDangerBefore) {
                    fstream << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    cout << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority17.push_back(possMoves[i]);
                    ipriority17.push_back(pieceIndex[i]);
                    continue;
                }
                if (inDangerAfter < inDangerBefore) {
                    prioritizeByValue(temp->value+inDangerBefore-inDangerAfter, i, "defndr less/equal val to atckr", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    continue;
                }
                prioritizeByValue(temp->value-piecesPoss[pieceIndex[i]]->value, i, "defndr less/equal val to atckr", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                continue;
            } else if (temp->attackers.size() > temp->defenders.size()) { // If more attackers than defenders
                int dValue = temp->value, aValue = 0, mostVal = 0;
                for (int j = 0; j < temp->attackers.size(); j++) {
                    aValue += temp->attackers[j]->value;
                    if (temp->attackers[j]->value > mostVal) {
                        mostVal = temp->attackers[j]->value;
                    }
                }
                for (int j = 0; j < temp->defenders.size(); j++) {
                    dValue += temp->defenders[j]->value;
                }
                if (inDangerAfter-temp->value > inDangerBefore) {
                    fstream << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    cout << "Move endangers more pieces or more valuable pieces, priority 17\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority17.push_back(possMoves[i]);
                    ipriority17.push_back(pieceIndex[i]);
                    continue;
                }
                if (inDangerAfter < inDangerBefore) {
                    prioritizeByValue(temp->value+inDangerBefore-inDangerAfter, i, "Undefended danger-relief attack", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    continue;
                }
                if (dValue > aValue-mostVal) { // If total defenders value is greater than total attacker value
                    prioritizeByValue(dValue-aValue-mostVal, i, "more atckrs than defndrs, defndrs value greater than atckrs", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    continue;
                }
            } else if (piecesPoss[pieceIndex[i]]->value == temp->value) { // Move would be a trade
                if (piecesPoss[pieceIndex[i]]->defenders.size() < piecesPoss[pieceIndex[i]]->attackers.size()) {
                    prioritizeByValue(temp->value, i, "Trade undefended piece", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    continue;
                }
                fstream << "Trade pieces, priority 15\n";
                cout << "Trade pieces, priority 15\n";
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                priority15.push_back(possMoves[i]);
                ipriority15.push_back(pieceIndex[i]);
                continue;
            } else { // Fewer or equal attackers than defenders, and attacker is not more valuable than attacked
                fstream << "Not enough attackers to capture, priority 17\n";
                cout << "Not enough attackers to capture, priority 17\n";
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                priority17.push_back(possMoves[i]);
                ipriority17.push_back(pieceIndex[i]);
                continue;
            }
        } else {
            if (inDangerAfter > inDangerBefore) {
                fstream << "Move endangers more pieces or more valuable pieces, priority 17\n";
                cout << "Move endangers more pieces or more valuable pieces, priority 17\n";
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                priority17.push_back(possMoves[i]);
                ipriority17.push_back(pieceIndex[i]);
                continue;
            }
            if (inDangerAfter < inDangerBefore) {
                if (piecesPoss[pieceIndex[i]]->pieceType == 'K' && piecesPoss[pieceIndex[i]]->timesMoved == 0) {
                    cout << "King loses castling ability to reduce danger, priority 13\n";
                    fstream << "King loses castling ability to reduce danger, priority 13\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority13.push_back(possMoves[i]);
                    ipriority13.push_back(pieceIndex[i]);
                    continue;
                }
                int z = inDangerBefore-inDangerAfter;
                
                string msg = to_string(z)+" points saved";
                prioritizeByValue(z, i, msg, fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                continue;
            }
            if (piecesPoss2[pieceIndex[i]]->attackers.size() > piecesPoss2[pieceIndex[i]]->defenders.size()) { // More attackers than defenders on new tile
                int dValue = piecesPoss2[pieceIndex[i]]->value, aValue = 0;
                for (int j = 0; j < piecesPoss2[pieceIndex[i]]->attackers.size(); j++) {
                    if (piecesPoss2[pieceIndex[i]]->attackers[j]->value < dValue) {
                        fstream << "Attacker is less valuable, priority 17\n";
                        cout << "Attacker is less valuable, priority 17\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority17.push_back(possMoves[i]);
                        ipriority17.push_back(pieceIndex[i]);
                        assigned = true;
                        break;
                    }
                    aValue += piecesPoss2[pieceIndex[i]]->attackers[j]->value;
                }
                if (assigned) {
                    continue;
                }
                for (int j = 0; j < piecesPoss2[pieceIndex[i]]->defenders.size(); j++) {
                    dValue += piecesPoss2[pieceIndex[i]]->defenders[j]->value;
                }
                if (aValue < dValue) {
                    fstream << "Attackers are less valuable than defenders, priority 17\n";
                    cout << "Attackers are less valuable than defenders, priority 17\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority17.push_back(possMoves[i]);
                    ipriority17.push_back(pieceIndex[i]);
                    continue;
                } else {
                    fstream << "Attackers are not less valuable than defenders, priority 16\n";
                    cout << "Attackers are not less valuable than defenders, priority 16\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority16.push_back(possMoves[i]);
                    ipriority16.push_back(pieceIndex[i]);
                    continue;
                }
            }
            for (int j = 0; j < piecesPoss[pieceIndex[i]]->attackers.size(); j++) {
                if (piecesPoss[pieceIndex[i]]->attackers[j]->value < piecesPoss[pieceIndex[i]]->value) { // If your piece is attacked by a lesser value piece
                    for (int k = 0; k < piecesPoss2[pieceIndex[i]]->attackers.size(); k++) {
                        if (piecesPoss2[pieceIndex[i]]->attackers[k]->value < piecesPoss2[pieceIndex[i]]->value) { // If your piece is still attacked by a lesser value piece after moving
                            fstream << "Move from danger to danger, priority 17\n";
                            cout << "Move from danger to danger, priority 17\n";
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            priority17.push_back(possMoves[i]);
                            ipriority17.push_back(pieceIndex[i]);
                            assigned = true;
                            break;
                        }
                    }
                    if (assigned) { // move already assigned
                        break;
                    }
                    prioritizeByValue(piecesPoss[pieceIndex[i]]->value, i, "Move to safety", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    assigned = true;
                }
                if (assigned) {
                    break;
                }
            }
            if (assigned) { // move already assigned
                continue;
            } else if (piecesPoss2[pieceIndex[i]]->attackers.size() > 0) { // If moved, piece is attacked
                for (int j = 0; j < piecesPoss2[pieceIndex[i]]->attackers.size(); j++) {
                    if (piecesPoss2[pieceIndex[i]]->attackers[j]->value < piecesPoss2[pieceIndex[i]]->value) { // Attacker is less valuable
                        fstream << "Attacker is less valuable, priority 17\n";
                        cout << "Attacker is less valuable, priority 17\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority17.push_back(possMoves[i]);
                        ipriority17.push_back(pieceIndex[i]);
                        assigned = true;
                        break;
                    }
                }
                if (assigned) {
                    continue;
                }
            }
            if (piecesPoss2[pieceIndex[i]]->pieceType == 'N' && ((piecesPoss[pieceIndex[i]]->posx == 3 || piecesPoss[pieceIndex[i]]->posx == 4) && (piecesPoss[pieceIndex[i]]->posy == 3 || piecesPoss[pieceIndex[i]]->posy == 4))) {
                fstream << "Move is away from power square, priority 16\n";
                cout << "Move is away from power square, priority 16\n";
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                priority16.push_back(possMoves[i]);
                ipriority16.push_back(pieceIndex[i]);
                continue;
            }
            if (((x == 4 && (y == 3 || y == 4)) || (x == 3 && (y == 3 || y == 4)))) { // Move is a power square
                if (piecesPoss2[pieceIndex[i]]->pieceType == 'P') {
                    fstream << "Move is a power square, priority 13\n";
                    cout << "Move is a power square, priority 13\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority13.push_back(possMoves[i]);
                    ipriority13.push_back(pieceIndex[i]);
                    continue;
                } else if (piecesPoss2[pieceIndex[i]]->pieceType == 'N') {
                    fstream << "Move is a power square, priority 14\n";
                    cout << "Move is a power square, priority 14\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority14.push_back(possMoves[i]);
                    ipriority14.push_back(pieceIndex[i]);
                    continue;
                }
            } else if (((x == 3 || x == 4) && (y == 2 || y == 5 || y == 1 || y == 6) )) { // Move is bishop opener
                if (piecesPoss[pieceIndex[i]]->pieceType == 'B' && piecesPoss[pieceIndex[i]]->timesMoved == 0) {
                    fstream << "Move is close to center, priority 13\n";
                    cout << "Move is close to center, priority 13\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority13.push_back(possMoves[i]);
                    ipriority13.push_back(pieceIndex[i]);
                    continue;
                }
            } else if ((x == 2 && (y == 3 || y == 4)) || (x == 5 && (y == 3 || y == 4))) { // Move is bishop opener
                if (piecesPoss[pieceIndex[i]]->pieceType == 'B' && piecesPoss[pieceIndex[i]]->timesMoved == 0) {
                    fstream << "Move is close to center, priority 14\n";
                    cout << "Move is close to center, priority 14\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority14.push_back(possMoves[i]);
                    ipriority14.push_back(pieceIndex[i]);
                    continue;
                }
            } 
            if (piecesPoss2[pieceIndex[i]]->coveredTiles.size() > piecesPoss[pieceIndex[i]]->coveredTiles.size()) { // Move increases board coverage
                if (piecesPoss2[pieceIndex[i]]->coveredTiles.size() > piecesPoss[pieceIndex[i]]->coveredTiles.size()+4) {
                    if (piecesPoss2[pieceIndex[i]]->pieceType == 'Q') {
                        fstream << "Increases queen's covered tiles by 5+, priority 14\n";
                        cout << "Increases queen's covered tiles by 5+, priority 14\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority14.push_back(possMoves[i]);
                        ipriority14.push_back(pieceIndex[i]);
                        continue;
                    }
                    fstream << "Increases covered tiles by 5+, priority 13\n";
                    cout << "Increases covered tiles by 5+, priority 13\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority13.push_back(possMoves[i]);
                    ipriority13.push_back(pieceIndex[i]);
                    continue;
                } else if (col == 'W') {
                if (piecesPoss2[15]->inCheck) {
                    for (int j = 0; j < piecesPoss2[pieceIndex[i]]->attacking.size(); j++) {
                        if (piecesPoss2[pieceIndex[i]]->attacking[j]->pieceType != 'K') {
                            if (piecesPoss2[pieceIndex[i]]->attacking[j]->defenders.size() == 0) {
                                prioritizeByValue(piecesPoss2[pieceIndex[i]]->attacking[j]->value, i, "Forks King and undefended piece", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                                assigned = true;
                                break;
                            } else if (piecesPoss2[pieceIndex[i]]->attacking[j]->value > piecesPoss2[pieceIndex[i]]->value) {
                                prioritizeByValue(piecesPoss2[pieceIndex[i]]->attacking[j]->value-piecesPoss2[pieceIndex[i]]->value, i, "Forks King and less valuable piece", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                                assigned = true;
                                break;
                            } // Eventually be good to check for value of all defending/attacking pieces
                        }
                    }
                    if (assigned) {
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        continue;
                    }
		    fstream << "Places opponent in check, priority 14\n";
                    cout << "Places opponent in check, priority 14\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority14.push_back(possMoves[i]);
                    ipriority14.push_back(pieceIndex[i]);
                    continue;
                } else if (possMoves[i][0] == 'P') {
                    if (possMoves[i][2] == '7' || possMoves[i][2] == '8') {
                        fstream << "Pawn close to promotion, priority 13\n";
                        cout << "Pawn close to promotion, priority 13\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority13.push_back(possMoves[i]);
                        ipriority13.push_back(pieceIndex[i]);
                        continue;
                    } else if (possMoves[i][2] == '6') {
                        fstream << "Pawn close to promotion, priority 15\n";
                        cout << "Pawn close to promotion, priority 15\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority15.push_back(possMoves[i]);
                        ipriority15.push_back(pieceIndex[i]);
                        continue;
                    }
                }
            } else if (col == 'B') {
                if (piecesPoss2[14]->inCheck) {
                    for (int j = 0; j < piecesPoss2[pieceIndex[i]]->attacking.size(); j++) {
                        if (piecesPoss2[pieceIndex[i]]->attacking[j]->pieceType != 'K') {
                            if (piecesPoss2[pieceIndex[i]]->attacking[j]->defenders.size() == 0) {
                                prioritizeByValue(piecesPoss2[pieceIndex[i]]->attacking[j]->value, i, "Forks King and undefended piece", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                                assigned = true;
                                break;
                            } else if (piecesPoss2[pieceIndex[i]]->attacking[j]->value > piecesPoss2[pieceIndex[i]]->value) {
                                prioritizeByValue(piecesPoss2[pieceIndex[i]]->attacking[j]->value-piecesPoss2[pieceIndex[i]]->value, i, "Forks King and less valuable piece", fstream, possMoves, pieceIndex, priority1, priority2, priority3, priority4, ipriority1, ipriority2, ipriority3, ipriority4, priority5, priority6, priority7, priority8, ipriority5, ipriority6, ipriority7, ipriority8, priority9, priority10, priority11, priority12, ipriority9, ipriority10, ipriority11, ipriority12);
                                assigned = true;
                                break;
                            } // Eventually be good to check for value of all defending/attacking pieces
                        }
                    }
                    if (assigned) {
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        continue;
                    }
		    fstream << "Places opponent in check, priority 14\n";
                    cout << "Places opponent in check, priority 14\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority14.push_back(possMoves[i]);
                    ipriority14.push_back(pieceIndex[i]);
                    continue;
                } else if (possMoves[i][0] == 'P') {
                    if (possMoves[i][2] == '2' || possMoves[i][2] == '1') {
                        fstream << "Pawn close to promotion, priority 13\n";
                        cout << "Pawn close to promotion, priority 13\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority13.push_back(possMoves[i]);
                        ipriority13.push_back(pieceIndex[i]);
                        continue;
                    } else if (possMoves[i][2] == '3') {
                        fstream << "Pawn close to promotion, priority 15\n";
                        cout << "Pawn close to promotion, priority 15\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority15.push_back(possMoves[i]);
                        ipriority15.push_back(pieceIndex[i]);
                        continue;
                    }
                }
            } else if (piecesPoss2[pieceIndex[i]]->coveredTiles.size() > piecesPoss[pieceIndex[i]]->coveredTiles.size()+2) {
                    if (piecesPoss[pieceIndex[i]]->pieceType == 'K') {
                        if (piecesPoss[pieceIndex[i]]->timesMoved == 0) {
                            fstream << "Move increases king coverage before he's moved, priority 17\n";
                            cout << "Move increases king coverage before he's moved, priority 17\n";
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            priority17.push_back(possMoves[i]);
                            ipriority17.push_back(pieceIndex[i]);
                            continue;
                        } else {
                            fstream << "Move increases king coverage after he's moved, priority 16\n";
                            cout << "Move increases king coverage after he's moved, priority 16\n";
                            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                            update(lastMove, boardPoss2, piecesPoss2);
                            priority16.push_back(possMoves[i]);
                            ipriority16.push_back(pieceIndex[i]);
                            continue;
                        }
                    } else if (piecesPoss2[pieceIndex[i]]->pieceType == 'Q') {
                        fstream << "Increases queen's covered tiles by 3-4, priority 15\n";
                        cout << "Increases queen's covered tiles by 3-4, priority 15\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority15.push_back(possMoves[i]);
                        ipriority15.push_back(pieceIndex[i]);
                        continue;
                    } else {
                        fstream << "Increases covered tiles by 3-4, priority 14\n";
                        cout << "Increases covered tiles by 3-4, priority 14\n";
                        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                        update(lastMove, boardPoss2, piecesPoss2);
                        priority14.push_back(possMoves[i]);
                        ipriority14.push_back(pieceIndex[i]);
                        continue;
                    }
                } else {
                    fstream << "Increases covered tiles by 1-2, priority 15\n";
                    cout << "Increases covered tiles by 1-2, priority 15\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority15.push_back(possMoves[i]);
                    ipriority15.push_back(pieceIndex[i]);
                    continue;
                }
            } else if ((x <= 5 && x >= 2) && (y >= 2 && y <= 5)) { // Move is close to center
                if (possMoves[i][0] == 'P' && (y == 3 || y == 4)) {
                    fstream << "Move is close to center, priority 14\n";
                    cout << "Move is close to center, priority 14\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority14.push_back(possMoves[i]);
                    ipriority14.push_back(pieceIndex[i]);
                    continue;
                } else if (piecesPoss[pieceIndex[i]]->pieceType != 'K') {
                    fstream << "Move is close to center, priority 15\n";
                    cout << "Move is close to center, priority 15\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority15.push_back(possMoves[i]);
                    ipriority15.push_back(pieceIndex[i]);
                    continue;
                } else {
                    fstream << "Move king close to center, priority 16\n";
                    cout << "Move king close to center, priority 16\n";
                    copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                    update(lastMove, boardPoss2, piecesPoss2);
                    priority16.push_back(possMoves[i]);
                    ipriority16.push_back(pieceIndex[i]);
                    continue;
                }
            } else if (piecesPoss2[pieceIndex[i]]->attacking.size() > piecesPoss[pieceIndex[i]]->attacking.size() || piecesPoss2[pieceIndex[i]]->defending.size() > piecesPoss[pieceIndex[i]]->defending.size()) {
                fstream << "Increases attackers/defenders, priority 15\n";
                cout << "Increases attackers/defenders, priority 15\n";
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                priority15.push_back(possMoves[i]);
                ipriority15.push_back(pieceIndex[i]);
                continue;
            }
            copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
            update(lastMove, boardPoss2, piecesPoss2);
        }
        if ((piecesPoss[pieceIndex[i]]->pieceType == 'N' || piecesPoss[pieceIndex[i]]->pieceType == 'B') && ((x == 0 || x == 7) || (y == 0 || y == 7))) {
            fstream << "Moves knight/bishop to the edge, priority 16\n";
            cout << "Moves knight/bishop to the edge, priority 16\n";
            priority16.push_back(possMoves[i]);
            ipriority16.push_back(pieceIndex[i]);
        } else if (piecesPoss[pieceIndex[i]]->timesMoved == 0 || piecesPoss[pieceIndex[i]]->timesMoved == 1) {
            if (piecesPoss[pieceIndex[i]]->pieceType == 'K' || (piecesPoss[pieceIndex[i]]->pieceType == 'R' && piecesPoss[king]->timesMoved == 0)) {
                fstream << "Rook/King have moved 0-1 time, priority 16\n";
                cout << "Rook/King have moved 0-1 time, priority 16\n";
                priority16.push_back(possMoves[i]);
                ipriority16.push_back(pieceIndex[i]);
            } else {
                fstream << "Bishop/Knight/Queen/Pawn have moved 0-1 time, priority 15\n";
                cout << "Bishop/Knight/Queen/Pawn have moved 0-1 time, priority 15\n";
                priority15.push_back(possMoves[i]);
                ipriority15.push_back(pieceIndex[i]);
            }
        } else if (piecesPoss[pieceIndex[i]]->timesMoved == 2 || piecesPoss[pieceIndex[i]]->timesMoved == 3) {
            if (piecesPoss[pieceIndex[i]]->pieceType == 'K' || piecesPoss[pieceIndex[i]]->pieceType == 'P'  || piecesPoss[pieceIndex[i]]->pieceType == 'R' || piecesPoss[pieceIndex[i]]->pieceType == 'Q') {
                fstream << "King/Pawn/Rook/Queen have moved 2-3 times, priority 16\n";
                cout << "King/Pawn/Rook/Queen have moved 2-3 times, priority 16\n";
                priority16.push_back(possMoves[i]);
                ipriority16.push_back(pieceIndex[i]);
            } else {
                fstream << "Bishop/Knight have moved 2-3 times, priority 16\n";
                cout << "Bishop/Knight have moved 2-3 times, priority 16\n";
                priority16.push_back(possMoves[i]);
                ipriority16.push_back(pieceIndex[i]);
            }
        } else {
            fstream << "Else, priority 17\n";
            cout << "Else, priority 17\n";
            priority17.push_back(possMoves[i]);
            ipriority17.push_back(pieceIndex[i]);
        }
    }
    possMoves.clear();
    pieceIndex.clear();
    r = rand();
    fstream << "Move ranking:\n";
    cout << "Move ranking:\n";
    for (int i = 0; i < priority0.size(); i++) {
        possMoves.push_back(priority0[(i+r)%priority0.size()]);
        pieceIndex.push_back(ipriority0[(i+r)%priority0.size()]);
        fstream << "\t" << i << ". " << possMoves.back() << " Priority 0" << endl;
        cout << "\t" << i << ". " << possMoves.back() << " Priority 0" << endl;
    }
    sort(priority1, ipriority1, piecesPoss, king);
    for (int i = 0; i < priority1.size(); i++) {
        possMoves.push_back(priority1[i]);
        pieceIndex.push_back(ipriority1[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 1" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 1" << endl;
    }
    sort(priority2, ipriority2, piecesPoss, king);
    for (int i = 0; i < priority2.size(); i++) {
        possMoves.push_back(priority2[i]);
        pieceIndex.push_back(ipriority2[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 2" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 2" << endl;
    }
    sort(priority3, ipriority3, piecesPoss, king);
    for (int i = 0; i < priority3.size(); i++) {
        possMoves.push_back(priority3[i]);
        pieceIndex.push_back(ipriority3[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 3" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 3" << endl;
    }
    sort(priority4, ipriority4, piecesPoss, king);
    for (int i = 0; i < priority4.size(); i++) {
        possMoves.push_back(priority4[i]);
        pieceIndex.push_back(ipriority4[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 4" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 4" << endl;
    }
    sort(priority5, ipriority5, piecesPoss, king);
    for (int i = 0; i < priority5.size(); i++) {
        possMoves.push_back(priority5[i]);
        pieceIndex.push_back(ipriority5[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 5" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 5" << endl;
    }
    sort(priority6, ipriority6, piecesPoss, king);
    for (int i = 0; i < priority6.size(); i++) {
        possMoves.push_back(priority6[i]);
        pieceIndex.push_back(ipriority6[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 6" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 6" << endl;
    }
    sort(priority7, ipriority7, piecesPoss, king);
    for (int i = 0; i < priority7.size(); i++) {
        possMoves.push_back(priority7[i]);
        pieceIndex.push_back(ipriority7[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 7" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 7" << endl;
    }
    sort(priority8, ipriority8, piecesPoss, king);
    for (int i = 0; i < priority8.size(); i++) {
        possMoves.push_back(priority8[i]);
        pieceIndex.push_back(ipriority8[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 8" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 8" << endl;
    }
    sort(priority9, ipriority9, piecesPoss, king);
    for (int i = 0; i < priority9.size(); i++) {
        possMoves.push_back(priority9[i]);
        pieceIndex.push_back(ipriority9[i]);
        fstream << "\t" << i << ". " << possMoves.back() << " Priority 9" << endl;
        cout << "\t" << i << ". " << possMoves.back() << " Priority 9" << endl;
    }
    sort(priority10, ipriority10, piecesPoss, king);
    for (int i = 0; i < priority10.size(); i++) {
        possMoves.push_back(priority10[i]);
        pieceIndex.push_back(ipriority10[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 10" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 10" << endl;
    }
    sort(priority11, ipriority11, piecesPoss, king);
    for (int i = 0; i < priority11.size(); i++) {
        possMoves.push_back(priority11[i]);
        pieceIndex.push_back(ipriority11[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 11" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 11" << endl;
    }
    sort(priority12, ipriority12, piecesPoss, king);
    for (int i = 0; i < priority12.size(); i++) {
        possMoves.push_back(priority12[i]);
        pieceIndex.push_back(ipriority12[i]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 12" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 12" << endl;
    }
    for (int i = 0; i < priority13.size(); i++) {
        possMoves.push_back(priority13[(i+r)%priority13.size()]);
        pieceIndex.push_back(ipriority13[(i+r)%priority13.size()]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 13" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 13" << endl;
    }
    for (int i = 0; i < priority14.size(); i++) {
        possMoves.push_back(priority14[(i+r)%priority14.size()]);
        pieceIndex.push_back(ipriority14[(i+r)%priority14.size()]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 14" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 14" << endl;
    }
    for (int i = 0; i < priority15.size(); i++) {
        possMoves.push_back(priority15[(i+r)%priority15.size()]);
        pieceIndex.push_back(ipriority15[(i+r)%priority15.size()]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 15" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 15" << endl;
    }
    for (int i = 0; i < priority16.size(); i++) {
        possMoves.push_back(priority16[(i+r)%priority16.size()]);
        pieceIndex.push_back(ipriority16[(i+r)%priority16.size()]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 16" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 16" << endl;
    }
    for (int i = 0; i < priority17.size(); i++) {
        possMoves.push_back(priority17[(i+r)%priority17.size()]);
        pieceIndex.push_back(ipriority17[(i+r)%priority17.size()]);
        fstream << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 17" << endl;
        cout << "\t" << possMoves.size() << ". " << possMoves.back() << " Priority 17" << endl;
    }
    // Validate moves in order of priority, then move
    string staleForced;	
    for (int i = 0; i < possMoves.size(); i++) {
        // cout << "Trying move " << possMoves[i] << " #" << i+1 << " of " << possMoves.size() << endl;
        int king, kr, qr, rkSq;
        if (possMoves[i][0] == '0') {
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
            if (possMoves[i] == "0-0") {
                piecesPoss[king]->move(rkSq, 6, boardPoss, piecesPoss);
                piecesPoss[kr]->move(rkSq, 5, boardPoss, piecesPoss);
                update(lastMove, boardPoss, piecesPoss);
                copyBoard(boardPoss, board, piecesPoss, pieces);
                update(lastMove, board, pieces);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                return possMoves[i];
            } else if (possMoves[i] == "0-0-0") {
                piecesPoss[king]->move(rkSq, 2, boardPoss, piecesPoss);
                piecesPoss[qr]->move(rkSq, 3, boardPoss, piecesPoss);
                update(lastMove, boardPoss, piecesPoss);
                copyBoard(boardPoss, board, piecesPoss, pieces);
                update(lastMove, board, pieces);
                copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
                update(lastMove, boardPoss2, piecesPoss2);
                return possMoves[i];
            }
        } else if (possMoves[i][0] != 'P') { // Check if not pawn piece
            possMove = possMoves[i][0];
        } else {
            possMove = "";
        }
        int x = charToNum(possMoves[i][2]), y = letterToNum(possMoves[i][1]);
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
        if (boardPoss[x][y] != "") { // Check if Capture
            if (possMove == "") {
                possMove += numToLetter(piecesPoss[pieceIndex[i]]->posy);
            }
            possMove += 'x'; // Add capture notation
        } else if (possMove == "") { // If piece is pawn, check en passant
            if (piecesPoss[pieceIndex[i]]->posy != y) {
                possMove += numToLetter(piecesPoss[pieceIndex[i]]->posy);
                possMove += 'x';
                Piece* temp = findPiece(piecesPoss[pieceIndex[i]]->posx, y, boardPoss, piecesPoss, boardPoss[piecesPoss[pieceIndex[i]]->posx][y][0]);
                temp->posx = 8; temp->posy = 8;
                boardPoss[piecesPoss[pieceIndex[i]]->posx][y] = "";
            }
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
        piecesPoss[pieceIndex[i]]->move(x, y, boardPoss, piecesPoss);
        update(lastMove, boardPoss, piecesPoss);
        if (prom) {
            promote(col, 'Q', pieceIndex[i], boardPoss2, piecesPoss2);   
        }
        copyBoard(boardPoss, boardPoss2, piecesPoss, piecesPoss2);
        update(lastMove, boardPoss2, piecesPoss2);
        if (check(boardPoss, piecesPoss, col)) { // Check if Check
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
	    staleForced = possMove;
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
    return staleForced;
}

bool canCastle(string lastMove, string move, string (*board)[8], string (*boardPoss)[8], string (*boardPoss2)[8], Piece** pieces, Piece** piecesPoss, Piece** piecesPoss2, char col, bool &gameOver) {
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
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return true;
                                } else {
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                            } else {
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                        } else {
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                    } else {
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
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
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return true;
                                        
                                    } else {
                                        copyBoard(board, boardPoss, pieces, piecesPoss);
                                        update(lastMove, boardPoss, piecesPoss);
                                        return false;
                                    }
                                } else {
                                    copyBoard(board, boardPoss, pieces, piecesPoss);
                                    update(lastMove, boardPoss, piecesPoss);
                                    return false;
                                }
                            } else {
                                copyBoard(board, boardPoss, pieces, piecesPoss);
                                update(lastMove, boardPoss, piecesPoss);
                                return false;
                            }
                        } else {
                            copyBoard(board, boardPoss, pieces, piecesPoss);
                            update(lastMove, boardPoss, piecesPoss);
                            return false;
                        }
                    } else {
                        copyBoard(board, boardPoss, pieces, piecesPoss);
                        update(lastMove, boardPoss, piecesPoss);
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}
