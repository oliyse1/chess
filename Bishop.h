#ifndef BISHOP_H
#define BISHOP_H

#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//The bishop can move any number of squares diagonally, but may not leap over other pieces.
class Bishop : public ChessPiece {

public:
    //constructor takes in type and colour of chess piece
    Bishop(Type type, Colour colour):ChessPiece(type, colour){}
    ~Bishop(){}
    //this function determines whether or not a move a valid based on current state of the chess board
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const override;
};

#endif