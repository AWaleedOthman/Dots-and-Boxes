<<<<<<< HEAD
#include <stdio.h>
#include <ctype.h>
#include <string.h>
// n ,boxes ,comp ,movesNum, grid ,playing data
void saveGrid(char* grid,int size,int comp,int moves,int fileNumber){ // saves comp,moves,grid
    FILE *save;
    char ch;
    char saved[20];
    fileName(fileNumber,saved);
    save = fopen(saved,"a");
    int n = (size-1)/2;
    fprintf(save,"%d",comp);
    fprintf(save,"%d",moves);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            ch = *(grid+(i*size)+j);
            fprintf(save,"%c", *(grid+(i*size)+j));
        }
    }
    fclose(save);
}
void saveBoxes(int* boxes, int n,int fileNumber){//saves n ,boxes
    FILE *savebox;
    char saved[20];
    fileName(fileNumber,saved);
    savebox = fopen(saved,"w");
    fprintf(savebox,"%d",n);
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            fprintf(savebox,"%d",*((boxes + i*n)+j));
        }
    }
    fclose(savebox);
}
void saveData(int score1,int turn1,int score2,int turn2,int turn, int fileNumber){ // saves data
    FILE *save;
    char saved[20];
    fileName(fileNumber,saved);
    save = fopen(saved,"a");
    fprintf(save,"*%d*%d*%d*%d*%d",turn,turn1,score1,turn2,score2);
    fclose(save);
}
void loadGrid(char* grid, int size, int fileNumber){ //load grid
    int n = (size-1)/2;
    int startRead = n*n+3;
    char startChar;
    char loaded[20];
    FILE *load;
    fileName(fileNumber,loaded);
    load = fopen(loaded,"r");
    fseek(load,startRead,SEEK_SET);
    startChar = fgetc(load);
    while(isdigit(startChar)){// if moves are more than one digit
        startChar = fgetc(load);
        startRead++;
    }
    fseek(load,startRead,SEEK_SET);//load main grid
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            *(grid+(i*size)+j) = fgetc(load);
        }
    }
    fclose(load);
}
void loadBoxes(int* boxes, int n,int fileNumber){ //loads n , boxes moves
    int fillW4;
    char loaded[20];
    FILE *load;
    fileName(fileNumber,loaded);
    load = fopen(loaded,"r");
    fscanf(load,"%1d",&n);
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            fscanf(load,"%1d",&fillW4);
            *((boxes + i*n)+j) = fillW4;
        }
    }
    fclose(load);
}
void loadData(int* turn, int* turn1, int* score1, int* turn2, int* score2,int fileNumber){ //load rest of data
    char ch;
    char loaded[20];
    FILE *load;
    fileName(fileNumber,loaded);
    load = fopen(loaded,"r");
    while(!feof(load)){
        ch = fgetc(load);
        if(ch == '*'){
            fscanf(load,"%d",turn);
            break;
        }
    }
    while(!feof(load)){
        ch = fgetc(load);
        if(ch == '*'){
            fscanf(load,"%d",turn1);
            break;
        }
    }
    while(!feof(load)){
        ch = fgetc(load);
        if(ch == '*'){
            fscanf(load,"%d",score1);
            break;
        }
    }
    while(!feof(load)){
        ch = fgetc(load);
        if(ch == '*'){
            fscanf(load,"%d",turn2);
            break;
        }
    }
    while(!feof(load)){
        ch = fgetc(load);
        if(ch == '*'){
            fscanf(load,"%d",score2);
            break;
        }
    }
    fclose(load);
}
void fileName(int fileNumber, char file[]){ //which file to save and load
    if(fileNumber == 1){
        strcpy(file,"save1.txt");
    }
    else if(fileNumber == 2){
        strcpy(file,"save2.txt");
    }
    else{
        strcpy(file,"save3.txt");
    }
}
