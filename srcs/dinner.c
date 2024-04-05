#include "philo.h"

void	*dinner_simulation (void *data)
{
	t_philo *philo;

	philo = (t_philo *) data;

	wait_all_thread(philo->table);



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
	
}
