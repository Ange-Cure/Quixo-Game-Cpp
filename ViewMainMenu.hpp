#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class ViewMainMenu
{
private:
    Controller* controller;
    sf::Color backgroundColor = sf::Color(37, 31, 46);

    sf::Texture texturePlayerVsPlayer;
    sf::Texture texturePlayerVsAI;
    sf::Texture textureChooseAI;

    sf::Sprite spritePlayerVsPlayer;
    sf::Sprite spritePlayerVsAI;
    sf::Sprite spriteChooseAI;

public:
    ViewMainMenu(Controller*);
    void display(sf::RenderWindow* window);
};