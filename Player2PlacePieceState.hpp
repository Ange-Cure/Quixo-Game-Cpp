#pragma once

#include "GameState.hpp"

class Player2PlacePieceState : public GameState {
public:
    void play(Model& model, int x, int y) override;
    int getState() override;
};
