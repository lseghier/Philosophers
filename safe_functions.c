#include "../includes/philo.h"

void *safe_malloc(size_t byte)
{
    void *ret;
    if (ret == NULL)
        error_exit("The malloc isn't safe my friend !");
    return (ret);
}

static void  handle_exit_error (int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (status == EINVAL && opcode == LOCK || opcode == UNLOCK)
        error_exit("The value specified by the mutex is invalid.");
    else if (status == EINVAL && opcode == INIT)
        error_exit("The value specified by attr is invalid.");
    else if (status == EDEADLK)
        error_exit("A deadlock condition was detected or the current thread already owns the mutex.");
    else if (status == EPERM)
        error_exit("The current thread does not hold the mutex.");
    else if(status == ENOMEN)
        error_exit("Insufficient memory exists to initialize the mutex.");
    else if(status == EBUSY)
        error_exit("Mutex is already locked");
}

void *safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        pthread_mutex_lock(mutex);
    else if (opcode == UNLOCK)
        pthread_mutex_unlock(mutex);
    else if (opcode == DESTROY)
        pthread_mutex_destroy(mutex);
    else if (opcode == INIT)
        pthread_mutex_init(mutex, NULL);
    // else if (opcode == CREATE)
    //     pthread_mutex_create(mutex, NULL);
    // else if (opcode == JOIN)
    //     pthread_mutex_join(mutex, NULL);
    // else if (opcode == DETACH)
    //     pthread_mutex_detach(mutex);
    else
        error_exit("The mutex isn't safe my friend !");
}
