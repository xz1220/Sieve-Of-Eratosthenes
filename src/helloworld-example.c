#include<stdio.h>
//#include</usr/lib64/mpi/gcc/openmpi/include/mpi.h>
#include<mpi.h>

int main(int argc, char** argv){

    //Initializfe the MPI environment
    MPI_Init(NULL,NULL);

    //get the number of processes
    int world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_size);

    //get the rank of process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    //get the name of processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;

    MPI_Get_processor_name(processor_name, &name_len);
    //print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

    // Finalize the MPI environment
    MPI_Finalize();
}
