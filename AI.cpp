#include "AI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

bool AI::checkWin(const vector<vector<char>>& board, char player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

bool AI::checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; 
            }
        }
    }
    return true; 
}

bool AI::isGameOver(const vector<vector<char>>& board) {
    return checkWin(board, 'X') || checkWin(board, 'O') || checkDraw(board);
}

int AI::minimax(vector<vector<char>>& board, int depth, bool isMaximizingPlayer) {
    if (AI::checkWin(board, 'O')) {
        return 10 - depth;  
    }
    if (AI::checkWin(board, 'X')) {
        return depth - 10;  
    }
    if (AI::checkDraw(board)) {
        return 0;  
    }

    if (isMaximizingPlayer) {
        int best = INT_MIN; 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';  
                    best = max(best, minimax(board, depth + 1, false));  
                    board[i][j] = ' ';  
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;  
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';  
                    best = min(best, minimax(board, depth + 1, true)); 
                    board[i][j] = ' ';  
                }
            }
        }
        return best;
    }
}

pair<int, int> AI::getAIMove(vector<vector<char>>& board) {
    int bestVal = INT_MIN;
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';  
                int moveVal = AI::minimax(board, 0, false);  
                board[i][j] = ' ';  

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}