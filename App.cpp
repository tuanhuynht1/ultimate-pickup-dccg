#include "GameState.h"
#include <iostream>
#include <sstream>

using namespace std;

void Continue();
void Print(const GameState& G);

int main() {
    
    GameState G = GameState();

    cout << endl << setw(64) << "Ball Hot!" << endl << endl;
    
    while (G.scoreboard[0] < 21 && G.scoreboard[1] < 21) {

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
                                cout << endl << setw(32) << G.user[G.ballIndex]->name << " has the ball!";
                                Continue();
                                break;

                            case 's':
                                G.HandleOffense(Shoot); 
                                cout << endl << setw(32) << G.user[G.ballIndex]->name << " takes a shot!";
                                Continue();
                                break;

                            case '1':
                                if (G.ballIndex != 0) {
                                    G.HandleOffense(Pass, 0); 
                                    cout << endl << setw(32) << G.user[0]->name << " gets the ball!";
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
                                    cout << endl << setw(32) << G.user[1]->name << " gets the ball!";
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
                                    cout << endl << setw(32) << G.user[2]->name << " gets the ball!";
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
                    // defense
                    // cpu offense
                }

                G.phase = G.shotAttempted || G.stealAttempted  ? Result : Main;
                break;

            // ----------------------------- RESULT PHASE -------------------------------//
            case Result:
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
        cout << setw(32) << i+1 << ". " << p->name << (i == G.ballIndex && !G.hasPosession ? "*" : "") << " ";
        cout << (G.hasPosession ? p->defense : p->offense); 
    }
    
    cout << endl << endl;

    for (int i = 0; i < G.teamSize; i++) {
        
        Player* p = G.user[i];
        cout << setw(32) << i+1 << ". " << p->name << (i == G.ballIndex && G.hasPosession ? "*" : "") << " ";
        cout << (G.hasPosession ? p->offense : p->defense); 
    }
}

              // ss.str(input);

                // while(getline(ss, param, ',')) {
                //     std::cout << param << '\n';
                // }