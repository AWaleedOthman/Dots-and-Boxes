#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "gamePlay.h"

int main()
{
    printArt();
    int choice, n;
    char arrChoice[256]; // string input
    printf("\n\nMAIN MENUE:  -please choose one of the following-\n\n");
    printf("1.Start Game\n2.Load Game\n3.Top 10\n4.Exit\n");
    scanf("%s", arrChoice); //Solves a problem where the program crashed when entering a non-integer
    choice = atoi(arrChoice);
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
        printf("Invalid, please try again\n");
        scanf("%s", arrChoice);
        choice = atoi(arrChoice);
    }
    switch(choice){
    case 1:
        system("cls");
        printArt();
        printf("\n\nPlease choose one of the following:\n");
        printf("\n1.Beginner\n2.Expert\n3.Custom\n");
        scanf("%s", arrChoice);
        choice  = atoi(arrChoice);
        while(choice != 1 && choice != 2 && choice != 3){
            printf("Invalid, please try again\n");
            scanf("%s", arrChoice);
            choice = atoi(arrChoice);
        }
        if(choice == 1){
            n = 3;
        }else if(choice == 2){
            n = 5;
        }else{
            printf("Please enter desired number of boxes: ");
            scanf("%s", arrChoice);
            n = atoi(arrChoice);
            while(n<1 || n>50){
                printf("Invalid, please try again\n");
                scanf("%s", arrChoice);
                n = atoi(arrChoice);
            }
        }
        break;
    default:
        exit(0);
    }
    int size = 2*n+1;
    char grid[size][size]; // the whole grid
    createGrid(&grid[0][0], size);
    movesLeft(2*n*(n+1));

    play(grid, size);
    return 0;
}
