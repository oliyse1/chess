#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "ChessPiece.h"
using namespace std;

//the ChessBoard class is where the user interacts with the chess pieces of a chess board.
class ChessBoard {

private:
    //colour of the current player
    Colour this_turn_colour = white;
    //a chess board which contains pointers to all chess pieces on a board
    ChessPiece* current_board[8][8] = {nullptr};
    //variable to hold the state of game
    bool is_game_over = false;
   
public:
    //no inputs needed for contructor, calls resetBoard()
    ChessBoard();
    //destructor deletes remaining pieces on the board
    ~ChessBoard();
    //this function resets the chess board for a new game
    void resetBoard();
    //this function returns the pointer to a chess piece on the chess board
    ChessPiece* getChessPiece(int row, int col) const;
    //this function returns the colour of the player who is not currently playing (not currently his/her turn)
    Colour getNextTurnColour() const;
    //this function alternates player turn
    void alternateTurns();
    //this function takes in references to a row and col variable and sets it to the position of the King on the chess board, of a specified player colour
    void getKingPosition(Colour colour, int& row, int& col);
    //this function checks if the player of a specified colour is in check
    bool isInCheck(Colour colour);
    //this function checks if a player of a specified colour has any valid moves across the whole chess board
    bool canMove(Colour colour);
    //this function checks if it a player of a specified colour is in checkmate or if the game is in stalemate
    bool isGameOver(Colour colour);
    //this function allows the player to interact with the check pieces on the chess board. source_sqaure and destination_square need to be in the format/range of "A1" to "H8"
    void submitMove(char const* source_square, char const* destination_square);
    //this function checks if a castling move is valid
    bool isCastlingValid(int src_row, int src_col, int dest_row, int dest_col);
    
};


#endif
