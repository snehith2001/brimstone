#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

typedef struct{
    int a;
    double b;
    char c;
}myStruct;

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    myStruct data;
    void* buffer;
    int buffersize;
    int position ;

    if(rank == 0){
        data.a = 1025;
        data.b = 25.5252;
        data.c = 'y';

        MPI_Pack_size(1,MPI_INT,MPI_COMM_WORLD,&buffersize);
        buffersize += sizeof(double) + sizeof(char);
        buffer = malloc(buffersize);
        position = 0;

        MPI_Pack(&data.a, 1, MPI_INT, buffer, buffersize,&position, MPI_COMM_WORLD);
        MPI_Pack(&data.b, 1, MPI_DOUBLE, buffer, buffersize,&position, MPI_COMM_WORLD);
        MPI_Pack(&data.c, 1, MPI_CHAR, buffer, buffersize,&position, MPI_COMM_WORLD);

        MPI_Send(buffer, buffersize,MPI_PACKED,1,0,MPI_COMM_WORLD);
        free(buffer);
    }
    if(rank == 1){
        MPI_Status status;
        MPI_Probe(0,0,MPI_COMM_WORLD,&status);
        MPI_Get_count(&status, MPI_PACKED, &buffersize);

        buffer = malloc(buffersize);

        MPI_Recv(buffer, buffersize,MPI_PACKED,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        position = 0;
        MPI_Unpack(buffer,buffersize,&position,&data.a,1,MPI_INT,MPI_COMM_WORLD);
        MPI_Unpack(buffer,buffersize,&position,&data.b,1,MPI_DOUBLE,MPI_COMM_WORLD);
        MPI_Unpack(buffer,buffersize,&position,&data.c,1,MPI_CHAR,MPI_COMM_WORLD);
        printf("a = %d b = %lf c = %c \n",data.a,data.b,data.c);

        free(buffer);   
    }

    MPI_Finalize();
    return 0;
}