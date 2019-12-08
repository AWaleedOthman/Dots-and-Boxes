#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "gamePlay.h"
#include "rankings.h"

int main()
{
    int choice, n, comp, loaded;
    int flag1 = 1; //to loop until user exits game
    int flag2 = 0; //for when the user chooses back option
    do{
        comp = loaded = 0;
        readTop10();
        system("cls");
        printArt();
        printf("\n\nMAIN MENU:  (please choose one of the following)\n\n");
        printf("1.Start Game\n2.Load Game\n3.Top 10\n4.How To Play\n5.Exit\n");
        inputToMenu(&choice);
        while(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5){
            printf("Invalid, please try again\n");
            inputToMenu(&choice);
        }
        switch(choice){
        case 1:
        {
            do{
                system("cls");
                printArt();
                printf("\n\nPlease choose one of the following:\n");
                printf("\n1.Beginner (3*3)\n2.Expert (5*5)\n3.Custom\n4.Back\n");
                inputToMenu(&choice);
                while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
                    printf("Invalid, please try again\n");
                    inputToMenu(&choice);
                }
                if(choice == 1){ //beginner
                    n = 2;
                }else if(choice == 2){ //expert
                    n = 5;
                }else if(choice == 4){
                    flag2 = 1;
                    break;
                }else{
                    printf("Please enter desired number of boxes (between 1 & 9): ");
                    inputToMenu(&n);
                    while(n<1 || n>9){
                        printf("Invalid, please try again\n");
                        inputToMenu(&n);
                    }
                }
                system("cls");
                printArt();
                printf("\n\nPlease choose one of the following:\n");
                printf("\n1.One Player\n2.Two Players\n3.Back\n");
                inputToMenu(&choice);
                while(choice != 1 && choice != 2 && choice != 3){
                    printf("Invalid, please try again\n");
                    inputToMenu(&choice);
                }
                if(choice == 2){
                    comp = 1;
                }
            }while(choice == 3);
            if(flag2)break;
            int size = 2*n+1;
            char grid[size][size];
            createGrid(&grid[0][0], size);
            movesLeft(2*n*(n+1)); //initializes number of moves left till end of game
            play(grid, size, comp);
            break;
        }// End Case 1
        case 2: //case load game
            system("cls");
            //Write code here
            while(getchar() != '\n');
            break;
        case 3: //case top10
            system("cls");
            printTop10();
            printf("\n\nPress Enter to return to main menu\n");
            while(getchar() != '\n');
            break;
        case 4: //how to
            howTo();
            while(getchar() != '\n');
            break;
        case 5: //case exit
            flag1 = 0;
            break;
        }
    }while(flag1);
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
