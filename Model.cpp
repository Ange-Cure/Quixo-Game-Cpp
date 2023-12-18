#include "Model.hpp"
#include <iostream>


Model::Model() {
    board = std::vector<std::vector<int>>(5, std::vector<int>(5, 0));
    currentPlayer = 1;
    selectedPieceX = -1;
    selectedPieceY = -1;
}

std::vector<std::vector<int>> Model::getBoard() {
    return board;
}

int Model::getCurrentPlayer() {
    return currentPlayer;
}

void Model::switchPlayer() {
    if (currentPlayer == 2) {
        currentPlayer = 1;
    } else {
        currentPlayer = 2;
    }
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
    board[selectedPieceX][0] = board[selectedPieceX][0] - 3;
    board[selectedPieceX][4] = board[selectedPieceX][4] - 3;
    board[0][selectedPieceY] = board[0][selectedPieceY] - 3;
    board[4][selectedPieceY] = board[4][selectedPieceY] - 3;
}

bool Model::isGameSolve() {
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

bool Model::isPieceValide(int x, int y) {
    return (board[x][y] == currentPlayer || board[x][y] == 0);
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

std::vector<std::vector<int>> Model::click(int x, int y) {
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
    return board;
}