#include "board.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

vector<Edge> graph[NUM_VERTICES + 1];
Player players[MAX_PLAYERS];
int numPlayers = 0;

void initializeGraph()
{
    for (int i = 1; i < NUM_VERTICES; ++i)
    {
        if (i + 1 <= NUM_VERTICES)
            graph[i].push_back({i + 1, 1});
    }

    // Ladders (L)
    graph[3].push_back({13, 5});
    graph[8].push_back({17, 6});
    graph[19].push_back({29, 5});
    graph[24].push_back({40, 7});
    graph[36].push_back({48, 5});
    
    // Snakes (S)
    graph[14].push_back({5, 4});
    graph[31].push_back({19, 4});
    graph[47].push_back({28, 6});
    graph[49].push_back({34, 7});
}

void initializePlayers()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i].position = 1;
        players[i].pathHistory.push_back(1);
    }
}

// Helper function to check if a cell has a ladder
bool hasLadder(int cell)
{
    return (cell == 3 || cell == 8 || cell == 19 || cell == 24 || cell == 36);
}

// Helper function to check if a cell has a snake
bool hasSnake(int cell)
{
    return (cell == 14 || cell == 31 || cell == 47 || cell == 49);
}

bool hasMinigame(int cell)
{
    return (cell % 5 == 0 && cell > 0 && cell <= 45);
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

        // Baris snake/ladder indicators
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            string indicator = " ";
            if (hasLadder(cells[c]))
                indicator = "L";
            else if (hasSnake(cells[c]))
                indicator = "S";
            else if (hasMinigame(cells[c]))
                indicator = "M";
            
            cout.width(cellWidth);
            cout << left << indicator;
        }
        cout << "|\n";

        // Baris pemain di setiap sel
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            string playerMark = " ";
            for (int i = 0; i < numPlayers; i++)
            {
                if (players[i].position == cells[c])
                {
                    string symbol = string(1, toupper(players[i].name[0])) + to_string(i + 1);
                    if (playerMark == " ")
                        playerMark = symbol;
                    else
                        playerMark += "," + symbol;
                }
            }
            cout.width(cellWidth);
            cout << left << playerMark;
        }
        cout << "|\n";
    }

    printBorder();
    
    cout << "\nLegend:\n";
    cout << "L = Ladder (naik)   S = Snake (turun)  M = Minigame\n";
}