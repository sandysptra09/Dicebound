#include "game.h"
#include "board.h"
#include "player.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <queue>        // QUEUE digunakan untuk giliran pemain
#include <vector>
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

using namespace std;
using namespace chrono;

// ===== TREE STRUCTURE FOR MINIGAME =====
// Node untuk tree minigame yang menyimpan prompt dan opsi
struct MinigameNode {
    string prompt;
    vector<MinigameNode*> options;
    MinigameNode(string p) : prompt(p) {}
};

class MinigameTree {
public:
    MinigameNode* root;
    MinigameTree() {
        // Membuat tree keputusan minigame
        root = new MinigameNode("You find 3 treasure chests. Which one do you open?");
        root->options.push_back(new MinigameNode("Trap! Lose a turn."));
        root->options.push_back(new MinigameNode("Gold! Move +3 tiles."));
        root->options.push_back(new MinigameNode("Enemy! You must win a math challenge."));
    }

    // Mainkan minigame berdasarkan tree
    int play() {
        #ifdef _WIN32
        PlaySoundA("SystemAsterisk", NULL, SND_ALIAS | SND_ASYNC);
        #endif

        MinigameNode* cur = root;
        cout << "\n\033[1;36m[MINIGAME] \033[0m" << cur->prompt << endl;
        for (int i = 0; i < (int)cur->options.size(); i++) {
            cout << i + 1 << ". " << cur->options[i]->prompt << endl;
        }
        int choice;
        cin >> choice;

        if (choice == 1) return -1;    // Trap, mundur/lose turn
        if (choice == 2) return 3;     // Dapat bonus maju 3 langkah
        if (choice == 3) {             // Tantangan matematika
            int a = rand() % 10 + 1, b = rand() % 10 + 1, ans;
            cout << "Solve: " << a << " + " << b << " = ";
            cin >> ans;
            return ans == a + b ? 2 : -1;
        }
        return 0;
    }
};

Game::Game() {
    srand(time(0));
}

// Fungsi untuk animasi teks muncul perlahan
void animatedText(string text, int delay) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(milliseconds(delay));
    }
    cout << endl;
}

// Fungsi animasi dadu dengan visual dice face
void showDiceAnimation(int result) {
    vector<vector<string>> faces = {
        {"+-----+", "|     |", "|  *  |", "|     |", "+-----+"},
        {"+-----+", "| *   |", "|     |", "|   * |", "+-----+"},
        {"+-----+", "| *   |", "|  *  |", "|   * |", "+-----+"},
        {"+-----+", "| * * |", "|     |", "| * * |", "+-----+"},
        {"+-----+", "| * * |", "|  *  |", "| * * |", "+-----+"},
        {"+-----+", "| * * |", "| * * |", "| * * |", "+-----+"},
    };
    for (int i = 0; i < 10; i++) {
        int temp = rand() % 6;
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        for (const auto& line : faces[temp]) cout << line << endl;
        this_thread::sleep_for(milliseconds(100));
    }
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    for (const auto& line : faces[result - 1]) cout << line << endl;
    cout << "\n🎲 Dice Result: " << result << "!\a\n";
    this_thread::sleep_for(seconds(2));
}

// Fungsi lempar dadu, hasil 1-6
int rollDice() {
    int result = rand() % 6 + 1;
    showDiceAnimation(result);
    return result;
}

// Animasi game over dan pengumuman pemenang
void gameOverAnimation(string winner) {
    cout << "\n\033[1;31m================== GAME OVER ==================\033[0m\n";
    animatedText("\n🏆 WINNER: " + winner + " 🏆", 100);
    string fireworks[] = {
        "     *     *     *",
        "   *    *    *    *",
        "*   *    *   *   *",
        "   *  🎆 YOU WIN 🎆 *",
        "*  *   *   *   *   *",
    };
    for (const auto& line : fireworks) {
        cout << "\033[1;33m" << line << "\033[0m\n";
        this_thread::sleep_for(milliseconds(200));
    }
    cout << "\033[1;31m==============================================\033[0m\n";
    this_thread::sleep_for(seconds(3));
}

// Main game loop dan logika permainan
void Game::start() {
    animatedText("✨ WELCOME TO...", 100);
    animatedText("🔥 THE ULTIMATE BOARD BATTLE ARENA 🔥", 70);
    animatedText("Prepare for chaos, minigames, traps... and GLORY!", 50);

    Board board;
    board.generateCrazyBoard(); // Graph digunakan di sini untuk board

    queue<Player> turnQueue; // QUEUE untuk giliran pemain (FIFO)
    vector<Player> players;  // Menyimpan data pemain aktif

    int n;
    cout << "\nEnter number of players: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        string name;
        cout << "Player " << i + 1 << " name: ";
        cin >> name;
        Player p(name);
        turnQueue.push(p);
        players.push_back(p);
    }

    MinigameTree mini; // TREE untuk minigame

    bool gameOver = false;
    while (!gameOver) {
        Player current = turnQueue.front();
        turnQueue.pop();

        animatedText("\nIt's " + current.name + "'s turn!", 40);
        int roll = rollDice();
        current.moveTo(current.position + roll);

        if (current.position >= 24) {
            gameOverAnimation(current.name);
            gameOver = true;
            break;
        }

        // Checkpoint: trigger minigame
        if (current.position % 6 == 0 && current.position != 0) {
            animatedText("Checkpoint reached! Time for a mini-game!", 40);
            int result = mini.play();
            current.moveTo(current.position + result);
        }

        // Update posisi di vector players
        for (auto& p : players) {
            if (p.name == current.name) {
                p = current;
                break;
            }
        }

        board.drawBoard(players);

        turnQueue.push(current);

        this_thread::sleep_for(seconds(2));
    }
}
