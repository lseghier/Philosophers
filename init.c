#include "philo.h"

void init_data(t_table *table)
{
    table->end_simulation = false;
    table->philos = safe_malloc(table->philo_nbr);
    
}