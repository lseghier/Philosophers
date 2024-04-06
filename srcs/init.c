#include "../includes/philo.h"

static void assign_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
    int philo_nbr;

    philo_nbr = philo->table->philo_nbr;

    philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
    philo->second_fork = &forks[philo_pos];
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_pos];
        philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
    }
}

static void philo_init(t_table *table)
{
    int i;
    t_philo *philo;

    i = -1;
    while (++i < table->philo_nbr)
    {
        philo = table->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meal_counter = 0;
        safe_mutex_handle(&philo->philo_mutex, INIT);
        philo->table = table;
        assign_forks(philo, table->forks, i);
    }
}

void init_data(t_table *table)
{
    int i;

    i = -1;
    table->end_simulation = false;
    table->all_threads_ready = false;
    table->threads_running_nbr = 0;
    table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
    safe_mutex_handle(&table->write_mutex, INIT);
    safe_mutex_handle(&table->table_mutex, INIT);
    table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
    while (++i < table->philo_nbr)
    {
        safe_mutex_handle(&table->forks[i].fork, INIT);
        table->forks[i].fork_id = i;
    }
    philo_init(table);
}
