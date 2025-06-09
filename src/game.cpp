#include "game.h"
#include "board.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "suit.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

Queue turnQueue;

void createQueue()
{
    turnQueue.front = 0;
    turnQueue.rear = -1;
    turnQueue.top = 0;
}

bool isEmpty()
{
    return turnQueue.top == 0;
}

bool isFull()
{
    return turnQueue.top >= MAX_QUEUE;
}

void inQueue(int val)
{
    if (isFull())
        return;
    turnQueue.rear++;
    turnQueue.data[turnQueue.rear] = val;
    turnQueue.top++;
}

int deQueue()
{
    if (isEmpty())
        return -1;
    int val = turnQueue.data[0];
    for (int i = 0; i < turnQueue.rear; ++i)
    {
        turnQueue.data[i] = turnQueue.data[i + 1];
    }
    turnQueue.rear--;
    turnQueue.top--;
    return val;
}

void displayQueue()
{
    if (isEmpty())
    {
        cout << "Antrian kosong.\n";
    }
    else
    {
        cout << "Urutan giliran: ";
        for (int i = 0; i <= turnQueue.rear; ++i)
        {
            cout << players[turnQueue.data[i]].name << " ";
        }
        cout << endl;
    }
}

int find(int val)
{
    if (isEmpty())
        return -1;
    for (int i = 0; i <= turnQueue.rear; ++i)
    {
        if (turnQueue.data[i] == val)
            return i;
    }
    return -1;
}

int rollDice()
{
    return rand() % 6 + 1;
}

void determineTurnOrder()
{
    createQueue();
    vector<pair<int, int>> rolls;
    setcolor(12);
    cout << "\nMenentukan giliran awal dengan melempar dadu...\n";
    for (int i = 0; i < numPlayers; ++i)
    {
        int roll = rollDice();
        cout << players[i].name << " roll: " << roll << endl;
        rolls.push_back({roll, i});
    }
    sort(rolls.rbegin(), rolls.rend());
    for (auto &r : rolls)
    {
        inQueue(r.second);
    }

    displayQueue();
}

bool playMinigame(int playerIndex)
{
    cout << players[playerIndex].name << " memasuki minigame!\n";
    cout << "Tebak angka antara 1 sampai 3 (input manual): ";
    int correct = rand() % 3 + 1;
    int guess;
    cin >> guess;
    cout << "Jawaban benar: " << correct << endl;
    return guess == correct;
}

void playTurn()
{
    int currentPlayerIndex = deQueue();
    if (currentPlayerIndex == -1)
        return;

    Player &p = players[currentPlayerIndex];

    cout << "\n--- Giliran " << p.name << " ---\n";
    cout << "Tekan ENTER untuk melempar dadu...";
    cin.ignore();
    cin.get();

    int dice = rollDice();
    cout << p.name << " roll dadu: " << dice << endl;

    int stepsLeft = dice;
    while (stepsLeft-- > 0)
    {
        for (auto &edge : graph[p.position])
        {
            if (edge.weight == 1)
            {
                p.position = edge.to;
                break;
            }
        }
    }

    cout << p.name << " sekarang di petak " << p.position << endl;

    for (auto &edge : graph[p.position])
    {
        if (edge.weight != 1)
        {
            cout << p.name << " terkena ";
            if (edge.to > p.position)
                cout << "TANGGA!";
            else
                cout << "ULAR!";
            cout << " Lompat ke petak " << edge.to << endl;
            p.position = edge.to;
            break;
        }
    }

        if (p.position % 5 == 0 && p.position < 50)
    {
        bool win;
        int minigameType = rand() % 2; // 0 = tebak angka, 1 = suit

        if (minigameType == 0)
        {
            cout << "🎮 Minigame: Tebak Angka!\n";
            win = playMinigame(currentPlayerIndex);
        }
        else
        {
            cout << "🎮 Minigame: Suit Batu-Gunting-Kertas!\n";
            win = playSuit(players[currentPlayerIndex].name);
        }

        if (win)
        {
            cout << p.name << " menang minigame! Maju 3 petak.\n";
            for (int i = 0; i < 3; ++i)
            {
                for (auto &edge : graph[p.position])
                {
                    if (edge.weight == 1)
                    {
                        p.position = edge.to;
                        break;
                    }
                }
            }
        }
        else
        {
            cout << p.name << " kalah minigame! Mundur 3 petak.\n";
            for (int i = 0; i < 3; ++i)
            {
                for (auto &edge : graph[p.position])
                {
                    if (edge.weight == 1 && edge.to < p.position)
                    {
                        p.position = edge.to;
                        break;
                    }
                }
            }
        }

        cout << p.name << " sekarang di petak " << p.position << endl;
        // Delay supaya pemain bisa lihat hasil
        cout << "Tekan ENTER untuk lanjut ke pemain berikutnya...";
        cin.ignore(); // penting untuk hapus newline dari input sebelumnya
        cin.get();    // tunggu ENTER
    }


    displayBoard();

    if (p.position >= 50)
    {
        cout << "\n🎉 " << p.name << " MENANG! 🎉\n";
        exit(0);
    }

    inQueue(currentPlayerIndex);
}
