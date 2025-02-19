#include<stdio.h>
#include<mpi.h>
#define N 100

int main(){
    int rank, size;
    int arr[N];
    MPI_Init(NULL, NULL);   
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int chunksize = N / size;
    int start = rank  * chunksize;
    int end = start + chunksize;
    if(rank == size -1){
        end = N;
    }
    for(int i = start; i < end; i++){
        arr[i] = i + 1;
    }

    for(int i =start;i<end;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    MPI_Finalize();

}