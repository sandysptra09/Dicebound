#include "player.h"
#include "board.h"
#include <iostream>
using namespace std;

void inputPlayers()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Masukkan nama pemain " << i + 1 << ": ";
        getline(cin, players[i].name);
    }
}
