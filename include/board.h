#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "player.h"
#include <windows.h>

const int NUM_VERTICES = 50;
const int MAX_PLAYERS = 4;

struct Edge
{
    int to;
    int weight;
};

extern std::vector<Edge> graph[NUM_VERTICES + 1];
extern Player players[MAX_PLAYERS];
extern int numPlayers;

void setcolor(unsigned short color);
void initializeGraph();
void initializePlayers();
void displayBoard();

#endif
