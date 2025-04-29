#include "../includes/philo.h"

void cleanup(t_data *data)
{
    int i;

    // Free allocated memory
    if (data->philos)
        free(data->philos);
    
    // Destroy mutexes
    if (data->forks)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_destroy(&data->forks[i]);
            i++;
        }
        free(data->forks);
    }
    
    pthread_mutex_destroy(&data->print_lock);
    pthread_mutex_destroy(&data->simulation_lock);
    pthread_mutex_destroy(&data->meal_lock);
}