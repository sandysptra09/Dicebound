// #include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "board.h"
#include "game.h"
#include "player.h"
#include "suit.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#endif

using namespace std;

extern bool gameEnded;

void ShowMainMenu()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    const string titles[] = {
        " _______   __    ______  _______ .______     ______    __    __  .__   __.  _______  ",
        "|       \\ |  |  /      ||   ____||   _  \\   /  __  \\  |  |  |  | |  \\ |  | |       \\ ",
        "|  .--.  ||  | |  ,----'|  |__   |  |_)  | |  |  |  | |  |  |  | |   \\|  | |  .--.  |",
        "|  |  |  ||  | |  |     |   __|  |   _  <  |  |  |  | |  |  |  | |  . `  | |  |  |  |",
        "|  '--'  ||  | |  `----.|  |____ |  |_)  | |  `--'  | |  `--'  | |  |\\   | |  '--'  |",
        "|_______/ |__|  \\______||_______||______/   \\______/   \\______/  |__| \\__| |_______/ ",
        "                                                                                     "};

    const int paddingLeft = 5;
    const int centerOffset = paddingLeft + 25;
    int blinkCounter = 0;

    while (
#ifdef _WIN32
        !_kbhit()
#else
        true
#endif
    )
    {
#ifdef _WIN32
        system("cls");
        SetConsoleTextAttribute(hConsole, 11);
#else
        system("clear");
#endif

        for (const auto &line : titles)
            cout << string(paddingLeft, ' ') << line << endl;

#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 7);
#endif
        cout << endl;

        if (blinkCounter % 10 < 5)
        {
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 14);
#endif
            cout << string(centerOffset, ' ') << "Press any key to play..." << endl;
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 7);
#endif
        }
        else
        {
            cout << endl;
        }

#ifdef _WIN32
        Sleep(100);
#else
        usleep(100000);
#endif
        blinkCounter++;

#ifndef _WIN32
        if (blinkCounter > 50)
            break;
#endif
    }

#ifdef _WIN32
    _getch();
#endif
    system("cls");
}

void showRulesAndTips()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    cout << "\n";
    cout << "╔══════════════════════════════════════════╗\n";
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, 14);
#endif
    cout << "║            📜 PERATURAN & TIPS           ║\n";
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, 7);
#endif
    cout << "╚══════════════════════════════════════════╝\n";

    cout << "🎯 Tujuan:\n";
    cout << "   Capai kotak terakhir lebih dulu!\n\n";

    cout << "🎲 Cara Main:\n";
    cout << "   - Setiap giliran, lempar dadu dan maju sesuai angka.\n";
    cout << "   - 🐍 Kena ular? Kamu akan turun!\n";
    cout << "   - 🪜 Kena tangga? Kamu naik lebih cepat!\n\n";

    cout << "👥 Pemain pertama ditentukan berdasarkan hasil roll dadu tertinggi.\n";
    cout << "🎉 Selamat bermain dan semoga beruntung!\n\n";

    cout << "🎮 Minigames (Permainan Mini):\n";
    cout << "   Selama permainan, kamu bisa menghadapi tantangan minigame berikut:\n\n";

    cout << "   🃏 **Blackjack**:\n";
    cout << "      - Pemain dan dealer (komputer) masing-masing mendapat kartu.\n";
    cout << "      - Tujuanmu adalah mencapai total kartu sedekat mungkin ke 21.\n";
    cout << "      - Tapi hati-hati, jika melebihi 21, kamu kalah otomatis (bust).\n";
    cout << "      - Menang = maju 3 petak!\n";
    cout << "      - Kalah = diam ditempat.\n\n";

    cout << "   ✊✋✌️ **Suit (Batu-Gunting-Kertas)**:\n";
    cout << "      - Pilih antara batu, gunting, atau kertas.\n";
    cout << "      - Batu menang lawan gunting, gunting menang lawan kertas,\n";
    cout << "        dan kertas menang lawan batu.\n";
    cout << "      - Melawan komputer secara acak.\n";
    cout << "      - Menang = lempar dadu tambahan!\n";
    cout << "      - Seri = diam ditempat.\n";
    cout << "      - Kalah = diam ditempat.\n";

    cout << "\n📌 Tips:\n";
    cout << "   - Gunakan minigame untuk membalikkan keadaan!\n";
    cout << "   - Ambil risiko saat tepat, tapi jangan terlalu nekat 😏\n";

    cout << "\n";
    cin.ignore();
}

int main()
{
    ShowMainMenu();
    srand(time(0));

    int choice;
    do
    {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 13);
#endif
        cout << "\n╔════════════════════════════════╗\n";
        cout << "║        🎮 MAIN MENU            ║\n";
        cout << "╠════════════════════════════════╣\n";
#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 11);
#endif
        cout << "║ 1. ▶️  Play                     ║\n";
        cout << "║ 2. ❌ Exit                     ║\n";
        cout << "╚════════════════════════════════╝\n";

#ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 14);
#endif

        while (true)
        {
            cout << "Pilih opsi (1/2): ";
            if (cin >> choice && (choice == 1 || choice == 2))
            {
                break;
            }
            else
            {
#ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
#endif
                cout << "❗ Input tidak valid. Masukkan angka 1 atau 2.\n\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        SetConsoleTextAttribute(hConsole, 10);
        if (choice == 1)
        {
            cout << "\nMenampilkan peraturan & tips...\n";
#ifdef _WIN32
            Sleep(1000);
#else
            usleep(1000000);
#endif
            showRulesAndTips();

            bool mainLagi = true;
            while (mainLagi)
            {
                do
                {
#ifdef _WIN32
                    SetConsoleTextAttribute(hConsole, 11);
#endif
                    cout << "\nMasukkan jumlah pemain (2-4): ";
                    if (!(cin >> numPlayers) || numPlayers < 2 || numPlayers > MAX_PLAYERS)
                    {
#ifdef _WIN32
                        SetConsoleTextAttribute(hConsole, 12);
#endif
                        cout << "❗ Jumlah pemain harus antara 2 sampai 4.\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                } while (numPlayers < 2 || numPlayers > MAX_PLAYERS);

                cin.ignore();

                inputPlayers();
                initializeGraph();
                initializePlayers();
                determineTurnOrder();
                displayBoard();

                gameEnded = false;
                while (!gameEnded)
                {
                    playTurn();
                    if (!gameEnded)
                    {
                        cout << "\nTekan ENTER untuk giliran berikutnya...";
                        cin.ignore();
#ifdef _WIN32
                        system("cls");
#else
                        system("clear");
#endif
                    }
                }

                char ulang;
                cout << "\nApakah ingin main lagi? (y/n): ";
                cin >> ulang;
                cin.ignore();
                if (tolower(ulang) != 'y')
                {
                    mainLagi = false;
                }
                else
                {
#ifdef _WIN32
                    system("cls");
#else
                    system("clear");
#endif
                }
            }
        }
        else
        {
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 12);
#endif
            cout << "\nKeluar dari game. Sampai jumpa!\n";
        }
    } while (choice != 2);

    return 0;
}
