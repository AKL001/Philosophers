/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:59:50 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/15 10:59:51 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	is_done(t_philo *philo)
{
	int	done;

	done = 0;
	sem_wait(philo->data->meal_check);
	done = (philo->data->max_meals != -1
			&& philo->meals_eaten >= philo->data->max_meals);
	sem_post(philo->data->meal_check);
	return (done);
}

void	philosopher_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	sem_wait(philo->data->sync);
	philo->last_meal_time = get_time_in_ms();
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philo))
		exit(1);
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_simulation_running(philo->data))
	{
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		if (is_done(philo))
		{
			if (philo->data->max_meals > 0)
				sem_post(philo->done);
			exit(0);
		}
		ft_sleep(philo);
		think(philo);
	}
	exit(0);
}
