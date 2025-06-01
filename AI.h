#ifndef AI_H
#define AI_H

#include <vector>
#include <utility>
#include <string>

using namespace std; 

class AI {
public:
    static bool checkWin(const vector<vector<char>>& board, char player);
    static bool checkDraw(const vector<vector<char>>& board);
    static bool isGameOver(const vector<vector<char>>& board);
    static int minimax(vector<vector<char>>& board, int depth, bool isMaximizingPlayer);
    static pair<int, int> getAIMove(vector<vector<char>>& board);
};

#endif 