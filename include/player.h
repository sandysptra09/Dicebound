#ifndef PLAYER_H
#define PLAYER_H

#include <string>

void inputPlayers();
extern int actualNumPlayers;

struct Player
{
    std::string name;
    int position;
};

#endif