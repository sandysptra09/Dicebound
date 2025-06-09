#include "blackjack.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

std::vector<Card> playerHand;
std::vector<Card> dealerHand;
std::vector<Card> deck;

const std::vector<std::string> suits = {"♠", "♥", "♦", "♣"};
const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

void initializeDeck()
{
    deck.clear();
    for (const auto &suit : suits)
    {
        for (const auto &rank : ranks)
        {
            deck.push_back({rank, suit});
        }
    }
}

void shuffleDeck()
{
    std::srand(unsigned(std::time(nullptr)));
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(std::rand()));
}

Card drawCard()
{
    Card card = deck.back();
    deck.pop_back();
    return card;
}

int calculateHandValue(const std::vector<Card> &hand)
{
    int value = 0;
    int aceCount = 0;
    for (const auto &card : hand)
    {
        if (card.rank == "A")
        {
            value += 11;
            aceCount++;
        }
        else if (card.rank == "K" || card.rank == "Q" || card.rank == "J")
        {
            value += 10;
        }
        else
        {
            value += std::stoi(card.rank);
        }
    }
    while (value > 21 && aceCount > 0)
    {
        value -= 10;
        aceCount--;
    }
    return value;
}

void printHand(const std::vector<Card> &hand, bool hideFirstCard)
{
    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            std::cout << "┌───────┐ ";
        }
        else
        {
            std::cout << "┌───────┐ ";
        }
    }
    std::cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            std::cout << "|*******| ";
        }
        else
        {
            std::cout << "|" << std::left << std::setw(2) << hand[i].rank << "     | ";
        }
    }
    std::cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        std::cout << "|       | ";
    }
    std::cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            std::cout << "|*******| ";
        }
        else
        {
            std::cout << "|   " << hand[i].suit << "   | ";
        }
    }
    std::cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        std::cout << "|       | ";
    }
    std::cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            std::cout << "|*******| ";
        }
        else
        {
            std::cout << "|     " << std::right << std::setw(2) << hand[i].rank << "| ";
        }
    }
    std::cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        std::cout << "└───────┘ ";
    }
    std::cout << '\n';
}

void playerTurn()
{
    while (true)
    {
        std::cout << "Your cards:\n";
        printHand(playerHand);
        int total = calculateHandValue(playerHand);
        std::cout << "Total: " << total << "\n";

        if (total > 21)
        {
            std::cout << "You busted!\n";
            return;
        }

        std::cout << "[1] Hit  [2] Stand\n> ";
        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            playerHand.push_back(drawCard());
        }
        else
        {
            break;
        }
    }
}

void dealerTurn()
{
    std::cout << "\nDealer's turn...\n";
    while (calculateHandValue(dealerHand) < 17)
    {
        dealerHand.push_back(drawCard());
    }
    std::cout << "Dealer's cards:\n";
    printHand(dealerHand);
    std::cout << "Total: " << calculateHandValue(dealerHand) << "\n";
}

bool playBlackjack(const std::string &playerName)
{
    playerHand.clear();
    dealerHand.clear();
    initializeDeck();
    shuffleDeck();

    // Deal 2 cards to player and dealer
    playerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());
    playerHand.push_back(drawCard());
    dealerHand.push_back(drawCard());

    std::cout << "Dealer shows:\n";
    printHand(dealerHand, true);

    playerTurn();

    if (calculateHandValue(playerHand) <= 21)
    {
        dealerTurn();
    }

    int playerTotal = calculateHandValue(playerHand);
    int dealerTotal = calculateHandValue(dealerHand);

    if (playerTotal > 21)
    {
        std::cout << "\nYou busted. Dealer wins!\n";
        return false;
    }
    else if (dealerTotal > 21)
    {
        std::cout << "\nDealer busted. You win!\n";
        return true;
    }
    else if (playerTotal > dealerTotal)
    {
        std::cout << "\nYou win!\n";
        return true;
    }
    else if (playerTotal < dealerTotal)
    {
        std::cout << "\nDealer wins!\n";
        return false;
    }
    else
    {
        std::cout << "\nIt's a tie!\n";
        return false; // misalnya tie dianggap kalah
    }
}
