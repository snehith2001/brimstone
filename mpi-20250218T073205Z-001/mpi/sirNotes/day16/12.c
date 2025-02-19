#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 8;
    int arr[n][n];

    MPI_Datatype vectorType;
    MPI_Type_vector(8,1,8,MPI_INT,&vectorType);
    MPI_Type_commit(&vectorType);

    if(rank ==0){
         for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                arr[i][j] = i + 1;
            }
        }
        MPI_Send(&arr[0][2],1,vectorType,1,0,MPI_COMM_WORLD);
    }else if(rank == 1){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                arr[i][j] = 0;
            }
        }
        MPI_Recv(&arr[0][2],1,vectorType,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process 1 received \n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%d ",arr[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Type_free(&vectorType);

    MPI_Finalize();
    return 0;
}