#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "player.h"

const int NUM_VERTICES = 50;
const int NUM_PLAYERS = 4;

struct Edge
{
    int to;
    int weight;
};

extern std::vector<Edge> graph[NUM_VERTICES + 1];
extern Player players[NUM_PLAYERS];

void initializeGraph();
void initializePlayers();
void displayBoard();

#endif