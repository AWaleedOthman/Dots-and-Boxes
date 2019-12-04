#include <stdio.h>
#include <stdlib.h>
#include "grid.h"



int main()
{
    int n = 3;
    int size = 2*n+1;
    char grid[size][size];
    createGrid(&grid[0][0], size);

    assignBox(&grid[0][0], size, 2, 2, 1);
    assignBox(&grid[0][0], size, 2, 2, 2);
    printGrid(&grid[0][0], size);
    drawLine(&grid[0][0], size, 5, 1, 2);
    drawLine(&grid[0][0], size, 5, 1, 1);
    printGrid(&grid[0][0], size);
    return 0;
}
