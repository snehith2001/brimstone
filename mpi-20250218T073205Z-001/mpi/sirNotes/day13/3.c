#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n= 2;
    int *localArr = malloc(sizeof(int)*n);
    int *finalArr = NULL;
    for(int i=0;i<n;i++){
        localArr[i] = rank; // or 1
    }
    if(rank == 0){
        finalArr = malloc(sizeof(int)*n*size);
    }
    if(rank!=0){
        MPI_Send(localArr,n,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{
        for(int i=0;i<n;i++){
            finalArr[i] = localArr[i];
        }
        for(int i = 1;i<size;i++){
            MPI_Recv(&finalArr[i * n], n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        for(int i = 0;i<n*size;i++){
            printf("%d ",finalArr[i]);
        }
        printf("\n");
    }
    free(localArr);
    if(rank == 0){
        free(finalArr);
    }
    MPI_Finalize();
    return 0;
}