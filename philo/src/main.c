/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:44:49 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/01 22:44:51 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_simulation(t_data *data)
{
	pthread_t	monitor;
	int			i;

	data->start_time = get_time_in_ms();
	i = -1;
	while (++i < data->num_philos)
		data->philos[i].last_meal_time = data->start_time;
	if (philos_threads(data))
		return (cleanup(data));
	if (pthread_create(&monitor, NULL, monitor_threads, data) != 0)
	{
		ft_putstr_fd("failed to create monitor thread\n", 2);
		stop_simulation(data);
		while (++i < data->num_philos)
			pthread_join(data->philos[i].thread, NULL);
		cleanup(data);
		return ;
	}
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (init_all(&data, argc, argv))
			return (1);
		start_simulation(&data);
		cleanup(&data);
	}
	else
		ft_putstr_fd("error\n", 2);
	return (0);
}
