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

void playSuitGame() {
    string pilih;
    int user;

    do {
        system("cls");
        acak();

        cout << "*nb: 'STOP' to stop program\n\n";
        cout << "1. BATU\n";
        cout << "2. GUNTING\n";
        cout << "3. KERTAS\n";
        cout << "Pilih\t: ";
        cin >> pilih;
        cout << "\n";

        int computer = setAngka;
        stringstream ss;
        ss << pilih;
        ss >> user;

        if (computer == user) {
            tampil(computer, user);
            gotoxy(0, 15);
            cout << "                  SERI";
            Skor();
        } else if ((computer == 1 && user == 3) || (computer == 2 && user == 1) || (computer == 3 && user == 2)) {
            tampil(computer, user);
            skorU += 1;
            gotoxy(0, 15);
            cout << "               KAMU MENANG";
            Skor();
        } else if ((computer == 1 && user == 2) || (computer == 2 && user == 3) || (computer == 3 && user == 1)) {
            tampil(computer, user);
            skorC += 1;
            gotoxy(0, 15);
            cout << "             KOMPUTER MENANG";
            Skor();
        }

        getch();
    } while (pilih != "STOP" && pilih != "stop");
    getch();
}
