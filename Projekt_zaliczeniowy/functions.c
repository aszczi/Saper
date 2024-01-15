//
// Created by T on 15.01.2024.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


void wyswietl_tablice(char tab[11][11]) {
    int i, j;
    for (i = 0; i < 11; i++) {
        for (j = 0; j < 11; j++) {
            printf("%c ", tab[i][j]);
        }
        printf("\n");

    }
}


void wypisz_zasady (){
    printf("Witaj w grze Saper!\n");
    printf("Zasady gry:\n");
    printf("1. Gra polega na odkrywaniu pol na planszy.\n");
    printf("2. Na planszy znajduja sie bomby, ktorych polozenie jest losowe.\n");
    printf("3. Celem gry jest odkrycie wszystkich pol na planszy, ktore nie sa bombami.\n");
    printf("4. Wpisujac litere (z duzej) i cyfre, odkrywasz pole o podanych wspolrzednych.\n");
    printf("5. Jesli odkryjesz pole, ktore nie jest bomba, na planszy pojawi sie liczba, ktora oznacza ilosc bomb wokol tego pola.\n");
    printf("6. Jesli chcesz zaznaczyc bombe wpisz najpierw $$ a pozniej wspolrzedne pola.\n");
    printf("7. Jesli chcesz zaznaczyc pole jako niewiadoma wpisz najpierw ?? a pozniej wspolrzedne pola.\n");
    printf("8. Jesli odkryjesz wszystkie pola, ktore nie sa bombami, wygrywasz, natomiat jesli trafisz na bombe przegrywasz.\n");
    printf("Powodzenia!\n");
    printf("\n");
}

int wybierz_poziom(){

    int ilosc_bomb;
    char poziom, enter1;

    while(poziom != 1 && poziom != 2 && poziom != 3 && poziom != 4){
        printf("Wybierz poziom trudnosci:\n");
        printf("1. latwy\n");
        printf("2. sredni\n");
        printf("3. trudny\n");
        printf("4. niemozliwy\n");

        scanf("%d%c", &poziom, &enter1);

        switch (poziom){
            case 1:
                printf("wybrales latwy poziom trudnosci\n");
                ilosc_bomb =5;
                break;
            case 2:
                printf("wybrales sredni poziom trudnosci\n");
                ilosc_bomb =10;
                break;
            case 3:
                printf("wybrales trudny poziom trudnosci\n");
                ilosc_bomb =15;
                break;
            case 4:
                printf("wybrales niemozliwy poziom trudnosci\n");
                ilosc_bomb =25;
                break;
            default:
                printf("wybrales zly poziom trudnosci, wybierz jeszcze raz\n");

                break;
        }
    }

    return ilosc_bomb;
}

void inicjalizacja_tab_z_bombami(char tab_z_bombami[11][11], int ilosc_bomb){
    int bomba;
    int i, j;
    int wielkosc = 10;
/*wielkosc to jest to ile na ile jest tablica*/

    /*inicjalizujemy tablice z bombami*/
    for(i = 0; i < ilosc_bomb; i++){
        bomba = (rand() % 100) + 1;
        int rzad = bomba / 10;
        int kolumna = (bomba%10);
        if(tab_z_bombami[rzad+1][kolumna+1] != 'B'){
            tab_z_bombami[rzad+1][kolumna+1] = 'B';
        }else{
            i--;
        }
    }

    for(i= 1; i <= wielkosc; i++){
        for(j = 1; j <= wielkosc; j++){
            if(tab_z_bombami[i][j] != 'B'){
                tab_z_bombami[i][j] = '0';
            }
        }
    }

    for(i = 0; i<= wielkosc; i++){
        tab_z_bombami[0][i] = ' ';
        tab_z_bombami[i][0] = ' ';

    }

    for(i = 1; i <= wielkosc; i++) {
        for (j = 1; j <= wielkosc; j++) {
            int ilosc = 0;
            if (tab_z_bombami[i][j] != 'B') {

                if (i>1 && j>1 && (tab_z_bombami[i - 1][j - 1] == 'B')) {
                    ilosc++;
                }
                if (i>1 && (tab_z_bombami[i - 1][j] == 'B')) {
                    ilosc++;
                }
                if (i>1 && j<wielkosc && (tab_z_bombami[i - 1][j + 1] == 'B')) {
                    ilosc++;
                }
                if (j>1 && (tab_z_bombami[i][j - 1] == 'B')) {
                    ilosc++;
                }
                if (j<wielkosc && (tab_z_bombami[i][j + 1] == 'B')) {
                    ilosc++;
                }
                if (i<wielkosc && j>1 && (tab_z_bombami[i + 1][j - 1] == 'B')) {
                    ilosc++;
                }
                if (i<wielkosc && (tab_z_bombami[i + 1][j] == 'B')) {
                    ilosc++;
                }
                if (i<wielkosc && j<wielkosc &&(tab_z_bombami[i + 1][j + 1] == 'B')) {
                    ilosc++;
                }
                tab_z_bombami[i][j] += ilosc;
            }
        }
    }

}

void inicjalizacja_tab_do_zgadywania (char tab[11][11]){
    int i, j;
    int wielkosc  = 10;

    tab[0][0]= ' ';
    for(i = 1; i<=wielkosc; i++){

        tab[i][0] = 'A' + i - 1;
        tab[0][i] = '0' + i - 1;
    }

    for (i = 1; i <=wielkosc; i++) {
        for (j = 1; j <=wielkosc; j++) {
            tab[i][j] = '*';
        }
    }
}


void rekordy_do_struktur(FILE *file, char *imie, float czas, struct Player *player_one, struct Player *player_two,
                         struct Player *player_three, struct Player *player_four, struct Player *player_five) {
    int i  = 0;

    if( czas < player_one->czas){
        player_five = player_four;
        player_four = player_three;
        player_three = player_two;
        player_two = player_one;
        while(imie[i] != '\0'){
            player_one->imie[i] = imie[i];
            i++;
        }
        player_one->czas = czas;
    }
    else if(czas < player_two->czas){
        player_five = player_four;
        player_four = player_three;
        player_three = player_two;
        while(imie[i] != '\0'){
            player_two->imie[i] = imie[i];
            i++;
        }
        player_two->czas = czas;
    }
    else if(czas < player_three->czas){
        player_five = player_four;
        player_four = player_three;
        while(imie[i] != '\0'){
            player_three->imie[i] = imie[i];
            i++;
        }
        player_three->czas = czas;
    }
    else if(czas < player_four->czas){
        player_five = player_four;
        while(imie[i] != '\0'){
            player_four->imie[i] = imie[i];
            i++;
        }
        player_four->czas = czas;
    }
    else if(czas < player_five->czas) {
        while (imie[i] != '\0') {
            player_five->imie[i] = imie[i];
            i++;
        }
        player_five->czas = czas;
    }

    printf("Gratulacje, wygrales!\n");
    printf("Twoj czas to: %f\n", czas);
    printf("Sprawdz czy jestes na tablicy rekordow\n");
    printf("Oto obecna tablica rekordow:\n");
    printf("%s %f\n", player_one->imie, player_one->czas);
    printf("%s %f\n", player_two->imie, player_two->czas);
    printf("%s %f\n", player_three->imie, player_three->czas);
    printf("%s %f\n", player_four->imie, player_four->czas);
    printf("%s %f\n", player_five->imie, player_five->czas);


    fprintf(file, "%s ", player_one->imie);
    fprintf(file, "%f\n", player_one->czas);

    fprintf(file, "%s ", player_two->imie);
    fprintf(file, "%f\n", player_two->czas);

    fprintf(file, "%s ", player_three->imie);
    fprintf(file, "%f\n", player_three->czas);

    fprintf(file, "%s ", player_four->imie);
    fprintf(file, "%f\n", player_four->czas);

    fprintf(file, "%s ", player_five->imie);
    fprintf(file, "%f\n", player_five->czas);
}

void tablica_rekordow(FILE *file, struct Player *player_one, struct Player *player_two, struct Player *player_three, struct Player *player_four, struct Player *player_five){
    int i;
    char imiona[5][100];
    float czasy[5];
    printf("Oto obecna tablica rekordow:\n");

    fscanf(file, "%s %f", &imiona[0], &czasy[0]);
    fscanf(file, "%s %f", &imiona[1], &czasy[1]);
    fscanf(file, "%s %f", &imiona[2], &czasy[2]);
    fscanf(file, "%s %f", &imiona[3], &czasy[3]);
    fscanf(file, "%s %f", &imiona[4], &czasy[4]);
    player_one->czas = czasy[0];
    player_two->czas = czasy[1];
    player_three->czas = czasy[2];
    player_four->czas = czasy[3];
    player_five->czas = czasy[4];
    for(i = 0; i < 100; i++){
        player_one->imie[i] = imiona[0][i];
        player_two->imie[i] = imiona[1][i];
        player_three->imie[i] = imiona[2][i];
        player_four->imie[i] = imiona[3][i];
        player_five->imie[i] = imiona[4][i];
    }
    printf("%s %f\n", player_one->imie, player_one->czas);
    printf("%s %f\n", player_two->imie, player_two->czas);
    printf("%s %f\n", player_three->imie, player_three->czas);
    printf("%s %f\n", player_four->imie, player_four->czas);
    printf("%s %f\n", player_five->imie, player_five->czas);

    printf("Jesli uda ci sie wygrac w sapera w czasie krotszym niz ktorys z rekordow, zostaniesz rowniez na nia wpisany:)\n");

}
