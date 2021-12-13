#ifndef KING_H
#define KING_H

#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//The king moves one square in any direction. 
class King : public ChessPiece {

public:
    //constructor takes in type and colour of chess piece
    King(Type type, Colour colour):ChessPiece(type, colour){}
    ~King(){}
    //this function determines whether or not a move a valid based on current state of the chess board
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const override;

};

#endif