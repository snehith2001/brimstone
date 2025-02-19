
#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int data;
    if(rank == 0){
        data = 100;
    }
    MPI_Bcast(&data,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("data is %d, this is from process %d \n",data, rank);
    MPI_Finalize();
    return 0;
}