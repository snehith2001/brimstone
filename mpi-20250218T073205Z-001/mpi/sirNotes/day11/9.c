#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = 1000;
    int *arr = NULL;
    int localSum = 0;
    if(rank == 0){
        arr = malloc(sizeof(int)*n);
        for(int i = 0;i<n;i++){
            arr[i] = i+1;
        }
        
        int chunksize = n/size;
        for(int i = 1;i<size;i++){
            int start = i * chunksize;
            int end = start + chunksize;
            if(i == size-1){
                end = n; 
            }
            int sendsize = end-start;
            MPI_Send(&arr[start], sendsize, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for(int i = 0;i<chunksize;i++){
            localSum += arr[i];
        }
        int finalSum = localSum;

        for(int i=1;i<size;i++){
            MPI_Recv(&localSum,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            finalSum += localSum;
        }
        printf("finalsum is %d \n",finalSum);
        free(arr);

    }else{
        int chunksize = n/size;
        int start = rank * chunksize;
        int end = start + chunksize;
        if(rank == size-1){
            end = n;
        }
        int recvsize = end - start;
        int *recvBuff = malloc(sizeof(int)*recvsize);
        MPI_Recv(recvBuff, recvsize, MPI_INT, 0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(int i = 0;i<recvsize;i++){
            localSum += recvBuff[i];
        }

        MPI_Send(&localSum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        free(recvBuff);   
    }

    MPI_Finalize();
    return 0;
}
