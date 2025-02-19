#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define n 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    int *buffer = malloc(sizeof(int)*n);

    for(int i=0;i<n;i++){
        buffer[i] = 8+rank;
    }
    if(rank ==0){
        MPI_Send(buffer,n,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Recv(buffer,n,MPI_INT,1,0,MPI_COMM_WORLD,&status);
        printf("process %d has ",rank);
        for(int i=n-5;i<n;i++){
            printf("%d ",buffer[i]);
        }   
        printf("\n");
    }else if(rank ==1){
        int *temp = malloc(sizeof(int)*n);
        MPI_Recv(temp,n,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        MPI_Send(buffer,n,MPI_INT,0,0,MPI_COMM_WORLD);
        for(int i=0;i<n;i++){
            buffer[i] = temp[i];
        }
        printf("process %d has ",rank);
        for(int i=n-5;i<n;i++){
            printf("%d ",buffer[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}