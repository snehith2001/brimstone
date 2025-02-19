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
    int *arr = NULL;
    int *localArr = malloc(sizeof(int)*chunksize);
    if(rank == 0){
        arr = malloc(sizeof(int)*n);
        for(int i =0;i<n;i++){
            arr[i] = i+1;
        }
    }
    MPI_Scatter(arr, chunksize, MPI_INT, localArr, chunksize, MPI_INT, 0, MPI_COMM_WORLD);
    int localSum = 0;
    for(int i=0;i<chunksize;i++){
        localSum += localArr[i];
    }
    int *finalArr = malloc(sizeof(int)*size);

    MPI_Allgather(&localSum,1,MPI_INT,finalArr,1,MPI_INT,MPI_COMM_WORLD);
    printf("process %d ",rank);
    for(int i=0;i<size;i++){
        printf(" %d ", finalArr[i]);
    }
    printf("\n");
    if(rank == 0){
        free(arr);
    }
    free(localArr);

    MPI_Finalize();
    return 0;
}