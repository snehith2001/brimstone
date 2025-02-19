#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data;
    if(rank ==0){
        data = 888;

        int buffersize = MPI_BSEND_OVERHEAD + sizeof(int);
        void* buffer = malloc(buffersize);

        MPI_Buffer_attach(buffer,buffersize);

        MPI_Bsend(&data,1,MPI_INT,1,0,MPI_COMM_WORLD);
        printf("PROCESS %d sent data %d \n",rank,data);

        MPI_Buffer_detach(&buffer,&buffersize);

        free(buffer);        

    }else if(rank ==1){
        MPI_Recv(&data,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("PROCESS %d received data %d \n",rank,data);
    }

    MPI_Finalize();
    return 0;
}