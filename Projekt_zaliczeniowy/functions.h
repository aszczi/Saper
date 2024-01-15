//
// Created by T on 15.01.2024.
//


#ifndef PROJEKT_ZALICZENIOWY_FUNCTIONS_H
#define PROJEKT_ZALICZENIOWY_FUNCTIONS_H

#include <stdio.h>


struct Player {
    char imie[100];
    float czas;
};

void wyswietl_tablice(char tab[11][11]) ;

void wypisz_zasady ();

int wybierz_poziom();

void inicjalizacja_tab_z_bombami(char tab_z_bombami[11][11], int ilosc_bomb);

void inicjalizacja_tab_do_zgadywania (char tab[11][11]);

void rekordy_do_struktur(FILE *file, char* imie, float czas, struct Player *player_one, struct Player *player_two, struct Player *player_three, struct Player *player_four, struct Player *player_five);

void tablica_rekordow(FILE *file, struct Player *player_one, struct Player *player_two, struct Player *player_three, struct Player *player_four, struct Player *player_five);

#endif //PROJEKT_ZALICZENIOWY_FUNCTIONS_H