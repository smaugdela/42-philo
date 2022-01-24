/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:07:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/24 19:25:03 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_checkposint(char *nb)
{
	char	*int_extremum;
	int		i;

	int_extremum = "2147483647";
	if (nb[0] == '-' || ft_strlen(nb) > ft_strlen(int_extremum))
		return (FALSE);
	else if (ft_strlen(nb) == ft_strlen(int_extremum))
	{
		i = 0;
		while (nb[i])
		{
			if (nb[i] > int_extremum[i] || !ft_isdigit(nb[i]))
				return (FALSE);
			++i;
		}
		return (TRUE);
	}
	else
		return (TRUE);
}

uint64_t	ft_clock(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putstr_fd("Error: gettimeofday error.\n", 2);
		return (-1);
	}
	return ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
}

void	ft_blabla(t_philo *info, const char *str)
{
	pthread_mutex_lock(&info->table->death_lock);
	if (info->table->death == TRUE)
	{
		pthread_mutex_unlock(&info->table->death_lock);
		return ;
	}
	pthread_mutex_unlock(&info->table->death_lock);
	pthread_mutex_lock(&info->table->talk_lock);
	pthread_mutex_lock(&info->table->clock_lock);
	printf("%5lu %3lu %s\n",
		ft_clock() - info->table->clock_start,
		info->index, str);
	pthread_mutex_unlock(&info->table->talk_lock);
	pthread_mutex_unlock(&info->table->clock_lock);
}
