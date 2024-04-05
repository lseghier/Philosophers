#include "philo.h"

void precise_usleep(long usec, t_table *table)
{
	long start;
	long elapsed;
	long rem;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(table))
			break ;
		elapsed	= gettime(MICROSECONDS) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECONDS) - start < usec)
				;
		}
	}
}

long gettime(t_time_code time_code)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		error_exit("gettimeofday failed");
	if (time_code == SECONDS)
		return (time.tv_sec + time.tv_usec / 1e6);
	else if (time_code == MILLISECONDS)
		return (time.tv_sec * 1000 + time.tv_usec / 1000);
	else if (time_code == MICROSECONDS)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		error_exit("Invalid time code");
	return (14);
}

void	error_exit (const char *error)
{
	printf(RED"%s\n"RST, error);
	exit(EXIT_FAILURE);
}
