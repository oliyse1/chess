#include <iostream>
#include <vector>
#include "ChessBoard.h"


char const* colours[2] = {"White" , "Black"};
char const* types[6] = {"King", "Rook", "Bishop", "Queen", "Knight", "Pawn"};


ChessPiece::ChessPiece(Type type, Colour colour) {
    this->type = type;
    this->colour = colour;
    // this->location.row = location_string[1] - '1';
    // this->location.col = location_string[0] - 'A';
}

// ChessPiece::~ChessPiece() 
// {

// }

Type ChessPiece::getType() const {
    return type;
}

Colour ChessPiece::getColour() const {
    return colour;
}

// bool ChessPiece::isValidDestination(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard){
//     return true;
// }

// Location ChessPiece::getCurrentLocation() const {
//     return location;
// }

// void ChessPiece::setCurrentLocation(char const* location_string) {
//     this->location.row = location_string[1] - '1';
//     this->location.col = location_string[0] - 'A';

// }

ChessBoard::ChessBoard() {
    resetBoard();
}

void ChessBoard::resetBoard() {

    cout << "A new chess game is started!" << endl << endl;

    this_turn_colour = white;

    //delete all existing pieces on the board and set all squares to nullptr
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
           
            current_board[row][col] = nullptr;
            
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

// ChessPiece ChessBoard::getCurrentBoard() const {
//     return current_board;
// }

ChessPiece* ChessBoard::getChessPiece(int row, int col) {
    // if(current_board[row][col] != nullptr) {
        return current_board[row][col];
    // }
    // else {
    //     cerr << "no chesspiece in this location " << row << "," << col << endl;
    //     throw(1);
    // }
    
}

void ChessBoard::setChessPiece(ChessPiece* chessPiece, int row, int col){
    current_board[row][col] = chessPiece;
}

void ChessBoard::alternateTurns() {
    if (this_turn_colour == white) {
        this_turn_colour = black;
    }
    else {
        this_turn_colour = white;
    }
}

void ChessBoard::submitMove(char const* source_square, char const* destination_square) {
    int src_row = source_square[1] - '1';
    int src_col = source_square[0] - 'A';
    int dest_row = destination_square[1] - '1';
    int dest_col = destination_square[0] - 'A';

    if (src_row < 0 || src_row > 7 || src_col < 0 || src_col > 7 || dest_row < 0 || dest_row > 7 || dest_col < 0 || dest_col > 7 || (src_row == dest_row && src_col == dest_col)) {
        cout << colours[getChessPiece(src_row, src_col)->getColour()] << "'s " << types[getChessPiece(src_row, src_col)->getType()] 
        << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
        return;
    }


    if (getChessPiece(src_row, src_col) == nullptr) {
        cout << "There is no piece at position " << static_cast<char>('A' + src_col) << static_cast<char>('1' + src_row) << "!" << endl;
        return;
    }

    if (getChessPiece(src_row, src_col)->getColour() != this_turn_colour) {
        cout << "It is not " << colours[getChessPiece(src_row, src_col)->getColour()] << "'s turn to move!" << endl;
        return;
    
    }

    if (getChessPiece(src_row, src_col)->isLegalMove(src_row, src_col, dest_row, dest_col, *this) == false) {
        cout << colours[getChessPiece(src_row, src_col)->getColour()] << "'s " << types[getChessPiece(src_row, src_col)->getType()] 
        << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
        return;
    }

    else { //make the move

        ChessPiece* temp = nullptr;
        temp = current_board[dest_row][dest_col];
        current_board[dest_row][dest_col] = current_board[src_row][src_col];
        current_board[src_row][src_col] = nullptr;

        //check if current player is in check, if so undo the move
        if (isInCheck(this_turn_colour)) {
            //undo the move
            current_board[src_row][src_col] = current_board[dest_row][dest_col];
            current_board[dest_row][dest_col] = temp;

            cout << colours[getChessPiece(src_row, src_col)->getColour()] << "'s " << types[getChessPiece(src_row, src_col)->getType()] 
            << " cannot move to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << "!" << endl;
            return;
        }
        else {

            if (temp == nullptr) {
                cout << colours[getChessPiece(dest_row, dest_col)->getColour()] << "'s " << types[getChessPiece(dest_row, dest_col)->getType()] 
                << " moves from " << static_cast<char>('A' + src_col) << static_cast<char>('1' + src_row) << " to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row) << endl;
            } 
            else {
                cout << colours[getChessPiece(dest_row, dest_col)->getColour()] << "'s " << types[getChessPiece(dest_row, dest_col)->getType()] 
                << " moves from " << static_cast<char>('A' + src_col) << static_cast<char>('1' + src_row) << " to " << static_cast<char>('A' + dest_col) << static_cast<char>('1' + dest_row)
                << " taking " << colours[temp->getColour()] << "'s " << types[temp->getType()] << endl; 
            }

            delete temp;
            temp = nullptr;

            if (isGameOver(getNextTurnColour()) == false) {
                if (isInCheck(getNextTurnColour())) {
                    cout << colours[getNextTurnColour()] << " is in check" << endl;
                }
            }

            alternateTurns();
        }

        if (getChessPiece(dest_row, dest_col)->getType() == pawn) {
            Pawn* pawn = (Pawn*)getChessPiece(dest_row, dest_col);
            if(pawn->isFirstMove() == true) {
                pawn->finishedFirstMove();
            }
        }
    } 

   
    
}

void ChessBoard::getKingPosition(Colour colour, int& king_row, int& king_col) {
    for (king_row = 0; king_row < 8; king_row++) {
        for (king_col = 0; king_col < 8; king_col++) {
            if(getChessPiece(king_row, king_col) != nullptr) {
                if(getChessPiece(king_row, king_col)->getType() == king && getChessPiece(king_row, king_col)->getColour() == colour) {
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

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if(getChessPiece(row, col) != nullptr) {
                if(getChessPiece(row, col)->isLegalMove(row, col, king_row, king_col, *this)) {
                    
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
            if (getChessPiece(row, col) != nullptr && getChessPiece(row, col)->getColour() == colour) {
                for (int move_row = 0 ; move_row < 8; move_row++) {
                    for (int move_col = 0; move_col < 8; move_col++) {
                        if (getChessPiece(row, col)->isLegalMove(row, col, move_row, move_col, *this)) {
                            ChessPiece* temp = current_board[move_row][move_col];
                            current_board[move_row][move_col] = current_board[row][col];
                            current_board[row][col] = nullptr;
                            bool is_in_check = isInCheck(colour);
                            //undo the move
                             current_board[row][col] = current_board[move_row][move_col];
                             current_board[move_row][move_col] = temp;
                             if (is_in_check == false) {
                                 return true;
                             }
                        }
                    }
                }
            }
        }
    }
    cout << "false in game canMove" << endl;

    return false;

}

bool ChessBoard::isGameOver(Colour colour) {
    if(!canMove(colour)) {
        if (isInCheck(colour)) {
            cout << colours[colour] << " is in checkmate" << endl;
        } 
        else {
            cout << "Stalemate!" << endl;
        }

        return true;
    } 

    return false;
}

// Status ChessBoard::isLegalMove(int src_row, int src_col, int dest_row, int dest_col) {

//     //if the destination is valid
//     if (getChessPiece(src_row, src_col)->isValidDestination(src_row, src_col, dest_row, dest_col, *this) == true) {

        
//         if (current_board[dest_row][dest_col] == nullptr) {

//             //make the move
//             current_board[dest_row][dest_col] = current_board[src_row][src_col];
//             current_board[src_row][src_col] = nullptr;

//             //check if in check
//             if (isInCheck(getNextTurnColour())) {

//                 int king_row, king_col;
//                 for (king_row = 0; king_row < 8; king_row++) {
//                     for (king_col = 0; king_col < 8; king_col++) {
//                         if(getChessPiece(king_row, king_col)->getType() == king && getChessPiece(king_row, king_col)->getColour() == getNextTurnColour()) {
//                             break;
//                         }
//                     }
//                 }
                
//                 //check if is chackmate
//                 for (int row = 0; row < 8; row++) {
//                     for (int col = 0; col < 8; col++) {
//                         if(isLegalMove(king))
//                     }
//                 }



//                 return check;
//             }

//             if(isInCheck(this_turn_colour)) {

//                 if()



//                 //undo move
//                 current_board[src_row][src_col] = current_board[dest_row][dest_col];
//                 current_board[dest_row][dest_col] = nullptr;
//                 return false;
//             }
//             else {
//                 //undo move
//                 current_board[src_row][src_col] = current_board[dest_row][dest_col];
//                 current_board[dest_row][dest_col] = nullptr;
//                 return true;
//             }
//         } 
//         else {

//             ChessPiece* temp =  current_board[dest_row][dest_col];
//             current_board[dest_row][dest_col] = current_board[src_row][src_col];
//             current_board[src_row][src_col] = nullptr; 
        
//             if(isInCheck(this_turn_colour)) {
//                 //undo move
//                 current_board[src_row][src_col] = current_board[dest_row][dest_col];
//                 current_board[dest_row][dest_col] = temp;
//                 temp = nullptr;
//                 return false;
//             }
//             else {
//                 //undo move
//                 current_board[src_row][src_col] = current_board[dest_row][dest_col];
//                 current_board[dest_row][dest_col] = temp;
//                 temp = nullptr;
//                 return true;
//             }
//         }
//     }
//     else {
//         return no;
//     }
// }

Colour ChessBoard::getNextTurnColour() {
    if (this_turn_colour == white) {
        return black;
    }
    else {
        return white;
    }
}

// bool Pawn::isValidDestination(Location& source, Location& destination, ChessPiece current_board[8][8]) {
//     if (current_board[destination.row][destination.col] == 0) {
        
//         if (this->getColour() == white) {
//             if ((destination.row - source.row) == 1 && destination.col == source.col) {
//             return true;
//             }
//             else {
//                 return false;

//         }
        
//     }



//     }
   
// }

bool King::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) {
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        if(abs(dest_row - src_row) == 1 || abs(dest_col - src_col) == 1) {
            return true;
        } 
    } 
    return false;
}

bool Rook::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) {
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        
        //if same row
        if (src_row == dest_row) {
            if (src_col < dest_col) {
                for (int col = src_col + 1; col < dest_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }

                return true;

            } else if (src_col > dest_col) {
                for (int col = dest_col + 1; col < src_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }

                return true;
            }
        }

        //if same col
        if (src_col == dest_col) {
            if (src_row < dest_row) {
                for (int row = src_row + 1; row < dest_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }

                return true;

            } else if (src_row > dest_row) {
                for (int row = dest_row + 1; row < src_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }

                return true;
            }
        }

    }
    

    return false;


}


bool Bishop::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) {
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
     
        if (abs(dest_row - src_row) == abs(dest_col - src_col) && (dest_row - src_row) != 0) {
            if (dest_row > src_row) {
                if(dest_col > src_col) {
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col + i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
                else if (dest_col < src_col) {
                    for (int i = 1; i < (src_col - dest_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col - i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
            }
            else if (src_row > dest_row) {
                if(dest_col > src_col) {
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col + i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
                else if (dest_col < src_col) {
                    for (int i = 1; i < (src_col - dest_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col - i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
            }
        }       
    }

    return false;

}

bool Queen::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) {
     if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        
        //if same row
        if (src_row == dest_row) {
            if (src_col < dest_col) {
                for (int col = src_col + 1; col < dest_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }

                return true;

            } else if (src_col > dest_col) {
                for (int col = dest_col + 1; col < src_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }

                return true;
            }
        }

        //if same col
        if (src_col == dest_col) {
            if (src_row < dest_row) {
                for (int row = src_row + 1; row < dest_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }

                return true;

            } else if (src_row > dest_row) {
                for (int row = dest_row + 1; row < src_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }

                return true;
            }
        }

        if (abs(dest_row - src_row) == abs(dest_col - src_col) && (dest_row - src_row) != 0) {
            if (dest_row > src_row) {
                if(dest_col > src_col) {
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col + i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
                else if (dest_col < src_col) {
                    for (int i = 1; i < (src_col - dest_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col - i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
            }
            else if (src_row > dest_row) {
                if(dest_col > src_col) {
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col + i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
                else if (dest_col < src_col) {
                    for (int i = 1; i < (src_col - dest_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col - i) != nullptr) {
                            return false;
                        }
                    }

                    return true;
                }
            }
        }       

    }
    

    return false;

}

bool Knight::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) {
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        if (abs(dest_row - src_row) == 2 && abs(dest_col - src_col) == 1) {
           return true;
        }
        else if (abs(dest_row - src_row) == 1 && abs(dest_col - src_col) == 2) {
            return true;
        }
    }
    return false;
}

bool Pawn::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) {
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr) {
        if (this->getColour() == white) {
            if (dest_col == src_col && (dest_row - src_row) == 1) {
                return true;
            } 
            else if (dest_col == src_col && (dest_row - src_row) == 2 && isFirstMove() == true) {
                if (chessBoard.getChessPiece(src_row + 1, src_col) != nullptr) {
                    return false;
                }
                return true;
            }
        }
        else {
            if (dest_col == src_col && (dest_row - src_row) == -1) {
                return true;
            } 
            else if (dest_col == src_col && (dest_row - src_row) == -2 && isFirstMove() == true) {
                if (chessBoard.getChessPiece(src_row - 1, src_col) != nullptr) {
                    return false;
                }
                return true;
            }
        }

    } 
    else if (chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        if (this->getColour() == white) {
            if ((dest_row - src_row) == 1 && abs(dest_col - src_col) == 1) {
                return true;
            }
        }
        else {
            if ((dest_row - src_row) == -1 && abs(dest_col - src_col) == 1) {
                return true;
            }
        }
    }

    return false;
}

bool Pawn::isFirstMove() {
    return is_first_move;
}

void Pawn::finishedFirstMove() {
    is_first_move = false;
}

