/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:37:21 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/20 17:23:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(t_philo *philo, uint64_t time)
{
	uint64_t	tempus_fugit;

	pthread_mutex_lock(&philo->table->clock_lock);
	tempus_fugit = ft_clock();
	pthread_mutex_unlock(&philo->table->clock_lock);
	while (42)
	{
		pthread_mutex_lock(&philo->table->clock_lock);
		if (ft_clock() - tempus_fugit >= time
			|| check_state(philo) == FALSE)
		{
			pthread_mutex_unlock(&philo->table->clock_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->clock_lock);
	}
}

t_bool	to_eat_even(t_philo *philo)
{
	if (philo->right_fork == NULL)
	{
		ft_wait(philo, philo->table->tt_die * 2);
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_blabla(philo, "has taken a fork.");
	if (!check_state(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->left_fork);
	ft_blabla(philo, "has taken a fork.");
	if (!check_state(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	ft_blabla(philo, "is eating.");
	return (TRUE);
}

t_bool	to_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_blabla(philo, "has taken a fork.");
	if (!check_state(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	if (philo->right_fork == NULL)
	{
		ft_wait(philo, philo->table->tt_die * 2);
		pthread_mutex_unlock(philo->left_fork);
		return (FALSE);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_blabla(philo, "has taken a fork.");
	if (!check_state(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	ft_blabla(philo, "is eating.");
	return (TRUE);
}

static t_bool	to_sleep(t_philo *philo)
{
	if (!check_state(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (FALSE);
	}
	if (philo->nb_meals == philo->table->full)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->table->full_lock);
		philo->table->nb_philos_full += 1;
		pthread_mutex_unlock(&philo->table->full_lock);
		philo->state = FULL;
		return (FALSE);
	}
	ft_blabla(philo, "is sleeping.");
	return (TRUE);
}

t_bool	to_think(t_philo *philo)
{
	if (to_sleep(philo) == FALSE)
		return (FALSE);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (!check_state(philo))
		return (FALSE);
	ft_wait(philo, philo->table->tt_sleep);
	if (!check_state(philo))
		return (FALSE);
	ft_blabla(philo, "is thinking.");
	if (!check_state(philo))
		return (FALSE);
	return (TRUE);
}
