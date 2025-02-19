#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

typedef struct{
    int a[3];
    double b;
    char c;
}myStruct;

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    myStruct data;

    MPI_Datatype structType;

    int blocks = 3;
    int ElementsPerBlock[3] = {3, 1, 1};
    MPI_Aint displacements[3];
    MPI_Datatype typeOfBlocks[3] = {MPI_INT, MPI_DOUBLE, MPI_CHAR};


    displacements[0] = offsetof(myStruct,a);
    displacements[1] = offsetof(myStruct,b);
    displacements[2] = offsetof(myStruct,c);

    MPI_Type_create_struct(blocks, ElementsPerBlock, displacements, typeOfBlocks, &structType);
    MPI_Type_commit(&structType);

    if(rank ==0){
        data.a[0] = 11;
        data.a[1] = 22;
        data.a[2] = 33;
        data.b = 4.444;
        data.c = 'z';
        MPI_Send(&data , 1, structType, 1, 0 ,MPI_COMM_WORLD);   
    }else if(rank == 1){
        data.a[0] = 0;
        data.a[1] = 0;
        data.a[2] = 0;
        data.b = 0.0;
        data.c = '0';
        MPI_Recv(&data, 1, structType, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process 1 received [arr = %d %d %d ] b = %lf c = %c \n",data.a[0],data.a[1],data.a[2],data.b,data.c);
    }

    MPI_Type_free(&structType);

    MPI_Finalize();
    return 0;
}