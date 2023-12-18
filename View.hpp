#pragma once
#include "Controller.hpp"
#include <SFML/Graphics.hpp>

class View
{
private:
    Controller* controller;

    sf::RenderWindow window;
    int spriteSize = 120;
    int x_offset = 25;
    int y_offset = 25;
    int x_screen_size = (x_offset * 2) + (spriteSize * 5);
    int y_screen_size = (y_offset * 2) + (spriteSize * 5) + 150;
    sf::Color backgroundColor = sf::Color(37, 31, 46);
    
    sf::Texture textureEmpty;
    sf::Texture textureRond;
    sf::Texture textureCroix;
    sf::Texture textureEmptyPlayable;
    sf::Texture textureRondPlayable;
    sf::Texture textureCroixPlayable;


    sf::Sprite spriteEmpty;
    sf::Sprite spriteRond;
    sf::Sprite spriteCroix;
    sf::Sprite spriteEmptyPlayable;
    sf::Sprite spriteRondPlayable;
    sf::Sprite spriteCroixPlayable;

public:
    View(Controller*);
    void display(std::vector<std::vector<int>>, int, int);
};

