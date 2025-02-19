#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data1, data2;
    if(rank == 0){
        data1 = 777;
        MPI_Sendrecv(&data1,1,MPI_INT,1,0,&data2,1,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process %d sent %d and received %d \n",rank,data1,data2);
    }else if(rank ==1){
        data2 = 333;
        MPI_Sendrecv(&data2,1,MPI_INT,0,0,&data1,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process %d sent %d and received %d \n",rank,data2,data1);
    }

    MPI_Finalize();
    return 0;
}