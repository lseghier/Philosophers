#include "philo.h"

void wait_all_thread(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
       ;
       // usleep(100);
}