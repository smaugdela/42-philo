/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/25 16:38:31 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_state(t_philo *philo)
{
	t_bool	ret;

	ret = TRUE;
	pthread_mutex_lock(philo->state_lock);
	if (philo->state != ALIVE)
		ret = FALSE;
	pthread_mutex_unlock(philo->state_lock);
	return (ret);
}

static void	life(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->full_lock);
	pthread_mutex_lock(philo->state_lock);
	if (philo->nb_meals == philo->table->full)
	{
		philo->state = TERM;
		pthread_mutex_unlock(philo->state_lock);
		pthread_mutex_unlock(&philo->table->full_lock);
		return ;
	}
	pthread_mutex_unlock(philo->state_lock);
	pthread_mutex_unlock(&philo->table->full_lock);
	while (check_state(philo))
	{
		if (philo->index % 2)
		{
			if (to_eat_odd(philo) == FALSE)
				break ;
		}
		else
		{
			if (to_eat_even(philo) == FALSE)
				break ;
		}
		if (eating(philo) == FALSE)
			break ;
		if (to_think(philo) == FALSE)
			break ;
	}
}

void	*ft_philo(void *info)
{
	t_philo		*philo;

	philo = (t_philo *)info;
	life(philo);
	pthread_mutex_lock(philo->state_lock);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(philo->state_lock);
		ft_blabla(philo, "died.");
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
	}
	else
		pthread_mutex_unlock(philo->state_lock);
	return (philo);
}
