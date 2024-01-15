#pragma once

#include "AIStrategy.hpp"

class Random : public AIStrategy {
public:
    void execute(Model& model) override;
};
