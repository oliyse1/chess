#include <iostream>
#include "Bishop.h"
#include "ChessBoard.h"

using namespace std;

bool Bishop::isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const {
    //if destination is nullptr or a chess piece of another colour
    if (chessBoard.getChessPiece(dest_row, dest_col) == nullptr || chessBoard.getChessPiece(dest_row, dest_col)->getColour() != this->getColour()) {
        //if it is a diagonal move
        if (abs(dest_row - src_row) == abs(dest_col - src_col) && (dest_row - src_row) != 0) {
            if (dest_row > src_row) {
                //direction of destination is top right
                if(dest_col > src_col) {
                    //if there are any chess pieces in between the bishop and the destination
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row + i, src_col + i) != nullptr) {
                            return false;
                        }
                    }
                }
                //direction of destination is top left
                else if (dest_col < src_col) {
                    //if there are any chess pieces in between the bishop and the destination
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
                    //if there are any chess pieces in between the bishop and the destination
                    for (int i = 1; i < (dest_col - src_col); i++) {
                        if (chessBoard.getChessPiece(src_row - i, src_col + i) != nullptr) {
                            return false;
                        }
                    }
                }
                //direction of destination is bottom left
                else if (dest_col < src_col) {
                    //if there are any chess pieces in between the bishop and the destination
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