#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 15;

    int blocks = 3;
    int blocksize = 2;
    int stride = 5;

    MPI_Datatype vector_type;
    MPI_Type_vector(blocks, blocksize, stride, MPI_INT, &vector_type);
    MPI_Type_commit(&vector_type);

    if(rank == 0){
        int data[n];
        for(int i=0;i<n;i++){
            data[i] = i+1;
        }
        MPI_Send(data, 1, vector_type, 1, 0, MPI_COMM_WORLD);
    }else if(rank ==1){
        int data[blocks*blocksize];
        MPI_Recv(data, blocks * blocksize, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i=0;i<blocks*blocksize;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&vector_type);

    MPI_Finalize();
    return 0;
}