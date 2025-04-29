// Functions for picking up forks, eating, sleeping, thinking
#include "../includes/philo.h"


long long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}



void print_action(t_philosopher *philo, char *action)
{
    pthread_mutex_lock(&philo->data->print_lock);
    if (is_simulation_running(philo->data))
    {
        printf("%lld %d %s\n", get_time_in_ms() - philo->data->start_time, philo->id, action);
    }
    pthread_mutex_unlock(&philo->data->print_lock);
}

int    philos_threads(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine, &data->philos[i]) != 0)
        {
            printf("Failed to create thread for philosopher %d\n", i);
            return 1;
        }
        i++;
    }
    return 0;
}
