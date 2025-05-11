#include "../includes/philo_bonus.h"
#include <string.h>

int	valid_arguments(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->max_meals = -1;
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (argc == 6 && data->max_meals <= 0))
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (1);
	}
	return (0);
}

int	init_semaphores(t_data *data)
{
	// int i;

	unlink_semaphores();
	// sem_unlink(SEM_SYNC);
	data->sync = sem_open(SEM_SYNC, O_CREAT, 0644, 0);
	if (data->sync == SEM_FAILED)
		return 1;
		
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->num_philos);
	if (data->forks == SEM_FAILED)
		return (1);
	
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (1);
	data->meal_check = sem_open(SEM_MEAL_CHECK, O_CREAT, 0644, 1);
	if (data->meal_check == SEM_FAILED)
		return (1);
	data->dead = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (data->dead == SEM_FAILED)
		return (1);
	// init simulation 
	data->sim_status = sem_open(SEM_SIM_STATUS, O_CREAT, 0644, 1);
	if (data->sim_status == SEM_FAILED)
		return (1);
	
	// if (data->max_meals != -1)
	// {
	// 	data->all_ate = sem_open(SEM_ALL_ATE, O_CREAT, 0644, 0);
	// 	if (data->all_ate == SEM_FAILED)
	// 		return (1);
	// }
	
	return (0);
}

static int	setup_philo_done_sem(t_data *data, int i)
{
	char	*id_str;
	char	*temp;

	id_str = ft_itoa(i);
	if (!id_str)
		return (1);
	temp = ft_strjoin(SEM_DONE_PREFIX, id_str);
	free(id_str);
	if (!temp)
		return (1);
	ft_strlcpy(data->philos[i].done_sem_name, temp,
		sizeof(data->philos[i].done_sem_name));
	free(temp);
	sem_unlink(data->philos[i].done_sem_name);
	if (data->max_meals != -1)
	{
		data->philos[i].done = sem_open(data->philos[i].done_sem_name,
				O_CREAT, 0644, 0);
		if (data->philos[i].done == SEM_FAILED)
			return (1);
	}
	return (0);
}

int	init_philosophers(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids)
	{
		free(data->philos);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		data->philos[i].done = NULL;
		data->philos[i].done_sem_name[0] = '\0';
		if (setup_philo_done_sem(data, i))
			return (1);
		i++;
	}
	return (0);
}

int	init_all(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	if (valid_arguments(argc, argv, data))
		return (1);
	if (init_semaphores(data))
	{
		ft_putstr_fd("Error: Failed to initialize semaphores\n", 2);
		close_semaphores(data);
		unlink_semaphores();
		return (1);
	}
	if (init_philosophers(data))
	{
		ft_putstr_fd("Error: Failed to initialize philosophers\n", 2);
		close_semaphores(data);
		unlink_semaphores();
		return (1);
	}
	return (0);
}
