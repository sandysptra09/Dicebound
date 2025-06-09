#ifndef GAME_H
#define GAME_H

#define MAX_QUEUE 10

struct Queue
{
    int data[MAX_QUEUE];
    int front;
    int rear;
    int top;
};

extern Queue turnQueue;

void createQueue();
bool isEmpty();
bool isFull();
void inQueue(int val);
int deQueue();
void displayQueue();
int find(int val);

void determineTurnOrder();
bool playMinigame(int playerIndex);
void playTurn();
int rollDice();

#endif
