#include "../includes/philo_bonus.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	smart_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_in_ms();
	while (is_simulation_running(data))
	{
		if (get_time_in_ms() - start >= duration)
			break ;
		usleep(500);
	}
}