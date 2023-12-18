#pragma once
#include "Model.hpp"

class View;

class Controller
{
private:
    Model model;
    View* view;

public:
    Controller(View*);
    void run();
    std::vector<std::vector<int>> click(int, int);
};

