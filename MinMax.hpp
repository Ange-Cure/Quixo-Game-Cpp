#pragma once

#include "AIStrategy.hpp"
#include <vector>

class MinMax : public AIStrategy {
public:
    void execute(Model& model) override;
    int evaluate(Model& model);
    std::vector<int> runMinMax(Model&, int);
};