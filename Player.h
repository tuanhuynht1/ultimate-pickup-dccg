#include <string>

using namespace std;

enum Position { Guard, Forward, Center };

class Player {
    public:
    string name;
    Position position;
    int baseOffense;
    int baseDefense;
    int offense;
    int defense;
    int passing;
    int rebound;

    Player(string nm, Position pos, int off, int def, int pass, int reb);
};