#include <SFML/Graphics.hpp>
#include <iostream>


std::vector<std::vector<int>> board(6, std::vector<int>(6, 0));

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
    std::cout << board[x][y] << std::endl;
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

int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    sf::Texture textureRond;
    textureRond.loadFromFile("./sprite/rond.png");

    sf::Texture textureCroix;
    textureCroix.loadFromFile("./sprite/croix.png");

    sf::Sprite spriteRond(textureRond);

    sf::Sprite spriteCroix(textureCroix);



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i positionSourisOnClick = sf::Mouse::getPosition(window);
                if (positionSourisOnClick.x <= 500 && positionSourisOnClick.y <= 500) {
                    std::cout << "Vous avez cliquer sur la case: " << positionSourisOnClick.x / 100 << " " << positionSourisOnClick.y / 100 << std::endl;
                    int x = positionSourisOnClick.x / 100;
                    int y = positionSourisOnClick.y / 100;
                    if (selectedPieceX != -1) {
                        if (isDeplacementValide(x, y)) {
                            board[selectedPieceX][selectedPieceY] = currentPlayer;
                            deplacementPiece(x, y);
                            unsetSelectedPiece();
                            switchPlayer();
                        }
                    } else {
                        if (isPieceValide(x, y)) {
                            std::cout << "valeur piece clique :" << board[x][y] << " currentPlayer: " << currentPlayer << std::endl;
                            setSelectedPiece(x, y);
                        }
                    }
                    std::cout << std::endl;
                }
            }
        }
        
        window.clear(sf::Color::White);

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (board[i][j] == 1) {
                    spriteRond.setPosition(i * 100, j * 100);
                    window.draw(spriteRond);
                }
                if (board[i][j] == 2) {
                    spriteCroix.setPosition(i * 100, j * 100);
                    window.draw(spriteCroix);
                }
            } 
        }

        for (int i = 0; i < 6; ++i) {
            // Dessiner les lignes verticales
            sf::VertexArray verticalLine(sf::Lines, 2);
            verticalLine[0].position = sf::Vector2f(i * 100, 0);
            verticalLine[1].position = sf::Vector2f(i * 100, 500);
            verticalLine[0].color = sf::Color::Black;
            verticalLine[1].color = sf::Color::Black;
            window.draw(verticalLine);

            // Dessiner les lignes horizontales
            sf::VertexArray horizontalLine(sf::Lines, 2);
            horizontalLine[0].position = sf::Vector2f(0, i * 100);
            horizontalLine[1].position = sf::Vector2f(500, i * 100);
            horizontalLine[0].color = sf::Color::Black;
            horizontalLine[1].color = sf::Color::Black;
            window.draw(horizontalLine);
        }

        window.display();
    }
    return 0;
}
