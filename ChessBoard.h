#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <vector>


using namespace std;

enum Colour {white = 0, black};
extern char const* colours[2];
enum Type {king = 0, rook, bishop, queen, knight, pawn};
extern char const* types[6];


class ChessBoard;

class ChessPiece {

protected:
    Type type;
    Colour colour;
    // Location location;


public:

    ChessPiece(Type type, Colour colour);
    //need virtual destructor, if not deleting a pointer to a base class might cause undefined behaviour
    virtual ~ChessPiece(){}
    Type getType() const;
    Colour getColour() const;
    // Location getCurrentLocation() const;
    // void setCurrentLocation(char const* location_string);
    virtual bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) = 0;
};

class ChessBoard {

private:
    Colour this_turn_colour = white;
    ChessPiece* current_board[8][8];
    bool in_check = false;
   

public:
    ChessBoard();
    void resetBoard();
    ChessPiece* getChessPiece(int row, int col);
    void setChessPiece(ChessPiece* chessPiece, int row, int col);
    void submitMove(char const* source_square, char const* destination_square);
    bool isOccupied(int row, int col);
    void reset();
    void alternateTurns();
    bool isInCheck(Colour colour);
    Colour getNextTurnColour();
    bool canMove(Colour colour);
    bool isGameOver(Colour colour);
    void getKingPosition(Colour colour, int& row, int& col);
    

};



class King : public ChessPiece {

public:
    King(Type type, Colour colour):ChessPiece(type, colour){}
    ~King(){}
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) override;

};

class Rook : public ChessPiece {

public:
    Rook(Type type, Colour colour):ChessPiece(type, colour){}
    ~Rook(){}
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) override;
};

class Bishop : public ChessPiece {

public:
    Bishop(Type type, Colour colour):ChessPiece(type, colour){}
    ~Bishop(){}
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) override;
};

class Queen : public ChessPiece {

public:
    Queen(Type type, Colour colour):ChessPiece(type, colour){}
    ~Queen(){}
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) override;
};

class Knight : public ChessPiece {

public:
    Knight(Type type, Colour colour):ChessPiece(type, colour){}
    ~Knight(){}
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) override;
};

class Pawn : public ChessPiece {
    //need to be set to false after first move
    bool is_first_move = true;

public:
    Pawn(Type type, Colour colour):ChessPiece(type, colour){}
    ~Pawn(){}
    bool isLegalMove(int src_row, int src_col, int dest_row, int dest_col, ChessBoard& chessBoard) override;
    bool isFirstMove();
    void finishedFirstMove();

};



#endif
