#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;
    int data;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size<2){
        fprintf(stderr,"world size must be greater than 1 for this program\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if(rank == 0){
        data = 888;
        MPI_Request request;
        MPI_Isend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        printf("process %d sent the data %d to process 1\n",rank,data);
    }else if(rank == 1){
        MPI_Request request;
        MPI_Irecv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        printf("process %d received the data %d from process 0\n",rank,data);

    }

    MPI_Finalize();
    return 0;
}