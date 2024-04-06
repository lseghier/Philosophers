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

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

#define RST "\033[0m"
#define RED "\033[1;31m"
#define G "\033[1;32m"
#define Y "\033[1;33m"
#define B "\033[1;34m"
#define M "\033[1;35m"
#define C "\033[1;36m"
#define W "\033[1;37m"

typedef struct s_table t_table;

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

typedef enum e_philo_state
{
	THINKING,
	EATING,
	SLEEPING,
	TAKE_FORK,
	TAKE_SECOND_FORK,
	DEAD,
}	t_philo_state;

typedef enum e_time_code
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
}	t_time_code;

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
	t_mtx	philo_mutex; // useful for races with monitor
	t_table *table;

}		t_philo;

struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nbr_limit_meals;
	long start_simulation; // time stamps from the start of simulation
	bool end_simulation; // a philo dies or all philos full
	bool all_threads_ready;
	long threads_running_nbr;
	pthread_t	monitor;
	t_mtx table_mutex; // avoid races while reading the table
	t_mtx write_mutex;
	t_fork *forks; // arr of forks
	t_philo *philos; // arr of philos
};

//time
long gettime(t_time_code time_code);

// parse functions

void	error_exit (const char *error);
void	parse_input (t_table *table, char **av);

//safe functions

void	*safe_malloc(size_t byte);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle (pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

// getters and setters to have a code more readable

void    set_bool (t_mtx *mutex, bool *var, bool value);
bool    get_bool (t_mtx *mutex, bool *value);
long   get_long (t_mtx *mutex, long *value);
void set_long (t_mtx *mutex, long *value, long new_value);
bool    simulation_finished (t_table *table);
bool    all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void wait_all_thread(t_table *table);

// synchronization functions

void wait_all_thread(t_table *table);
long gettime(t_time_code time_code);
void precise_usleep(long usec, t_table *table);
void    increase_long(t_mtx *mutex, long *value);

// init and free functions

void	free_all(t_table *table);
void init_data(t_table *table);

// write function
void write_status (t_philo_state status, t_philo *philo, bool debug);

//monitoring
void *monitor_dinner(void *data);

// dining philos
void	*dinner_simulation (void *data);
void dinner_start(t_table *table);

#endif
