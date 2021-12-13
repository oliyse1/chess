#include <iostream>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"

using namespace std;

//constructor calls resetBoard
ChessBoard::ChessBoard() {
    resetBoard();
}

ChessBoard::~ChessBoard() {
    //delete all existing pieces on the board and set all squares to nullptr
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if(current_board[row][col] != nullptr) {
                delete current_board[row][col];
                current_board[row][col] = nullptr;
            }  
        }
    }
}

void ChessBoard::resetBoard() {

    cout << "A new chess game is started!" << endl;

    is_game_over = false;
    
    //white always goes first
    this_turn_colour = white;

    //delete all existing pieces on the board and set all squares to nullptr
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if(current_board[row][col] != nullptr) {
                delete current_board[row][col];
                current_board[row][col] = nullptr;
            }  
        }
    }

    //fill board with initial chess setup
    current_board[0][0] = new Rook(rook, white);
    current_board[0][1] = new Knight(knight, white);
    current_board[0][2] = new Bishop(bishop, white);
    current_board[0][3] = new Queen(queen, white);
    current_board[0][4] = new King(king, white);
    current_board[0][5] = new Bishop(bishop, white);
    current_board[0][6] = new Knight(knight, white);
    current_board[0][7] = new Rook(rook, white);

    for (int col = 0; col < 8; col++) {
        current_board[1][col] = new Pawn(pawn, white);
    }

    for (int col = 0; col < 8; col++) {
        current_board[6][col] = new Pawn(pawn, black);
    }

    current_board[7][0] = new Rook(rook, black);
    current_board[7][1] = new Knight(knight, black);
    current_board[7][2] = new Bishop(bishop, black);
    current_board[7][3] = new Queen(queen, black);
    current_board[7][4] = new King(king, black);
    current_board[7][5] = new Bishop(bishop, black);
    current_board[7][6] = new Knight(knight, black);
    current_board[7][7] = new Rook(rook, black);
  
}

ChessPiece* ChessBoard::getChessPiece(int row, int col) const {
    return current_board[row][col];
}

Colour ChessBoard::getNextTurnColour() const {
    if (this_turn_colour == white) {
        return black;
    }
    else {
        return white;
    }
}

void ChessBoard::alternateTurns() {
    if (this_turn_colour == white) {
        this_turn_colour = black;
    }
    else {
        this_turn_colour = white;
    }
}

void ChessBoard::getKingPosition(Colour colour, int& king_row, int& king_col) {
    for (king_row = 0; king_row < 8; king_row++) {
        for (king_col = 0; king_col < 8; king_col++) {
            if(current_board[king_row][king_col] != nullptr) {
                if(current_board[king_row][king_col]->getType() == king && current_board[king_row][king_col]->getColour() == colour) {
                    return;
                }
            }
        }
    }
}

bool ChessBoard::isInCheck(Colour colour) {
    //find position of King in check
    int king_row, king_col;
    getKingPosition(colour, king_row, king_col);

    //check if it is a valid move for any piece on the board to have the King of the specified colour as their destination
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if(current_board[row][col] != nullptr) {
                if(current_board[row][col]->isLegalMove(row, col, king_row, king_col, *this)) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool ChessBoard::canMove(Colour colour) {
    for (int row = 0 ; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            //check for any piece on the board which is the specified colour
            if (current_board[row][col] != nullptr && current_board[row][col]->getColour() == colour) {
                //for all destinations on the board
                for (int move_row = 0 ; move_row < 8; move_row++) {
                    for (int move_col = 0; move_col < 8; move_col++) {
                        
                        //check if it is a valid move for the chess piece, no need to check for castling as castling will never be to only move a player can make 
                        if (current_board[row][col]->isLegalMove(row, col, move_row, move_col, *this)) {
                            //make the move
                            ChessPiece* temp = current_board[move_row][move_col];
                            current_board[move_row][move_col] = current_board[row][col];
                            current_board[row][col] = nullptr;

                            //check if player of the specified colour is in check after making the move
                            bool is_in_check = isInCheck(colour);

                            //undo the move
                            current_board[row][col] = current_board[move_row][move_col];
                            current_board[move_row][move_col] = temp;

                            //if was not in check, it is a legal move, so return true
                            if (is_in_check == false) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool ChessBoard::isGameOver(Colour colour) {
    //if player of specified colour cannot make any moves
    if(!canMove(colour)) {
        //if player of specified colour is in check then that player is in checkmate
        if (isInCheck(colour)) {
            cout << colours[colour] << " is in checkmate" << endl;
        } 
        //if player of specified colour is not in check then a staltemate has occured
        else {
            cout << "Stalemate!" << endl;
        }
        return true;
    } 
    //if player of specified colour is able to move
    return false;
}

void ChessBoard::submitMove(char const* source_square, char const* destination_square) {
    //cannot make a move when game is over
    if (is_game_over) {
        cout << "Game is over, please start a new game with resetBoard()." << endl;
        return;
    }
    //temporary variable
    int length_of_source_square = 0;
    int length_of_destination_square = 0;

    //check if length of source_square input is fine
    while (source_square[length_of_source_square] != '\0') {
        length_of_source_square++;
    }

    //check if length of destination_square input is fine
    while (destination_square[length_of_destination_square] != '\0') {
        length_of_destination_square++;
    }

    //print message if length of inputs are not fine
    if (length_of_source_square != 2 || length_of_destination_square != 2) {
        cout << "Invalid input in submitMove(\"" << source_square << "\", \"" << destination_square<< "\"). " 
        << "Arguments source_square and destination_square should be in the format of \"A4\", ranging from \"A1\" to \"H8\"."<< endl;
        return;
    }

    int src_row = source_square[1] - '1';
    int src_col = source_square[0] - 'A';
    int dest_row = destination_square[1] - '1';
    int dest_col = destination_square[0] - 'A';

    //ehck that the rows and columns can only range from 0 to 7
    if (src_row < 0 || src_row > 7 || src_col < 0 || src_col > 7 || dest_row < 0 || dest_row > 7 || dest_col < 0 || dest_col > 7) {
        cout << "Invalid input in submitMove(\"" << source_square << "\", \"" << destination_square<< "\"). " 
        << "Arguments source_square and destination_square should be in the format of \"A4\", ranging from \"A1\" to \"H8\"."<< endl;
        return;
    }

    //check if there is currently a chess piece in source_square
    if (current_board[src_row][src_col] == nullptr) {
        cout << "There is no piece at position " << static_cast<char>('A' + src_col) << static_cast<char>('1' + src_row) << "!" << endl;
        return;
    }

    //check if the piece at source_square is the colour of this turn's player
    if (current_board[src_row][src_col]->getColour() != this_turn_colour) {
        cout << "It is not " << colours[current_board[src_row][src_col]->getColour()] << "'s turn to move!" << endl;
        return;
    }

     //check if  destination_square is the same as source_square
    if (src_row == dest_row && src_col == dest_col) {
        cout << colours[current_board[src_row][src_col]->getColour()] << "'s " << types[current_board[src_row][src_col]->getType()] 
        << " is already currently at " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
        return;
    }

    //check for castling
    int is_castling_valid = false;
    if (current_board[src_row][src_col]->getType() == king && abs(dest_col - src_col) ==  2) {
       is_castling_valid = isCastlingValid(src_row, src_col, dest_row, dest_col);
       if (is_castling_valid == false) {
            cout << colours[current_board[src_row][src_col]->getColour()] << "'s " << types[current_board[src_row][src_col]->getType()] 
            << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
            return;
       }
    }
       
    //check if the move submitted is a valid move for the chess piece
    else if (current_board[src_row][src_col]->isLegalMove(src_row, src_col, dest_row, dest_col, *this) == false) {
        cout << colours[current_board[src_row][src_col]->getColour()] << "'s " << types[current_board[src_row][src_col]->getType()] 
        << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
        return;
    }

    //if it is a castling move, check if the king passes through a square under attack
    if (is_castling_valid == true) {
        //king moves one square in direction of destination
        if (dest_col > src_col) {
            current_board[src_row][src_col + 1] = current_board[src_row][src_col];
            current_board[src_row][src_col] = nullptr;
        }
        else if (dest_col < src_col) {
            current_board[src_row][src_col - 1] = current_board[src_row][src_col];
            current_board[src_row][src_col] = nullptr;
        }

        bool king_passes_through_check = isInCheck(this_turn_colour);
        //undo the move
        if (dest_col > src_col) {
            current_board[src_row][src_col] = current_board[src_row][src_col + 1];
            current_board[src_row][src_col + 1] = nullptr;
        }
        else if (dest_col < src_col) {
            current_board[src_row][src_col] = current_board[src_row][src_col - 1];
            current_board[src_row][src_col - 1] = nullptr;
        }

        if (king_passes_through_check == true) {
            cout << colours[current_board[src_row][src_col]->getColour()] << "'s " << types[current_board[src_row][src_col]->getType()] 
            << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
            return;
        }
    }
    
    //make the move
    ChessPiece* temp = nullptr;
    temp = current_board[dest_row][dest_col];
    current_board[dest_row][dest_col] = current_board[src_row][src_col];
    current_board[src_row][src_col] = nullptr;

    //move the rook as well if it is a castling move
    if (is_castling_valid == true) {
        if (dest_col > src_col) {
            current_board[src_row][src_col + 1] = current_board[src_row][src_col + 3];
            current_board[src_row][src_col + 3] = nullptr;
        }
        else if (dest_col < src_col) {
            current_board[src_row][src_col - 1] = current_board[src_row][src_col - 4];
            current_board[src_row][src_col - 4] = nullptr;
        }
    }

    //check if current player is in check, if so undo the move
    if (isInCheck(this_turn_colour)) {
        //undo the move
        current_board[src_row][src_col] = current_board[dest_row][dest_col];
        current_board[dest_row][dest_col] = temp;

        //undo rook move as well if it is a castling move 
        if (is_castling_valid == true) {
            if (dest_col > src_col) {
                current_board[src_row][src_col + 3] = current_board[src_row][src_col + 1];
                current_board[src_row][src_col + 1] = nullptr;
            }
            else if (dest_col < src_col) {
                current_board[src_row][src_col - 4] = current_board[src_row][src_col - 1];
                current_board[src_row][src_col - 1] = nullptr;
            }
        }
        
        cout << colours[current_board[src_row][src_col]->getColour()] << "'s " << types[current_board[src_row][src_col]->getType()] 
        << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << " as this leaves their King in check." << endl;
        return;
    }
    else {

        if (temp == nullptr) {
            cout << colours[current_board[dest_row][dest_col]->getColour()] << "'s " << types[current_board[dest_row][dest_col]->getType()] 
            << " moves from " << static_cast<char>('A' + src_col) << static_cast<char>('1' + src_row) << " to " 
            << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << endl;
        } 
        else {
            cout << colours[current_board[dest_row][dest_col]->getColour()] << "'s " << types[current_board[dest_row][dest_col]->getType()] 
            << " moves from " << static_cast<char>('A' + src_col) << static_cast<char>('1' + src_row) << " to " 
            << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row)
            << " taking " << colours[temp->getColour()] << "'s " << types[temp->getType()] << endl; 
        }

        //delete the taken piece
        delete temp;
        temp = nullptr;

        //if it is a castling move
        if (is_castling_valid) {
            if (dest_col > src_col) {
                cout << colours[current_board[src_row][src_col + 1]->getColour()] << "'s " << types[current_board[src_row][src_col + 1]->getType()] 
                << " moves from " << static_cast<char>('A' + src_col + 3) << static_cast<char>('1' + src_row) << " to " 
                << static_cast<char>('A' + src_col + 1) << static_cast<char>('1' + src_row) << " (castling implemented)" << endl;
            }
            else if (dest_col < src_col) {
                cout << colours[current_board[src_row][src_col - 1]->getColour()] << "'s " << types[current_board[src_row][src_col - 1]->getType()] 
                << " moves from " << static_cast<char>('A' + src_col - 4) << static_cast<char>('1' + src_row) << " to " 
                << static_cast<char>('A' + src_col - 1) << static_cast<char>('1' + src_row) << " (castling implemented)" << endl;
            }
        } 

    
        //check if it game over for the opponent after the current player makes his/her move
        if (isGameOver(getNextTurnColour()) == false) {
            //if not game over for opponent, check if opponent is in check
            if (isInCheck(getNextTurnColour())) {
                cout << colours[getNextTurnColour()] << " is in check" << endl;
            }
        } 
        else {
            is_game_over = true;
        }
        //switch player turns
        alternateTurns();
    }

    //if the piece which moved made its first move, record it
    if(current_board[dest_row][dest_col]->isFirstMove() == true) {
        current_board[dest_row][dest_col]->finishedFirstMove();
    }
    
}

bool ChessBoard::isCastlingValid(int src_row, int src_col, int dest_row, int dest_col) {
    if (!isInCheck(current_board[src_row][src_col]->getColour())) {
        if (current_board[src_row][src_col]->isFirstMove()) { 
            if (dest_col - src_col > 0) {
                if (current_board[src_row][src_col + 3] != nullptr) {
                    if (current_board[src_row][src_col + 3]->getType() == rook
                        && current_board[src_row][src_col + 3]->isFirstMove() == true
                        && current_board[src_row][src_col + 1] == nullptr
                        && current_board[src_row][src_col + 2] == nullptr) {
                        
                        return true;
                    } 
                }      
            }

            else if (dest_col - src_col < 0) {
                if (current_board[src_row][src_col - 4] != nullptr) {
                    if (current_board[src_row][src_col - 4]->getType() == rook 
                        && current_board[src_row][src_col - 4]->isFirstMove() == true
                        && current_board[src_row][src_col - 1] == nullptr
                        && current_board[src_row][src_col - 2] == nullptr
                        && current_board[src_row][src_col - 3] == nullptr) {
                        
                        return true;
                    } 
                }
            }
        }
    }

    return false;
}

