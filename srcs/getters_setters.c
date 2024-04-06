#include "../includes/philo.h"

void    set_bool (t_mtx *mutex, bool *var, bool value)
{
    safe_mutex_handle(mutex, LOCK);
    *var = value;
    safe_mutex_handle(mutex, UNLOCK);
}


bool    get_bool (t_mtx *mutex, bool *value)
{
    bool ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

long   get_long (t_mtx *mutex, long *value)
{
    long ret;

    safe_mutex_handle(mutex, LOCK);
    ret = *value;
    safe_mutex_handle(mutex, UNLOCK);
    return (ret);
}

void set_long (t_mtx *mutex, long *value, long new_value)
{
    safe_mutex_handle(mutex, LOCK);
    *value = new_value;
    safe_mutex_handle(mutex, UNLOCK);
}

bool    simulation_finished (t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_simulation));
}
