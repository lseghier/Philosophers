#ifndef PHILOSOPHERS_H

#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

#define RST "\033[0m"
#define RED "\033[1;31m"
#define G "\033[1;32m"
#define Y "\033[1;33m"
#define B "\033[1;34m"
#define M "\033[1;35m"
#define C "\033[1;36m"
#define W "\033[1;37m"

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;


typedef pthread_mutex_t t_mtx;

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
	t_fork	*first_fork;
	t_fork	*second_fork;
	pthread_t thread_id;
	t_table *table;

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
	bool all_threads_ready;
	t_mtx *table_mutex; // avoid races while reading the table
	t_fork *forks; // arr of forks
	t_philo *philos; // arr of philos
}	t_table;


// parse functions

void	error_exit (const char *error);
void	parse_input (t_table *table, char **av);

//safe functions

void	*safe_malloc(size_t byte);
void	*safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle (pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);


#endif
