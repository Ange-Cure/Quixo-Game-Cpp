#include "Controller.hpp"
#include "View.hpp"
#include "ViewMainMenu.hpp"
#include "ViewChooseAI.hpp"

Controller::Controller() {
    model = new Model();
    window = new sf::RenderWindow(sf::VideoMode(650, 850), "Quixo", sf::Style::Titlebar | sf::Style::Close);
}

std::unique_ptr<GameState>& Controller::getCurrentState() {
    return model->currentState;
}

std::vector<std::vector<int>> Controller::getBoard() {
    return model->getBoard();
}

void Controller::run() {
    ViewMainMenu view(this);
    view.display(window);
}

void Controller::changeViewPlayerVsPlayer() {
    View view(this, false);
    view.display(window);
}

void Controller::changeViewPlayerVsAI() {
    View view(this, true);
    view.display(window);
}

void Controller::changeViewChooseAI() {
    ViewChooseAI view(this);
    view.display(window);
}

void Controller::click(int x, int y) {
    model->click(x, y);
}

void Controller::resetGame() {
    model->resetGame();
}

void Controller::setStrategyMinMax() {
    model->setStrategyMinMax();
}

void Controller::setStrategyRandom() {
    model->setStrategyRandom();
}

void Controller::executeAI() {
    model->executeAI();
}


