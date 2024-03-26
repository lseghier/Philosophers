#ifndef PHILOSOPHERS_H

#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx fork;
	int fork_id;
}		t_fork;

typedef struct s_philo
{
	int		id;
	long	meal_counter;
	bool	full;
	long	last_meal_time;
	t_fork	*left_fork;
	t_fork	*right_fork;
	pthread_t thread_id;

}		t_philo;

typedef struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nbr_limit_meals;
	long start_simulation; // time stamps from the start of simulation
	bool end_simulation; // a philo dies or all philos full
	t_fork *fork; // arr of forks
	t_philo *philos; // arr of philos
}	t_table;


// parse functions

void	error_exit (const char *error);




#endif
