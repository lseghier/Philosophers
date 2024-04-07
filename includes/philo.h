/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseghier <lseghier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:30:35 by lseghier          #+#    #+#             */
/*   Updated: 2024/04/07 02:50:09 by lseghier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FORK,
	TAKE_SECOND_FORK,
	DIED,
}						t_philo_status;

typedef enum e_time_code
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}						t_time_code;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_opcode;

# define RST "\033[0m" /* Reset to default color */
# define RED "\033[1;31m" /* Red */
# define G "\033[1;32m" /* Green */
# define Y "\033[1;33m" /* Yellow */
# define B "\033[1;34m" /* Blue */
# define M "\033[1;35m" /* Magenta */
# define C "\033[1;36m" /* Cyan */
# define W "\033[1;37m" /* White */

//*******************************    STRUCTS    *****************************//
typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	bool				full;
	long				meals_counter;
	long				last_meal_time;
	pthread_t			thread_id;
	t_fork				*first_fork;
	t_fork				*second_fork;
	t_mtx				philo_mutex;
	t_table				*table;
}						t_philo;

struct					s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				philo_nbr;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	long				threads_running_nbr;
	pthread_t			monitor;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
};

//***************    PROTOTYPES     ***************

//*** functions with embedded controls to make the code DRY ***
void					safe_thread_handle(pthread_t *thread,
							void *(*dinsim)(void *), void *data,
							t_opcode opcode);
void					safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void					*safe_malloc(size_t bytes);

//*** function to process the input ***
void					parse_input(t_table *table, char **av);

//*** init table and philos data ***
void					data_init(t_table *table);

//*** function to kick in the dinner ***
void					dinner_start(t_table *table);

//*** setter and getters, very useful to write DRY code ***
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dest, long value);
bool					simulation_finished(t_table *table);

//*** utils ***
time_t					gettime(int time_code);
void					precise_usleep(long usec, t_table *table);
void					free_all(t_table *table);
void					error_exit(const char *error);

//*** write the philo status ***
void					write_status(t_philo_status status, t_philo *philo,
							bool debug);

//*** useful functions to synchro philos ***
void					wait_all_threads(t_table *table);
void					increase_long(t_mtx *mutex, long *value);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					philo_think(t_philo *philo, bool pre_simulation);
void					de_synchronize_philos(t_philo *philo);

//*** monitoring for deaths ***
void					*monitor_dinner(void *data);

#endif
