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

bool isValid(int **board, int rows, int columns, int row, int column, int num) { //O(n)
    // Check the number in the current row and column
    for (int x = 0; x < rows; x++)
        if (board[row][x] == num)
            return false;
    for (int x = 0; x < columns; x++)
        if (board[x][column] == num)
            return false;
    
    // Check the number in the current grid
    int startRow = row - row % (int)sqrt(rows);
    int startColumn = column - column % (int)sqrt(columns);
    for (int i = 0; i < sqrt(rows); i++)
        for (int j = 0; j < sqrt(columns); j++)
            if (board[i + startRow][j + startColumn] == num)
                return false;
    
    return true;
}

bool solveSudoku(int **board, int rows, int columns) { //O(n^n)
    int row = -1;
    int column = -1;
    bool isEmpty = true;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == 0) {
                row = i;
                column = j;

                // We still have some remaining cells in the Sudoku
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty)
            break;
    }

    // No empty space left
    if (isEmpty)
        return true;
    
    // Else for each-row backtrack
    for (int num = 1; num <= rows; num++) {
        if (isValid(board, rows, columns, row, column, num)) {
            board[row][column] = num;
            if (solveSudoku(board, rows, columns))
                return true;
            else
                board[row][column] = 0;  // replace it
        }
    }
    return false;
}


int main(void){
    int rows = 4;
    int columns = 4;

    // This is a solvable 4x4 sudoku puzzle
    int sudoku[4][4] = {
        {2, 0, 0, 0},
        {0, 1, 0, 2},
        {0, 0, 3, 0},
        {0, 0, 0, 4}
    };

    // Create the sudoku board
    int **board = createBoard(rows, columns, 0);

    // Fill the board with the unsolved sudoku values
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            board[i][j] = sudoku[i][j];
        }
    }

    // Solve the sudoku and print the result
    if (solveSudoku(board, rows, columns)){
        printBoard(board, rows, columns);
    } else {
        printf("No solution exists for the provided Sudoku puzzle.\n");
    }

    // Don't forget to free the memory allocated for the board
    for (int i = 0; i < rows; i++){
        free(board[i]);
    }
    free(board);
    
    return 0;
}

