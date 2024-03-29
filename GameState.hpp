#pragma once

class Model;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void play(Model& model, int x, int y) = 0;
    virtual int getState() = 0;
};
