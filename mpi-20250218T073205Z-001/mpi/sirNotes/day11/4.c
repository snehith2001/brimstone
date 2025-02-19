#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int *arr;
    int chunksize = N / size;
    int *subArr = malloc(sizeof(int) *  chunksize);

    if(rank == 0){
        arr = malloc(sizeof(int) * N);
        for(int i = 0; i<N;i++){
            arr[i] = i+1;
        }
        for(int i=1;i<size;i++){
            MPI_Send(arr + i*chunksize,chunksize,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        for(int i=0;i<chunksize;i++){
            subArr[i] = arr[i];
        }
    }else{
        MPI_Recv(subArr,chunksize,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    int localSum = 0;
    for(int i = 0;i<chunksize;i++){
        localSum += subArr[i];
    }
    if(rank!=0){
        MPI_Send(&localSum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{
        int finalSum = 0;
        finalSum += localSum;
        int tempSum;
        for(int i=1;i<size;i++){
            MPI_Recv(&tempSum,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            finalSum += tempSum;
        }
        printf("sum of array elements is %d \n",finalSum);
        free(arr);
    }

    free(subArr);
    MPI_Finalize();
    return 0;
}