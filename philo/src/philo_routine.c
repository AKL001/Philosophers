// Philosopher thread routine (eating, sleeping, thinking)
#include "../includes/philo.h"
#include <unistd.h>

void smart_sleep(long long duration, t_data *data)
{
    long long start = get_time_in_ms();
    while (is_simulation_running(data))
    {
        if (get_time_in_ms() - start >= duration)
            break;
        usleep(100);
    }
}

// void smart_sleep(long long duration, t_data *data)
// {
//     long long start;
//     long long elapsed;
    
//     start = get_time_in_ms();
//     while (is_simulation_running(data))
//     {
//         elapsed = get_time_in_ms() - start;
//         if (elapsed >= duration)
//             break;
//         // Sleep less as we approach target time for better precision
//         if (duration - elapsed > 10)
//             usleep(1000); // 1ms sleep when we have time to spare
//         else
//             usleep(100);  // Finer granularity near the end
//     }
// }

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

    while (get_time_in_ms() < philo->data->start_time)
        continue;
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        smart_sleep(philo->data->time_to_die, philo->data);
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }

    if (philo->id % 2 == 0)
        usleep(700); // tiny delay for even IDs to reduce collision
    // 700 seems to fix that try other testes 
    while (is_simulation_running(philo->data))
    {
        take_forks(philo);
        eat(philo);
        if (put_down_forks(philo))
            break ;
        // if (!is_simulation_running(philo->data))
        //     break ;
        ft_sleep(philo);
        // if (!is_simulation_running(philo->data))
        //     break ;
        think(philo);
    }
    return (NULL);
}
