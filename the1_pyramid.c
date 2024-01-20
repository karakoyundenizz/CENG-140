#include <stdio.h>
double bas(int x, int y, double weight, double hstry[51][51]) {
    double sol_basnc, sag_basnc, basnc;
    if(hstry[x][y] != 0){
        return hstry[x][y];
    }
    else if (x == 0){
        return 0;
    }
    else if (x == y){
        basnc = bas(x-1, y-1, weight, hstry) * 0.15 + (weight * 0.5) ;
    }
    else if (y == 0){
        basnc = bas(x-1, y, weight, hstry) * 0.15 + (weight * 0.5) ;
    }
    else if (y != 0 && x != y){
        basnc =  (bas(x-1, y-1, weight,hstry) + bas(x-1, y, weight,hstry)) * 0.15 + weight;
    }
    else {
        basnc = 0;
    }
    hstry[x][y] = basnc;
    return basnc;
}

void print_func(int x, int y, double weight, int son_x, double hstry[51][51]) {
    if (x != y) {
        printf("(%d,%d) %.8f\n", x, y, bas(x,y,weight,hstry));
        print_func(x, y+1, weight, son_x,hstry);
    }
    if (x != son_x && y == x) {
        printf("(%d,%d) %.8f\n", x, y, bas(x,y,weight,hstry));
        print_func(x+1, 0, weight, son_x,hstry);
    }
    if (x == son_x && y == x) {
        printf("(%d,%d) %.8f\n", x, y, bas(x,y,weight,hstry));
    }
}
double calculate_pressure_on_block(int row, int column, double block_weight ){
    double hstry[51][51] = {0};
    print_func(0, 0, block_weight, row-1, hstry);
    return 5.0;
}

int main(){
    int katman;
    double weight;
    scanf("%d %lf", &katman, &weight);
    calculate_pressure_on_block(katman,katman,weight);
    return 0;
}
