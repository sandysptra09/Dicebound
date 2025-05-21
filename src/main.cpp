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
    initializePlayers();
    initializeGraph();
    determineTurnOrder();
    displayBoard();

    while (true)
    {
        playTurn();
        cout << "\nTekan ENTER untuk giliran berikutnya...";
        cin.ignore();
        cin.get();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    return 0;
}