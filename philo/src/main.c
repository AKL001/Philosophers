#include "../includes/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    t_data *philo = NULL;

    // memset(&philo, 0, sizeof(t_data *));
    philo = malloc(sizeof(t_data *));
    if (!philo)
        return (printf("failed allocation\n"),1);
    if (valid_agruments(argc, argv, philo))
        return (free(philo), 1);
    else
    {
        printf("num_philo[%d]\n",philo->num_philos);
        printf("num_philo[%d]\n",philo->time_to_die);
        printf("num_philo[%d]\n",philo->time_to_eat);
        printf("num_philo[%d]\n",philo->time_to_sleep);
        if (philo->max_meals != -1)
            printf("num_philo[%d]\n",philo->max_meals);
    }
        
    return 0;
}
