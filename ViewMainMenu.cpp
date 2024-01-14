#include "ViewMainMenu.hpp"
#include "Controller.hpp"
#include <iostream>

ViewMainMenu::ViewMainMenu(Controller* c) : controller(c) {

    texturePlayerVsPlayer.loadFromFile("./sprite/playervsplayer.png");
    texturePlayerVsAI.loadFromFile("./sprite/playervsai.png");
    textureChooseAI.loadFromFile("./sprite/chooseai.png");

    spritePlayerVsPlayer.setTexture(texturePlayerVsPlayer);
    spritePlayerVsAI.setTexture(texturePlayerVsAI);
    spriteChooseAI.setTexture(textureChooseAI);
}



void ViewMainMenu::display(std::vector<std::vector<int>> board, std::unique_ptr<GameState>& currentState, sf::RenderWindow* window) {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i positionSourisOnClick = sf::Mouse::getPosition(*window);
                if (175 <= positionSourisOnClick.x && positionSourisOnClick.x <= 475) {
                    if (190 <= positionSourisOnClick.y && positionSourisOnClick.y <= 315) {
                        controller->changeViewPlayerVsPlayer();
                    }
                    if (365 <= positionSourisOnClick.y && positionSourisOnClick.y <= 485) {
                        controller->changeViewPlayerVsAI();
                    }
                    if (535 <= positionSourisOnClick.y && positionSourisOnClick.y <= 655) {
                        controller->changeViewChooseAI();
                    }
                }
            }
        }
        
        window->clear(backgroundColor);

        spritePlayerVsPlayer.setPosition(175, 191);
        window->draw(spritePlayerVsPlayer);

        spritePlayerVsAI.setPosition(175, 364);
        window->draw(spritePlayerVsAI);

        spriteChooseAI.setPosition(175, 536);
        window->draw(spriteChooseAI);

        window->display();
    }
}