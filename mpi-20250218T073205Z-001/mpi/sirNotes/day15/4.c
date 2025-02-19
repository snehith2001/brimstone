#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data;

    if(rank == 0){
        data = 444;
        MPI_Sendrecv(&data, 1, MPI_INT, 1, 0, &data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d received the data %d \n",rank,data);
    }else if(rank == 1){
        data = 666;
        MPI_Sendrecv(&data, 1, MPI_INT, 0, 0, &data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d received the data %d \n",rank,data);
    }

    MPI_Finalize();
    return 0;
}