#include "player.h"
#include "board.h"
#include <iostream>
using namespace std;

void inputPlayers()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        while (true)
        {
            cout << "Masukkan nama pemain " << i + 1 << ": ";
            getline(cin, players[i].name);
            if (!players[i].name.empty())
                break;
            cout << "❗ Nama tidak boleh kosong.\n";
        }
    }
}
