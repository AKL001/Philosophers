#include "../includes/philo_bonus.h"

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	think(t_philo *philo)
{
	long long	time_to_think;
	long long	time_since_last_meal;

	if (!is_simulation_running(philo->data))
		return ;
	print_action(philo, "is thinking");
	sem_wait(philo->data->meal_check);
	time_since_last_meal = get_time_in_ms() - philo->last_meal_time;
	time_to_think = (philo->data->time_to_die - time_since_last_meal) / 2;
	sem_post(philo->data->meal_check);
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 200)
		time_to_think = 200;
	// else if (time_to_think < 10)
	// 	time_to_think = 10;
	smart_sleep(time_to_think, philo->data);
}

void	ft_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	eat(t_philo *philo)
{
	if (!is_simulation_running(philo->data))
		return ;
	sem_wait(philo->data->meal_check);
	philo->last_meal_time = get_time_in_ms();
	print_action(philo, "\033[1;32mis eating\033[0m");
	philo->meals_eaten++;
	if (philo->data->max_meals != -1
		&& philo->meals_eaten >= philo->data->max_meals)
		sem_post(philo->data->all_ate);
	sem_post(philo->data->meal_check);
	smart_sleep(philo->data->time_to_eat, philo->data);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
}
