#include "Player2PlacePieceState.hpp"
#include "Player1SelectPieceState.hpp"
#include "Model.hpp"

void Player2PlacePieceState::play(Model& model, int x, int y) {
    if (model.isDeplacementValide(x, y)) {
        model.unsetDeplacementValide();
        auto& board = model.getBoardRef();
        board[model.getSelectedPieceX()][model.getSelectedPieceY()] = 2;
        model.deplacementPiece(x, y);
        model.unsetSelectedPiece();
        model.changeState(std::make_unique<Player1SelectPieceState>());
    }
}

int Player2PlacePieceState::getState() {
    return 2;
}