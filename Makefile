chess: ChessMain.o ChessBoard.o
	g++ ChessMain.o ChessBoard.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp

.PHONY: clean
clean:
	rm -f ChessMain.o ChessBoard.o chess
