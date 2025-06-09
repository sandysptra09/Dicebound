#include "game.h"
#include "board.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "suit.h"
#include "blackjack.h"


#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

Queue turnQueue;

// Fungsi untuk delay/sleep lintas platform
void gameDelay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

// ASCII art untuk dadu
void drawDice(int value) {
    cout << "\n";
    switch(value) {
        case 1:
            cout << "┌─────────┐\n";
            cout << "│         │\n";
            cout << "│    ●    │\n";
            cout << "│         │\n";
            cout << "└─────────┘\n";
            break;
        case 2:
            cout << "┌─────────┐\n";
            cout << "│  ●      │\n";
            cout << "│         │\n";
            cout << "│      ●  │\n";
            cout << "└─────────┘\n";
            break;
        case 3:
            cout << "┌─────────┐\n";
            cout << "│  ●      │\n";
            cout << "│    ●    │\n";
            cout << "│      ●  │\n";
            cout << "└─────────┘\n";
            break;
        case 4:
            cout << "┌─────────┐\n";
            cout << "│  ●   ●  │\n";
            cout << "│         │\n";
            cout << "│  ●   ●  │\n";
            cout << "└─────────┘\n";
            break;
        case 5:
            cout << "┌─────────┐\n";
            cout << "│  ●   ●  │\n";
            cout << "│    ●    │\n";
            cout << "│  ●   ●  │\n";
            cout << "└─────────┘\n";
            break;
        case 6:
            cout << "┌─────────┐\n";
            cout << "│  ●   ●  │\n";
            cout << "│  ●   ●  │\n";
            cout << "│  ●   ●  │\n";
            cout << "└─────────┘\n";
            break;
    }
    cout << "\n";
}

// Fungsi queue - implementasi yang sudah ada
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

// Fungsi roll dadu dengan animasi
int rollDiceAnimated() {
    cout << "\n🎲 Melempar dadu...\n";
    
    // Animasi rolling (menampilkan angka acak beberapa kali)
    for(int i = 0; i < 8; i++) {
        int randomShow = rand() % 6 + 1;
        
        // Clear previous line and show dice
        cout << "\r🎲 Rolling... " << randomShow << "  ";
        cout.flush();
        
        gameDelay(200 + i * 50); // Delay bertambah untuk efek melambat
    }
    
    // Hasil akhir
    int finalResult = rand() % 6 + 1;
    cout << "\r🎉 HASIL DADU! 🎉         \n";
    drawDice(finalResult);
    cout << "Nilai: " << finalResult << "\n";
    
    gameDelay(1000); // Pause sebentar untuk melihat hasil
    
    return finalResult;
}

// Update fungsi rollDice dengan animasi
int rollDice()
{
    return rollDiceAnimated();
}

void determineTurnOrder()
{
    createQueue();
    vector<pair<int, int>> rolls;
    setcolor(12);
    cout << "\n=== MENENTUKAN GILIRAN AWAL ===\n";
    cout << "Setiap pemain akan melempar dadu!\n\n";
    
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "🎯 Giliran " << players[i].name << "!\n";
        cout << "Tekan ENTER untuk melempar dadu...";
        cin.get();
        
        int roll = rollDiceAnimated();
        cout << players[i].name << " mendapat: " << roll << "\n";
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        
        rolls.push_back({roll, i});
        gameDelay(500);
    }
    
    sort(rolls.rbegin(), rolls.rend());
    for (auto &r : rolls)
    {
        inQueue(r.second);
    }

    cout << "\n🏆 URUTAN GILIRAN DITENTUKAN! 🏆\n";
    displayQueue();
}

bool playMinigame(int playerIndex)
{
    cout << players[playerIndex].name << " memasuki minigame tebak angka!\n";
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

    cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "👤 GILIRAN " << p.name << " 👤\n";
    cout << "Posisi saat ini: Petak " << p.position << "\n";
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    cout << "Tekan ENTER untuk melempar dadu...";
    cin.get();

    int dice = rollDiceAnimated();
    cout << p.name << " bergerak " << dice << " langkah!\n";

    // Animasi pergerakan
    cout << "🚶 Bergerak";
    int stepsLeft = dice;
    while (stepsLeft-- > 0)
    {
        cout << ".";
        cout.flush();
        gameDelay(400);
        
        for (auto &edge : graph[p.position])
        {
            if (edge.weight == 1)
            {
                p.position = edge.to;
                break;
            }
        }
    }
    cout << "\n";

    cout << "📍 " << p.name << " sekarang di petak " << p.position << endl;

    // Cek ular/tangga dengan animasi
    for (auto &edge : graph[p.position])
    {
        if (edge.weight != 1)
        {
            cout << "\n";
            if (edge.to > p.position)
            {
                cout << "🪜 TANGGA! " << p.name << " naik ke petak " << edge.to << "! 🎉\n";
            }
            else
            {
                cout << "🐍 ULAR! " << p.name << " turun ke petak " << edge.to << "! 😱\n";
            }
            p.position = edge.to;
            gameDelay(1000);
            break;
        }
    }

    // Minigame logic yang sudah ada (dengan 2 jenis minigame)
    if (p.position % 5 == 0 && p.position < 50)
    {
        bool win;
        int minigameType = rand() % 2; // 0 = tebak angka, 1 = suit

        cout << "\n🎮 MINIGAME ZONE! 🎮\n";
        
        if (minigameType == 0)
        {
            cout << "🃏 Minigame: Blackjack!\n";
            win = playBlackjack(players[currentPlayerIndex].name);
        }
        else
        {
            cout << "✂️ Minigame: Suit Batu-Gunting-Kertas!\n";
            win = playSuit(players[currentPlayerIndex].name);
        }

        if (win)
        {
            cout << "🎉 " << p.name << " menang minigame! Maju 3 petak.\n";
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
            cout << "😔 " << p.name << " kalah minigame! Mundur 3 petak.\n";
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

        cout << "📍 " << p.name << " sekarang di petak " << p.position << endl;
        // Delay supaya pemain bisa lihat hasil
        cout << "Tekan ENTER untuk lanjut ke pemain berikutnya...";
        cin.get();    // tunggu ENTER
    }

    displayBoard();

    if (p.position >= 50)
    {
        cout << "\n🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊\n";
        cout << "🏆 " << p.name << " MENANG! 🏆\n";
        cout << "🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊🎊\n";
        exit(0);
    }

    inQueue(currentPlayerIndex);
}