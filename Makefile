chess: ChessMain.o ChessPiece.o King.o Rook.o Bishop.o Queen.o Knight.o Pawn.o ChessBoard.o
	g++ ChessMain.o ChessPiece.o King.o Rook.o Bishop.o Queen.o Knight.o Pawn.o ChessBoard.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -Wall -g -c ChessPiece.cpp

King.o: King.cpp King.h ChessPiece.h
	g++ -Wall -g -c King.cpp

Rook.o: Rook.cpp Rook.h ChessPiece.h
	g++ -Wall -g -c Rook.cpp

Bishop.o: Bishop.cpp Bishop.h ChessPiece.h
	g++ -Wall -g -c Bishop.cpp

Queen.o: Queen.cpp Queen.h ChessPiece.h
	g++ -Wall -g -c Queen.cpp

Knight.o: Knight.cpp Knight.h ChessPiece.h
	g++ -Wall -g -c Knight.cpp

Pawn.o: Pawn.cpp Pawn.h ChessPiece.h
	g++ -Wall -g -c Pawn.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp

.PHONY: clean
clean:
	rm -f *.o chess
