#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//The knight moves to any of the closest squares that are not on the same row, column, or diagonal, 
//thus the move forms an 'L'-shape: two squares vertically and one square horizontally, or two squares horizontally and one square vertically. 
//The knight is the only piece that can leap over other pieces.
class Knight : public ChessPiece {

public:
    //constructor takes in type and colour of chess piece
    Knight(Type type, Colour colour):ChessPiece(type, colour){}
    ~Knight(){}
    //this function determines whether or not a move a valid based on current state of the chess board
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const override;
};

#endif