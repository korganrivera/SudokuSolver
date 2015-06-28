/*  sudoku solver.
    start:  2015.6.27.21:23
    end:    2015.6.27.23:05
*/

#include <stdio.h>
#include <stdlib.h>

unsigned grid[9][9]={
    {8,0,0,0,0,0,0,0,0},
    {0,0,3,6,0,0,0,0,0},
    {0,7,0,0,9,0,2,0,0},
    {0,5,0,0,0,7,0,0,0},
    {0,0,0,0,4,5,7,0,0},
    {0,0,0,1,0,0,0,3,0},
    {0,0,1,0,0,0,0,6,8},
    {0,0,8,5,0,0,0,1,0},
    {0,9,0,0,0,0,4,0,0}
};

void func(unsigned x);
void show(void);

int main(void){
    puts("\n problem:");
    show();
    func(0);
    puts("\n unsolvable.");
}

void func(unsigned x){
    unsigned quadindex, i, list[9]={1,1,1,1,1,1,1,1,1};

    //  if at element 81, the grid is complete. display and end.
    if(x==81){ puts("\n solution:"); show(); exit(0); }

    //  if element isn't zero, skip over it.
    if(grid[x/9][x%9]){ func(x+1); return; }

    quadindex = 3*(x/27) + (x/3)%3;                 //  get quad's index.

    for(i=0; i<9; i++){
        if(grid[i][x%9]) list[grid[i][x%9]-1]=0;    //  check current column.
        if(grid[x/9][i]) list[grid[x/9][i]-1]=0;    //  check current row.
        if(grid[i/3+(quadindex/3)*3][i%3+(quadindex%3)*3]) list[grid[i/3+(quadindex/3)*3][i%3+(quadindex%3)*3]-1]=0; //  check current quad.
    }

    //  now all the numbers that element x could be are noted in list[].
    //  if list is empty, then something is fucked, so return.
    for(i=0; i<9; i++) if(list[i]) break;
    if(i==9) return;

    //  try the first element in the list, and move onto next element after backtrack.
    for(i=0; i<9; i++){
        if(!list[i]) continue;
        grid[x/9][x%9] = i+1;
        func(x+1);
    }

    //  if used all values in the list, reset this element so next call can find it.
    grid[x/9][x%9]=0;
}

void show(void){
    unsigned i;
    for(i=0; i<81; i++){ if(!(i%9)) putchar('\n'); printf(" %u", grid[i/9][i%9]); }
    putchar('\n');
}
