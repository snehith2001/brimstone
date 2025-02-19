#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 20

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    const int count = 5;
    int data[N];
    MPI_Datatype contiguous_type;

    MPI_Type_contiguous(count, MPI_INT, &contiguous_type);
    MPI_Type_commit(&contiguous_type);

    if(rank == 0){
        for(int i =0;i<N;i++){
            data[i] = i + 1;
        }
        MPI_Send(data, 4, contiguous_type, 1, 0, MPI_COMM_WORLD);
        printf("process %d sent data ",rank);
        for(int i =0;i<N;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
    }else if(rank == 1){
        MPI_Recv(data, 4, contiguous_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d received data ",rank);
        for(int i =0;i<N;i++){
            printf("%d ",data[i]);
        }
        printf("\n");
    }
    MPI_Type_free(&contiguous_type);

    MPI_Finalize();
    return 0;
}