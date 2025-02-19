
#include<stdio.h>
#include<mpi.h>
#define N 10

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int arr[N];
    if(rank == 0){
        for(int i=0;i<N;i++){
            arr[i] = i + 1;
        }
    }
    MPI_Bcast(arr,N,MPI_INT,0,MPI_COMM_WORLD);
    for(int i=0;i<N;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    MPI_Finalize();
    return 0;
}