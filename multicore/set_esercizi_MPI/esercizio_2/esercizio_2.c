/*
1. Relying only on point-to-point MPI calls, implement a function with the same signature/arguments and
behaviour of MPI_Allreduce (call it <<MPI_Allreduce_custom>>).
2. Then, measure its runtime, and compare it with the runtime of MPI_Allreduce.
3. Check if the runtime changes when using Send/Recv compared to Isend/Irecv/Wait.
4. Think about how many bytes are you sending and how many send/recv are you executing(similar to what we
have done in class for the broadcast). Can you find a way to do it transmitting only 2*n bytes and
receiving only 2*n bytes (where n is the number of bytes in the vector to reduce), and performing at most
2*log_2(p) send and 2*log_2(p) recvs (where p is the number of processes)?
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

int size, rank = 0;
int call = 0;
int totCall = 0;

int MPI_Allreduce_custom(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm);
int main(int argc, char const *argv[])
{
  // costanti
  const int BUF_SIZE = 10;
  const int MAX_INT = 100;
  const int ARR_SIZE = 500;
  // fine costanti
  // inizializzazione
  MPI_Init(NULL,NULL);
  char array[ARR_SIZE];
  char res[ARR_SIZE];
  strcpy(array, "");
  strcpy(res, "");
  clock_t singleTime = 0;
  float totalElapsed = 0;

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // fine inizializzazione
  
  int sendbuf[BUF_SIZE];
  int recvbuf[BUF_SIZE];
  
  // inserimento di dati necessari per MPI_Allreduce_custom
  
  srand(time(NULL));
  char temp[10];
  for(int i = 0; i < BUF_SIZE; i++){
    sendbuf[i] = abs(((rand() + rank)*(rank + 1))% MAX_INT);
    sprintf(temp, "%d ", sendbuf[i]);
    strcat(array, temp);
  }
  int count = BUF_SIZE;
  MPI_Op operation = MPI_BOR;
  MPI_Datatype datatype = MPI_INT;

  
  // start MPI_Allreduce_custom
  MPI_Barrier(MPI_COMM_WORLD);
  singleTime = clock();
  MPI_Allreduce_custom(sendbuf, recvbuf, count, datatype, operation, MPI_COMM_WORLD);
  singleTime = clock() - singleTime;
  float elapsed = (float)singleTime / CLOCKS_PER_SEC;
  MPI_Barrier(MPI_COMM_WORLD);
  // end MPI_Allreduce_custom, print time
  MPI_Reduce(&elapsed, &totalElapsed, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  if(rank == 0){
    totalElapsed= totalElapsed/size;
    printf("totalTime MPI_Allreduce_custom: %.10fs\n", totalElapsed);
  }

  MPI_Barrier(MPI_COMM_WORLD);
  singleTime = clock();
  MPI_Allreduce(sendbuf, recvbuf, count, datatype, operation, MPI_COMM_WORLD);
  singleTime = clock() - singleTime;
  elapsed = (float)singleTime / CLOCKS_PER_SEC;
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Reduce(&elapsed, &totalElapsed, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Reduce(&call, &totCall, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if(rank == 0){
    totalElapsed= totalElapsed/size;
    printf("totalTime MPI_Allreduce:        %.10fs\n", totalElapsed);
    printf("total calls: %d in %d processes\n", totCall, size);
  }
  



  MPI_Finalize();
  return 0;
}
// asynchronous reduce
int MPI_Allreduce_custom(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm){
  int typesize = 0;
  MPI_Type_size(datatype, &typesize);
  if(rank != 0){
    MPI_Request recReq;
    MPI_Request senReq;
    MPI_Irecv(recvbuf, count, datatype, 0, MPI_ANY_TAG, comm, &recReq);
    for(int k = 0; k < count; k++){
      call++;
      MPI_Isend(sendbuf+k*typesize, 1, datatype, 0, k, comm, &senReq);
      MPI_Wait(&senReq, MPI_STATUS_IGNORE);
    }
    MPI_Wait(&recReq, MPI_STATUS_IGNORE);
  }else{

    MPI_Request request;
    void *res = malloc(typesize);
    void *temp = malloc(typesize);


    for (int i = 0; i < count; i++) // ciclo sull'indice del buffer
    {
      memcpy(res, sendbuf + i*typesize, typesize);
      for (int j = 1; j < size; j++) // ciclo per i recv
      {
        MPI_Irecv(temp, 1, datatype, j, i, comm, &request); // ricezione di un dato alla volta
        // operazione: temp op res => si va avanti, res = next ecc.
        if(datatype == MPI_INT){
          if(op == MPI_SUM){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int *)res + *(int *)temp;
            
          }else if(op == MPI_PROD){ 
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int*)res * *(int*)temp;
          
          }else if(op == MPI_MAX){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            if (*(int*)temp > *(int*)res)
            *(int*)res = *(int*)temp;
          
          }else if(op == MPI_MIN){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            if(*(int*)temp < *(int*)res)
            *(int*)res = *(int*)temp;

          }else if(op == MPI_BAND){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int*)res & *(int*)temp;
          }else if(op == MPI_BOR){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int*)res | *(int*)temp;
          }else if(op == MPI_BXOR){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int*)res ^ *(int*)temp;
          }else if(op == MPI_LAND){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int*)res && *(int*)temp;
          }else if(op == MPI_LOR){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            *(int*)res = *(int*)res || *(int*)temp;
          }else if(op == MPI_LXOR){
            MPI_Wait(&request, MPI_STATUS_IGNORE);
            if((*(int*)res && *(int*)temp) || (!(*(int*)res) && !(*(int*)temp)))
              *(int*)temp = 0;
            else
            *(int*)temp = 1;
          }

        
        }else if(datatype == MPI_FLOAT){
          
        }

      }
      memcpy(recvbuf + i*typesize, res, typesize);
    }
    MPI_Request reqs[size];
    for(int i = 1; i<size; i++){
      MPI_Isend(recvbuf, count, datatype, i, 0, comm, &reqs[i-1]);
      call++;
    }
  
    free(res);
    free(temp);

  }
  return 0;
}
/*
*/
// synchronous reduce
/*
int MPI_Allreduce_custom(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm){
  int typesize = 0;
  MPI_Type_size(datatype, &typesize);
  if(rank != 0){
    for(int k = 0; k < count; k++){
      MPI_Send(sendbuf+k*typesize, 1, datatype, 0, k, comm);
    }
    MPI_Recv(recvbuf, count, datatype, 0, MPI_ANY_TAG, comm, MPI_STATUS_IGNORE);
  }else{

    void *res = malloc(typesize);
    void *temp = malloc(typesize);


    for (int i = 0; i < count; i++) // ciclo sull'indice del buffer
    {
      memcpy(res, sendbuf + i*typesize, typesize);
      for (int j = 1; j < size; j++) // ciclo per i recv
      {
        MPI_Recv(temp, 1, datatype, j, i, comm, MPI_STATUS_IGNORE); // ricezione di un dato alla volta
        // operazione: temp op res => si va avanti, res = next ecc.
        if(datatype == MPI_INT){
          if(op == MPI_SUM){
            *(int*)res = *(int *)res + *(int *)temp;
            
          }else if(op == MPI_PROD){ 
            *(int*)res = *(int*)res * *(int*)temp;
          
          }else if(op == MPI_MAX){
            if (*(int*)temp > *(int*)res)
            *(int*)res = *(int*)temp;
          
          }else if(op == MPI_MIN){
            if(*(int*)temp < *(int*)res)
            *(int*)res = *(int*)temp;

          }else if(op == MPI_BAND){
            *(int*)res = *(int*)res & *(int*)temp;
          }else if(op == MPI_BOR){
            *(int*)res = *(int*)res | *(int*)temp;
          }else if(op == MPI_BXOR){
            *(int*)res = *(int*)res ^ *(int*)temp;
          }else if(op == MPI_LAND){
            *(int*)res = *(int*)res && *(int*)temp;
          }else if(op == MPI_LOR){
            *(int*)res = *(int*)res || *(int*)temp;
          }else if(op == MPI_LXOR){
            if((*(int*)res && *(int*)temp) || (!(*(int*)res) && !(*(int*)temp)))
              *(int*)temp = 0;
            else
            *(int*)temp = 1;
          }

        
        }else if(datatype == MPI_FLOAT){
          
        }

      }
      memcpy(recvbuf + i*typesize, res, typesize);
    }
    for(int i = 1; i<size; i++){
      MPI_Send(recvbuf, count, datatype, i, 0, comm);
    }

    free(res);
    free(temp);

  }
  return 0;
}
*/