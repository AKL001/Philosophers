#include "../includes/philo_bonus.h"

int	is_simulation_running(t_data *data)
{
	int	running;
	if (!data || !data->sim_status)
		return (0);
	sem_wait(data->sim_status);
	running = data->is_simulation_running;
	sem_post(data->sim_status);
	return (running);
}

void	print_action(t_philo *philo, char *action)
{
	long long	timestamp;

	if (!philo || !philo->data || !is_simulation_running(philo->data) || !philo->data->print)
		return;
	sem_wait(philo->data->print);

	timestamp = get_time_in_ms() - philo->data->start_time;
	printf("%lld %d %s\n", timestamp, philo->id, action);

	sem_post(philo->data->print);
}

void	start_simulation(t_data *data)
{
	// data->start_time = get_time_in_ms();
	data->is_simulation_running = 1;
	if (start_processes(data))
	{
		ft_putstr_fd("Error: Failed to create processes\n", 2);
		cleanup(data);
		return ;
	}
	wait_for_processes(data);
	cleanup(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	// ft_memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo_bonus num_philos time_to_die ");
		printf("time_to_eat time_to_sleep [max_meals]\n");
		return (1);
	}
	if (init_all(&data, argc, argv) != 0)
	{
		cleanup(&data);
		return (1);
	}
	start_simulation(&data);
	return (0);
}