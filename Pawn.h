#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "ChessPiece.h"
#include "ChessBoard.h"
using namespace std;

//The pawn may move forward to the unoccupied square immediately in front of it on the same column;
//or on its first move it may advance two squares along the same column provided both squares are unoccupied; 
//or it may move to a square occupied by an opponent's piece which is diagonally in front of it on an adjacent column, capturing that piece.
class Pawn : public ChessPiece {
    
public:
    //constructor takes in type and colour of chess piece
    Pawn(Type type, Colour colour):ChessPiece(type, colour){}
    ~Pawn(){}
    //this function determines whether or not a move a valid based on current state of the chess board
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const override;
   
};

#endif