#include "../includes/philo.h"

void wait_all_thread(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
       ;
       // usleep(100);
}

bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
    bool ret;

    ret = false;
    safe_mutex_handle(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = true;
    return (ret);
}

void    increase_long(t_mtx *mutex, long *value)
{
    safe_mutex_handle(mutex, LOCK);
    (*value)++;
    safe_mutex_handle(mutex, UNLOCK);
}
