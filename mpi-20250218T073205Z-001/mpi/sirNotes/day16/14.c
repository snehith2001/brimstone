#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 20;
    int data[n];
    MPI_Datatype indexType;

    int blocks = 4;
    int ElementsPerBlock[4] = {5,5,5,5};
    int displacements[4] = {0,5,10,15};
    MPI_Type_indexed(blocks, ElementsPerBlock, displacements,MPI_INT,&indexType);
    MPI_Type_commit(&indexType);
    if(rank == 0){
        for(int i=0;i<n;i++){
            data[i] = i + 1;
        }
        MPI_Send(data,1,indexType,1,0,MPI_COMM_WORLD);
    }else if(rank == 1){

        for(int i=0;i<n;i++){
            data[i] =0;
        }
        MPI_Recv(data,1,indexType,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        for(int i=0;i<n;i++){
           printf("%d ", data[i] );
        }
        printf("\n");
    }
    MPI_Type_free(&indexType);
    MPI_Finalize();
    return 0;
}