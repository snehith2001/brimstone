#include<stdio.h>
#include<mpi.h>
#define n 1000

int main(){
    int rank, size;
    int arr[n];
    for(int i =0;i<n;i++){
        arr[i] = i+1;
    }
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int chunksize = n/size;
    int start = rank * chunksize;
    int end  = start + chunksize;
    if(rank == size-1){
        end = n;
    }
    int localSum = 0;
    for(int i = start;i<end;i++){
        localSum += arr[i];
    }
    if(rank!=0){
        MPI_Send(&localSum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{
        int finalSum = localSum;
        int tempSum;
        for(int i = 1;i<size;i++){
            MPI_Recv(&tempSum,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            finalSum += tempSum;
        }
        printf("sum of array elements is %d \n",finalSum);
    }
    MPI_Finalize();
    return 0;
}