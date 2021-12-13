#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//The queen combines the power of the rook and bishop and can move any number of squares along row, column, or diagonal, but it may not leap over other pieces.
class Queen : public ChessPiece {

public:
    //constructor takes in type and colour of chess piece
    Queen(Type type, Colour colour):ChessPiece(type, colour){}
    ~Queen(){}
    //this function determines whether or not a move a valid based on current state of the chess board
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const override;
};

#endif