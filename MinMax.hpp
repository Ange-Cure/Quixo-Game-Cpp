#pragma once

#include "AIStrategy.hpp"

class MinMax : public AIStrategy {
public:
    void execute(Model& model) override;
};