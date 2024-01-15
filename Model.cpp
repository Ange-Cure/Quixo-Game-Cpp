#include "Model.hpp"
#include "Player1SelectPieceState.hpp"
#include "EndGamePlayer1State.hpp"
#include "EndGamePlayer2State.hpp"
#include <iostream>


Model::Model() : currentState(std::make_unique<Player1SelectPieceState>()), strategyMinMax(new MinMax()), strategyRandom(new Random()), currentStrategy(strategyRandom) {
    board = std::vector<std::vector<int>>(5, std::vector<int>(5, 0));
    selectedPieceX = -1;
    selectedPieceY = -1;
}

std::vector<std::vector<int>> Model::getBoard() {
    return board;
}

std::vector<std::vector<int>>& Model::getBoardRef() {
    return board;
}

int Model::getSelectedPieceX() {
    return selectedPieceX;
}

int Model::getSelectedPieceY() {
    return selectedPieceY;
}

GameState& Model::getCurrentState() {
    return *currentState;
}

void Model::setStrategyMinMax() {
    currentStrategy = strategyMinMax;
}

void Model::setStrategyRandom() {
    currentStrategy = strategyRandom;
}

void Model::executeAI() {
    currentStrategy->execute(*this);
}

void Model::switchPiece(int xA, int yA, int xB, int yB) {
    int temp = board[xA][yA];
    board[xA][yA] = board[xB][yB];
    board[xB][yB] = temp;
}

void Model::setSelectedPiece(int x, int y) {
    selectedPieceX = x;
    selectedPieceY = y;
}
void Model::unsetSelectedPiece() {
    selectedPieceX = -1;
    selectedPieceY = -1;
}

void Model::deplacementPiece(int x, int y) {
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

void Model::setDeplacementValide(int x, int y) {
    if (y != 0) board[x][0] = board[x][0] + 3;
    if (y != 4) board[x][4] = board[x][4] + 3;
    if (x != 0) board[0][y] = board[0][y] + 3;
    if (x != 4) board[4][y] = board[4][y] + 3;
}

void Model::unsetDeplacementValide() {
    if (selectedPieceY != 0) board[selectedPieceX][0] = board[selectedPieceX][0] - 3;
    if (selectedPieceY != 4) board[selectedPieceX][4] = board[selectedPieceX][4] - 3;
    if (selectedPieceX != 0) board[0][selectedPieceY] = board[0][selectedPieceY] - 3;
    if (selectedPieceX != 4) board[4][selectedPieceY] = board[4][selectedPieceY] - 3;
}

bool Model::isGameSolve(int checkedPlayer) {
    // Check rows and columns
    bool isRowValid;
    bool isColumnValid;
    for (int i = 0; i < 5; i++) {
        isColumnValid = true;
        isRowValid = true;
        for (int j = 0; j < 5; j++) {
            isRowValid = (isRowValid && board[i][j] != 0 && board[i][j] == checkedPlayer);
            isColumnValid = (isColumnValid && board[j][i] != 0 && board[j][i] == checkedPlayer);
        }
        if (isRowValid || isColumnValid) return true;
    }

    // Check diagonals
    bool isMainDiagonalValid = true;
    bool isInverseDiagonalValid = true;
    for (int i = 1; i < 5; i++) {
        isMainDiagonalValid = (isMainDiagonalValid && board[i][i] != 0 && board[i][i] == checkedPlayer);
        isInverseDiagonalValid = (isInverseDiagonalValid && board[i][4 - i] != 0 && board[i][4 - i] == checkedPlayer);
    }
    if (isMainDiagonalValid || isInverseDiagonalValid) return true;

    return false;
}

bool Model::isDeplacementValide(int x, int y) {
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

void Model::changeState(std::unique_ptr<GameState> newState) {
    currentState = std::move(newState);
}

void Model::click(int x, int y) {
    if (currentState) {
        currentState->play(*this, x, y);
        if (currentState->getState() == 1) {
            if (isGameSolve(1)) {
                changeState(std::make_unique<EndGamePlayer1State>());
            } else if (isGameSolve(2)) {
                changeState(std::make_unique<EndGamePlayer2State>());
            }
        } else if (currentState->getState() == 2) {
            if (isGameSolve(2)) {
                changeState(std::make_unique<EndGamePlayer2State>());
            } else if (isGameSolve(1)) {
                changeState(std::make_unique<EndGamePlayer1State>());
            }
        }
    }
}

void Model::resetGame() {
    board = std::vector<std::vector<int>>(5, std::vector<int>(5, 0));
    currentState = std::make_unique<Player1SelectPieceState>();
    selectedPieceX = -1;
    selectedPieceY = -1;
}