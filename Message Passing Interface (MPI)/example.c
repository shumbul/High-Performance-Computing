#include <stdio.h>
#include <mpi.h>
//Include user libraries
//Defines
//Global variables
int main (int argc, char *argv[]) {
//Declare int variables for Process number, number of processes and length of processor name.
int
rank, size, namelen;
//Declare char variable for name of processor
char name[100];
//Intialize MPI
MPI_Init(&argc, &argv);
//Get number of processes
MPI_Comm_size(MPI_COMM_WORLD, &size);
//Get processes number
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//Get processesor name
MPI_Get_processor_name(name, &namelen);
printf ("Hello World. Rank %d out of %d running on %s!\n", rank, size, name);
//Terminate MPI environment
MPI_Finalize();
return 0;
}
