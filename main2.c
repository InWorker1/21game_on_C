#include <stdio.h>
// #include <conio.h>
#include "string.h"
#include <time.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Функция для вывода массива символов
void print_array(const char *arr) {
    // Проверка на NULL указатель
    if (arr == NULL) {
        printf("(NULL)\n");
        return;
    }
    
    // Поэлементный вывод до нуль-терминатора
    int i = 0;
    while (arr[i] != '\0') {
        putchar(arr[i]);
        i++;
    }
    putchar('\n'); // Переход на новую строку после вывода
}

int getch(void) {
    struct termios oldt, newt;
    int ch;
    
    // Получаем текущие настройки терминала
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    
    // Отключаем канонический режим и эхо
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    // Получаем символ
    ch = getchar();
    
    // Восстанавливаем настройки терминала
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return ch;
}

void remch(char *s, int index) {
    for (int i = index; s[i]; i++)
        s[i] = s[i + 1];
}


int random_int(int max) {
    // int min = 0;
    // return min + arc4random_uniform(max - min + 1);
    srand(time(NULL));
    int a = rand() % (max + 1);
    return a;
}


char getcard(char a, int *sum, int *b, char *cards) {
    // printf("\n in fuck -- %c, %d, %d, %d\n", a, *b, *sum, (int)a);
    while (a == '.') {
        int c = random_int(*b);
        char a = cards[c];
    }
    int cif = a - '0';
    switch (cif) {
            case 1: printf("туз\n"); *sum+=11; break;
            case 0: printf("10\n"); *sum+=10; break;
            case 2: printf("валет\n"); *sum+=cif; break;
            case 3: printf("дама\n"); *sum+=cif; break;
            case 4: printf("кароль\n"); *sum+=cif; break;
            default: printf("%c\n", a); *sum+=cif;
        }
    *b-=1;

    return 0;
}


int main(void)
{
    int m = 35;
    int sum_user = 0; 
    int sum_pc = 0;
    
    char cards[] = "00003333444466667777888899991111";
    printf("%s\n", cards);
    printf("Привет дружа! Сыграем в 21?)) да или нет\n -> ");
    char otv[4]; 
    scanf("%s", otv);
    int otv1 = strcmp(otv, "да");
    

    if (otv1 == 0) {
        printf("Я покажу свою карту и выдам тебе две карты. Ты сможешь выбрать между: оставить (< = >) или продолжить(<Enter>)\n");
        

        int c = random_int(m);
        printf("rand cif %d\n", c);
        char card = cards[c];
        
        printf("Моя первая карта ");
        
        getcard(card, &sum_pc, &m, cards);
        cards[c] = '.';
        
        print_array(cards);
        
        
        char otv2[20];
        getch();
        while (getch() != '=') {
            c = random_int(m);
            card = cards[c];
            printf("Твоя карта ");
            getcard(card, &sum_user, &m, cards);
            printf("Сумма игрока: %d\n", sum_user);
            cards[c] = '.';
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
