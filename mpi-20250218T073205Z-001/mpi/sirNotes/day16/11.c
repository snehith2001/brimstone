#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int n = 20;


    MPI_Datatype vectorType;
    MPI_Type_vector(3,4,6,MPI_INT,&vectorType);
    MPI_Type_commit(&vectorType);

    if(rank ==0){
        int arr[n];
        for(int i=0;i<n;i++){
                arr[i] = i+1;
        }
        MPI_Send(arr,1,vectorType,1,0,MPI_COMM_WORLD);
    }else if(rank == 1){
        int data[12];
        for(int i=0;i<12;i++){
                data[i] = 0;
        }
        MPI_Recv(data,12,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("process 1 received \n");
        for(int i=0;i<12;i++){
                printf("%d ",data[i]);
        }
            printf("\n");
    }

    MPI_Type_free(&vectorType);

    MPI_Finalize();
    return 0;
}