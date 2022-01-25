/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:07:05 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/25 17:01:28 by smagdela         ###   ########.fr       */
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
	pthread_mutex_lock(&info->table->talk_lock);
	pthread_mutex_lock(&info->table->clock_lock);
	printf("%5lu %3lu %s\n",
		ft_clock() - info->table->clock_start,
		info->index, str);
	pthread_mutex_unlock(&info->table->death_lock);
	pthread_mutex_unlock(&info->table->talk_lock);
	pthread_mutex_unlock(&info->table->clock_lock);
}

static void	destroy_mutexes(t_data *table)
{
	pthread_mutex_destroy(&table->clock_lock);
	pthread_mutex_destroy(&table->talk_lock);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->full_lock);
}

int	clean(t_philo *philos, t_data *table)
{
	size_t	i;

	destroy_mutexes(table);
	if (philos != NULL)
	{
		i = 0;
		while (i < table->nb_philos && &philos[i] != NULL)
		{
			if (philos[i].left_fork != NULL)
			{
				pthread_mutex_destroy(philos[i].left_fork);
				free(philos[i].left_fork);
			}
			if (philos[i].state_lock != NULL)
			{
				pthread_mutex_destroy(philos[i].state_lock);
				free(philos[i].state_lock);
			}
			++i;
		}
		free(philos);
	}
	return (1);
}
