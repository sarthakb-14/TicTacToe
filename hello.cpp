#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Leaderboard.h"  
#include "AI.h"
#include <chrono>
#include <thread>

using namespace std;

void printBoard(const vector<vector<char>>& board) {
    cout << endl;
    int counter = 1;  
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                cout << counter++;  
            } else {
                cout << board[i][j];
                counter++; 
            }
            if (j < 2) cout << " | ";  
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;  
    }
    cout << endl;
}

bool checkWin(const vector<vector<char>>& board, char player) {
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

bool checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void playerMove(vector<vector<char>>& board, char player) {
    int move;
    while (true) {
        cout << "Enter your move (1 to 9): ";
        cin >> move;

        if (move >= 1 && move <= 9) {
            int row = (move - 1) / 3;  
            int col = (move - 1) % 3;  
            if (board[row][col] == ' ') {
                board[row][col] = player;
                break;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        } else {
            cout << "Invalid input! Please enter a number between 1 and 9." << endl;
        }
    }
}

void twoPlayerGame(Leaderboard& leaderboard) {
    vector<vector<char>> board(3, vector<char>(3, ' '));  
    string player1, player2;
    char player = 'X';

    cout << "Enter Player 1 username: ";
    cin >> player1;
    cout << "Enter Player 2 username: ";
    cin >> player2;

    while (true) {
        printBoard(board);
        if (player == 'X') {
            cout << player1 << "'s turn (X)" << endl;
        } else {
            cout << player2 << "'s turn (O)" << endl;
        }

        playerMove(board, player);
        if (checkWin(board, player)) {
            printBoard(board);
            if (player == 'X') {
                cout << player1 << " wins!" << endl;
                leaderboard.updateScore(player1, true); 
            } else {
                cout << player2 << " wins!" << endl;
                leaderboard.updateScore(player2, true);
            }
            return;
        }
        if (checkDraw(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            return;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
}

void singlePlayerGame(Leaderboard& leaderboard, const string& username) {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char player = 'X';  
    
    while (true) {
        printBoard(board);
        
        if (player == 'X') {
            playerMove(board, player);  
        } else {
            cout << "AI is making a move..." << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            pair<int, int> aiMove = AI::getAIMove(board); 
            board[aiMove.first][aiMove.second] = 'O';
        }

        if (checkWin(board, 'X')) {
            printBoard(board);
            cout << username << " wins!" << endl;
            leaderboard.updateScore(username, false);  
            return;
        }
        
        if (checkWin(board, 'O')) {
            printBoard(board);
            cout << "You lose!" << endl;
            return;
        }

        if (checkDraw(board)) {
            printBoard(board);
            cout << "It's a draw!" << endl;
            return;
        }

        player = (player == 'X') ? 'O' : 'X';  
    }
}

int main() {
    string username;
    int choice;
    Leaderboard leaderboard; 

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "Please enter your username: ";
    cin >> username;

    while (true) {
        cout << "\nSelect Game Mode:" << endl;
        cout << "1. Two-Player Game" << endl;
        cout << "2. Single-Player Game (Against AI)" << endl;
        cout << "3. View Leaderboard" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        if (choice == 1) {
            twoPlayerGame(leaderboard);  
        } else if (choice == 2) {
            singlePlayerGame(leaderboard, username); 
        } else if (choice == 3) {
            leaderboard.displayLeaderboard(); 
        } else {
            cout << "Exiting game. Goodbye!" << endl;
            break;
        }
    }

    return 0;
}