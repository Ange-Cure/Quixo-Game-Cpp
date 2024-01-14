#include "Controller.hpp"
#include "View.hpp"
#include "ViewMainMenu.hpp"

Controller::Controller() {
    window = new sf::RenderWindow(sf::VideoMode(650, 850), "Quixo", sf::Style::Titlebar | sf::Style::Close);
}

std::unique_ptr<GameState>& Controller::getCurrentState() {
    return model.currentState;
}

std::vector<std::vector<int>> Controller::getBoard() {
    return model.getBoard();
}

void Controller::run() {
    ViewMainMenu view(this);
    view.display(model.getBoard(), model.currentState, window);
}

void Controller::changeViewPlayerVsPlayer() {
    View view(this);
    view.display(window);
}

void Controller::changeViewPlayerVsAI() {
    View view(this);
    view.display(window);
}

void Controller::changeViewChooseAI() {
    View view(this);
    view.display(window);
}

void Controller::click(int x, int y) {
    model.click(x, y);
}

void Controller::resetGame() {
    model.resetGame();
}


