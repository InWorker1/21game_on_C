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
    if (str == NULL || index < 0 || index >= strlen(str)) {
        // Проверка на некорректные входные данные
        return;
    }
    
    // Сдвигаем все символы после индекса на одну позицию влево
    for (int i = index; str[i] != '\0'; i++) {
        str[i] = str[i + 1];
    }
}



char getcard(char a, int *sum, int *b) {
    // printf("\n in fuck -- %c, %d, %d, %d\n", a, *b, *sum, (int)a);
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

int random_int(int max) {
    int min = 0;
    return min + arc4random_uniform(max - min + 1);
}

int main(void)
{
    int m = 35;
    int sum_user = 0; 
    int sum_pc = 0;
    
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
        getcard(card, &sum_pc, &m);
        remch(cards, card);
        
        
        
        char otv2[20];
        getch();
        while (getch() != '=') {
            c = random_int(m);
            card = cards[c];
            printf("Твоя карта ");
            getcard(card, &sum_user, &m);
            printf("Сумма игрока: %d\n", sum_user);
            remch(cards, card);
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
        printf("моя вторая карта ");
        getcard(card, &sum_pc, &m);
        printf("Сумма банкира: %d\n", sum_pc);
        remch(cards, card);
        // if (sum_user )
    }
    else {
        printf("Ты видимо не из понятливых. Заново запускай и пиши да.");
    }
 return 0;
}
