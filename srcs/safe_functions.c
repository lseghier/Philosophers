#include "../includes/philo.h"

void *safe_malloc(size_t byte)
{
    void *ret;
    if (ret == NULL)
        error_exit("The malloc isn't safe my friend !");
    return (ret);
}

static void  handle_mutex_error (int status, t_opcode opcode)
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
    else if(status == ENOMEM)
        error_exit("Insufficient memory exists to initialize the mutex.");
    else if(status == EBUSY)
        error_exit("Mutex is already locked");
}

void *safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
    if (opcode == LOCK)
        handle_exit_error (pthread_mutex_lock(mutex), opcode);
    else if (opcode == UNLOCK)
        handle_exit_error (pthread_mutex_unlock(mutex), opcode);
    else if (opcode == DESTROY)
        handle_exit_error (pthread_mutex_destroy(mutex), opcode);
    else if (opcode == INIT)
        handle_exit_error (pthread_mutex_init(mutex, NULL), opcode);
    else
        error_exit("The mutex isn't safe my friend !");
}

static void handle_thread_error(int status, t_opcode opcode)
{
    if (status == 0)
        return ;
    if (status == EAGAIN)
        error_exit("Insufficient resources to create another thread.");
    else if (status == EPERM)
        error_exit("No permission to set the parameters specified in attr.");
    else if (status == EINVAL && opcode == CREATE)
        error_exit ("The value specified by attr is invalid.");
    else if (status == EINVAL && opcode == JOIN || opcode == DETACH)
        error_exit("The value specified by thread is not joinable.");
    else if (status == ESRCH)
        error_exit("No thread could be found corresponding to that");
    else if (status == EDEADLK)
        error_exit("A deadlock was detected or the value of" \
        "thread specified the calling thread.");
}


void    safe_thread_handle (pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode)
{
    if (opcode == CREATE)
        handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
    else if (opcode == JOIN)
        handle_thread_error(pthread_join(*thread, NULL), opcode);
    else if (opcode == DETACH)
        handle_thread_error(pthread_detach(*thread), opcode);
    else
        error_exit ("Wrong opcode for thread_handle:" \
        " use <CREATE>  <JOIN>  <DETACH>");
}
