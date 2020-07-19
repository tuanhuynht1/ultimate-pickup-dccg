#include "GameState.h"
#include <iostream>

using namespace std;

void Continue();

int main() {
    
    GameState state = GameState();

    cout << endl << setw(64) << "Ball Hot!" << endl << endl;

    while(true) {

        if (state.phase == Start) {
            
            state.Print();
            Continue();
        }
    }

}

void Continue() {

    cout << endl << endl << endl << "press ENTER to continue... ";
    cin.get();
    cout << endl;
}