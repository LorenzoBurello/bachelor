#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
int MAX_NUM = 4;

void create_and_rand_init_array(int* A, int len);
void print_array_matrix(int* A, int rows, int cols);
void transpose_array_matrix(int* A, int* At, int rows, int cols);
void calculate_array_matrix_product(int *A, int* B, int* C, int m, int n, int p);

int main(int argc, char const *argv[])
{

  // input reading (assuming correct input)
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  int p = atoi(argv[3]);

  // matrices allocation and initialization
  int* A = (int*) malloc(sizeof(int) * m * n);
  int* B = (int*) malloc(sizeof(int) * n * p);
  
  srand(time(NULL));
  create_and_rand_init_array(A, m*n);
  create_and_rand_init_array(B, n*p);


  #ifdef DEBUG
    
    printf("A:\n");
    print_array_matrix(A, m, n);

    printf("B:\n");
    print_array_matrix(B, n, p);
  
  #endif
  // allocation and calculation of C matrix (product)
  int* C = (int*)malloc(sizeof(int) * m * p);

  // transposition of B matrix
  int* Bt = (int*)malloc(sizeof(int) * p * n);

  transpose_array_matrix(B, Bt, n, p);

  calculate_array_matrix_product(A, B, C, m, n, p);

  #ifdef DEBUG
  printf("C:\n");
  print_array_matrix(C, m, p);
  #endif

  free(A);
  free(B);
  free(Bt);
  free(C);
  return 0;
}

void create_and_rand_init_array(int* A, int len){
  for(int i=0;i<len;i++){
    A[i] = rand()%MAX_NUM;
  }
  return;
}

void print_array_matrix(int* A, int rows, int cols){
  for(int row = 0; row < rows; row++){
    for(int column = 0; column < cols; column++){
      printf( "%d ", A[row*cols + column]);
    }
    printf("\n");
  }
}

void transpose_array_matrix(int* A, int* At, int rows, int cols){
  for(int row = 0; row < rows; row++){
    for(int col = 0; col < cols; col++){
      At[col*rows + row]  = A[row*cols + col];
    }
  }
}

void calculate_array_matrix_product(int *A, int* B, int* C, int m, int n, int p){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < p; j++){
      int sum = 0;
      for(int k = 0; k < n; k++){
        sum += A[i*n + k] * B[j*n + k];
      }
      C[i*p + j] = sum;
    }
  }
}