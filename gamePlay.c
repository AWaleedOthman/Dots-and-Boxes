void play(char* grid, int size){
    int inputRow, inputCol;
    int turn = 1;
    while(movesLeft(0)){
        printGrid(grid, size);
        printf("Please choose row then column separated by a comma: ");
        scanf("%d,%d", &inputCol, &inputRow);
        while(!drawLine(grid, size, inputRow, inputCol, turn)){
            printf("Invalid\n");
            printf("Please choose column then row separated by a comma: ");
            scanf("%d,%d", &inputCol, &inputRow);
        }
        turn = turn==1? 2:1;
    }
    printGrid(grid, size);
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
