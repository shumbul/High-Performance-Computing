#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <mpi.h>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  
  int i, rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 
  int* sendbuf;
  if(rank ==0) {
    sendbuf = (int*) malloc(sizeof(int) * size * 4);
    for(i=0; i<size * 4; i++) sendbuf[i] = i;
  }
  int recvbuf[4];
  MPI_Datatype my_own_datatype; // Declaring the user defined datatype
  MPI_Type_contiguous(4, MPI_INT, &my_own_datatype); // specifying to runtime that this datatype is contiguous
  MPI_Type_commit(&my_own_datatype); // A datatype can only be communicated once its committed (saved).
  
  int sendcnt = 4;
  int recvcnt = 1; 
  MPI_Scatter(sendbuf, sendcnt, MPI_INT, recvbuf, recvcnt, my_own_datatype, 0, MPI_COMM_WORLD);

  char msg[100];
  sprintf(msg,"Rank %d: ", rank);
  for(i=0; i<4; i++){
    sprintf(msg + strlen(msg),"%d ", recvbuf[i]);
  }
  sprintf(msg + strlen(msg),"\n");
  printf("%s",msg);
  fflush(stdout);
 
  MPI_Finalize();
  return 0;
}
