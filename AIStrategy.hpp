#pragma once

class Model;

class AIStrategy {
public:
    virtual void execute(Model& model) = 0;
};