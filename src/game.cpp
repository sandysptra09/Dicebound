#include "game.h"
#include "board.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

queue<int> turnQueue;

int rollDice() {
    return rand() % 6 + 1;
}

void determineTurnOrder() {
    vector<pair<int, int>> rolls;
    cout << "\nMenentukan giliran awal dengan melempar dadu...\n";
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        int roll = rollDice();
        cout << players[i].name << " roll: " << roll << endl;
        rolls.push_back({roll, i});
    }
    sort(rolls.rbegin(), rolls.rend());
    for (auto& r : rolls) {
        turnQueue.push(r.second);
    }
    cout << "\nUrutan giliran: ";
    queue<int> temp = turnQueue;
    while (!temp.empty()) {
        cout << players[temp.front()].name << " ";
        temp.pop();
    }
    cout << endl;
}

bool playMinigame(int playerIndex) {
    cout << players[playerIndex].name << " memasuki minigame!\n";
    cout << "Tebak angka antara 1 sampai 3 (input manual): ";
    int correct = rand() % 3 + 1;
    int guess;
    cin >> guess;
    cout << "Jawaban benar: " << correct << endl;
    return guess == correct;
}

void playTurn() {
    int currentPlayerIndex = turnQueue.front();
    turnQueue.pop();
    Player& p = players[currentPlayerIndex];

    cout << "\n--- Giliran " << p.name << " ---\n";
    cout << "Tekan ENTER untuk melempar dadu...";
    cin.ignore();
    cin.get();

    int dice = rollDice();
    cout << p.name << " roll dadu: " << dice << endl;

    int stepsLeft = dice;
    while (stepsLeft > 0) {
        bool moved = false;
        for (auto& edge : graph[p.position]) {
            if (edge.weight == 1) {
                p.position = edge.to;
                moved = true;
                break;
            }
        }
        if (!moved) break;
        stepsLeft--;
    }

    cout << p.name << " sekarang di petak " << p.position << endl;

    for (auto& edge : graph[p.position]) {
        if (edge.weight != 1) {
            cout << p.name << " terkena ";
            if (edge.to > p.position) cout << "TANGGA!";
            else cout << "ULAR!";
            cout << " Lompat ke petak " << edge.to << endl;
            p.position = edge.to;
            break;
        }
    }

    if (p.position % 5 == 0 && p.position < 50) {
        bool win = playMinigame(currentPlayerIndex);
        if (win) {
            cout << p.name << " menang minigame! Maju 3 petak.\n";
            for (int i = 0; i < 3; ++i) {
                for (auto& edge : graph[p.position]) {
                    if (edge.weight == 1) {
                        p.position = edge.to;
                        break;
                    }
                }
            }
        } else {
            cout << p.name << " kalah minigame! Mundur 3 petak.\n";
            for (int i = 0; i < 3; ++i) {
                for (auto& edge : graph[p.position]) {
                    if (edge.weight == 1 && edge.to < p.position) {
                        p.position = edge.to;
                        break;
                    }
                }
            }
        }
        cout << p.name << " sekarang di petak " << p.position << endl;
    }

    displayBoard();

    if (p.position >= 50) {
        cout << "\n🎉 " << p.name << " MENANG! 🎉\n";
        exit(0);
    }

    turnQueue.push(currentPlayerIndex);
}
