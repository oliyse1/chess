#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
using namespace std;

//forward declare ChessBoard class
class ChessBoard;

//type definition for colour of chess piece
enum Colour {white = 0, black};
//type definition for type of chess piece
enum Type {king = 0, rook, bishop, queen, knight, pawn};

//arrays storing string of the colour and type of chess pieces
extern char const* colours[2];
extern char const* types[6];

//abstract class ChessPiece is the base class for all types of chess piece types.
class ChessPiece {

protected:
    //each chess piece contains information on its colour and type, and whether it is the piece's first move
    Type type;
    Colour colour;
    bool is_first_move = true;
  
public:
    //constructor takes in type and colour of chess piece
    ChessPiece(Type type, Colour colour): type(type), colour(colour) {}
    //virtual destructor needed so that deleting a pointer to a base class does not cause cause undefined behaviour
    virtual ~ChessPiece(){}
    //this function returns the type of the chess piece
    Type getType() const;
    //this function returns the colour of the chess piece
    Colour getColour() const;
    //this function returns true if it is the chess piece's first move, false otherwise
    bool isFirstMove() const;
    //this functions sets is_first_move to false after the chess piece has performed its first move
    void finishedFirstMove();
    //this virtual function is overridden in all derived classes of chess piece types.
    //this function determines whether or not a move a valid based on current state of the chess board
    virtual bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) const = 0;
};

#endif