#include "../includes/philo_bonus.h"

void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_MEAL_CHECK);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_ALL_ATE);
	sem_unlink(SEM_DONE);
	sem_unlink(SEM_SIM_STATUS);
}

void	close_semaphores(t_data *data)
{
	// int i;
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
	if (data->sim_status)
		sem_close(data->sim_status);
	if (data->philos) {
		for (int i = 0; i < data->num_philos; i++) {
		if (data->philos[i].done)
			sem_close(data->philos[i].done);
		}
    }
	
	// if (data->philos)
	// {
	// i = -1;
	// while (++i < data->num_philos)
	// 	sem_close(data->philos[i].done);
	// }
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
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
}

void unblock_meal_monitor(t_data *data)
{
    if (data->max_meals == -1)
        return;

    for (int i = 0; i < data->num_philos; i++)
    {
        sem_post(data->philos[i].done); // Unblock meal_monitor if waiting
    }
}

void	cleanup(t_data *data)
{
	sem_wait(data->sim_status);
    data->is_simulation_running = 0;
    sem_post(data->sim_status);
    
	if (data->max_meals != -1)
		unblock_meal_monitor(data);			
    // usleep(10000);
	if (data->max_meals != -1 && data->meal_monitor_tid)
    {
        pthread_join(data->meal_monitor_tid, NULL);
		// pthread_detach(data->meal_monitor_tid);
        data->meal_monitor_tid = 0;
    }

	if (!data)
		return ;
	if (data->philos)
		free(data->philos);
	if (data->pids)
		free(data->pids);
	data->philos = NULL;
	data->pids = NULL;	
	close_semaphores(data);

	if (data->philos) {
		for (int i = 0; i < data->num_philos; i++) {
			if (data->philos[i].done_sem_name[0] != '\0') {
				sem_unlink(data->philos[i].done_sem_name);
			}
		}
	}
	unlink_semaphores();
}