#include "../includes/philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL_CHECK);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_ALL_ATE);
}

void	close_semaphores(t_data *data)
{
	if (data->forks)
		sem_close(data->forks);
	if (data->print)
		sem_close(data->print);
	if (data->meal_check)
		sem_close(data->meal_check);
	if (data->dead)
		sem_close(data->dead);
	if (data->all_ate)
		sem_close(data->all_ate);
}

void	kill_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	if (data->philos)
		free(data->philos);
	if (data->pids)
		free(data->pids);
	data->philos = NULL;
	data->pids = NULL;
	close_semaphores(data);
	unlink_semaphores();
}