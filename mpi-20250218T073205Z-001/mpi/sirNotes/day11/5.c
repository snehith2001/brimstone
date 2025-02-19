#include<stdio.h>
#include<mpi.h>
#define N 1000

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size<2){
        fprintf(stderr, "world size must be greater than 2 for this program \n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    int data;
    if(rank == 0){
        data = 777;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("process %d sent the data %d to process 1\n",rank,data);
        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d received the data %d from process 1\n",rank,data);
    }else if(rank == 1){
        data = 222;
        MPI_Send(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("process %d sent the data %d to process 0\n",rank,data);
        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d received the data %d from process 0\n",rank,data);
    }

    MPI_Finalize();
    return 0;
}