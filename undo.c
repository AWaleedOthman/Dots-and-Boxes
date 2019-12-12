typedef struct{ // structure containing both players
    int turnsPlayed;
    int score;
    }Player;

void fillWith0s(int* undo, int* redo, int possibleMoves){
    for(int i = 0; i < possibleMoves; ++i){ //Undo
        for(int j = 0; j < 3; ++j){
            *(undo+(3*i)+j) = 0;
        }
    }
    for(int i = 0; i < possibleMoves; ++i){ //Redo
        for(int j = 0; j < 3; ++j){
            *(redo+(3*i)+j) = 0;
        }
    }
}

void addUndo(int* undo, int inputRow, int inputCol, int turn){
    int i=0;
    while(*(undo+i*3) != 0){
        ++i;
    }
    *(undo+i*3) = inputRow;
    *(undo+ i*3 + 1) = inputCol;
    *(undo+ i*3 + 2) = turn;
}

void addRedo(int* redo, int inputRow, int inputCol, int turn){
    int i=0;
    while(*(redo+i*3) != 0){
        ++i;
    }
    *(redo+i*3) = inputRow;
    *(redo+ i*3 + 1) = inputCol;
    *(redo+ i*3 + 2) = turn;
}

void deleteLine(char* grid, int size, int inputRow, int inputCol){
    *((grid + (inputRow-1)*size)+(inputCol-1)) = ' ';
    movesLeft(1);
}

void undoPlay(char* grid, int size, int* undo, int possibleMoves, int* boxes,
               int* turn, Player* player1, Player* player2, int* redo){

    int temp = 0;
    int i = possibleMoves-1;
    while(i>=0 && *(undo + 3*i) == 0){--i;}
    if(i != -1){ //undo valid
        deleteLine(grid, size, *(undo+i*3), *(undo+ i*3 + 1));
        //increase remaining sides in boxes
        temp = checkBoxAgain(boxes, (size-1)/2, *(undo+i*3), *(undo+ i*3 + 1), grid);
        //minus one from turnsPlayed
        if(*(undo+ i*3 + 2) == 1){
            --(*player1).turnsPlayed;
            (*player1).score += temp;
        }
        else if(*(undo+ i*3 + 2) == 2){
            --(*player2).turnsPlayed;
            (*player2).score += temp;
        }
        //swap turn
        *turn = *(undo+ i*3 + 2);
        //addRedo
        addRedo(redo, *(undo+i*3), *(undo+ i*3 + 1), *(undo+ i*3 + 2));
        *(undo+i*3) = 0;
        *(undo+ i*3 + 1) = 0;
        *(undo+ i*3 + 2) = 0;
    }
}

int checkBoxAgain(char* boxes, int n, int inputRow, int inputCol, char* grid){
    int boxesR, boxesC, score = 0;
    if(inputRow%2 == 1){ //line drawn is horizontal
        boxesR = inputRow/2 - 1;
        boxesC = inputCol/2 - 1;
        if(boxesR != -1 && boxesR != n-1){
            //minus one from moves left in box and assign it if moves left for that box is now zero
            if((*((boxes + (boxesR)*n)+(boxesC)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow-1, inputCol);
                --score;
            }
            if((*((boxes + (boxesR+1)*n)+(boxesC)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow+1, inputCol);
                --score;
            }
        }else if(boxesR == -1){
            if((*((boxes + (boxesR+1)*n)+(boxesC)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow+1, inputCol);
                --score;
            }
        }else{
            if((*((boxes + (boxesR)*n)+(boxesC)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow-1, inputCol);
                --score;
            }
        }
    }else{ //line drawn is vertical
        boxesC = inputCol/2 -1;
        boxesR = inputRow/2 - 1;
        if(boxesC != -1 && boxesC != n-1){
            //minus one from moves left in box and assign it if moves left for that box is now zero
            if((*((boxes + (boxesR)*n)+(boxesC)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow, inputCol-1);
                --score;
            }
            if((*((boxes + (boxesR)*n)+(boxesC+1)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow, inputCol+1);
                --score;
            }
        }else if(boxesC == -1){
            if((*((boxes + (boxesR)*n)+(boxesC+1)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow, inputCol+1);
                --score;
            }
        }else{
            if((*((boxes + (boxesR)*n)+(boxesC)) += 1) == 1){
                assignBoxAgain(grid, 2*n+1, inputRow, inputCol-1);
                --score;
            }
        }
    }
    return score;
}

void assignBoxAgain(char* grid, int size, int row, int col){
                *((grid + (row-1)*size)+(col-1)) = ' ';
}

void redoPlay(int* inputRow, int* inputCol, int* redo, int possibleMoves, int* turn){
    int i = possibleMoves-1;
    while(i>=0 && *(redo + 3*i) == 0)--i;
    if(i == -1){
        *inputCol = 0;
        *inputRow = 0;
    }else{
        *inputRow = *(redo + 3*i);
        *(redo + 3*i) = 0;
        *inputCol = *(redo + 3*i + 1);
        *(redo + 3*i + 1) = 0;
        *turn = *(redo + 3*i + 2);
        *(redo + 3*i + 2) = 0;
    }

}

void clearRedo(int* redo, int possibleMoves){
   for(int i = 0; i < possibleMoves; ++i){ //Redo
        for(int j = 0; j < 3; ++j){
            *(redo+(3*i)+j) = 0;
        }
    }
}
