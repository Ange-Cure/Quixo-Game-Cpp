#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class ViewChooseAI
{
private:
    Controller* controller;
    sf::Color backgroundColor = sf::Color(37, 31, 46);

    sf::Texture textureRandom;
    sf::Texture textureMinMax;
    sf::Texture textureBack;

    sf::Sprite spriteRandom;
    sf::Sprite spriteMinMax;
    sf::Sprite spriteBack;

public:
    ViewChooseAI(Controller*);
    void display(sf::RenderWindow* window);
};