int searchForTwo(int *boxes,int n,int searchRow,int searchCol){//checks if the box of Column searchCol and row searchRow in boxes grid has 2 in it
int z=0;
if(*(boxes+searchRow*n+searchCol)==2){
    z=1;
}
return z;
}
int searchForTwoX(int *boxes,int n,int row,int column){//counts the number of twos around giving indices
int i=row;
int j=column;
int z=0;
            if(i==0){
                if(j==0){
                    if((searchForTwo(boxes,n,0,1))==1){
                       z++;
                    if((searchForTwo(boxes,n,1,0))==1){
                        z++;
                    }
                    }
                }
                else if(j==n-1){
                    if(searchForTwo(boxes,n,1,n-1)==1){
                        z++;
                    }
                    if(searchForTwo(boxes,n,0,n-2)==1){
                        z++;
                    }
                }
                else{
                    if(searchForTwo(boxes,n,0,j+1)==1){
                    z++;
                    }
                    if(searchForTwo(boxes,n,0,j-1)==1){
                        z++;
                    }
                    if(searchForTwo(boxes,n,1,j)==1){
                        z++;
                    }
                }
            }
            else if(i==n-1){
                if(j==0){
                    if(searchForTwo(boxes,n,n-2,0)==1){
                            z++;
                    }
                    if(searchForTwo(boxes,n,n-1,1)==1){
                        z++;
                    }
                }
                else if(j==n-1){
                    if(searchForTwo(boxes,n,n-2,n-1)==1){
                            z++;
                    }
                    if(searchForTwo(boxes,n,n-1,n-2)==1){
                        z++;
                    }
                }
                else{
                    if(searchForTwo(boxes,n,n-1,j+1)==1){
                       z++;
                    }
                    if(searchForTwo(boxes,n,n-1,j-1)==1){
                        z++;
                    }
                    if(searchForTwo(boxes,n,n-2,j)==1){
                        z++;
                    }
                }
            }
            else if (j==0){
                if(searchForTwo(boxes,n,i-1,j)==1){
                    z++;
                }
                if(searchForTwo(boxes,n,i+1,j)==1){
                    z++;
                }
                if(searchForTwo(boxes,n,i,j+1)==1){
                    z++;
                }
            }
            else if (j==n-1){
                if(searchForTwo(boxes,n,i-1,j)==1){
                 z++;
                }
                if(searchForTwo(boxes,n,i+1,j)==1){
                    z++;
                }
                if(searchForTwo(boxes,n,i,j-1)==1){
                    z++;
                }
            }
            else{
                if(searchForTwo(boxes,n,i-1,j)==1){
                    z++;
                }
                if(searchForTwo(boxes,n,i+1,j)==1){
                    z++;
                }
                if(searchForTwo(boxes,n,i,j-1)==1){
                    z++;
                }
                if(searchForTwo(boxes,n,i,j+1)==1){
                    z++;
                }

            }
            return z;
        }
int searchForTF(int *boxes,int n,int*compcol,int *comprow,int numSearch){//searches for 3 or 4 with least number of 2's around
int i,j,z=0,k=0,g=0;
while(n!=-1){
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(*((boxes+i*n)+j)==numSearch){
               if(searchForTwoX(boxes,n,i,j)==k){
                *compcol=2*j+1;
                *comprow=2*i+1;
                z=1;
                break;
               }
            }
            }
            if(z==1){
                n=-1;
                break;
            }
        }
        k++;
        if(k==5){
            break;
        }
        }
        return z;
}
int compSearchNum(int* boxes,int n ,int* compcol,int * comprow,int numSearch){// numsearch is the number to search for in the small grid
    int i,j,z=0;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(*((boxes+i*n)+j)==numSearch){
               z=1;
               *comprow=i*2+1;
               *compcol=j*2+1;
               break;
            }
            if(z==1){
                break;
            }
        }
    }
    return z;
}
int compSearchNumX(int* boxes,int n,int compcol,int comprow,int numSearch){//checks if box of col x and row y in boxes grid has a specific number in it (2)
int z=0;
int x,y;
x=(compcol-1)/2;
y=(comprow-1)/2;
if (((*((boxes+y*n)+x)))==numSearch){
    z=1;
}
return z;
}
void compSearchRc(char* grid,int size,int* compcol,int* comprow){// this function searches for the row and col where the computer will play
    int row= *comprow;
    int col= *compcol;
        if( *((grid+row*size)+(col+1))==' '){
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
void compSearchRcX(char* grid,int size,int *boxes,int n,int* compcol,int* comprow){// this function searches for the row and col where the computer will play
    int row= *comprow;
    int col= *compcol;
    if(row==1||col==1||row==size-2||col==size-2){
        if(row==1){
            if(col==1){
                if(*((grid+(row-1)*size)+col)==' '){
                    *compcol+=1;
    }
                else if(*((grid+row*size)+(col-1))==' '){
                    *comprow+=1;
                }
                else if( *((grid+row*size)+(col+1))==' '&&((compSearchNumX(boxes,n,*compcol+2,*comprow,2))!=1)){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if(*((grid+(row+1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow+2,2))!=1)){
                    *comprow+=2;
                    *compcol+=1;
    }
                else if(*((grid+row*size)+(col+1))==' '){
                    *comprow+=1;
                    *compcol+=2;
                }
                else if(*((grid+(row+1)*size)+col)==' '){
                     *comprow+=2;
                     *compcol+=1;
                }
            }
            else if(col==size-2){
                if(*((grid+(row-1)*size)+col)==' '){
                    *compcol+=1;
    }
                else if( *((grid+row*size)+(col+1))==' '){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if(*((grid+row*size)+(col-1))==' '&&((compSearchNumX(boxes,n,*compcol-2,*comprow,2))!=1)){
                    *comprow+=1;
                }

                else if(*((grid+(row+1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow+2,2))!=1)){
                    *comprow+=2;
                    *compcol+=1;
    }
                else if(*((grid+row*size)+(col-1))==' '){
                    *comprow+=1;
                }
                else if (*((grid+(row+1)*size)+col)==' '){
                    *comprow+=2;
                    *compcol+=1;
                }
            }
            else {
                if(*((grid+(row-1)*size)+col)==' '){
                    *compcol+=1;
    }
                else if(*((grid+row*size)+(col-1))==' '&&((compSearchNumX(boxes,n,*compcol-2,*comprow,2))!=1)){
                    *comprow+=1;
                }

                else if(*((grid+(row+1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow+2,2))!=1)){
                    *comprow+=2;
                    *compcol+=1;
    }
                else if( *((grid+row*size)+(col+1))==' '&&((compSearchNumX(boxes,n,*compcol+2,*comprow,2))!=1)){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if (*((grid+row*size)+(col-1))==' '){
                    *comprow+=1;
                }
                else if (*((grid+(row+1)*size)+col)==' '){
                    *comprow+=2;
                    *compcol+=1;
                }
                else if (*((grid+row*size)+(col+1))==' '){
                    *comprow+=1;
                    *compcol+=2;
                }
            }
        }
        else if(row==size-2){
            if(col==1){
                if(*((grid+row*size)+(col-1))==' '){
                    *comprow+=1;
                }
                else if(*((grid+(row+1)*size)+col)==' '){
            *comprow+=2;
            *compcol+=1;
    }
                else if( *((grid+row*size)+(col+1))==' '&&((compSearchNumX(boxes,n,*compcol+2,*comprow,2))!=1)){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if(*((grid+(row-1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow-2,2))!=1)){
                    *comprow+=2;
                    *compcol+=1;
    }
                else if(*((grid+row*size)+(col+1))==' '){
                    *comprow+=1;
                    *compcol+=2;
                }
                else if (*((grid+(row-1)*size)+col)==' '){
                    *comprow+=2;
                    *compcol+=1;
                }

            }
            else if (col==size-2){
                if(*((grid+(row+1)*size)+col)==' '){
                    *comprow+=2;
                    *compcol+=1;
    }
                else if( *((grid+row*size)+(col+1))==' '){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if(*((grid+row*size)+(col-1))==' '&&((compSearchNumX(boxes,n,*compcol-2,*comprow,2))!=1)){
                    *comprow+=1;
                }
                else if(*((grid+(row-1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow-2,2))!=1)){
                    *compcol+=1;
    }
                else if(*((grid+row*size)+(col-1))==' '){
                    *comprow+=1;
                }
                else if (*((grid+(row-1)*size)+col)==' '){
                    *compcol+=1;
                }
            }
            else{
                if(*((grid+(row+1)*size)+col)==' '){
                    *comprow+=2;
                    *compcol+=1;
    }
                else if( *((grid+row*size)+(col+1))==' '&&((compSearchNumX(boxes,n,*compcol+2,*comprow,2))!=1)){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if(*((grid+row*size)+(col-1))==' '&&((compSearchNumX(boxes,n,*compcol-2,*comprow,2))!=1)){
                    *comprow+=1;
    }
                else if(*((grid+(row-1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow-2,2))!=1)){
                    *compcol+=1;
    }
                else if( *((grid+row*size)+(col+1))==' '){
                    *comprow+=1;
                    *compcol+=2;
    }
                else if(*((grid+row*size)+(col-1))==' '){
                    *comprow+=1;
    }
                else if(*((grid+(row-1)*size)+col)==' '){
                    *compcol+=1;
    }
            }
        }
        else if(col==1){
            if(*((grid+row*size)+(col-1))==' '){
                *comprow+=1;
    }
            else if( *((grid+row*size)+(col+1))==' '&&((compSearchNumX(boxes,n,*compcol+2,*comprow,2))!=1)){
            *comprow+=1;
            *compcol+=2;
    }
            else if(*((grid+(row+1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow+2,2))!=1)){
                *comprow+=2;
                *compcol+=1;
    }
            else if(*((grid+(row-1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow-2,2))!=1)){
                *compcol+=1;
    }
            else if( *((grid+row*size)+(col+1))==' '){
            *comprow+=1;
            *compcol+=2;
    }
            else if(*((grid+(row+1)*size)+col)==' '){
                *comprow+=2;
                *compcol+=1;
    }
            else if(*((grid+(row-1)*size)+col)==' '){
                *compcol+=1;
    }
        }
        else if (col==size-2){
            if( *((grid+row*size)+(col+1))==' '){
            *comprow+=1;
            *compcol+=2;
    }
        else if(*((grid+row*size)+(col-1))==' '&&((compSearchNumX(boxes,n,*compcol-2,*comprow,2))!=1)){
            *comprow+=1;
    }
        else if(*((grid+(row+1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow+2,2))!=1)){
            *comprow+=2;
            *compcol+=1;
    }
        else if(*((grid+(row-1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow-2,2))!=1)){
            *compcol+=1;
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

    }
    else {
        if( *((grid+row*size)+(col+1))==' '&&((compSearchNumX(boxes,n,*compcol+2,*comprow,2))!=1)){
            *comprow+=1;
            *compcol+=2;
    }
        else if(*((grid+row*size)+(col-1))==' '&&((compSearchNumX(boxes,n,*compcol-2,*comprow,2))!=1)){
            *comprow+=1;
    }
        else if(*((grid+(row+1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow+2,2))!=1)){
            *comprow+=2;
            *compcol+=1;
    }
        else if(*((grid+(row-1)*size)+col)==' '&&((compSearchNumX(boxes,n,*compcol,*comprow-2,2))!=1)){
            *compcol+=1;
    }

        else if( *((grid+row*size)+(col+1))==' '){
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
}
void compChoose(int *boxes, int n, char *grid, int size , int *comprow, int *compcol){
    if (compSearchNum(boxes,n,compcol,comprow,1)){
        compSearchRc(grid,size,compcol,comprow);
    }
    else if(searchForTF(boxes,n,compcol,comprow,3)){
        compSearchRcX(grid,size,boxes,n,compcol,comprow);
    }
    else if (searchForTF(boxes,n,compcol,comprow,4)){
        compSearchRcX(grid,size,boxes,n,compcol,comprow);
    }
    else if(compSearchNum(boxes,n,compcol,comprow,2)){
        compSearchRc(grid,size,compcol,comprow);
    }
}

