#include "../includes/philo_bonus.h"

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
			printf("%lld %d died\n",
				get_time_in_ms() - philo->data->start_time, philo->id);
            // sem_post(philo->data->print);
			philo->data->is_simulation_running = 0;
			sem_post(philo->data->dead);
			sem_post(philo->data->meal_check);
			return (NULL);
		}
		sem_post(philo->data->meal_check);
		usleep(1000);
	}
	return (NULL);
}

void	*meal_monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->num_philos && is_simulation_running(data))
	{
		sem_wait(data->all_ate);
		i++;
	}
	if (i == data->num_philos)
	{
		data->is_simulation_running = 0;
		sem_post(data->dead);
	}
	return (NULL);
}

int	start_processes(t_data *data)
{
	int			i;
	pthread_t	meal_monitor;

	i = 0;
	if (data->max_meals > 0)
	{
		if (pthread_create(&meal_monitor, NULL, meal_monitor_routine, data))
			return (1);
		pthread_detach(meal_monitor);
	}
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			return (1);
		else if (data->philos[i].pid == 0)
		{
			philosopher_routine(&data->philos[i]);
			exit(0);
		}
		data->pids[i] = data->philos[i].pid;
		i++;
	}
	return (0);
}

void	wait_for_processes(t_data *data)
{
	sem_wait(data->dead);
	data->is_simulation_running = 0;
	kill_processes(data);
}