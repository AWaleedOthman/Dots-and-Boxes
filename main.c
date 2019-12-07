#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "gamePlay.h"

int main()
{
    int choice, n;
    int flag; //flags back to main menu
    do{
        flag = 1;
        system("cls");
        printArt();
        printf("\n\nMAIN MENU:  -please choose one of the following-\n\n");
        printf("1.Start Game\n2.Load Game\n3.Top 10\n4.Exit\n");
        inputToMenu(&choice);
        while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
            printf("Invalid, please try again\n");
            inputToMenu(&choice);
        }
        switch(choice){
        case 1:
        {
            system("cls");
            printArt();
            printf("\n\nPlease choose one of the following:\n");
            printf("\n1.Beginner (3*3)\n2.Expert (5*5)\n3.Custom\n4.Back To Main Menu\n");
            inputToMenu(&choice);
            while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
                printf("Invalid, please try again\n");
                inputToMenu(&choice);
            }
            if(choice == 1){
                n = 3;
            }else if(choice == 2){
                n = 5;
            }else if(choice == 4){
                flag = 1;
                break;
            }else{
                printf("Please enter desired number of boxes (between 1 & 10): ");
                inputToMenu(&n);
                while(n<1 || n>10){
                    printf("Invalid, please try again\n");
                    inputToMenu(&n);
                }
            }
            int size = 2*n+1;
            char grid[size][size];
            createGrid(&grid[0][0], size);
            movesLeft(2*n*(n+1)); //initializes number of moves left till end of game
            play(grid, size);
            break;
        }
        case 2: //case load game
            system("cls");
            //Write code here
            while(getchar() != '\n');
            break;
        case 3: //case top10
            system("cls");
            //Write code here
            while(getchar() != '\n');
            break;
        case 4: //case exit
            flag = 0;
            break;
        }
    }while(flag);
    return 0;
}

void inputToMenu(int* choice){
    char arrChoice[3]; // string input
    arrChoice[2] = '\0';
    while((arrChoice[0] = getchar()) == '\n');   //Solves a problem where the program crashes when entering a non-integer
    arrChoice[1] = getchar();
    if(arrChoice[1] == '\n'){
        arrChoice[1] = '\0';
        *choice = atoi(arrChoice);
        arrChoice[1] = '\n';
    }else{
        while(getchar() != '\n');
        *choice = 0;
    }
}
