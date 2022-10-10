#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<wchar.h>

/* Global Variables */
char choice;
char name1[50];
char name2[50] = "CPU";
int pos_p1 = 0, pos_p2 = 0;
unsigned char P1 = 254, P2 = 254;
char trash;
unsigned char snakes = 219, ladders = 206;
int flag1 = 0, flag2 = 0;

/* Prototype Function Declaration */
void roll_Dice();
void frame();
void pause_Roll();
int snake(int *, int*);
int ladder(int *, int *);

int main(void){
    /* Player1 Name */
    printf("Enter Player1 : ");
    scanf("%s", name1);
    fflush(stdin);  // Clear the Buffer

    /* Player2 Name */
    /*printf("Enter Player2 : ");
    scanf("%s", name2);
    fflush(stdin);  // Clear the Buffer*/

    /* Clear console Output */
    system("cls");
    printf("Welcome %s and %s!\n\n", name1, name2);
    /* Void function call, return NULL */
    frame();
    return 0;
}
//========================================================================

/* Pause Function */
void pause_Roll(){
    printf("\n\033[0;32mRolling...\033[0m");
    sleep(1);
}
//========================================================================

/* Snake */
/* 99-28 97-86 89-67 73-12 76-63 66-24 50-34 35-5 39-3 27-7 */
int snake(int *a, int *b){
    if(*a == 99) { *a = 28; return 1;}
    if(*a == 97) { *a = 86; return 1;}
    if(*a == 89) { *a = 67; return 1;}
    if(*a == 73) { *a = 12; return 1;}
    if(*a == 76) { *a = 63; return 1;}
    if(*a == 66) { *a = 24; return 1;}
    if(*a == 50) { *a = 34; return 1;}
    if(*a == 35) { *a = 5; return 1;}
    if(*a == 39) { *a = 3; return 1;}
    if(*a == 27) { *a = 7; return 1;}

    if(*b == 99) { *b = 28; return 2;}
    if(*b == 97) { *b = 86; return 2;}
    if(*b == 89) { *b = 67; return 2;}
    if(*b == 73) { *b = 12; return 2;}
    if(*b == 76) { *b = 63; return 2;}
    if(*b == 66) { *b = 24; return 2;}
    if(*b == 50) { *b = 34; return 2;}
    if(*b == 35) { *b = 5; return 2;}
    if(*b == 39) { *b = 3; return 2;}
    if(*b == 27) { *b = 7; return 2;}

    return 0;
}

//========================================================================

/* Ladder */
/* 80-83 87-93 70-90 54-69 44-58 30-48 28-77 22-41 7-29 2-23 */
int ladder(int *a, int *b){
    if(*a == 80) { *a = 83; return 1; }
    if(*a == 87) { *a = 93; return 1; }
    if(*a == 70) { *a = 90; return 1; }
    if(*a == 54) { *a = 69; return 1; }
    if(*a == 44) { *a = 58; return 1; }
    if(*a == 30) { *a = 48; return 1; }
    if(*a == 28) { *a = 77; return 1; }
    if(*a == 22) { *a = 41; return 1; }
    if(*a == 7) { *a = 29; return 1; }
    if(*a == 2) { *a = 23; return 1; }

    if(*b == 80) { *b = 83; return 2; }
    if(*b == 70) { *b = 90; return 2; }
    if(*b == 87) { *b = 93; return 2; }
    if(*b == 54) { *b = 69; return 2; }
    if(*b == 44) { *b = 58; return 2; }
    if(*b == 30) { *b = 48; return 2; }
    if(*b == 28) { *b = 77; return 2; }
    if(*b == 22) { *b = 41; return 2; }
    if(*b == 7) { *b = 29; return 2; }
    if(*b == 2) { *b = 23; return 2; }

    return 0;
}
//========================================================================

/* Frame */
void frame(){
    int i, j;
    int rand_N1, rand_N2;
    time_t t;
    srand((unsigned) time(&t));

    while(1){
        printf("\t\033[0;33mP1 -> (\033[0;31m%c\033[0;33m)\033[0m\n", P1);
        printf("\t\033[0;33mP2 -> (\033[0;34m%c\033[0;33m)\033[0m\n", P2);
        printf("\t\033[0;33mSnakes -> (\033[0;35m%c\033[0;33m)\033[0m\n", snakes);
        printf("\t\033[0;33mLadders -> (\033[0;36m%c\033[0;33m)\033[0m\n", ladders);
        printf("\t(\033[0;31mRemember \033[0m->\033[0;32m Enter any number of characters to Auto throw that many times!!!\033[0m)\n\n");
        int frame[10][10] = {{100,99,98,97,96,95,94,93,92,91},
                            {81,82,83,84,85,86,87,88,89,90},
                            {80,79,78,77,76,75,74,73,72,71},
                            {61,62,63,64,65,66,67,68,69,70},
                            {60,59,58,57,56,55,54,53,52,51},
                            {41,42,43,44,45,46,47,48,49,50},
                            {40,39,38,37,36,35,34,33,32,31},
                            {21,22,23,24,25,26,27,28,29,30},
                            {20,19,18,17,16,15,14,13,12,11},
                            {1,2,3,4,5,6,7,8,9,10},};

        rand_N1 = (rand() % 6) + 1;
        rand_N2 = (rand() % 6) + 1;

        for (i = 0; i < 10; i++){
            for (j = 0; j < 10; j++){
                if ((pos_p1+rand_N1) > 100 || (pos_p2+rand_N2) > 100){
                    continue;
                }
                if (frame[i][j] == 99 || frame[i][j] == 97 || frame[i][j] == 89 || frame[i][j] == 73 || frame[i][j] == 76 || frame[i][j] == 66 || frame[i][j] == 50 || frame[i][j] == 35 || frame[i][j] == 39 || frame[i][j] == 27){
                    printf("\033[0;35m");
                    printf("%6c", snakes);
                    printf("\033[0m");
                    continue;
                }
                if (frame[i][j] == 87 || frame[i][j] == 80 || frame[i][j] == 70 || frame[i][j] == 54 || frame[i][j] == 44 || frame[i][j] == 30 || frame[i][j] == 28 || frame[i][j] == 22 || frame[i][j] == 7 || frame[i][j] == 2){
                    printf("\033[0;36m");
                    printf("%6c", ladders);
                    printf("\033[0m");
                    continue;
                }
                if (pos_p1 == frame[i][j]){
                    printf("\033[0;31m");
                    printf("%6c", P1);
                    printf("\033[0m");
                    continue;
                }
                if (pos_p2 == frame[i][j]){
                    printf("\033[0;34m");
                    printf("%6c", P2);
                    printf("\033[0m");
                    continue;
                }
                printf("%6d", frame[i][j]);
            }
            printf("\n\n");
        }

        pos_p1 += rand_N1;
        pos_p2 += rand_N2;

        flag1 = snake(&pos_p1, &pos_p2);
        flag2 = ladder(&pos_p1, &pos_p2);

        printf("\nflag1 = %d\nflag2 = %d\n\n", flag1, flag2);

        printf("\t\033[0;31m%s's\033[0m chance to Roll!\n", name1);
        printf("\t\nEnter to Roll!");
        scanf("%c", &trash);
        pause_Roll();
        printf("\t\033[0;31m%s\033[0m Rolled: %d\n", name1, rand_N1);

        printf("\t\033[0;34m%s\033[0m chance to Roll!\n", name2);
        pause_Roll();
        printf("\t\033[0;34m%s\033[0m Rolled: %d\n\n", name2, rand_N2);

        if (flag1 == 1){ printf("\nP1 Bitten by snake!!!\n"); }
        if (flag2 == 1){ printf("\nP1 Ladder up!!!\n"); }
        if (flag1 == 2){ printf("\nP2 Bitten by snake!!!\n"); }
        if (flag2 == 2){ printf("\nP2 Ladder up!!!\n"); }

        sleep(3);
        system("cls");

        if (pos_p1 == 100){
            printf("\n\n%s Wins!!!\n\n", name1);
            break;
        }
        else if (pos_p2 == 100){
            printf("\n\n%s Wins!!!\n\n", name2);
            break;
        }
    }
}
//========================================================================
