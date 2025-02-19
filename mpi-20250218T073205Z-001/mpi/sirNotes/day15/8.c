#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define n 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *buffer = malloc(sizeof(int)*n);

    for(int i = 0;i<n;i++){
        buffer[i] = rank;
    }
    if(rank ==0){
        MPI_Sendrecv_replace(buffer,n,MPI_INT,1,0,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process %d has ",rank);
        for(int i = n-5;i<n;i++){
            printf("%d ",buffer[i]);
        }   
        printf("\n");
    }else if(rank == 1){
        MPI_Sendrecv_replace(buffer,n,MPI_INT,0,0,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process %d has ",rank);
        for(int i = n-5;i<n;i++){
            printf("%d ",buffer[i]);
        }   
        printf("\n");

    }

    MPI_Finalize();
    return 0;
}