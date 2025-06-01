#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <map>
#include <string>
#include "Streak.h"  

using namespace std;

class Leaderboard {
private:
    map<string, int> playerScores;
    Streak streak;  

public:
    Leaderboard();
    void updateScore(const string& username, bool isTwoPlayerGame);
    void displayLeaderboard() const;
    void checkStreak(const string& username); 
};

#endif