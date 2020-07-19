#include "GameState.h"


GameState::GameState() {

    scoreboard[2] = {0};
    ballIndex = 0;
    teamSize = 3;
    shotClock = 3;
    cpuScore = 0;
    userScore = 0;
    hasPosession = true; // 50/50
    shotAttempted = false;
    stealAttempted = false;
    phase = Start;

    // sample players
    cpu[0] = new Player("Stephen Curry", Guard, 94, 70, 92, 32);
    cpu[1] = new Player("Kevin Durant", Forward, 96, 82, 75, 82);
    cpu[2] = new Player("Joel Embiid", Center, 86, 94, 60, 90);

    user[0] = new Player("James Harden", Guard, 96, 62, 80, 80);
    user[1] = new Player("Lebron James", Forward, 88, 82, 99, 88);
    user[2] = new Player("Anthony Davis", Center, 90, 90, 60, 92);

};

void GameState::Print() {
    
    cout << "Score Board: " << userScore << " to " << cpuScore << endl;
    cout << "Shot Clock: " << shotClock << endl << endl;

    for (int i = 0; i < teamSize; i++) {
        
        Player* p = cpu[i];
        cout << setw(32) << p->name << (i == ballIndex && !hasPosession ? "*" : "") << " ";
        cout << (hasPosession ? p->defense : p->offense); 
    }
    
    cout << endl << endl;

    for (int i = 0; i < teamSize; i++) {
        
        Player* p = user[i];
        cout << setw(32) << p->name << (i == ballIndex && hasPosession ? "*" : "") << " ";
        cout << (hasPosession ? p->offense : p->defense); 
    }
}