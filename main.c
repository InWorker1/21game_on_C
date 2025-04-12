#include <stdio.h>
// #include <conio.h>
#include "string.h"

#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

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

void remch(char *str, int index) {
    for (int i = index; str[i] != 0; i++) {
        str[i] = str[i + 1];
    }
}

// char getcard(int b, char a, int *sum_pc, int *m, char cards) {
    
//     if (a == '2') {
//             printf("Моя первая карта валет\n");
//             *sum_pc += 2;
//             *m-=1;
//         }
//     else if (a == '3') {
//         printf("Моя первая карта дама\n");
//         *sum_pc += 3;
//         *m-=1;
//     }
//     else if (a == '4') {
//         printf("Моя первая карта кароль\n");
//         *sum_pc += 4;
//         *m-=1;
//     }
//     else if (a == '1') {
//         printf("Моя первая карта туз\n");
//         *sum_pc += 11;
//         *m-=1;
//     }
//     else {
//         printf("Моя первая карта %c\n", cards[b]);
//         *sum_pc += (int)*sum_pc;
//         *m-=1;
//     }
// }

char getcard(char a, int *sum, int *m) {
    switch ((int)a) {
            case 1: printf("туз\n"); break;
            case 0: printf("10\n"); break;
            case 2: printf("валет"); break;
            case 3: printf("дама"); break;
            case 4: printf("кароль"); break;
            default: printf("%c", a); break;
        }
    *m-=1;
    if (a == '0') {
        *sum+=10;
    }
    else if (a == '1') {
        *sum+=11;
    }
    else {
        *sum+=(int)a;
    }
}

int random_int(int max) {
    int min = 0;
    return min + arc4random_uniform(max - min + 1);
}

int main(void)
{
    int m = 35;
    int sum_user = 0; int sum_pc = 0;
    
    char cards[] = "00003333444466667777888899991111";
    
    printf("Привет дружа! Сыграем в 21?)) да или нет\n -> ");
    char otv[4]; 
    scanf("%s", otv);
    int otv1 = strcmp(otv, "да");
    

    if (otv1 == 0) {
        printf("Я покажу свою карту и выдам тебе две карты. Ты сможешь выбрать между: оставить (< = >) или продолжить(<Enter>)\n");
        int c = random_int(m);
        char card = cards[c];
        printf("Моя первая карта ");
        // switch ((int)card) {
        //     case 1: printf("туз\n"); break;
        //     case 0: printf("10\n"); break;
        //     case 2: printf("валет"); break;
        //     case 3: printf("дама"); break;
        //     case 4: printf("кароль"); break;
        //     default: printf("%c", card); break;
        // }
        getcard(card, &sum_pc, &m);
        remch(cards, card);
        
        // getcard(c, card, &sum_pc, &m, *cards);
        
        
        c = random_int(m);
        card = cards[c];
        
        
        char otv2[20];
        // getch();
        // while ((otv[i] = getch()) != 10) {
        //     putchar(otv2[0]);
        // }
        // printf("%c", cards[c]);
        while (getch() != '=') {
            printf("f\n");
        }
    }
    else {
        printf("Ты видимо не из понятливых. Заново запускай и пиши да.");
    }
 return 0;
}
