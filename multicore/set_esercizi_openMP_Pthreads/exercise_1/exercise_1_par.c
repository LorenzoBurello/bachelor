/*
solve exercise_1 using Pthreads instead of MPI

this will be my first attempt with Pthreads. I will probably
over-explain simple concepts to understand them better

p.s.  this seems like an easy scenario, there are
      no race conditions and it's kinda similar to 
      the MPI variation, except for the fact that with
      Pthreads I don't need to pass values bc of the
      shared memory
*/


#include <pthread.h> // must be linked by the compiler "−lpthread"
#include <stdio.h>
#include <stdlib.h>

void* thread_routine(void* v_rank);

const int MAX_NUM = 4;

int* A;
int* B;
int* C;
int m;
int n;
int p;
int Clen;
int thread_count;

int main(int argc, char const *argv[])
{
  pthread_t* t_handlers;
  int thread;
  /*
  a thread is launched with function 
  pthread_create(
    pthread_t* thread_p           // out
    const pthread_attr_t* attr_p  // in
    void* (start_routine)(void*)  // in
    void* arg_p                   // in
  )
    thread_p -> thread handler
    attr_p -> won't be used in this course
    start_routine -> function pointer, will be the routine executed by the thread
    arg_p -> the argument passed in start_routine()
  */

  // first of all read inputs (assume correct inputs):
  thread_count = atoi(argv[1]);
  m = atoi(argv[2]);
  n = atoi(argv[3]);
  p = atoi(argv[4]);
  Clen = m*p;

  // init matrices (same as MPI variant) (I actually copied and paste it :p)
  A = (int*) malloc(sizeof(int) * m * n);
  B = (int*) malloc(sizeof(int) * n * p);

  for(int i = 0; i < m * n; i++){
    A[i] = rand() % MAX_NUM;
  }

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

  /*
  printf("Bt:\n");
  for(int i = 0; i < n * p; i++){
    int row = i / n;
    int column = i % n;
    if (column == 0 && i != 0)
    printf("\n");
    printf( "%d ", Bt[i]);
  }
  printf("\n");
  */
  #endif
    
  for(int i = 0; i < n * p; i++){
    B[i] = rand() % MAX_NUM;
  }

  // create an array of thread handlers
  t_handlers = (pthread_t*) malloc(sizeof(pthread_t) * thread_count);
  
  // create and run all threads
  for(int thread = 0; thread < thread_count; thread++){
    pthread_create(&t_handlers[thread], NULL, thread_routine, (void*) thread);
  }

  // then wait for all threads to end:
  for(int thread = 0; thread < thread_count; thread++){
    pthread_join(t_handlers[thread], NULL);
  }

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

  // that's it! :D
  return 0;
}

void* thread_routine(void* v_rank){

  int rank = (int) v_rank;
  int cell_qty = (Clen + thread_count - 1)/thread_count;
  int calc_cell = cell_qty*rank;
  int last_cell = cell_qty*(rank+1) - 1;

  // check if last process goes out of range (it will probably happen)
  if(last_cell >= Clen){
    last_cell = Clen-1;
  }


  // calculate C
  while(calc_cell <= last_cell){
    int result = 0;
    int x = calc_cell % p;
    int y = calc_cell / p;
    for(int k = 0; k < n; k++){
      result += A[y*n + k]*B[k*p + x];
    }
    C[calc_cell] = result;
    calc_cell++;
  }

  return;
}