#include "Player1PlacePieceState.hpp"
#include "Player2SelectPieceState.hpp"
#include "Model.hpp"

void Player1PlacePieceState::play(Model& model, int x, int y) {
    if (model.isDeplacementValide(x, y)) {
        model.unsetDeplacementValide();
        auto& board = model.getBoardRef();
        board[model.getSelectedPieceX()][model.getSelectedPieceY()] = 1;
        model.deplacementPiece(x, y);
        model.unsetSelectedPiece();
        model.changeState(std::make_unique<Player2SelectPieceState>());
    }
}

int Player1PlacePieceState::getState() {
    return 1;
}