#include "Player2SelectPieceState.hpp"
#include "Player2PlacePieceState.hpp"
#include "Model.hpp"

void Player2SelectPieceState::play(Model& model, int x, int y) {
    if (model.getBoard()[x][y] == 2 || model.getBoard()[x][y] == 0) {
        model.setSelectedPiece(x, y);
        model.setDeplacementValide(x, y);
        model.changeState(std::make_unique<Player2PlacePieceState>());
    }
}

int Player2SelectPieceState::getState() {
    return 2;
}
