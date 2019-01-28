#include <mpi.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char** argv) {
  int error;
  error = MPI_Init(&argc, &argv);
  if (error != 0) {
    err(error, "MPI_Init error");
  }

  printf("MPI: Hello, world!\n");

  error = MPI_Finalize();
  if (error != 0) {
    err(error, "MPI_Finalize error");
  }
  return 0;
}
