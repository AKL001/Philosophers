// Functions to initialize structs, threads & mutexes
#include "../includes/philo.h"
#include <stdlib.h>


static int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (1);
    i = 0;
    while (i < data->num_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&data->print_lock, NULL) != 0)
        return (1);
    if (pthread_mutex_init(&data->simulation_lock, NULL) != 0)
        return (1);
    return (0);
}

static int init_philosophers(t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philosopher) * data->num_philos);
    if (!data->philos)
        return (1);
    i = 0;
    while (i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = 0;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;
        i++;
    }
    return (0);
}

int init_all(t_data *data, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [max_meals]\n");
        return (1);
    }
    if (valid_agruments(argc,argv,data))
        return (1);
    if (init_mutexes(data))
    {
        printf("Failed to initialize mutexes\n");
        return (1);
    }
    if (init_philosophers(data))
    {
        printf("Failed to initialize philosophers\n");
        return (1);
    }
    data->is_simulation_running = 1;
    // init the data->start_time long long
    // or init the data->start_time just before we start the simulation or 
    // creating threads
    return (0);
}