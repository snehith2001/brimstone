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

    MPI_Datatype contiguousType;
    MPI_Type_contiguous(3,MPI_INT,&contiguousType);
    MPI_Type_commit(&contiguousType);

    if(rank ==0){
        int temp = 1;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                arr[i][j] = temp;
                temp++;
            }
        }
        MPI_Send(arr,n,contiguousType,1,0,MPI_COMM_WORLD);
    }else if(rank == 1){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                arr[i][j] = 0;
            }
        }
        MPI_Recv(arr,n,contiguousType,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process 1 received \n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%d ",arr[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Type_free(&contiguousType);

    MPI_Finalize();
    return 0;
}