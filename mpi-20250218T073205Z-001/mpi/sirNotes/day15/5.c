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
        data = 999;
        MPI_Sendrecv_replace(&data,1,MPI_INT,1,0,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process 0 sent and received the number %d \n",data);
    }else if(rank == 1){
        data = 111;
        MPI_Sendrecv_replace(&data,1,MPI_INT,0,0,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process 1 sent and received the number %d \n",data);
    }

    MPI_Finalize();
    return 0;
}