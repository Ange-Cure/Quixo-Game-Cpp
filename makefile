all:test

test:
	g++ -c main.cpp
	g++ main.o -o Quixo -lsfml-graphics -lsfml-window -lsfml-system
	./Quixo