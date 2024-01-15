#include "ViewChooseAI.hpp"
#include <iostream>

ViewChooseAI::ViewChooseAI(Controller* c) : controller(c) {

    textureRandom.loadFromFile("./sprite/random.png");
    textureMinMax.loadFromFile("./sprite/minMaxIncoming.png");
    textureBack.loadFromFile("./sprite/back.png");

    spriteRandom.setTexture(textureRandom);
    spriteMinMax.setTexture(textureMinMax);
    spriteBack.setTexture(textureBack);
}



void ViewChooseAI::display(sf::RenderWindow* window) {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i positionSourisOnClick = sf::Mouse::getPosition(*window);
                if (10 <= positionSourisOnClick.x && positionSourisOnClick.x <= 225 && 775 <= positionSourisOnClick.y && positionSourisOnClick.y <= 840) {
                    return;
                }
                if (175 <= positionSourisOnClick.x && positionSourisOnClick.x <= 475) {
                    if (275 <= positionSourisOnClick.y && positionSourisOnClick.y <= 400) {
                        controller->setStrategyMinMax();
                        return;
                    }
                    if (450 <= positionSourisOnClick.y && positionSourisOnClick.y <= 575) {
                        controller->setStrategyRandom();
                        return;
                    }
                }
            }
        }
        
        window->clear(backgroundColor);

        spriteMinMax.setPosition(175, 275);
        window->draw(spriteMinMax);

        spriteRandom.setPosition(175, 450);
        window->draw(spriteRandom);

        spriteBack.setPosition(10, 775);
        window->draw(spriteBack);

        window->display();
    }
}