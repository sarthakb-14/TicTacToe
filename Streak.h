#ifndef STREAK_H
#define STREAK_H

#include <string>

using namespace std;

class Streak {
private:
    int currentStreak;
    string currentPlayer;
    
public:
    Streak();  
    void resetStreak();  
    void updateStreak(const string& player);  
    bool checkStreakReward(int& points); 
    void printStreakReward(int points);  
};

#endif