#ifndef SUIT_H
#define SUIT_H

#include <iostream>

extern int setAngka;
extern int skorU;
extern int skorC;

void gotoxy(int x, int y);
void batu(int nilai);
void gunting(int nilai);
void kertas(int nilai);
void tampil(int computer, int user);
void acak();
void Skor();
void playSuitGame();  // This is the game function you'll call from main

#endif // SUIT_H
