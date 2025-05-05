#include "../includes/philo_bonus.h"


void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor_thread;
	int			done;

	done = 0;
	philo->last_meal_time = get_time_in_ms();
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philo))
		exit(1);
	pthread_detach(monitor_thread);
	// pthread_join(monitor_thread, NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_simulation_running(philo->data))
	{
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		
		sem_wait(philo->data->meal_check);
        done = (philo->data->max_meals != -1 && 
                  philo->meals_eaten >= philo->data->max_meals);
        sem_post(philo->data->meal_check);
        
		if (done)
        {
            if (philo->data->max_meals > 0)
                sem_post(philo->done);  // Signal completion
            break;
        }
		
		ft_sleep(philo);
		
		// if (is_simulation_running(philo->data))
		// 	break;
		think(philo);
        // if (is_simulation_running(philo->data))
        //     printf("similation is done\n");
		
	}
	exit(0);
}
