/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:43:14 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/03 17:11:13 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(const char *str, int fd)
{
	size_t	i;

	i = 0;
	if (str == NULL || fd < 0)
		return ;
	while(str[i])
	{
		write(fd, str + i, 1);
		++i;
	}
}

t_bool	ft_is_str_digits(const char* str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (FALSE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				sign;
	int				i;
	unsigned int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		++i;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		++i;
	}
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - 48);
		++i;
	}
	return (sign * result);
}
