#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>
#include <string>
#include <map>

// Struktur kartu
struct Card {
    std::string rank;
    std::string suit;
};

// Global variables (bisa diakses dari file lain)
extern std::vector<Card> playerHand;
extern std::vector<Card> dealerHand;
extern std::vector<Card> deck;

// Fungsi-fungsi utama
void initializeDeck();
void shuffleDeck();
Card drawCard();
int calculateHandValue(const std::vector<Card>& hand);
void printHand(const std::vector<Card>& hand, bool hideFirstCard = false);
void playerTurn();
void dealerTurn();

bool playBlackjack(const std::string& playerName);

#endif
