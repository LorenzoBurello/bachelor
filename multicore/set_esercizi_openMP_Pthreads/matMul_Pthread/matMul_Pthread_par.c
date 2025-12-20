/*
solve exercise_1 using Pthreads instead of MPI

this will be my first attempt with Pthreads. I will probably
over-explain simple concepts to understand them better
*/


#include <pthread.h> // must be linked by the compiler "−lpthread"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
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

  return 0;
}
