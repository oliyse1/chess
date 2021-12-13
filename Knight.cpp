#include <iostream>
#include "Knight.h"
#include "ChessBoard.h"

using namespace std;

bool Knight::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const {
    //if destination is nullptr or a chess piece of another colour
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        //move in 'L' shaped manner
        if ((abs(dest_row - src_row) == 2 && abs(dest_col - src_col) == 1)
            || (abs(dest_row - src_row) == 1 && abs(dest_col - src_col) == 2)) {
            return true;
        }
    }
    return false;
}