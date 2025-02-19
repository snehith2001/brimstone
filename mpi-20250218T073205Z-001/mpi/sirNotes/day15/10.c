#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr = malloc(sizeof(int)*N);

    if(rank == 0){
        for(int i=0;i<N;i++){
            arr[i] = i+1;
        }

        int buffersize = MPI_BSEND_OVERHEAD + sizeof(int)*N;
        void* buffer = malloc(buffersize);

        MPI_Buffer_attach(buffer,buffersize);

        MPI_Bsend(arr,N,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("process %d sent the data \n",rank);
        MPI_Buffer_detach(&buffer,&buffersize);

        free(buffer);
    }else if(rank==1){
        MPI_Recv(arr,N,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process %d received the data \n",rank);
        for(int i=N-5;i<N;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }
    free(arr);
    MPI_Finalize();
    return 0;
}