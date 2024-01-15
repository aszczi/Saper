
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"
#include "functions.c"


int main() {
    clock_t start, end;    /*zmienne do mierzenia czasu*/
    srand(time(NULL));
    int i, j;
    int poziom;
    int ilosc_bomb;
    char enter1;
    int bomba;
    char tab_z_bombami[11][11];
    int pierwsza_int;
    int druga_int;
    char pierwsza, druga, enter;
    int licznik = 0; //licznik odkrytych pol
    float czas_wykonania;
    char imie[100];
    float czas;

    struct Player player_one;
    struct Player player_two;
    struct Player player_three;
    struct Player player_four;
    struct Player player_five;

    //wypisujemy zasady gry
    wypisz_zasady();

    ilosc_bomb = wybierz_poziom();

    FILE *file;

    /* Otwieramy plik do odczytu*/
    file = fopen("rekordy.txt", "r");

    /* Sprawdzamy, czy udało się otworzyć plik*/
    if (file == NULL) {
        printf("Nie udało się otworzyć pliku.\n");
        return 1;
    }

    printf("Podaj imie:");
    scanf("%s", imie);

    /*wcztywanie danych z pliku do tablicy struktur z rozdzielnikeim jako spacja*/
    tablica_rekordow(file, &player_one, &player_two, &player_three, &player_four, &player_five);

    fclose(file);/*zamykamy plik, ktory sluzyl nam do odczytu*/

    /*inicjalizujemy tablice z bombami*/

    inicjalizacja_tab_z_bombami(tab_z_bombami, ilosc_bomb);


 /* inicjalizujemy tablice do zgadywania*/
    char tab[11][11];
    inicjalizacja_tab_do_zgadywania(tab);

    /*zaczynamy grac*/

    wyswietl_tablice(tab);
    start=clock();
    scanf("%c", &enter);
    while(licznik<(100 - ilosc_bomb)){
            printf("Podaj wspolrzedne pola, ktore chcesz odkryc: ");
            scanf("%c%c%c", &pierwsza, &druga, &enter);

         if(pierwsza =='$' && druga =='$'){

             printf("\nPodaj wspolrzedne pola, ktore chcesz oznaczyc jako bombe: \n");
             scanf("%c%c%c", &pierwsza, &druga, &enter);
             pierwsza_int = pierwsza - 'A' + 1;
             druga_int = druga - '0' + 1;
             tab[pierwsza_int][druga_int] = '$';
             printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
             wyswietl_tablice(tab);

         }else if(pierwsza =='?' && druga =='?'){

             printf("\nPodaj wspolrzedne pola, ktore chcesz oznaczyc jako niewiadomą (?): \n");
             scanf("%c%c%c", &pierwsza, &druga, &enter);
             pierwsza_int = pierwsza - 'A' + 1;
             druga_int = druga - '0' + 1;
             tab[pierwsza_int][druga_int] = '?';
             printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            wyswietl_tablice(tab);

         }else{

             pierwsza_int = pierwsza - 'A' + 1;
             druga_int = druga - '0' + 1;
             //  printf("%d %d\n", pierwsza_int, druga_int);
             if(tab_z_bombami[pierwsza_int][druga_int] == 'B'){
               //printf("Przegrales!\n");
                 wyswietl_tablice(tab_z_bombami);
                 break;
             }else{
                 if(tab[pierwsza_int][druga_int] != tab_z_bombami[pierwsza_int][druga_int]) {
                     licznik++;
                 }
                 tab[pierwsza_int][druga_int] = tab_z_bombami[pierwsza_int][druga_int];
                 printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                 wyswietl_tablice(tab);

            }
        }
    }
   end=clock();
   czas_wykonania = (float)(end-start)/CLOCKS_PER_SEC;
   czas = czas_wykonania;

    if(licznik == (100 - ilosc_bomb)){
        /* Otwieramy plik do zapisu*/

        file = fopen("rekordy.txt", "w");

        if (file == NULL) {
            printf("Nie udało się otworzyć pliku.\n");
            return 1;
        }
        /*zapisujemy dane do pliku*/
        rekordy_do_struktur(file, imie, czas, &player_one, &player_two, &player_three, &player_four, &player_five);

        /* Zamykamy plik*/
        fclose(file);
    }
    else{
        printf("Przegrales, nastepnym razem bedzie lepiej :)\n");
    }

    return 0;
}