/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/24 19:57:55 by smagdela         ###   ########.fr       */
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

void	*ft_philo(void *info)
{
	t_philo		*philo;

	philo = (t_philo *)info;
	while (42)
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
	pthread_mutex_lock(philo->state_lock);
	if (philo->state == DEAD)
		ft_blabla(philo, "died.");
	pthread_mutex_unlock(philo->state_lock);
	return (philo);
}
