#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 1000;
    int chunksize = n / size;
    int start = rank * chunksize;
    int end = start + chunksize;
    if(rank == size -1 ){
        end = n;
        chunksize += n % size;
    }
    int arr[chunksize];

    int index = 0;
    for(int i = start;i<end;i++){
        arr[index] = i+1;
        index++;
    }
    int localSum = 0;
    index=0;
    for(int i = start;i<end;i++){
        localSum += arr[index];
        index++;
    }
    if(rank!=0){
        MPI_Send(&localSum,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{
        int finalsum = localSum;
        for(int i = 1;i<size;i++){
            MPI_Recv(&localSum,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            finalsum += localSum;
        }
        printf("sum is %d\n",finalsum);
    }

    MPI_Finalize();
    return 0;
}