/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:38:35 by smagdela          #+#    #+#             */
/*   Updated: 2022/01/11 15:53:17 by smagdela         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->state_lock);
	memento_mori = philo->nb_meals;
	pthread_mutex_unlock(&philo->state_lock);
	ft_wait(philo, philo->table->tt_die);
	if (philo->nb_meals <= memento_mori && philo->state == ALIVE)
	{
		pthread_mutex_lock(&philo->state_lock);
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->state_lock);
	}
	return (NULL);
}

static t_bool	check_state(t_philo *philo)
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

void	*ft_philo(void *info)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)info;
	pthread_create(&thread, NULL, &faucheuse, philo);
	philo->faucheuse_id = thread;
	while (42)
	{
		pthread_mutex_lock(&philo->left_fork);
		if (!check_state(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			break ;
		}

		ft_blabla(philo, "has taken left fork.");
		if (!check_state(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			break ;
		}

		if (philo->right_fork == NULL)
		{
			ft_wait(philo, philo->table->tt_die * 2);
			pthread_mutex_unlock(&philo->left_fork);
			break ;
		}
		pthread_mutex_lock(philo->right_fork);
		if (!check_state(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}

		ft_blabla(philo, "has taken right fork.");
		if (!check_state(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}

		ft_blabla(philo, "is eating.");
		pthread_detach(philo->faucheuse_id);
		philo->nb_meals += 1;
		pthread_create(&philo->faucheuse_id, NULL, &faucheuse, philo);
		ft_wait(philo, philo->table->tt_eat);
		if (!check_state(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}

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

		ft_blabla(philo, "is sleeping.");
		if (!check_state(philo))
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}

		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		ft_wait(philo, philo->table->tt_sleep);
		if (!check_state(philo))
			break ;

		ft_blabla(philo, "is thinking.");
		if (!check_state(philo))
			break ;
	}
	pthread_detach(philo->faucheuse_id);
	if (philo->table->death == FALSE && philo->state == DEAD)
	{
		ft_blabla(philo, "is dead.");
		pthread_mutex_lock(&philo->table->death_lock);
		philo->table->death = TRUE;
		pthread_mutex_unlock(&philo->table->death_lock);
	}
	else if (philo->state == FULL)
		ft_blabla(philo, "has finished.");
	return (philo);
}
