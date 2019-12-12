int compSearchNum(char* boxes,int n ,int* compcol,int * comprow,char numSearch){// numsearch is the number to search for in the small grid
int i,j,z=0;
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        if(*((boxes+i*n)+j)==numSearch){
           z=1;
           * comprow=i*2+1;
           * compcol=j*2+1;
           break;
        }
        if(z==1){
            break;
        }
    }
}
return z;
}
void compSearchRc(char* grid,int size,int* compcol,int* comprow){// this function searches for the row and col where the computer will play
int row=*comprow;
int col=*compcol;
    if(*((grid+row*size)+(col+1))==' '){
        *comprow+=1;
        *compcol+=2;
}
    else if(*((grid+row*size)+(col-1))==' '){
        *comprow+=1;
}
    else if(*((grid+(row+1)*size)+col)==' '){
        *comprow+=2;
        *compcol+=1;
}
    else if(*((grid+(row-1)*size)+col)==' '){
        *compcol+=1;
}
}
<<<<<<< HEAD
/*
void compChoose(){
if (compsearch(&boxes[0][0],n,compcol,comprow,1)){
=======
void compChoose(char *boxes,int n,char *grid,int size ,int *comprow,int *compcol){
if (compsearch(boxes,n,compcol,comprow,'1')){
>>>>>>> 2d330c7171c6ba101c2c51080a7b065bb9ccf7cd
    comSearchRc(grid,size,compcol,comrow);
}
else if(compsearch(boxes,n,compcol,comprow,'3')){
    comSearchRc(grid,size,compcol,comrow);
}
else if (compsearch(boxes,n,compcol,comprow,'4')){
    comSearchRc(grid,size,compcol,comrow);
}
else if(compsearch(boxes,n,compcol,comprow,'2')){
      comSearchRc(grid,size,compcol,comrow);
}
}
*/
