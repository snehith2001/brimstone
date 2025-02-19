#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[20];

    int blockLength[3] = {3,4,5};
    int displacements[3] = {0,7,14};

    MPI_Datatype indexType;
    MPI_Type_indexed(3, blockLength, displacements, MPI_INT, &indexType);
    MPI_Type_commit(&indexType);

    if(rank == 0){
        for(int i=0;i<20;i++){
            data[i] = i+1;
        }
        MPI_Send(data, 1, indexType, 1,0,MPI_COMM_WORLD);
    }else if(rank ==1){
        for (int i = 0; i < 20; i++) {
            data[i] = 0;
        }
        MPI_Recv(data, 1, indexType, 0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int i=0;i<20;i++){
            printf("%d ",data[i]);
        }
        // int recvData[12];
        // MPI_Recv(recvData,12,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        // for(int i=0;i<12;i++){
        //     printf("%d ",recvData[i]);
        // }
        printf("\n");
    }

    MPI_Type_free(&indexType);

    MPI_Finalize();
    return 0;
}