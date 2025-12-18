/*implement matrix-matrix multiplication in MPI. Let's assume that you run this on p processes (from 0 to p-1). The
two input matrices are generated randomly by rank p-1. The order of matrices must be read from argv (which
means you can use an array but you need to allocate dynamic memory). After the resulting matrix has been
computed, it must be stored into rank 0 memory.

- check if the resulting matrix is correct (e.g. by doing the same computation sequentially)
- try to think about possible different ways of implementing it
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  int rank;
  int size;
  int* A;
  int* B;
  int* C;
  int* C_final;
  int Alen;
  int Blen;
  int m;
  int n;
  int p;
  int start;
  int end;
  int cellPerProcess;
  int* recvbuf = NULL;
  int MAX_NUM = 4;

  MPI_Init(NULL, NULL); // MPI initialization

  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // obtaining core values
  MPI_Comm_size(MPI_COMM_WORLD, &size); 

  if (rank == size-1){ // process p-1 creates the matrices
    
    // assuming correct input
    m = atoi(argv[1]);
    n = atoi(argv[2]);
    p = atoi(argv[3]);
    
    cellPerProcess = (m*p + size - 1) / size;

    srand(time(NULL));
    // simplify 2D matrix in 1D array
    A = (int*) malloc(sizeof(int) * m * n);
    B = (int*) malloc(sizeof(int) * n * p);

    for(int i = 0; i < m * n; i++){
      A[i] = rand() % MAX_NUM;
    }

    for(int i = 0; i < n * p; i++){
      B[i] = rand() % MAX_NUM;
    }

    // TODO (maybe):
    // condense broadcasts in one
    MPI_Bcast(&m, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&p, 1, MPI_INT, size-1, MPI_COMM_WORLD);

    // debug only
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

    // invio della matrice A
    MPI_Bcast(A, n*m, MPI_INT, size-1, MPI_COMM_WORLD);

    // invio della matrice B
    MPI_Bcast(B, m*p, MPI_INT, size-1, MPI_COMM_WORLD);
  }
  else{ // processes other than p-1

    // TODO (maybe):
    // condense broadcasts in one
    MPI_Bcast(&m, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&p, 1, MPI_INT, size-1, MPI_COMM_WORLD);

    cellPerProcess = (m*p + size - 1) / size;
    A = (int*) malloc(sizeof(int) * m * n);
    B = (int*) malloc(sizeof(int) * n * p);

    // TODO:
    // maybe condense?
    
    // ricezione della matrice A
    MPI_Bcast(A, n*m, MPI_INT, size-1, MPI_COMM_WORLD);

    // ricezione della matrice B
    MPI_Bcast(B, m*p, MPI_INT, size-1, MPI_COMM_WORLD);

  }

  start = rank*cellPerProcess;
  end = ((rank+1)*cellPerProcess)-1;


  //printf("process %d cells: (%d, %d)\n", rank, start, end);

  // allocate space to save products
  C = (int*)malloc(sizeof(int) * cellPerProcess);

  // init CArray:
  for (int i = 0; i < cellPerProcess; i++){
    C[i] = -1;
  }
  // start calculating matrix multiplication
  for(int cell = start; cell <= end && cell < m*p; cell++){
    int x = cell % p;
    int y = cell / p;
    int result = 0;
    for(int i = 0; i < n; i++){
      result += A[y * n + i]*B[i * m + x];
    }
    C[cell - start] = result;
   //printf("calculated cell %d: %d\n", cell, result);
  }
  
  // matrix calculated, sending to process 0
  if(rank == 0){
    C_final = malloc(sizeof(int) * size * cellPerProcess);
    recvbuf = C_final;
    MPI_Gather(C, cellPerProcess, MPI_INT, recvbuf, cellPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
    // debug
    #ifdef DEBUG
    
    // print matrix to check:
    printf("C:\n");
    for(int row = 0; row < m; row++){
      for(int column = 0; column < p; column++){
        printf( "%d ", C_final[row*p + column]);
      }
      printf("\n");
    }
     
    #endif
    
    free(C_final);
  }else{
    MPI_Gather(C, cellPerProcess, MPI_INT, recvbuf, cellPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
  }

  free(A);
  free(B);
  free(C);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}