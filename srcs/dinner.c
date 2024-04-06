#include "../includes/philo.h"

static void philo_think (t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}

void *lone_philo (void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	wait_all_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
	philo->meal_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0 \
	&& philo->meal_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

void	*dinner_simulation (void *data)
{
	t_philo *philo;

	philo = (t_philo *) data;

	wait_all_thread(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
	increase_long(&philo->table->table_mutex, &philo->table->threads_running_nbr);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		philo_eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		// philo_sleep(philo);
		philo_think(philo);
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
		safe_thread_handle(&table->philos[0].thread_id, lone_philo, &table->philos[0], CREATE);
	else
		while (++i < table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation,\
			 &table->philos[i], CREATE);
	safe_thread_handle(&table->monitor, monitor_dinner, table, CREATE);
	table->start_simulation = gettime(MILLISECONDS);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}
