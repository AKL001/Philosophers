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

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

    if (philo->id % 2 == 0)
        usleep(1000); // tiny delay for even IDs to reduce collision

    while (is_simulation_running(philo->data))
    {
        print_action(philo, "is thinking");

        take_forks(philo);

        eat(philo);

        put_down_forks(philo);

        print_action(philo, "is sleeping");

        smart_sleep(philo->data->time_to_sleep, philo->data);
    }
    return (NULL);
}
