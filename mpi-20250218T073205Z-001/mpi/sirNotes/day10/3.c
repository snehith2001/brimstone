#include<stdio.h>
#include<mpi.h>

int main(){
    int rank, size, myval;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        myval = 66;
        MPI_Send(&myval, 1, MPI_INT,1,0,MPI_COMM_WORLD);
        printf("Process %d sent the data %d \n", rank, myval);
    }else if(rank == 1){
        MPI_Recv(&myval, 1, MPI_INT,0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received the data %d \n", rank, myval);

    }else{
        printf("I have nothing to do \n");
    }

    MPI_Finalize();

    return 0;
}