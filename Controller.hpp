#pragma once
#include "Model.hpp"
#include <SFML/Graphics.hpp>

class Controller
{
private:
    Model* model;
    sf::RenderWindow* window;

public:
    Controller();
    std::unique_ptr<GameState>& getCurrentState();
    std::vector<std::vector<int>> getBoard();
    void run();
    void changeViewPlayerVsPlayer();
    void changeViewPlayerVsAI();
    void changeViewChooseAI();
    void click(int, int);
    void resetGame();
    void setStrategyMinMax();
    void setStrategyRandom();
    void executeAI();
};

