#include <mpi.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char** argv) {
  // Инициализация MPI
  MPI_Init(&argc, &argv);

  // Получение количества процессов в группе глобального коммуникатора
  int world_comm_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);

  // Получение ранга текущего процесса в группе процессов глобального коммуникатора
  int world_comm_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);

  // Получение имено процессора
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int processor_name_length;
  MPI_Get_processor_name(processor_name, &processor_name_length);

  printf("MPI: Hello from processor \"%s\" with rank %d/%d\n",
         processor_name, world_comm_rank, world_comm_size);

  // Завершение работы MPI
  MPI_Finalize();
  return 0;
}
