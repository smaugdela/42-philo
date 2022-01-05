/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maieutique.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:53:55 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/05 12:53:05 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	philo_birth(t_philo philo)
{
	pthread_t	thread_id;

	if (pthread_create(&thread_id, NULL, &ft_philo, &philo) != 0)
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

	i = 0;
	while (i < philos->table->nb_philos)
	{
		philo_birth(philos[i]);
		++i;
	}
	return(FALSE);
	return(TRUE);
}