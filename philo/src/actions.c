#include "../includes/philo.h"
#include <pthread.h>


void put_down_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->data->simulation_lock);
    philo->last_meal_time = get_time_in_ms();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->data->simulation_lock);

    print_action(philo, "is eating");
    smart_sleep(philo->data->time_to_eat, philo->data);
}

void    take_forks(t_philosopher *philo)
{
    // we need to prevent dead locks
    if (philo->id % 2  == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);   
        print_action(philo, "has taken a fork");
    }
    else {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
    }
}
