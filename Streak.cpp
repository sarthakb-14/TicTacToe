#include "Streak.h"
#include <iostream>

using namespace std;

Streak::Streak() : currentStreak(0), currentPlayer("") {}

void Streak::resetStreak() {
    currentStreak = 0;
    currentPlayer = "";
}

void Streak::updateStreak(const std::string& player) {
    if (player == currentPlayer) {
        currentStreak++;  
    } else {
        currentPlayer = player;
        currentStreak = 1; 
    }
}

bool Streak::checkStreakReward(int& points) {
    if (currentStreak == 3) {
        points += 5;
        printStreakReward(5);
        return true;
    } else if (currentStreak == 5) {
        points += 10;
        printStreakReward(10);
        return true;
    }
    return false;
}

void Streak::printStreakReward(int points) {
    cout << "Streak Reward: " << points << " bonus points!" << endl;
}