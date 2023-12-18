all:test

test:
	g++ -c main.cpp Model.cpp View.cpp Controller.cpp
	g++ main.o View.o Model.o Controller.o -o Quixo -lsfml-graphics -lsfml-window -lsfml-system
	./Quixo