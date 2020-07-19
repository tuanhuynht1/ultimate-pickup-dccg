#include "Player.h"

Player::Player(string nm, Position pos, int off, int def, int pass, int reb) {
    name = nm;
    position = pos;
    offense = off;
    defense = def;
    passing = pass;
    rebound = reb;
} 