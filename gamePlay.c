typedef struct{ // structure containing both players
    int turnsPlayed;
    int score;
    }Player;

void play(char* grid, int size){
    int startingTime = time(0);
    int n = (size-1)/2;
    int scoreInc; //to store increment of score
    char boxes[n][n]; // array with number of boxes where each cell contains number of sides remaining
    fillWith4s(&boxes[0][0], n);
    Player player1 = {0,0};
    Player player2 = {0,0};
    int inputRow, inputCol;
    int turn = 1;
    while(movesLeft(0)){
        printGrid(grid, size);
        printBar(turn, player1, player2, startingTime);
        printf("Please choose column then row separated by a comma: ");
        getInput(&inputCol, &inputRow);
        while(!drawLine(grid, size, inputRow, inputCol, turn)){
            printf("Invalid\n");
            printf("Please choose column then row separated by a comma: ");
            getInput(&inputCol, &inputRow);
        }
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
    printBar(turn, player1, player2, startingTime);
    if(player1.score != player2.score){
        printf("\n%sPlayer %d%s has won the game\n",
               player1.score>player2.score? "\033[0;34m":"\033[0;31m",
               player1.score>player2.score? 1:2, "\033[0m");
    }else{
        printf("\nIt's a tie!\n");
    }
}

//The following function returns moves left after:
//deducting one if input is -1
//assigning the input to be the moves left
//doing nothing on number of moves left if input is 0
int movesLeft(int moves){
    static int movesLeft;
    if(moves == -1){
        --movesLeft;
    }else if(moves != 0){
        movesLeft = moves;
    }
    return movesLeft;
}

void fillWith4s(char* boxes, int n){
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            *((boxes + i*n)+j) = 4;
        }
    }
}

int checkBox(char* boxes, int n, int inputRow, int inputCol, char* grid, int playerNum){
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

void printBar(int turn, Player player1, Player player2, int startingTime){ // prints the info under the grid
    int timeElapsed = time(0) - startingTime;
    printf("\n\n");
    printf("%s",turn==1? "\033[0;34m": "\033[0;31m");
    printf("Player %d's turn", turn);
    printf("\033[0m");
    printf("     Total moves left: %d", movesLeft(0));
    printf("     Time elapsed: %d minute(s) %d seconds\n", timeElapsed/60, timeElapsed%60);
    printf("\033[0;34m");
    printf("\nPlayer 1:     played %d turns     Score = %d", player1.turnsPlayed, player1.score);
    printf("\033[0;31m");
    printf("\nPlayer 2:     played %d turns     Score = %d\n\n", player2.turnsPlayed, player2.score);
    printf("\033[0m");
}

//This function is for protecting program against malicious user's input
void getInput(int* col, int* row){
    char cCol[3];
	cCol[2]='\0'; // null character for terminating string
	char cRow[3];
	cRow[3]='\0';
	char temp[256];
	for(int i = 0; i<255; ++i){
	    temp[i]=',';
	}
	temp[255]='\0';
	scanf("%2[^,]%255[^,]", cCol, temp);
	while(temp[254] != ','){
	    for(int i = 0; i<255; ++i){
	    temp[i]=',';
		}
		scanf("%255[^,]",temp);
	}
	scanf(",%2[^ \n \t]", cRow);
	/*
	scanf("%255[^\n]", temp);
	while(temp[254] != ','){
	    for(int i = 0; i<255; ++i){
	    temp[i]=',';
		}
		scanf("%255[^\n]",temp);
	}*/
	*col = atoi(cCol);
	*row = atoi(cRow);
}
