/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/17 18:24:22 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_state(t_philo *philo)
{
	t_bool	ret;

	ret = TRUE;
	pthread_mutex_lock(&philo->table->death_lock);
	pthread_mutex_lock(&philo->state_lock);
	if (philo->state != ALIVE || philo->table->death == TRUE)
		ret = FALSE;
	pthread_mutex_unlock(&philo->table->death_lock);
	pthread_mutex_unlock(&philo->state_lock);
	return (ret);
}

void	*faucheuse(void *info)
{
	t_philo		*philo;
	int			memento_mori;

	philo = (t_philo *)info;
	pthread_mutex_lock(&philo->state_lock);
	memento_mori = philo->nb_meals;
	pthread_mutex_unlock(&philo->state_lock);
	ft_wait(philo, philo->table->tt_die);
	pthread_mutex_lock(&philo->state_lock);
	if (philo->nb_meals <= memento_mori && philo->state == ALIVE)
		philo->state = DEAD;
	pthread_mutex_unlock(&philo->state_lock);
	return (NULL);
}

static void	*the_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	pthread_mutex_lock(&philo->state_lock);
	if (philo->table->death == FALSE && philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		pthread_mutex_unlock(&philo->state_lock);
		ft_blabla(philo, "died.");
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->death_lock);
		pthread_mutex_unlock(&philo->state_lock);
	}
	return (philo);
}

void	*ft_philo(void *info)
{
	t_philo		*philo;

	philo = (t_philo *)info;
	pthread_create(&philo->faucheuse_id, NULL, &faucheuse, philo);
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
		pthread_detach(philo->faucheuse_id);
		philo->nb_meals += 1;
		pthread_create(&philo->faucheuse_id, NULL, &faucheuse, philo);
		if (to_think(philo) == FALSE)
			break ;
	}
	pthread_detach(philo->faucheuse_id);
	return (the_end(philo));
}
