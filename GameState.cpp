#include "GameState.h"


GameState::GameState() {

    ballIndex = 0;
    teamSize = 3;
    shotClock = 3;
    cpuScore = 0;
    userScore = 0;
    hasPosession = true; // 50/50
    shotAttempted = false;
    stealAttempted = false;
    phase = Main;

    // sample players
    cpu[0] = new Player("Stephen Curry", Guard, 94, 70, 92, 32);
    cpu[1] = new Player("Kevin Durant", Forward, 96, 82, 75, 75);
    cpu[2] = new Player("Joel Embiid", Center, 86, 94, 60, 90);

    user[0] = new Player("James Harden", Guard, 96, 62, 80, 70);
    user[1] = new Player("Lebron James", Forward, 88, 82, 99, 82);
    user[2] = new Player("Anthony Davis", Center, 90, 90, 60, 92);

};

void GameState::HandleOffense(Action action, int tgt) {

    switch (action) {
        case Hold:
            user[ballIndex]->offense += 10; 
            break;
        case Shoot:
            shotAttempted = true; 
            break;
        case Pass:
            ballIndex = tgt;
            user[ballIndex]->offense += 10; 
            break;
    }

    return;
}

void GameState::Reset() {
    shotClock = 3;
    shotAttempted = false;
    stealAttempted = false;
}

bool GameState::HandleShotAttempt() {
    
    int shot = hasPosession ? user[ballIndex]->offense : cpu[ballIndex]->offense;
    int defense = hasPosession ? cpu[ballIndex]->defense : user[ballIndex]->defense;
    
    double r = rand() % (shot + defense);

    if (r <= shot) {

        hasPosession ? userScore += 2 : cpuScore += 2;
        return true;
    }
    else {
        return false;
    }
}

void GameState::HandleRebound() {

    vector<int> cumSum;

    cumSum.push_back(cpu[0]->rebound);
    cumSum.push_back(user[0]->rebound + cumSum[0]);
    cumSum.push_back(cpu[1]->rebound + cumSum[1]);
    cumSum.push_back(user[1]->rebound + cumSum[2]);
    cumSum.push_back(cpu[2]->rebound + cumSum[3]);
    cumSum.push_back(user[2]->rebound + cumSum[4]);

    int r = rand() % cumSum.back();

    cout << r << endl;
    for (auto i : cumSum) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < cumSum.size(); i++) {
        
        if (r <= cumSum[i]) {
            hasPosession = i % 2 == 0 ? false : true;
            ballIndex = i / 2;
            break;
        }
    }
}