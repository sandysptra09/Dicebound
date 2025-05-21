#include "player.h"
using namespace std;

Player::Player(string n) : name(n), position(0) {}

void Player::moveTo(int pos) {
    moveHistory.push(position);  // simpan posisi sebelumnya
    position = pos;
    if (position > 24) position = 24;
}
