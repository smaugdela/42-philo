/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:28 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static void	ft_wait(t_philo *philo, uint64_t time)
{
	uint64_t	tempus_fugit;

	pthread_mutex_lock(&philo->table->clock_lock);
	tempus_fugit = ft_clock();
	pthread_mutex_unlock(&philo->table->clock_lock);
	while (philo->state == ALIVE && philo->table->death == FALSE)
	{
		pthread_mutex_lock(&philo->table->clock_lock);
		if (ft_clock() - tempus_fugit >= time)
		{
			pthread_mutex_unlock(&philo->table->clock_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->table->clock_lock);
	}
}

static void	*faucheuse(void *info)
{
	t_philo		*philo;
	int			memento_mori;

	philo = (t_philo *)info;
	memento_mori = philo->nb_meals;
	ft_wait(philo, philo->table->tt_die);
	if (philo->nb_meals <= memento_mori)
	{
		philo->state = DEAD;
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
	}
	return (NULL);
}

void	*ft_philo(void *info)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)info;
	pthread_create(&thread, NULL, &faucheuse, philo);
	philo->faucheuse_id = thread;
	while (philo->state == ALIVE && philo->table->death == FALSE)
	{
		pthread_mutex_lock(&philo->left_fork);
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;
		
		ft_blabla(philo, "has taken left fork.");
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;

		if (philo->right_fork == NULL)
		{
			ft_wait(philo, philo->table->tt_die * 2);
			break ;
		}
		pthread_mutex_lock(philo->right_fork);
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;

		ft_blabla(philo, "has taken right fork.");
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;

		ft_blabla(philo, "is eating.");
		pthread_detach(philo->faucheuse_id);
		philo->nb_meals += 1;
		pthread_create(&philo->faucheuse_id, NULL, &faucheuse, philo);
		ft_wait(philo, philo->table->tt_eat);
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;

		if (philo->nb_meals == philo->table->full)
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_detach(philo->faucheuse_id);
			pthread_mutex_lock(&philo->table->full_lock);
			philo->table->nb_philos_full += 1;
			pthread_mutex_unlock(&philo->table->full_lock);
			philo->state = FULL;
			break ;
		}

		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		ft_blabla(philo, "is sleeping.");
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;

		ft_wait(philo, philo->table->tt_sleep);
		if (philo->state != ALIVE || philo->table->death == TRUE)
			break ;

		ft_blabla(philo, "is thinking.");
	}
	if (philo->state == ALIVE && philo->table->death == TRUE)
		ft_blabla(philo, "has left.");
	else if (philo->state == DEAD)
		ft_blabla(philo, "is dead.");
	else if (philo->state == FULL)
		ft_blabla(philo, "is full.");
	return (philo);
}
