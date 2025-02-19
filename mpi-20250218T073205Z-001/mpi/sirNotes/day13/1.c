#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 100;
    int chunksize = n/size;
    int *arr;
    int *arr2 = malloc(sizeof(int)*chunksize);

    if(rank==0){
        arr = malloc(sizeof(int)*n);
        for (int i = 0; i < n; i++)
        {
            arr[i] = i + 1;
        }
    }
    MPI_Scatter(arr, chunksize, MPI_INT, arr2, chunksize, MPI_INT,0,MPI_COMM_WORLD );
    for(int i = 0;i<chunksize;i++){
        printf("%d ",arr2[i]);
    }
    printf("\n");
    free(arr2);
    if(rank == 0) {
        free(arr);
    }
    MPI_Finalize();
    return 0;
}