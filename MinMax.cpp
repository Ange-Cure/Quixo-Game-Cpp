#include "MinMax.hpp"
#include "Model.hpp"
#include "Player2SelectPieceState.hpp"
#include "Player1SelectPieceState.hpp"
#include <iostream>


int MinMax::evaluate(Model& model) {
    std::vector<std::vector<int>> board = model.getBoard();
    int value = 0;
    if (model.isGameSolve(1)) return 2147483647;
    if (model.isGameSolve(2)) return -2147483647;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j+1]) {
                if (board[i][j] == 2) {
                    value++;
                } else {
                    value--;
                }
            }
            if (board[j][i] != 0 && board[j][i] == board[j+1][i]) {
                if (board[j][i] == 2) {
                    value++;
                } else {
                    value--;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (board[i][i] != 0 && board[i][i] == board[i+1][i+1]) {
            if (board[i][i] == 2) {
                value++;
            } else {
                value--;
            }
        }
        if (board[i][4 - i] != 0 && board[i][4 - i] == board[i+1][4 - (i+1)]) {
            if (board[i][4-i] == 2) {
                value++;
            } else {
                value--;
            }
        }
    }
    return value;
}


std::vector<int> MinMax::runMinMax(Model& model, int depth) {
    std::vector<int> best = std::vector<int>(5, 0);
    if (depth%2 == 1) {
        best[0] = -2147483647;
    }
    if (depth%2 == 0) {
        best[0] = 2147483647;
    }
    if (depth == 0) {
        best[0] = evaluate(model);
        return best;
    }
    std::vector<int> result;

    std::vector<std::vector<int>> possibleMove;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i == 0 || i == 4 || j == 0 || j == 4) && (model.getBoard()[i][j] == depth % 2 + 1 || model.getBoard()[i][j] == 0)) {
                if (j != 0) {
                    possibleMove.push_back({i, j, i, 0});
                }
                if (j != 4) {
                    possibleMove.push_back({i, j, i, 4});
                }
                if (i != 0) {
                    possibleMove.push_back({i, j, 0, j});
                }
                if (i != 4) {
                    possibleMove.push_back({i, j, 4, j});
                }
            }
        }
    }

    
    for (const auto& move : possibleMove) {
        Model currentBoard = Model(model);
        if (depth%2 == 0) {
            currentBoard.changeState(std::make_unique<Player1SelectPieceState>());  
        }
        if (depth%2 == 1) {
            currentBoard.changeState(std::make_unique<Player2SelectPieceState>());    
        }
        
        currentBoard.click(move[0], move[1]);
        currentBoard.click(move[2], move[3]);
        result = runMinMax(currentBoard, depth-1);

        if (depth % 2 == 1 && result[0] >= best[0]) {
            best[0] = result[0];
            best[1] = move[0];
            best[2] = move[1];
            best[3] = move[2];
            best[4] = move[3];
        }
        if (depth % 2 == 0 && result[0] <= best[0]) {
            best[0] = result[0];
            best[1] = move[0];
            best[2] = move[1];
            best[3] = move[2];
            best[4] = move[3];
        }
    }
    return best;
}

void MinMax::execute(Model& model) {
    std::vector result = runMinMax(model, 3);

    model.click(result[1], result[2]);
    model.click(result[3], result[4]);
}