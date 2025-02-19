#include"stdio.h"
#include"mpi.h"

int main(int argc, char **argv)
{
	int rank, size;
	int myval;

	MPI_Init(&argc,&argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(size < 2){
        fprintf(stderr, "world size must be greater than 1 for this program \n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    if(rank == 0){
        myval = -999;
        MPI_Ssend(&myval, 1, MPI_INT, 1, 0 , MPI_COMM_WORLD);
        printf("process %d sent the data %d to process 1 \n",rank,myval);
    }else if(rank == 1){
        MPI_Recv(&myval, 1, MPI_INT, 0, 0 , MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d received the data %d from process 0\n",rank ,myval);
    }

	MPI_Finalize();
 return 0;   
}