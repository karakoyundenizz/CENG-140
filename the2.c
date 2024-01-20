#include <stdio.h>
#include <stdlib.h>

int ext = 0;

int search(char **array, int x, int y,int row, int column){
    if( x < 0 || y < 0){
        return 0;
    }
    else if(x > column || y > row){
        return 0;
    }
    else if(array[y][x] == 'X'){
        return 0;
    }
    else if((x == 0 || x == column || y == row || y == 0) && (array[y][x] == ' ') ){
        array[y][x] = '*';
        ext = 3;
        return 13;
    }
    
    if(array[y][x] == ' ') {
        array[y][x] = '*';

        if(search(array, x, y + 1, row,column) == 13){
            return 13;
        } 
        else if(search(array, x, y - 1, row,column) == 13){
            return 13;
        } 
        else if(search(array, x - 1, y, row,column) == 13){
            return 13;
        }
        else if(search(array, x + 1, y, row,column) == 13){
            return 13;
        }
        array[y][x] = '.' ;
        return 0;
    }
    return 0;
}


int main(){
    
    char **array;
    int row = 0, column = 0, x, y, i, j,temp_column;
    char  temp;
    array = (char**)malloc(sizeof(char*)*1);
    
    scanf("%d %d", &x, &y);
    getchar();
    /* Take inputs */
    while (temp != EOF){
        temp = getchar();
           
        if(column == 0 && temp != EOF){
            array[row] = (char*)malloc(sizeof(char));
            array[row][column] = temp;
            column++;
        }
        
        else if(temp != '\n' && temp != EOF){
            array[row] =(char*)realloc(array[row],sizeof(char)*(column +1));
            array[row][column] = temp;
            column++;
        }

        else if (temp == '\n'){
            row++;
            temp_column = column;
            column = 0;
            array = (char**)realloc(array, sizeof(char*) * (row + 1));
        }
    }
    search(array, x, y, row-1, temp_column-1);
    /* if there is no path turn '*' s to '.'   */
    if(ext == 3){
        for(i = 0; i < row; i++ ){
            for(j = 0; j < temp_column; j++){
                if(array[i][j] == '.'){
                    array[i][j] = ' ';
                }
            }
        }
    }
    /* print ettirme*/
    for(i = 0; i < row ; i++){
        for(j = 0; j < temp_column;j ++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
        /* heap boşaltma*/
    for(i = 0; i < row; i++){
        free(array[i]);
        }
    free(array);

    return 0;
}
