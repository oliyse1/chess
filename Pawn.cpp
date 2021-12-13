#include <iostream>
#include "Pawn.h"
#include "ChessBoard.h"

using namespace std;

bool Pawn::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const {
    //if destination is nullptr
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr) {
        //if current player is white
        if (this->getColour() == white) {
            //one square forward in the same column
            if (dest_col == src_col && (dest_row - src_row) == 1) {
                return true;
            } 
            //2 sqares forward if it is the pawn's first move
            else if (dest_col == src_col && (dest_row - src_row) == 2 && isFirstMove() == true) {
                //if there is a chess piece in between the pawn and the destination
                if (chessBoard.getChessPiece(src_row + 1, src_col) != nullptr) {
                    return false;
                }
                return true;
            }
        }
        //if current player is black
        else {
            //one square forward in the same column
            if (dest_col == src_col && (dest_row - src_row) == -1) {
                return true;
            } 
            //2 sqares forward if it is the pawn's first move
            else if (dest_col == src_col && (dest_row - src_row) == -2 && isFirstMove() == true) {
                //if there is a chess piece in between the pawn and the destination
                if (chessBoard.getChessPiece(src_row - 1, src_col) != nullptr) {
                    return false;
                }
                return true;
            }
        }
    } 
    //if destination is a chess piece of another colour
    else if (chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        //if current player is white
        if (this->getColour() == white) {
            //one square forward diagonally
            if ((dest_row - src_row) == 1 && abs(dest_col - src_col) == 1) {
                return true;
            }
        }
        //if current player is black
        else {
            //one square forward diagonally
            if ((dest_row - src_row) == -1 && abs(dest_col - src_col) == 1) {
                return true;
            }
        }
    }

    return false;
}