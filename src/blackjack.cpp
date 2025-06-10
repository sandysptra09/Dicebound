#include "blackjack.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

vector<Card> playerHand;
vector<Card> dealerHand;
vector<Card> deck;

const vector<string> suits = {"♠", "♥", "♦", "♣"};
const vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

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
    srand(unsigned(time(nullptr)));
    shuffle(deck.begin(), deck.end(), default_random_engine(rand()));
}

Card drawCard()
{
    Card card = deck.back();
    deck.pop_back();
    return card;
}

int calculateHandValue(const vector<Card> &hand)
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
            value += stoi(card.rank);
        }
    }
    while (value > 21 && aceCount > 0)
    {
        value -= 10;
        aceCount--;
    }
    return value;
}

void printHand(const vector<Card> &hand, bool hideFirstCard)
{
    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            cout << "┌───────┐ ";
        }
        else
        {
            cout << "┌───────┐ ";
        }
    }
    cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            cout << "|*******| ";
        }
        else
        {
            cout << "|" << left << setw(2) << hand[i].rank << "     | ";
        }
    }
    cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        cout << "|       | ";
    }
    cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            cout << "|*******| ";
        }
        else
        {
            cout << "|   " << hand[i].suit << "   | ";
        }
    }
    cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        cout << "|       | ";
    }
    cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirstCard)
        {
            cout << "|*******| ";
        }
        else
        {
            cout << "|     " << right << setw(2) << hand[i].rank << "| ";
        }
    }
    cout << '\n';

    for (size_t i = 0; i < hand.size(); ++i)
    {
        cout << "└───────┘ ";
    }
    cout << '\n';
}

void playerTurn()
{
    while (true)
    {
        cout << "Your cards:\n";
        printHand(playerHand);
        int total = calculateHandValue(playerHand);
        cout << "Total: " << total << "\n";

        if (total > 21)
        {
            cout << "You busted!\n";
            return;
        }

        cout << "[1] Hit  [2] Stand\n> ";
        int choice;
        cin >> choice;

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
    cout << "\nDealer's turn...\n";
    while (calculateHandValue(dealerHand) < 17)
    {
        dealerHand.push_back(drawCard());
    }
    cout << "Dealer's cards:\n";
    printHand(dealerHand);
    cout << "Total: " << calculateHandValue(dealerHand) << "\n";
}

bool playBlackjack(const string &playerName)
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

    cout << "Dealer shows:\n";
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
        cout << "\nYou busted. Dealer wins!\n";
        return false;
    }
    else if (dealerTotal > 21)
    {
        cout << "\nDealer busted. You win!\n";
        return true;
    }
    else if (playerTotal > dealerTotal)
    {
        cout << "\nYou win!\n";
        return true;
    }
    else if (playerTotal < dealerTotal)
    {
        cout << "\nDealer wins!\n";
        return false;
    }
    else
    {
        cout << "\nIt's a tie!\n";
        return false; // misalnya tie dianggap kalah
    }
}
