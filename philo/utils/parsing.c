/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:48:11 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/01 22:48:12 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdbool.h>

bool check(const char *str)
{
	int i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while(str[i]) 
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return true;
	}
	return false;
}

int	valid_philo_num(const char *arg)
{
	if (check(arg) || ft_atoi(arg) <= 0)
	{
		ft_putstr_fd("Error: Invalid number of philosophers argument\n", 2);
		return (1);
	}
	return (0);
}

int	valid_ms(const char *arg)
{
	if (check(arg) ||ft_atoi(arg) <= 0)
	{
		ft_putstr_fd("Error: Invalid number of ms argument\n", 2);
		return (1);
	}
	return (0);
}

int	valid_must_eat(const char *arg)
{
	if (check(arg) ||ft_atoi(arg) <= 0)
	{
		ft_putstr_fd("Error: Invalid number of must eat argument\n", 2);
		return (1);
	}
	return (0);
}

int	valid_agruments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("more than 6 args or less than 5\n", 2);
		return (1);
	}
	if (valid_philo_num(argv[1]) || valid_ms(argv[2]) || valid_ms(argv[3])
		|| valid_ms(argv[4]) || (argc == 6 && valid_must_eat(argv[5])))
	{
		return (1);
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	return (0);
}
