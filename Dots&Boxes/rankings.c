#include <stdio.h>

    typedef struct{
    char name[21];
    int score;
    }Top;
    Top top10[10];

void readTop10(){
    FILE* fptr = fopen("rankings.txt", "r");
    for(int i = 0; i<10; ++i){
        fscanf(fptr, "\n%s", &top10[i].name);
        fscanf(fptr, " %d", &top10[i].score);
    }
    fclose(fptr);
}

void printTop10(){
    printArt();
    printf("\n         TOP 10\n         ======\n");
    for(int i = 0; i<10; ++i){
        printf("\n%2d.%-22s%d", i+1, top10[i].name, top10[i].score);
    }
}

void updateTop10(char newName[], int newScore){
    int i,j,match=0;
    //check for same name
    for(i = 9; i>=0; --i){
        if(strcmpCaseins(top10[i].name, newName)){
            match = 1;
            break;
        }
    }
    if(match){
        if(newScore >= top10[i].score){
            //sort Array
            for(j = i-1; j>=0; --j){
                if(top10[j].score >= newScore)break;
            }
            for(int k = i-1; k>=j; --k){
                top10[k+1] = top10[k];
            }
            strcpy(top10[j+1].name, newName);
            top10[j+1].score = newScore;
        }
    }else{ //not same name
        for(i = 9; i>=0; --i){
            if(top10[i].score >= newScore)break;
        }
        for(int j = 8; j>=i+1; --j){
            top10[j+1] = top10[j];
        }
        strcpy(top10[i+1].name, newName);
        top10[i+1].score = newScore;
    }
    //store the new updated array in the file
    FILE* fptr = fopen("rankings.txt", "w");
    for(i = 0; i<10; ++i){
        fprintf(fptr, "\n%s %d", top10[i].name, top10[i].score);
    }
    fclose(fptr);
}

int checkHighScore(int newScore){
    if(newScore > top10[9].score){
        return 1;
    }else{
        return 0;
    }
}

void getName(char tempName[]){
    char c;
    for(int i = 0; i<21; ++i){
        tempName[i] = '\0';
    }
    while((c=getchar())=='\n' || c==' ' || c=='\t');
    scanf("%20[^ \n\t]", tempName);
    for(int i = 19; i>=0; --i){
        tempName[i+1] = tempName[i];
    }
    tempName[0] = c;
}

int strcmpCaseins(char str1[], char str2[]){
    int i = 0;
    while(str1[i]!='\0' && str2[i]!='\0'){
        if(tolower(str1[i]) != tolower(str2[i])){
            return 0;
        }
        ++i;
    }
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 1;
    }else{
        return 0;
    }
}
