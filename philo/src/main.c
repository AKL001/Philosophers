#include "../includes/philo.h"


void print_data_state(t_data *data)
{
    printf("\n===== DATA STATE =====\n");
    printf("Number of Philosophers: %d\n", data->num_philos);
    printf("Time to Die: %d ms\n", data->time_to_die);
    printf("Time to Eat: %d ms\n", data->time_to_eat);
    printf("Time to Sleep: %d ms\n", data->time_to_sleep);
    if (data->max_meals != -1)
        printf("Max Meals: %d\n", data->max_meals);
    else
        printf("Max Meals: Unlimited\n");
    printf("Start Time: %lld\n", data->start_time);
    printf("=======================\n\n");

    printf("Philosopher Info:\n");
    for (int i = 0; i < data->num_philos; i++)
    {
        printf("Philosopher %d:\n", data->philos[i].id);
        printf("  Meals Eaten: %d\n", data->philos[i].meals_eaten);
        printf("  Last Meal Time: %lld\n", data->philos[i].last_meal_time);
        printf("  Left Fork Address: %p\n", (void *)data->philos[i].left_fork);
        printf("  Right Fork Address: %p\n", (void *)data->philos[i].right_fork);
        printf("\n");
    }
}

void start_simulation(t_data *data)
{
    pthread_t monitor;
    int       i;

    data->start_time = get_time_in_ms();
    i = -1;
    while(++i < data->num_philos)
        data->philos[i].last_meal_time = data->start_time;
    if (philos_threads(data))
        return (cleanup(data));
    if (pthread_create(&monitor, NULL, monitor_threads, data) != 0)
    {
        ft_putstr_fd("failed to create monitor thread\n",2);
        stop_simulation(data);
        while (++i < data->num_philos)
            pthread_join(data->philos[i].thread, NULL);
        cleanup(data);
        return ;
    }
    i = -1;
    while (++i < data->num_philos)
        pthread_join(data->philos[i].thread, NULL);
    pthread_join(monitor, NULL);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc == 5 || argc == 6)
    {
        if (init_all(&data, argc, argv))
            return (1);
        // print_data_state(&data);
        start_simulation(&data);
        cleanup(&data);
    }
    else {
        ft_putstr_fd("error\n", 2);
    }
    return 0;
}
