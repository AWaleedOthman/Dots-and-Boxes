void createGrid(char* grid, int size){
    //START: fill points
    for(int row = 0; row<size; row+=2){
        for(int col = 0; col<size; col+=2){
            *((grid + row*size)+col) = 'o';
        }
    }
    //END: fill points
    //START: fill spaces
    for(int row = 0; row<size; row+=2){
        for(int col = 1; col<size; col+=2){
            *((grid + row*size)+col) = ' ';
        }
    }
    for(int row = 1; row<size; row+=2){
        for(int col = 0; col<size; ++col){
            *((grid + row*size)+col) = ' ';
        }
    }
    //END: fill spaces
}

void printGrid(char* grid, int size){
    //clears the command prompt
    system("cls");
    printArt();
    printf("\n\n");
    printf("     ");
    //prints indexes above grid
    for(int i = 0; i<size; ++i){
    printf("%5d", i+1);
    }
    printf("\n\n");
    //prints grid with index before each row
    for(int row = 0; row<size; ++row){

        if(row%2 == 0){ //if row containing points
            printf("%5d", row+1);
            printf("%5c", *((grid + row*size)));
            for(int col = 1; col<size; ++col){
                if(col%2 == 0){
                    printf("%c", *((grid + row*size)+col));
                }else{
                    //changing color depending on player then back to default
                    if(*((grid + row*size)+col) == '1'){
                        printf("\033[0;34m");
                        for(int i = 0; i<9; ++i){
                            printf("%c", '-');
                        }
                        printf("\033[0m");
                    }else if(*((grid + row*size)+col) == '2'){
                        printf("\033[0;31m");
                        for(int i = 0; i<9; ++i){
                            printf("%c", '-');
                        }
                        printf("\033[0m");
                    }else{
                        for(int i = 0; i<9; ++i){
                            printf("%c", *((grid + row*size)+col));
                        }
                    }
                }
            }
            printf("\n");
        }else{ // if row not containing points
            for(int i = 0; i<3; ++i){
                if(i != 1){
                    printf("     ");
                    for(int col = 0; col<size; ++col){
                        if(*((grid + row*size)+col) != '1' && *((grid + row*size)+col) != '2'){
                            printf("     ");
                        }else{
                            if(*((grid + row*size)+col) == '1'){
                                printf("\033[0;34m");
                                printf("%5c", '|');
                                printf("\033[0m");
                            }else if(*((grid + row*size)+col) == '2'){
                                printf("\033[0;31m");
                                printf("%5c", '|');
                                printf("\033[0m");
                            }
                        }
                    }
                }else{
                    printf("%5d", row+1);
                    for(int col = 0; col<size; ++col){
                        if(*((grid + row*size)+col) == '1' || *((grid + row*size)+col) == 'B'){
                            printf("\033[0;34m");
                            if(*((grid + row*size)+col) == '1'){
                                printf("%5c", '|');
                            }else{
                                printf("%5c", 'B');
                            }
                            printf("\033[0m");
                        }else if(*((grid + row*size)+col) == '2' || *((grid + row*size)+col) == 'R'){
                            printf("\033[0;31m");
                            if(*((grid + row*size)+col) == '2'){
                                printf("%5c", '|');
                            }else{
                                printf("%5c", 'R');
                            }
                            printf("\033[0m");
                        }else{
                            printf("%5c", *((grid + row*size)+col));
                        }
                    }
                }
                printf("\n");
            }
        }
    }
}

//The following functions attempts to draw a line in a give position.
//It returns 1 if the position is valid and returns 0 otherwise.
int drawLine(char* grid, int size, int inputRow, int inputCol, int playerNum){
    if((inputRow+inputCol)%2 != 0 && *((grid + (inputRow-1)*size)+(inputCol-1)) == ' ' && inputRow<=size && inputCol<=size){
        *((grid + (inputRow-1)*size)+(inputCol-1)) = playerNum + '0';
        movesLeft(-1);
        return 1;
    }else{
        return 0;
    }
}

//The following functions attempts to assign a given position to a player.
//It returns 1 if the position is valid and returns 0 otherwise.
int assignBox(char* grid, int size, int row, int col, int playerNum){
    if(row%2 == 0 && col%2 == 0 &&*((grid + (row-1)*size)+(col-1)) == ' ' && row<=size && col<=size){
            if(playerNum == 1){
                *((grid + (row-1)*size)+(col-1)) = 'B';
            }else{
                *((grid + (row-1)*size)+(col-1)) = 'R';
            }

        return 1;
    }else{
        return 0;
    }
}

void printArt(){
    printf("            ____        _          ___     ____                      \n"
         "           |  _ \\  ___ | |_ ___   ( _ )   | __ )  _____  _____  ___  \n"
         "           | | | |/ _ \\| __/ __|  / _ \\/\\ |  _ \\ / _ \\ \\/ / _ \\/ __| \n"
         "           | |_| | (_) | |_\\__ \\ | (_>  < | |_) | (_) >  <  __/\\__ \\ \n"
         "           |____/ \\___/ \\__|___/  \\___/\\/ |____/ \\___/_/\\_\\___||___/ \n");
}
