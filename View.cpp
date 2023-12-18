#include "View.hpp"
#include "Controller.hpp"

View::View(Controller* c) : controller(c) {
    window.create(sf::VideoMode(x_screen_size, y_screen_size), "Quixo");

    textureEmpty.loadFromFile("./sprite/empty.png");
    textureRond.loadFromFile("./sprite/rond.png");
    textureCroix.loadFromFile("./sprite/croix.png");
    textureEmptyPlayable.loadFromFile("./sprite/emptyPlayable.png");
    textureRondPlayable.loadFromFile("./sprite/rondPlayable.png");
    textureCroixPlayable.loadFromFile("./sprite/croixPlayable.png");

    spriteEmpty.setTexture(textureEmpty);
    spriteRond.setTexture(textureRond);
    spriteCroix.setTexture(textureCroix);
    spriteEmptyPlayable.setTexture(textureEmptyPlayable);
    spriteRondPlayable.setTexture(textureRondPlayable);
    spriteCroixPlayable.setTexture(textureCroixPlayable);
}

void View::display(std::vector<std::vector<int>> board, int currentPlayer, int isGameSolve) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i positionSourisOnClick = sf::Mouse::getPosition(window);
                int x = (positionSourisOnClick.x - x_offset) / spriteSize;
                int y = (positionSourisOnClick.y - y_offset) / spriteSize;
                if ((x == 0 || y == 0 || x == 4 || y == 4) && 0 <= x && x <= 4 && 0 <= y && y <= 4) {
                    board = controller->click(x, y);
                }
            }
        }
        
        window.clear(backgroundColor);

        if (currentPlayer == 1) {
            spriteRond.setPosition((x_screen_size / 2) - (spriteSize / 2), y_screen_size - 150);
            window.draw(spriteRond);
        } else {
            spriteCroix.setPosition((x_screen_size / 2) - (spriteSize / 2), y_screen_size - 150);
            window.draw(spriteCroix);
        }

        if (isGameSolve) {
            if (currentPlayer == 2) {
                spriteRond.setPosition(x_screen_size - spriteSize, y_screen_size - spriteSize);
                window.draw(spriteRond);
            } else {
                spriteRond.setPosition(x_screen_size - spriteSize, y_screen_size - spriteSize);
                window.draw(spriteCroix);
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == 0) {
                    spriteEmpty.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window.draw(spriteEmpty);
                }
                if (board[i][j] == 1) {
                    spriteRond.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window.draw(spriteRond);
                }
                if (board[i][j] == 2) {
                    spriteCroix.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window.draw(spriteCroix);
                }
                if (board[i][j] == 3) {
                    spriteEmptyPlayable.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window.draw(spriteEmptyPlayable);
                }
                if (board[i][j] == 4) {
                    spriteRondPlayable.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window.draw(spriteRondPlayable);
                }
                if (board[i][j] == 5) {
                    spriteCroixPlayable.setPosition(i * spriteSize + x_offset, j * spriteSize + y_offset);
                    window.draw(spriteCroixPlayable);
                }
            } 
        }

        window.display();
    }
}