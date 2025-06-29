#include "board.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//
vector<Edge> graph[NUM_VERTICES + 1];

//
Player players[MAX_PLAYERS];

//
int numPlayers = 0;

// initialize graph with edges representing the board
void initializeGraph()
{
    // create edges for the board
    for (int i = 1; i < NUM_VERTICES; ++i)
    {
        if (i + 1 <= NUM_VERTICES)
            graph[i].push_back({i + 1, 1});
    }

    // create edges for ladders with weights
    graph[3].push_back({13, 5});
    graph[8].push_back({17, 6});
    graph[19].push_back({29, 5});
    graph[24].push_back({40, 7});
    graph[36].push_back({48, 5});

    // create edges for snakes with weights
    graph[14].push_back({5, 4});
    graph[31].push_back({19, 4});
    graph[47].push_back({28, 6});
    graph[49].push_back({34, 7});
}

// initialize players position and path history
void initializePlayers()
{
    for (int i = 0; i < numPlayers; ++i)
    {
        players[i].position = 1;
        players[i].pathHistory.push_back(1);
    }
}

// helper function to check if a cell has a ladder
bool hasLadder(int cell)
{
    return (cell == 3 || cell == 8 || cell == 19 || cell == 24 || cell == 36);
}

// helper function to check if a cell has a snake
bool hasSnake(int cell)
{
    return (cell == 14 || cell == 31 || cell == 47 || cell == 49);
}

// helper function to check if a cell has a minigame
bool hasMinigame(int cell)
{
    return (cell % 5 == 0 && cell > 0 && cell <= 45);
}

// display the game board with players, ladders, snakes, and minigames
void displayBoard()
{
    cout << "=== GAME BOARD ===\n";

    int rows = 5;
    int cols = 10;
    int cellWidth = 10;

    // ANSI color codes
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";

    // helper function to print a border
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

        // row cell numbers
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            cout.width(cellWidth);
            cout << left << cells[c];
        }
        cout << "|\n";

        // row: ladders (L), snakes (S), minigames (M)
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            string mark = "";
            if (hasLadder(cells[c]))
                mark = YELLOW + "L" + RESET;
            else if (hasSnake(cells[c]))
                mark = RED + "S" + RESET;
            else if (hasMinigame(cells[c]))
                mark = GREEN + "M" + RESET;

            int visualLen = mark.empty() ? 0 : 1;
            cout << mark;
            for (int i = 0; i < cellWidth - visualLen; ++i)
                cout << " ";
        }
        cout << "|\n";

        const string COLORS[] = {
            "\033[36m", // Player 1: Cyan
            "\033[35m", // Player 2: Magenta
            "\033[34m", // Player 3: Blue
            "\033[92m"  // Player 4: Bright Green
        };
        const string RESET = "\033[0m";

        // row player positions
        for (int c = 0; c < cols; c++)
        {
            cout << "|";
            string mark = "";
            int visualLength = 0;

            for (int i = 0; i < numPlayers; i++)
            {
                if (players[i].position == cells[c])
                {
                    string symbol = string(1, toupper(players[i].name[0])) + to_string(i + 1);
                    string coloredSymbol = COLORS[i % 4] + symbol + RESET;

                    if (!mark.empty()) {
                        mark += ",";
                        visualLength++; // ini baru nambah koma secara tepat
                    }
                mark += coloredSymbol;
                visualLength += symbol.length();
                }
            }

            cout << mark;

            for (int i = 0; i < cellWidth - visualLength; ++i)
                cout << " ";
        }
        cout << "|\n";
    }

    printBorder();

    cout << "\nLegend:\n";
    cout << YELLOW << "L" << RESET << " = Ladder (naik)   "
         << RED << "S" << RESET << " = Snake (turun)   "
         << GREEN << "M" << RESET << " = Minigame\n";
}
