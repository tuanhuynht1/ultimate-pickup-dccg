#include "Player.h"

Player::Player(string nm, Position pos, int off, int def, int pass, int reb) {
    name = nm;
    position = pos;
    offense = off;
    baseOffense = off;
    defense = def;
    baseDefense = def;
    passing = pass;
    rebound = reb;
} 