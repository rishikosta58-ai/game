#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

void clear_screen_fast() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
}

void playGame() {
    srand(time(0));
    PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);

    int x = 1; // player pos
    int step = 0;
    int obstaclePos = rand() % 3;
    int score = 0;
    int lives = 3;
    int gameOver = 0;

    while (!gameOver) {

        if (_kbhit()) {
            char ch = getch();
            if (ch == 75 && x > 0) x--;   // Left
            if (ch == 77 && x < 2) x++;   // Right
        }

        clear_screen_fast();

        printf("   SCORE: %d   LIVES: %d\n", score, lives);
        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            if (i == step) {
                if (obstaclePos == 0) printf("| %d        |\n", 1);
                else if (obstaclePos == 1) printf("|     %d    |\n", 1);
                else if (obstaclePos == 2) printf("|        %d |\n", 1);
            } else {
                printf("|           |\n");
            }
        }

        if (x == 0) printf("| %d         |\n", 6);
        else if (x == 1) printf("|     %d     |\n", 6);
        else if (x == 2) printf("|        %d  |\n", 6);

        // Collision
        if (step == 10 && x == obstaclePos) {
            PlaySound(NULL, NULL, 0);
            PlaySound(TEXT("impact.wav"), NULL, SND_ASYNC);
            lives--;
            if (lives == 0) {
                gameOver = 1;
                break;
            }
            Sleep(400);
            PlaySound(TEXT("bg.wav"), NULL, SND_ASYNC | SND_LOOP);
        }

        Sleep(120);
        step++;

        if (step > 10) {
            step = 0;
            score++;
            obstaclePos = rand() % 3;
        }
    }

    PlaySound(NULL, NULL, 0);
    printf("\n\n GAME OVER! \n");
    printf("Final Score: %d\n", score);
}

int main() {

    while (1) {
        system("cls");
        system("color 4F");// color
        
        printf("\n\n====== DODGE GAME ======\n");
        printf("1. Play\n");
        printf("2. Exit\n");
        printf("Choose: ");

        char choice;
        scanf(" %c", &choice);

        if (choice == '1') {
            system("cls");
            playGame();
            printf("\n\nPlay again? (y/n): ");
            char again;
            scanf(" %c", &again);
            
            if (again == 'y' || again == 'Y')
                continue;
            else
                break;
        }
        else if (choice == '2') {
            break;
        }
        else {
            printf("Invalid choice!\n");
            Sleep(1000);
        }
    }

    printf("\nThanks for Playing!\n");
    return 0;
}
