#include "Player.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>     
#include <vector>

using namespace std;

enum Phase { Main, Result, Rebound };
enum Action { Hold, Shoot, Pass };

class GameState {
    
    public:
    int ballIndex;
    int teamSize;
    int shotClock;
    int cpuScore;
    int userScore;
    bool hasPosession;
    bool shotAttempted;
    bool stealAttempted;
    Player* cpu[3];
    Player* user[3];
    Phase phase;

    GameState();
    void HandleOffense(Action action, int tgt = 0);
    void Reset();
    bool HandleShotAttempt();
    void HandleRebound();
};