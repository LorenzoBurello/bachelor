    /*
    **  PROGRAM: Matrix Multiply
    **
    **  PURPOSE: This is a simple matrix multiply program. 
    **           It will compute the product
    **
    **                C  = A * B
    **
    **           A and B are set to constant matrices so we
    **           can make a quick test of the multiplication.
    **
    **  HISTORY: Written by Tim Mattson, Nov 1999.
    */
    #include <malloc.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <mpi.h>
    #include <math.h>

    #define AVAL 3.0
    #define BVAL 5.0
    #define TOL  0.001

    int main(int argc, char **argv)
    {
        int Ndim, Pdim, Mdim;   /* A[N][P], B[P][M], C[N][M] */
        int i,j,k;
        double *A, *B, *C, cval, err, errsq;
        double dN, mflops;
        double start_time, run_time;
        int rank, size;

        if (argc < 2) {
            printf("Usage: %s <matrix_order>\n", argv[0]);
            return -1;
        }

        int order = atoi(argv[1]);
        Ndim = order;
        Pdim = order;
        Mdim = order;

        /* Initialize matrices */

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        B = (double *)malloc(Pdim*Mdim*sizeof(double));
        if (rank == 0) {
            A = (double *)malloc(Ndim*Pdim*sizeof(double));
            C = (double *)malloc(Ndim*Mdim*sizeof(double));

            for (i=0; i<Ndim; i++)
                for (j=0; j<Pdim; j++)
                    *(A+(i*Ndim+j)) = AVAL;

            for (i=0; i<Pdim; i++)
                for (j=0; j<Mdim; j++)
                    *(B+(i*Pdim+j)) = BVAL;

            for (i=0; i<Ndim; i++)
                for (j=0; j<Mdim; j++)
                    *(C+(i*Ndim+j)) = 0.0;
        }

        start_time = MPI_Wtime();
        /* =========================== AREA OF INTEREST ============================ */
        if(rank != 0){
            A = (double *)malloc(Ndim*Pdim*sizeof(double));
        }
        MPI_Bcast(A, Ndim*Pdim, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(B, Pdim*Mdim, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        /* Do the matrix product */
        int N = Ndim*Mdim;
        int chunk = (N + size - 1) / size;
        int s = rank * chunk;
        int start = (s < N ? s : N);
        int end = (s + chunk < N ? s + chunk : N);

        double* cells = (double*)malloc(chunk * sizeof(double));
        for(int _ = 0; _ < chunk; _++){
            cells[_] = 0;
        }

        int c = 0;
        for(int cell = start; cell < end; cell ++){
            int i = cell / Mdim;
            int j = cell % Mdim;
            for(k = 0; k < Pdim ; k++){
                cells[c] += *(A+(i*Ndim+k)) * *(B+(k*Pdim+j));
            }
            c++;
        }

        double* Ctemp;
        if (rank == 0){
            Ctemp = (double*) malloc(chunk*size*sizeof(double));
            MPI_Gather(cells, chunk, MPI_DOUBLE, Ctemp, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            for(i = 0; i < N; i++){
                C[i] = Ctemp[i];
            }
            free(Ctemp);
        }else{
            free(A);
            MPI_Gather(cells, chunk, MPI_DOUBLE, Ctemp, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        }
        free(cells);
        

        /* ========================= END AREA OF INTEREST ========================== */
        run_time = MPI_Wtime() - start_time;
    
        if (rank == 0) {
            double max_time;
            MPI_Reduce(&run_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

            printf("Order %d multiplication in %f seconds\n", order, run_time);

            dN = (double)order;
            mflops = 2.0 * dN * dN * dN / (1.0e6 * run_time);
            printf("Order %d multiplication at %f mflops\n", order, mflops);
            // Check the result
            cval = Pdim * AVAL * BVAL;
            errsq = 0.0;
            for (i = 0; i < Ndim; i++)
                for (j = 0; j < Mdim; j++) {
                    err = C[i * Mdim + j] - cval;
                    errsq += err * err;
                }

            if (errsq > TOL)
                printf("Errors in multiplication: %f\n", errsq);
            else
                printf("Hey, it worked!\n");

            free(A);
            free(C);
        } else {
            MPI_Reduce(&run_time, NULL, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        }

        free(B);

        MPI_Finalize();
    }