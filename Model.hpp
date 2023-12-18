#pragma once
#include <vector>

class Model {
public:
    Model();

    std::vector<std::vector<int>> getBoard();

    int getCurrentPlayer();

    void switchPlayer();

    void switchPiece(int xA, int yA, int xB, int yB);

    void setSelectedPiece(int x, int y);

    void unsetSelectedPiece();

    void deplacementPiece(int x, int y);

    void setDeplacementValide(int x, int y);

    void unsetDeplacementValide();

    bool isGameSolve();

    bool isPieceValide(int x, int y);

    bool isDeplacementValide(int x, int y);

    std::vector<std::vector<int>> click(int, int);

private:
    std::vector<std::vector<int>> board;
    int currentPlayer;
    int selectedPieceX;
    int selectedPieceY;
};
