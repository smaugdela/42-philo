/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:14:23 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/25 18:08:05 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*create_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
	{
		ft_putstr_fd("Error: philos mutexes malloc failed\n", 2);
		return (NULL);
	}
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		ft_putstr_fd("Error: philos mutexes initialisation failed\n", 2);
		return (NULL);
	}
	return (mutex);
}

static t_bool	init_philomut(t_philo *philo)
{
	philo->left_fork = create_mutex();
	if (philo->left_fork == NULL)
		return (FALSE);
	philo->state_lock = create_mutex();
	if (philo->state_lock == NULL)
	{
		free(philo->left_fork);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	link_forks(t_philo *philos, t_data *table)
{
	size_t	i;

	if (table->nb_philos <= 1)
	{
		philos[0].right_fork = NULL;
		return (TRUE);
	}
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i].right_fork = philos[(i + 1) % table->nb_philos].left_fork;
		if (philos[i].right_fork == NULL)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	init_philos(t_philo *philos, t_data *table)
{
	size_t			i;

	if (philos == NULL || table == NULL)
		return (FALSE);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i].table = table;
		philos[i].index = i + 1;
		if (!init_philomut(&philos[i]))
			return (FALSE);
		philos[i].nb_meals = 0;
		philos[i].state = ALIVE;
		++i;
	}
	return (link_forks(philos, table));
}
