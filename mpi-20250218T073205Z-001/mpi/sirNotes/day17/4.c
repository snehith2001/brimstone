#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank,size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0){
        int arr[5] = {2,52,225,252,5};
        MPI_Send(arr,5,MPI_INT,1,0,MPI_COMM_WORLD);
    }else if(rank ==1){
        MPI_Status status;
        MPI_Probe(0,0,MPI_COMM_WORLD,&status);
        int bufferSize;
        MPI_Get_count(&status,MPI_INT,&bufferSize);
        int *buffer = malloc(bufferSize);
        MPI_Recv(buffer,bufferSize,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int i =0;i<bufferSize;i++){
            printf("%d ",buffer[i]);
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}