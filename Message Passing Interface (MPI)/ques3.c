#include "mpi.h"
#include <stdio.h>
#include <string.h>
 
int main(int argc, char *argv[])  {
   int numtasks, rank, dest, source, rc, count,len; 
   char inmsg[30],outmsg0[]="hello world", outmsg1[]="hello world",
      outmsg2[]="hello world",outmsg3[]=" hello world";
   int Tag1=6,Tag2=10;  /*Just Random int s. There is a max size consideration.*/
   char name[MPI_MAX_PROCESSOR_NAME];
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Get_processor_name(name, &len);
   if (rank >= 1) {     
       dest = 0;
       source = 0;
       MPI_Send(&outmsg0,strlen(outmsg0), MPI_CHAR, dest, Tag1, MPI_COMM_WORLD);
       MPI_Send(&outmsg2,strlen(outmsg2), MPI_CHAR, dest, Tag2, MPI_COMM_WORLD);
       MPI_Send(&outmsg1,strlen(outmsg1), MPI_CHAR, dest, Tag1, MPI_COMM_WORLD);
       MPI_Send(&outmsg3,strlen(outmsg3), MPI_CHAR, dest, Tag2, MPI_COMM_WORLD);
 
   } else if (rank == 0) {
       dest = 1;
       source = 1;
       memset(inmsg, 0, 30);
       MPI_Recv(&inmsg,30, MPI_CHAR, source, Tag2, MPI_COMM_WORLD,  MPI_STATUS_IGNORE);
       printf("received this  message:\n   %s\n",inmsg);
      
   }
   MPI_Finalize();
}
