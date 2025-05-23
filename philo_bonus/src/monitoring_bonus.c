/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:59:42 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/15 10:59:43 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <string.h>

void	stop_simulation(t_data *data)
{
	sem_wait(data->sim_status);
	data->is_simulation_running = 0;
	sem_post(data->sim_status);
	sem_post(data->dead);
}

void	*monitor_routine(void *arg)
{
	t_philo		*philo;
	long long	time_since_last_meal;

	philo = (t_philo *)arg;
	while (is_simulation_running(philo->data))
	{
		sem_wait(philo->data->meal_check);
		time_since_last_meal = get_time_in_ms() - philo->last_meal_time;
		if (time_since_last_meal > philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("\033[0;31m%lld %d died\033[0m\n", get_time_in_ms()
				- philo->data->start_time, philo->id);
			sem_post(philo->data->dead);
			sem_wait(philo->data->sim_status);
			philo->data->is_simulation_running = 0;
			sem_post(philo->data->sim_status);
			sem_post(philo->data->meal_check);
			exit(1);
		}
		sem_post(philo->data->meal_check);
		usleep(500);
	}
	return (NULL);
}

void	*meal_monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (data->max_meals == 0)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		if (!is_simulation_running(data))
			break ;
		sem_wait(data->philos[i].done);
		if (!is_simulation_running(data))
			break ;
		i++;
	}
	if (i == data->num_philos && is_simulation_running(data))
	{
		sem_wait(data->sim_status);
		data->is_simulation_running = 0;
		sem_post(data->sim_status);
		sem_post(data->dead);
	}
	data->meal_monitor_running = 0;
	return (NULL);
}

int	start_processes(t_data *data)
{
	int			i;
	pthread_t	meal_monitor;

	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			return (1);
		else if (data->philos[i].pid == 0)
		{
			philosopher_routine(&data->philos[i]);
		}
		data->pids[i] = data->philos[i].pid;
		i++;
	}
	if (data->max_meals > 0)
	{
		data->meal_monitor_running = 1;
		if (pthread_create(&meal_monitor, NULL, meal_monitor_routine, data))
			return (1);
		data->meal_monitor_tid = meal_monitor;
	}
	return (0);
}

void	wait_for_processes(t_data *data)
{
	sem_wait(data->dead);
	sem_wait(data->sim_status);
	data->is_simulation_running = 0;
	sem_post(data->sim_status);
	kill_processes(data);
}
