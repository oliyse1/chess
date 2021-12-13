#include <iostream>
#include "Queen.h"
#include "ChessBoard.h"

using namespace std;

bool Queen::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const {
    //if destination is nullptr or a chess piece of another colour
     if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        
        //if destination is same row
        if (src_row == dest_row) {
            if (src_col < dest_col) {
                //if there are any chess pieces in between the queen and the destination
                for (int col = src_col + 1; col < dest_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }
            } 
            else if (src_col > dest_col) {
                //if there are any chess pieces in between the queen and the destination
                for (int col = dest_col + 1; col < src_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }
            }
            return true;
        }

        //if destination is same column
        if (src_col == dest_col) {
            if (src_row < dest_row) {
                //if there are any chess pieces in between the queen and the destination
                for (int row = src_row + 1; row < dest_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }
            } 
            else if (src_row > dest_row) {
                for (int row = dest_row + 1; row < src_row; row++) {
                    //if there are any chess pieces in between the queen and the destination
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }
            }
            return true;
        }

        //if it is a diagonal move
        if (abs(dest_row - src_row) == abs(dest_col - src_col) && (dest_row - src_row) != 0) {
            if (dest_row > src_row) {
                //direction of destination is top right
                if(dest_col > src_col) {
                    //if there are any chess pieces in between the queen and the destination
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col + i) != nullptr) {
                            return false;
                        }
                    }
                }
                //direction of destination is top left
                else if (dest_col < src_col) {
                    //if there are any chess pieces in between the queen and the destination
                    for (int i = 1; i < (src_col - dest_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col - i) != nullptr) {
                            return false;
                        }
                    }
                }
                return true;
            }
            else if (src_row > dest_row) {
                //direction of destination is bottom right
                if(dest_col > src_col) {
                    //if there are any chess pieces in between the queen and the destination
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col + i) != nullptr) {
                            return false;
                        }
                    }
                }
                //direction of destination is bottom left
                else if (dest_col < src_col) {
                    //if there are any chess pieces in between the queen and the destination
                    for (int i = 1; i < (src_col - dest_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col - i) != nullptr) {
                            return false;
                        }
                    }
                }
                return true;
            }
        }       
    }
    
    return false;

}