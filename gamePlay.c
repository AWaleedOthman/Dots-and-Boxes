#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else //This should work for Unix. It is included since Eng. Reham works on Linux -I think.
#include <unistd.h>
#endif // _WIN32
#include "rankings.h"
#include <pthread.h>
typedef struct{ // structure containing both players
    int turnsPlayed;
    int score;
    }Player;

typedef struct{
    char* grid;
    int* size;
    int* turn;
    Player* player1;
    Player* player2;
    int* startingTime;
    int* comp;
}AUX;

void* updateTime(void*p){
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int AuxStartingTime = time(0);
    AUX* myAux = (AUX*)p;
    Player* player1 = (*myAux).player1;
    Player* player2 = (*myAux).player2;
    while(1){
        if(time(0)-AuxStartingTime >= 60){
            AuxStartingTime = time(0);
            printGrid((*myAux).grid, *(*myAux).size);
            printBar(*(*myAux).turn, *player1, *player2, *(*myAux).startingTime, *(*myAux).comp);
            printf("Please choose column then row separated by a comma: ");
        }else{
            holdOn();
        }
    }
}

void play(char* grid, int size, int comp, int loaded, int loadedMoves){
    int flag = 0, lastWasUndoRedo = 0, thisIsUndoRedo = 0;
    int startingTime = time(0);
    int n = (size-1)/2;
    if(loaded == 1 || loaded == 2 || loaded == 3){
        movesLeft(loadedMoves);
    }
    else{
        movesLeft(2*n*(n+1)); //initializes number of moves left till end of game////////////////OR load
    }
    int temp = 0; //to store value of input; useful for in-game menu
    int scoreInc; //to store increment of score
    int boxes[n][n]; // array with number of boxes where each cell contains number of sides remaining
    int undo[2*n*(n+1)][3]; //array for undo
    int redo[2*n*(n+1)][3];//for redo
    fillWith0s(&undo[0][0], &redo[0][0], 2*n*(n+1));
    fillWith4s(&boxes[0][0], n);
    Player player1 = {0,0};
    Player player2 = {0,0};
    int inputRow, inputCol;
    int turn = 1;
    if(loaded == 1 || loaded == 2 || loaded == 3){
        loadBoxes(&boxes[0][0], n, loaded);
        loadData(&turn, &player1.turnsPlayed, &player1.score, &player2.turnsPlayed, &player2.score, loaded);
    }
    //for multi-threading
    AUX myAux = {grid, &size, &turn, &player1, &player2, &startingTime, &comp};
    pthread_t myThread;
    //
    while(movesLeft(0)){
        thisIsUndoRedo = 0;
        flag=1;
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime, comp);
        if(comp && turn == 2){// let computer choose
            if(temp!=1)
                holdOn();
                compChoose(&boxes[0][0], n, grid, size, &inputRow, &inputCol);
        }else{
            printf("Please choose column then row separated by a comma: ");
            pthread_create(&myThread, NULL, updateTime,&myAux);
            temp = getInput(&inputCol, &inputRow);
            pthread_cancel(myThread);
        }
        if(temp == 4){
            return;
        }
        else if(temp == 1){ //Undo
            undoPlay(grid, size, &undo[0][0], 2*n*(n+1), boxes, &turn, &player1, &player2, &redo[0][0]);
            lastWasUndoRedo = 1;
            continue;
        }else if(temp == 2){ //Redo
            redoPlay(&inputRow, &inputCol, &redo[0][0], 2*n*(n+1), &turn);
            thisIsUndoRedo = 1;
            lastWasUndoRedo = 1;
        }else if(temp == 3){
            do{
                printf("Please choose saved games 1, 2 or 3 to overwrite: ");
                inputToMenu(&temp);
            }while(temp!=1 && temp!=2 && temp!=3);
            saveBoxes(boxes, n, temp);
            saveGrid(grid, size, comp, movesLeft(0), temp);
            saveData(player1.score, player1.turnsPlayed, player2.score, player2.turnsPlayed, turn, temp);
            return;
        }

        while(flag && !drawLine(grid, size, inputRow, inputCol, turn, &undo[0][0], &redo[0][0], turn, lastWasUndoRedo, 2*n*(n+1), thisIsUndoRedo)){
            thisIsUndoRedo = 0;
            printf("Invalid\n");
            printf("Please choose column then row separated by a comma: ");
            pthread_create(&myThread, NULL, updateTime,&myAux);
            temp = getInput(&inputCol, &inputRow);
            pthread_cancel(myThread);
            if(temp == 4){
                return;
            }
            else if(temp == 1){ //Undo
                undoPlay(grid, size, &undo[0][0], 2*n*(n+1), boxes, &turn, &player1, &player2, &redo[0][0]);
                flag=0;
                lastWasUndoRedo = 1;
            }else if(temp == 2){ //Redo
                thisIsUndoRedo = 1;
                lastWasUndoRedo = 1;
                redoPlay(&inputRow, &inputCol, &redo[0][0], 2*n*(n+1), &turn);
            }else if(temp == 3){
                do{
                    printf("Please choose saved games 1, 2 or 3 to overwrite: ");
                    inputToMenu(&temp);
                }while(temp!=1 && temp!=2 && temp!=3);
                saveBoxes(boxes, n, temp);
                saveGrid(grid, size, comp, movesLeft(0), temp);
                saveData(player1.score, player1.turnsPlayed, player2.score, player2.turnsPlayed, turn, temp);
                return;
                }
        }
        if(!flag)continue;
        if(!thisIsUndoRedo){lastWasUndoRedo = 0;}
        if(turn == 1){
            player1.score += (scoreInc = checkBox(&boxes[0][0], n, inputRow, inputCol, grid, 1));
            ++player1.turnsPlayed;
            turn = scoreInc? 1:2;
        }else{
            player2.score += (scoreInc = checkBox(&boxes[0][0], n, inputRow, inputCol, grid, 2));
            ++player2.turnsPlayed;
            turn = scoreInc? 2:1;
        }
    }
    printGrid(grid, size);
    printBar(turn, player1, player2, startingTime, comp);
    if(comp && player2.score>player1.score){
        printf("\n%sComputer%s has won the game\n", "\033[0;31m", "\033[0m");
        printf("Press Enter to return to main menu\n");
    }else if(player1.score != player2.score){
        int tempScore = player1.score>player2.score? player1.score:player2.score;
        char tempName[21];
        for(int i = 0; i<20; ++i)tempName[i]='\0';
        printf("\n%sPlayer %d%s has won the game\n",
               player1.score>player2.score? "\033[0;34m":"\033[0;31m",
               player1.score>player2.score? 1:2, "\033[0m");
               if(checkHighScore(tempScore)){
                printf("\nNew High Score!\nPlease enter username (20 character max. without spaces): ");
                getName(tempName);
                updateTop10(tempName, tempScore);
                system("cls");
                printTop10();
                printf("\n\nPress Enter to return to main menu\n");
                while(getchar() != '\n');
               }
    }else{
        printf("\nIt's a tie!\n");
        printf("Press Enter to return to main menu\n");
    }
    while(getchar() != '\n');
}

//The following function returns moves left after:
//deducting one if input is -1
//increasing one if input is -2
//assigning the input to be the moves left
//doing nothing on number of moves left if input is 0
int movesLeft(int moves){
    static int movesLeft;
    if(moves == -1){
        --movesLeft;
    }else if(moves == -2){
     ++movesLeft;
    }else if(moves != 0){
        movesLeft = moves;
    }
    return movesLeft;
}

void fillWith4s(int* boxes, int n){
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            *((boxes + i*n)+j) = 4;
        }
    }
}

int checkBox(int* boxes, int n, int inputRow, int inputCol, char* grid, int playerNum){
    int boxesR, boxesC, score = 0;
    if(inputRow%2 == 1){ //line drawn is horizontal
        boxesR = inputRow/2 - 1;
        boxesC = inputCol/2 - 1;
        if(boxesR != -1 && boxesR != n-1){
            //minus one from moves left in box and assign it if moves left for that box is now zero
            if((*((boxes + (boxesR)*n)+(boxesC)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow-1, inputCol, playerNum);
                ++score;
            }
            if((*((boxes + (boxesR+1)*n)+(boxesC)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow+1, inputCol, playerNum);
                ++score;
            }
        }else if(boxesR == -1){
            if((*((boxes + (boxesR+1)*n)+(boxesC)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow+1, inputCol, playerNum);
                ++score;
            }
        }else{
            if((*((boxes + (boxesR)*n)+(boxesC)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow-1, inputCol, playerNum);
                ++score;
            }
        }
    }else{ //line drawn is vertical
        boxesC = inputCol/2 -1;
        boxesR = inputRow/2 - 1;
        if(boxesC != -1 && boxesC != n-1){
            //minus one from moves left in box and assign it if moves left for that box is now zero
            if((*((boxes + (boxesR)*n)+(boxesC)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow, inputCol-1, playerNum);
                ++score;
            }
            if((*((boxes + (boxesR)*n)+(boxesC+1)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow, inputCol+1, playerNum);
                ++score;
            }
        }else if(boxesC == -1){
            if((*((boxes + (boxesR)*n)+(boxesC+1)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow, inputCol+1, playerNum);
                ++score;
            }
        }else{
            if((*((boxes + (boxesR)*n)+(boxesC)) -= 1) == 0){
                assignBox(grid, 2*n+1, inputRow, inputCol-1, playerNum);
                ++score;
            }
        }
    }
    return score;
}

void printBar(int turn, Player player1, Player player2, int startingTime, int comp){ // prints the info under the grid
    char s1[] = "\033[1m";
    char s2[] = "\033[0m";
    int timeElapsed = time(0) - startingTime;
    printf("\n\n");
    if(movesLeft(0)){
        printf("%s",turn==1? "\033[0;34m": "\033[0;31m");
        if(comp && turn==2){
            printf("Computer's turn     ");
        }else{
            printf("Player %d's turn     ", turn);
        }
        printf("\033[0m");
    }
    printf("Total moves left: %d", movesLeft(0));
    printf("     Time elapsed: %d minute(s) %d seconds\n", timeElapsed/60, timeElapsed%60);
    printf("\033[0;34m");
    printf("\nPlayer 1:     played %d turns     Score = %d", player1.turnsPlayed, player1.score);
    printf("\033[0;31m");
    printf("\n%s:     played %d turns     Score = %d\n\n", comp? "Computer":"Player 2", player2.turnsPlayed, player2.score);
    printf("\033[0m");
    printf("%sU%s: undo   %sR%s: redo   %sS%s: save and exit   %sE%s: exit to main menu\n\n",s1,s2,s1,s2,s1,s2,s1,s2);
}

//This function is for protecting program against malicious user's input
int getInput(int* col, int* row){
    char cCol[3];
	cCol[2]='\0'; // null character for terminating string
	cCol[1]='\0';
	char cRow[3];
	cRow[2]='\0';
	cRow[1]='\0';
	char temp;
	while((cCol[0] = getchar()) == '\n');
	//for in-game menu
	if(cCol[0] == 'E' || cCol[0] == 'e'){
        if(getchar()=='\n')return 4;
        else{
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
        }
	}else if(cCol[0] == 'U' || cCol[0] == 'u'){
        if(getchar()=='\n')return 1;
        else{
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
        }
	}else if(cCol[0] == 'R' || cCol[0] == 'r'){
        if(getchar()=='\n')return 2;
        else{
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
        }
	}else if(cCol[0] == 'S' || cCol[0] == 's'){
        if(getchar()=='\n')return 3;
        else{
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
        }
	}
	//end in-game menu
	if(atoi(cCol) <= 0 || atoi(cCol) > 9){
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
	}
	cCol[1] = getchar();
	if(cCol[1] == ','){
        cCol[1] = '\0';
        *col = atoi(cCol);
	}else if(cCol[1] == '\n'){
	    *col = 0;
        *row = 0;
        return 0;
	}else if(atoi(cCol) < 10 || atoi(cCol) > 99){
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
	}else if((temp=getchar()) == ','){
        *col = atoi(cCol);
	}else{
        *col = 0;
        *row = 0;
        if(temp != '\n'){
            while(getchar() != '\n');
        }
        return 0;
	}
	//reading second number
	cRow[0] = getchar();
	if(atoi(cRow) <= 0 || atoi(cRow) > 9){
        *col = 0;
        *row = 0;
        if(cRow[0] != '\n'){
            while(getchar() != '\n');
        }
        return 0;
	}
	cRow[1] = getchar();
	if(cRow[1] == '\n'){
        cRow[1] = '\0';
        *row = atoi(cRow);
	}else if(atoi(cRow) < 10 || atoi(cRow) > 99){
        *col = 0;
        *row = 0;
        while(getchar() != '\n');
        return 0;
	}else if((temp=getchar()) == '\n'){
        *row = atoi(cRow);
	}else{
        *col = 0;
        *row = 0;
        if(temp != '\n'){
            while(getchar() != '\n');
        }
        return 0;
	}
}

void howTo(){
        int size = 3;
        char grid[size][size];
        createGrid(&grid[0][0], size);
        movesLeft(4); //initializes number of moves left till end of game
        int startingTime = time(0);
        int n = 1;
        int temp = 0; //to store value of input; useful for in-game menu
        int scoreInc; //to store increment of score
        int boxes[1][1]; // array with number of boxes where each cell contains number of sides remaining
        fillWith4s(&boxes[0][0], 1);
        Player player1 = {0,0};
        Player player2 = {0,0};
        int inputRow, inputCol;
        //First Move
        int turn = 1;
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime, 0);
        printf("Please choose column then row separated by a comma: ");
        holdOn();
        inputCol = 3;
        printf("%d", inputCol);
        holdOn();
        printf(",");
        holdOn();
        inputRow = 2;
        printf("%d", inputRow);
        holdOn();
        drawLineHowTo(grid, size, inputRow, inputCol, turn);
        ++player1.turnsPlayed;
        //Second Move
        turn = 2;
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime, 0);
        printf("Please choose column then row separated by a comma: ");
        holdOn();
        inputCol = 2;
        printf("%d", inputCol);
        holdOn();
        printf(",");
        holdOn();
        inputRow = 3;
        printf("%d", inputRow);
        holdOn();
        drawLineHowTo(grid, size, inputRow, inputCol, turn);
        ++player2.turnsPlayed;
        //Third Move
        turn = 1;
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime, 0);
        printf("Please choose column then row separated by a comma: ");
        holdOn();
        inputCol = 1;
        printf("%d", inputCol);
        holdOn();
        printf(",");
        holdOn();
        inputRow = 2;
        printf("%d", inputRow);
        holdOn();
        drawLineHowTo(grid, size, inputRow, inputCol, turn);
        ++player1.turnsPlayed;
        //Last Move
        turn = 2;
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime, 0);
        printf("Please choose column then row separated by a comma: ");
        holdOn();
        inputCol = 2;
        printf("%d", inputCol);
        holdOn();
        printf(",");
        holdOn();
        inputRow = 1;
        printf("%d", inputRow);
        holdOn();
        drawLineHowTo(grid, size, inputRow, inputCol, turn);
        ++player2.turnsPlayed;
        ++player2.score;
        assignBox(&grid[0][0], 3, 2, 2, 2);
        //End turns
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime, 0);
        printf("%sPlayer 2 has won the game%s\n", "\033[0;31m", "\033[0m");
        printf("\nPress Enter to return to main menu\n");

}

void holdOn(){
    #ifdef _WIN32
    Sleep(1000);
    #else
    sleep(1);
    #endif // _WIN32
}
