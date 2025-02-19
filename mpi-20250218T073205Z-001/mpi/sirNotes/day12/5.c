#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rankSum=0;
    if(rank!=0){
        MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }else{
        rankSum = rank;
        int temp;
        for(int i = 1;i<size;i++){
            MPI_Recv(&temp,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            rankSum += temp;
        }
    }
    MPI_Bcast(&rankSum,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("sum of all ranks is %d, this is from process %d \n",rankSum, rank);

    MPI_Finalize();
    return 0;
}