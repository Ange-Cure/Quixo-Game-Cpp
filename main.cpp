#include <SFML/Graphics.hpp>
#include <iostream>


std::vector<std::vector<int>> board(5, std::vector<int>(5, 0));

int currentPlayer = 1;
int selectedPieceX = -1;
int selectedPieceY = -1;


void switchPlayer() {
    if (currentPlayer == 2) {
        currentPlayer = 1;
    } else {
        currentPlayer = 2;
    }
}

void switchPiece(int xA, int yA, int xB, int yB) {
    int temp = board[xA][yA];
    board[xA][yA] = board[xB][yB];
    board[xB][yB] = temp;
}

void setSelectedPiece(int x, int y) {
    selectedPieceX = x;
    selectedPieceY = y;
}
void unsetSelectedPiece() {
    selectedPieceX = -1;
    selectedPieceY = -1;
}

void deplacementPiece(int x, int y) {
    int directionX = 0;
    int directionY = 0;
    if (selectedPieceX == x){
        if (selectedPieceY > y) {
            directionY = -1;
        } else {
            directionY = 1;
        }
    } else {
        if (selectedPieceX > x) {
            directionX = -1;
        } else {
            directionX = 1;
        }
    }
    while (selectedPieceX != x || selectedPieceY != y) {
        switchPiece(selectedPieceX, selectedPieceY, selectedPieceX + directionX, selectedPieceY + directionY);
        selectedPieceX = selectedPieceX + directionX;
        selectedPieceY = selectedPieceY + directionY;
    }
}

bool isPieceValide(int x, int y) {
    return (board[x][y] == currentPlayer || board[x][y] == 0);
}

bool isDeplacementValide(int x, int y) {
    if (!(x == selectedPieceX && y == selectedPieceY)) {
        if (x == selectedPieceX && y == 0) {
            return true;
        }
        if (x == selectedPieceX && y == 4) {
            return true;
        }
        if (x == 0 && y == selectedPieceY) {
            return true;
        }
        if (x == 4 && y == selectedPieceY) {
            return true;
        }
    }
    return false;
}

void setDeplacementValide(int x, int y) {
    if (y != 0) board[x][0] = board[x][0] + 3;
    if (y != 4) board[x][4] = board[x][4] + 3;
    if (x != 0) board[0][y] = board[0][y] + 3;
    if (x != 4) board[4][y] = board[4][y] + 3;
}

void unsetDeplacementValide() {
    board[selectedPieceX][0] = board[selectedPieceX][0] - 3;
    board[selectedPieceX][4] = board[selectedPieceX][4] - 3;
    board[0][selectedPieceY] = board[0][selectedPieceY] - 3;
    board[4][selectedPieceY] = board[4][selectedPieceY] - 3;
}

bool isGameSolve() {
    // Check rows and columns
    bool isRowValid;
    bool isColumnValid;
    for (int i = 0; i < 5; i++) {
        isColumnValid = true;
        isRowValid = true;
        for (int j = 1; j < 5; j++) {
            isRowValid = (isRowValid && board[i][j] != 0 && board[i][j] == board[i][0]);
            isColumnValid = (isColumnValid && board[j][i] != 0 && board[j][i] == board[0][i]);
        }
        if (isRowValid || isColumnValid) return true;
    }

    // Check diagonals
    bool isMainDiagonalValid = true;
    bool isInverseDiagonalValid = true;
    for (int i = 1; i < 5; i++) {
        isMainDiagonalValid = (isMainDiagonalValid && board[i][i] != 0 && board[i][i] == board[0][0]);
        isInverseDiagonalValid = (isInverseDiagonalValid && board[i][4 - i] != 0 && board[i][4 - i] == board[0][4]);
    }
    if (isMainDiagonalValid || isInverseDiagonalValid) return true;

    return false;
}

int spriteSize = 120;
int x_offset = 25;
int y_offset = 25;
int x_screen_size = (x_offset * 2) + (spriteSize * 5);
int y_screen_size = (y_offset * 2) + (spriteSize * 5) + 150;

int main() {

    sf::RenderWindow window(sf::VideoMode(x_screen_size, y_screen_size), "SFML works!");

    sf::Color backgroundColor(37, 31, 46);

    sf::Texture textureRond;
    textureRond.loadFromFile("./sprite/rond.png");

    sf::Texture textureCroix;
    textureCroix.loadFromFile("./sprite/croix.png");

    sf::Texture textureRondPlayable;
    textureRondPlayable.loadFromFile("./sprite/rondPlayable.png");

    sf::Texture textureCroixPlayable;
    textureCroixPlayable.loadFromFile("./sprite/croixPlayable.png");

    sf::Texture textureEmptyPlayable;
    textureEmptyPlayable.loadFromFile("./sprite/emptyPlayable.png");

    sf::Texture textureEmpty;
    textureEmpty.loadFromFile("./sprite/empty.png");

    sf::Sprite spriteRond(textureRond);

    sf::Sprite spriteCroix(textureCroix);

    sf::Sprite spriteRondPlayable(textureRondPlayable);

    sf::Sprite spriteCroixPlayable(textureCroixPlayable);

    sf::Sprite spriteEmpty(textureEmpty);

    sf::Sprite spriteEmptyPlayable(textureEmptyPlayable);

    


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
                    if (selectedPieceX != -1) {
                        if (isDeplacementValide(x, y)) {
                            unsetDeplacementValide();
                            board[selectedPieceX][selectedPieceY] = currentPlayer;
                            deplacementPiece(x, y);
                            unsetSelectedPiece();
                            switchPlayer();
                        }
                    } else {
                        if (isPieceValide(x, y)) {
                            setSelectedPiece(x, y);
                            setDeplacementValide(x, y);
                        }
                    }
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

        if (isGameSolve()) {
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
    return 0;
}
