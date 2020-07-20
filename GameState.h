#include "Player.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>     
#include <vector>

using namespace std;

enum Phase { Main, Result, Rebound };
enum Action { Hold, Shoot, Pass, Steal, Contest, HelpLeft, HelpRight };

class GameState {
    
    public:
    int ballIndex;
    int teamSize;
    int shotClock;
    int cpuScore;
    int userScore;
    int stealIndex;
    int contestIndex;
    bool hasPosession;
    bool shotAttempted;
    bool stealAttempted;
    bool shotContested;
    Player* cpu[3];
    Player* user[3];
    Phase phase;

    GameState();
    void HandleOffense(Action action, int tgt = 0);
    void HandleDefense(Action action, int tgt = 0);
    void Reset();
    void ResetStats();
    bool HandleShotAttempt();
    bool HandleStealAttempt();
    void HandleShotContest();
    void HandleRebound();
};