#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
//dimensions of the array must be passed to the function as parameters, since C does not 
//allow you to determine the size of a multi-dimensional array at runtime.
int **createBoard(int rows, int columns, int fill_value){ //Create the Board (O(n^2))
  int **Board;
  Board = malloc(sizeof(int *) * rows); 
  //Allocate memory for the amount of rows we have
  for (int i = 0; i < rows; i++){
    Board[i] = malloc(sizeof(int) * columns);
    //For each amount of rows, we allocate space for the columns
  }
  //Fill the board with the fill_values
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      Board[i][j] = fill_value;
    }
  }
  return Board;
}


bool isBalanced(int rows, int columns){ //O(1)
    //Checks if board can be actually made into a balanced sudoku (4x4,9x9,16x16 etc...)
    //Basically checks if the rows and columns match and if they can be squarerooted
    double rowsD = rows;
    double columnsD = columns;
    double rowsResult = (rowsD / sqrt(rows));
    double columnsResult = (columnsD / sqrt(columnsD));
    int rowsResult2 = (rows/sqrt(rows));
    int columnsResult2 = (columns/sqrt(columns));
    if (rowsResult == rowsResult2 && columnsResult == columnsResult2 && rows == columns){
        return true;
    }
    else{
        return false;
    }
}

bool isPrime(int size){
    //checks if row/column of board is prime number
    for (int i = 2 ; i <= size - 1 ; i++ )
    { 
      if ( size % i== 0 ){
          return false;
      }
    }
    return true;
}

void printBoard(int **Board, int rows, int columns){ //Prints the board (O(n^2))
  if (isPrime(rows) == false || isPrime(columns) == false){ //Tests if the Sudoku is a balanced square
      for (int i = 0; i < rows; i++)
      {
        int rowsResult = sqrt(rows);
        if (i > 0 && i % rowsResult == 0 && isPrime(rows) == false){ 
            //To print the horizontal line borders (deactivates if prime)
            for (int k = 1; k < columns; k++){
                printf("--");
            }

            printf("-\n");
        }
        for (int j = 0; j < columns; j++){
            int columnsResult = sqrt(columns);
            if (j > 0 && j % columnsResult == 0 && isPrime(columns) == false){
                //To print the vertical line borders (deactivates if prime)
                printf("\b|"); //\b is backspace to remove the extra space
            }
            printf("%d ", *(*(Board + i) + j));
            //First finds the pointer to board at *(Board + i), then find the pointer to j and prints the element there.
        }
        printf("\n");
      }
  }
  else{ //If sudoku is funky looking
     for (int i = 0; i < rows; i++)
      {
        for (int j = 0; j < columns; j++)
          printf("%d ", *(*(Board + i) + j));
          //First finds the pointer to board at *(Board + i), then find the pointer to j and prints the element there.
        printf("\n");
      }
  }
}

int main(void)
{
  int **Board;
  int m = 6;
  int n = 6;
  Board = createBoard(m,n,2);
  printBoard(Board,m,n);
  printf("Input the amount of rows: ");
  scanf("%d", &m);
  printf("Input the amount of columns: ");
  scanf("%d", &n);
  return 0;
}


