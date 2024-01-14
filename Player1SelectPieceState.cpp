#include "Player1SelectPieceState.hpp"
#include "Player1PlacePieceState.hpp"
#include "Model.hpp"

void Player1SelectPieceState::play(Model& model, int x, int y) {
    if (model.getBoard()[x][y] == 1 || model.getBoard()[x][y] == 0) {
        model.setSelectedPiece(x, y);
        model.setDeplacementValide(x, y);
        model.changeState(std::make_unique<Player1PlacePieceState>());
    }
}

int Player1SelectPieceState::getState() {
    return 1;
}
