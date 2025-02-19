#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rankSum = 0;
    int data;
    if(rank!=0){
        data = rank;
        MPI_Send(&data,1,MPI_INT,0,0,MPI_COMM_WORLD);
        MPI_Recv(&rankSum,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("ranksum %d is received by process %d from process 0 \n",rankSum,rank);
    }else{
        data = rank;
        rankSum = data;
        for(int i = 1;i<size;i++){
            MPI_Recv(&data,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            rankSum += data;
        }
        printf("rank sum is %d\n",rankSum);
        for(int i = 1;i<size;i++){
            MPI_Send(&rankSum,1,MPI_INT,i,0,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}