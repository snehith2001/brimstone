#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;
    int arr[N];

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        for(int i =0;i<N;i++){
            arr[i] =i+1;
        }
        for(int i=1;i<size;i++){
            MPI_Send(arr, N, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }else{
            MPI_Recv(arr, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(int i = N - 5;i<N;i++){
            printf("%d ",arr[i] );
        }
        printf("\n");
    }


    MPI_Finalize();

    return 0;
}