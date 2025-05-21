#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <stack>

// ===== STACK STRUCTURE =====
// Stack untuk menyimpan history posisi
class Player {
public:
    std::string name;
    int position;
    std::stack<int> moveHistory;

    Player(std::string n);
    void moveTo(int pos);
};

#endif
