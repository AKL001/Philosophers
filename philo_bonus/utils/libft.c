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

#include "../includes/philo_bonus.h"

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
size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (len == 0)
		return (src_len);
	if (len)
	{
		while (i < len - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src)
		return (NULL);
	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)(dest + i)) = *((unsigned char *)(src + i));
		i++;
	}
	return (dest);
}

static void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
		{
			*((unsigned char *)(dest + n)) = *((unsigned char *)(src + n));
		}
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	max_len;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	max_len = s1_len + s2_len;
	ptr = (char *)malloc(sizeof(char) * (max_len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memmove(ptr, s1, s1_len);
	ft_memmove(ptr + s1_len, s2, s2_len);
	ptr[max_len] = '\0';
	return (ptr);
}

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