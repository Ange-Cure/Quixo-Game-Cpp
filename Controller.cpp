#include "Controller.hpp"
#include "View.hpp"

Controller::Controller(View* v) : view(v) {}

void Controller::run() {
    view->display(model.getBoard(), model.getCurrentPlayer(), model.isGameSolve());
}

std::vector<std::vector<int>> Controller::click(int x, int y) {
    return model.click(x, y);
}

