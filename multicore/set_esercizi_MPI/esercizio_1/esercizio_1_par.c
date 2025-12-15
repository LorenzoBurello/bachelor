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

int ** allocateIntMatrix(int x, int y);
void freeIntMatrix(int** M, int y);
int main(int argc, char const *argv[])
{
  int rank;
  int size;
  int** A;
  int** B;
  int* CArray = NULL;
  int* CArrMatrix;
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
  MPI_Init(NULL, NULL);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);


  if (rank == size-1){
    if (argc < 4){
     //printf("error: input must be 3 integers\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }

    m = atoi(argv[1]);
    n = atoi(argv[2]);
    p = atoi(argv[3]);
    
    cellPerProcess = (m*p + size - 1) / size;
    srand(time(NULL));
    A = (int**) malloc(sizeof(int*) * m);
    B = (int**) malloc(sizeof(int*) * n);

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
    // TODO:
    // condense broadcasts in one
    MPI_Bcast(&m, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&p, 1, MPI_INT, size-1, MPI_COMM_WORLD);

    // debug only
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

    // TODO:
    // maybe condense?

    // invio della matrice A
    for (int i = 0; i < m; i++){ // ciclo sulle righe di A, ogni riga viene inviata singolarmente
      MPI_Bcast(A[i], n, MPI_INT, size-1, MPI_COMM_WORLD);
    }

    // invio della matrice B
    for (int i = 0; i < n; i++){ // ciclo sulle righe di B, ogni riga viene ricevuta singolarmente
      MPI_Bcast(B[i], p, MPI_INT, size-1, MPI_COMM_WORLD);
    }
  }
  else{

    // TODO:
    // condense broadcasts in one
    MPI_Bcast(&m, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    MPI_Bcast(&p, 1, MPI_INT, size-1, MPI_COMM_WORLD);
    cellPerProcess = (m*p + size - 1) / size;
    A = allocateIntMatrix(m, n);
    B = allocateIntMatrix(n, p);

    // TODO:
    // maybe condense?
    
    // ricezione della matrice A
    for (int i = 0; i < m; i++){ // ciclo sulle righe di A, ogni riga viene ricevuta singolarmente
      MPI_Bcast(A[i], n, MPI_INT, size-1, MPI_COMM_WORLD);
    }

    // ricezione della matrice B
    for (int i = 0; i < n; i++){ // ciclo sulle righe di B, ogni riga viene ricevuta singolarmente
      MPI_Bcast(B[i], p, MPI_INT, size-1, MPI_COMM_WORLD);
    }

  }

  start = rank*cellPerProcess;
  end = ((rank+1)*cellPerProcess)-1;


  //printf("process %d cells: (%d, %d)\n", rank, start, end);

  // allocate space to save products
  CArray = (int*)malloc(sizeof(int) * cellPerProcess);

  // init CArray:
  for (int i = 0; i < cellPerProcess; i++){
    CArray[i] = -1;
  }
  // start calculating matrix multiplication
  for(int cell = start; cell <= end && cell < m*p; cell++){
    int x = cell % p;
    int y = cell / p;
    int result = 0;
    for(int i = 0; i < n; i++){
      result += A[y][i]*B[i][x];
    }
    CArray[cell - start] = result;
   //printf("calculated cell %d: %d\n", cell, result);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  

  // matrix calculated, sending to process 0
  if(rank == 0){
    CArrMatrix = malloc(sizeof(int) * size * cellPerProcess);
    recvbuf = CArrMatrix;
    MPI_Gather(CArray, cellPerProcess, MPI_INT, recvbuf, cellPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
    // debug
    #ifdef DEBUG
    
    // print matrix to check:
    printf("C:\n");
    for(int row = 0; row < m; row++){
      for(int column = 0; column < p; column++){
        printf( "%d ", CArrMatrix[row*p + column]);
      }
      printf("\n");
    }
     
    #endif
    
    free(CArrMatrix);
  }else{
    MPI_Gather(CArray, cellPerProcess, MPI_INT, recvbuf, cellPerProcess, MPI_INT, 0, MPI_COMM_WORLD);
  }

  free(CArray);
  freeIntMatrix(A, m);
  freeIntMatrix(B, n);
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

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