#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data;
    if(rank !=0){
        int data = rank;
        MPI_Send(&data, 1, MPI_INT, 0,0,MPI_COMM_WORLD);
    }else if(rank == 0){
        MPI_Status status;
        MPI_Recv(&data,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        printf("process %d received data from %d \n",rank,status.MPI_SOURCE);
    }

    MPI_Finalize();
    return 0;
}