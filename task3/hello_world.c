#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  printf("MPI: Hello, world!\n");
  MPI_Finalize();
  return 0;
}
