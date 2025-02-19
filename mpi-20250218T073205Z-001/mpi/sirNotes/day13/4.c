#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int data = rank;
    int *recvBuffer = NULL;
    if(rank == 0){
        recvBuffer = malloc(sizeof(int)*size);
    }
    MPI_Gather(&data,1,MPI_INT,recvBuffer,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank == 0){
        for(int i=0;i<size;i++){
            printf("%d ",recvBuffer[i]);
        }
        printf("\n");
        free(recvBuffer);
    }

    MPI_Finalize();
    return 0;
}