#include "suit.h"
#include <conio.h>
#include <sstream>
#include <time.h>
#include <windows.h>
using namespace std;

// Define global variables
int setAngka = 0, skorU = 0, skorC = 0;

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void batu(int nilai) {
  if (nilai == 0) {
    gotoxy(27, 7); cout << "  _______    \n";
    gotoxy(27, 8); cout << " (____   '---\n";
    gotoxy(27, 9); cout << "(_____)      \n";
    gotoxy(27, 10); cout << "(_____)      \n";
    gotoxy(27, 11); cout << " (____)      \n";
    gotoxy(27, 12); cout << "  (___)__.---\n";
    gotoxy(30, 13); cout << "USER\n";
  } else if (nilai == 1) {
    cout << "    _______\n";
    cout << "---'   ____)\n";
    cout << "      (_____)\n";
    cout << "      (_____)\n";
    cout << "      (____)\n";
    cout << "---.__(___)\n";
    cout << "COMPUTER\n";
  }
}

void gunting(int nilai) {
  if (nilai == 0) {
    gotoxy(22, 7); cout << "       _______    \n";
    gotoxy(22, 8); cout << "  ____(____   '---\n";
    gotoxy(22, 9); cout << " (______          \n";
    gotoxy(22, 10); cout << "(__________       \n";
    gotoxy(22, 11); cout << "      (____)      \n";
    gotoxy(22, 12); cout << "       (___)__.---\n";
    gotoxy(30, 13); cout << "USER\n";
  } else if (nilai == 1) {
    cout << "    _______\n";
    cout << "---'   ____)____\n";
    cout << "          ______)\n";
    cout << "       __________)\n";
    cout << "      (____)\n";
    cout << "---.__(___)\n";
    cout << "COMPUTER\n";
  }
}

void kertas(int nilai) {
  if (nilai == 0) {
    gotoxy(23, 7); cout << "     _______     \n";
    gotoxy(23, 8); cout << " ___(____    '---\n";
    gotoxy(23, 9); cout << "(_____           \n";
    gotoxy(23, 10); cout << "(______          \n";
    gotoxy(23, 11); cout << " (______         \n";
    gotoxy(23, 12); cout << "   (_________.---\n";
    gotoxy(30, 13); cout << "USER\n";
  } else if (nilai == 1) {
    cout << "     _______\n";
    cout << "---'    ____)___\n";
    cout << "           _____)\n";
    cout << "          ______)\n";
    cout << "         ______)\n";
    cout << "---._________)\n";
    cout << "COMPUTER\n";
  }
}

void tampil(int computer, int user) {
  if (computer == 1) batu(1);
  else if (computer == 2) gunting(1);
  else if (computer == 3) kertas(1);

  if (user == 1) batu(0);
  else if (user == 2) gunting(0);
  else if (user == 3) kertas(0);
}

void acak() {
  srand(time(0));
  int iSecret = rand() % 2 + 1;

  if (iSecret == setAngka && iSecret < 3)
    iSecret += 1;
  else if (iSecret == setAngka && iSecret == 3)
    iSecret -= 1;

  setAngka = iSecret;
}

void Skor() {
  gotoxy(0, 17);
  cout << "SKOR USER     : " << skorU << endl;
  gotoxy(0, 18);
  cout << "SKOR COMPUTER : " << skorC << endl;
}


bool playSuit(std::string playerName) {
    system("cls");
    std::cout << playerName << " bermain Suit Game melawan komputer!\n";

    acak();  // set nilai random untuk komputer

    std::string pilih;
    int user;

    std::cout << "1. BATU\n";
    std::cout << "2. GUNTING\n";
    std::cout << "3. KERTAS\n";
    std::cout << "Pilih: ";
    std::cin >> pilih;
    std::cout << "\n";

    int computer = setAngka;
    std::stringstream ss;
    ss << pilih;
    ss >> user;

    tampil(computer, user);

    gotoxy(0, 15);
    if (computer == user) {
        std::cout << "                SERI\n";
        return false;  // Seri, tidak menang
    } else if ((computer == 1 && user == 3) ||
               (computer == 2 && user == 1) ||
               (computer == 3 && user == 2)) {
        std::cout << "              KAMU MENANG\n";
        return true;  // Menang
    } else {
        std::cout << "            KOMPUTER MENANG\n";
        return false;  // Kalah
    }
}


