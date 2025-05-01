/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:44:58 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/01 22:44:59 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Thread to check for philosopher deaths
#include "../includes/philo.h"

void	stop_simulation(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	data->is_simulation_running = 0;
	pthread_mutex_unlock(&data->simulation_lock);
}

int	is_simulation_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(&data->simulation_lock);
	running = data->is_simulation_running;
	pthread_mutex_unlock(&data->simulation_lock);
	return (running);
}

int	all_philos_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->max_meals == -1)
		return (0);
	pthread_mutex_lock(&data->meal_lock);
	all_ate = 1;
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (all_ate);
}

int	someone_died(t_data *data)
{
	int			i;
	long long	now;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_lock);
		now = get_time_in_ms();
		if (now - data->philos[i].last_meal_time > data->time_to_die)
		{
			pthread_mutex_unlock(&data->meal_lock);
			stop_simulation(data);
			pthread_mutex_lock(&data->print_lock);
			printf("%lld %d died\n", now - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (0);
}

void	*monitor_threads(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (is_simulation_running(data))
	{
		if (someone_died(data))
			break ;
		if (data->max_meals != -1 && all_philos_ate(data))
		{
			stop_simulation(data);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
