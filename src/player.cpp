#include "board.h"
#include <iostream>
#include <limits>

using namespace std;

int actualNumPlayers = NUM_PLAYERS;

void inputPlayers()
{
    cout << "Masukkan jumlah pemain (1-4): ";
    int n;
    while (true)
    {
        cin >> n;
        if (cin.fail() || n < 1 || n > 4)
        {
            cout << "Jumlah pemain tidak valid. Masukkan antara 1 sampai 4: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }

    actualNumPlayers = n;
    cin.ignore();

    for (int i = 0; i < actualNumPlayers; ++i)
    {
        cout << "Masukkan nama untuk Player " << i + 1 << ": ";
        getline(cin, players[i].name);
        players[i].position = 1;
    }

    for (int i = actualNumPlayers; i < NUM_PLAYERS; ++i)
    {
        players[i].name = "";
        players[i].position = -1;
    }
}
