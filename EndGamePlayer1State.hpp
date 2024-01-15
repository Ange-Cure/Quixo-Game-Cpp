#pragma once

#include "GameState.hpp"

class EndGamePlayer1State : public GameState {
public:
    void play(Model& model, int x, int y) override;
    int getState() override;
};
