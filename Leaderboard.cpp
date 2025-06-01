#include "Leaderboard.h"
#include <iostream>
#include <map>
#include <string>

using namespace std;

Leaderboard::Leaderboard() {}

void Leaderboard::updateScore(const string& username, bool isTwoPlayerGame) {
    int points = isTwoPlayerGame ? 2 : 1;

    if (playerScores.find(username) == playerScores.end()) {
        playerScores[username] = points;
    } else {
        playerScores[username] += points;
    }

    checkStreak(username);  
}

void Leaderboard::checkStreak(const string& username) {
    streak.updateStreak(username); 

    int streakPoints = 0;
    if (streak.checkStreakReward(streakPoints)) { 
        playerScores[username] += streakPoints; 
    }
}

void Leaderboard::displayLeaderboard() const {
    cout << "\nLeaderboard:\n";
    for (const auto& player : playerScores) {
        cout << player.first << ": " << player.second << " points\n";
    }
    cout << "\n";
}