/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablabib <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:05:46 by ablabib           #+#    #+#             */
/*   Updated: 2025/05/15 11:05:47 by ablabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	ft_sign(int nbr)
{
	if (nbr < 0)
		return (-1);
	return (1);
}

static int	ft_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	int		sign;
	int		len;
	char	*dest;

	sign = ft_sign(nbr);
	len = ft_len(nbr);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	if (nbr == 0)
	{
		dest[0] = '0';
		return (dest);
	}
	if (nbr < 0)
		dest[0] = '-';
	while (nbr)
	{
		len--;
		dest[len] = '0' + (sign * (nbr % 10));
		nbr /= 10;
	}
	return (dest);
}
