/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:48:04 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/01 22:48:06 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	is_numeric(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;

	if (!s || fd < 0)
		return ;
	s_len = ft_strlen(s);
	write(fd, s, s_len);
}

int	ft_atoi(const char *src)
{
	size_t	i;
	size_t	nb;
	size_t	sign;

	nb = 0;
	sign = 1;
	i = 0;
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == 32)
		i++;
	if (src[i] == '-' || src[i] == '+')
	{
		if (src[i + 1] == '+' || src[i + 1] == '-')
			return (0);
		else if (src[i] == '-')
			sign = -1;
		i++;
	}
	while (src[i] >= '0' && src[i] <= '9')
	{
		nb = (nb * 10) + (src[i] - '0');
		i++;
	}
	return (nb * sign);
}
