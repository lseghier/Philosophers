#include "../includes/philo.h"

static bool philo_died(t_philo *philo)
{
	long	elapsed;
	long	time_to_death;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);

	elapsed = gettime(MILLISECONDS) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	time_to_death = gettime(MILLISECONDS) / 1000;

	if (elapsed > time_to_death)
		return (true);
	return (false);
}

void *monitor_dinner(void *data)
{
	int i;
	t_table *table;

	table = (t_table *) data;

	while (!all_threads_running(&table->table_mutex, &table->threads_running_nbr,\
	table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				write_status(DEAD, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
