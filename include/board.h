#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <map>
#include <string>

// ===== GRAPH STRUCTURE =====
// Representasi node sebagai tile di board
struct Node {
    int id;
    std::vector<int> neighbors;
};

class Board {
private:
    std::map<int, Node> nodes;
public:
    Board();
    void generateCrazyBoard(); // Membuat board sebagai graph
    void drawBoard(const std::vector<class Player>& players);
};

#endif
