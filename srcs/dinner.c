#include "philo.h"

static void	philo_eat(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	safe_mutex_handle(philo->first_fork, LOCK);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(philo->second_fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	write_status(EATING, philo, DEBUG_MODE);
	philo->last_meal = gettime(MILLISECONDS);
	precise_usleep(table->time_to_eat, table);
	philo->meal_counter++;
	if (table->nbr_limit_meals > 0 && philo->meal_counter >= table->nbr_limit_meals)
		philo->full = true;
	safe_mutex_handle(philo->first_fork, UNLOCK);
	safe_mutex_handle(philo->second_fork, UNLOCK);
}

void	*dinner_simulation (void *data)
{
	t_philo *philo;

	philo = (t_philo *) data;

	wait_all_thread(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		philo_eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		// philo_sleep(philo);
		// philo_think(philo);
	}

	return (NULL);
}


void dinner_start(t_table *table)
{
	int i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else
	{
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,\
			 &table->philos[i], CREATE);
	}
	table->start_simulation = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);

	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);

}
