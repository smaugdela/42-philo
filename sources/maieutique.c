/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maieutique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:55 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/07 11:56:30 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	philo_birth(t_philo *philo)
{
	pthread_t	thread;

	printf("Philosopher %lu is born\n", philo->index);
	if (pthread_create(&thread, NULL, &ft_philo, philo) != 0)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
		return (FALSE);
	}
	philo->thread_id = thread;
	return (TRUE);
}

t_bool launch(t_philo *philos)
{
	size_t	i;

	if (philos == NULL)
		return (FALSE);
	i = 0;
	philos->table->clock_start = ft_clock();
	while (i < philos->table->nb_philos)
	{
		if (philo_birth(&philos[i]) == FALSE)
			return (FALSE);
		i += 2;
	}
	if (philos->table->nb_philos <= 1)
		return (TRUE);
	i = 1;
	usleep(philos->table->tt_eat * 500);
	while (i < philos->table->nb_philos)
	{
		if (philo_birth(&philos[i]) == FALSE)
			return (FALSE);
		i += 2;
	}
	return(TRUE);
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
		philos[i].left_fork = init_fork_mutex();
		philos[i].table = table;
		philos[i].nb_meals = 0;
		philos[i].state = ALIVE;
		++i;
	}
	if (table->nb_philos <= 1)
	{
		philos[0].right_fork = NULL;
		return (TRUE);
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
