#include <iostream>
#include "ChessPiece.h"

using namespace std;


//definition of arrays which hold the colour and types of chess pieces
char const* colours[2] = {"White" , "Black"};
char const* types[6] = {"King", "Rook", "Bishop", "Queen", "Knight", "Pawn"};

Type ChessPiece::getType() const {
    return type;
}

Colour ChessPiece::getColour() const {
    return colour;
}

bool ChessPiece::isFirstMove() const {
    return is_first_move;
}

void ChessPiece::finishedFirstMove() {
    is_first_move = false;
}