#pragma once
#include <vector>
#include <memory>
#include "GameState.hpp"

class Model {
public:
    Model();

    std::unique_ptr<GameState> currentState;
    std::vector<std::vector<int>> getBoard();
    std::vector<std::vector<int>>& getBoardRef();
    int getSelectedPieceX();
    int getSelectedPieceY();
    GameState& getCurrentState();
    void switchPiece(int xA, int yA, int xB, int yB);
    void setSelectedPiece(int x, int y);
    void unsetSelectedPiece();
    void deplacementPiece(int x, int y);
    void setDeplacementValide(int x, int y);
    void unsetDeplacementValide();
    bool isGameSolve(int);
    bool isDeplacementValide(int x, int y);
    void changeState(std::unique_ptr<GameState> newState);
    void click(int, int);
    void resetGame();

private:
    std::vector<std::vector<int>> board;
    int selectedPieceX;
    int selectedPieceY;
};
