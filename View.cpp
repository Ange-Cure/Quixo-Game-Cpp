#include "View.hpp"
#include "Controller.hpp"
#include <iostream>

View::View(Controller* c) : controller(c) {
    textureEmpty.loadFromFile("./sprite/empty.png");
    textureRond.loadFromFile("./sprite/rond.png");
    textureCroix.loadFromFile("./sprite/croix.png");
    textureEmptyPlayable.loadFromFile("./sprite/emptyPlayable.png");
    textureRondPlayable.loadFromFile("./sprite/rondPlayable.png");
    textureCroixPlayable.loadFromFile("./sprite/croixPlayable.png");
    textureBack.loadFromFile("./sprite/back.png");
    textureCroixVictory.loadFromFile("./sprite/croixVictory.png");
    textureRondVictory.loadFromFile("./sprite/rondVictory.png");
    texturePlayAgain.loadFromFile("./sprite/playAgain.png");

    spriteEmpty.setTexture(textureEmpty);
    spriteRond.setTexture(textureRond);
    spriteCroix.setTexture(textureCroix);
    spriteEmptyPlayable.setTexture(textureEmptyPlayable);
    spriteRondPlayable.setTexture(textureRondPlayable);
    spriteCroixPlayable.setTexture(textureCroixPlayable);
    spriteBack.setTexture(textureBack);
    spriteCroixVictory.setTexture(textureCroixVictory);
    spriteRondVictory.setTexture(textureRondVictory);
    spritePlayAgain.setTexture(texturePlayAgain);
}

void View::display(sf::RenderWindow* window) {
    while (window->isOpen()) {
        std::vector<std::vector<int>> board = controller->getBoard();
        std::unique_ptr<GameState>& currentState = controller->getCurrentState();
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i positionSourisOnClick = sf::Mouse::getPosition(*window);
                int x = (positionSourisOnClick.x - x_offset) / spriteSize;
                int y = (positionSourisOnClick.y - y_offset) / spriteSize;
                if ((x == 0 || y == 0 || x == 4 || y == 4) && 0 <= x && x <= 4 && 0 <= y && y <= 4) {
                    controller->click(x, y);
                }
                if (775 <= positionSourisOnClick.y && positionSourisOnClick.y <= 840 && 10 <= positionSourisOnClick.x && positionSourisOnClick.x <= 225) {
                    controller->resetGame();
                    return;
                }
                if ((currentState->getState() == 3 || currentState->getState() == 4) && 775 <= positionSourisOnClick.y && positionSourisOnClick.y <= 840 && 427 <= positionSourisOnClick.x && positionSourisOnClick.x <= 640) {
                    controller->resetGame();
                }
            }
        }
        
        window->clear(backgroundColor);

        if (currentState->getState() == 1) {
            spriteRond.setPosition((x_screen_size / 2) - (spriteSize / 2), y_screen_size - 150);
            window->draw(spriteRond);
        } else if (currentState->getState() == 2) {
            spriteCroix.setPosition((x_screen_size / 2) - (spriteSize / 2), y_screen_size - 150);
            window->draw(spriteCroix);
        } else if (currentState->getState() == 3) {
            spriteRondVictory.setPosition(25, 630);
            window->draw(spriteRondVictory);
            spritePlayAgain.setPosition(427, 775);
            window->draw(spritePlayAgain);
        } else if (currentState->getState() == 4) {
            spriteCroixVictory.setPosition(25, 630);
            window->draw(spriteCroixVictory);
            spritePlayAgain.setPosition(427, 775);
            window->draw(spritePlayAgain);
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == 0) {
                    spriteEmpty.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window->draw(spriteEmpty);
                }
                if (board[i][j] == 1) {
                    spriteRond.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window->draw(spriteRond);
                }
                if (board[i][j] == 2) {
                    spriteCroix.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window->draw(spriteCroix);
                }
                if (board[i][j] == 3) {
                    spriteEmptyPlayable.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window->draw(spriteEmptyPlayable);
                }
                if (board[i][j] == 4) {
                    spriteRondPlayable.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window->draw(spriteRondPlayable);
                }
                if (board[i][j] == 5) {
                    spriteCroixPlayable.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window->draw(spriteCroixPlayable);
                }
            } 
        }

        spriteBack.setPosition(10, 775);
        window->draw(spriteBack);

        window->display();
    }
}