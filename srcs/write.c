#include "philo.h"

static void write_status_debug(t_philo_state status, t_philo, long elapsed)
{
    if (status == TAKE_FORK && !simulation_finished(philo->table))
        printf(W"%6ld"RST"%d has taken a fork\n", elapsed, philo->id, philo->first_fork->fork_id);
    else if (status == TAKE_SECOND_FORK && !simulation_finished(philo->table))
        printf(W"%6ld"RST"%d has taken a fork\n", elapsed, philo->id, philo->second_fork->fork_id);
    else if (status == EATING && !simulation_finished(philo->table))
        printf(W"%6ld"C"%d is eating\n", elapsed, philo->id);
    else if (status == SLEEPING && !simulation_finished(philo->table))
        printf(W"%6ld"RST"%d is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !simulation_finished(philo->table))
        printf(W"%6ld"RST"%d is thinking\n", elapsed, philo->id);
    else if (status == DIED)
        printf(RED"%6ld"D"%d died\n", elapsed, philo->id);
}

void write_status (t_philo_state status, t_philo *philo, bool debug)
{
    if (philo->full)
        return ;
    safe_mutex_handle(&philo->table->write_mutex, LOCK);
    if (debug)
        write_status_debug(status, philo, elapsed);
    else
    {
        if ((status == TAKE_FORK || status == TAKE_SECOND_FORK)
        && !simulation_finished(philo->table))
            printf (W"%-6ld"RST"%d has taken a fork\n", gettime(MILLISECONDS) - philo->table->start_simulation, philo->id);
        else if (status == EATING && !simulation_finished(philo->table))
            printf (W"%-6ld"C"%d is eating\n", gettime(MILLISECONDS) - philo->table->start_simulation, philo->id);
        else if (status == SLEEPING && !simulation_finished(philo->table))
            printf (W"%-6ld"RST"%d is sleeping\n", gettime(MILLISECONDS) - philo->table->start_simulation, philo->id);
        else if (status == THINKING && !simulation_finished(philo->table))
            printf (W"%-6ld"RST"%d is thinking\n", gettime(MILLISECONDS) - philo->table->start_simulation, philo->id);
        else if (status == DIED && !simulation_finished(philo->table))
            printf (RED"%-6ld"D"%d died\n", gettime(MILLISECONDS) - philo->table->start_simulation, philo->id);
    }
    safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}