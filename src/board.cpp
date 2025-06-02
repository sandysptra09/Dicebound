#include "board.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

std::vector<Edge> graph[NUM_VERTICES + 1];
Player players[MAX_PLAYERS];
int numPlayers = 0;

void initializeGraph() {
    for (int i = 1; i < NUM_VERTICES; ++i) {
        if (i + 1 <= NUM_VERTICES)
            graph[i].push_back({i + 1, 1});
    }

    graph[3].push_back({13, 5});
    graph[8].push_back({17, 6});
    graph[20].push_back({29, 5});
    graph[25].push_back({40, 7});
    graph[35].push_back({48, 5});
    graph[14].push_back({5, 4});
    graph[31].push_back({19, 4});
    graph[45].push_back({28, 6});
    graph[49].push_back({34, 7});
}

void initializePlayers() {
    for (int i = 0; i < numPlayers; ++i) {
        players[i].name = "Player " + to_string(i + 1);
        players[i].position = 1;
    }
}


void displayBoard()
{
    cout << "=== GAME BOARD ===\n";

    int rows = 5;
    int cols = 10;
    int cellWidth = 8;

    auto printBorder = [&]()
    {
        for (int i = 0; i < cols; i++)
        {
            cout << "+";
            for (int j = 0; j < cellWidth; j++)
                cout << "-";
        }
        cout << "+\n";
    };

    for (int r = rows - 1; r >= 0; r--)
    {
        vector<int> cells(cols);
        int base = r * cols + 1;
        if (r % 2 == 0)
        {
            for (int c = 0; c < cols; c++)
                cells[c] = base + c;
        }
        else
        {
            for (int c = 0; c < cols; c++)
                cells[c] = base + (cols - 1 - c);
        }

        printBorder();

        // Baris angka sel
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            cout.width(cellWidth);
            cout << left << cells[c];
        }
        cout << "|\n";

        // Baris pemain di setiap sel
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            string playerMark = " ";
            for (int i = 0; i < numPlayers; i++)  // Diganti dari NUM_PLAYERS
            {
                if (players[i].position == cells[c])
                {
                    if (playerMark == " ")
                        playerMark = "P" + to_string(i + 1);
                    else
                        playerMark += ",P" + to_string(i + 1);
                }
            }
            cout.width(cellWidth);
            cout << left << playerMark;
        }
        cout << "|\n";
    }
    printBorder();
}
