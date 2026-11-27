#include "student.h"
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

static double get_rand_minus_one_one(void) {
    return 2 * (rand() / (double)RAND_MAX) - 1;
}

/* Replace this sequential baseline with an MPI implementation.
 * num_tosses is the total number of tosses across all ranks.
 * MPI is already initialized; rank 0 prints the returned estimate.
 */
double estimate_pi(int num_tosses, int rank, int size) {
    (void)rank;
    (void)size;
    int tot_tosses = num_tosses;
    int last_tosses = num_tosses - ceil(num_tosses/size)*(size-1);
    int tot_hits = 0;

    if(rank == size -1){
        num_tosses = last_tosses;
    }else{
        num_tosses =  ceil(num_tosses/size);
    }
    
    int num_hits = 0;
    for (int toss = 0; toss < num_tosses; toss++) {
        double x = get_rand_minus_one_one();
        double y = get_rand_minus_one_one();
        if (x*x + y*y <= 1) {
            num_hits++;
        }
    }

    MPI_Reduce(&num_hits, &tot_hits, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank != 0){
        return 0;
    }else{
        return 4 * tot_hits / (double)tot_tosses;
    }
}