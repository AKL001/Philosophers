// Thread to check for philosopher deaths
#include "../includes/philo.h"


void stop_simulation(t_data *data)
{
    pthread_mutex_lock(&data->simulation_lock);
    data->is_simulation_running = 0;
    pthread_mutex_unlock(&data->simulation_lock);
}

void *monitor_threads(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    long long time_since_last_meal;

    while (is_simulation_running(data))
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->simulation_lock);
            time_since_last_meal = get_time_in_ms() - data->philos[i].last_meal_time;
            if (time_since_last_meal > data->time_to_die)
            {
                pthread_mutex_unlock(&data->simulation_lock);
                print_action(&data->philos[i], "died");
                stop_simulation(data);
                return NULL;
            }
            pthread_mutex_unlock(&data->simulation_lock);

            i++;
        }
        usleep(1000); // Sleep for 1ms to avoid CPU overload
    }
    return NULL;
}