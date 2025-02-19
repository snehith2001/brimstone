#include<stdio.h>
#include<mpi.h>
#define N 100

int main(){
    int rank, size;
    int arr[N];

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank == 0){
        for(int i = 0;i<N;i++){
            arr[i] = i+1;
        }
        MPI_Send(arr, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("process %d sent the array \n",rank);
    }else if(rank == 1){
        MPI_Recv(arr, N, MPI_INT, 0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  
        printf("process %d received the array \n",rank);
        for(int i=0;i<N;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");
    }else{
        printf("i have nothing to do\n");
    }

    MPI_Finalize();
    return 0;
}