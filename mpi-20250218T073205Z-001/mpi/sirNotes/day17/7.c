#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int color = rank % 2;

    MPI_Comm newComm;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank , &newComm);

    int newRank, newSize;
    MPI_Comm_size(newComm, &newSize);
    MPI_Comm_rank(newComm, &newRank);

    printf("world rank is %d new rank is %d new size %d \n",rank, newRank, newSize);

    int send_data = newRank;
    int recv_data;
    MPI_Allreduce(&send_data, &recv_data, 1, MPI_INT, MPI_SUM, newComm);
    printf("World Rank: %d, New Comm Sum: %d\n", rank, recv_data);

    MPI_Comm_free(&newComm);
    MPI_Finalize();
    return 0;
}