#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "game.h"
#include "player.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#endif

using namespace std;

void ShowMainMenu()
{
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

        const string title1 = " _______   __    ______  _______ .______     ______    __    __  .__   __.  _______  ";
        const string title2 = "|       \\ |  |  /      ||   ____||   _  \\   /  __  \\  |  |  |  | |  \\ |  | |       \\ ";
        const string title3 = "|  .--.  ||  | |  ,----'|  |__   |  |_)  | |  |  |  | |  |  |  | |   \\|  | |  .--.  |";
        const string title4 = "|  |  |  ||  | |  |     |   __|  |   _  <  |  |  |  | |  |  |  | |  . `  | |  |  |  |";
        const string title5 = "|  '--'  ||  | |  `----.|  |____ |  |_)  | |  `--'  | |  `--'  | |  |\\   | |  '--'  |";
        const string title6 = "|_______/ |__|  \\______||_______||______/   \\______/   \\______/  |__| \\__| |_______/ ";
        const string title7 = "                                                                                     ";

        const string titles[] = {
            title1, title2, title3, title4, title5, title6, title7};

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
                {
                        cout << string(paddingLeft, ' ') << line << endl;
                }

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

int main()
{
        ShowMainMenu();

        srand(time(0));

        int choice;
        do
        {
                cout << "=== ULAR TANGGA GRAPH ===\n";
                cout << "1. Play\n";
                cout << "2. Exit\n";
                cout << "Pilih: ";
                cin >> choice;

                if (choice == 1)
                {
                        do
                        {
                                cout << "Masukkan jumlah pemain (1-4): ";
                                cin >> numPlayers;
                        } while (numPlayers < 1 || numPlayers > MAX_PLAYERS);

                        cin.ignore(); // Bersihkan newline dari buffer

                        inputPlayers(); // <-- Input nama pemain

                        initializeGraph();
                        initializePlayers(); // Inisialisasi posisi awal pemain
                        determineTurnOrder();
                        displayBoard();

                        while (true)
                        {
                                playTurn();
                                cout << "\nTekan ENTER untuk giliran berikutnya...";
                                cin.ignore();
#ifdef _WIN32
                                system("cls");
#else
                                system("clear");
#endif
                        }
                }
                else if (choice == 2)
                {
                        cout << "Keluar dari game.\n";
                }
                else
                {
                        cout << "Pilihan tidak valid.\n";
                }
        } while (choice != 2);

        return 0;
}
