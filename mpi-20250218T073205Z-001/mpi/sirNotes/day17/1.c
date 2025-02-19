#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

typedef struct{
    char name[20];
    int prn;
    int age;
    char email[20];
    double salary;
    int marks[3];
}myStruct;

int main(){
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    myStruct data;
    MPI_Datatype structType;

    int blocks = 6;
    int elementsPerBlock[6] = {20,1,1,20,1,3};
    MPI_Aint displacements[6];
    MPI_Datatype types[6] = {MPI_CHAR, MPI_INT, MPI_INT, MPI_CHAR, MPI_DOUBLE, MPI_INT};
    displacements[0] = offsetof(myStruct, name);
    displacements[1] = offsetof(myStruct, prn);
    displacements[2] = offsetof(myStruct, age);
    displacements[3] = offsetof(myStruct, email);
    displacements[4] = offsetof(myStruct, salary);
    displacements[5] = offsetof(myStruct, marks);
    MPI_Type_create_struct(blocks, elementsPerBlock, displacements, types ,&structType);
    MPI_Type_commit(&structType);

    if(rank == 0){
        strcpy(data.name,"chamber");
        data.prn = 1025;
        data.age = 24;
        strcpy(data.email,"chamber@gmail.com");
        data.salary = 96.36225;
        data.marks[0] = 77;
        data.marks[1] = 69;
        data.marks[2] = 78;
        MPI_Send(&data,1,structType,1,0,MPI_COMM_WORLD);
    }
    if(rank ==1){
        strcpy(data.name,"");
        data.prn = 0;
        data.age = 0;
        strcpy(data.email,"");
        data.salary = 0;
        data.marks[0] = 0;
        data.marks[1] = 0;
        data.marks[2] = 0;
        MPI_Recv(&data,1,structType,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf(" name = %s prn = %d age = %d gmail = %s salary %lf ",data.name,data.prn,data.age,data.email,data.salary);
        for(int i=0;i<3;i++){
            printf("%d ",data.marks[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&structType);

    MPI_Finalize();
    return 0;
}