#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 3;
    int arr[n][n];
    if(rank ==0){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                arr[i][j] = rank + 1;
            }
        }
        MPI_Send(arr,n*n,MPI_INT,1,0,MPI_COMM_WORLD);
    }else if(rank == 1){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                arr[i][j] = 0;
            }
        }
        MPI_Recv(arr,n*n,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process 1 received \n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%d ",arr[i][j]);
            }
            printf("\n");
        }
    }


    MPI_Finalize();
    return 0;
}