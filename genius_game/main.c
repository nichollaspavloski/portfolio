#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <dos.h>
#include <conio.h>
#include <stdbool.h>

int i;
void menu();
int highscore=0;
void instructions(void){

    printf("Intrucoes:\n#Repita a sequencia que o Simon criar. Cada botao aceso e\num botao da sequencia.\n\n#Espere o Simon terminar a sequencia para repetir.\n#Cada vez que a sequencia for repetida corretamente um \nbotao sera adicionado a sequencia\n\nTECLAS:\n\nverde    => 7\nvermelho => 9\namarelo  => 1\nazul     => 3\n");

    printf("\naperte qualquer tecla para voltar para o menu");
    getch();
    system("cls");
    menu(highscore);
}

void creditos(void){

    SetColor(13);
    printf("Nichollas Pavloski\n\nRodrigo Kenji Kawano\n\n");
    SetColor(12);
    printf("Professor Juliano\n\n");

    SetColor(07);
    printf("\naperte qualquer tecla para voltar para o menu");
    getch();
    system("cls");
    menu();
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* ---CORES---*/

void green(int r){

    FILE *arq;
    int y = 0;

    arq = fopen("green.txt", "rt");

    if(arq){
        char texto[500];

        while(fgets(texto, 500, arq)){

            gotoxy(37, y);

            if(r == 0){
                SetColor(10);
                printf("%s", texto);
            } else {
                SetColor(2);
                printf("%s", texto);
            }

            y++;
        }
    }

    fclose(arq);
}

void red(int r){

    FILE *arq;
    int y = 0;

    arq = fopen("red.txt", "rt");

    if(arq){
        char texto[500];


        while(fgets(texto, 500, arq)){

            gotoxy(60, y);

            if(r == 1){
                SetColor(12);
                printf("%s", texto);
            } else {
                SetColor(4);
                printf("%s", texto);
            }

            y++;
        }
    }

    fclose(arq);
}

void yellow(int r){

    FILE *arq;
    int y = 12;

    arq = fopen("yellow.txt", "rt");

    if(arq){
        char texto[500];


        while(fgets(texto, 500, arq)){
            gotoxy(37, y);

            if(r == 2){
                SetColor(14);
                printf("%s", texto);
            } else {
                SetColor(6);
                printf("%s", texto);
            }

            y++;
        }
    }

    fclose(arq);
}

void blue(int r){

    FILE *arq;
    int y = 12;
    arq = fopen("blue.txt", "rt");

    if(arq){
        char texto[500];

        while(fgets(texto, 500, arq)){
            gotoxy(60, y);

            if(r == 3){
                SetColor(9);
                printf("%s", texto);
            } else {
                SetColor(1);
                printf("%s", texto);
            }

            y++;
        }
    }

    fclose(arq);
}

void colors(int r){

    green(r);
    red(r);
    printf("\n");
    yellow(r);
    blue(r);
    printf("\n");

    SetColor(7);
}

/* ---------------SONS------------------*/

void som(int r){
    if(r == 0){
        Beep(830, 500);
    }
    else if(r == 1){
        Beep(622, 500);
    }
    else if(r == 2){
        Beep(494, 500);
    }
    else if(r == 3){
        Beep(415, 500);
    }
}

int get_key(int k){

    int key;

    if(k == 55){
        key = 0;
    } else if(k == 57){
        key = 1;
    } else if(k == 49){
        key = 2;
    } else if(k == 51){
        key = 3;
    } else {
        key = 5;
    }

    return key;
}

/* -----jogo----- */

int game(int highscore){

    int level = 1;
    int r[50], key[50], key_r[50];
    bool tries = TRUE;

    srand((unsigned)time(NULL));
    //system("color 70");

    while(tries){

        r[level - 1] = rand()%4;

        gotoxy(57, 25);
        SetColor(13);
        printf("LEVEL %d", level);

        for(i = 0; i < level; i++){
            colors(5);
            Sleep(500);

            colors(r[i]);
            som(r[i]);
        }

        for(int j = 0; j < level; j++){

            colors(5);
            key[j] = getch();

            key_r[j] = get_key(key[j]);

            colors(key_r[j]);
            som(key_r[j]);

            if(key_r[j] != r[j]){
                //j = level;
                tries = FALSE;

                gotoxy(60, 15);
                colors(5);

                system("cls");
                gotoxy(56, 12);
                SetColor(13);
                printf("PERDEU!");
                Beep(270,1000);
                getch();
                system("cls");

                menu(highscore);
            }
        }

        level++;

        if(level > highscore)
            highscore = level;
        Sleep(2);
    }

    getchar();
}

/* -----menus---- */

void menu(highscore){

    gotoxy(60, 15);
    colors(5);

    gotoxy(70, 16);
    printf("jogar");
    gotoxy(68, 17);
    printf("aperte(j)");

    gotoxy(43, 6);
    printf("instrucoes");
    gotoxy(43, 7);
    printf("aperte(i)");

    gotoxy(68, 6);
    printf("creditos");
    gotoxy(68, 7);
    printf("aperte(c)");

    gotoxy(43, 16);
    printf("highscore:");
    gotoxy(46, 17);
    printf("%i", highscore);

    char c = getch();

    system("cls");

    if(c == 'i')
        instructions();
    if(c == 'c')
        creditos();
    if(c = 'j')
        game(highscore);
}


/*-------------------------------------------*/

int main()
{
    colors(0);
    som(0);
    colors(1);
    som(1);
    colors(3);
    som(3);
    colors(2);
    som(2);
    menu(highscore);

    return 0;
}

/*-------------------------------------------*/

void SetColor(int ForgC){

    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){

        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }

    return;
}
