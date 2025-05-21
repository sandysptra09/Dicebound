#include "board.h"
#include "player.h"
#include <iostream>
#include <iomanip>

using namespace std;

Board::Board() {
    generateCrazyBoard();
}

void Board::generateCrazyBoard() {
    // Membuat struktur graph dengan 25 tile
    for (int i = 0; i < 25; ++i) {
        nodes[i] = Node{i, {}};
    }
    for (int i = 0; i < 24; ++i) {
        nodes[i].neighbors.push_back(i + 1); // linear path
    }
    // Shortcut atau jebakan
    nodes[5].neighbors.push_back(10);
    nodes[15].neighbors.push_back(20);
    nodes[23].neighbors.push_back(2);  // trap balik
}

void Board::drawBoard(const vector<Player>& players) {
    cout << "\n========== 🧭 BOARD STATUS ==========\n";
    for (int i = 0; i < 25; ++i) {
        cout << "[" << setw(2) << i;
        for (const auto& p : players) {
            if (p.position == i) cout << ":" << p.name[0];
        }
        cout << "] ";
        if ((i + 1) % 5 == 0) cout << endl;
    }
    cout << "=====================================\n";
}
