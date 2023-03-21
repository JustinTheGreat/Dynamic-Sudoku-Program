#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
int **create_grid(int m, int n){
//Based off the link: https://github.com/portfoliocourses/c-example-code/blob/main/return_dynamic_2d_array.c
//m = Rows, n = columns
  int **matrix;
  matrix = malloc(sizeof(int *) * m);
  for (int i = 0; i < m; i++){
    matrix[i] = malloc(sizeof(int) * n);
}
  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      matrix[i][j] = 0;
    }
  }

  return matrix;
}
void typewriter_effect(char message[])
{
    int length = strlen(message);

    for (int i = 0; i < length; i++)
    {
        printf("%c", message[i]);
        fflush(stdout);
        usleep(50000); //50 milliseconds pause
    }
}
static void main(){
    printf("Welcome to the Sudoku Program");
    return 0;
}