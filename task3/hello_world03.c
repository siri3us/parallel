#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const double kLowerBound = 270;
const double kUpperBound = 271;

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

  printf("Processor \"%s\" with rank %d/%d\n",
         processor_name, world_comm_rank, world_comm_size);

  MPI_Status mpi_status;
  // Теперь начинаем работу
  if (world_comm_rank == 0) {
    // world_comm_rank == 0 - это master-процессор
    srand(0);  // Вместо нуля можно поставить другое число
    int sent_messages_number = 0;
    int message_pairs_number = 0;
    // Входим в бесконечный цикл опроса slave-процессоров. Выйдем из цикла, когда итоговая сумма
    // окажется в требуемом диапазоне
    double sum = 0;
    bool sum_in_range = false;
    while (true) {
      // Шаг 1. Отправка чисел slave-процессорам
      int target_process_rank;
      for (target_process_rank = 1; target_process_rank < world_comm_size; target_process_rank++) {
        // Генерируем число на отправку в диапазоне [0.0, 180.0]
        double number_to_send = 1.0 * rand() / RAND_MAX * 180.0;
        // Отправляем число одному из процессоров
        MPI_Send((void*) &number_to_send,
                 sizeof(double),
                 MPI_DOUBLE,
                 target_process_rank,
                 sent_messages_number,
                 MPI_COMM_WORLD);
        // printf("Number %.6f sent from master-process 0 to process %d\n",
        //        number_to_send, target_process_rank);
      }
      sent_messages_number += 1;
      // Шаг 2. Получение ответов от slave-процессоров
      for (target_process_rank = 1;
           target_process_rank < world_comm_size;
           target_process_rank++) {
        double received_number;
        MPI_Recv((void*) &received_number,
                 sizeof(received_number),
                 MPI_DOUBLE,
                 target_process_rank,
                 sent_messages_number,
                 MPI_COMM_WORLD,
                 &mpi_status);
        // Ответ от очередного процессора получен - добавляем его к сумме
        message_pairs_number += 1;
        sum = fmod(sum + received_number, 360.0);
        sum_in_range = sum < kUpperBound && sum > kLowerBound;
        if (sum_in_range == true) {
          // Останавливаем опрос slave-процессоров: больше в этом нет необходимости
          break;
        }
      }
      // Проверяем, лежит ли итоговая сумма в нужном диапазоне
      if (sum_in_range) {
        // Шлем всем slave-ам сигнал о завершении - отрицательное число
        printf("The final number is %f\n", sum);
        double number_to_send = -1;
        for (target_process_rank = 1;
              target_process_rank < world_comm_size;
              target_process_rank++) {
          MPI_Send((void*) &number_to_send,
                  sizeof(double),
                  MPI_DOUBLE,
                  target_process_rank,
                  sent_messages_number,
                  MPI_COMM_WORLD);
        }
        // Выходим из бесконечного цикла
        break;
      }
    }
    // Шаг 3. Печать в терминал и файл RESULT.txt
    FILE* file = fopen("RESULT.txt", "w"); 
    fprintf(file, "Ping-pong pairs number = %d\n", message_pairs_number);
    fprintf(stderr, "Ping-pong pairs number = %d\n", message_pairs_number);
  } else {
    int received_messages_number = 0;
    while (true) {
      double received_number;
      MPI_Recv((void*) &received_number,
               sizeof(double),
               MPI_DOUBLE,
               0,
               received_messages_number,
               MPI_COMM_WORLD,
               &mpi_status);
      received_messages_number += 1;
      if (received_number < 0) {
        // Эффект достигнут - выходим из бесконечного цилка и завершаем работу
        break;
      } else {
        // Отправляем число обратно master-процессу
        MPI_Send((void*) &received_number,
                 sizeof(double),
                 MPI_DOUBLE,
                 0,  // Номер процессора, которому шлем сообщение 
                 received_messages_number,
                 MPI_COMM_WORLD);

      }
    }
  }

  // Завершение работы MPI
  MPI_Finalize();
  return 0;
}
