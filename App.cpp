#include "GameState.h"
#include <iostream>
#include <sstream>
#include <time.h>      

using namespace std;

void Continue();
void Print(const GameState& G);

int main() {
    
    GameState G = GameState();

    srand(time(NULL));

    cout << endl << setw(64) << "Ball Hot!" << endl << endl;

    while (G.userScore < 21 && G.cpuScore < 21) {

        string input;
        switch (G.phase) {
            
            // ----------------------------- MAIN PHASE -------------------------------//
            case Main:

                Print(G);

                if (G.hasPosession) {
                    
                    cout << endl << endl << "Action: ";
                    getline(cin, input);

                    bool valid;
                    do{
                        valid = true;
                        switch (input[0]) {

                            case 'h': 
                                G.HandleOffense(Hold); 
                                cout << endl << setw(16) << G.user[G.ballIndex]->name << " has the ball!";
                                Continue();
                                break;

                            case 's':
                                G.HandleOffense(Shoot); 
                                cout << endl << setw(16) << G.user[G.ballIndex]->name << " takes a shot!";
                                Continue();
                                break;

                            case '1':
                                if (G.ballIndex != 0) {
                                    G.HandleOffense(Pass, 0); 
                                    cout << endl << setw(16) << G.user[0]->name << " gets the ball!";
                                    Continue();
                                }
                                else {
                                    input[0] = 'h';
                                    valid = false;
                                }
                                break;

                            case '2':
                                if (G.ballIndex != 1) {
                                    G.HandleOffense(Pass, 1); 
                                    cout << endl << setw(16) << G.user[1]->name << " gets the ball!";
                                    Continue();
                                }
                                else {
                                    input[0] = 'h';
                                    valid = false;
                                }
                                break;

                            case '3':
                                if (G.ballIndex != 2) {
                                    G.HandleOffense(Pass, 2); 
                                    cout << endl << setw(16) << G.user[2]->name << " gets the ball!";
                                    Continue();
                                }
                                else {
                                    input[0] = 'h';
                                    valid = false;
                                }
                                break;

                            default: 
                                cout << "Try Again: ";
                                getline(cin, input);
                                valid = false;
                        }
                    } while (!valid);
                    // cpu defense
                }

                else {
                    
                    cout << endl << endl;
                    
                    for (int i = 0; i < G.teamSize; i++) {
                        
                        cout << G.user[i]->name << "'s Defensive Action: ";
                        getline(cin, input);

                        switch (input[0]) {
                            case 's':
                                if (!G.stealAttempted) {
                                    G.stealIndex = i;
                                    G.stealAttempted = true;
                                }
                                break;

                            case 'c':
                                if (!G.shotContested) {
                                    G.contestIndex = i;
                                    G.shotContested = true;
                                }
                                break;

                            default: break;
                        }
                    }

                    // cpu offense
                }

                G.shotClock--;
                G.phase = G.shotAttempted || G.stealAttempted || G.shotContested || G.shotClock == 0 ? Result : Main;
                break;

            // ----------------------------- RESULT PHASE -------------------------------//
            case Result:

                if (G.stealAttempted) {
                    
                    if (G.HandleStealAttempt()) {

                        cout << endl << setw(16) << (G.hasPosession ? G.user[G.ballIndex]->name : G.cpu[G.ballIndex]->name) << " with the steal!";
                        G.phase = Main;

                        G.Reset();
                        G.ResetStats();
                        Continue();
                        break;
                    }
                    else {
                        G.stealAttempted = false;
                        G.phase = Main;
                    }
                }

                if (G.shotContested) {
                    G.HandleShotContest();
                    G.shotContested = false;
                    G.phase = Main;
                }

                if (G.shotAttempted) {
                    
                    if (G.HandleShotAttempt()) {
                         cout << endl << setw(16) << "Swish!";
                         G.hasPosession = !G.hasPosession;
                         G.ResetStats();
                         G.phase = Main;
                    }
                    else {
                        cout << endl << setw(16) << "Clank!";
                        G.phase = Rebound;
                    }

                    G.Reset();
                    Continue();
                }

                else if (G.shotClock == 0) {
                    
                    G.hasPosession = !G.hasPosession;
                    G.ballIndex = 0;
                    G.ResetStats();

                    cout << endl << setw(16) << "Shot clock violation!";
                    Continue();

                    G.phase = Main;
                    G.Reset();
                }
          
                break;

                // ----------------------------- REBOUND PHASE -------------------------------//
                case Rebound:

                    G.HandleRebound();

                    cout << endl << setw(16) << (G.hasPosession ? G.user[G.ballIndex]->name : G.cpu[G.ballIndex]->name) << " grabs the rebound!";
                    Continue();

                    G.phase = Main;
                    break;
        }
        
    }
}

void Continue() {

    cout << endl << endl << endl << "press ENTER to continue... ";
    cin.get();
    cout << endl;
}

void Print(const GameState& G) {
    
    cout << "Score Board: " << G.userScore << " to " << G.cpuScore << endl;
    cout << "Shot Clock: " << G.shotClock << endl << endl;

    for (int i = 0; i < G.teamSize; i++) {
        
        Player* p = G.cpu[i];
        cout << setw(16) << i+1 << ". " << p->name << (i == G.ballIndex && !G.hasPosession ? "*" : "") << " ";
        cout << (G.hasPosession ? p->defense : p->offense); 
    }
    
    cout << endl << endl;

    for (int i = 0; i < G.teamSize; i++) {
        
        Player* p = G.user[i];
        cout << setw(16) << i+1 << ". " << p->name << (i == G.ballIndex && G.hasPosession ? "*" : "") << " ";
        cout << (G.hasPosession ? p->offense : p->defense); 
    }
}

              // ss.str(input);

                // while(getline(ss, param, ',')) {
                //     std::cout << param << '\n';
                // }