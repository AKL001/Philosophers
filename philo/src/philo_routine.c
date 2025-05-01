/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:45:05 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/01 22:45:06 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Philosopher thread routine (eating, sleeping, thinking)
#include "../includes/philo.h"
#include <unistd.h>

void	smart_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_in_ms();
	while (is_simulation_running(data))
	{
		if (get_time_in_ms() - start >= duration)
			break ;
		usleep(100);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (get_time_in_ms() < philo->data->start_time)
		continue ;
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		smart_sleep(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(700);
	while (is_simulation_running(philo->data))
	{
		take_forks(philo);
		eat(philo);
		if (put_down_forks(philo))
			break ;
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}
