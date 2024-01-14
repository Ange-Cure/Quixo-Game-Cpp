all: test

test: 
	g++ -c main.cpp 
	g++ main.o Model.cpp View.cpp ViewMainMenu.cpp Controller.cpp Player1SelectPieceState.cpp Player1PlacePieceState.cpp Player2SelectPieceState.cpp Player2PlacePieceState.cpp EndGamePlayer1State.cpp EndGamePlayer2State.cpp -o Quixo -lsfml-graphics -lsfml-window -lsfml-system
	./Quixo

clean:
	rm -rf *.o
	rm Quixo

