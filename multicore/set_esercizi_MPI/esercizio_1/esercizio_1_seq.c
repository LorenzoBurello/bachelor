#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
int MAX_NUM = 4;

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
  int* A = (int*) malloc(sizeof(int) * m * n);
  int* B = (int*) malloc(sizeof(int) * n * p);

  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      A[i * n + j] = rand() % MAX_NUM;
    }
  }

  for(int i = 0; i < n; i++){
    for(int j = 0; j < p; j++){
      B[i * p + j] = rand() % MAX_NUM;
    }
  }

  #ifdef DEBUG
    
    printf("A:\n");
    for(int i = 0; i < m * n; i++){
      int row = i / n;
      int column = i % n;
      if (column == 0 && i != 0)
        printf("\n");
      printf( "%d ", A[i]);
    }
    printf("\n");
    
    printf("B:\n");
    for(int i = 0; i < n * p; i++){
      int row = i / p;
      int column = i % p;
      if (column == 0 && i != 0)
        printf("\n");
      printf( "%d ", B[i]);
    }
    printf("\n"); 
  
  #endif
  // allocation and calculation of C matrix (product)
  int* C = (int*)malloc(sizeof(int) * m * p);

  int* Bt = (int*)malloc(sizeof(int) * p * n);
  for(int i = 0; i < n; i++){
    for(int j = 0; j < p; j++){
      Bt[j*n + i]  = B[i*p + j];
    }
  }

  for(int i = 0; i < m; i++){
    for(int j = 0; j < p; j++){
      int sum = 0;
      for(int k = 0; k < n; k++){
        sum += A[i*n + k] * Bt[j*n + k];
      }
      C[i*p + j] = sum;
    }
  }

  #ifdef DEBUG
  printf("C:\n");
  for(int row = 0; row < m; row++){
    for(int column = 0; column < p; column++){
      printf( "%d ", C_final[row*p + column]);
    }
    printf("\n");
  }
  #endif

  free(A);
  free(B);
  free(Bt);
  free(C);
  return 0;
}