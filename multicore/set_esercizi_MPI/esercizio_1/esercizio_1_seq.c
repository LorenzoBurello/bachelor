#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
int MAX_NUM = 4;

int ** allocateIntMatrix(int x, int y);
void freeIntMatrix(int** M, int y);

int main(int argc, char const *argv[])
{
  if (argc < 4){
      printf("error: input must be 3 integers\n");
    }

  // input reading (assuming correct input)
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int p = atoi(argv[3]);

  // matrices allocation and initialization
  srand(time(NULL));
  int** A = (int**) malloc(sizeof(int*) * m);
  int** B = (int**) malloc(sizeof(int*) * n);

  for(int i = 0; i < m; i++){
    A[i] = (int*) malloc(sizeof(int) * n);
    for(int j = 0; j < n; j++){
      A[i][j] = rand() % MAX_NUM;
    }
  }

  for(int i = 0; i < n; i++){
    B[i] = (int*) malloc(sizeof(int) * p);
    for(int j = 0; j < p; j++){
      B[i][j] = rand() % MAX_NUM;
    }
  }

  #ifdef DEBUG
    
  printf("A:\n");
  for(int row = 0; row < m; row++){
    for(int column = 0; column < n; column++){
      printf( "%d ", A[row][column]);
    }
    printf("\n");
  }
  
  printf("B:\n");
  for(int row = 0; row < n; row++){
    for(int column = 0; column < p; column++){
      printf( "%d ", B[row][column]);
    }
    printf("\n");
  }
  
  #endif
  // allocation and calculation of C matrix (product)
  int** C = allocateIntMatrix(m, p);

  for(int i = 0; i < m; i++){
    for(int j = 0; j < p; j++){
      int sum = 0;
      for(int k = 0; k < n; k++){
        sum += A[i][k] * B[k][j];
      }
      C[i][j] = sum;
    }
  }

  #ifdef DEBUG
  printf("C:\n");
  for(int row = 0; row < m; row++){
    for(int column = 0; column < p; column++){
      printf( "%d ", C[row][column]);
    }
    printf("\n");
  }
  #endif

  freeIntMatrix(A, m);
  freeIntMatrix(B, n);
  freeIntMatrix(C, p);
  return 0;
}

int ** allocateIntMatrix(int rows, int columns){
  void **M = malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++){
    M[i] = malloc(sizeof(int) * columns);
  }
  return (int**)M;
}

void freeIntMatrix(int** M, int y){

  for (int i = 0; i < y; i++){
    free(M[i]);
  }
  free(M);
  return;
}