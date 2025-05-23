/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:44:30 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/01 22:44:32 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <pthread.h>

int	put_down_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->meal_lock);
	if (philo->meals_eaten != 0 && philo->meals_eaten == philo->data->max_meals)
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

void	think(t_philosopher *philo)
{
	long long	time_to_think;

	pthread_mutex_lock(&philo->data->meal_lock);
	time_to_think = (philo->data->time_to_die - (get_time_in_ms()
				- philo->last_meal_time)) / 2;
	pthread_mutex_unlock(&philo->data->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 200)
		time_to_think = 200;
	print_action(philo, "is thinking");
	smart_sleep(time_to_think, philo->data);
}

void	ft_sleep(t_philosopher *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	print_action(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
}

void	take_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}
