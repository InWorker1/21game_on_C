#include <stdio.h>
#include <conio.h>
#include "string.h"
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <random>

void print_array(const char* arr) {
    int i = 0;
    while (arr[i] != '\0') {
        putchar(arr[i]);
        i++;
    }
    putchar('\n');
}


int random_int(int max) {
    // int min = 0;
    // return min + arc4random_uniform(max - min + 1);
    srand(time(NULL));
    int a = rand() % (max + 1);
    return a;
}


void getcard(char a, int* sum, int* b, char* cards) {
    while (a == '.') {
        int c = random_int(*b);
        char a = cards[c];
    }
    int cif = a - '0';
    switch (cif) {
    case 1: printf("туз\n"); *sum += 11; break;
    case 0: printf("10\n"); *sum += 10; break;
    case 2: printf("валет\n"); *sum += cif; break;
    case 3: printf("дама\n"); *sum += cif; break;
    case 4: printf("кароль\n"); *sum += cif; break;
    default: printf("%c\n", a); *sum += cif;
    }
    *b -= 1;
}


int main(void)
{
    setlocale(LC_ALL, "RU");
    int m = 35;
    int sum_user = 0;
    int sum_pc = 0;

    char cards[] = "00003333444466667777888899991111";

    printf("Привет дружа! Сыграем в 21?)) да или нет\n -> ");
    char otv[] = "да";
    /*scanf_s("%2s", &otv, 2);*/
    /*otv[2] = '\0';*/ 
    print_array(otv);
    int otv1 = strcmp(otv, "да");
    
    if (strcmp(otv, "да") == 0) {
        /*free(otv);*/
        printf("Я покажу свою карту и выдам тебе две карты. Ты сможешь выбрать между: оставить (< = >) или продолжить(<Enter>)\n");


        int c = random_int(m);
        /*printf("rand cif %d\n", c);*/
        char card = cards[c];

        printf("Моя первая карта ");

        getcard(card, &sum_pc, &m, cards);
        cards[c] = '.';

        /*print_array(cards);*/


        
        while (_getch() != '=') {
            c = random_int(m);
            card = cards[c];
            printf("Твоя карта ");
            getcard(card, &sum_user, &m, cards);
            printf("Сумма игрока: %d\n", sum_user);
            cards[c] = '.';
            /*print_array(cards);*/
            if (sum_user == 21) {
                printf("YOU WIN");
                return 0;
            }
            else if (sum_user > 21) {
                printf("YOU LOSE");
                return 0;
            }
            else {
                continue;
            }
        }
        c = random_int(m);
        card = cards[c];
        printf("\n");
        printf("моя вторая карта ");
        getcard(card, &sum_pc, &m, cards);
        printf("Сумма банкира: %d\n", sum_pc);
        cards[c] = '.';
        while (22 > sum_pc) {
            if (sum_pc == 21) {
                printf("HAHAHAHAHAH I WON, I ACTUALLY WON!");
                return 0;
            }
            else if (sum_user < sum_pc) {
                printf("I won");
                return 0;
            }
            c = random_int(m);
            card = cards[c];
            printf("моя карта ");
            getcard(card, &sum_pc, &m, cards);
            printf("Сумма банкира: %d\n", sum_pc);
            cards[c] = '.';
        }
        printf("i lose... see u later");
    }
    else {
        printf("Ты видимо не из понятливых. Заново запускай и пиши да.");
    }
    return 0;
}
