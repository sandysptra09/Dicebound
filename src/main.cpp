#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
#include "game.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int main()
{
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

                        cin.ignore(); // Buat cin.get() nanti

                        initializeGraph();
                        initializePlayers();
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
