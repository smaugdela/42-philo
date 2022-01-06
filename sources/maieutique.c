/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maieutique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:55 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/06 13:12:05 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	philo_birth(t_philo philo)
{
	if (pthread_create(philo.thread_id, NULL, &ft_philo, &philo) != 0)
	{
		pthread_mutex_lock(&philo.table->death_lock);
		philo.table->death = TRUE;
		pthread_mutex_unlock(&philo.table->death_lock);
		return (FALSE);
	}
	return (TRUE);
}

t_bool launch(t_philo *philos)
{
	int	i;

	if (philos == NULL)
		return (FALSE);
	i = 0;
	philos->table->clock_start = ft_clock();
	while (i < philos->table->nb_philos)
	{
		if (philo_birth(philos[i]) == FALSE)
			return (FALSE);
		i += 2;
	}
	i = 1;
	while (i < philos->table->nb_philos)
	{
		if (philo_birth(philos[i]) == FALSE)
			return (FALSE);
		i += 2;
	}
	return(TRUE);
}

static void init_thread_id(pthread_t *t1, pthread_t *t2)
{
	pthread_t	thread_id;
	pthread_t	faucheuse_id;

	*t1 = thread_id;
	*t2 = faucheuse_id;
}

static pthread_mutex_t init_fork_mutex(void)
{
	pthread_mutex_t	fork_mutex;

	if (pthread_mutex_init(&fork_mutex, NULL) != 0)
		ft_putstr_fd("Error: fork mutex init failed\n", 2);
	return (fork_mutex);
}

t_bool	init_philos(t_philo *philos, t_data *table)
{
	size_t			i;

	if (philos == NULL || table == NULL)
		return (FALSE);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i].index = i + 1;
		init_thread_id(philos[i].thread_id, philos[i].faucheuse_id);
		philos[i].left_fork = init_fork_mutex();
		philos[i].table = table;
		philos[i].nb_meals = 0;
		philos[i].state = ALIVE;
		++i;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i].right_fork = &philos[(i + 1) % table->nb_philos].left_fork;
		if (philos[i].right_fork == NULL)
			return (FALSE);
		++i;
	}
	return (TRUE);
}
