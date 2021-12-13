#ifndef ROOK_H
#define ROOK_H

#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//The rook (or castle) can move any number of squares along any row or column, but may not leap over other pieces.
class Rook : public ChessPiece {

public:
    //constructor takes in type and colour of chess piece
    Rook(Type type, Colour colour):ChessPiece(type, colour){}
    ~Rook(){}
    //this function determines whether or not a move a valid based on current state of the chess board
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const override;
};

#endif