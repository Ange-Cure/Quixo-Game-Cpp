#include "Random.hpp"
#include "Model.hpp"
#include <iostream>
#include <ctime>

void Random::execute(Model& model) {
    std::srand(std::time(0));
    while (model.currentState->getState() == 2) {
        int border = rand() % 4;
        int row, column;

        switch (border) {
            case 0:
                row = 0;
                column = rand() % 5;
                break;
            case 1:
                row = 5 - 1;
                column = rand() % 5;
                break;
            case 2:
                row = rand() % 5;
                column = 0;
                break;
            case 3:
                row = rand() % 5;
                column = 5 - 1;
                break;
        }

        model.click(row, column);
    }
}