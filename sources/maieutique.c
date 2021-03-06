/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maieutique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:55 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/25 17:15:13 by smagdela         ###   ########.fr       */
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
