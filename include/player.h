#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
void inputPlayers();

struct Player
{
    std::string name;
    int position;
    std::vector<int> pathHistory; // NEW: to store their journey
};

#endif