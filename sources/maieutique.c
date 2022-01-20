/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maieutique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:55 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/20 17:50:06 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	philo_birth(t_philo *philo)
{
	pthread_t	thread_philo;

	pthread_mutex_lock(philo->state_lock);
	philo->last_meal = philo->table->clock_start;
	pthread_mutex_unlock(philo->state_lock);
	if (pthread_create(&thread_philo, NULL, &ft_philo, philo) != 0)
	{
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
		return (FALSE);
	}
	philo->thread_id = thread_philo;
	return (TRUE);
}

t_bool	launch(t_philo *philos)
{
	size_t	i;

	if (philos == NULL)
		return (FALSE);
	i = 0;
	pthread_mutex_lock(&philos->table->clock_lock);
	philos->table->clock_start = ft_clock();
	pthread_mutex_unlock(&philos->table->clock_lock);
	while (i < philos->table->nb_philos)
	{
		if (philo_birth(&philos[i]) == FALSE)
			return (FALSE);
		i += 2;
	}
	if (philos->table->nb_philos <= 1)
		return (TRUE);
	i = 1;
	usleep(200);
	while (i < philos->table->nb_philos)
	{
		if (philo_birth(&philos[i]) == FALSE)
			return (FALSE);
		i += 2;
	}
	return (TRUE);
}

static t_bool	init_philomut(t_philo *philo)
{
	pthread_mutex_t	*mutex_1;
	pthread_mutex_t	*mutex_2;

	mutex_1 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex_1 == NULL)
	{
		ft_putstr_fd("Error: philos mutexes malloc failed\n", 2);
		return (FALSE);
	}
	mutex_2 = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (mutex_2 == NULL)
	{
		free(mutex_1);
		ft_putstr_fd("Error: philos mutexes malloc failed\n", 2);
		return (FALSE);
	}
	if (pthread_mutex_init(mutex_1, NULL) != 0)
	{
		free(mutex_1);
		free(mutex_2);
		ft_putstr_fd("Error: philos mutexes initialisation failed\n", 2);
		return (FALSE);
	}
	if (pthread_mutex_init(mutex_2, NULL) != 0)
	{
		free(mutex_1);
		free(mutex_2);
		pthread_mutex_destroy(mutex_1);
		ft_putstr_fd("Error: philos mutexes initialisation failed\n", 2);
		return (FALSE);
	}
	philo->left_fork = mutex_1;
	philo->state_lock = mutex_2;
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
		philos[i].index = i + 1;
		if (!init_philomut(&philos[i]))
			return (FALSE);
		philos[i].table = table;
		philos[i].nb_meals = 0;
		philos[i].state = ALIVE;
		++i;
	}
	return (link_forks(philos, table));
}
