#include <iostream>
#include "Rook.h"
#include "ChessBoard.h"

using namespace std;

bool Rook::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const {
    //if destination is nullptr or a chess piece of another colour
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        
        //if destination is same row
        if (src_row == dest_row) {
            if (src_col < dest_col) {
                //if there are any chess pieces in between the rook and the destination
                for (int col = src_col + 1; col < dest_col; col++) {
                    if (chessBoard.getChessPiece(src_row, col) != nullptr) {
                        return false;
                    }
                }
            } 
            else if (src_col > dest_col) {
                //if there are any chess pieces in between the rook and the destination
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
                //if there are any chess pieces in between the rook and the destination
                for (int row = src_row + 1; row < dest_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }
            } 
            else if (src_row > dest_row) {
                //if there are any chess pieces in between the rook and the destination
                for (int row = dest_row + 1; row < src_row; row++) {
                    if (chessBoard.getChessPiece(row, src_col) != nullptr) {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    return false;
    
}
