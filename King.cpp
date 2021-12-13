#include <iostream>
#include "King.h"
#include "ChessBoard.h"

using namespace std;

bool King::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const {
    //if destination is nullptr or a chess piece of another colour
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        if((abs(dest_row - src_row) == 1 && abs(dest_col - src_col) == 0) //one step vertically
        || (abs(dest_row - src_row) == 0 && abs(dest_col - src_col) == 1)  //one step horizontally
        || (abs(dest_row - src_row) == 1 && abs(dest_col - src_col) == 1)) { //one step diagonally
            return true;
        } 
    } 
    return false;
}